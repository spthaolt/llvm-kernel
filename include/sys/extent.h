/*	$NetBSD: extent.h,v 1.18 2008/04/28 20:24:10 martin Exp $	*/

/*-
 * Copyright (c) 1996, 1998 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason R. Thorpe.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _SYS_EXTENT_H_
#define _SYS_EXTENT_H_

#include <sys/queue.h>
#include <sys/mutex.h>
#include <sys/condvar.h>

struct extent_region {
	LIST_ENTRY(extent_region) er_link;	/* link in region list */
	u_long 	er_start;		/* start of region */
	u_long	er_end;			/* end of region */
	int	er_flags;		/* misc. flags */
};

/* er_flags */
#define ER_ALLOC	0x01	/* region descriptor dynamically allocated */

struct extent {
	const char *ex_name;		/* name of extent */
	kmutex_t ex_lock;		/* lock on this extent */
	kcondvar_t ex_cv;		/* synchronization */
					/* allocated regions in extent */
	LIST_HEAD(, extent_region) ex_regions;
	u_long	ex_start;		/* start of extent */
	u_long	ex_end;			/* end of extent */
	struct malloc_type *ex_mtype;	/* memory type */
	int	ex_flags;		/* misc. information */
};

struct extent_fixed {
	struct extent	fex_extent;	/* MUST BE FIRST */
					/* freelist of region descriptors */
	LIST_HEAD(, extent_region) fex_freelist;
	void *		fex_storage;	/* storage space for descriptors */
	size_t		fex_storagesize; /* size of storage space */
};

/* ex_flags; for internal use only */
#define EXF_FIXED	0x01		/* extent uses fixed storage */
#define EXF_NOCOALESCE	0x02		/* coalescing of regions not allowed */
#define EXF_FLWANTED	0x08		/* someone asleep on freelist */

#define EXF_BITS	"\20\4FLWANTED\2NOCOALESCE\1FIXED"

/* misc. flags passed to extent functions */
#define EX_NOWAIT	0x00		/* not safe to sleep */
#define EX_WAITOK	0x01		/* safe to sleep */
#define EX_FAST		0x02		/* take first fit in extent_alloc() */
#define EX_CATCH	0x04		/* catch signals while sleeping */
#define EX_NOCOALESCE	0x08		/* create a non-coalescing extent */
#define EX_MALLOCOK	0x10		/* safe to call malloc() */
#define EX_WAITSPACE	0x20		/* wait for space to become free */
#define EX_BOUNDZERO	0x40		/* boundary lines start at 0 */

/*
 * Special place holders for "alignment" and "boundary" arguments,
 * in the event the caller doesn't wish to use those features.
 */
#define EX_NOALIGN	1		/* don't do alignment */
#define EX_NOBOUNDARY	0		/* don't do boundary checking */

#if defined(_KERNEL) || defined(_EXTENT_TESTING)
#define EXTENT_FIXED_STORAGE_SIZE(_nregions)		\
	(ALIGN(sizeof(struct extent_fixed)) +		\
	((ALIGN(sizeof(struct extent_region))) *	\
	 (_nregions)))

struct malloc_type;

struct	extent *extent_create(const char *, u_long, u_long,
	    struct malloc_type *, void *, size_t, int);
void	extent_destroy(struct extent *);
int	extent_alloc_subregion1(struct extent *, u_long, u_long,
	    u_long, u_long, u_long, u_long, int, u_long *);
int	extent_alloc_subregion(struct extent *, u_long, u_long,
	    u_long, u_long, u_long, int, u_long *);
int	extent_alloc_region(struct extent *, u_long, u_long, int);
int	extent_alloc1(struct extent *, u_long, u_long, u_long, u_long, int,
	    u_long *);
int	extent_alloc(struct extent *, u_long, u_long, u_long, int, u_long *);
int	extent_free(struct extent *, u_long, u_long, int);
void	extent_print(struct extent *);
void	extent_init(void);

#endif /* _KERNEL || _EXTENT_TESTING */

#endif /* ! _SYS_EXTENT_H_ */
