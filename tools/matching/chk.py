#!/usr/bin/env python3
"""Compile one source once and score it against MANY original functions (no global lock).

usage: chk.py <file.cpp> <slice-id | va[,va...]> [more vas...] [--flags "/Od /Ob1 /MD /Gy /TP"] [-a]
For every target VA it scores the symbol its manifest.txt row names (column "manif"), else the symbol
defined after the VA's `// @ 0x<va>` marker in the source ("marker"); only a VA with neither falls back to
the best symbol of similar size ("~size", fewest differing bytes). A symbol of another name that is
byte-identical still counts as MATCH ("other"; the manifest row must then name that symbol). Relocations are masked on both sides, so a whole
slice is checked with a single wine compile.
A slice id (sXXXXXXXX) is looked up in work/batches/*.json. -a also lists every symbol's best VA.
Exit 0 iff every target VA has a MATCH. Final verification is still run_all.py --manifest.
"""
import argparse, glob, hashlib, json, os, subprocess, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cmpobj import parse_coff, REL_SIZES
from run_all import Original, winpath, DEFAULT_FLAGS, INCLUDE, ROOT, resolve_flags
from card import load_funcs, bounds
sys.path.insert(0, os.path.join(ROOT, "tools", "difftest"))
from slice import marker_names, demangle_qual, base_ident  # noqa: E402

SKIP = ("__ehhandler", "__unwindfunclet", "__catch", "__tryend", "$")


def slice_vas(sid):
    for f in sorted(glob.glob(os.path.join(ROOT, "work", "batches", "*.json"))):
        for s in json.load(open(f)):
            if s["id"] == sid:
                return [int(v, 16) for v in s["vas"]]
    sys.exit("slice %s not found in work/batches/*.json" % sid)


def manifest_syms(src):
    """{va: symbol} from manifest.txt rows next to the source that name this source file."""
    out = {}
    mf = os.path.join(os.path.dirname(src), "manifest.txt")
    if os.path.exists(mf):
        for l in open(mf):
            p = l.split("#", 1)[0].split()
            if len(p) >= 3 and os.path.basename(p[0]) == os.path.basename(src):
                try:
                    out[int(p[2], 16)] = p[1]
                except ValueError:
                    pass
    return out


def marker_syms(src, va, names):
    """Object symbols the source's `// @ 0x<va>` marker names: the definition after the marker, matched on
    its qualified name (a definition inside a class body gives only the short name, so a '::name' suffix
    counts too). Several overloads can match; the caller scores them all."""
    want = marker_names(src, va)
    out = []
    for w in want:
        for name in names:
            q = demangle_qual(name)
            if q is None:
                hit = base_ident(name) == w.split("::")[-1]          # template: compare the identifier
            else:
                hit = q == w or q.endswith("::" + w) or w.endswith("::" + q)
            if hit and name not in out:
                out.append(name)
        if out:
            break
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src"); ap.add_argument("targets", nargs="+")
    ap.add_argument("--flags", default=" ".join(DEFAULT_FLAGS)); ap.add_argument("-a", action="store_true")
    a = ap.parse_args()
    vas = []
    for t in a.targets:
        for p in t.split(","):
            vas += slice_vas(p) if p.startswith("s") else [int(p, 16)]
    flags = resolve_flags(a.flags.split())
    src = os.path.abspath(a.src)
    tag = hashlib.md5((src + a.flags).encode()).hexdigest()[:10]
    obj = os.path.join(ROOT, "work", "match", "chk", "%s_%s.obj" % (os.path.basename(src).rsplit(".", 1)[0], tag))
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    if os.path.exists(obj):
        os.remove(obj)  # never score a stale object from an earlier compile
    r = subprocess.run([os.path.join(ROOT, "tools", "matching", "cl.sh"), "/nologo", "/c", *flags, INCLUDE,
                        "/Fo" + winpath(obj), winpath(src)], capture_output=True, text=True)
    if r.returncode or not os.path.exists(obj):
        sys.exit("COMPILE FAIL\n" + (r.stdout + r.stderr)[-3000:])

    secs, syms = parse_coff(obj)
    starts = {}
    for si, off in syms.values():
        starts.setdefault(si, set()).add(off)
    funcs = []
    for name, (si, off) in syms.items():
        if name.startswith(SKIP) or not (0 <= si < len(secs)) or secs[si] is None:
            continue
        sec = secs[si]
        nxt = sorted(o for o in starts[si] if o > off)
        mine = sec["data"][off:nxt[0] if nxt else len(sec["data"])]
        if nxt:
            mine = mine.rstrip(b"\xcc")
        if not mine:
            continue
        rmask = {v + k - off for v, _s, t in sec["relocs"] for k in range(REL_SIZES.get(t, 4)) if off <= v + k < off + len(mine)}
        funcs.append((name, mine, rmask))

    orig = Original()
    fstarts, _ = load_funcs()
    best, sym_best = {}, {}
    names = [f[0] for f in funcs]
    manifest = manifest_syms(src)
    for va in vas:
        n0 = len(bounds(va, fstarts))
        if manifest.get(va) in names:
            bound, how = {manifest[va]}, "manif"
        else:
            bound = set(marker_syms(src, va, names))
            how = "marker" if bound else "~size"
        size_best = None
        for name, mine, rmask in funcs:
            n = len(mine)
            near = abs(n - n0) <= max(8, n0 // 8)
            if name not in bound and not near:
                continue
            theirs, omask = orig.bytes_and_mask(va, n)
            d = sum(1 for i in range(n) if i not in rmask and i not in omask and theirs[i] != mine[i]) + abs(n - n0)
            if near and (size_best is None or d < size_best[0]):
                size_best = (d, n, name)
            if (not bound or name in bound) and (va not in best or d < best[va][0]):
                best[va] = (d, n, name)
            if name not in sym_best or d < sym_best[name][0]:
                sym_best[name] = (d, va)
        if size_best and size_best[0] == 0 and best.get(va, (1,))[0] != 0:
            # an identical function under another name (an implicit dtor, a ??_G deleting dtor the marked
            # function inlines): it is a real MATCH, but the manifest row must name this symbol
            best[va], how = size_best, "other"
        b = best.get(va)
        if b:
            print("%08x %5d  %4d diff  %-6s %s%s" % (va, n0, b[0], how, b[2], "  MATCH" if b[0] == 0 else
                                                     ("  (size %d vs %d)" % (b[1], n0) if b[1] != n0 else "")))
        else:
            print("%08x %5d     -  (no marker symbol and no symbol of similar size)" % (va, n0))
    if a.a:
        print("---- per symbol")
        for name, (d, va) in sorted(sym_best.items(), key=lambda x: x[1][1]):
            print("%08x %4d  %s" % (va, d, name[:110]))
    m = sum(1 for va in vas if best.get(va, (1,))[0] == 0)
    print("%d / %d target functions MATCH" % (m, len(vas)))
    return 0 if m == len(vas) else 1


if __name__ == "__main__":
    sys.exit(main())
