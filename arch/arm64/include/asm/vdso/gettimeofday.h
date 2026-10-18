/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2018 ARM Limited
 */
#ifndef __ASM_VDSO_GETTIMEOFDAY_H
#define __ASM_VDSO_GETTIMEOFDAY_H

#ifndef __ASSEMBLY__

#include <asm/barrier.h>
#include <asm/unistd.h>

#define VDSO_HAS_CLOCK_GETRES		1

#if defined(__aarch64__) && defined(__ILP32__)
/*
 * ILP32 vDSO: ILP32 tasks use the asm-generic system call table with a 32-bit
 * time_t, so __NR_clock_gettime/__NR_clock_getres are the time32 calls; the
 * 64-bit time versions are clock_gettime64 (403) and clock_getres_time64 (406).
 */
#define VDSO_NR_CLOCK_GETTIME		403
#define VDSO_NR_CLOCK_GETRES		406
#else
#define VDSO_NR_CLOCK_GETTIME		__NR_clock_gettime
#define VDSO_NR_CLOCK_GETRES		__NR_clock_getres
#endif

static __always_inline
int gettimeofday_fallback(struct __kernel_old_timeval *_tv,
			  struct timezone *_tz)
{
	register struct timezone *tz asm("x1") = _tz;
	register struct __kernel_old_timeval *tv asm("x0") = _tv;
	register long ret asm ("x0");
	register long nr asm("x8") = __NR_gettimeofday;

	asm volatile(
	"       svc #0\n"
	: "=r" (ret)
	: "r" (tv), "r" (tz), "r" (nr)
	: "memory");

	return ret;
}

static __always_inline
long clock_gettime_fallback(clockid_t _clkid, struct __kernel_timespec *_ts)
{
	register struct __kernel_timespec *ts asm("x1") = _ts;
	register clockid_t clkid asm("x0") = _clkid;
	register long ret asm ("x0");
	register long nr asm("x8") = VDSO_NR_CLOCK_GETTIME;

	asm volatile(
	"       svc #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	return ret;
}

static __always_inline
int clock_getres_fallback(clockid_t _clkid, struct __kernel_timespec *_ts)
{
	register struct __kernel_timespec *ts asm("x1") = _ts;
	register clockid_t clkid asm("x0") = _clkid;
	register long ret asm ("x0");
	register long nr asm("x8") = VDSO_NR_CLOCK_GETRES;

	asm volatile(
	"       svc #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	return ret;
}

#if defined(__aarch64__) && defined(__ILP32__)
/* time32 fallbacks for the ILP32 vDSO (lib/vdso BUILD_VDSO32) */
static __always_inline
int clock_gettime32_fallback(clockid_t _clkid, struct old_timespec32 *_ts)
{
	register struct old_timespec32 *ts asm("x1") = _ts;
	register clockid_t clkid asm("x0") = _clkid;
	register long ret asm ("x0");
	register long nr asm("x8") = __NR_clock_gettime;

	asm volatile(
	"       svc #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	return ret;
}

static __always_inline
int clock_getres32_fallback(clockid_t _clkid, struct old_timespec32 *_ts)
{
	register struct old_timespec32 *ts asm("x1") = _ts;
	register clockid_t clkid asm("x0") = _clkid;
	register long ret asm ("x0");
	register long nr asm("x8") = __NR_clock_getres;

	asm volatile(
	"       svc #0\n"
	: "=r" (ret)
	: "r" (clkid), "r" (ts), "r" (nr)
	: "memory");

	return ret;
}
#endif

static __always_inline u64 __arch_get_hw_counter(s32 clock_mode,
						 const struct vdso_data *vd)
{
	u64 res;

	/*
	 * Core checks for mode already, so this raced against a concurrent
	 * update. Return something. Core will do another round and then
	 * see the mode change and fallback to the syscall.
	 */
	if (clock_mode == VDSO_CLOCKMODE_NONE)
		return 0;

	/*
	 * This isb() is required to prevent that the counter value
	 * is speculated.
	 */
	isb();
	asm volatile("mrs %0, cntvct_el0" : "=r" (res) :: "memory");
	/*
	 * This isb() is required to prevent that the seq lock is
	 * speculated.#
	 */
	isb();

	return res;
}

static __always_inline
const struct vdso_data *__arch_get_vdso_data(void)
{
	return _vdso_data;
}

#ifdef CONFIG_TIME_NS
static __always_inline
const struct vdso_data *__arch_get_timens_vdso_data(void)
{
	return _timens_data;
}
#endif

#endif /* !__ASSEMBLY__ */

#endif /* __ASM_VDSO_GETTIMEOFDAY_H */
