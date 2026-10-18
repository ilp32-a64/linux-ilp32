// SPDX-License-Identifier: GPL-2.0
/*
 * ARM64 ILP32 userspace implementations of gettimeofday() and similar.
 *
 * ILP32 user space has a 32-bit time_t (like AArch32): clock_gettime() and
 * clock_getres() take a struct old_timespec32, as the time32 system calls of
 * the ILP32 table do. clock_gettime64() is there for 64-bit time_t users.
 * Based on arch/arm64/kernel/vdso32/vgettimeofday.c.
 */
/*
 * No includes: lib/vdso/gettimeofday.c is included by the Makefile (-include), as for
 * the LP64 vDSO; kernel headers do not build with -mabi=ilp32.
 */

int __kernel_clock_gettime(clockid_t clock, struct old_timespec32 *ts)
{
	return __cvdso_clock_gettime32(clock, ts);
}

int __kernel_clock_gettime64(clockid_t clock, struct __kernel_timespec *ts)
{
	return __cvdso_clock_gettime(clock, ts);
}

int __kernel_gettimeofday(struct __kernel_old_timeval *tv, struct timezone *tz)
{
	return __cvdso_gettimeofday(tv, tz);
}

int __kernel_clock_getres(clockid_t clock_id, struct old_timespec32 *res)
{
	return __cvdso_clock_getres_time32(clock_id, res);
}
