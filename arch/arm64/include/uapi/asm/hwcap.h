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
#ifndef _UAPI__ASM_HWCAP_H
#define _UAPI__ASM_HWCAP_H

/*
 * Bits 32 and up. unsigned long is 32-bit for ILP32; there these bits cannot be seen
 * through the 32-bit entries of the auxiliary vector, but the values stay in range.
 * The same definition as glibc's <bits/hwcap.h>.
 */
#ifdef __LP64__
#define __AARCH64_HWCAP64(n)	(1UL << (n))
#else
#define __AARCH64_HWCAP64(n)	(1ULL << (n))
#endif

/*
 * HWCAP flags - for AT_HWCAP
 *
 * Bits 62 and 63 are reserved for use by libc.
 * Bits 32-61 are unallocated for potential use by libc.
 */
#define HWCAP_FP		(1 << 0)
#define HWCAP_ASIMD		(1 << 1)
#define HWCAP_EVTSTRM		(1 << 2)
#define HWCAP_AES		(1 << 3)
#define HWCAP_PMULL		(1 << 4)
#define HWCAP_SHA1		(1 << 5)
#define HWCAP_SHA2		(1 << 6)
#define HWCAP_CRC32		(1 << 7)
#define HWCAP_ATOMICS		(1 << 8)
#define HWCAP_FPHP		(1 << 9)
#define HWCAP_ASIMDHP		(1 << 10)
#define HWCAP_CPUID		(1 << 11)
#define HWCAP_ASIMDRDM		(1 << 12)
#define HWCAP_JSCVT		(1 << 13)
#define HWCAP_FCMA		(1 << 14)
#define HWCAP_LRCPC		(1 << 15)
#define HWCAP_DCPOP		(1 << 16)
#define HWCAP_SHA3		(1 << 17)
#define HWCAP_SM3		(1 << 18)
#define HWCAP_SM4		(1 << 19)
#define HWCAP_ASIMDDP		(1 << 20)
#define HWCAP_SHA512		(1 << 21)
#define HWCAP_SVE		(1 << 22)
#define HWCAP_ASIMDFHM		(1 << 23)
#define HWCAP_DIT		(1 << 24)
#define HWCAP_USCAT		(1 << 25)
#define HWCAP_ILRCPC		(1 << 26)
#define HWCAP_FLAGM		(1 << 27)
#define HWCAP_SSBS		(1 << 28)
#define HWCAP_SB		(1 << 29)
#define HWCAP_PACA		(1 << 30)
#define HWCAP_PACG		(1UL << 31)

/*
 * HWCAP2 flags - for AT_HWCAP2
 */
#define HWCAP2_DCPODP		(1 << 0)
#define HWCAP2_SVE2		(1 << 1)
#define HWCAP2_SVEAES		(1 << 2)
#define HWCAP2_SVEPMULL		(1 << 3)
#define HWCAP2_SVEBITPERM	(1 << 4)
#define HWCAP2_SVESHA3		(1 << 5)
#define HWCAP2_SVESM4		(1 << 6)
#define HWCAP2_FLAGM2		(1 << 7)
#define HWCAP2_FRINT		(1 << 8)
#define HWCAP2_SVEI8MM		(1 << 9)
#define HWCAP2_SVEF32MM		(1 << 10)
#define HWCAP2_SVEF64MM		(1 << 11)
#define HWCAP2_SVEBF16		(1 << 12)
#define HWCAP2_I8MM		(1 << 13)
#define HWCAP2_BF16		(1 << 14)
#define HWCAP2_DGH		(1 << 15)
#define HWCAP2_RNG		(1 << 16)
#define HWCAP2_BTI		(1 << 17)
#define HWCAP2_MTE		(1 << 18)
#define HWCAP2_ECV		(1 << 19)
#define HWCAP2_AFP		(1 << 20)
#define HWCAP2_RPRES		(1 << 21)
#define HWCAP2_MTE3		(1 << 22)
#define HWCAP2_SME		(1 << 23)
#define HWCAP2_SME_I16I64	(1 << 24)
#define HWCAP2_SME_F64F64	(1 << 25)
#define HWCAP2_SME_I8I32	(1 << 26)
#define HWCAP2_SME_F16F32	(1 << 27)
#define HWCAP2_SME_B16F32	(1 << 28)
#define HWCAP2_SME_F32F32	(1 << 29)
#define HWCAP2_SME_FA64		(1 << 30)
#define HWCAP2_WFXT		(1UL << 31)
#define HWCAP2_EBF16		__AARCH64_HWCAP64 (32)
#define HWCAP2_SVE_EBF16	__AARCH64_HWCAP64 (33)
#define HWCAP2_CSSC		__AARCH64_HWCAP64 (34)
#define HWCAP2_RPRFM		__AARCH64_HWCAP64 (35)
#define HWCAP2_SVE2P1		__AARCH64_HWCAP64 (36)
#define HWCAP2_SME2		__AARCH64_HWCAP64 (37)
#define HWCAP2_SME2P1		__AARCH64_HWCAP64 (38)
#define HWCAP2_SME_I16I32	__AARCH64_HWCAP64 (39)
#define HWCAP2_SME_BI32I32	__AARCH64_HWCAP64 (40)
#define HWCAP2_SME_B16B16	__AARCH64_HWCAP64 (41)
#define HWCAP2_SME_F16F16	__AARCH64_HWCAP64 (42)
#define HWCAP2_MOPS		__AARCH64_HWCAP64 (43)
#define HWCAP2_HBC		__AARCH64_HWCAP64 (44)
#define HWCAP2_SVE_B16B16	__AARCH64_HWCAP64 (45)
#define HWCAP2_LRCPC3		__AARCH64_HWCAP64 (46)
#define HWCAP2_LSE128		__AARCH64_HWCAP64 (47)
#define HWCAP2_FPMR		__AARCH64_HWCAP64 (48)
#define HWCAP2_LUT		__AARCH64_HWCAP64 (49)
#define HWCAP2_FAMINMAX		__AARCH64_HWCAP64 (50)
#define HWCAP2_F8CVT		__AARCH64_HWCAP64 (51)
#define HWCAP2_F8FMA		__AARCH64_HWCAP64 (52)
#define HWCAP2_F8DP4		__AARCH64_HWCAP64 (53)
#define HWCAP2_F8DP2		__AARCH64_HWCAP64 (54)
#define HWCAP2_F8E4M3		__AARCH64_HWCAP64 (55)
#define HWCAP2_F8E5M2		__AARCH64_HWCAP64 (56)
#define HWCAP2_SME_LUTV2	__AARCH64_HWCAP64 (57)
#define HWCAP2_SME_F8F16	__AARCH64_HWCAP64 (58)
#define HWCAP2_SME_F8F32	__AARCH64_HWCAP64 (59)
#define HWCAP2_SME_SF8FMA	__AARCH64_HWCAP64 (60)
#define HWCAP2_SME_SF8DP4	__AARCH64_HWCAP64 (61)
#define HWCAP2_SME_SF8DP2	__AARCH64_HWCAP64 (62)
#define HWCAP2_POE		__AARCH64_HWCAP64 (63)

#endif /* _UAPI__ASM_HWCAP_H */
