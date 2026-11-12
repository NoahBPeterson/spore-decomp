#!/usr/bin/env python3
"""Which manifests a change can affect: those listing a changed source, those whose sources reach a changed file
through #include (quoted or angle, resolved next to the including file, then in the row's /I directories, then
match/include, match/include/vc71 for /vc71 rows), and changed manifests themselves.

usage: affected.py CHANGED_PATH...        (repo-relative; prints one manifest path per line)
       affected.py --from-file LIST
"""
import argparse, glob, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))
import run_all as R     # noqa: E402

INC = re.compile(r'^\s*#\s*include\s*[<"]([^">]+)[">]', re.M)


def all_manifests():
    """manifest.txt files and the proven-equivalent lists (equivalent.txt) the gate also checks"""
    return R.manifests() + sorted(glob.glob(os.path.join(ROOT, "src", "game", "**", "manifest.txt"), recursive=True)) \
        + sorted(glob.glob(os.path.join(ROOT, "match", "slices", "*", "equivalent.txt")) +
                 glob.glob(os.path.join(ROOT, "src", "game", "**", "equivalent.txt"), recursive=True))


def include_dirs(flags):
    out = []
    for f in R.resolve_flags(list(flags)):
        if f.startswith("/I"):
            p = f[2:]
            out.append(p[2:].replace("\\", "/") if p.startswith("Z:") else os.path.join(ROOT, p))
    out.append(os.path.join(ROOT, "match", "include"))
    if "/vc71" in flags:
        out.append(os.path.join(ROOT, "match", "include", "vc71"))
    return out


_closure = {}


def closure(src, dirs):
    key = (src, tuple(dirs))
    if key in _closure:
        return _closure[key]
    seen, todo = set(), [os.path.normpath(src)]
    while todo:
        f = todo.pop()
        if f in seen:
            continue
        seen.add(f)
        try:
            text = open(f, "rb").read().decode("latin-1")
        except OSError:
            continue
        for name in INC.findall(text):
            for d in [os.path.dirname(f)] + dirs:
                c = os.path.normpath(os.path.join(d, name))
                if os.path.isfile(c):
                    todo.append(c)
                    break
    _closure[key] = seen
    return seen


def affected(changed):
    changed = {os.path.normpath(os.path.join(ROOT, c)) for c in changed}
    out = []
    for m in all_manifests():
        if os.path.normpath(m) in changed:
            out.append(m)
            continue
        # an LTCG stub file (ltcg/<va>.cpp) or a proof bundle (equivalent/<va>.json) next to the list
        d = os.path.dirname(os.path.normpath(m))
        if any(c.startswith(os.path.join(d, "ltcg") + os.sep) or c.startswith(os.path.join(d, "equivalent") + os.sep)
               for c in changed):
            out.append(m)
            continue
        for src, _sym, _va, flags in R.read_rows([m], ""):
            if closure(os.path.join(ROOT, "match", src), include_dirs(flags)) & changed:
                out.append(m)
                break
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("paths", nargs="*")
    ap.add_argument("--from-file")
    a = ap.parse_args()
    paths = list(a.paths) + ([l.strip() for l in open(a.from_file) if l.strip()] if a.from_file else [])
    for m in affected(paths):
        print(os.path.relpath(m, ROOT))


if __name__ == "__main__":
    main()
