# Byte-exact matching (stage 2)

> **See also [`codegen.md`](codegen.md)** — the mechanism guide ("why does the
> compiler emit this shape?"), organised by mechanism and partitioned across the
> three toolchains this binary was built with (VS2008 cl 15.00, VC .NET 2003
> cl 13.10, and RW4 core with `/GL`+`/LTCG`). This file is the procedure and
> accumulated rules; `codegen.md` is the mechanism reference to read **before** you
> iterate — skim it in setup, then open it the moment the first diff appears, not
> after a few failed rounds.

## Toolchain
- `tools/matching/cl.sh` runs **cl 15.00.30729.01 (VS2008 SP1, x86)** under wine, taken from
  Microsoft's `VCForPython27.msi` (SHA-1 `7800d037ba962f288f9b952001106d35ef57befe`, verified)
  and kept in `work/toolchain/` (git-ignored; never commit Microsoft binaries).
- RTM vs SP1 is still open. The Rich header was destroyed by SteamStub, and the manifest's
  9.0.21022.8 CRT binding is SP1's default too. So far every function matches with SP1.
  If residual mismatches appear, test them with a VS2008 RTM cl (15.00.21022.08).

### Toolchain provenance — what built which code
The exe links several prebuilt middleware libraries, each built by its own compiler. This is the
single most important thing to know before chasing a near-miss: a few bytes off is often the
*compiler*, not the source.

| Code | Compiler | How we compile it |
|---|---|---|
| Spore game code + EA framework (UTFSpore) | VS2008 SP1, cl 15.00.30729.01 | default (`cl.sh`) |
| **Havok 3.1.0** (all 469 objects) | **VC .NET 2003, cl 13.10.3077** | `/vc71` (we match with 13.10.3052) |
| **RenderWare 4 core libraries** | **VC .NET 2003, cl 13.10** | `/vc71` |
| Other code inside the RenderWare address range (NegateRows, LpcSynthesize, …) | VS2008 SP1 | default |
| RenderWare 4 core **additionally** | **/GL + /LTCG** (link-time codegen) | not reproducible single-object |

Evidence and rules of thumb are below.

- **Havok was built with VC .NET 2003, not VS2008.** The dev PDB's S_COMPILE records give
  cl 13.10.3077 for all 469 Havok objects. Integer code often matches with VS2008, but x87 code
  never does (instruction selection differs, e.g. `fld st(i); fmul [m]` vs `fld [m]; fmul st(i)`).
  Add the pseudo-flag **`/vc71`** to a manifest line's flags (or `chk.py --flags`) and `cl.sh`
  hands the compile to `tools/matching/cl71.sh`: cl **13.10.3052** from the Visual C++ Toolkit
  2003 (`VCToolkitSetup.exe`, SHA-1 `956c81c3106b97042c4126b23c81885c4b5211f4`; bin/include/lib
  extracted from its embedded MSI without running the installer into `work/toolchain/vc71tk/`).
  3052 is a slightly earlier build than 3077; so far it has matched. VC7.1 has no `/fp:` switch
  (it warns and ignores it); its default is what Havok used.
- **RenderWare 4's core libraries are VC .NET 2003 too** (rw_HashString, Shader, Device/D3D9
  adapter code, ArenaManager): those match only with `/vc71`. Code elsewhere in the RenderWare
  address range (e.g. NegateRows, LpcSynthesize) and the EA framework (UTFSpore: 751 functions
  exact with VS2008 vs 82 with 7.1) are VS2008. When a function in a prebuilt library is
  complete but a few bytes off (`dec [m]` vs `sub [m],1`, x87 operand order), try `/vc71`.
- **RenderWare 4's core was also built with link-time code generation (`/GL` + `/LTCG`).**
  With `/GL` the compiler emits a low-level intermediate form and defers real codegen to
  `link.exe /LTCG`, which then sees *every* callee's body and optimises across call boundaries:
  it keeps a value in a register it can prove the callee does not touch, inlines across TUs, and
  allocates registers globally. Evidence: `Raster::Initialize` (0x011efeb0) sets `edx = 0`, calls
  `FormatGetDepth`, and keeps using `edx == 0` afterwards — legal only when the compiler knows
  `FormatGetDepth` leaves `edx` alone. We reproduced it by compiling that one function with `/GL`
  and linking with the 2003 `link.exe /LTCG`.
  Consequence: a **single-object compile cannot match these functions byte-for-byte**, because its
  register choices are made without the callees; matching would require every callee in the call
  tree compiled faithfully and linked as one unit. Record such functions as complete
  (equivalence-checked) instead of chasing bytes — *except* leaf functions that make no calls,
  where /LTCG has nothing to cross-optimise and they can still match. Havok shows no sign of LTCG
  (its functions match single-object once the compiler version is right). `equiv.py` reports
  register-only leftovers here, and ABI mismatches like a clobbered `ebx`.
  **Policy: RenderWare 4 core is equivalence-only until the whole binary has compilable source** —
  do not chase byte-exactness for its callers; record them as complete + equivalence-checked
  (`symbols/renderware4_core.txt` lists the ranges). Leaf functions may still match.

## Workflow
1. `tools/matching/disasm.py work/SporeApp.analysis.bin <va>` prints the original instructions.
2. Write candidate spellings into a scratch file, then run
   `tools/matching/try_variants.py <scratch.cpp> <va>`, which ranks every function by diff bytes.
3. Move the winner into `match/<subsystem>/*.cpp`, add it to `match/manifest.txt`, and run
   `tools/matching/run_all.py`. That recompiles and re-verifies the whole set, so it stays green.
4. `tools/matching/cmpobj.py` is the verifier. It masks relocations on our side (COFF
   DIR32/REL32/...) and on the original's side (.reloc absolute addresses).

## Recovered build settings (evidence-based, per module)
| Setting | Evidence |
|---|---|
| `/O2` with frame-pointer omission | `/Oy-` breaks every match so far; `/O1` and `/Os` diverge |
| `/MD` (dynamic CRT) | CRT calls go through the IAT (`mov ebp,[__imp_towlower]; call ebp`) |
| C++ (`/TP`), `/EHsc` | mangled class methods, EH tables elsewhere |
| Mixed optimization | some modules look `/Od` (e.g. hash table near 0x0050E850): to verify |

## Codegen levers learned on this binary
- **Byte swaps use the intrinsics** `_byteswap_ushort` / `_byteswap_ulong`. A shift/or swap
  becomes `rol`, and a byte-wise memory swap spills to the stack.
- **`return true;` / `return false;`** yield `mov al,1` / `xor al,al`. Returning a comparison
  yields full-width `mov eax,1` / `xor eax,eax`.
- **Loop shape matters.** `while (n--) h = f(*s++);` matched; `for (; n; --n)` did not
  (register assignment and `dec`/`sub` choice differ).
- 16-bit ops with constants preloaded into registers come from intrinsic results being
  compared as `unsigned short`.

## Tally
`run_all.py` prints it. Currently **4 / 4 attempted byte-exact**, out of ~96,420 functions.

## Agent playbook (fan-out slices)
**Papercuts:** before finishing, append any real friction you hit (tooling bugs, unclear docs, tricks you had
to rediscover) to `docs/Papercuts.md`, following the instructions at the top of that file. Read its Open
section first. It may already have the answer to something you're stuck on.

**Codegen reference:** read `docs/codegen.md` during setup (skim it) and return to it the **first** time a
slice shows a diff — not after N failed rounds. It is organised by the *kind* of difference (loop shape,
register choice, frame offsets, x87 order, block layout, ABI) and tagged by the toolchain that built each
address — `[15]` VS2008 cl 15.00, `[13]` VC .NET 2003 cl 13.10, `[LTCG]`, `[DDK]`. Classify the diff, apply
the matching lever, and only then decide a function is unmatchable. It is the companion to this file and the
successor to the "Batch-2 lessons" list below.

Each slice `sXXXXXXXX` is a contiguous run of functions. All output goes in:
- `match/slices/<id>/<id>.cpp` (plus optional `<id>.h`): source for **every** function in the slice.
- `match/slices/<id>/manifest.txt`: one line per **byte-exact** function:
  `slices/<id>/<id>.cpp  <symbol-substring>  <va>  [flags override]`
- `match/slices/<id>/nonmatching.txt`: `<va>  <diff-bytes>  <short reason>` for functions written
  as COMPLETE behaviorally-equivalent source (every path and call of the original) that is not byte-exact (yet).
- `match/slices/<id>/partial.txt`: same format, for anything incomplete or approximate (stubbed blocks,
  skeletons, omitted paths). Partial source is not counted as decompiled, so never list it in nonmatching.txt.
- `symbols/slices/<id>.txt`: `<va> <Name>  # evidence` for names you are confident in.
Never edit shared files (match/include, tools, docs, other slices), and never run git or Ghidra.

Tools (from repo root):
- `.venv/bin/python tools/matching/card.py <va> [...]`: annotated disassembly + Ghidra decompile
- `.venv/bin/python tools/matching/chk.py <file.cpp> <slice-id | va,va,...> --flags "<cl flags>" [-a]`: ONE
  compile, diff count for every VA of the slice (no global lock; use this to iterate, and
  run_all.py --manifest only for the final check). Each line is `<va> <original size> <diff bytes> <how>
  <symbol>`: the symbol is the VA's manifest row (`manif`), else the definition after its `// @ 0x<va>`
  marker (`marker`), else the nearest size (`~size`, unreliable). `other` means a byte-identical symbol of
  another name, which the manifest row must then name. `(size N vs M)` is your function's size against
  the original's. For each MATCH not yet in manifest.txt it prints the finished manifest row, flags
  included (run_all.py reads flags per row, not from chk's `--flags`): copy it as printed. Put scratch files only under `work/match/scratch_<id>_*`
  (the session scratchpad is shared between concurrent agents and gets clobbered).
- `.venv/bin/python tools/matching/try_variants.py <scratch.cpp> <va>`: rank candidate spellings
  (use `work/match/scratch_<id>_N.cpp` files; every function symbol in the file is compared)
- `.venv/bin/python tools/matching/cmpobj.py work/SporeApp.analysis.bin <obj> <symbol> <va>`
- `.venv/bin/python tools/matching/run_all.py --manifest match/slices/<id>/manifest.txt` (final check)
- `.venv/bin/python tools/pdb_type.py <ClassName> [--exact]`: the class/struct/enum layout from the 2008
  dev-build PDB as a C++ declaration with byte offsets (real member names!). Retail may differ in a few
  fields, so confirm offsets against the disassembly. Many retail functions now carry real names from that
  PDB (see docs/xmatch.md); the card shows them. Use these real names for classes, methods and members.
- Spore ModAPI headers (community reverse engineering of the 2017 Steam build, much closer to retail than the
  2008 PDB, and covering Galactic Adventures): `rg --no-ignore -n "<Class or method>" "work/ext/Spore-ModAPI/Spore ModAPI/Spore"` (use rg, not grep, for all searches).
  Class names differ from the PDB's (ModAPI `Simulator::cCreatureBase` = PDB `SP::cSPCreatureBase`), but
  member names, virtual method order and enums are a good reference. Its addresses are for the 2017 build, NOT ours.
- `.venv/bin/python tools/matching/od_names.py fit K`: local-variable slot order for /Od functions (below).
- **Before writing source:** run an ordered call-target / vtable-slot / constant diff against the original (map the
  object's COFF relocations onto the original's call targets) as a cheap completeness check, and read the
  neighbouring slice of the same class/subsystem first — it usually already has the real layouts, vtable slots and
  inline helpers. The raw dev PDB (`work/devbuild/SporeBin/SporeApp.pdb`) `S_BPREL32`/`S_REGREL32` records give real
  /Od local/param names. See "Re-mined levers" below.

Writing matchable source:
- Default flags `/O2 /MD /Gy /EHsc /TP`; include `types.h` from match/include for fixed-width types.
- Calling conventions are visible in the epilogue: `ret N` with ECX used as `this` = `__thiscall`
  member (declare a local stub class with fields at the right offsets, `char pad[N]` gaps);
  `ret N` without ECX = `__stdcall`; ECX+EDX args = `__fastcall`; plain `ret` = `__cdecl`.
- **Name every field you touch; no raw-offset casts** (2026-10-23). Declare the members you read or write at their
  offsets in the class (gaps as `uint32_t padN[...]`) and access them by name: `herd->mpLeader->mFlags &= ~0x400000`,
  never `*(u32*)((char*)(*(void**)((char*)p + 0xb4c)) + 0x5fc) &= 0xffbfffff`. Same bytes, but the cast chain hides
  what the code does and every one has to be rewritten when the slice migrates onto canonical headers. Take the name
  from `tools/pdb_type.py <Class> --exact` only when the dev PDB's member at that offset has the same type as the
  retail use (retail layouts are often shifted: gold6's `cHerd` +0x164 is a refcounted creature pointer in retail but
  the enum `mCreaturePersonality` in the dev PDB); otherwise name it by role and offset (`mpLeader_164`). A pointer
  you only pass through may stay `void*`; a pointer you dereference gets a type. `tools/matching/rawcasts.py`
  counts the casts, and `commit_slice.sh` reports the count.
- **Every callee needs the right calling convention, not just the right address.** Callees, globals
  and vtable targets are masked relocations, so the byte diff does not check where a call goes. It also
  barely notices a wrong convention, so a wrong declaration can look nearly matching. The most common
  bug found by the equivalence checker (docs/equivalence.md) is a **thiscall method declared as a free
  `cdecl`/`stdcall` function**: `this` is never passed in ECX, the callee runs on garbage, and the
  stack is cleaned up wrongly. Before you record a function as complete, check every direct callee
  at its call site in the original:
  - `mov ecx, ...` / `lea ecx, ...` right before the call (and ECX not otherwise an argument) means
    the callee is a **thiscall member**. Declare it as a member of a stub class (`__thiscall` is
    rejected on free functions) and call it as `obj->Method(...)`. Pushed arguments go in the
    member's parameter list; the callee's `ret N` gives their total size (`.venv/bin/python
    tools/matching/disasm.py work/SporeApp.analysis.bin <callee-va>`).
  - No `add esp, N` after the call means the callee pops its arguments (`ret N`): thiscall or
    stdcall. A free cdecl declaration is wrong there.
  - Also compare return types: if the original never writes EAX before `ret`, the function is
    `void`, even when a caller-side convention made `bool` look plausible.
  Run `.venv/bin/python tools/difftest/equiv.py <slice> <va>` on functions you record in
  nonmatching.txt. A FAIL on `esp`, on a call trace, or "original reads ecx at entry" almost always
  means one of these declarations is wrong.
- Virtual calls need a stub class with the vtable slot at the right index (pad with placeholder
  virtuals). Reference-counted objects (`AddRef`/`Release`, `AutoRefCount<T>`/`intrusive_ptr`):
  copying a smart pointer calls `AddRef`. A raw-pointer store where the original copies an
  `AutoRefCount` drops a reference, and the byte diff will not catch it.
- Prefer the levers listed above: intrinsics, explicit `return true/false`, loop shapes,
  `while (n--)`, field types (`bool` vs `int`), signedness (`movsx`/`movzx`, `sar`/`shr`, `jl`/`jb`),
  and evaluation order of conditions.
- Budget your effort: up to ~6 variant rounds per function. If it won't match, keep the best
  behaviorally-correct version (it must compile) and list it in nonmatching.txt.

**No assembly transcription.** A function written as `__declspec(naked)` + `__asm`, with `_emit` bytes, or
generated from the disassembly by a script is not decompiled and never counts as byte-exact; record it in
partial.txt. Only a few `__asm` statements inside C++ where the original used an asm helper (fnstcw/fldcw,
cvtss2si, the maxss/minss clamp) are allowed: a block of at most 8 instructions. `run_all.py` enforces this (since
2026-10-18): a naked, `_emit` or longer-block row prints `ASM` instead of MATCH and does not count.
`tools/matching/asm_audit.py --all-rows` lists offending manifest and nonmatching rows; `--review` adds bodies with
many helper-sized blocks, for a human look. The 2026-10-18 audit moved 12 claimed rows (9 byte-exact) to partial.txt.

**Atomics are semantics, not shape.** Where the original has `lock xadd`, `lock cmpxchg`, `lock inc/dec` or
`xchg mem,reg`, write the `_Interlocked*` intrinsic (`_InterlockedExchangeAdd`, `_InterlockedCompareExchange`,
`_InterlockedExchange`, ...), never `++*(volatile long*)p`. The equivalence harness is single-threaded and
passes the plain version; the game then races on refcounts and crashes nondeterministically (found with the
hybrid build, 2026-10-11). `tools/hybrid/build.py` refuses to hook a function whose locked-instruction count
differs from the original.

**Annotate template helpers by address.** `eastl::lower_bound`, `find`, `sort`, hash and copy helpers exist
once per element type; a bare qualified name in a declaration is ambiguous, and the resolver once sent a
`GetProperty` to another `lower_bound` instantiation (hybrid crash, 2026-10-11). Put the callee's address
from the call site on the declaration (`// 0x00612db0`) as for any other callee; the resolver now rejects a
name-only match that the original function does not actually call.

**Declare the return the original has, not the one the signature suggests.** If the original writes eax
right before every `ret` (a hidden return pointer handed back, `return this`, the popped node, the copy's
end pointer), the function returns that value and LTCG callers use it, whatever the dev PDB or the pseudocode
says. Seven hybrid defects were `void` declarations of such functions (2026-10-12). The harness now compares
eax in that case (`void_hides_eax` in the result, "declared void but the original writes eax" in the notes):
return the value. The static rule (`returns_eax` in `tools/difftest/regfacts.py`, shared with
`tools/hybrid/build.py`) also flags a **call-free** function whose *first* eax write is a load
(`mov eax, dword ptr [ … ]`) or `mov eax, ecx`, with nothing rewriting eax before the ret — a pop-front, a
`lower_bound`, a copy's end pointer, an init returning `this` (`ArenaSelf::initRange` 0x011e29c0,
`LowerBoundPair` 0x007c8160, `rbtree::find` 0x00e5c780, rw pop-front 0x01141200). If a walk back from `ret`
hits a `call` first, there is no return value. Mechanism and the full instance table: `codegen.md` §11.3.

**`ret N` is the argument cleanup, not a detail.** A `ret 4` original declared `ret` (or the reverse)
shifts every caller's `esp` by 4. `equiv.py` records the original's `callee_pop`/`pop_variants`; the `esp`
observable fails. (A merged extent with two ret forms, e.g. `ret 12`/`ret 20`, is a split, not one ABI.)
The register-footprint rule is the paragraph below.

**Virtual and callback arguments in the original's push order.** The arguments of a call through a vtable
or a function pointer are now compared (`fake call #k arg i` / `fake call #k this`). Read the pushes at the
call site: the last push is the first argument, `ecx` at the call is `this` — not "register allocation".
`cViewer::SetRaster` passed `(&rect, a, b)` for `(a, b, &rect)` (no galaxy), `FUN_00753fc0` called vtable
slot 0 with no `this` (crash), `SharedRelease` passed the vptr value as `this` (crash): all PASSed before.

**Do not write a register the original never writes.** An LTCG caller may keep a live value in a register
its callee is known not to touch (per call site). `InterpRamp` 0x114e780 wrote xmm3 where the original uses
xmm0-2 and xmm7: crackling audio, no crash. The harness now reports `xmm3 (untouched by the original)` and
`tools/hybrid/build.py` refuses such hooks (169 of 1,730 PASS functions). The compiler owns register
allocation, so the fixes are indirect: fewer live temporaries (recompute instead of caching), the original's
expression order, `/arch:SSE` vs x87 as the original, or declaring the function as needing an asm shim
(record `custom register ABI` in the row). The register sets are in the result (`orig_untouched_regs`).

### Lessons from the pilot (12 agents)
- **Module flags vary**; check the disassembly first:
  - `/Od /Ob1`: `push ebp; mov ebp,esp`, ecx spilled to `[ebp-N]`, every local in memory, but small
    helpers still inlined (EASTL containers). Local *names* can reorder `/Od` stack slots.
  - `/arch:SSE` or `/arch:SSE2`: scalar `movss`/`xorps` for float copies, x87 still used for float
    args/returns. Float arithmetic in `ucomiss`/`subss` without `cvtps2pd` needs `/arch:SSE /fp:fast`.
  - `/GS-`: an old-style EH prolog (`push -1; push handler; mov eax,fs:[0]`) without a cookie xor.
  - A manifest flags override replaces the **whole** list; write it out in full,
    e.g. `/O2 /MD /Gy /EHsc /TP /arch:SSE2`.
- Some regions look like a **different toolset** (VC8 / prebuilt libs): memory-indirect
  `call [reg+N]`, `mov dl,[m]; test dl,dl`, non-dllimport CRT. Check one call site before investing.
- `char pad[]` in a stack local triggers `/GS` cookies; use `uint32_t pad[]` in stub structs.
- For functions with EH, put the **exact mangled name** in the manifest (substrings also hit
  `__ehhandler$` / `__unwindfunclet$`). Declaring a dealloc helper `throw()` removes extra EH stores.
- EASTL: strings are 16 bytes (incl. a 4-byte allocator); tag args are derived empty structs passed
  as `const T&`; `clear()` must go through an inline `erase(first,last)` to get the right schedule.
- IAT calls in naked asm: `call dword ptr [g_imp]` against an `extern void*`.
- `tools/matching/cmpdis.py <obj> <symbol> <va>`: instruction-level diff (beats byte counts for
  frame-offset and scheduling puzzles). Under load, wine compiles are slow: batch variants per run.
- Under zsh a flags string in a variable is one argument unless written `${=var}`.
- Scratch files must have unique names (`work/match/scratch_<slice>_*`); never use shared tmp paths.

### Static ResourceKey initializers (8,374 functions, pattern `xor eax,eax; mov [g],imm; mov [g+4],eax; mov [g+8],eax`)
The immediate is an FNV hash of a resource name: `0x4133FE05` = "interplanetarydrive"
(`tools/hashnames.py`, 7,031/8,374 named into `symbols/key_globals.txt`). So the source was something like
`ResourceKey kX(id("InterplanetaryDrive"), 0, 0)`: the front end can't evaluate the hash (hence a runtime
initializer) but the optimizer folds it to an immediate. A plain constant folds to static data under /O2,
and neither a loop hash nor a `__forceinline` recursive hash folds fully in cl 15.00.30729.
Resolution (pattern agent): `tools/matching/synth_templates/key_init_store3.py` matches all 8,374 instances
with a plain function doing the three stores. This is **shape-equivalent**, not the original syntax: the
original is a compiler-generated dynamic initializer. Bytes and behavior are identical, but a relinked build
must register these functions in `.CRT$XCU` explicitly. Other initializer templates carry the same caveat
unless their header comment says the real `??__E` form was reproduced.

### Pattern-template lessons (tier 1, 24 templates, 25,407 functions)
- Dynamic initializers `??__E<var>@@YAXXZ`: a file-scope global initialized from an `extern const` defined in
  another TU stays a runtime copy under /O2 (float/vector copies; Vector3 needs a user copy-ctor that copies
  per field, or the implicit copy uses integer regs). Constant-folding kills ctor-with-literal forms.
- Unoptimized modules (`push ebp; mov ebp,esp` frames) use `/Od /Ob1 [/arch:SSE]`; constants load from
  `__real@` and nothing folds, so the real `Vector3 g(1.0f, ...)` form works there.
- MI adjustor thunks `sub ecx,N; jmp`: class D : B0, B1 with B1 at offset N, both declaring virtual f,
  D overriding f (declared only), out-of-line `D::D() {}` to force the vtable; mangled `?f@D@@W<N>AEXXZ`.
- Templates that write `extern` globals named from addresses never collide between instances.
- Use `/GR-` in templates that emit many vtables (fewer COMDATs); cmpobj now reads >32k sections.

### /Od frame layout (from Papercuts; this cost agents 1-3 h each)
- At /Od, a scope's named locals are laid out by a **hash of their names**, not by declaration order.
  Don't hand-search: run `tools/matching/od_names.py fit K` for a scope with K locals. It prints name
  sets measured in a real K-local scope, already in slot order from highest address (ebp-4) down.
  Assign your roles to one line in order. The order depends on K, so always measure at your exact K.
- Unused slots/holes come from unused locals inside inlined helpers: an inlined
  `template<int N> inline void ScratchSlots(){ uint32_t s[N]; }` call reproduces a gap of N dwords.
- Inline-arg temps get slots only for params the callee modifies or takes the address of, or that are
  converted; an inline helper's return value gets a slot only if the helper stores it in a named local.
- Tag args: pass `const Tag&` with a derived empty struct that has a user ctor (`AllocTag(){}`), or cl stores 0.
- `memcpy` is non-dllimport (E8 call), `memmove` is dllimport (call [iat]); `n*4 + (int)memcpy(...)` keeps
  n in esi across the call, while pointer arithmetic doesn't.
- Some /Od modules have no `/EHsc` (with it, `new (p) T(v)` adds a temp slot). A `return true` temp byte before
  dtor calls means RAII locals with inline dtors. An inline member `void Begin(){ p->Begin(); }` gives the
  ecx-first vcall order.

### Havok 3.1.0 references (ranked by authority)
1. `match/include/havok31/hkReflectedClasses.h` (+ `work/havok31_classes.json`): generated by tools/havok_classes.py
   from Spore's OWN Havok reflection tables, so it's exactly 3.1.0: 189 classes with real member names, types,
   offsets and sizes. Only serialized members are listed; gaps are non-reflected fields.
2. `symbols/havok_names.txt`: 1,236 real mangled names (class, method, parameter types).
3. `tools/pdb_type.py <hkClass> --exact`: dev-PDB layouts for Havok types used by Spore code.
4. Havok SDK headers, local only and NEVER committed (proprietary): 6.x (2008) at
   `work/ext/havok6/etc/vendor/havok/Source`, 2013 at `work/ext/havok2013` (its `.inl` files contain inline
   implementations). Both are newer than 3.1: hkX was renamed hkpX, and the 2013 math library was rewritten
   (hkSimdReal), so use them for algorithm shape and naming, never for layouts.

### Batch-2 lessons (100 slices, 1,708 byte-exact; condensed from Papercuts)

**Flags by region (check the card's code shape, then confirm with chk.py):**
- Editor `/Od` region (about 0x484e40-0x4a6660): `/Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast`, with no /EHsc. Many editor modules also need `/GS-`; a `wchar_t buf[64]` with no cookie tells you that.
- `/Od` code with 16-byte-aligned locals (Havok hkVector4, prologue `and esp,-16`) needs `/Oy` added. It doesn't change ordinary frames, so the whole slice can use it.
- UI modules: no `/arch:SSE` (fld/fstp float pushes) and no /EHsc (a string local with a dtor gets no EH frame).
- A float return without fstp/fld rounding needs a per-line `/fp:fast`. One slice can mix modules: use a second .cpp with per-line manifest flags.

**EASTL: write the real EASTL code, not shape hacks.** The template instances (vector::DoInsertValue, rbtree insert/lower_bound/DoNuke, uninitialized_copy/relocate, basic_string append/rfind, hashtable find/bucket_index) match when written as literal EASTL source with EASTL's own local names: extractKey, pCurrent, pRangeEnd, pNodeLeft, bValueLessThanNode, `const size_type nCapacity = (mpCapacity - mpBegin) - 1;`. cl then makes the original's inline/no-inline choices on its own. `work/ext/Spore-ModAPI/EASTL-3.02.01` is a close reference: ModAPI uses it because its layout is compatible with Spore's. The 2008 code differs in details, so verify.
- `template class eastl::map<K,V>;` (explicit instantiation) emits every member at once. If an implicit dtor then goes out of line, add a user `~vector() {}`.
- Explicit specializations of in-class members are never emitted. Emit them through a `#pragma inline_depth(0)` helper that calls them.
- Iterators: rbtree_iterator and hashtable_iterator need their user copy ctors (and hashtable_iterator its base class), or by-value args and sret stores come out wrong. generic_iterator wrappers produce the temp slots in uninitialized_copy and fill.
- Tags: the three `const bool` locals in copy/copy_backward, declared in the order bOutputIsPointer, bInputIsPointer, bHasTrivialCopy. is_integral (false_type) emits no store; true_type() does. A tag with no user ctor gets a stored 0 byte, and one with a user ctor gets nothing.
- `xor r,r; shl r,2` is an inlined `operator[](int)` called with 0. memcpy/memset are direct E8 calls; memmove is dllimport. 0x011e0744 is the memcpy thunk.

**`/Od` frame layout (on top of the section above):**
- Slot order is a hash bucket per name; within a bucket, later-declared names come first. `od_names.py fit` is only a start, because params and inline locals count too. What works: compile many renamed copies of one function in a single object, rank them with chk.py `-a`, and search whole name sets rather than swaps. Same-type pairs often ignore renames, so swap the declaration order instead. For-init loop variables are allocated after the enclosing scope.
- **Holes are the reserved frames of inline callees that cl declined** (called out of line), such as RefCountTemplate::Release, VectorBase dtor, vector::insert, hashtable::find and string operator==. Give those helpers their real inline bodies and the holes appear by themselves; declaring them extern loses the hole. A helper defined out of class without `inline` leaves no hole. Otherwise use `ScratchSlots<N>()` exactly where the call sits. A named unused local gives a hole above the other slots, ScratchSlots one at the bottom. One value type copied at several sites can share a single hole block.
- cl /Ob1 never inlines a function containing `delete this` (Release, removeReference) unless it's `__forceinline` (Havok HK_FORCE_INLINE).
- An inline's param or `this` gets a slot only if it is used more than once or modified. Returned refs, pointers and floats of inline accessors get a slot. A 2-level accessor gives the "slot, then copy into a named local" pattern.
- `p->~T()` always goes through the scalar deleting dtor `??_GT(0)` (`xor ecx,ecx; and ecx,1; je`). A compiler-generated dtor skips the vptr store at entry; `~X(){}` adds it.
- Refcounts: `AddRef(){ return mnRefCount++ + 1; }` and `int n = mnRefCount - 1; mnRefCount = mnRefCount - 1;` (temp, then store). bool to byte is `v ? 1 : 0`.
- An empty POD default-arg temporary (`hash_allocator()`) blocks ctor inlining. Give the class a user ctor `{}`.
- `throw E(fmt, ...)` constructs in place only if E has a user copy ctor. A variadic ctor is __cdecl with `this` pushed.
- A union of two 8-byte structs gives the "64-bit copy twice" pattern (`#pragma pack(4)` if it holds a uint64).

**`/O2` levers (register choice, reloads, ordering):**
- A member loaded into a callee-saved register before a call: copy it to a local at that point in the source. Calls can modify members, so source order pins the load.
- Test-then-reload (`cmp [r],0; je; mov ecx,[r]`) means the member chain is written twice without a local. A kept `lea` means a `T& ref = v[i];` local. Calling a trivial inline accessor instead of the raw member fixes stubborn register swaps.
- Refcount release `mov eax,[ecx+4]; add eax,-1; mov [ecx+4],eax` = `int n = (*(volatile int*)&mnRefCount += -1);`.
- `cond ? A : B` constant args fold to setne or neg/sbb, while the original's per-arm pushes come from `if (c) f(A); else f(B);`. Switch case order and case-body order change the compare tree, so brute-force orderings in one compile. A common tail `push; jmp common` per case is a `__forceinline` helper.
- `return k == 0xd;` emits `xor eax,eax` first, while `if (k == 0xd) return true; return false;` doesn't. A shared final `return false;` keeps ebx saved in the prologue.
- Overloaded virtuals are laid out in REVERSE declaration order. An IHandler::HandleMessage override sees `this` as the IHandler subobject (offsets shifted by -8). Dump vtables straight from the binary before writing stub classes.
- Without /GL, `static` functions get register calling conventions (an arg in eax/edi means a static helper in the same TU): reproducible, keep the helper `static` with a same-TU stand-in caller (codegen.md 6.3). Distinct from the LTCG register ABI (codegen.md 11.4): a function that reads a register at entry no C signature explains, with callers in other objects, is equivalence-only; write the correct version, record it in nonmatching.txt with the register noted, and move on. A function with ecx=this and `ret 4` that uses no members is still a thiscall member.
- Struct copies: a user copy ctor compiles to movss, a user `operator=` to fld/fstp. `T x(...); return x;` (NRVO) and `return T(...)` differ. Try a const copy against a const reference.
- `/arch:SSE` modules use `__asm` float helpers (Floor/CeilToInt with cvtss2si/cmovb, and Min/Max/Clamp with minss/maxss), not `_mm_*`, which forces an aligned frame.
- EA `new("Editor",0,0,0,0) T()` must be a real new-expression against the 6-arg operator new with no matching delete.
- An out-of-line same-TU helper that receives a local's address: give it its real body as a `__declspec(noinline)` specialization, so cl knows it doesn't write the object.
- Parameter types: a float forwarded by `push reg` is an int param. `cvttss2si` vs fistp-qword tells int from unsigned. `(x>>n)&1` (shr; test r,1) is an inline helper, while bitfields give `test byte [m],mask`.

**Tool notes:** anonymous-namespace classes mangle as `?A0x<hash-of-path>`, so give manifests the prefix up to the class name, and quote `?`-symbols in zsh. In cmpdis, relocated zero immediates (`push 0` vs `<addr>`) aren't real diffs.

### Re-mined levers from the subagent lesson corpus (2026-10-13)
From 931 structured `lessons` in the ~2,000 subagent transcripts (see `work/lessons_clusters.txt`) plus 226
`work/match/scratch_*_papercut.md`. Codegen only — harness/tool bugs are in `docs/Papercuts.md` "Open" and ticket
P3. The corpus is a lagging log: several tool bugs it reports are already fixed, so verify before acting on one.

**Inlining & scheduling:**
- Inlining is decided **per call site** and `inline` has a budget: when cl declined a plain `inline` helper,
  `__forceinline` restores it. Model the mix by declaring the out-of-line sites as a declared-only extern and
  adding a separately-named inline copy for the inlined sites. [recurring]
- A `volatile` access anywhere in an /O2 function disables stack-slot sharing for the **whole** function (one
  frame grew 0x48→0x9c). Keep the non-volatile spelling except where the original's shape demands it.
- cl unrolls a counted loop 4× only when the trip count is a local int read once (`const unsigned n = v.size()`);
  reading a member each pass blocks it — don't hand-unroll.
- `_ReadWriteBarrier()` pins a vptr/field store ahead of a later load; swapping two member stores or two `if` arms
  flips /O2 scheduling and can un-tail-merge two virtual calls. Place it **between the scheduling-critical store and
  the hoisted load/store it must precede** — that one placement banked 007997f0, 00f139f0, 008d20c0 and 00b95e90 in
  the gold4 wave (see `codegen.md` §17). A `volatile` access at the single site clears the CSE cl still does, but
  keep it local: a `volatile` access anywhere disables stack-slot sharing for the whole function.

**x87 / floating point:**
- The x87 compare shape follows the source branch **and its NaN polarity**: `if (!(sumR >= dist))` gives
  `fcompi st(1); jb`; `test ah,5; jp` is `(a<b)` and `test ah,0x41; je` is `(a>b)`. `if (!(x >= -r))` avoids a
  canonicalised operand swap.
- Match the literal's **type**, not its value: `1.0 - x` (double) → `fld1; fsubrp`, `1.0f - x` → `fld1; fsub`.
- To get an inline `fsqrt`/`fpatan` without changing slice flags, scope `#pragma float_control(precise, off)` to
  the one function and call `(float)sqrt((double)x)` / `atan2((double)y,(double)x)`.
- `(float)(uint32_t)x` lowers to `fild` + a conditional `fadd 2^32` — the Ghidra `if (x<0) f += 4.29e9` lines are
  unsigned casts, not hand-written source.
- `_mm_cvtsd_si32(_mm_set_sd(x))` reproduces x87 `fistp dword`, including the 0x80000000 overflow clamp; the
  single-precision intrinsic does not.

**Instruction selection:**
- Condition **polarity in a clamp/compare is a lever** as much as the x87 NaN mask: `(r >= amount) ? 1 : 0` gives
  `setge` where `>` gives `setg`, and `if (x <= lo) x = lo` vs `if (x < lo) x = lo` pick opposite `comiss`/branch
  polarity. Read the original's `setcc`/`jcc` and mirror the relational; keep the result in a named `bool`, or the
  `setcc` folds into a `test`/`sbb` normalize (gold4; `codegen.md` §17).
- A virtual call must stay **one expression**. The bare inline cast
  `((void(__thiscall*)(void*,int))((void**)*(void***)self)[N/4])(self,arg)` and a typed call
  `((Iface*)self)->Method(arg)` are both byte-exact; naming the pointer first
  (`void*(__thiscall*fn)(void*)=…; fn(self);`) moves the callee from `edx` to `eax` (2 diff bytes, 00b8fb70).
  The type can be a **declaration-only placeholder** (only single-expression + slot index matter) — the typed form is a
  readable scaffold, not idiomatic C++; reach for it when the slot is shallow, else spell the cast.

**Layouts & padding:**
- Retail layouts drift from the 2008 dev PDB — read sizes off stack-slot spacing: `SP::cString` 0x14 (not 0x1c),
  `eastl::vector` with `sp_vector_allocator` 0x14, `fixed_vector` buffer at +0x18, `cMDSection` 0x8c. cSPUI's PDB
  class is uniformly +0x10 off; don't trust it.
- A class with `uint64` members gets padding after the vfptr unless `#pragma pack(4)` (which shifts every field by
  4); an empty member struct occupies 1 byte. Diff the set of non-stack `[reg+N]` offsets original-vs-ours.
- A vtable class with 16-byte-aligned members gives the vfptr its own 16-byte block — declare `uint32_t pad[4]` as
  the header. `char raw[N]`/`char pad[N]` stub members force a /GS cookie; use `uint32_t raw[N/4]`.
- A method whose `this` is a secondary base (`lea esi,[ebp-4]` / `add esi,-N` before owner calls) should be an
  ordinary member of the full class via **real multiple inheritance** — cl then reproduces the subobject `this`
  and the shifted offsets itself.

**/Od:**
- At /Od, `T v = a + b;` with the same type elides the copy; a `movss` copy through a parameter slot means a
  converting ctor from the operator's return type, and a by-reference `SetOffset(const Vector3P&)` argument copies
  with integer moves.
- /Od switch layout follows source order and merges case labels that share the default body (`case 0: case 1:
  default:` emits `sub 2` and a smaller table); write `case 0: ; case 1: ; default:` to keep the table based at 0.

**Durable codegen gotchas (a tool fix cannot clear these):**
- An explicit `void* vftable` member doubles the implicit vptr (a duplicate store at +0x0).
- `*(T*)(p+off)` with `p == 0` folds to an absolute `mov X,[off]` **even through `volatile`** — no null check
  survives.
- Adding a member with a destructor turns a byte-exact ctor into a full EH frame (217→277 B); keep nontrivial
  members out of a matched ctor.
- Signed `A<char>` vs `A<uint8_t>` flips `movzx`/`movsx` at every element access — template tag signedness must
  match.
- A constant-size `_alloca(8)` forces a drift-immune frame when matching a callee-pop `esp` mismatch.
- A register-ABI LTCG callee can be transcribed under a unique name with **no** `// 0x` marker and still
  link/match.

**Techniques worth reusing:**
- Fastest completeness check: an ordered call-target / vtable-slot / float-constant diff mapping the object's COFF
  relocations onto the original's call targets — run it before any byte work. Normalise cmpdis's relocated
  operands first.
- Rank candidate spellings by instruction-level diff **ignoring jumps/calls/relocated immediates**, not raw byte
  counts; keep many renamed copies in one namespace-wrapped file and score them in a single compile.
- The dev PDB's `S_BPREL32`/`S_REGREL32` records give real local/param names — fixes /Od hash-ordered frames
  directly.
- Vendored source exists for some subsystems (`work/ext/EAWebKitSupportPackages` for EAText): writing it verbatim
  with `#define mX RF(T,off)` matched byte-exact. Shim leaf differences with inline defs placed **before** the
  dependent include.
- Check the neighbouring slice before reconstructing anything — across the corpus it repeatedly carried the real
  layouts, vtable slots and inline helpers, converting hours of work into a first-compile match. Highest-leverage
  habit found.
