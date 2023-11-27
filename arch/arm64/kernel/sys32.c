// SPDX-License-Identifier: GPL-2.0-only
/*
 * arch/arm64/kernel/sys32.c
 *
 * Copyright (C) 2015 ARM Ltd.
 */

#include <linux/compat.h>
#include <linux/compiler.h>
#include <linux/syscalls.h>

#include <asm/syscall.h>
#include <asm/unistd_compat_32.h>

asmlinkage long compat_sys_sigreturn(void);
asmlinkage long compat_sys_rt_sigreturn(void);

#define __SYSCALL_WITH_COMPAT(nr, sym, compat) __SYSCALL(nr, compat)

#undef __SYSCALL
#define __SYSCALL(nr, sym)	asmlinkage long __arm64_##sym(const struct pt_regs *);
#include <asm/syscall_table_32.h>

#undef __SYSCALL
#define __SYSCALL(nr, sym)	[nr] = __arm64_##sym,

const syscall_fn_t a32_sys_call_table[__NR_compat32_syscalls] = {
	[0 ... __NR_compat32_syscalls - 1] = __arm64_sys_ni_syscall,
#include <asm/syscall_table_32.h>
};
