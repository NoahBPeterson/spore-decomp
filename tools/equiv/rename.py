"""Layer 1: register renaming plus scheduling (rename_core.py). Milliseconds; proves equivalence when the two
functions differ only by a consistent register renaming and a reordering of independent instructions.
Sound by construction (same CFG, same def-use graph); it never refutes, a rejection is `unknown`."""
import time

import facts
import rename_core

rename_core.STD_SAFE = facts.std_call_safe


def prove(retail, ours, level, hints=None, timeout=10.0):
    t = time.time()
    model = "ltcg" if ours.meta.get("dll") else "std"
    ok, why = rename_core.check(retail.code, retail.va, retail.relocs, ours.code, ours.va, ours.relocs,
                                model=model, level=2 if level == "L2" else 1)
    return {"status": "proved" if ok else "unknown", "seconds": round(time.time() - t, 3),
            "detail": why, "hints": {}}
