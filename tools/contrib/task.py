#!/usr/bin/env python3
"""task: everything you need to work on one function (a "context pack", printed).

  .venv/bin/python tools/contrib/task.py 0x00529690

Prints where the function lives (its source file and object), its status (byte-exact, complete but not yet byte-exact,
partial, or no source yet), the compiler flags it is checked with, its retail size, the headers its file includes, the
current source of the function, and what to do next.  Needs only the repo: no game files.

  --list [--max-size N]   open work: functions with source that is not byte-exact yet, smallest first
"""
import argparse, glob, gzip, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.join(ROOT, "tools", "difftest"), os.path.join(ROOT, "tools", "matching"),
                os.path.join(ROOT, "tools", "ci")]
import slice as S       # noqa: E402

FP = os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl.gz")
_fps = None


def fingerprints():
    global _fps
    if _fps is None:
        _fps = {int(d["va"], 16): d for d in map(json.loads, gzip.open(FP, "rt"))}
    return _fps


def sources():
    out = []
    for d in (os.path.join(ROOT, "src", "game"), os.path.join(ROOT, "match", "slices")):
        out += [f for f in glob.glob(os.path.join(d, "**", "*.c*"), recursive=True) if os.path.isfile(f)]
    return out


def locate(va):
    """(source file, ident) carrying the line-start marker `// @ 0x<va>`; src/game first"""
    pat = re.compile(r"(?mi)^//\s*@\s*0x0*%x\b" % va)
    for f in sources():
        if pat.search(open(f, errors="replace").read()):
            rel = os.path.relpath(f, ROOT)
            if rel.startswith("src" + os.sep):
                stem = os.path.splitext(os.path.basename(f))[0]
                d = os.path.basename(os.path.dirname(f))
                return f, (stem if S.module_dir(stem) else "%s/%s" % (d, stem))
            return f, rel.split(os.sep)[2]
    return None, None


def status(ident, va):
    d = S.slice_dir(ident)
    if any(r[2] == va for r in S.manifest_rows(ident)):
        return "byte-exact", ""
    for name, label in (("nonmatching.txt", "complete, not byte-exact yet"), ("partial.txt", "partial")):
        for rva, diff, reason in S.read_rows(os.path.join(d, name)):
            if rva == va:
                return label, "%s byte(s) differ; note: %s" % (diff, reason) if diff else reason
    return "has source, not listed", ""


def body(src, va):
    """the source text from the marker to the end of the function's braces"""
    t = open(src, errors="replace").read()
    m = re.search(r"(?mi)^//\s*@\s*0x0*%x\b.*$" % va, t)
    i = t.find("{", m.end())
    depth, j = 0, i
    while j < len(t):
        depth += {"{": 1, "}": -1}.get(t[j], 0)
        if depth == 0:
            break
        j += 1
    return t[m.start():j + 1]


def open_work(max_size):
    rows = []
    for f in glob.glob(os.path.join(ROOT, "match", "slices", "*", "nonmatching.txt")) + \
            glob.glob(os.path.join(ROOT, "src", "game", "**", "nonmatching.txt"), recursive=True):
        for va, diff, reason in S.read_rows(f):
            fp = fingerprints().get(va)
            if fp and fp["size"] <= max_size:
                rows.append((fp["size"], va, diff, os.path.relpath(os.path.dirname(f), ROOT), reason))
    return sorted(rows)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("va", nargs="?")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--max-size", type=int, default=256)
    a = ap.parse_args()
    if a.list:
        rows = open_work(a.max_size)
        print("%d functions with complete source that is not byte-exact yet, up to %d bytes:" % (len(rows), a.max_size))
        for size, va, diff, where, reason in rows:
            print("  0x%08x  %5d bytes  %4s differ  %s  %s" % (va, size, diff or "?", where, (reason or "")[:70]))
        return 0
    if not a.va:
        ap.error("give a function address, or --list")
    va = int(a.va, 16)
    fp = fingerprints().get(va)
    src, ident = locate(va)
    print("function   0x%08x" % va)
    print("retail     %s" % ("%d bytes (fingerprint: %d bytes are addresses, not compared)" %
                             (fp["size"], sum(n for _s, n in fp["mask"])) if fp else "no fingerprint: not a known function start"))
    if not src:
        print("source     none yet: no file has a `// @ 0x%08x` marker. Write it in the object's source file" % va)
        return 0
    st, note = status(ident, va)
    flags, how = S.choose_flags(ident, va)
    print("source     %s   (object %s)" % (os.path.relpath(src, ROOT), ident))
    print("status     %s%s" % (st, "\n           " + note[:300] if note else ""))
    print("flags      %s   (from %s)" % (" ".join(flags), how))
    incs = re.findall(r'(?m)^\s*#\s*include\s*([<"][^">]+[">])', open(src, errors="replace").read())
    print("includes   %s" % (" ".join(incs) or "none"))
    print("\n----- current source -----\n%s\n--------------------------\n" % body(src, va))
    print("next: edit the function in %s (any other function, header, constructor or class layout may change too),\n"
          "      then: .venv/bin/python tools/contrib/check.py 0x%08x\n"
          "      Rules and the full loop: AGENTS.md" % (os.path.relpath(src, ROOT), va))
    return 0


if __name__ == "__main__":
    sys.exit(main())
