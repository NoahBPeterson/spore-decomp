# Code generation in `SporeApp.exe`

How the Microsoft backends turn ordinary source into the shapes seen in
`SporeApp.exe`, and which source choices move those shapes. This is the
Spore analogue of banteg's *MSVC 6 code generation* guide for Crimsonland
(`crimson.banteg.xyz/re/static/msvc-codegen/`): same idea — mechanism → source
choice → native shape → where it was demonstrated — but for **three toolchains
at once**, because this binary was not built by one compiler.

Use this the way you use that guide: read it before you start iterating, and open it the first time a diff appears — find the section for the kind of difference you see (loop shape, register choice, frame offsets, x87 order, block layout, ABI), check the entries **for the toolchain that built that address**, then retest against native evidence. A rule here
explains a mechanism; it does not promise the same spelling works at another
site. This document summarises and organises evidence that lives in
[`matching.md`](matching.md), [`floating_point.md`](floating_point.md),
[`equivalence.md`](equivalence.md), [`Papercuts.md`](Papercuts.md) and
[`xmatch.md`](xmatch.md); those are the primary sources with the full notes.

---

## 1. Which compiler produced this function?

This is the single most important thing to establish before chasing a near-miss,
because **a few bytes off is often the compiler, not the source** (see
`matching.md` "Toolchain provenance"). `SporeApp.exe` links prebuilt
middleware, each built by its own compiler:

| Code | Compiler | How we compile it | Marker |
|---|---|---|---|
| Spore game code + EA framework (UTFSpore) | **VS2008 SP1, cl 15.00.30729.01** (RTM 15.00.21022.08 still open) | default `tools/matching/cl.sh` | **[15]** |
| Havok 3.1.0 (all 469 objects) | **VC .NET 2003, cl 13.10.3077** | `/vc71` → `cl71.sh` (surrogate 13.10.3052) | **[13]** |
| RenderWare 4 core libraries | **VC .NET 2003, cl 13.10** | `/vc71` | **[13]** |
| RenderWare 4 core **additionally** | **`/GL` + `/LTCG`** (link-time codegen) | not reproducible single-object | **[LTCG]** |
| Other code inside the RenderWare address range (NegateRows, LpcSynthesize, RW audio) | VS2008 SP1 | default | **[15]** |
| DirectX 8.1 `d3dx8.lib` members, IJG 6a / zlib 1.1.3 / libpng 1.0.5 | product 29 build 9178 (XP DDK); pinned upstream | `msvc7.0ddk`-style / upstream source | **[DDK]** |

The distinction matters because cl 15 and cl 13.10 make the **same** decisions
for integer code but **different** ones for x87 floating point, and `/LTCG`
defers codegen to the linker so a single-object compile cannot match callers at
all. The pseudo-flag `/vc71` selects `cl71.sh`; it lives in the flag list so
manifests, `chk.py` and `difftest` pick it per line. `tools/matching/chk.py
--flags` and a manifest row's flags both accept it.

**Two x87 smell tests** (from `matching.md` and Papercuts):
- `fld st(i); fmul [m]` (a just-computed value reused) is **cl 13.10** output;
  cl 15 emits `fld [m]; fmul st(i)`. Havok x87 code never matches under cl 15.
- `sqrt` compiling to a `_CIsqrt` **call** means you are on cl 13.10 without
  `/fp:fast`; the original may inline `fsqrt`. If a Havok function FAILs on a
  first import, you forgot `/vc71` (or `/fp:fast`).

**One `/LTCG` smell test** (from Papercuts, `Raster::Initialize` 0x011efeb0):
the function sets `edx = 0`, calls `FormatGetDepth`, and keeps using `edx == 0`
afterwards. That is only legal if the compiler knew the callee leaves `edx`
alone — which only the linker knows under `/LTCG`. More generally, the original
reads `ecx`/`eax`/`edx` at entry with no C signature that explains them
(`docs/tickets.md`, "custom/LTCG register ABI"). See §11.4.

**Policy for [LTCG]:** equivalence-only until the whole binary has compilable
source. Do not chase byte-exactness for callers (`symbols/renderware4_core.txt`
lists the ranges: `0112c500–01176a90`, `011e2000–0120bc50`). Leaf functions that
make no calls have nothing to cross-optimise and can still match under `/vc71`.

---

## 2. What is the same as MSVC 6, and what is different

banteg's guide is for MSVC 6.5 (C2). cl 13.10 (VC7.1) and cl 15.00 (VC9) are
the **same backend lineage** — the code generator is still `c2.dll`, and most
whole-function mechanisms carry over almost unchanged. The differences that bite
are concentrated in floating point, deferred codegen (`/GL`), and the newer
front end's EH/security scaffolding.

| Mechanism (banteg §) | MSVC 6.5 | cl 13.10 (VS2003) | cl 15.00 (VS2008) |
|---|---|---|---|
| Indexed loop → pointer IV | yes | yes | yes (same) |
| Countdown `dec/jne` for unused index | yes | yes | yes |
| Loop inversion / peeling | yes | yes | yes |
| IV anchor chosen by merge order / use counts | yes | yes | yes |
| Whole-function register allocation keyed by ids | yes | yes | yes |
| Identical tails cross-jumped | yes | yes | yes |
| Then-arm fallthrough, late range mover | yes | yes | yes |
| May-alias classes, dead stores survive | yes | yes | yes |
| Args evaluated right-to-left | yes | yes | yes |
| Hidden sret for by-value struct returns | yes | yes | yes |
| Hidden EAX return despite a `void` declaration | yes | yes | yes (worse under `/LTCG`) |
| `ret N` carries the argument cleanup | yes | yes | yes |
| Callee must not clobber an untouched register | no | no | **`/LTCG` callers depend on it** |
| Tail call → `jmp` | yes | yes | yes |
| Static/register calling conventions in a TU | yes (custom) | yes | yes |
| Linker folds identical COMDAT bodies (ICF) | yes | yes | yes |
| x87 NaN test mask / `fcomp` orientation | `fnstsw` idiom | `test ah,5; jp` vs `test ah,1; je` per site | same as 13.10 but different picks |
| Floats via SSE | no | optional `/arch:SSE` | **yes** in `/arch:SSE[2]` modules |
| `/Od` local slot order | decl-order (untested) | decl-independent | **hash of names** (§6.4) |
| EH frames | `/GX` | `/EHsc` | `/EHsc` + `/GS` cookies |
| Deferred codegen | no | no | **`/GL`+`/LTCG`** for RW4 core |
| String literals writable `.data` | yes | yes | `.rdata`/pooled (§12) |

Everything else in banteg's guide — the induction-variable machinery, statement
ordering, value-class temporaries, alias classes, stack colouring, block layout,
instruction selection, inlining budget, calling conventions, data/link — applies
with the same *character* to all three of our backends. Where we have
Spore-specific evidence we give it below; where the only difference is version
we tag it **[13]** or **[15]**.

---

## 3. Loops and induction variables

C2's strength reduction, linear-test replacement, loop reversal and loop
inversion exist in all three backends. **Almost all of banteg's §Loops applies
verbatim to cl 13.10 and cl 15.00.** The Spore-specific additions:

### 3.1 The IV-anchor and countdown rules are unchanged

Writing a hand-rolled pointer walk where native has an indexed loop remains a
mistake: write the plain indexed `for`, let C2 create the IV. The signedness of
the latch (`jl`/`jle` vs `jb`) still follows the compared source value's
signedness, not index-vs-pointer (`matching.md` "Loop shape matters": `while
(n--) h = f(*s++)` matched, `for (; n; --n)` did not — register assignment and
`dec`/`sub` differ).

### 3.2 Unrolling is version-dependent **[13] vs [15]**

cl 13.10 unrolls a Havok loop only when the trip count is a **local copy** of
the member, not the member itself:

```cpp
const int nB = m_dimB;          // [13] unrolls 4x with this
for (int i = 0; i < nB; i++) ...  // not with m_dimB directly
```

(Papercut `cl2 s0110dd70…`, `setTransformedPos`.) This is a genuine difference
from MSVC 6, where trip-count exposure and late IV elimination follow the
"early constant trip count specializes later loops" rule in banteg §Loops.

**Straight-line repeats must be written out, not looped.** When the original
emits a repeated release/handle or pointer-vector-drain block fully unrolled and
you write it as a loop, cl lowers it to one shared loop and the body roughly
**halves**; expand it by hand (macros are fine). The unrolling is the source
shape, not an optimizer pass you can trigger (spcg1 `00e65ad0`
`cPartGfx::Clear`: ten handle blocks + three vector drains).

### 3.3 cl 13.10 merges same-valued induction variables sooner **[13]**

A 13³ table filler kept an outer counter and a running `(i+j)` sum as separate
IVs; cl 13.10 merge them and **no spelling of the loop-variable types
reproduced the original spills** (Papercut `cl2 s008beca0…`). When two IVs that
the source kept distinct collapse, that is the backend, not your source.

### 3.4 cl 15 rotates through scratch registers per temporaries **[15]**

cl 15.00 adds an explicit "whole-function allocation rotates scratch registers
through EAX/ECX/EDX and advances a shared preference cursor" behaviour
(`matching.md`, "Allocation is whole-function" from the pilot): inserting or
removing one temporary — even a wrapper helper or a named `bool` — shifts every
later register pick, and two identical arms get different registers (which also
blocks cross-jumping). Same character as MSVC 6's id-keyed ties, but cl 15 makes
it easy to see by adding one variant and watching distant bytes move.

---

## 4. Statement order, ownership and spelling

banteg's §Statement order is the part of the MSVC 6 guide that transfers most
directly, because it is about the **front end and scheduler**, which cl 13.10
and cl 15.00 share with VC6 in outline. The Spore-specific shape of each rule:

- **Repeat a pure expression instead of naming it.** cl 15 CSE picks the owner
  register; a named local imposes a lifetime that hoists, spills, or rotates
  registers. `matching.md` `/O2` levers: "A member loaded into a callee-saved
  register before a call: copy it to a local at that point in the source" and
  the `_ReadWriteBarrier()` trick (`<intrin.h>`) to pin a vptr/field store
  before a load that cl hoists above it — a diagnostic, not a match trick.
- **Re-read fields and globals at each use.** Without `/GL`, cl treats a call as
  able to clobber everything, so native reloads after calls are source re-reads.
  With `/GL` (RW4 core) it does the opposite and can keep a value in a register
  across a call — see §11.4.
- **Test-then-reload** (`cmp [r],0; je; mov ecx,[r]`) means the member chain is
  written twice without a local; a **kept `lea`** means a `T& ref = v[i];` local.
  Calling a trivial inline accessor instead of the raw member fixes stubborn
  register swaps (Papercut `bfs4 s00902460…`).
- **First assignment matters, declaration order usually does not.** cl 15 at
  `/Od` is the exception: there, slot order is a name hash (§6.4). At `/O2`,
  permuting declarations is normally byte-identical.
- **Write a local's initializer where it is first used, not at the top of the
  scope.** A `void* h = 0;` declared early and passed as `&h` to a later call can
  force a `push ebp` frame and shift the prologue; moving the declaration down to
  the call site matched (spcg1 `00e72ac0`, 31→0 bytes).
- **Chained assignment stores the rightmost target first**, and for floats keeps
  the value on the x87 stack (`fld st(0); fstp`). `a = b = v` is not the same as
  two statements; float chains are order-sensitive. (Same across all three.)
- **Aggregate identity changes alias ordering.** Modelling a separately declared
  global as one struct makes cl treat sub-object accesses differently. cl 15's
  alias-class budget is **0x400**; a big function can exceed it and collapse
  classes (Papercut `s011fab10…` and `matching.md` "The 0x400 alias-class
  budget"). Not a thing in the MSVC 6 guide, or at least not documented there.
- **`/Od` is its own world [15]/[13].** Some Spore modules are `/Od /Ob1`:
  `push ebp; mov ebp,esp`, ecx spilled, every local in memory, but small EASTL
  helpers still inlined. In those modules source *names* reorder slots (§6.4),
  and a `new (p) T(v)` needs the right `/EHsc` state.

---

## 5. C++ value classes and aggregates

The 2003/2008 SDK value types (`vec2_t`, `vec3`, colour classes, `Vector3`) and
EASTL containers drive most frame sizes and copy shapes, exactly as banteg's
`vec2_t` section describes for VC6. Differences worth calling out:

### 5.1 Copy flavour decides the instructions

The rule is toolchain-independent but worth restating with Spore evidence
(Papercut `s00623f90…`):

| Source | Code |
|---|---|
| class with a user copy ctor, passed by value | `fld`/`fstp` per float |
| `T x(y)` (copy-init) | `movss` |
| POD struct copy | integer regs |
| POD returned from an inline helper then assigned | stack temps (`movss [esp]; mov r,[esp]`) |

A user `operator=` gives `fld`/`fstp`; a user copy ctor gives `movss`. So the
presence of `fld`/`fstp` in a copy tells you the *original class had a user
copy ctor*, and `movss` tells you copy-init or a vector-friendly type. This is
the same mechanism as banteg's "Keep implicit copy constructors and assignment",
extended with the SSE (`movss`) case that VC6 does not have.

### 5.2 A user copy ctor is required to build a by-value arg in place **[13]/[15]**

`f(String(p), Info())` builds a by-value class argument in place (no temp +
`rep movs` copy, no caller dtor) **only if the class has a user-declared copy
ctor**. With the implicit copy ctor, cl builds a temp and copies (Papercuts
`s00948de0…`, `s009aa590…`). The MI/secondary-base analogues:

- A refcount release through a **secondary base at +0x10** needs the stub to
  derive from a *polymorphic* primary base (a dummy `virtual` + `char pad[0xc]`)
  plus a polymorphic refcount base. A non-polymorphic `char pad[0x10]` makes cl
  hoist the only vptr-bearing base to offset 0 (Papercuts `s0064eb60…`,
  `w1g4 s51-62`).
- An embedded polymorphic subobject at +4 is a **member with its own vptr**, not
  a pointer (Papercut `s00a20060…`).

### 5.3 Whole-float aggregates copy with integer moves **[15]**

`Vector3`/`vec2_t` whole copies select integer `mov`s (or `rep movsd`), never
`fld`/`fstp`; component float assignments select x87/SSE. A `union` with an
`__m128` member is what makes `Vec4` copy as `movaps` (Papercut
`s011fab10…`). `Vector3` needs a user copy ctor **and** `operator=` to get
`movss` copies instead of int-register copies (Papercut `s011666d0…`).

### 5.4 Initialized POD locals are constant-folded away

A plain initialized two-float local read only for stores is constant-propagated
and its slot disappears. Native frames that materialise zeros need an object the
compiler cannot fold — a constructor-expression temporary, or a union overlay
(`matching.md` "Initialized POD locals…"). Same as banteg.

---

## 6. Register allocation and C2 internals

The whole-function, id-keyed allocator is the same family across VC6/VC7.1/VC9.
The Spore-specific facts:

### 6.1 Whole-function rotation and split markers **[15]**

At `/O2`, one added temporary shifts every later pick; a residual far from the
edit is normal. A spill often comes from interference with a coexisting
temporary (a "pressure split marker") or an extended live range, not from the
long-lived value's own priority (`matching.md` "Long-lived values and named
booleans"). `bool`-vs-`int` for a call result decides whether you get AL-tested
directly or a materialised 0/1.

### 6.2 Commutative/SIB order keyed by ids

C2 sorts commutative operands, SIB components and scheduler ties by internal
symbol/IL ids (in VC6: memory operands by id mod 8, ties by id mod 2048, globals
in 32-id chunks). Any source change that adds/removes named locals, references,
inline formals, operator records or earlier global references can flip operand
order in distant code. **Directly commuting one op's operands in source is
normally neutral.** This carries to cl 15 unchanged (`matching.md`).

### 6.3 Register-argument conventions for TU-local statics **[13]/[15]**

**Without `/GL`, static functions get register calling conventions.** Params
1/2/3 land in `eax`/`edx`/`ecx`; an arg arriving in `eax`/`edi` means a static
helper in the same TU. To reproduce it, keep the helper `static` and give it a
**same-TU stand-in caller** (Papercuts `s008beca0…`, `s008ce020…`, `bfs4
s00902460…`). A function with `ecx=this` and `ret 4` that uses no members is
still a thiscall member (Papercut `s00945ed0…`). This is the same *character* as
banteg's "Static callees in provider objects use custom conventions", but it
applies to ordinary game code here too — and on **[LTCG]** it becomes worse
(§11.4).

### 6.4 `/Od` slot order is a hash of names **[15]**

This has **no counterpart in banteg's MSVC 6 /O2 guide** and is the top
time-sink in `/Od` slices. In a `/Od` scope, named locals are laid out by a
**hash of their names**, not by declaration order; within a bucket,
later-declared names come first. Use `tools/matching/od_names.py fit K` for a
scope with K locals, then assign your roles one line at a time. The order
depends on K, so measure at your exact K. Params and inline locals count too.
For-in loop variables are allocated **after** the enclosing scope. Holes come
from unused locals inside inlined helpers that cl declined to inline; a
`ScratchSlots<N>()` or a named unused local reproduces them (Papercut
`s0041dd90…`, resolved). Applied to `basic_string::WriteString`: swapping only
two local names (`p`↔`z`) turned a 4-byte diff into a MATCH (Papercut `w1g2
s005300d0…`). This hash order is observed for the
VS2008 backend; we have not observed it under `/vc71`, whose `/Od` slot order
was independent of declaration order too but not name-hashed in the same way.

### 6.5 cl 15.00 `static` + `/GL` and out-of-line bodies **[15]**

- A same-TU function called before its definition is still inlined by `/O2`;
  mark the definition `__declspec(noinline)` when the original calls it out of
  line.
- A helper member declared in the class but **defined as an empty stub `{}` in
  the same TU** gets inlined/removed, losing the call the original has. Declare
  it (and any auto-refcount `AddRef`/`Release`) **without a body** to force
  the out-of-line `call` (Papercut `s00577130`).
- `__forceinline` is required for the compiler to keep an inline helper's
  *boundary* in some cases; a same-TU helper that receives a local's address
  should be given its real body as a `__declspec(noinline)` specialization so cl
  knows it does not write the object (Papercut `s00948de0…`).

---

## 7. Stack layout

banteg's colouring rules ("slots coloured by lifetime, then size and use count")
hold for cl 13.10 and cl 15.00 at `/O2`. Spore-specific:

- **`/O2`:** homes come from a conflict graph over lifetimes, ordered by
  increasing size then decreasing use count (params scanned separately);
  narrow scoping or per-arm short-lived vectors let later values reuse slots and
  shrink the frame. Local-slot order under `/vc71` did **not** depend on
  declaration order in 24 shuffled variants (Papercut `s01126f80…`).
- **Large frames** are ordered by `floor(1000*uses/size)` with an unstable
  middle-pivot quicksort, same as banteg; one extra use can move a group.
- **Dead incoming-argument slots** hold locals once the arg is dead.
- **`/GS` and strike-through:** a `char pad[]` / `uint8_t` pad in a stack local
  triggers a `/GS` cookie at `/O2`; use `uint32_t pad[]` in stub structs. Under
  `/vc71`, `/GS-` is **ignored unless every stack array is `uint32_t[]`**
  (Papercut `s0109d9c0…`).
- **16-byte alignment:** a local `hkVector4` / `HK_ALIGN16` inplace array adds
  `and esp,-16`; `struct HK_ALIGN16 hkInplaceArrayD` reproduces the prologue
  (Papercut `cl2 s008beca0…`). Under `/Od`, editor modules with 16-aligned
  locals need `/Oy` added (Papercut batch-2).
- **`/Od`:** holes are reserved frames of inline callees cl declined; give the
  helper its real inline body so the hole appears by itself (Papercut
  `s0041dd90…`).
- **Vector3 / Havok alignment:** named scalar floats do **not** reproduce an
  aligned `hkVector4` frame; use an `hkVector4` local (Papercut
  `s01111330…`).
- **vtable + 16-byte-aligned members:** cl gives the **vfptr its own 16-byte
  block**, so declare the header explicitly as `uint32_t pad[4]` (then the
  members) instead of letting the vfptr sit inline. A `char raw[N]`/`char pad[N]`
  stub member forces a `/GS` cookie (see above); use `uint32_t raw[N/4]`
  (re-mined 2026-10-13).
- **`uint64` members pad after the vfptr** unless `#pragma pack(4)` (which then
  shifts every field by 4); an empty member struct occupies 1 byte. Cheap check:
  diff the set of non-stack `[reg+N]` offsets, original vs ours (re-mined
  2026-10-13).

---

## 8. Block layout and control flow

All of banteg's §Block layout applies: then-arm fallthrough, identical tails
cross-jumped (with a ~20-byte threshold), a late block/range mover that needs an
unconditional skip, and switch lowering to range-check + jump table or a
`sub`/`dec` compare chain. Spore specifics:

- **Switch case order** sets block layout while the jump table stays numeric.
  The `sub`/`dec` compare tree depends on case order, so brute-force orderings
  in one compile (Papercuts `bfs4 s21-23`, `s00945ed0…`).
- **Arm order is chosen by `if (x == 0) {A} else {B}` vs the inverted form** —
  decides which block is outlined (Papercut `s0060d860…`). A named `bool`
  compound predicate can set native arm order where structured control flow
  cannot (`matching.md`).
- **`do { if (a) break; ... } while (0)`** is the idiom for a guarded block with
  several forward exits to one join; nested ifs/early returns often compile
  identically because cross-jumping rebuilds shared exits.
- **`goto` ladders** are occasionally the only exact form where an if-chain and
  a switch both fail (`matching.md` grim_is_key_active).
- **[13] vs [15]:** Havok code under cl 13.10 loses the compare structure only
  when the compiler version is wrong; the block shapes themselves are the same
  family.

---

## 9. Floating point and x87 (and SSE)

**This is where the three toolchains diverge most, and where banteg's MSVC 6
guide needs the most adaptation.** CRITICAL context from
[`floating_point.md`](floating_point.md):

- The CRT sets 53-bit precision, then **D3D9 puts the device thread into
  **24-bit** x87 precision** (no `D3DCREATE_FPU_PRESERVE`). Gameplay/rendering
  therefore runs at **single precision**, which ports almost exactly to SSE
  `float` — *except* `double` arithmetic, which also runs at 24-bit and is NOT
  plain C++ `double`. `fsqrt` in 24-bit mode is correctly-rounded `sqrtf`.
- Never build with fast-math/FMA contraction for behaviour; use `/fp:precise`.
- Extraction: derive float sum **grouping from the asm, not the decompile**
  (stock Ghidra groups associative; patched Ghidra is NaN-exact — see the two
  patches in `floating_point.md`).

### 9.1 x87 operand shape is version-specific **[13] vs [15]**

- `fld st(i); fmul [m]` (keeps a just-computed value on the stack and multiplies
  by memory) is **cl 13.10**; cl 15 emits `fld [m]; fmul st(i)`. Havok x87 code
  never matches cl 15.
- `fstp [local]` then reload is **VC7.1** output; where the original does that,
  your source must keep the value in a **memory-resident struct field**
  (`hkVector4` local), because a `const float` scalar stays unrounded on the x87
  stack (Papercut `s010c2890…`). A `volatile` read of the stored field is the
  cheap lever (`s01092e10…`).
- The NaN-test mask **differs per site even within 13.10**: `if (a < b)` can
  emit `test ah,5; jp` or `test ah,1; je`; the original's opposite mask is
  sometimes `!(a >= b)`-shaped and sometimes not, and the NaN behaviour decides
  (Papers `s010c2890…`, `s01092e10…`). Read the mask off the asm; do not infer
  it from the C relational alone.
- A `double` compared against a `float` constant: `d < 0.5f` with `d` double emits
  `fld qword`; `(float)d < 0.5f` gives the original `fld dword` + `fcompi`
  (Papercut `cl2 s008beca0…`).

### 9.2 `sqrt` needs `/fp:fast` on 13.10 **[13]**

VC7.1 has no `/fp:` switch (it warns and ignores it). `sqrt` becomes a
`_CIsqrt` call; the original may inline `fsqrt`. If a Havok function FAILs on a
first `_CIsqrt` import, add `/fp:fast` to the flags (cl 13.10 ignores it, so it
is safe to carry) or use `/vc71` and the equivalence harness will inline it.
`/vc71` with `--flags "/vc71 /O2 /MD /Gy /TP"` is the reliable path
(Papercuts `s01111330…`, `s01094510…`).

### 9.3 SSE is a distinct toolchain mode **[15]**, also in RW4 audio **[13]**

Several modules are built `/arch:SSE` or `/arch:SSE2`, not x87. VC7.1 also
supports `/arch:SSE` (RW4's audio layer, e.g. `s0113dc00`, is `/vc71 … /arch:SSE`),
so SSE is not strictly a VS2008 marker — check the float opcodes, not the
version:

- Scalar `movss`/`xorps` for float copies, `ucomiss`/`subss` — but x87 still
  used for float args/returns. Flags: `/arch:SSE /fp:fast`.
- `/arch:SSE` mesh modules need `Vector3` user copy ctor + `operator=` for
  `movss` copies.
- `_mm_cvt_ss2si` (Floor/CeilToInt) adds `and esp,-16` and bloats frames; use an
  `__asm { cvtss2si }` block instead (Papercut `s01011530…`).
- Min/Max/Clamp use `minss`/`maxss`; `cmova`/`cmovbe` from an `/arch` flag.
- A `Vec4` copies as `movaps` only with an `__m128` union member.
- **Module flags by region** (Papercut batch-2):
  - Editor `/Od` (≈0x484e40–0x4a6660): `/Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast`,
    no `/EHsc`, often `/GS-`.
  - UTFInternet (0x945ed0–0x94a000): `/O2 /MD /Gy /TP /GS- /arch:SSE` (or SSE2).
  - INetFileCache: `/O2 /MD /Gy /TP /GS- /arch:SSE2`.
  - UI modules: **no** `/arch:SSE` (fld/fstp float pushes) and no `/EHsc`.
  - Windows-Mgr modules with member dtors: no `/EHsc`.

### 9.4 The rest of banteg's §Floating point transfers

- **Float32 stores at expression/object boundaries**, `fst`-and-keep vs
  `fstp`-and-reload, **parentheses emitting `FROUND` nodes** (VC6 C1); the
  cl 15 front end keeps the same parenthesis-sensitivity (Papercuts mention 81-
  node scheduling windows and parenthesised lanes). Constant folding of additive
  chains, x87 operand orientation following source order, `double` locals and
  cast placement, literals that must round to the native bits (one-ULP traps),
  a local snapshot of a float global (`fld st(0)` duplicate), and integer views
  via `memcpy`/one-float wrappers — all apply. See
  [`floating_point.md`](floating_point.md) and banteg for the mechanisms.
- A float literal read as `fmul dword [mem]` against a double needs an
  `extern const float` **variable**; a literal `0.001f` folds to a **double**
  constant (`fmul qword`) (Papercut `s010c2890…`).

### 9.5 Per-function and literal-shape levers (re-mined 2026-10-13)

- To get an inline `fsqrt`/`fpatan` **without changing slice flags**, scope
  `#pragma float_control(precise, off)` to the one function and call
  `(float)sqrt((double)x)` / `atan2((double)y,(double)x)` — useful where only one
  function in an `/fp:precise` slice needs the fast form **[13]/[15]**.
- The **literal's type**, not its value, picks the opcode: `1.0 - x` (double) →
  `fld1; fsubrp`, `1.0f - x` → `fld1; fsub` — same family as the `fmul dword` vs
  `fmul qword` case above.
- `(float)(uint32_t)x` lowers to `fild` + a conditional `fadd 2^32`; the recurring
  Ghidra `if (x < 0) f += 4.29e9` lines are unsigned casts, not hand-written
  source **[13]/[15] x87**.
- `_mm_cvtsd_si32(_mm_set_sd(x))` reproduces x87 `fistp dword`, including the
  `0x80000000` overflow clamp; the single-precision intrinsic does **not**
  **[15] SSE**.
- x87 compare **NaN polarity**, read from the exact mask: `test ah,5; jp` is
  `(a<b)` and `test ah,0x41; je` is `(a>b)`; `if (!(x >= -r))` avoids a
  canonicalised operand swap when the original did not swap (extends §9.1).

---

## 10. Instruction selection

banteg's §Instruction selection (source types and comparison spellings go
literally into instructions) holds for cl 13.10 and cl 15.00. Spore-specific
additions:

- **cl canonicalises bit-test idioms:** `(f & 0x100) >> 8`, `!= 0`, `?1:0`,
  `/256` all become `shr;and 1` for any unsigned/int flags. The original's
  `and 0x100; shr 8` came only from an `int16 flags` with `(flags & 0x100) != 0`
  (Papercut `s008ce020…`).
- **`return k == 0xd;`** emits `xor eax,eax` first; `if (k == 0xd) return true;
  return false;` emits `setb` (Papercut `s00a20060…`). Same as banteg.
- **`_alldiv`/`_allmul` must be declared `__stdcall`** (callee pops 16 bytes);
  `__cdecl` adds a stray `add esp,0x10` (Papercut `s0092e3d0…`).
- **`#pragma intrinsic(strlen/strcmp)`** selects the `lea esi,[eax+1]; mov dl,
  [eax]; inc eax; test dl,dl` idiom and the pair-unrolled `sbb/sbb` compare; a
  hand loop gives `movzx` (Papercut `s008fc670…`).
- **`wcslen()` intrinsic** is `lea edx,[eax+2]; mov cx,[eax]; add eax,2; test
  cx,cx; jne`; a hand loop is `cmp [eax],0; add eax,2` (Papercut `s0092e3d0…`).
- **`_ReadWriteBarrier()`** pins an order; `_Interlocked*` intrinsics are
  semantics, not shape (see §12.2 and `matching.md`).
- **Byte swaps** use `_byteswap_ushort`/`_byteswap_ulong`; a shift/or swap
  becomes `rol`, a memory swap spills (Papercut `s00945ed0…`).

---

## 11. Calls and ABI

### 11.1 Calling conventions are read from the epilogue

`ret N` with ECX used as `this` = `__thiscall` (declare a stub class, `char
pad[N]` gaps, `uint32_t pad[]` not `char`); `ret N` without ECX = `__stdcall`;
ECX+EDX args = `__fastcall`; plain `ret` = `__cdecl`. **Every callee needs the
right convention**, and the byte diff barely notices a wrong one — the most
common equivalence bug is a thiscall declared as free `cdecl`/`stdcall`
(`matching.md` "check every direct callee"). `__thiscall` is rejected on free
functions (C3865) but accepted inside function-pointer casts (Papercut
`s0064dbd0…`).

A method whose `this` is a **secondary base** (cl emits `lea esi,[ebp-4]` /
`add esi,-N` before the owner calls) should be an ordinary member of the **full**
class via **real multiple inheritance** — cl then reproduces the subobject `this`
and the shifted offsets itself; find the vtable with a `.rdata` scan for the
function address (re-mined 2026-10-13).

### 11.2 cl 13.10 has no usable `__thiscall` in casts **[13]**

The VC7.1 toolkit cannot cast to `__thiscall`; you must model each direct callee
as a stub-class member (`match/slices/s0113dc00`).

### 11.3 Hidden sret and `void`-hides-eax

Struct-by-value returns use a hidden destination pointer (first stack arg,
returned in EAX). The body is byte-identical to an explicit out-pointer
contract, so the callee alone cannot tell them apart — but the **caller and
EAX differ**. banteg's rule applies unchanged.

The `void`-hides-eax family is the **single largest Spore defect class**: the
byte diff cannot see it (relocations are masked, so a callee's address and its
return convention are not checked), and until 2026-10-12 the equivalence
harness compared EAX only when *our declaration* had a return type. So a
function the original hands a value back from was declared `void`, PASSed the
emulator's synthetic inputs, and then crashed the hybrid: **seven defects in
one day** (2026-10-12). Always **declare the return the original has, not the
one the dev PDB or the pseudocode suggests** — especially where **[LTCG]**
callers consume EAX.

**Static detection** (`returns_eax` in `tools/difftest/regfacts.py`, shared by
the harness and `tools/hybrid/build.py`). The original returns a value in EAX
when, for **every** `ret`, walking back to the last EAX writer stops before any
`call` (a call means the value is not computed here — but see the wrapper case
below) and the write reaches the ret surviving only `pop`/`leave`/`add esp,N`,
or is one of these shapes:

- a **hidden return pointer** handed back: `mov eax,[esp+…]` with a store
  `mov [eax+…],…` in between;
- **`return this`**: `mov eax, ecx` (the classic `ArenaSelf::initRange` shape);
- a **call-free** function whose *first* EAX write is a load
  (`mov eax, dword ptr [ … ]`) or `mov eax, ecx`, with nothing rewriting EAX
  before the ret — a pop-front, a `lower_bound`, a copy returning its end
  pointer, an init returning `this`.

Confirmed instances, all once declared `void` and all PASSing before the fix:

| Function | Shape | Symptom when wrong |
|---|---|---|
| `ArenaSelf::initRange` 0x011e29c0 | `eax = ecx` on entry, kept to ret → returns `this` | LTCG caller used the object; next hash lookup divided by garbage |
| `LowerBoundPair` 0x007c8160 | `lower_bound` over 16-byte pairs; returns the position | caller read `[eax+4]` of garbage and crashed |
| `rbtree::find` 0x00e5c780 | iterator via hidden return pointer; not-found → eax = 0 | `RegisterCommandGenerator` crashed at the not-found path |
| rw audio pop-front leaf 0x01141200 | returns the popped node in eax (0 when empty) | voice allocation got the list pointer; audio never started → **black screen** |
| `InterpRamp` 0x114e780 | returns a **pair in EAX:EDX** | (also the untouched-register case below) |

Two refinements the build gate encodes beyond `returns_eax`:

- **Constructors are exempt** (`??0…`): a thiscall constructor hands `this` back
  in EAX on both sides, so a `void` declaration there is not a defect.
- **A `void` wrapper returns its last callee's EAX.** If the original makes a
  call and does *not* write EAX after it, the value the caller sees is that
  callee's EAX (an allocation callback, `Pool_AllocGlobal` 0x928ad0). Ours must
  then also not write EAX after *its* last call
  (`writes_eax_after_last_call` in `build.py`). Two hybrid crashes came from this
  family (`uninitialized_copy` 0x0099efa0, `rbtree::find` 0x00e5c780).

For a **[LTCG]** caller this is worse than for `[15]`/`[13]`: the linker sees
the callee's body and *relies* on the returned value, so a wrong declaration is
a silent miscompile rather than a benign idiom. The harness now compares EAX at
return whenever `orig_returns_eax` holds, promotes `ret_kind` to `unknown`, and
sets `void_hides_eax` with a layout note; `tools/hybrid/build.py` refuses such
hooks. Regression test: the pop-front mutant (declared `void`, no return) must
FAIL on `eax`.

### 11.3.1 `ret N` is part of the contract

The immediate on `ret N` **is** the argument-cleanup amount — thiscall and
stdcall callees pop their own arguments, cdecl callers do. A `ret 4` original
declared `ret` (or the reverse) leaves the caller's `esp` off by 4 bytes on
every call. Two hooks were found this way (`ret 4` vs `ret`: 0x0056fe60,
0x0075c9d0). `equiv.py` records the original's `callee_pop` (max of its ret
immediates) and `pop_variants`; the observable comparison fails on `esp`.
Caveat: a function-table extent can contain **two** ret forms (`0x6e6a20` has
`ret 12` and `ret 20`) because the discovery pass merged neighbours — split the
extent instead of treating it as one ABI.

### 11.3.2 Untouched registers are a per-call-site contract **[LTCG]**

An LTCG caller may keep a live value in a register it can prove its callee never
writes — the same fact that lets `Raster::Initialize` keep `edx` across a call.
So our replacement must not write a register the original never writes and left
untouched. `InterpRamp` 0x114e780 wrote `xmm3` where the original uses only
`xmm0–2` and `xmm7`: crackling audio, no crash, PASS, 100% coverage. **169 of
1,730 PASS hooks** wrote some register the original does not (50 `ecx`,
43 `edx`, 15 `ebx`, 15 x87, 38 `xmm`). `regs_written` in
`tools/difftest/regfacts.py` computes the original's written set (minus
`pop`-restored registers); the harness fails on `<reg> (untouched by the
original)`, and `build.py` refuses the hook. The compiler owns allocation, so
the fixes are indirect: fewer live temporaries (recompute instead of caching),
the original's expression order, `/arch:SSE` vs x87 as the original, or declare
a custom register ABI / asm shim in the row. `orig_untouched_regs` is in the
result.

### 11.4 The `/LTCG` custom register ABI **[LTCG]**

This is the Spore feature with **no MSVC 6 analogue**. Under `/GL` the compiler
emits low-level IR and `link.exe /LTCG` generates code seeing every callee:

- It keeps a value in a register it can prove the callee does not touch.
  `Raster::Initialize` (0x011efeb0) keeps `edx == 0` across `FormatGetDepth`.
- It allocates registers **globally across call boundaries**, so a single-object
  compile makes different choices. A caller may thus read a register at entry
  that no C signature explains (`docs/tickets.md`: "original reads ecx/eax at
  entry, our decl passes nothing" — 259 rows; "custom/LTCG register ABI").
- A hook that writes a register the original leaves untouched can corrupt the
  caller: §11.3.2 has the static detection (`regs_written`) and the fixes, and
  `tools/hybrid/regfootprint.py` lists the affected hooks. The compiler owns
  allocation, so the fixes are indirect.
- **Policy:** equivalence-only for callers; leaf functions may still match.
  `equiv.py` reports such ABI mismatches as UNSUPPORTED rather than testing
  them.

### 11.5 The rest transfers

Right-to-left argument evaluation, caller cleanup coalescing (fixed-arg
prototype vs variadic; C coalesces more aggressively than C++), varargs members
falling back to cdecl with `this` pushed, `new T` emitting an out-of-line
allocation-failure block, compiler-generated scalar-deleting destructors, and
unreachable epilogues after imported `longjmp`/`exit`/`_endthread` (VC does not
treat them as noreturn) — all as in banteg. Plus:

- **`printf`-style members**: `this`, x, y, fmt are all pushed; plain `ret`.
- **`throw()`** on a dealloc helper removes extra EH stores; declaring a
  constructing function `extern "C"` omits the constructor unwind graph C++
  linkage keeps.
- **Inline `__asm` in an atomic helper blocks inlining** — so the original did
  not use it (Papercut `s0060d860…`).

---

## 12. Data, sections and linking

### 12.1 Linker folds identical COMDAT bodies (ICF)

Identical bodies (no-op ctors, identical dtors, empty debug functions) fold to
one address; the caller's prototype still decides its stack cleanup
(`handoff-resolve-unresolved-refs.md` "MSVC link-time code folding"). Emit both
natural bodies and let the linker fold; use a weak-external alias only when an
identity has no recoverable body. This is stronger under **[LTCG]** and can make
two decorated identities resolve to one implementation.

### 12.2 Atomics are semantics, not shape

Where the original has `lock xadd`/`lock cmpxchg`/`lock inc/dec`/`xchg mem,reg`,
write the `_Interlocked*` intrinsic — never `++*(volatile long*)p`. The
single-threaded equivalence harness passes the plain version and the game then
races (Papercut, 0x0070eb30, 0x006df280, 0x00833400). `build.py` refuses such
hooks.

### 12.3 Static initializers and globals

- `ResourceKey kX(id("Name"), 0, 0)` folds the runtime hash to an immediate
  (`tools/hashnames.py`; 8,374 functions). A plain constant folds to static data
  under `/O2`, so the initializer must stay dynamic — shape-equivalent, but a
  relinked build must register it in `.CRT$XCU`.
- Function-local statics share a guard with one bit per object in declaration
  order; each object with a destructor gets a COFF-local `$E<n>` thunk pushed to
  `atexit`. Introducing a new local-static scope shifts `$E` numbering and can
  need TU co-location to link (§12.4).
- A global array of a class with a destructor emits a reverse array-destruction
  callback `_$E2` calling `??_M` with the stride; placement-constructing over
  static storage removes the null check and reproduces the initializer exactly.

### 12.4 Translation-unit neighbours are mostly neutral

Symbol ids and most codegen are per-function, so compiling address neighbours or
shared classes in one TU is normally byte-neutral. **Exceptions:** the preceding
function can decide tail cloning/merging (**the block mover sizes tails with the
previous function's frame flags**), and compiler-local names (`$S`/`$E`,
`$L`/`$T`) renumber with TU contents. On **[LTCG]** the linker sees the whole
program, so "TU neighbours" becomes "everything"; on **[15]** with `/GL` some
modules defer codegen entirely.

### 12.5 String literals and enums

VC (all versions here) pools identical literals; `/O2` emits diagnostic
literals as separate pooled COMDAT objects in address order, `/Ox` flattens or
aliases them. Add `extern const wchar_t[]` (not a literal) when you need the
original's `strlen` loop + `rep movsd/movsb` instead of unrolled `movs`
(Papercut `s00945ed0…`).

---

## 13. Toolchain and flags

Fix the profile from Rich/`@comp.id`/archive provenance first, then work on
source. Flag matrices almost never explain a residual in game code.

### 13.1 Recovered build settings

| Setting | Evidence |
|---|---|
| `/O2` with frame-pointer omission | `/Oy-` breaks every match; `/O1` and `/Os` diverge |
| `/MD` (dynamic CRT) | CRT calls go through the IAT (`mov ebp,[__imp_towlower]; call ebp`) |
| C++ (`/TP`), `/EHsc` | mangled class methods, EH tables elsewhere |
| Some modules `/Od` | e.g. hash table near 0x0050E850, editor region |
| `/arch:SSE[2]` in mesh/UI/UTFInternet modules | SSE float copies, `cmov*` |
| `/GS-` where no cookie | a module with `wchar_t buf[64]` and no cookie |
| `/vc71` for Havok + RW4 core | dev PDB `S_COMPILE` = cl 13.10.3077 |
| `/GL /LTCG` for RW4 core | cross-call register allocation |

- RTM vs SP1 is still open: the Rich header was destroyed by SteamStub, and the
  manifest's `9.0.21022.8` CRT binding is SP1's default too. Every function so
  far matches with SP1. Test residual mismatches against VS2008 RTM
  (15.00.21022.08).
- Havok was built with **cl 13.10.3077**; we match with **13.10.3052** (Visual
  C++ Toolkit 2003).
- VC7.1 has no `/fp:` switch.
- **`SPGonzago/SPCellGame.obj` is a `/GS-` TU.** `00e66280` carries a
  ~0x800-byte escaping stack buffer and **no `__security_cookie`** prologue, so
  reconstructions there need `/GS-` in their manifest flags (spcg1, 2026-10-14).

### 13.2 The `[DDK]` / provider toolchains

`d3dx8.lib` members carry product 29 build 9178 (XP DDK), not VC6/VC8: it
selects `and byte [..],0` where VC7.1/VS2008 emit `mov byte [..],0`. Use the
`msvc7.0ddk`-style profile. Compile pinned upstream source (IJG 6a, zlib 1.1.3,
libpng 1.0.5) without shaping it. `/Oi` is required for some `rep stosd`
sequences. These are "freebies" excluded from the denominator (see
`STATUS.md`), but their Rich counts are provider ancestry in the exe.

### 13.3 Global practicalities

- `types.h` from `match/include` for fixed-width types; stub structs use
  `uint32_t pad[]`.
- Under zsh, a flags string in a variable is one argument unless `${=var}`.
- Scratch files must carry the slice id (`work/match/scratch_<slice>_*`); the
  session scratchpad is shared and gets clobbered.
- `#pragma pack(4)` around DirectX Win32 structures: the Wine `d3d8` header
  applies `pshpack4` only under `__i386__`, which VC does not define
  (`_M_IX86`), silently growing every DirectX struct and shifting every frame
  displacement (Papercut `grim_d3d_init`, `D3DADAPTER_IDENTIFIER8` 0x42c→0x430).
  One site, silent and general.

---

## 14. Scoring pitfalls and methodology

### 14.1 Scoring pitfalls

- **Raw match% moves with alignment, not semantics.** Branch labels compare as
  byte offsets, and C2 rotates scratch registers, so one extra temporary renames
  every later register, a size change relabels every branch, a frame diff shifts
  every stack operand. Correct changes can lower the raw score while
  label-masked views rise. `chk.py` prints `(no symbol of similar size)` when the
  size is >12.5% off, and its "best symbol" column often names an unrelated
  function — use `cmpdis.py` with the **exact mangled name** for real diffs.
- **`cmpdis` masks relocations to zero**, so every `call`/`push <addr>` shows as
  a diff and hides the real one; and it disassembles the original only up to
  your length, so size mismatches truncate the tail. A register/stack-normalised
  whole-function score over both full lengths (calls masked) ranks variants
  reliably.
- **Judge with** label-, register- and stack-masked views, encoded-body
  identity, a relocation-aware reference audit, and the instruction count.
  Reject winners that delete native temporaries, add reference mismatches, change
  the lowering kind, or move the count away from native.

### 14.2 Methodology

The workflow is `matching.md` "Workflow"; the lessons that keep recurring:

- **Test interactions, not single mutations.** Many exact matches needed
  several coordinated changes that were each neutral/negative alone. Sweep
  pairs and full combinations; propagate a lifetime change to every homologous
  site before calling something a residual.
- **A negative sweep holds only for its baseline.** Replay rejected spellings
  after an ownership/lifetime change.
- **Fix frame, extent and ABI first.** Map ESP-relative homes per access, treat
  a frame-size delta as one root cause; settle the function extent (epilogues
  after noreturn calls, guard-bounded switch tables) and the convention
  (`ret imm`, ECX use, EAX residue) before chasing instruction deltas.
- **Provenance comes from Rich/`@comp.id`/archive evidence, not the best score.**
  Rule flags out once with a matrix, then work on source.
- **Native evidence outranks a minimal-source prior.** No-op parentheses, split
  increments and overwritten default stores are real when they move toward native
  without adding reference mismatches.
- **`equiv.py` is evidence, not proof.** PASS = a few hundred fuzzed inputs
  bit-identical at ≥60% coverage. Check `coverage.pct`; treat the uncovered part
  as untested.
- **The harness's blind spots were the game's crashes.** The hidden-eax family
  alone produced seven of twelve hybrid defects in one week; fake-call
  `this`/argument order produced four more; untouched registers (LTCG) and
  atomics produced the rest. All are now verdicts (`void_hides_eax`,
  `fake call #k …`, `<reg> (untouched by the original)`, a locked-instruction
  count check), but the lesson generalises: a PASS from synthetic inputs is not
  game-safe, and **the byte diff is blind to callee addresses, return
  conventions and register footprints** because of relocation masking. When
  adding a class of worst-case code, ask what the *caller* needs from the callee
  and verify that, not just the callee's own output.
- **Do not write a register the original never writes** on **[LTCG]** callers;
  the compiler owns allocation, so fix it indirectly.

---

## 15. Levers found in the 2026-10-19 overnight waves

The dec1 and mig waves (reports in `work/claude/dec1_reports/`, requests in `work/claude/mig8_requests.md`) found these. Each one made at least one function byte-exact or removed a named diff. They are not yet folded into the sections above.

**Frame and stack slots**
- MSVC reuses a dead parameter's stack slot for a later local. Reusing the parameter in source (`int& count = (int&)key;`) reproduces it (0x661b10).
- An empty-class temporary, such as an empty allocator argument, is passed as the address of an existing parameter slot. Passing `&param` reproduces the reload after the call (s00689ee0).
- An output dword local must be `uint32_t`, not a 12-byte struct, or the frame grows (s00660dd0).
- Local order is not plain declaration order. In 0x91fca0 the locals sorted by size ascending, then by declaration. Shrinking an array (`char q1[0x105]`) was the only way to move it below another.
- For `/Od` slot order, see `tools/matching/od_names.py`. A hill-climbing probe prototype that found a 14-local order in one run is at `work/match/scratch_s0056a7b0_probe.py`.

**Calls, EH and inlining**
- Declaring a dealloc helper (`EastlFree`) `throw()` removes the extra EH state store before an inlined vector destructor (0x711490).
- A six-argument placement `new` gets its EH state stores only when a matching placement `operator delete` is declared (0x697c40).
- MSVC drops a call to an empty function in the same file even when it is `noinline`. Give the stub a `volatile` store (0x5e4560 and its caller 0x5e49c0).
- MSVC elides `mLayout(Tmp())` copies. Use a distinct temporary type with its own constructor and destructor, and put the member in a base class so the derived vptr store comes after the member copy (s008087f0).
- `delete f()` and `delete p` produce the inlined scalar-deleting-destructor block, and a default-argument allocator temporary inside an inlined vector constructor gives the temp-then-stores order (`/Od`, s00440110).
- A class-level `operator new` reproduces a null-checked allocation (0x6b5c50).
- A function whose original has no unwind frames around its refcount temporaries must be compiled without `/EHsc`. Several property-UI functions need `/O2 /MD /Gy /TP /arch:SSE /fp:fast`.
- Functions with an old-style EH frame often match only under `/GS-`.

**Types and layout**
- Model `cSPUIBehaviorEventBase` with real multiple inheritance (a 0x18-byte primary base, the interface at +0x18). The container null-check then comes from the upcast; this flipped three functions in s007f9550.
- An EASTL bool tag passed by value is a `struct { bool b; }` local set to false. The compiler stores a 0 byte into a dead parameter slot and pushes the dword (0x660c10).
- In `insert(&it, v.Ctor(...), tag)` the `Ctor` call is evaluated before the tag store.
- A hinted map insert, an iterator passed by value, and `__assume(p == 0)` on null `AutoRefCount` temporaries took 0x69eb60 from 134 to 69 diff bytes.
- Pass the raw pointer to the inlined `AutoRefCount` copy to get the original's register-held refcount pointer (s00660dd0).

**Intrinsics and floating point**
- An unrolled two-character compare ending in `sbb eax,eax; sbb eax,-1` is the `wcscmp` intrinsic (`#pragma intrinsic(wcscmp)` with `<wchar.h>`). Use `wcslen` the same way.
- `fabsf` without `/Oi`: declare `extern "C" double __cdecl fabs(double); #pragma intrinsic(fabs)` before including `math.h` and `xmmintrin.h`.
- `if (fabsf(x) > kGlobalConst)` gives the SSE compare through a stack temporary. A literal gives x87 `fcompi` (s0056a7b0).
- `/arch:SSE2` turns 0x24-byte by-value copies into `movq`, where the original uses `rep movsd`. Use `/arch:SSE` for such functions (0x65ef30).
- `_ReadWriteBarrier()` also pins a load after earlier stores (0x7cde80, 15 diff bytes to 0).

**Not a lever: member access vs raw offset casts** (controlled test, 2026-10-19, `work/claude/exp_style/`)
- Rewriting `p->mX` as `*(T*)((char*)p + OFF)` with the same `T` and `OFF`, or the reverse, changed nothing in 40 of 41 functions: 14 of 15 byte-exact functions stayed exact, 15 of 15 non-exact and 11 of 11 cast-to-member functions kept their exact diff byte count. MSVC 2008 folds both forms into the same addressing. Prefer member access for readability, but do not spend rounds on it to chase bytes.
- The exception (0x452080, `/Od`): a `float` member read passed as a call argument went from `fld/fstp` to `movss` when written as a cast, and an inline method called on a cast lvalue (`OFF(hkVector4,&info,0x10).set(...)`) spilled an extra pointer temporary, growing the frame. Under `/Od`, keep float member reads and method receivers as member access.
- What does move bytes is what the casts usually stand in for: a wrong member TYPE (`void*` locals vs a typed self-referential node), a wrong layout or padding, and missing language constructs (arrays of destructible objects, `bool` returns, base destructors). The higher exact rate of member-style code in the slices comes from those, not from the syntax.

**Still without a lever**
- the `sub eax,N / je` dispatch chain (0x7e0340, 0x7e05e0), where switch, if-chain and unsigned switch all give range compares;
- the property-UI `Modify*` frame of 0x60 against the original's 0x4c (nine functions);
- a callee's ABI that is custom register arguments.

## 16. Levers found in the 2026-10-20 waves (dec2, gold2, gold3)

Mined from the final-report lessons of 127 DeepSeek sessions and 45 `work/match/scratch_*_papercut.md` notes. Each item made a function byte-exact, removed a named diff, or turned an equivalence FAIL into PASS in at least one slice. Items that sections 1–15 or `matching.md` already cover are left out.

**Read the calling convention off the caller first.** This was the largest single lever of the three waves.
- `push`es then `call` with no `add esp` afterwards means the callee pops: `__stdcall`, or `__thiscall` if `ecx` was set. `add esp,N` after the call means `__cdecl`. A `ret N` in the target fixes its own argument count exactly (0xa1b440 dropped a phantom first parameter and stopped failing on `esp after return`).
- A function that uses `ecx` as `this` must be a real member function. A free function taking an explicit `self` pushes the object and gets the wrong cleanup. Converting such functions to members took one slice from 1 to 7 byte-exact (0xa1acd0–0xa1b440) and another from hundreds of diff bytes to zero on eight functions (slice 71).
- For an absolute-address callee, declare it as a member of a declaration-only placeholder struct (`struct TC_x { void f(int); };`). That gives `call rel32` with `this` in `ecx`. A function-pointer cast to the address gives `mov eax,addr; call eax`, which is 5 bytes longer. The unresolved symbol is fine, because chk masks relocations.
- A tail call `mov ecx,esi; jmp f` needs `f` to be `__thiscall`. A `__cdecl` callee forces push, call, add and ret.
- A `static` member defaults to caller-pops. `static void __stdcall f(...)` gives the original's `ret 0xc` (0x74a290).
- The CRT EH helpers (`_eh_vector_constructor_iterator` and the like) are `__stdcall`, with `YG` in the mangled name. Better still, declare a local array of a class with a constructor and destructor (`RDesc8 desc[4];`), and cl emits both iterator calls and the EH frame itself.
- A 12-byte struct passed by value through a vtable slot must be a by-value aggregate parameter, which gives one `sub esp,0xc` block; three scalars give three `push`es. Conversely, a "struct" the original pushes as separate dwords (EAPd's `t_symbol` in `trigger_list`) must be declared as separate dword parameters. Count the pushes.
- Argument order is visible only in the push order, and equivalence reports it as a fault on one middle word (`call #0 arg 3`). `outlet_list(to, argc, a, s, argv)`-style reorderings flipped six EAPd functions from FAIL to MATCH.

**Return types**
- A `bool` return gives `mov al,1; ret`, and a `void` one gives `jmp edx` (0xa1acd0). A `uint8_t` return must stay `uint8_t`: `mov al,[ecx+0xc0]; shr al,3`, where `uint32_t` gives `movzx eax`. x87 returns must be declared `double` to come back in `st0`.
- Scalar deleting destructors return `this` in `eax`. Declaring them `void` gives a spurious equivalence mismatch on `eax`.
- `bool found = x != 0; return found;` gives `test; setne al`. Returning the comparison directly gives the 32-bit `neg; sbb; neg` normalize.

**Statement shape decides block layout**
- `switch` emits out-of-line case blocks where three `if (id == K) { store; return; }` tests got inlined at each test (gold2 range r26).
- Two separate early returns, not `a || b`, collapsed DoMessage from 93 to 20 diff bytes. `if (A && B) {...} else {...}` matched OnRebuild.
- To put a rare case's body out of line after the `ret`, invert the guard: `if (m != 2) { ...; return; } call1;` (0xba6660). `if (table) return call(...); return false;` keeps the false block out of line, while `if (!table) return false;` inverts the `je`/`jne`.
- cl15 tail-merges a shared `*pValue = value; Advance(); return true;` only from the nested `if (n == 4) ... else { if (n != 3) ... }` shape. Flat `else if` and `goto` versions duplicate the epilogue.

**Expressions and types**
- `mov eax,0x80; test byte ptr [obj],al; jne; or [obj],eax` comes from the mask held in a local (`uint32_t mask = 0x80;`). An inline literal loads the whole dword and tests `al`.
- A min/max that the original computes as a pointer-select (`lea`/`ja` over two stack addresses) needs both operands to be addressable locals. With literals or `if (x < y) x = y;`, cl emits conditional moves and the function comes out about 200 bytes smaller.
- Copying a field pair as one `*(long long*)&dst = *(const long long*)&src` flipped a register swap to the original's allocation (CellList::push_back, 7 diff bytes to 0).
- A float field the original copies with `mov edx,[ecx+x]; mov [eax+y],edx` must be copied through `uint32_t*`. Through `float*`, MSVC emits `fld`/`fstp`. Likewise a parameter stored with `mov` rather than `movss` is an integer.
- Declare a pointer parameter `u32**` and dereference `*base` inside the loop to keep the original's pointer-compare loop with its per-iteration reload. With `u32*`, cl computes a trip count and uses `mul` (DestroyValues, 0x104 stride, to byte-exact).
- Binding a member to a local reference before a branch (`string_type& t = mMatchText;`) makes cl cache its address in a register before the `jne`. That removed about 370 diff bytes from MatchColor.
- Compute a call's store target before the call (`float* d = ...; *d = fn(...);`) to get `mov edi,[esi+0xc]; add edi,0x1e4; call edx; fstp [edi]`.
- A guard on the address of a field of a fresh allocation (`lea ecx,[eax+8]; test ecx,ecx; je`) is real: write `if (&pNode->mValueA)`. Removing it shrinks the function.
- `(*(void***)obj)[n]` emits two loads, and going through a `vftable` member emits three. Write a vtable call as a bare inline cast; an inline helper that returns the function pointer makes cl spill the callee.
- A declared `float one = ...;` placed between two stores stops cl from reloading an aliasing global twice (SetColor_8 and SetColor_14 to byte-exact).

**Floating point and flags**
- `(float)sqrt((double)x)` gives the original's x87 `fld; fsqrt; fst`. `sqrtf` gives the SSE form (0xfc2080 to byte-exact).
- `cvtss2si` in the original is round-to-nearest. A plain C cast compiles to truncating `cvttss2si` and is behaviourally different for fractional inputs, so the equivalence gate fails it. Use the `__asm` helper from `matching.md`.
- A float compare done as single-precision `ucomiss` needs `/fp:fast`. `/arch:SSE2` alone gives `cvtps2pd; ucomisd` and clobbers `xmm2`, which also fails equivalence (StageCache::Ready).
- A region comment that says `/arch:SSE2` is wrong when the original uses x87 `fsqrt`/`fdivrp`. Recompile with `/arch:SSE`; this also removed an `xmm4` clobber that had failed equivalence (0x7df780).
- `/GS` puts a stack cookie on any local whose type contains an array. Spelling a large padding as nested scalar structs removes the cookie and its frame shift (0x9c2ef0 and 0x9c3040 to byte-exact).
- `#include <math.h>` makes `fabsf` an intrinsic. A hand-declared `fabsf` compiles but stays an unresolved external, so every caller becomes UNSUPPORTED under equivalence.
- `__declspec(dllimport)` on `wcsstr` gives the original's IAT call where cl would otherwise inline the loop.

**EH frames and object lifetime**
- A non-trivial destructor on a local is what buys the original's `_ehhandler` prologue. Hand-written cleanup drops the frame (0x60eab0 to byte-exact). `__try/__finally` instead gives a full `ebp` frame: don't.
- An explicit `p->~T()` with an inline `~T` gives `/Od`'s "dead guarded delete" (`xor r,r; and r,1; je; push p; call ??3`). A `bool`-guarded `delete p;` does not (0x5702c0 to byte-exact).
- A function with C linkage loses the EH cleanup of a placement `new`. Keep such a function C++, and see `tools/matching/synth_templates/eh_unwind_placement_delete.py` for the declaration pair.
- `__forceinline` on a value-type copy constructor keeps it from being emitted out of line as `push; call ctor`.
- Under `/Od`, unused scalars get no stack slot; only arrays do. Frame padding must be real arrays.
- For a "dead" vptr store the original keeps, make just that store volatile: `*(void* volatile*)&mpVtbl = ...` (0x714260, 0x713f90, and the base-ctor case 0xfc4cd0).

**Class-key: take it from the PDB, never from convention**
- The dev PDB records whether each type was declared `class` or `struct`: `tools/pdb_type.py <Name> --exact` prints it as the first word of the layout. MSVC also mangles it into every symbol that takes the type as a parameter (`PAV<name>@` for a class, `PAU<name>@` for a struct), so the wrong keyword gives a symbol name that differs from the PDB's.
- EA did not follow the "struct for plain data, class for hierarchies" convention: `cSPVector3` is a `struct` with a base class, and `EA::ResourceMan::Key` is a `class`. Use the recorded keyword even when it looks unconventional. A `class` needs `public:` before members that other code uses.
- The keyword changes no bytes of code, only mangled names. When you change it, update the manifest rows that name affected symbols in the same edit. `tools/classkey_triage.py` lists every definition in our sources whose keyword differs from the PDB's.
- Swapping the keyword also swaps the default access of members and bases, and MSVC mangles member access too (`Q` public, `A` private). So write the old default out: `struct X : B {` becomes `class X : public B { public:`, and `class Y {` becomes `struct Y { private:`. Then only the U/V letter changes.
- The letter appears wherever the type does: pointers and references (`PAU`/`PAV`, `ABU`/`ABV`), by-value parameters (`UName@@`/`VName@@`), returns (`?AUName@`), template arguments (`U?$Name@`) and back-references (`PAU12@`). A by-value or template use is easy to miss when re-binding rows.
- Forward declarations must use the same keyword as the definition. MSVC mangles with the keyword of the first declaration it sees (warning C4099), so a stray `struct X;` above `class X {...}` keeps the old letter.
- A keyword change in a header that other slices include (`../s010cbaa0/hk31_b005.h`) renames symbols in those slices too. Re-run `run_all` on every slice that includes the header, directly or through another header, and re-bind their rows; their manifests are otherwise silently broken until someone runs them (five slices were, after the class-key pass).
- `tools/classkey_fix.py <slice | src/game/<dir>/<obj>>` does all of the above for one unit: it swaps the keyword with explicit access, follows forward declarations, re-binds manifest rows, and keeps the edit only if every row still matches (or, with `--object-gate`, if a unit with no manifest rows compiles to identical code). It does not re-run includers of a shared header; do that by hand.

**Signs that an object was built by an older compiler** (stop early; cl15 cannot reproduce them)
- It materialises the constant 0 as `mov eax,esi; sub eax,esi`.
- It keeps both null checks of an `if (x && x)` that cl15 merges.
- It makes per-field struct copies where cl15 emits `rep movsd`.

**Not source-controllable** (confirmed across many slices; record the function as complete and move on after two rounds without a diff drop)
- Which callee-saved register holds `this` or a loop pointer (`esi`/`edi`/`ebx` swaps), and `edx`/`ecx` swaps in the same instruction stream.
- MSVC 2008 stores a constructor's `field = 0` before the base vptr, and cl15 does the reverse.
- The frame sharing around pushed `double` varargs, which costs 12 bytes in `cSetC`/`V2`/`V3`/`V4`.
- Six `push`es against `sub esp,0x18` plus six stores for a by-value 6-int block (five 0xba5xxx functions).
- Extended-precision x87 ordering that differs by one ULP.
- Reordering stores or `lea` temporaries to "match" the disassembly. It made three EAPd functions worse, so revert any experiment that raises the diff.

---

## 17. Levers found in the 2026-10-20/21 gold4 wave

Mined while banking near-miss functions in the gold4 ranges r20/r25/r35. Each item moved at least one function to byte-exact. Items §1–16 or `matching.md` already cover are left out.

**Scheduling and barriers**
- **Place `_ReadWriteBarrier()` (`<intrin.h>`) between a scheduling-critical store and the hoisted load/store it must precede.** cl's scheduler hoists a load above an earlier store (or sinks a store) when it sees no dependence; the barrier is a compiler fence that emits no code and pins the order. This one lever banked 007997f0, 00f139f0, 008d20c0 and 00b95e90 and shrank 00ec21c0 to a 6-byte diff; it also pins a load after earlier stores (0x7cde80, 15 diff bytes to 0). When cl still CSEs the reload, read the field through a `volatile` access at the one site — but keep `volatile` local, because a `volatile` access anywhere disables stack-slot sharing for the whole function (§15).
- **Condition polarity is a lever in clamp/compare idioms**, not just x87 NaN masks. `return (r >= amount) ? 1 : 0;` gives `xor ecx,ecx; setge cl; mov al,cl`, where `>` gives `setg`; `if (x <= lo) x = lo;` and `if (x < lo) x = lo;` select opposite `comiss`/branch polarity. Read the original's `setcc`/`jcc` polarity off the asm and mirror it in the source relational, and keep the result in a named `bool` — returning the comparison directly can fold the `setcc` into a `test`/`sbb` normalize (§16 "Return types"). One known ceiling: a `jb` vs `jbe` clamp difference on 00ec21c0 could not be forced even with the barrier, so record it and move on.

**Call and dispatch shape**
- **Keep a virtual call a single expression — the bare inline cast and a typed vcall are both exact; an intermediate local or helper is not.** The original's `mov eax,[this]; mov edx,[eax+N]; mov ecx,this; call edx` is one expression's worth of IL. `((void(__thiscall*)(void*,int))((void**)*(void***)self)[N/4])(self,arg)` and a typed call `((Iface*)self)->Method(arg)` both hold the callee in `edx` and match byte-for-byte (00b8fb70: 0 diff) — *the type need not be the real domain class*; codegen depends only on single-expression + slot index, so a declaration-only placeholder `Iface` with the right number of preceding virtuals works. That makes `((Iface*)self)->Method(arg)` a *readable scaffold*, not idiomatic C++: real idiom only arrives once `Iface` is the reconstructed domain class with real method names/return types. Prefer it only where the slot is shallow enough to be worth naming; for a deep slot the cast is the more honest spelling. **Look up the real names first** — `work/decomp_all/index_*.csv` maps VA→demangled symbol and the Ghidra decompile (`work/decomp_all/c/*.c`) types the call, so you often *can* rebuild the real hierarchy: `00b8fb70` is `Simulator::cSpaceInventoryItem::IsAvailableInCurrentPlanet`, whose slot-6 virtual is `GetItemID()` returning a `ResourceKey*` (`this+0x5c`); declaring `DefaultRefCounted` + `cSpaceInventoryItem` (with `GetType`/`SetItemID`/`GetItemID`) makes it genuinely idiomatic and still byte-exact (0 diff). Naming the pointer first — `void*(__thiscall*fn)(void*)=…; fn(self);` — moves the callee to `eax` (2 diff bytes, 00b8fb70), and a helper that returns the pointer spills it (§15): the local's live range changes the callee register. For a call on a known `this`, the first load collapses: `((void**)*(void***)this)[N/4]`.
- A declared-symbol direct call (`extern "C" void f();`) keeps the `call rel32` shape; holding the address in a function pointer gives `mov reg,imm; call reg`, five bytes longer (§16).
- A `switch` whose case bodies are outlined after the `ret` reproduces that layout, and the **case order in source controls the block order and jump-table order** — sort the source cases into the original's address order, not ascending value order (§16 "Statement shape").

**Loops**
- A rotated/do-first loop (`do { body; } while (cond);`) reproduces a loop whose test is at the bottom where a `while`/`for` gave a different block order; keep the induction update in the same position the asm shows (§3).

## Appendix: where to look

| Need | Tool / doc |
|---|---|
| Which compiler built this VA | `symbols/components.json`, `matching.md` "Toolchain provenance", `/vc71` smell tests §1 |
| Annotated disasm + decompile | `tools/matching/card.py <va>` |
| Compile + rank variants for a slice | `tools/matching/chk.py`, `try_variants.py` |
| Instruction-level diff | `tools/matching/cmpdis.py` (use exact mangled name) |
| Byte diff, relocations masked | `tools/matching/cmpobj.py` |
| `/Od` local slot order | `tools/matching/od_names.py fit K` |
| Behaviour equivalence | `tools/difftest/equiv.py`, `docs/equivalence.md` |
| x87 / SSE / precision | `docs/floating_point.md` |
| LTCG ranges | `symbols/renderware4_core.txt` |
| Havok classes/names | `match/include/havok31/`, `symbols/havok_names.txt` |
| EASTL reference | `work/ext/Spore-ModAPI/EASTL-3.02.01` |
| Friction log | `docs/Papercuts.md` |
