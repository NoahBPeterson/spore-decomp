#!/usr/bin/env python3
"""Semantic class/struct consistency + canonical registry.

Unlike typecheck.py (which diffs raw text), this reads the `// +0xNN` offset annotations the slices
carry and compares the *offsets of members that two slices both declare*. That finds real layout
contradictions, not the benign "this slice only declares the members it needs" differences.

usage: type_registry.py [--write work/opencode/type_registry.json] [--examples 20]

Outputs:
  - a contradiction list: same type, same member name, different offsets in different slices
  - a canonical registry (majority offset per member) written as JSON for the hot shared types
"""
import argparse, collections, glob, json, os, re, sys

ap = argparse.ArgumentParser()
ap.add_argument("--write", default="work/opencode/type_registry.json")
ap.add_argument("--examples", type=int, default=20)
a = ap.parse_args()
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
os.chdir(ROOT)

DEF = re.compile(r"\b(struct|class)\s+(\w+)\s*(?::[^{;]*)?\{")
OFF = re.compile(r"//\s*\+?\s*0x([0-9a-fA-F]+)\b")
IDENT = re.compile(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*;")


def bodies(text):
    for m in DEF.finditer(text):
        depth, j = 0, m.end() - 1
        while j < len(text):
            if text[j] == "{":
                depth += 1
            elif text[j] == "}":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        yield m.group(2), text[m.end():j]


# name -> member -> offset -> set(slices)
reg = collections.defaultdict(lambda: collections.defaultdict(lambda: collections.defaultdict(set)))
for p in glob.glob("match/slices/*/*.cpp"):
    sid = os.path.basename(os.path.dirname(p))
    try:
        text = open(p, errors="replace").read()
    except OSError:
        continue
    for name, body in bodies(text):
        for line in body.splitlines():
            mo = OFF.search(line)
            if not mo:
                continue
            ids = IDENT.findall(line.split("//")[0])
            if not ids:
                continue
            member = ids[-1]
            off = int(mo.group(1), 16)
            reg[name][member][off].add(sid)

contradictions = []
for name, mem in reg.items():
    for member, offs in mem.items():
        if len(offs) > 1:
            contradictions.append((name, member, {("%#x" % o): sorted(s)[:3] for o, s in offs.items()}))

# canonical registry: majority offset per member, for types seen in >=5 slices
canon = {}
for name, mem in reg.items():
    slices = set()
    for offs in mem.values():
        for s in offs.values():
            slices |= s
    if len(slices) < 5:
        continue
    table = {}
    for member, offs in mem.items():
        best = max(offs.items(), key=lambda kv: len(kv[1]))
        table[member] = {"off": "%#x" % best[0], "votes": len(best[1])}
    canon[name] = {"slices": len(slices), "members": dict(sorted(table.items(), key=lambda kv: int(kv[1]["off"], 16)))}

print("types with offset annotations: %d" % len(reg))
print("layer contradictions (same member, different offset): %d" % len(contradictions))
for name, member, offs in contradictions[: a.examples]:
    print("  %-34s %-22s %s" % (name, member, offs))
print("canonical registry entries (>=5 slices): %d" % len(canon))
os.makedirs(os.path.dirname(a.write), exist_ok=True)
json.dump(canon, open(a.write, "w"), indent=1)
print("wrote %s" % a.write)
sys.exit(1 if contradictions else 0)
