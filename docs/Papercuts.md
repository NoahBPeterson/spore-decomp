# Papercuts

Shared log of friction that matching/pattern agents hit: tooling bugs, confusing instructions,
re-discovered tricks, wasted time. The orchestrator reviews this between batches and folds
fixes into tools, docs/matching.md and the agent prompts. Entries that have been addressed get
moved to "Resolved".

## How to add an entry (agents)
Append ONE entry with a single shell command so concurrent appends don't interleave:

    cat >> docs/Papercuts.md <<'PAPERCUT'
    - [<slice-or-pattern id>] <category: tooling|docs|codegen|toolchain|data> — <what cost you time>.
      Fix idea: <one line>. Time lost: ~<minutes>.
    PAPERCUT

Only log things that cost real time or that the next agent will hit too. Check whether an
existing entry already covers it; if so, don't duplicate it (you may append "+1 [<id>]" under it instead).

## Open

## Resolved
- [orchestrator] tooling: cmpobj misread section numbers above 32k (signed 16-bit). Fixed in cmpobj/libmatch/libresolve.
- [orchestrator] tooling: hand-typed workflow args. Agents now resolve slices via slice_info.py / pattern_info.py.
- [s0041dd90] codegen — /Od frames reserve unused slots for inlined-helper locals and slot order depends on local *names*; a `template<int N> inline void ScratchSlots(){uint32_t s[N];}` call (inlined, unused local) reproduces gaps, and brute-forcing local names via many member variants in one TU + try_variants.py finds the order. Fix idea: document both tricks. Time lost: ~60 minutes.
- [s004248c0] codegen — /Od slot order of locals and /Ob1 inline-temp behavior cost time. Findings: a function-scope local declared first (e.g. `void* q;`) gets the highest slot (-4) while block locals go below; inline-arg temps are only made for params the callee modifies (or whose address is taken); nested inline of a function that itself contains an inline call fails at /Ob1, but EASTL generic_iterator wrapper structs (by-value args) reproduce the 3+3 arg temporaries; `memcpy(a,b,8)` intrinsic gives the "src reg reused" 2-word copy; brute-forcing local names in one TU (try_variants.py ranks 300+ functions in ~1 min) finds slot orders. Fix idea: document these in docs/matching.md. Time lost: ~90 minutes (mostly wine under load 40+).
- [s00426430] codegen — /Od slot layout: inline-helper return values only get a temp slot when the helper has a named local (`uint32_t h = f(k); return h;`), and params/temps/locals of nested inlines order by call structure, not by variable NAMES (renaming locals changed nothing here). Tag temporaries passed as `const Tag&` args to inline helpers reproduce the one-byte stores that named tag locals could not place. `X + memcpy(...)` keeps X in esi only for a non-intrinsic memcpy inside a template helper. This slice also needed NO /EHsc (with it, `new (p) T(v)` adds an extra temp slot). Fix idea: document. Time lost: ~60 minutes.
- [s0042d560] codegen — /Od slot order of named locals follows the NAME (not declaration order) in some inlined helpers; brute-forcing names with a generator (placeholders @1..@n in a template, 100-900 variants per TU, try_variants ranking) found exact orders for Realloc/vector-assign/partial_sort in ~1 compile each. Also: explicit `p->~T()` on a class with a class-level `operator delete` reproduces the dead `xor eax,eax; and eax,1; je; call dealloc` branch; and memcpy must be declared non-dllimport (E8 thunk call) while memmove is dllimport (call [iat]). Fix idea: document in matching.md. Time lost: ~20 minutes.
- [s0042a220] codegen — /Od slot layout puzzles: (1) named locals are ordered by a name hash (declaration order is only a tiebreak), so brute-force names in one TU (try_variants compiles ~300 big variants in ~40s); (2) compiler temps for by-const-ref tag args (`const TagA&` fed `TagA()`) are allocated in-region in expansion order, and a second 1-byte unused local (`struct Tag2{}`) puts the pushed tag at +2 in its dword; (3) `n*4 + (int)memcpy(...)` (integer left operand) makes cl keep the count in esi across the call like the original, while `ptr + n` forms never do; (4) nested inline of tag-passing wrappers needs `PadN<k>()` before the call to reproduce unused-slot holes. Fix idea: document these and add a name-hash search helper to tools. Time lost: ~180 minutes.
- [s0042f9d0] codegen — /Od local slot order is a NAME-hash order within a scope (two-variable functions give a consistent total order; collisions fall back to reverse declaration), so: rank a pool of candidate names with ONE flat function of N `int` locals, pick names with increasing rank per role, verify in a batch compile (~20s for 300 variants; naive hill-climbing gets stuck at ~30 diff bytes). Also: (1) a bool helper result is only stored (`mov byte [slot],1; jmp`) when assigned to a shared local (`ok = TryGet(...)`); (2) ecx-first virtual call (`mov ecx,[x]; mov eax,[x]; mov edx,[eax]`) comes from an inline member `void Begin(){ p->Begin(); }`, plain `p->f()` gives eax-first; (3) a `return true` temp byte before dtor calls means RAII locals (inline dtors), not explicit cleanup calls; (4) ScratchSlots<N>() in an inline dtor/operator new sizes the compiler-generated ??_G / new-expression frames; (5) an empty-struct temp `AllocTag()` needs a user ctor `AllocTag(){}` or cl stores 0 into it. Fix idea: add the flat-rank name picker to tools/matching. Time lost: ~150 minutes.
