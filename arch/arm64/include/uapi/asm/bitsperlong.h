/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __ASM_BITSPERLONG_H
#define __ASM_BITSPERLONG_H

#if defined(__aarch64__) && defined(__ILP32__)
#  define __BITS_PER_LONG 32
#else
/*
 * LP64. The AArch32 compat vDSO is built from these headers with an arm
 * compiler (neither __LP64__ nor __ILP32__); it gets 64, as it always has.
 */
#  define __BITS_PER_LONG 64
#endif

#include <asm-generic/bitsperlong.h>

#endif	/* __ASM_BITSPERLONG_H */
