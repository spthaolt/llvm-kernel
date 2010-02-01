/*-
 * Multiboot-specific entry point.
 *
 * Copyright (c) 2009 Alex Suhan & Andrei Homescu
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

#include <multiboot.h>

/* Physical memory addresses of the kernel */
#define	KERNEL_START		0x100000
#define	KERNEL_END		_end

/* The video memory address. */
#define VIDEO                   0xB8000

/* Magic values for 80x24 VGA text mode */
#define COLUMNS                 80
#define LINES                   25

/* Text color */
#define WHITE               	15

#define IS_SET(bit, flags)		((flags) & (1 << (bit)))

/* Character coordinates and pointer to the video memory. */
static int column;
static int line;
static volatile unsigned char *video;

extern main();

static void memset(void *s, int c, size_t n)
{
	unsigned i = 0;
	
	for (; i < n; i++)
		*((char *) s + i) = c;
}

/* Put a character on the screen. */
void putc(char c, int color)
{
	switch (c)
	{
		case '\n':
			line++;
		case '\r':
			column = 0;
			break;
		default:
			video[2 * (column + line * COLUMNS)] = c;
			video[2 * (column + line * COLUMNS) + 1] = color;
			column++;
	}
	
	if (column == COLUMNS)
	{
		line++;
		column = 0;
	}
	if (line == LINES)
		line = 0;
}

/* Echo a message - no bounds checking or other "fancy" stuff */
void echo(const char *message, int color)
{
	int char_idx = 0;
	
	for (char_idx = 0; message[char_idx] != 0; char_idx++)
		putc(message[char_idx], color);
}

/* Init the video memory pointer and character coordinates. */
static void init_video()
{
	video = (unsigned char *) VIDEO;
	column = 0;
	line = 0;
}

/* Clear the screen */
static void clear_screen()
{
	memset((void *) video, 0, COLUMNS * LINES * 2);
}

void mb_main(unsigned long magic, struct multiboot_info *mb_info)
{
	int color_idx = 0;
	
	init_video();
	clear_screen();
	
	/* test palette */
	for (; color_idx < 16; color_idx++)
		putc('*', color_idx);
	putc('\n', -1);
	
	printf("LLVM kernel started, using printf: 0x%02x\n\n", 255);
	
	/* dump multiboot flags */
	printf("mi_flags = 0x%x\n\n", (unsigned) mb_info->mi_flags);
	
	/* print multiboot memory limits */
	if (IS_SET(0, mb_info->mi_flags)) {
		printf("mi_mem_lower = %u KB\n", (unsigned) mb_info->mi_mem_lower);
		printf("mi_mem_upper = %u KB\n", (unsigned) mb_info->mi_mem_upper);
	}
	
	if (IS_SET(6, mb_info->mi_flags))
	{
		multiboot_mmap_t *crt_mmap = (multiboot_mmap_t *) mb_info->mi_mmap_addr;
		
		printf("mi_mmap_addr = 0x%08x\n", (unsigned) mb_info->mi_mmap_addr);
		printf("mi_mmap_length = %u\n\n", (unsigned) mb_info->mi_mmap_length);
		
		while ((unsigned) crt_mmap < mb_info->mi_mmap_addr + mb_info->mi_mmap_length) {
			printf("mm_size = %0u ", (unsigned) crt_mmap->mm_size);
			printf("mm_base_addr = 0x%08x ",
			       (unsigned) crt_mmap->mm_base_addr);
			printf("mm_length = 0x%08x ",
			       (unsigned) crt_mmap->mm_length);
			printf("mm_type = %u\n", crt_mmap->mm_type);
			
			crt_mmap = (multiboot_mmap_t *) ((unsigned) crt_mmap +
			                                 crt_mmap->mm_size +
			                                 sizeof(crt_mmap->mm_size));
		}
    }
	
	echo("\nLLVM kernel - entering eternal loop\n", WHITE);
	
 	main();
}
