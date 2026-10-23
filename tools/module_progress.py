#!/usr/bin/env python3
"""Per-module progress, and the module make-up of a batch.

usage: module_progress.py                 table of every top-level module (docs/modules.md): functions, code size,
                                          objects, byte-exact (and how many of those are synth), complete, partial, no row
       module_progress.py --batch <name>  for work/batches/<name>.json: each module's functions in the batch next to
                                          its unrecorded functions overall, so a batch that silently leaves a module out
                                          is visible when it is built (2026-10-23: a "SPGonzago" substring filter kept
                                          the whole game module out of gold2-gold5 unnoticed)

Sources: work/migrate/modmap.json (module of each function) and every bookkeeping file: manifests under match/slices
and src/game, match/manifest.txt, match/synth/*.manifest and match/clones.txt (byte-exact), nonmatching.txt, partial.txt.
"""
import argparse, json, glob, re, collections, os, sys
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)
ap = argparse.ArgumentParser(); ap.add_argument("--batch"); A = ap.parse_args()
SOUND = ("cmn", "plugins", "mix", "decoders", "ealayer30", "ealayer31")   # EA's sound library, one row
mm = json.load(open("work/migrate/modmap.json"))["functions"]
def va(x): return x.lower().replace("0x","").zfill(8)
size = {va(v): (m or {}).get("size") or 0 for v, m in mm.items()}
st = {}
def mark(v, k, rank={"exact":3, "nonexact":2, "partial":1}):
    if rank[k] > rank.get(st.get(v), 0): st[v] = k
synth = set()
for f in glob.glob("match/slices/*/manifest.txt") + glob.glob("src/game/**/manifest.txt", recursive=True) + ["match/manifest.txt"] + glob.glob("match/synth/*.manifest"):
    if not os.path.exists(f): continue
    for l in open(f, errors="replace"):
        p = l.split("#",1)[0].split()
        if len(p) >= 3 and re.fullmatch(r"(0x)?[0-9a-fA-F]{6,8}", p[2]):
            mark(va(p[2]), "exact")
            if "/synth/" in f: synth.add(va(p[2]))
for l in open("match/clones.txt", errors="replace"):
    p = l.split("#",1)[0].split()
    if len(p) >= 3 and re.fullmatch(r"(0x)?[0-9a-fA-F]{6,8}", p[2]): mark(va(p[2]), "exact")
for kind, k in (("nonmatching","nonexact"), ("partial","partial")):
    for f in glob.glob("match/slices/*/%s.txt" % kind) + glob.glob("src/game/**/%s.txt" % kind, recursive=True):
        for l in open(f, errors="replace"):
            p = l.split()
            if p and re.fullmatch(r"(0x)?[0-9a-fA-F]{6,8}", p[0]): mark(va(p[0]), k)
D = collections.defaultdict(collections.Counter); objs = collections.defaultdict(set)
for v, m in mm.items():
    mod = (m or {}).get("module") or ""
    top = mod.split("/")[0] if "/" in mod else (mod or "(unassigned)")
    v8 = va(v); D[top]["n"] += 1; D[top]["bytes"] += size.get(v8, 0); D[top][st.get(v8, "none")] += 1
    if v8 in synth: D[top]["synth"] += 1
    objs[top].add(os.path.basename(mod))
def top_of(mod):
    t = mod.split("/")[0] if "/" in mod else (mod or "(unassigned)")
    return "EA sound" if t in SOUND else t
if A.batch:
    vas = {va(v) for e in json.load(open("work/batches/%s.json" % A.batch)) for v in e["vas"]}
    inb, pool = collections.Counter(), collections.Counter()
    for v, m in mm.items():
        t = top_of((m or {}).get("module") or "")
        if va(v) in vas: inb[t] += 1
        if st.get(va(v)) is None: pool[t] += 1
    print("%-22s %8s %8s %6s" % ("module", "in batch", "no row", "share"))
    for t in sorted(set(inb) | set(pool), key=lambda t: -pool[t]):
        flag = "   <- none offered" if pool[t] >= 100 and not inb[t] else ""
        print("%-22s %8d %8d %5.0f%%%s" % (t, inb[t], pool[t], 100.0 * inb[t] / max(1, pool[t]), flag))
    print("batch functions without a module-map entry: %d" % len(vas - {va(v) for v in mm}))
    sys.exit(0)
G = collections.Counter()
for t in SOUND: G.update(D.pop(t, collections.Counter())); objs["EA sound"] |= objs.pop(t, set())
D["EA sound"] = G
for top, c in sorted(D.items(), key=lambda kv: -kv[1]["bytes"]):
    print("%-22s %6d %5.2f %4d | exact %5d (synth %5d) nonexact %5d partial %5d none %5d" % (top, c["n"], c["bytes"]/1e6, len(objs[top]), c["exact"], c["synth"], c["nonexact"], c["partial"], c["none"]))
