/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifdef __ILP32__
#include <asm/unistd_ilp32.h>

/*
 * ILP32 has the AArch32 argument order of sync_file_range(): fd, flags, offset, nbytes
 * (sync_file_range2), as arm, csky and hexagon do.
 */
#undef __NR_sync_file_range
#define __NR_sync_file_range2 84
#else
#include <asm/unistd_64.h>
#endif
