/*
 * Copyright (C)      2023 Colin Ian King
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */
#include <immintrin.h>
#include <string.h>
#include <stdlib.h>

void rndset(unsigned char *ptr, const size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		ptr[i] = random();
}

int __attribute__ ((target("avx512bw"))) main(int argc, char **argv)
{
	__m512i r;
	unsigned char a[256];

	(void)rndset((unsigned char *)&a, sizeof(a));
	r = _mm512_loadu_si512((void *)a);

	return *(int *)&r;
}