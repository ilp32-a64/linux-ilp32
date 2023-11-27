/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * arch/arm64/include/asm/seccomp.h
 *
 * Copyright (C) 2014 Linaro Limited
 * Author: AKASHI Takahiro <takahiro.akashi@linaro.org>
 */
#ifndef _ASM_SECCOMP_H
#define _ASM_SECCOMP_H

#include <asm/unistd.h>
#include <asm/unistd_compat_32.h>

#ifdef CONFIG_AARCH32_EL0
#define __NR_seccomp_read_32		__NR_compat32_read
#define __NR_seccomp_write_32		__NR_compat32_write
#define __NR_seccomp_exit_32		__NR_compat32_exit
#define __NR_seccomp_sigreturn_32	__NR_compat32_rt_sigreturn
#endif /* CONFIG_AARCH32_EL0 */

#ifdef CONFIG_COMPAT
#ifndef __COMPAT_SYSCALL_NR

static inline const int *get_compat_mode1_syscalls(void)
{
#ifdef CONFIG_AARCH32_EL0
	static const int mode1_syscalls_a32[] = {
		__NR_seccomp_read_32, __NR_seccomp_write_32,
		__NR_seccomp_exit_32, __NR_seccomp_sigreturn_32,
		0, /* null terminated */
	};
#endif
	static const int mode1_syscalls_ilp32[] = {
		__NR_read, __NR_write,
		__NR_exit, __NR_rt_sigreturn,
		0, /* null terminated */
	};

#ifdef CONFIG_AARCH32_EL0
	if (is_a32_compat_task())
		return mode1_syscalls_a32;
#endif
	return mode1_syscalls_ilp32;
}

#define get_compat_mode1_syscalls get_compat_mode1_syscalls

#endif
#endif

#include <asm-generic/seccomp.h>

#define SECCOMP_ARCH_NATIVE		AUDIT_ARCH_AARCH64
#define SECCOMP_ARCH_NATIVE_NR		NR_syscalls
#define SECCOMP_ARCH_NATIVE_NAME	"aarch64"
#ifdef CONFIG_COMPAT
#include <asm/unistd_compat_32.h>
# define SECCOMP_ARCH_COMPAT		AUDIT_ARCH_ARM
# define SECCOMP_ARCH_COMPAT_NR		__NR_compat32_syscalls
# define SECCOMP_ARCH_COMPAT_NAME	"arm"
#endif

#endif /* _ASM_SECCOMP_H */
