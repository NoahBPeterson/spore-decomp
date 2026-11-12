# Equivalence layers: the interface prove.py calls

`tools/contrib/prove.py <va>` decides whether our build of a function is behaviourally equivalent to the retail
function, as a stack of independent layers ("Swiss cheese"). This file is the contract every layer implements.
Research behind it: work/scratch/equiv_brief.md (definitions), work/scratch/equiv_{rename,angr,ddec,alive}/.

## Inputs (tools/equiv/func.py)

`Func`: one side of the comparison.
- `va` (int): the address the code is placed at (retail VA; ours is placed at the same VA).
- `code` (bytes): the function's bytes, exactly the retail fingerprint size.
- `relocs` (dict offset -> token): every 4-byte relocated operand (absolute address or rel32 call/jmp target leaving
  the function), as a token naming what it refers to: retail `("abs", target)`; ours from an object
  `("sym", name, coff_type, addend)`, ours from an /LTCG DLL `("abs", target_in_dll)`.
  Tokens are compared through one consistent bijection (the same trust the byte-match check places in relocations).
- `calls` (list): for each call site, offset, token of the target, and `conv` facts when known
  (`ret_n`, `entry_regs`, `kill`), from tools/equiv/facts.py.
- `name` (str): for messages.

`meta` (ours): `src`, `flags`, `symbol`, `ret64` (returns edx:eax), and for /LTCG builds `dll` and `stubs`.
Register facts per call (kill set, entry registers, `ret N`) come from tools/equiv/facts.py.

`retail_func(va)` and `our_func(va)` build them (ours from the object, or from the /LTCG DLL when the function has a
stub file, tools/matching/ltcg.py).

## The layer API

Each layer is a module in tools/equiv/ with

    def prove(retail: Func, ours: Func, level: str, hints: dict | None, timeout: float) -> dict

- `level`: `"L1"` (calling contract: eax (+edx for 64-bit returns), every memory write with its order relative to
  calls, every call with its target and the arguments it can read, ebx/esi/edi/ebp/esp restored, DF) or `"L2"`
  (L1 plus every register, including ecx/edx/xmm, at every call and at every return).
- `hints`: the layer's own bundle entry from an earlier run, or None. With hints the layer must not search for what
  the hints give, only check it; wrong hints must make it fail (never silently fall back to trusting them).
- Returns `{"status": "proved" | "refuted" | "unknown", "seconds": float, "detail": str, "hints": dict}`.
  - `proved`: sound proof at that level. Loops: either fully covered (a checked bound with a reason) or proved with
    an invariant. A bounded-only result is `unknown`.
  - `refuted`: a concrete counterexample exists at the requested level (describe it in `detail`). Refuted at L2 only
    says something a normal caller may ignore differs (for example a scratch register); prove.py asks for L2 only
    when the kill set or entry registers differ, where that difference does matter.
  - `unknown`: anything else, including timeouts and unsupported instructions. Never guess.
  - `hints`: what makes a recheck cheap (see Bundle). Keep it small; no instructions, no retail output values.
- Must enforce `timeout` itself and leave no processes behind.
- Must not print or store game bytes outside work/.

## Self-test (mutation) contract

`tools/equiv/mutate.py` makes `k` mutants of `ours` (changed immediate, dropped store, swapped call arguments,
swapped dependent instructions, changed register). prove.py accepts a layer's `proved` only if the same layer refutes
or fails to prove every mutant (a layer that proves a mutant is broken for this function).

## Acceptance rule (prove.py)

A function is EQUIVALENT when, in order:
1. Build is faithful: for LTCG functions the stub check passes (kill set, entry registers, ret N of each stub).
2. `facts.py`: our kill set and entry registers equal retail's (needed unless the proof is at L2).
3. Some layer returns `proved` at `L2`, or at `L1` with step 2 passing, and passes the mutation self-test.
4. No layer returns `refuted`.
Layers run cheapest first: rename (ms), angr (seconds to minutes, loop-free or bounded loops), ddec (loops).

## The layers

- **rename** (rename.py, rename_core.py): register renaming plus reordering of independent instructions; never
  refutes. A call is modelled with the standard convention (reads its arguments, writes eax/ecx/edx) only where the
  retail callee really kills eax/ecx/edx (facts.std_call_safe); otherwise it reads and writes every register.
- **angr** (angr_layer.py): symbolic execution with Z3, in its own venv (`python3 -m venv work/angr-venv &&
  work/angr-venv/bin/pip install angr==10.0.6 pefile capstone`, or $EQUIV_ANGR_PYTHON). Fully automatic: call
  sites, returns, loop heads, callee `ret N` and argument registers come from the code and our decorated names.
  Loops are accepted only with a checked bound (every state reaching the bound provably diverges). Modelling
  assumption: an address computed only from the entry state never points into the 1 MB below the entry esp (the
  function's own not-yet-allocated frame), as the compiler itself assumes when it moves pushes across loads.
  Counterexamples that rest on a guessed relocation pairing, assumed callee register reads, differences inside the
  function's own frame at L1, differing x87 sequences or supplied hints are reported as unknown, never refuted.
  angr 10 note: claripy's `AST.identical()` returns True for different symbols (gave a false proof once); compare
  by hash. Unsupported (unknown): switch tables, nested loops, loops that call or write memory, segment registers.
- **ddec** (ddec_layer.py, ddec/): DDEC from STOKE (commit 98d8a0f) in Docker, optional and mainly for maintainers:
  skipped when Docker is missing. Build once: `docker build --platform linux/amd64 -t spore-stoke-ddec:98d8a0f-1
  tools/equiv/ddec`. Each 32-bit function is translated to x86-64 code with 32-bit addresses kept, split at calls;
  invariants are learned from unicorn traces (equality invariants of the DDEC paper, DDEC_EQ_ONLY) and proved
  inductive by Z3; hints carry the cut points and invariants so a recheck learns nothing. No counterexamples except
  from a concrete run; slow on loop-free code with many branches. Unsupported: x87, string instructions, segment
  overrides, switch tables; SSE float conversions time out.

## Bundle

One JSON per function, stored in the `equivalent.txt` row's sibling file `equivalent/<va>.json`, at most
2 KB + 1 KB per KB of function code:

    {"va": "011efeb0", "level": "L2", "retail_fp": "<fingerprint sha256>", "build": "<sha256 of our masked bytes>",
     "facts": {"kill": [...], "entry": [...]}, "layer": "ddec",
     "hints": {...layer-specific...}, "tools": {"prove": "1", "angr": "10.0.6", "stoke": "98d8a0f+ddec-hints-1"}}

Layer hints: rename: none; angr: path pairing (branch-decision bit strings) and loop bounds with their reason;
ddec: segment cut points and the learned invariants (as STOKE prints them).
