# Byte-exact matching (stage 2)

## Toolchain
- `tools/matching/cl.sh` runs **cl 15.00.30729.01 (VS2008 SP1, x86)** under wine, taken from
  Microsoft's `VCForPython27.msi` (SHA-1 `7800d037ba962f288f9b952001106d35ef57befe`, verified)
  and kept in `work/toolchain/` (git-ignored; never commit Microsoft binaries).
- RTM vs SP1 is still open. The Rich header was destroyed by SteamStub, and the manifest's
  9.0.21022.8 CRT binding is SP1's default too. So far every function matches with SP1.
  If residual mismatches appear, test them with a VS2008 RTM cl (15.00.21022.08).

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
- `.venv/bin/python tools/matching/try_variants.py <scratch.cpp> <va>`: rank candidate spellings
  (use `work/match/scratch_<id>_N.cpp` files; every function symbol in the file is compared)
- `.venv/bin/python tools/matching/cmpobj.py work/SporeApp.analysis.bin <obj> <symbol> <va>`
- `.venv/bin/python tools/matching/run_all.py --manifest match/slices/<id>/manifest.txt` (final check)

Writing matchable source:
- Default flags `/O2 /MD /Gy /EHsc /TP`; include `types.h` from match/include for fixed-width types.
- Calling conventions are visible in the epilogue: `ret N` with ECX used as `this` = `__thiscall`
  member (declare a local stub class with fields at the right offsets, `char pad[N]` gaps);
  `ret N` without ECX = `__stdcall`; ECX+EDX args = `__fastcall`; plain `ret` = `__cdecl`.
- Callees, globals and vtable targets are masked relocations, so any declaration with the right
  calling convention and argument types works. Virtual calls need a stub class with the vtable
  slot at the right index (pad with placeholder virtuals).
- Prefer the levers listed above: intrinsics, explicit `return true/false`, loop shapes,
  `while (n--)`, field types (`bool` vs `int`), signedness (`movsx`/`movzx`, `sar`/`shr`, `jl`/`jb`),
  and evaluation order of conditions.
- Budget your effort: up to ~6 variant rounds per function. If it won't match, keep the best
  behaviorally-correct version (it must compile) and list it in nonmatching.txt.

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
