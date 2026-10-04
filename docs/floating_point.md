# Floating point in SporeApp.exe

Findings from static analysis of the retail exe (2026-10-04). These matter for porting physics (Havok 3.1.0,
which is ~71k x87 instructions) and any other x87 code.

## FPU precision at runtime

1. **CRT startup sets 53-bit (double) precision:** `0x11e151a` calls `_controlfp_s(NULL, _PC_53, _MCW_PC)`
   (MSVC's standard `_setdefaultprecision`).
2. **Direct3D 9 then switches the device thread to 24-bit (single) precision.** RenderWare creates the
   device at `0x11f874e` (IDirect3D9::CreateDevice, in FUN_011f8680) with BehaviorFlags built from
   SOFTWARE_VP 0x20, HARDWARE_VP 0x40, HARDWARE_VP+PUREDEVICE 0x50 or MIXED_VP 0x80, plus
   MULTITHREADED 0x04. **D3DCREATE_FPU_PRESERVE (0x02) is never set**, so D3D9 puts the x87 of the thread
   that called CreateDevice into single precision (24-bit mantissa), round-to-nearest, exceptions masked,
   and keeps it there.
3. **Local exceptions:** the audio system (FUN_00a31800) saves the control word, forces `_PC_53` around one
   call and restores it. A scoped guard whose dtor is FUN_00a206c0 restores precision when leaving some
   function.
4. **Rounding-mode changes are local:** all 396 inline `fldcw` sites set truncation (`or 0xC00`) for a
   float-to-int conversion and then restore. None of them change precision.

**So code running on the render/main thread after device creation computes at x87 single precision.**
Threads created later start with the default control word (53-bit) unless they set it. To confirm at
runtime: which thread calls CreateDevice and which runs the simulation/Havok step (expected: the same main
thread).

## What this means for a port (SSE/NEON, 32- and 64-bit)

With the x87 in 24-bit mode, every arithmetic result is rounded to a 24-bit mantissa, as SSE `float` math
is. The exponent range stays extended, though. Consequences:
- **float code ports almost exactly** to SSE float. The exceptions are values that would overflow,
  underflow or go denormal in float but not in the x87's extended exponent range, and the last-bit result
  of `fsin`/`fcos` (x87 transcendental accuracy differs from libm).
- **`double` arithmetic in this code runs at float precision.** `fld qword` loads a double, but each
  operation's result is rounded to 24 bits. A faithful port of such an expression is NOT plain C++
  `double` math. Round to float after each operation (or compute in float) when bit-exact behavior
  matters. Loads, stores and conversions keep their own widths.
- **`fsqrt` in 24-bit mode** gives the correctly rounded float square root, so `sqrtf` matches.
- Never build this code with fast-math or FMA contraction: `/fp:precise`, `-ffp-contract=off`,
  `-fno-fast-math`.

## Verification plan

Differential tests (tools/difftest, Unicorn): run the original function with the x87 control word set to
0x007F (24-bit, round-to-nearest, all exceptions masked) to reproduce the device thread's state. Compare
bit-for-bit against our build of the same function on random and edge-case inputs (NaN, ±0, denormals,
huge values). Spots marked `// X87-PRECISION:` by the decompiling agents are where differences are
expected first.

## Ghidra decompiler patch (float grouping)

Stock Ghidra prints float `+` and `*` with the integer operator tokens, which are marked associative. So a
sum computed as `a + (b + c)` was printed as `a + b + c`, which C reads as `(a + b) + c`. That's a different
float computation. Example: hkTransform::setInverse (0x01080e70) computes `(z*m8 + y*m4) + x*m0`. Stock
Ghidra printed `x*m0 + y*m4 + z*m8`; patched Ghidra prints `x*m0 + (y*m4 + z*m8)` (same grouping; operand
order within one `+` may be swapped, which is exact in IEEE). Patch: tools/ghidra/patches/float-nonassociative.patch;
build+install: tools/ghidra/patch_decompiler.sh (re-run after any Ghidra upgrade). Decompiles exported before
2026-10-04 15:00 may show regrouped float sums, so take grouping from the disassembly for those.
