# AArch64 ILP32 for Linux

Kernel branches with the AArch64 ILP32 ABI (32-bit `long` and pointers, 64-bit kernel). ILP32 was never
merged into mainline Linux; the maintained out-of-tree series is in the openEuler kernel (branches
`OLK-5.10` and `OLK-6.6`, where `ARM64_ILP32` is compiled but disabled in the default configuration).
This repository carries that series on kernel.org releases, plus fixes found by running a real ILP32
user space.

This default branch only holds this file. The kernel is in the branches below.

## Branches

**`ilp32-6.12.y` is the only maintained branch.** It is on the 6.12 stable series (`v6.12.114`); all new
work goes there and all tests run on it.

| Branch | Base | Status |
|---|---|---|
| `ilp32-6.12.y` | `v6.12.114` | **maintained**: the ILP32 series on 6.12 stable, with the fixes below |
| `ilp32-6.12` | `v6.12` | deprecated: the first 6.12 port, without the stable updates and the later fixes |
| `ilp32-6.6.y` | `v6.6.160` | deprecated |
| `ilp32-6.6` | `v6.6` | deprecated |
| `ilp32-6.6-olk` | `v6.6` | deprecated: the openEuler OLK-6.6 ILP32 series (31 commits), unchanged |
| `ilp32-5.10` | `v5.10` | deprecated |
| `ilp32-5.10-olk` | `v5.10` | deprecated: the openEuler OLK-5.10 ILP32 series (23 commits), unchanged |

The deprecated branches stay for reference. They are no longer updated or tested, and they do not have
the fixes made after they were left (pointer authentication, BTI, SVE, the uapi changes; see below).

Commits taken from openEuler keep their author, date and message and end with
`(cherry picked from openEuler OLK-<version> commit <id>)`. Commits changed for another kernel version end
with a note such as `[6.12: what was changed and why]` or `[6.12.y: ...]` and the Signed-off-by of whoever
changed them.

## What `ilp32-6.12.y` has

The openEuler OLK-6.6 ILP32 series ported to 6.12 (there is no openEuler series for 6.12), plus:

- ILP32 vDSO: linked as a shared object (it had no dynamic symbols), relinked when the link command
  changes, data page offset (SIGBUS on every call), 32-bit `time_t` `clock_gettime`/`clock_getres` plus
  `__kernel_clock_gettime64`, the linker flags (`DT_HASH`, `-Bsymbolic`, build ID), the relocation check,
  `FORCE` for its object rules.
- ILP32 without AArch32 (`ARM64_ILP32=y`, `AARCH32_EL0=n`): seccomp, AArch32-only errata, no generic
  compat ELF loader on arm64 (it was registered twice with AArch32).
- The 6.12 port: the ILP32 system call table is generated from `scripts/syscall.tbl` (ABIs
  `common 32 time32 stat64 memfd_secret`, compat entry points, no symlink); the shared LP64/ILP32 signal
  code is redone on the 6.12 code (FPMR, POE); the AArch32-only `is_compat_task()` checks of 6.12 use
  `is_a32_compat_task()`; seccomp strict mode allows AArch32 tasks `rt_sigreturn` like upstream.
- The stable updates of 6.12.y (`[6.12.y: ...]` notes): signal code, `update_syscall_orig_x0_after_ptrace()`,
  debug exceptions, the LP64 vDSO changes.
- uapi: the time32 and stat64 system call numbers (`__NR_futex`, `__NR_clock_gettime`, `__NR_fstat64`, ...)
  are not exposed to ILP32 user space, as on riscv32; the system call table keeps them for binaries built
  with a 32-bit `time_t`. Define `__ILP32_WANT_TIME32_SYSCALLS` to get the names. `<asm/hwcap.h>`: the
  HWCAP2 bits 32 and up use `__AARCH64_HWCAP64(n)` (`1ULL` for ILP32).
- Pointer authentication: `ARM64_ILP32` no longer depends on `!ARM64_PTR_AUTH` (the ILP32 vDSO is built
  without return address signing, which GCC does not support for ILP32); the PAC prctls and ptrace regsets
  work for ILP32 tasks.
- BTI: GNU property notes of ELF32 files are parsed with the ELF32 alignment (ILP32 programs with a BTI
  note were refused with ENOEXEC before), so BTI is enforced for ILP32 as for LP64.
- SVE: ILP32 tasks can use SVE (the first SVE instruction raised SIGILL before, while `HWCAP_SVE` was
  set, so every glibc 2.41 program died on a CPU with SVE). `ARM64_SME` depends on `BROKEN` in 6.12.y;
  the SME parts are done the same way but not built.

## Configuration

arm64 `defconfig` plus:

```
CONFIG_COMPAT=y
CONFIG_ARM64_ILP32=y
CONFIG_AARCH32_EL0=y          # optional: AArch32 tasks
CONFIG_COMPAT_32BIT_TIME=y    # optional: the time32 system calls, for binaries with a 32-bit time_t
```

Pointer authentication (`ARM64_PTR_AUTH`, `ARM64_PTR_AUTH_KERNEL`) and BTI can stay on.

## Testing

[ilp32-a64/test-ilp32](https://github.com/ilp32-a64/test-ilp32) runs ILP32 and AArch32 test programs in
QEMU, with AArch32 on and off, using the ILP32 toolchain with GCC 14.3 and glibc 2.41 (64-bit `time_t`,
[ilp32-a64/glibc-ilp32](https://github.com/ilp32-a64/glibc-ilp32) branch `ilp32-2.41`); musl 1.2.5 is
tested there too. Pointer authentication, BTI and SVE were checked on QEMU `-cpu max`.

## Status

- ILP32 user space (glibc 2.41, CPython 3.14) runs on a Cortex-A35 board with an `ilp32-6.12.y` kernel
  (based on 6.12.111). Pointer authentication, BTI and SVE are tested in QEMU only (`-cpu max`).
- GCC 15 deprecates `-mabi=ilp32`; the toolchain uses GCC 14.3. GCC has no return address signing for
  ILP32; clang can build ILP32 code with `-mbranch-protection=pac-ret`.
- Programs built with clang `pac-ret` need the libgcc ILP32 unwinder fix (test-ilp32
  `glibc/toolchain/patches/`, OpenWrt patch 990) for C++ exceptions and backtraces.
