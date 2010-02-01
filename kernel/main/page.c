/*-
 * Physical page allocator code.
 *
 * Copyright (c) 2009 Andrei Homescu
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer
 * in this position and unchanged.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#include <sys/queue.h>
#include <sys/types.h>

#include <machine/vmparam.h>

#define	MAX_REGIONS_SHIFT	10
#define	MAX_REGIONS		(1 << MAX_REGIONS_SHIFT)
#define	NULL_REGION		(-1)

struct region {
	paddr_t addr;
        psize_t size;
	int next;
} regions[MAX_REGIONS];

struct overlapping_regions {
	int last_before, first_deleted, first_after;
	paddr_t head_addr, tail_addr;
};

static int next_unalloc_region, next_avail_region;

void page_init() {
	int i;
	for (i = 0; i < MAX_REGIONS - 1; i++) {
		regions[i].next = i + 1;
	}
	regions[MAX_REGIONS - 1].next = NULL_REGION;
	next_unalloc_region = 0;
	next_avail_region = NULL_REGION;
}

static int alloc_region() {
	if (next_unalloc_region == NULL_REGION) {
		printf("ERROR: no free regions\n");
		return NULL_REGION;
	}

	int res = next_unalloc_region;
	next_unalloc_region = regions[res].next;
	return res;
}

static void free_region(int reg) {
	regions[reg].next = next_unalloc_region;
	next_unalloc_region = reg;
}

static void insert_region_after(int reg, int prev) {
	if (prev == NULL_REGION) {
		next_avail_region = reg;
	} else {
		regions[prev].next = reg;
	}
}

static void find_overlapping_regions(paddr_t start, paddr_t end,
				     struct overlapping_regions *ovr) {
	int curr;
	paddr_t cstart, cend;

	ovr->head_addr = start;
	ovr->tail_addr = end;
	ovr->last_before = NULL_REGION;
	ovr->first_deleted = NULL_REGION;
	ovr->first_after = NULL_REGION;
	for (curr = next_avail_region; curr != NULL_REGION; 
	     curr = regions[curr].next) {
		cstart = regions[curr].addr;
		cend = regions[curr].addr + regions[curr].size;
		if (cend <= start) {
			ovr->last_before = curr;
			continue;
		}
		if (cstart >= end) {
			ovr->first_after = curr;
			break;
		}
		if (cstart < start) 
			ovr->head_addr = cstart;
		if (cend > end) 
			ovr->tail_addr = cend;
		if (ovr->first_deleted == NULL_REGION)
			ovr->first_deleted = curr;
	}
}

static void delete_overlapping_regions(struct overlapping_regions *ovr) {
	/* Delete the old interval of regions from the list */
	int curr, new_reg;
	for (curr = ovr->first_deleted; curr != ovr->first_after; ) {
		new_reg = regions[curr].next;
		free_region(curr);
		curr = new_reg;
	}

}

void set_region_reserved(paddr_t addr, psize_t size) {
	/* Align the region to page boundaries */
	size = (addr + size + PAGE_SIZE - 1) >> PAGE_SHIFT - 
		addr >> PAGE_SHIFT;
	addr >>= PAGE_SHIFT;
	if (!size)
		return;
	
	paddr_t end = addr + size;
	struct overlapping_regions ovr;
	int new_reg = NULL_REGION;
	find_overlapping_regions(addr, end, &ovr);
	if (ovr.head_addr < addr) {
		/* Add a new element for the region just before this one */
		new_reg = alloc_region();
		regions[new_reg].addr = ovr.head_addr;
		regions[new_reg].size = addr - ovr.head_addr;
		insert_region_after(new_reg, ovr.last_before);
		ovr.last_before = new_reg;
	}	
	if (ovr.tail_addr > end) {
		/* Add a new element for the region remaining at the end */
		new_reg = alloc_region();
		regions[new_reg].addr = end;
		regions[new_reg].size = ovr.tail_addr - end;
		insert_region_after(new_reg, ovr.last_before);
		ovr.last_before = new_reg;
	}
	insert_region_after(ovr.first_after, ovr.last_before);
	delete_overlapping_regions(&ovr);
}

void set_region_available(paddr_t addr, psize_t size) {
	/* Align the region to page boundaries */
	size = (addr + size) >> PAGE_SHIFT - 
		(addr + PAGE_SIZE - 1) >> PAGE_SHIFT;
	addr = (addr + PAGE_SIZE - 1) >> PAGE_SHIFT;
	if (!size)
		return;

	int new_reg = alloc_region();
	struct overlapping_regions ovr;
	find_overlapping_regions(addr, addr + size, &ovr);
	regions[new_reg].addr = ovr.head_addr;
	regions[new_reg].size = ovr.tail_addr - ovr.head_addr;
	insert_region_after(new_reg, ovr.last_before);
	insert_region_after(ovr.first_after, new_reg);
	delete_overlapping_regions(&ovr);
}

paddr_t page_alloc() {
	int curr = next_avail_region;
	if (curr == NULL_REGION) {
		printf("ERROR: no free pages\n");
		return (paddr_t)NULL;
	}

	paddr_t res = regions[curr].addr << PAGE_SHIFT;
	regions[curr].addr++;
	regions[curr].size--;
	if (!regions[curr].size) {
		/* Update the pointer from the previous element */
		next_avail_region = regions[curr].next;
		free_region(curr);
	}
	return res;
}

void page_free(paddr_t addr) {
	addr &= ~PAGE_MASK;
	set_region_available(addr, PAGE_SIZE);
}

