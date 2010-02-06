/*-
 * Process management code
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
#include <sys/types.h>
#include <sys/proc.h>
#include <sys/queue.h>

pid_t next_pid;
struct proc proc_table[MAX_RUNNING_PROCESSES];
struct proc *next_proc_hint;
struct proc *current;

struct proc *alloc_proc() {
	struct proc *res;
	/* Find a free process starting from the hint */
	for (res = next_proc_hint; res != proc_table + MAX_RUNNING_PROCESSES; res++) {
		if (!res->pid)
			goto found_proc;
	}
	/* Reached the end of the array, wrap around */
	for (res = proc_table; res != next_proc_hint; res++) {
		if (!res->pid)
			goto found_proc;
	}
	return NULL;

found_proc:
	/* Advance the "hint" for the next search */
	next_proc_hint = res;
	next_proc_hint++;

	res->pid = next_pid;
	next_pid++;
	return res;
}

void proc_init() {
	next_pid = 1;
	next_proc_hint = &proc_table[0];

	/* Allocate the first process */
	current = alloc_proc();
}


