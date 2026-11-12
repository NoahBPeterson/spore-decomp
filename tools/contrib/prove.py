#!/usr/bin/env python3
"""prove: is our build of a function behaviourally equivalent to the retail one?  (docs: tools/equiv/LAYERS.md)

  .venv/bin/python tools/contrib/prove.py 0x011efe30            # run the layers, print the verdict
  .venv/bin/python tools/contrib/prove.py 0x011efe30 --record   # on EQUIVALENT: write the equivalent.txt row + bundle
  .venv/bin/python tools/contrib/prove.py 0x011efe30 --recheck  # re-verify the recorded bundle (maintainers)

Needs work/SporeApp.analysis.bin (tools/contrib/make_image.py, from your own game). A function that is byte-exact
needs no proof. Otherwise the layers run cheapest first, each with a time limit:
  rename   register renaming + independent reordering (milliseconds, no extra installs)
  angr     symbolic execution with Z3 (tools/equiv/angr_layer.py; pip install angr)
  ddec     loop invariants with STOKE's DDEC in Docker (tools/equiv/ddec_layer.py)
A function is EQUIVALENT when a layer proves it at L2 (every register), or at L1 (the calling contract) with the same
kill set and entry registers as retail (tools/equiv/facts.py), and that layer rejects every mutant of our build
(tools/equiv/mutate.py). A counterexample from any layer makes it REFUTED: the source computes something else.
"""
import argparse, hashlib, importlib, json, os, sys, time

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", "equiv"), os.path.join(ROOT, "tools", "contrib")]
import func as FN    # noqa: E402
import facts         # noqa: E402
import mutate        # noqa: E402

LAYERS = ("rename", "angr_layer", "ddec_layer")
PROVE_VERSION = "1"


build_hash = FN.build_hash


def load_layer(name):
    try:
        return importlib.import_module(name)
    except ImportError as e:
        return str(e)


def tool_versions():
    v = {"prove": PROVE_VERSION}
    try:
        import angr
        v["angr"] = angr.__version__ if isinstance(angr.__version__, str) else ".".join(map(str, angr.__version__))
    except Exception:
        pass
    return v


def is_byte_exact(va, ours):
    import task
    import fingerprint as F
    fp = task.fingerprint(va)
    rel = {o + k for o in ours.relocs for k in range(4)}
    return F.check(fp, ours.code, rel) == "PASS"


def run(va, layers, timeout, hints=None, want=None, k_mutants=5, log=print):
    retail = FN.retail_func(va)
    ours = FN.our_func(va)
    import asm_audit
    asm = asm_audit.transcribed(os.path.join(ROOT, ours.meta["src"])).get("%08x" % va)
    if asm:
        return {"verdict": "ERROR", "detail": "assembly transcription (%s): write it as C++ first" % asm}
    if len(ours.code) == len(retail.code) and is_byte_exact(va, ours):
        return {"verdict": "MATCH", "detail": "byte-exact: nothing to prove"}
    same, why, fa = facts.same(retail, ours)
    level = want or ("L1" if same else "L2")
    log("facts: kill %s, entry %s; %s -> proving at %s" % (fa["kill"], fa["entry"],
                                                           "same as ours" if same else why, level))
    if ours.meta.get("stubs"):
        log("LTCG build with %s (the stubs must match retail's callees: ltcgstub.py --check-stubs)" % ours.meta["stubs"])
    results = []
    for name in layers:
        mod = load_layer(name)
        if isinstance(mod, str):
            log("  %-10s skipped (%s)" % (name, mod))
            continue
        h = (hints or {}).get(name) if hints else None
        r = mod.prove(retail, ours, level, h, timeout)
        log("  %-10s %-8s %6.1fs  %s" % (name, r["status"], r["seconds"], r["detail"][:150]))
        results.append((name, r))
        if r["status"] == "refuted":
            return {"verdict": "REFUTED", "layer": name, "detail": r["detail"], "level": level}
        if r["status"] != "proved":
            continue
        bad = []
        for desc, m in mutate.mutants(ours, k_mutants, seed=va):
            mr = mod.prove(retail, m, level, None, timeout)
            if mr["status"] == "proved":
                bad.append(desc)
        if bad:
            log("  %-10s self-test FAILED: proved mutant(s) %s; its proof is not accepted" % (name, "; ".join(bad)))
            continue
        bundle = {"va": "%08x" % va, "level": level, "retail_fp": retail.meta["fingerprint"],
                  "build": build_hash(ours), "facts": {"kill": fa["kill"], "entry": fa["entry"]},
                  "layer": name, "hints": r.get("hints") or {}, "tools": tool_versions()}
        return {"verdict": "EQUIVALENT", "layer": name, "level": level, "bundle": bundle, "ours": ours}
    return {"verdict": "UNKNOWN", "level": level, "detail": "no layer proved it"}


def bundle_limit(size):
    return 2048 + 1024 * ((size + 1023) // 1024)


def record(va, res):
    import task as T
    import slice as S
    src, ident = T.locate(va)
    d = S.slice_dir(ident)
    ours = res["ours"]
    rel_src = os.path.relpath(src, os.path.join(ROOT, "match")).replace(os.sep, "/")
    line = "%s  %s  %08x  %s" % (rel_src, ours.meta["symbol"], va, " ".join(ours.meta["flags"]))
    data = json.dumps(res["bundle"], separators=(",", ":"), sort_keys=True)
    if len(data) > bundle_limit(len(ours.code)):
        raise SystemExit("bundle is %d bytes, over the %d-byte limit" % (len(data), bundle_limit(len(ours.code))))
    os.makedirs(os.path.join(d, "equivalent"), exist_ok=True)
    open(os.path.join(d, "equivalent", "%08x.json" % va), "w").write(data + "\n")
    path = os.path.join(d, "equivalent.txt")
    rows = open(path).read().splitlines() if os.path.exists(path) else ["# source  symbol  va  flags   (proved "
                                                                         "equivalent, not byte-exact: tools/contrib/prove.py)"]
    rows = [r for r in rows if r.startswith("#") or "%08x" % va not in r.split()[2:3]] + [line]
    open(path, "w").write("\n".join(rows) + "\n")
    print("recorded: %s\n  %s\nbundle: %s (%d bytes)" % (os.path.relpath(path, ROOT), line,
                                                          os.path.relpath(os.path.join(d, "equivalent", "%08x.json" % va), ROOT), len(data)))


def find_bundle(va):
    import task as T
    import slice as S
    _src, ident = T.locate(va)
    p = os.path.join(S.slice_dir(ident), "equivalent", "%08x.json" % va)
    return json.load(open(p)) if os.path.exists(p) else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("va")
    ap.add_argument("--layers", default=",".join(LAYERS))
    ap.add_argument("--timeout", type=float, default=300.0, help="seconds per layer run")
    ap.add_argument("--level", choices=("L1", "L2"))
    ap.add_argument("--record", action="store_true", help="on EQUIVALENT, write the equivalent.txt row and bundle")
    ap.add_argument("--recheck", action="store_true", help="re-verify the recorded bundle with its hints")
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args()
    va = int(a.va, 16)
    t = time.time()
    layers = [x if x == "rename" or x.endswith("_layer") else x + "_layer" for x in a.layers.split(",")]
    hints = None
    if a.recheck:
        b = find_bundle(va)
        if not b:
            raise SystemExit("0x%08x has no recorded bundle" % va)
        layers, hints = [b["layer"]], {b["layer"]: b["hints"]}
    res = run(va, layers, a.timeout, hints, a.level or (b["level"] if a.recheck else None))
    if a.recheck and res["verdict"] == "EQUIVALENT" and res["bundle"]["build"] != b["build"]:
        res = {"verdict": "UNKNOWN", "detail": "our build changed since the proof (build hash differs)"}
    print("%s  0x%08x  %s  (%.1fs)" % (res["verdict"], va, res.get("layer", "") + " " + res.get("level", "")
                                       if res["verdict"] != "MATCH" else res["detail"], time.time() - t))
    if res.get("detail") and res["verdict"] in ("REFUTED", "UNKNOWN"):
        print("  " + res["detail"])
    if a.json:
        print(json.dumps({k: v for k, v in res.items() if k != "ours"}, indent=1))
    if a.record and res["verdict"] == "EQUIVALENT" and not a.recheck:
        record(va, res)
    return 0 if res["verdict"] in ("EQUIVALENT", "MATCH") else 1


if __name__ == "__main__":
    sys.exit(main())
