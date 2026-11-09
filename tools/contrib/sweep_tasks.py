#!/usr/bin/env python3
"""sweep_tasks: does every function task.py --list offers at least compile, with the flags check.py would use?

  .venv/bin/python tools/contrib/sweep_tasks.py [--max-size N] [--jobs N] [--out report.txt] [--write-blocked]

A maintainer check, not a contributor step. It runs before inviting contributors and after large merges. A newcomer's first
check.py run should show what differs, not a compile error they did not cause. Each distinct (source, flags) pair is
compiled once. Prints each failing pair with how many listed functions it blocks and the first error line.
--write-blocked writes those functions to tools/contrib/blocked.txt, which task.py --list leaves out (run it on a clean
clone: files under work/ would hide failures).
"""
import argparse, collections, os, re, sys
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path[:0] = [os.path.dirname(os.path.abspath(__file__)), os.path.join(ROOT, "tools", "difftest"),
                os.path.join(ROOT, "tools", "matching"), os.path.join(ROOT, "tools", "ci")]
import task as T            # noqa: E402
import slice as S           # noqa: E402

MARK = re.compile(r"(?mi)^//\s*@\s*0x0*([0-9a-f]+)\b")


def marker_index():
    """va -> (source, ident), with task.locate's precedence (src/game before match/slices)"""
    out = {}
    for f in T.sources():
        rel = os.path.relpath(f, ROOT)
        if rel.startswith("src" + os.sep):
            stem = os.path.splitext(os.path.basename(f))[0]
            ident = stem if S.module_dir(stem) else "%s/%s" % (os.path.basename(os.path.dirname(f)), stem)
        else:
            ident = rel.split(os.sep)[2]
        for m in MARK.finditer(open(f, errors="replace").read()):
            va = int(m.group(1), 16)
            if va not in out or (rel.startswith("src" + os.sep) and not out[va][0].startswith(os.path.join(ROOT, "src"))):
                out[va] = (f, ident)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--max-size", type=int, default=256)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--out")
    ap.add_argument("--write-blocked", action="store_true")
    a = ap.parse_args()
    idx = marker_index()
    groups, nomarker = collections.defaultdict(list), 0
    for size, va, diff, where, reason in T.open_work(a.max_size):
        if va not in idx:
            nomarker += 1
            continue
        src, ident = idx[va]
        flags, _how = S.choose_flags(ident, va)
        groups[(src, tuple(flags))].append(va)

    def build(key):
        obj, log = S.compile_obj(key[0], list(key[1]))
        if obj:
            return key, None
        err = next((l.strip() for l in (log or "").splitlines() if re.search(r"error|fatal", l, re.I)), (log or "").strip()[-200:])
        return key, err

    fails = []
    with ThreadPoolExecutor(a.jobs) as ex:
        for key, err in ex.map(build, sorted(groups)):
            if err:
                fails.append((len(groups[key]), key, err))
    total = sum(len(v) for v in groups.values())
    blocked = sum(n for n, _k, _e in fails)
    lines = ["%d listed functions in %d (source, flags) pairs; %d pairs fail to compile, blocking %d functions; "
             "%d listed functions have no marker" % (total, len(groups), len(fails), blocked, nomarker)]
    for n, (src, flags), err in sorted(fails, reverse=True):
        lines.append("%5d  %s  [%s]\n       %s" % (n, os.path.relpath(src, ROOT), " ".join(flags), re.sub(r"^.*?\.(?:cpp|c|h)\(\d+\) : ", "", err)[:200]))
    text = "\n".join(lines) + "\n"
    print(text, end="")
    if a.write_blocked:
        with open(os.path.join(ROOT, "tools", "contrib", "blocked.txt"), "w", encoding="utf-8", newline="\n") as f:
            f.write("# Functions task.py --list leaves out: their source does not compile on a clean clone with the flags\n"
                    "# check.py would use (tools/contrib/sweep_tasks.py --write-blocked).  Fixing one is maintainer work.\n")
            for n, (src, flags), err in sorted(fails, key=lambda x: x[1]):
                why = re.sub(r"^.*?\.(?:cpp|c|h)\(\d+\) : ", "", err)[:160]
                for va in sorted(groups[(src, flags)]):
                    f.write("%08x  %s: %s\n" % (va, os.path.relpath(src, ROOT).replace(os.sep, "/"), why))
    if a.out:
        open(a.out, "w", encoding="utf-8").write(text)
    return 1 if fails else 0


if __name__ == "__main__":
    sys.exit(main())
