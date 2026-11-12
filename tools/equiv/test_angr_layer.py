#!/usr/bin/env python3
"""Tests of the angr equivalence layer (tools/equiv/angr_layer.py). Needs the analysis image and the angr venv.

    test_angr_layer.py [CASE ...] [--jobs N] [--timeout S] [--out FILE] [--hinted]

Cases:
  pitch      D3D9GetStreamedMipLevelPitch 0x011efe30, /LTCG build from the vs2005-cpp harness
             (work/scratch/equiv_angr/pitchbuild): L1 proved, L2 refuted (edx at return)
  init       Raster::Initialize 0x011efeb0 (/LTCG stub build via func.our_func): L2 proved
  neg_mask, neg_store, neg_swap   mutants of init (0x40 -> 0x41, a dropped store, two swapped stores): refuted
  rename     loop-free, non-LTCG functions the renaming checker rejected (work/scratch/equiv_rename/reg300_re.jsonl)
--hinted reruns each proved case with the hints of its first run and reports both times.
Results go to work/scratch/equiv_angr2/results.jsonl (game bytes never leave work/).
"""
import argparse, json, os, sys, threading, time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
import func as FN          # noqa: E402
import angr_layer as AL    # noqa: E402

PROTO = os.path.join(ROOT, "work", "scratch", "equiv_angr")
OUT = os.path.join(ROOT, "work", "scratch", "equiv_angr2")


def dll_func(dll, sym, size, va_retail):
    import ltcg
    m = ltcg.read_map(os.path.join(os.path.dirname(dll), "ltcg.map"))
    base = m[sym]
    data, rel = ltcg.cut(dll, base, size)
    return FN.Func(base, data, FN.tokens_abs(data, base, rel), sym, "ours", {"dll": dll, "symbol": sym})


def raw_func(code, base, like):
    """ours from raw (mutated) bytes: relocated fields = rel32 calls/jumps leaving the function"""
    rel = set()
    for i in FN.MD.disasm(code, base):
        b = i.bytes
        if (b[0] in (0xE8, 0xE9) and i.size == 5) or (b[0] == 0x0F and 0x80 <= b[1] <= 0x8F and i.size == 6):
            t = int(i.op_str, 16)
            if not base <= t < base + len(code):
                o = i.address + i.size - 4 - base
                rel |= {o, o + 1, o + 2, o + 3}
    return FN.Func(base, code, FN.tokens_abs(code, base, rel), like.name, "ours", dict(like.meta))


_init = {}
_lock = threading.Lock()


def init_ours():
    with _lock:
        if "f" not in _init:
            _init["f"] = FN.our_func(0x011efeb0)
        return _init["f"]


def cases(names):
    out = []
    pitch_sym = "?D3D9GetStreamedMipLevelPitch@Raster@graphics@rw@@QAEIE@Z"
    if "pitch" in names:
        mk = lambda: (FN.retail_func(0x011efe30),
                      dll_func(os.path.join(PROTO, "pitchbuild", "ltcg.dll"), pitch_sym, 116, 0x011efe30))
        out += [("pitch", "L1", mk, "proved"), ("pitch", "L2", mk, "refuted")]
    if "init" in names:
        out.append(("init", "L2", lambda: (FN.retail_func(0x011efeb0), init_ours()), "proved"))
    for neg in ("neg_mask", "neg_store", "neg_swap"):
        if neg in names:
            def mk(neg=neg):
                spec = json.load(open(os.path.join(PROTO, neg + ".json")))
                ours = init_ours()
                return FN.retail_func(0x011efeb0), raw_func(bytes.fromhex(spec["b"]["hex"]), ours.va, ours)
            out.append((neg, "L1", mk, "refuted"))
    if "rename" in names:
        rows = [json.loads(l) for l in open(os.path.join(ROOT, "work", "scratch", "equiv_rename", "reg300_re.jsonl"))]
        picked = 0
        for r in sorted(rows, key=lambda r: r["size"]):
            lo, hi = int(os.environ.get("RENAME_MIN", "0")), int(os.environ.get("RENAME_MAX", "160"))
            if r["L1"][0] != "REJECT" or not os.path.exists(r["obj"]) or not lo <= r["size"] <= hi:
                continue
            va = int(r["va"], 16)
            try:
                ret = FN.retail_func(va)
                ours = FN.obj_func(r["obj"], r["sym"])
            except BaseException:
                continue
            if AL.classify(ret.code, ret.va)["heads"] or AL.classify(ours.code, 0)["heads"]:
                continue
            out.append(("rename:%s" % r["va"], "L1", lambda ret=ret, ours=ours: (ret, ours), None))
            picked += 1
            if picked >= int(os.environ.get("RENAME_N", "12")):
                break
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("case", nargs="*", default=["pitch", "init", "neg_mask", "neg_store", "neg_swap", "rename"])
    ap.add_argument("--jobs", type=int, default=2)
    ap.add_argument("--timeout", type=float, default=900)
    ap.add_argument("--hinted", action="store_true")
    ap.add_argument("--out", default=os.path.join(OUT, "results.jsonl"))
    a = ap.parse_args()
    todo = cases(set(c.split(":")[0] for c in a.case) if a.case else set())
    sem = threading.Semaphore(max(1, min(4, a.jobs)))
    rows, ths = [], []

    def one(name, level, mk, want):
        with sem:
            retail, ours = mk()
            r = AL.prove(retail, ours, level, None, a.timeout)
            row = {"case": name, "level": level, "want": want, "status": r["status"], "seconds": r["seconds"],
                   "detail": r["detail"][:400], "hints_bytes": len(json.dumps(r["hints"], separators=(",", ":")))}
            if a.hinted and r["status"] == "proved":
                r2 = AL.prove(retail, ours, level, r["hints"], a.timeout)
                row.update(hinted_status=r2["status"], hinted_seconds=r2["seconds"])
                bad = json.loads(json.dumps(r["hints"]))
                if bad.get("loops"):
                    side = sorted(bad["loops"])[0]
                    h = sorted(bad["loops"][side])[0]
                    bad["loops"][side][h][0] = max(1, bad["loops"][side][h][0] // 4)
                elif bad.get("bij") and len(bad["bij"]) >= 2:
                    bad["bij"][0][1], bad["bij"][1][1] = bad["bij"][1][1], bad["bij"][0][1]
                elif bad.get("bij"):
                    bad["bij"][0][1] += 1          # not a relocated field of ours
                else:
                    bad["fallback"] = []
                    bad["pairs"] = [["0", "1"], ["1", "0"]]
                r3 = AL.prove(retail, ours, level, bad, a.timeout)
                row.update(wrong_hint_status=r3["status"], wrong_hint_detail=r3["detail"][:200])
            ok = want is None or row["status"] == want
            print("%-18s %s %-8s %7.1fs %s %s" % (name, level, row["status"], row["seconds"],
                                                  "" if ok else "EXPECTED %s" % want, row["detail"][:160]),
                  flush=True)
            if "hinted_seconds" in row:
                print("%-18s    hinted: %s %.1fs; wrong hint: %s" % (name, row["hinted_status"],
                                                                     row["hinted_seconds"],
                                                                     row["wrong_hint_status"]), flush=True)
            with _lock:
                rows.append(row)
                with open(a.out, "a") as f:
                    f.write(json.dumps(dict(row, t=time.strftime("%Y-%m-%d %H:%M"))) + "\n")

    for c in todo:
        t = threading.Thread(target=one, args=c)
        t.start()
        ths.append(t)
    for t in ths:
        t.join()
    bad = [r for r in rows if r["want"] and r["status"] != r["want"]]
    print("%d cases, %d unexpected" % (len(rows), len(bad)))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
