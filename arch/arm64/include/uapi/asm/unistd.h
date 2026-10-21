/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifdef __ILP32__
#include <asm/unistd_ilp32.h>

/*
 * ILP32 has the AArch32 argument order of sync_file_range(): fd, flags, offset, nbytes
 * (sync_file_range2), as arm, csky and hexagon do.
 */
#undef __NR_sync_file_range
#define __NR_sync_file_range2 84

/*
 * The syscall table keeps the time32 and stat64 calls for binaries built with a 32-bit
 * time_t (glibc 2.30). User space with a 64-bit time_t must use the *_time64 calls and
 * statx instead, so the plain names are not exposed, as on riscv32: passing a 64-bit
 * struct timespec to them would go wrong silently. Define __ILP32_WANT_TIME32_SYSCALLS
 * to get them, e.g. to build a C library with a 32-bit time_t. The kernel (the ILP32
 * vDSO fallbacks) uses them.
 */
#ifndef __KERNEL__
#ifndef __ILP32_WANT_TIME32_SYSCALLS
#undef __NR_io_getevents
#undef __NR_pselect6
#undef __NR_ppoll
#undef __NR_fstatat64
#undef __NR_fstat64
#undef __NR_timerfd_settime
#undef __NR_timerfd_gettime
#undef __NR_utimensat
#undef __NR_futex
#undef __NR_nanosleep
#undef __NR_timer_gettime
#undef __NR_timer_settime
#undef __NR_clock_settime
#undef __NR_clock_gettime
#undef __NR_clock_getres
#undef __NR_clock_nanosleep
#undef __NR_sched_rr_get_interval
#undef __NR_rt_sigtimedwait
#undef __NR_gettimeofday
#undef __NR_settimeofday
#undef __NR_adjtimex
#undef __NR_mq_timedsend
#undef __NR_mq_timedreceive
#undef __NR_semtimedop
#undef __NR_recvmmsg
#undef __NR_wait4
#undef __NR_clock_adjtime
#undef __NR_io_pgetevents
#endif
#endif
#else
#include <asm/unistd_64.h>
#endif
