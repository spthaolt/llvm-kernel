/*	$NetBSD: fgetwln.c,v 1.3 2009/09/24 20:38:53 roy Exp $	*/

/*-
 * Copyright (c) 2002-2004 Tim J. Robbins.
 * All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
#if 0
__FBSDID("$FreeBSD: src/lib/libc/stdio/fgetwln.c,v 1.2 2004/08/06 17:00:09 tjr Exp $");
#else
__RCSID("$NetBSD: fgetwln.c,v 1.3 2009/09/24 20:38:53 roy Exp $");
#endif
#endif /* LIBC_SCCS and not lint */

#include "namespace.h"
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "reentrant.h"
#include "local.h"

#ifdef __weak_alias
__weak_alias(fgetwln,_fgetwln)
#endif

/*
 * Expand the line buffer.  Return -1 on error.
#ifdef notdef
 * The `new size' does not account for a terminating '\0',
 * so we add 1 here.
#endif
 */
static int
__slbexpand(FILE *fp, size_t newsize)
{
	void *p;

#ifdef notdef
	++newsize;
#endif
	_DIAGASSERT(fp != NULL);

	/* fp->_lb._size is an int ..... */
	if (newsize > INT_MAX) {
		errno = EOVERFLOW;
		return (-1);
	}
	if ((size_t)fp->_lb._size >= newsize)
		return (0);
	if ((p = realloc(fp->_lb._base, newsize)) == NULL)
		return (-1);
	fp->_lb._base = p;
	fp->_lb._size = newsize;
	return (0);
}

wchar_t *
fgetwln(FILE * __restrict fp, size_t *lenp)
{
	wint_t wc;
	size_t len;

	FLOCKFILE(fp);
	_SET_ORIENTATION(fp, 1);

	len = 0;
	while ((wc = __fgetwc_unlock(fp)) != WEOF) {
#define	GROW	512
		if (len * sizeof(wchar_t) >= (size_t)fp->_lb._size &&
		    __slbexpand(fp, (len + GROW) * sizeof(wchar_t)))
			goto error;
		*((wchar_t *)(void *)fp->_lb._base + len++) = wc;
		if (wc == L'\n')
			break;
	}
	if (len == 0)
		goto error;

	FUNLOCKFILE(fp);
	*lenp = len;
	return ((wchar_t *)(void *)fp->_lb._base);

error:
	FUNLOCKFILE(fp);
	*lenp = 0;
	return (NULL);
}