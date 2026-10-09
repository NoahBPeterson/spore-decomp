#!/usr/bin/env python3
"""Report duplicated / divergent class+struct definitions across match/slices/*/*.cpp.

usage: typecheck.py [--examples N]

Byte-exact slices each re-declare the types they need, so the same class name can drift between
slices. This scans every slice, extracts each `struct/class Name { ... }` body, normalizes it, and
groups by name:
  - SAME  : one normalized body across all slices that define it (no drift)
  - DRIFT : the same name has 2+ different bodies (a layout/signature disagreement)
Exit status is non-zero if any DRIFT is found, so it can gate a daily/commit check.
"""
import argparse, collections, glob, os, re, sys

ap = argparse.ArgumentParser()
ap.add_argument("--examples", type=int, default=15)
a = ap.parse_args()

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
os.chdir(ROOT)


def defs(text):
    out = []
    for m in re.finditer(r"\b(struct|class)\s+(\w+)\s*(?::[^{;]*)?\{", text):
        name = m.group(2)
        depth = 0
        j = m.end() - 1
        while j < len(text):
            if text[j] == "{":
                depth += 1
            elif text[j] == "}":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        out.append((name, text[m.end():j]))
    return out


def norm(body):
    body = re.sub(r"//[^\n]*", "", body)
    body = re.sub(r"/\*.*?\*/", "", body, flags=re.S)
    return " ".join(re.findall(r"\w+|[{}();,<>=*&:\[\]]", body))


by = collections.defaultdict(lambda: collections.defaultdict(set))  # name -> body -> slices
for p in glob.glob("match/slices/*/*.cpp"):
    sid = os.path.basename(os.path.dirname(p))
    try:
        text = open(p, errors="replace").read()
    except OSError:
        continue
    for name, body in defs(text):
        by[name][norm(body)].add(sid)

multi = {n: v for n, v in by.items() if sum(len(s) for s in v.values()) >= 2}
drift = {n: v for n, v in multi.items() if len(v) >= 2}
same = {n: v for n, v in multi.items() if len(v) == 1}

print("type names defined in >=2 slices: %d" % len(multi))
print("  consistent (1 distinct body): %d" % len(same))
print("  DRIFT (2+ distinct bodies):   %d" % len(drift))
print("total slice-type definitions: %d" % sum(len(s) for v in by.values() for s in v.values()))
print("\ntop drift (name: #bodies / #slices):")
for n, v in sorted(drift.items(), key=lambda kv: -(len(kv[1]) + sum(len(s) for s in kv[1].values())))[: a.examples]:
    print("  %-40s bodies=%d slices=%d" % (n, len(v), len(set().union(*v.values()))))
sys.exit(1 if drift else 0)
