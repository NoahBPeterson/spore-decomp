# Equivalence layers: the interface prove.py calls

`tools/contrib/prove.py <va>` decides whether our build of a function is behaviourally equivalent to the retail
function, as a stack of independent layers ("Swiss cheese"). This file is the contract every layer implements.
Research behind it: work/scratch/equiv_brief.md (definitions), work/scratch/equiv_{rename,angr,ddec,alive}/.

## Inputs (tools/equiv/func.py)

`Func`: one side of the comparison.
- `va` (int): the address the code is placed at (retail VA; ours is placed at the same VA).
- `code` (bytes): the function's bytes, exactly the retail fingerprint size.
- `relocs` (dict offset -> token): every 4-byte relocated operand (absolute address or rel32 call/jmp target leaving
  the function), as a token naming what it refers to. Retail tokens are `"va:%08x"`; ours are the COFF symbol name.
  Tokens are compared through one consistent bijection (the same trust the byte-match check places in relocations).
- `calls` (list): for each call site, offset, token of the target, and `conv` facts when known
  (`ret_n`, `entry_regs`, `kill`), from tools/equiv/facts.py.
- `name` (str): for messages.

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
  - `refuted`: a concrete counterexample exists (describe it in `detail`).
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

## Bundle

One JSON per function, stored in the `equivalent.txt` row's sibling file `equivalent/<va>.json`, at most
2 KB + 1 KB per KB of function code:

    {"va": "011efeb0", "level": "L2", "retail_fp": "<fingerprint sha256>", "build": "<sha256 of our masked bytes>",
     "facts": {"kill": [...], "entry": [...]}, "layer": "ddec",
     "hints": {...layer-specific...}, "tools": {"prove": "1", "angr": "10.0.6", "stoke": "98d8a0f"}}

Layer hints: rename: none; angr: path pairing (branch-decision bit strings) and loop bounds with their reason;
ddec: segment cut points and the learned invariants (as STOKE prints them).
