# AArch64 ILP32 for Linux

Kernel branches with the AArch64 ILP32 ABI (32-bit `long` and pointers, 64-bit kernel). ILP32 was never
merged into mainline Linux; the maintained out-of-tree series is in the openEuler kernel (branches
`OLK-5.10` and `OLK-6.6`, where `ARM64_ILP32` is compiled but disabled in the default configuration).
These branches carry that series on vanilla kernel.org releases, plus fixes found by running a real ILP32
user space.

This default branch only holds this file. The kernel is in the branches below.

## Branches

| Branch | Base | Content |
|---|---|---|
| `ilp32-6.12` | `v6.12` | `ilp32-6.6` ported to 6.12 (no openEuler series exists for 6.12) |
| `ilp32-6.6` | `v6.6` | `ilp32-6.6-olk` + fixes (see below) |
| `ilp32-6.6-olk` | `v6.6` | the openEuler OLK-6.6 ILP32 series (31 commits), unchanged |
| `ilp32-5.10` | `v5.10` | `ilp32-5.10-olk` + later OLK-5.10 ILP32 fixes + fixes (see below) |
| `ilp32-5.10-olk` | `v5.10` | the openEuler OLK-5.10 ILP32 series (23 commits), unchanged |

Commits taken from openEuler keep their author, date and message and end with
`(cherry picked from openEuler OLK-<version> commit <id>)`. Commits changed for another kernel version end
with a note such as `[6.12: what was changed and why]` and the Signed-off-by of whoever changed them.

## Fixes on top of the openEuler series

| Fix | 6.12 | 6.6 | 5.10 |
|---|---|---|---|
| ILP32 vDSO linked as a shared object (it had no dynamic symbols, the C library could not use it) | yes | yes | yes |
| relink the ILP32 vDSO when the link command changes | yes | yes | yes |
| ILP32 vDSO data page offset (SIGBUS on every vDSO call) | yes | yes | yes |
| ILP32 vDSO with 32-bit `time_t` `clock_gettime`/`clock_getres` (it wrote a 64-bit timespec into a 32-bit one), `__kernel_clock_gettime64` | yes | yes | yes |
| linker flags of the ILP32 vDSO (`DT_HASH`, `-Bsymbolic`, build ID) | yes | yes | yes |
| relocation check of the ILP32 vDSO | yes | yes | yes (5.10 version) |
| `FORCE` for the ILP32 vDSO object rules | yes | yes | yes |
| ILP32 without AArch32 (`ARM64_ILP32=y`, `AARCH32_EL0=n`): seccomp (from OLK-5.10), AArch32-only errata, no generic compat ELF loader on arm64 (it was registered twice with AArch32) | yes | yes | errata only (the rest does not apply) |
| time64 system calls for `__SYSCALL_COMPAT` | generated table | in v6.6 | yes |
| later OLK-5.10 ILP32 fixes (erratum 1418040, addr_limit, audit, seccomp, ABI, UBSAN) | in the OLK-6.6 series | in the OLK-6.6 series | yes |

## 6.12 port

Main changes against `ilp32-6.6` (details in the `[6.12: ...]` notes of the commits):

- System call table: arm64 generates its tables from `syscall.tbl` since 6.11. The ILP32 table is generated
  from `scripts/syscall.tbl` (`arch/arm64/tools/syscall_ilp32.tbl`, ABIs `common 32 time32 stat64
  memfd_secret`, compat entry points), with the user space numbers in `asm/unistd_ilp32.h`; same entries
  as the 6.6 table except `lookup_dcookie` (removed in 6.10) and the system calls added since 6.6.
  `sync_file_range` keeps the AArch32 argument order (`__NR_sync_file_range2`).
- Signal frames: the shared LP64/ILP32 signal code (`asm/signal_common.h`) is redone on the 6.12 code,
  with the FPMR and POE contexts and the POR_EL0 handling.
- Many `#ifdef CONFIG_COMPAT` blocks became runtime `is_compat_task()` checks in 6.12 (1984c805461f); the
  AArch32-only ones use `is_a32_compat_task()`.
- seccomp strict mode allows AArch32 tasks `rt_sigreturn` like upstream (the series had `sigreturn`).

## Configuration

arm64 `defconfig` plus:

```
CONFIG_COMPAT=y
CONFIG_ARM64_ILP32=y
CONFIG_AARCH32_EL0=y          # optional: AArch32 tasks
# CONFIG_ARM64_PTR_AUTH is not set
CONFIG_COMPAT_32BIT_TIME=y    # ILP32 glibc 2.30 has a 32-bit time_t
```

## Testing

[ilp32-a64/ilp32-test](https://github.com/ilp32-a64/ilp32-test) builds an ILP32 toolchain (GCC 10.5,
glibc 2.30 from [ilp32-a64/glibc](https://github.com/ilp32-a64/glibc)) and runs ILP32 and AArch32 test
programs on these kernels in QEMU, with AArch32 on and off. `ilp32-6.12`, `ilp32-6.6` and `ilp32-5.10`
pass.

## Status

- Not tested on hardware by this project yet.
- Bases are `v6.12`, `v6.6` and `v5.10`, without stable updates.
- GCC 15 deprecates `-mabi=ilp32`; the toolchain here uses GCC 10.5.
