# Equivalence testing (differential execution)

`nonmatching.txt` lists functions whose source compiles and is *claimed* to behave like the
original but is not byte-exact. `tools/difftest/equiv.py` tests that claim: it runs the ORIGINAL
function (from `work/SporeApp.analysis.bin`) and OUR compiled function side by side under Unicorn
on the same inputs and compares everything either one can observably do. This is
**differential testing** (industry term): evidence from sampled inputs, not a proof.

## Running it

```
.venv/bin/python tools/difftest/equiv.py <slice-id> [<va> ...] [options]
.venv/bin/python tools/difftest/batch.py work/batches/<batch>.json --out work/difftest/<batch>_equiv.json [options]
.venv/bin/python -m pytest tools/difftest/test_equiv.py          # self-tests, ~30 s
```

Without VAs, `equiv.py` tests every VA in the slice's `nonmatching.txt`; any VA works, including
byte-exact ones from `manifest.txt`. `batch.py` runs every nonmatching VA of a batch file in one
process and writes the JSON plus `<out>_summary.md` (counts and KB per verdict, one row per function).
Neither tool writes anything under `match/`; objects go to `work/difftest/obj/`, failing inputs to
`work/difftest/fail_inputs/`.

| option | default | meaning |
|---|---|---|
| `--flags "..."` | see below | cl flags for our object |
| `--src file.cpp` | slice source | test another source (used for mutants) |
| `--inputs N` | 400 | inputs to try (attempts, not valid ones) |
| `--seed S` | 1 | inputs are reproducible from (slice, va, seed) |
| `--min-valid K` / `--min-cov C` | 200 / 60 | PASS thresholds |
| `--ulp U` | 0 | tolerate float32 dwords (and an x87 result) within U ulps; reported |
| `--strict-calls` | off | do not tolerate call-trace differences explained by inlining |
| `--nan` | off | also generate NaN/Inf float bit patterns |
| `--alias P` | 0 | probability that a generated pointer aliases an argument object |
| `--repairs N` | 24 | fault repairs per input (0 = off) |
| `--no-fake-calls` | | discard inputs that call through a generated function pointer |
| `--ignore-abi` | | run even if the original reads an undeclared register argument |
| `--budget N`, `--run-seconds S`, `--time-limit S` | 10M insns, 10 s, 600 s | per-run and per-function caps (ours gets 4x) |
| `--replay file.pkl` | | re-run one saved failing input and print both sides' registers, calls and imports |
| `--json out.json` | | write the per-function results |

Flags come from, in order: `--flags`; a `flags /O2 ...` note in the nonmatching reason; a
`// Flags: ...` comment near the top of the source; the reason's loose flag tokens; the slice
manifest; `/O2 /MD /Gy /EHsc /TP`. Only `/O2`-vs-`/Od` and `/fp:` change behavior in practice.

## What happens

1. **Our function**: compile, then find our symbol for the VA: the manifest row, else the name in
   `symbols/slices/<id>.txt` or after the `// @ 0x<va>` marker, matched against the object's
   symbols (an implausible size, more than 5x off, is rejected).
2. **Relocations** (`tools/difftest/resolve.py`): every symbol our function, its local helpers and
   its data reference is mapped to the ORIGINAL address, so both sides call the same real callees
   and touch the same real globals. Methods, in order: `__imp_` imports and import thunks; CRT
   helpers from `symbols/lib_names.txt`; exact mangled or unique qualified names in `symbols/`;
   an address in the name (`FUN_00abcdef`, `Fn9467b0`, `g_01582df8`); a `// 0x...` (or
   `// DAT_...`, `// 0169cc88`) comment on the declaration, matched by identifier, enclosing class
   and, for overloads, parameter types; string literals found in `.rdata`; and finally
   **alignment**: our N-th call/global reference against the original's, accepted only for a
   single unresolved reference between two agreeing anchors (on op1, held-out resolved symbols
   pair correctly 99% of the time that way, 89% for two-reference gaps, worse beyond, so longer gaps
   may only veto; it iterates, newly resolved symbols becoming anchors). A vtable our code
   constructs is mapped to the original's when all its slots resolve and that slot sequence
   occurs once in `.rdata`. Anything still unresolved makes the function **UNSUPPORTED** and is listed.
   Symbols reachable only from EH tables, RTTI or a vtable we could not map are not required:
   they point at trap addresses, and an input that reaches one is discarded (`ours-trap`).
   Disagreements between alignment and the other methods are reported as `resolution_conflicts`.
3. **Inputs**: arguments follow the decorated name's signature (pointer, int, float, double, bool;
   `this` in ecx). Pointers lead to lazily materialised 64 KB objects whose 4 KB pages are filled,
   on first touch, with "pointer soup": a deterministic mix of pointers to further objects,
   zeros, small ints, floats and constants harvested from the original's immediates. Both runs
   see identical bytes. Then:
   - **fault repair**: when the original faults on a bad pointer, the dword it was loaded from
     (found by tracing reads; the faulting instruction's base register gives the exact value) is
     replaced by a pointer to a fresh object and the input is retried;
   - **fake methods**: a call through a generated function pointer (a soup vtable) returns a
     deterministic value and pops the argument bytes counted at the call site; float returns are
     detected by the x87 code after the call. Both sides must count the same arity per target;
   - **coverage-guided fuzzing** (industry term; AFL-style): 60% of inputs are mutations of
     earlier inputs that reached new code in the original.
4. **Runs**: original first; an input is *discarded* (counted by reason) if the original faults,
   hits an unhandled import, exceeds the budget, or returns with clobbered callee-saved
   registers / wrong esp (garbage input). Otherwise ours runs on a restored snapshot; if ours
   faults, times out or breaks the ABI where the original did not, that is a mismatch.
5. **Observables compared**: return value per the declared type (al for bool, ax for short,
   eax, edx:eax for 64-bit; never for void), ebx/esi/edi/ebp, esp after return, x87 stack depth,
   st0 (80-bit, bit-exact), x87 control word, MXCSR control bits, every byte of image
   `.data`/`.bss`/`.tls`, every touched input page, the malloc heap, the caller's stack above the
   arguments, TEB/TLS, and any write by ours to its own static data. Plus the ordered **import
   trace** at any depth (name + arguments) and the **depth-1 call trace** of the function itself
   (callee, `this`/edx when the callee uses them, stack arguments up to the callee's `ret N`, or
   our declaration's arity for cdecl callees; by-value struct arguments are not compared).
   Pointers into either side's own stack frame compare equal to each other ("STK"), since frame
   layouts legitimately differ; so do two pointers to byte-identical read-only constants (the same
   string pooled at two addresses). Call-trace differences consisting only of callees that one side
   never calls on that input are tolerated as inlining differences (counted in `tolerated`).
6. **Coverage**: distinct instructions of the original (recursive-descent disassembly, jump
   tables followed) executed by valid inputs.

## Verdicts

- **PASS**: >= K valid inputs (default 200), no mismatch, original coverage >= C (default 60%).
- **WEAK**: no mismatch but below a threshold. Usually low coverage: random objects rarely satisfy
  the conditions guarding the interesting paths.
- **FAIL**: a mismatch on some valid input. The JSON has the observable, both values (up to 8
  differing dwords, with a float ulp distance when they are close floats), a triage `kind`
  (`float-rounding`: all differences are finite floats within 1024 ulps; `float-special`: a NaN/Inf
  on one side; `value`: anything else), how many fake method calls and fault repairs the input
  needed (`fake_calls`, `repairs`: the more, the less realistic the input), and the input file for
  `--replay`. If ours stores the address of its *own* copy of an object/vtable/constant where the
  original stores the image's, the verdict is UNSUPPORTED instead (map that symbol).
- **UNSUPPORTED**: symbol not found, compile error, unresolved reference, an undeclared register
  argument in the original (custom/LTCG ABI), our code reaching a trapped symbol, or fewer than
  max(10, 5% of tried) valid inputs.

### What PASS means, and what it does not

PASS means: on a few hundred random, fuzzed and repaired inputs that the original handled
without faulting, ours produced bit-identical results, and those inputs together executed at
least 60% of the original's instructions. It is evidence, not proof. In particular:

- Paths behind specific object states (message IDs, linked structures, valid vtables) are often
  not reached; check `coverage.pct`, and treat the uncovered 40% as untested.
- Inputs are adversarial-random, not realistic. A FAIL can come from behavior real data never
  triggers (huge or denormal floats, aliasing-free objects, garbage in padding). Every FAIL still
  shows a real difference between the two binaries on that input; decide whether it matters.
- Callees run for real, but objects behind generated function pointers are do-nothing fakes, so
  their side effects are not modelled.
- Float compare is bit-exact by default. Source that reassociates float math (often fine under
  `/fp:fast`) FAILs with a small ulp distance; `--ulp` loosens it, and the report says so.
- NaN/Inf bit patterns are not generated by default (`--nan` adds them): equivalent spellings of
  a comparison legitimately differ on NaN, and that drowned out everything else.

## Known limitations

- Object-heavy functions (HandleMessage, managers, EASTL containers) are mostly UNSUPPORTED or
  WEAK: circular lists, required vtables and singletons set at runtime cannot be synthesised from
  random bytes; repair and fake methods only go so far.
- Fake-method arity is a heuristic (pushes walked back from the call site). Disagreement between
  the two sides discards the input; an agreeing but wrong count breaks the ABI and the input is
  discarded too, but it can in principle still mislead.
- Resolution relies on the source's annotations being right. A wrong `// 0x...` comment makes
  ours call the wrong function and produces a FAIL that is the annotation's fault (often visible
  in `resolution_conflicts`).
- A register-argument ABI (LTCG) in the original that our declaration does not reproduce is
  reported UNSUPPORTED rather than tested.
- Only CRT/Win32 imports with a handler in `tools/difftest/machine.py` run; any other import in
  the original discards the input (`import:<name>`). rdtsc returns a per-run counter.
- Our local helpers that have no original counterpart are loaded from our object; their calls
  count as depth-1 calls of our function.
