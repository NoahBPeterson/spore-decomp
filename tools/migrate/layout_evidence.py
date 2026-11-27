#!/usr/bin/env python3
"""Retail layout evidence for a class, from byte-exact functions that symbols/pdb_names.json names Class::Method.

usage: layout_evidence.py [--names symbols/pdb_names.json] SP::cAppModeEditorBase [more classes]
For each such function: its manifest row gives the source file and the mangled symbol; the symbol's class is the
`this` type the source used (often a stand-in struct). That struct's definition is parsed with sliceviews' parser and
layout evaluator; the members the function's body names are retail-proven offsets of the class (the function is
byte-exact, and it is the class's method). They are compared with the header's re-laid members
(src/game/include/<ns>/<class>.h, "// 0x<offset> <provenance>" comments).

Two reports per class: every proven offset against the header member there, and, for stand-in members that carry a
header member's name, the shift (stand-in offset - header offset). A run of equal shifts locates a retail-only or grown
member; single outliers are usually a stand-in member an agent named wrongly (the offset is proven, its name is not).
Fixes go into tools/migrate/layout_overrides.json ("insert" / "remove"), never into the generated header.
"""
import collections, glob, json, os, re, sys
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
os.chdir(ROOT)
sys.path[:0] = [os.path.join(ROOT, "tools", "migrate"), os.path.join(ROOT, "tools", "ci"), os.path.join(ROOT, "tools", "matching")]
import sliceviews as SV
import run_all

args = sys.argv[1:]
names_path = "symbols/pdb_names.json"
if args[:1] == ["--names"]:
    names_path, args = args[1], args[2:]
if not args:
    sys.exit(__doc__)
names = json.load(open(names_path))
classes = args

# byte-exact rows: va -> (source path, symbol)
known = {l.split()[0].lower() for l in open("tools/ci/known_failures.txt") if l.strip() and not l.startswith("#")}
manifests = run_all.manifests() + sorted(glob.glob("src/game/**/manifest.txt", recursive=True))
rows = {}
for mf in manifests:
    for line in open(mf):
        p = line.split()
        if len(p) >= 3 and not line.startswith("#") and re.fullmatch(r"[0-9a-fA-F]{8}", p[2]):
            src = os.path.normpath(os.path.join("match", p[0]))
            rows.setdefault(p[2].lower(), (src, p[1], mf))

def sym_class(sym):
    m = re.match(r"\?([^@?]+)@([^@]+)@", sym)
    return m.group(2) if m else None

parsed = {}
def parse(src):
    if src in parsed:
        return parsed[src]
    ctx, fails = SV.Ctx(), []
    files = [src]
    d = os.path.dirname(src)
    files = sorted(glob.glob(os.path.join(d, "*.h"))) + files
    srcs, defs = [], []
    for f in files:
        try:
            sr = SV.Src(f, os.path.relpath(f, ROOT))
        except Exception:
            continue
        p = SV.Parser(os.path.basename(d), ctx, fails)
        try:
            p.scan(sr)
        except RecursionError:
            pass
        defs += p.defs
        srcs.append((sr, p.spans))
    parsed[src] = (defs, SV.sections(srcs))
    return parsed[src]

def header_members(cls):
    short = cls.split("::")[-1]
    hp = os.path.join("src/game/include", *cls.split("::")[:-1], short + ".h")
    if not os.path.exists(hp):
        return hp, {}
    t = open(hp).read().splitlines()
    out, inside, depth = {}, False, 0
    for l in t:
        if re.match(r"\s*class\s+%s\b.*\{" % re.escape(short), l):
            inside, depth = True, 0
        if not inside:
            continue
        depth += l.count("{") - l.count("}")
        m = re.match(r"  (?! )([^/(]*?)\s+(\w+)(\[[^\]]*\])?;\s*// 0x([0-9a-f]+)\s*(\S*)", l)
        if m:
            out[int(m.group(4), 16)] = (m.group(2), m.group(1).strip(), m.group(5))
        if depth <= 0 and "};" in l:
            break
    return hp, out

for cls in classes:
    pref = cls + "::"
    vas = sorted(r for r, v in names.items() if v["name"].startswith(pref) and r in rows and r not in known)
    hp, hm = header_members(cls)
    ev = collections.defaultdict(set)     # offset -> {(size, stand-in member, va)}
    used = 0
    for va in vas:
        src, sym, mf = rows[va]
        sc = sym_class(sym)
        if not sc or not os.path.exists(src):
            continue
        defs, secs = parse(src)
        ids = secs.get(va, set())
        cand = [d for d in defs if d["name"] == sc and d.get("size_known")]
        if not cand:
            continue
        d = cand[0]
        used += 1
        for m in d["members"]:
            if m["pad"] or m["name"] not in ids:
                continue
            ev[m["offset"]].add((m["size"], m["name"], va))
    agree = conflict = new = 0
    lines = []
    for off in sorted(ev):
        sizes = {s for s, _, _ in ev[off]}
        h = hm.get(off)
        # a header member covering this offset?
        cover = [(o, x) for o, x in hm.items() if o <= off < o + 4 and o != off]
        if h:
            verdict = "agrees with %s (%s)" % (h[0], h[2]); agree += 1
        elif cover:
            verdict = "CONFLICT: inside header member %s at 0x%x" % (cover[0][1][0], cover[0][0]); conflict += 1
        else:
            verdict = "no header member here"; new += 1
        lines.append("  0x%03x size %s  %-28s %s  (%d fn)" % (off, "/".join(map(str, sorted(sizes))),
                     ",".join(sorted({n for _, n, _ in ev[off]}))[:28], verdict, len({v for _, _, v in ev[off]})))
    print("== %s: %d named byte-exact functions, %d via a stand-in; %d offsets proven: %d agree, %d conflict, %d not in header (%s, %d members)"
          % (cls, len(vas), used, len(ev), agree, conflict, new, hp, len(hm)))
    print("\n".join(lines))

# name-based shifts: a stand-in member whose name is a header member's name
print("\n== by name (stand-in member name = header member name): stand-in offset - header offset")
for cls in classes:
    pref = cls + "::"
    hp, hm = header_members(cls)
    byname = {v[0]: o for o, v in hm.items()}
    out = []
    for va in sorted(r for r, v in names.items() if v["name"].startswith(pref) and r in rows and r not in known):
        src, sym, mf = rows[va]
        sc = sym_class(sym)
        if not sc or not os.path.exists(src):
            continue
        defs, secs = parse(src)
        ids = secs.get(va, set())
        for d in [d for d in defs if d["name"] == sc and d.get("size_known")][:1]:
            for m in d["members"]:
                if not m["pad"] and m["name"] in byname and m["name"] in ids:
                    out.append((byname[m["name"]], m["offset"], m["name"], va))
    print(cls)
    for ho, so, n, va in sorted(set(out)):
        print("  header 0x%03x  stand-in 0x%03x  shift %+d  %s  (%s)" % (ho, so, so - ho, n, va))
