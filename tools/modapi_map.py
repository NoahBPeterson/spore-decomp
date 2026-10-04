#!/usr/bin/env python3
"""Carry Spore ModAPI names (github.com/emd4600/Spore-ModAPI, for the 2017 Steam build) over to our 2024 build.

usage: modapi_map.py <out.json>
The 2024 exe is a recompile of nearly the same code, so addresses differ by a small, piecewise-constant
shift (e.g. -0x320 across the whole DBPF module). Anchors are ModAPI entries whose method name equals the
dev-PDB name of exactly one retail function within +-256 KB. Every ModAPI address is then shifted by the
offset that most of its nearest anchors agree on, and kept only if it lands on a retail function start.
Precision is measured leave-one-out on the anchors and printed.
Output: {retail_va: {"name", "modapi_va", "offset", "agree", "pdb_name"?}}
"""
import bisect, collections, glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)
M = W("work/ext/Spore-ModAPI")


def modapi_entries():
    e = {}
    x = open(os.path.join(M, "SDKtoGhidra/SporeGhidra_march2017.xml"), errors="ignore").read()
    for m in re.finditer(r'<FUNCTION ADDRESS="([0-9a-f]+)" NAME="([^"]+)"', x):
        e.setdefault(int(m.group(1), 16), m.group(2))
    for line in open(os.path.join(M, "SDKtoGhidra/additional_march2017.txt"), errors="ignore"):
        m = re.match(r"\s*0x([0-9a-fA-F]+)=(\S+)", line)
        if m:
            e.setdefault(int(m.group(1), 16), m.group(2))
    for f in glob.glob(os.path.join(M, "Spore ModAPI/**/*.cpp"), recursive=True):
        src = open(f, errors="ignore").read()
        for m in re.finditer(r"DefineAddress\((\w+),\s*SelectAddress\(0x[0-9a-fA-F]+,\s*0x([0-9a-fA-F]+)\)", src):
            pre = src[:m.start()]
            ns = re.findall(r"namespace\s+Addresses\((\w+)\)|namespace\s+(\w+)Addresses", pre)
            cls = [a or b for a, b in ns][-1] if ns else ""
            e.setdefault(int(m.group(2), 16), (cls + "::" if cls else "") + m.group(1))
    return e


def main(outp):
    ent = modapi_entries()
    ret = json.load(open(W("work/xmatch/retail.json")))
    starts = sorted(int(k, 16) for k in ret)
    sset = set(starts)
    pdb = json.load(open(W("symbols/pdb_names.json")))
    byname = collections.defaultdict(list)
    for k, v in pdb.items():
        byname[v["name"].split("::")[-1]].append(int(k, 16))
    anchors = []  # (modapi_va, offset)
    for a, n in ent.items():
        last = n.split("::")[-1]
        if last.startswith("func") or len(last) < 5:
            continue
        c = [x for x in byname.get(last, []) if abs(x - a) < 0x40000]
        if len(c) == 1:
            anchors.append((a, c[0] - a))
    anchors.sort()
    av = [a for a, _ in anchors]

    def predict(a, exclude=None, k=6, need=4):
        i = bisect.bisect_left(av, a)
        cand = [j for j in range(max(0, i - k), min(len(av), i + k)) if av[j] != exclude]
        cand.sort(key=lambda j: abs(av[j] - a))
        # the two nearest anchors on each side must all agree (the shift is piecewise constant)
        lo = [j for j in range(i - 1, -1, -1) if av[j] != exclude][:2]
        hi = [j for j in range(i, len(av)) if av[j] != exclude][:2]
        near = [anchors[j][1] for j in lo + hi if abs(av[j] - a) < 0x20000]
        if len(near) < 3 or len(set(near)) != 1:
            return None, len(near)
        return near[0], len(near)

    # leave-one-out precision on anchors
    ok = bad = miss = 0
    for a, o in anchors:
        p, n = predict(a, exclude=a)
        if p is None or (a + p) not in sset:
            miss += 1
        elif p == o:
            ok += 1
        else:
            bad += 1
    print("anchors %d; leave-one-out: correct %d, wrong %d, no prediction %d" % (len(anchors), ok, bad, miss))
    out = {}
    for a, n in sorted(ent.items()):
        p, agree = predict(a)
        if p is None or (a + p) not in sset:
            continue
        r = "%08x" % (a + p)
        d = {"name": n, "modapi_va": "%08x" % a, "offset": p, "agree": agree}
        if r in pdb:
            d["pdb_name"] = pdb[r]["name"]
        out[r] = d
    json.dump(out, open(outp, "w"), indent=0, sort_keys=True)
    same = sum(1 for v in out.values() if "pdb_name" in v and v["pdb_name"].split("::")[-1] == v["name"].split("::")[-1])
    diff = sum(1 for v in out.values() if "pdb_name" in v) - same
    print("ModAPI entries %d -> mapped %d (new names %d; agree with PDB name %d, disagree %d)" % (
        len(ent), len(out), sum(1 for v in out.values() if "pdb_name" not in v), same, diff))


if __name__ == "__main__":
    main(*sys.argv[1:2])
