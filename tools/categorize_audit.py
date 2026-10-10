#!/usr/bin/env python3
"""Audit slice bookkeeping: every function a slice is responsible for must be in exactly one of
manifest.txt (byte-exact) / nonmatching.txt (equivalent) / partial.txt (incomplete).

Why: run_all.py reads only manifest.txt (byte-exact verification) and batch.py/equiv.py read only
nonmatching.txt (equivalence verification). A VA an agent forgot to categorise, put in two files, or
dropped is invisible to BOTH pipelines — it silently disappears. This reconciles the three files
against each other, against the function's source markers, and against the batch's target VA set.

usage: categorize_audit.py [--batch NAME] [--all] [slice-id ...]      (default --all)
Findings (exit 1 if any ERROR):
  IN-MULTIPLE-FILES      ERROR  a VA appears in more than one of manifest/nonmatching/partial
                                (progress double-counts it and the authoritative verdict is ambiguous)
  TARGET-UNCATEGORISED   ERROR  a batch "vas" VA is in none of the three files (never done/listed)
  WRITTEN-NOT-CATEGORISED ERROR a "// @ 0xVA" marker in this slice's source is in none of the files
  CATEGORISED-NOT-WRITTEN WARN  a listed VA has no source marker in this slice or anywhere else
                                (stale/typo);  a VA marked in ANOTHER slice is reported as CROSS-SLICE
-v prints one line per slice. Markers are the `// @ 0xVA` convention; slices that name real symbols
instead of markers (run_all resolves symbols, markers are not required) simply have no marker rows.
"""
import argparse, glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)
MARK = re.compile(r"//\s*@\s*(?:0x)?([0-9a-fA-F]{6,8})\b")
TEXTS = (".cpp", ".c", ".cc", ".h", ".hpp", ".inl")
HEX8 = re.compile(r"^(?:0x)?([0-9a-fA-F]{6,8})$")


def z(v):
    return v.lower().replace("0x", "").zfill(8)


def markers_in(paths):
    out = set()
    for f in paths:
        if os.path.splitext(f)[1].lower() not in TEXTS:
            continue
        try:
            txt = open(f, errors="ignore").read()
        except OSError:
            continue
        for m in MARK.finditer(txt):
            out.add(z(m.group(1)))
    return out


def file_vas(path, manifest):
    out = set()
    if not os.path.exists(path):
        return out
    for l in open(path, errors="ignore"):
        if l.lstrip().startswith("#"):
            continue
        p = l.split("#", 1)[0].split()
        if manifest:
            if len(p) >= 3:
                m = HEX8.match(p[2])
                if m:
                    out.add(z(m.group(1)))
        elif p:
            m = HEX8.match(p[0])
            if m:
                out.add(z(m.group(1)))
    return out


ap = argparse.ArgumentParser()
ap.add_argument("args", nargs="*")
ap.add_argument("--batch")
ap.add_argument("--all", action="store_true")
ap.add_argument("-v", action="store_true")
ap.add_argument("--gate", action="store_true",
                help="commit-gate mode: only TARGET-UNCATEGORISED / IN-MULTIPLE-FILES are errors "
                     "(functions invisible to run_all AND the equivalence backlog, or double-counted); "
                     "WRITTEN-NOT-CATEGORISED is reported but does not fail")
a = ap.parse_args()

if a.batch:
    b = json.load(open(W("work/batches", a.batch + ".json")))
    ids = sorted({r["id"] for r in b if isinstance(r, dict) and "id" in r})
elif a.args:
    ids = a.args
else:
    ids = sorted(os.path.basename(d) for d in glob.glob(W("match/slices", "*")))
    a.all = True

# global marker ownership: VA -> set of slices whose source marks it (for cross-slice detection),
# and the repo-wide set of categorised VAs (a marker here but categorised in a sibling is tracked).
owner = {}
cat_global = set()
_all_dirs = glob.glob(W("match/slices", "*"))
for d in _all_dirs:
    sid = os.path.basename(d)
    for va in markers_in(glob.glob(os.path.join(d, "*"))):
        owner.setdefault(va, set()).add(sid)
    cat_global |= file_vas(os.path.join(d, "manifest.txt"), True)
    cat_global |= file_vas(os.path.join(d, "nonmatching.txt"), False)
    cat_global |= file_vas(os.path.join(d, "partial.txt"), False)

# batch target set per slice (records with a real "vas"; shards use "test_vas")
tgt = {}
for f in glob.glob(W("work/batches", "*.json")):
    try:
        b = json.load(open(f))
    except Exception:
        continue
    if not isinstance(b, list):
        continue
    for r in b:
        if isinstance(r, dict) and "id" in r and "vas" in r:
            tgt.setdefault(r["id"], set()).update(z(v) for v in r["vas"])

errors = 0
warns = 0
for sid in ids:
    d = W("match/slices", sid)
    man = file_vas(os.path.join(d, "manifest.txt"), True)
    non = file_vas(os.path.join(d, "nonmatching.txt"), False)
    par = file_vas(os.path.join(d, "partial.txt"), False)
    own = markers_in(glob.glob(os.path.join(d, "*")))
    cat = man | non | par
    overlap = (man & non) | (man & par) | (non & par)
    uncat = own - cat_global
    uncovered = tgt.get(sid, set()) - cat
    stale = {v for v in cat if v not in own and v not in owner}
    cross = {v for v in cat if v not in own and v in owner}
    bad = bool(overlap or uncovered) if a.gate else bool(overlap or uncat or uncovered)
    warn = bool(stale or (uncat if a.gate else False))
    errors += bad
    warns += warn
    if bad or warn or a.v:
        tag = "ERROR" if bad else ("WARN" if warn else "ok")
        print("%s %s written=%d man=%d non=%d par=%d" % (tag, sid, len(own), len(man), len(non), len(par)))
        for label, s in (("IN-MULTIPLE-FILES", overlap), ("TARGET-UNCATEGORISED", uncovered),
                         ("WRITTEN-NOT-CATEGORISED", uncat), ("CATEGORISED-NOT-WRITTEN", stale),
                         ("CROSS-SLICE-MARKER", cross)):
            if s:
                print("    %-24s %d: %s" % (label, len(s), " ".join(sorted(s)[:20])))

print("%d slices: %d ERROR, %d WARN (markers in %d slices)" % (len(ids), errors, warns, len(owner)))
sys.exit(1 if errors else 0)
