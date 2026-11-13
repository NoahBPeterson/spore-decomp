#!/usr/bin/env python3
"""Map every compiled symbol of ours to its retail address, from the // @ 0x... markers (maintainers).

  .venv/bin/python tools/equiv/symmap.py [--jobs N] [--limit N]     # writes work/symmap.json

Each source file with markers is compiled with its flags (cached in work/difftest/obj) and each marker's symbol is
found the way check.py finds it (slice.find_symbol). The angr layer uses the map to pair a relocation of ours with
its retail address exactly, instead of by aligning instructions.
"""
import argparse, json, os, re, sys, time
from concurrent.futures import ProcessPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", d) for d in ("contrib", "difftest", "matching", "ci")]
MARK = re.compile(r"(?mi)^//\s*@\s*0x0*([0-9a-f]+)\b")
OUT = os.path.join(ROOT, "work", "symmap.json")


def one(src):
    import task as T
    import slice as S
    from coff import Coff
    vas = [int(m, 16) for m in MARK.findall(open(src, errors="replace").read())]
    out, bad = {}, 0
    if not vas:
        return out, bad
    try:
        _s, ident = T.locate(vas[0])
        fl, _ = S.choose_flags(ident, vas[0], None)
        obj, _log = S.compile_obj(src, fl)
        if not obj:
            return out, len(vas)
        coff = Coff(obj)
        for va in vas:
            fp = T.fingerprint(va)
            sym, _why = S.find_symbol(coff, ident, va, src, orig_size=fp["size"] if fp else None)
            if isinstance(sym, str):
                out[sym] = "%08x" % va
            else:
                bad += 1
    except Exception:
        bad += len(vas)
    return out, bad


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--limit", type=int)
    a = ap.parse_args()
    import task as T
    srcs = sorted(T.sources())[:a.limit]
    t, m, bad = time.time(), {}, 0
    with ProcessPoolExecutor(a.jobs) as ex:
        for k, (o, b) in enumerate(ex.map(one, srcs, chunksize=4), 1):
            m.update(o)
            bad += b
            if k % 500 == 0:
                print("%d/%d files, %d symbols" % (k, len(srcs), len(m)), flush=True)
    json.dump(m, open(OUT, "w"), sort_keys=True)
    print("%d symbols from %d files (%d markers not resolved) in %.0fs -> %s" % (len(m), len(srcs), bad,
                                                                             time.time() - t, os.path.relpath(OUT, ROOT)))


if __name__ == "__main__":
    main()
