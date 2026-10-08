# Byte-exact matching (stage 2)

## Toolchain
- `tools/matching/cl.sh` runs **cl 15.00.30729.01 (VS2008 SP1, x86)** under wine, taken from
  Microsoft's `VCForPython27.msi` (SHA-1 `7800d037ba962f288f9b952001106d35ef57befe`, verified)
  and kept in `work/toolchain/` (git-ignored; never commit Microsoft binaries).
- RTM vs SP1 is still open. The Rich header was destroyed by SteamStub, and the manifest's
  9.0.21022.8 CRT binding is SP1's default too. So far every function matches with SP1.
  If residual mismatches appear, test them with a VS2008 RTM cl (15.00.21022.08).
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
  Evidence: `Raster::Initialize` (0x011efeb0) keeps `edx = 0` live across a call to
  `FormatGetDepth`, which is only legal when the compiler knows the callee leaves `edx` alone.
  A `/GL` compile linked with the 2003 `link.exe /LTCG` reproduces that, but register choices
  then depend on the callees' real bodies, so a single-object compile cannot match these
  functions byte for byte. Record them as complete (equivalence-checked) unless a function
  makes no calls. Havok shows no sign of LTCG.

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
- `.venv/bin/python tools/matching/chk.py <file.cpp> <slice-id | va,va,...> --flags "<cl flags>" [-a]`: ONE
  compile, best symbol + diff count for every VA of the slice (no global lock; use this to iterate, and
  run_all.py --manifest only for the final check). Put scratch files only under `work/match/scratch_<id>_*`
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

Writing matchable source:
- Default flags `/O2 /MD /Gy /EHsc /TP`; include `types.h` from match/include for fixed-width types.
- Calling conventions are visible in the epilogue: `ret N` with ECX used as `this` = `__thiscall`
  member (declare a local stub class with fields at the right offsets, `char pad[N]` gaps);
  `ret N` without ECX = `__stdcall`; ECX+EDX args = `__fastcall`; plain `ret` = `__cdecl`.
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
cvtss2si) are allowed. `tools/matching/asm_audit.py` lists offending manifest entries; run it before integrating.

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
- Without /GL, `static` functions get register calling conventions (an arg in eax/edi means a static helper in the same TU). A function with ecx=this and `ret 4` that uses no members is still a thiscall member.
- Struct copies: a user copy ctor compiles to movss, a user `operator=` to fld/fstp. `T x(...); return x;` (NRVO) and `return T(...)` differ. Try a const copy against a const reference.
- `/arch:SSE` modules use `__asm` float helpers (Floor/CeilToInt with cvtss2si/cmovb, and Min/Max/Clamp with minss/maxss), not `_mm_*`, which forces an aligned frame.
- EA `new("Editor",0,0,0,0) T()` must be a real new-expression against the 6-arg operator new with no matching delete.
- An out-of-line same-TU helper that receives a local's address: give it its real body as a `__declspec(noinline)` specialization, so cl knows it doesn't write the object.
- Parameter types: a float forwarded by `push reg` is an int param. `cvttss2si` vs fistp-qword tells int from unsigned. `(x>>n)&1` (shr; test r,1) is an inline helper, while bitfields give `test byte [m],mask`.

**Tool notes:** anonymous-namespace classes mangle as `?A0x<hash-of-path>`, so give manifests the prefix up to the class name, and quote `?`-symbols in zsh. In cmpdis, relocated zero immediates (`push 0` vs `<addr>`) aren't real diffs.
