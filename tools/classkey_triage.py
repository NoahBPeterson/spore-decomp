#!/usr/bin/env python3
"""Triage `struct` vs `class` in our C++ against what the original source used.

usage: classkey_triage.py [paths...] [--tsv out.tsv] [--all]
       (default paths: match/slices src/game; prints a per-file summary of mismatches)

The class-key is not a style choice we can infer from convention: the 2008 dev PDB records it per type
(LF_CLASS vs LF_STRUCTURE, `kind` in work/devbuild/types.json), and MSVC mangles it into every symbol that
takes the type as a parameter (`PAV<name>@` = class, `PAU<name>@` = struct). EA did not follow the
"struct = plain data" convention: cSPVector3 is a struct with a base, EA::ResourceMan::Key is a class.

For every struct/class *definition* (with a body) in our sources, the verdict is:
  MISMATCH  the PDB type with the same fully qualified name used the other keyword: fix it
  mismatch? only a type with the same short name (any namespace) or mangled-name uses disagree; this may
            be an unrelated type (squish::Vec3 vs our Vec3), so check the namespace before changing it
  ok        the original used the same keyword
  conflict  the PDB/mangled names disagree for this short name (several types share it): check by hand
  unknown   no record of the name (placeholder types such as `S`, `TC_x`, `FUN_...` thunk structs);
            the hint column says `class?` when it is polymorphic (virtual members or a base list)

Changing the keyword changes mangled names (U <-> V) of every function that takes the type as a parameter,
so manifest rows naming such a symbol must be updated in the same edit; run_all.py will report the symbol
missing otherwise. Matching the original's keyword makes our mangled names agree with the PDB's.
"""
import argparse, collections, glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)

DEF = re.compile(r"(?m)^[ \t]*(?:template\s*<[^;{]*?>\s*)?(struct|class)\s+(?:__declspec\([^)]*\)\s*)?"
                 r"((?:[A-Za-z_]\w*::)*[A-Za-z_]\w*)\s*(?:final\s*)?(:[^;{]*)?\{")
# pointer/reference/const-qualified uses of a named type inside an MSVC mangled name: P/Q/R/S/A + A/B + U/V + name@
MANGLED_USE = re.compile(r"(?:[PQRSA][ABCD])([UV])([A-Za-z_]\w*)@")


def short(name):
    return re.sub(r"<.*", "", name).split("::")[-1]


def load_truth():
    """short name -> Counter of keywords the original used."""
    pdb = collections.defaultdict(collections.Counter)
    full = {}
    for name, t in json.load(open(W("work/devbuild/types.json")))["structs"].items():
        if t.get("kind") in ("struct", "class"):
            pdb[short(name)][t["kind"]] += 1
            full.setdefault(re.sub(r"<.*", "", name), collections.Counter())[t["kind"]] += 1
    mang = collections.defaultdict(collections.Counter)
    names = []
    try:
        names += [f.get("name", "") for f in json.load(open(W("work/devbuild/symbols.json"))).get("functions", [])]
    except (OSError, ValueError):
        pass
    for f in glob.glob(W("symbols", "*.txt")):
        for l in open(f, errors="replace"):
            p = l.split("#", 1)[0].split()
            if len(p) >= 2:
                names.append(p[1])
    for n in names:
        if n.startswith("?"):
            for kv, nm in MANGLED_USE.findall(n):
                mang[nm]["class" if kv == "V" else "struct"] += 1
    return pdb, mang, full


def strip_comments(src):
    src = re.sub(r"/\*.*?\*/", lambda m: "\n" * m.group(0).count("\n"), src, flags=re.S)
    return re.sub(r"//[^\n]*", "", src)


def body_after(src, i):
    """Text of the brace block that starts at src[i] == '{' (bounded)."""
    depth, j = 0, i
    while j < len(src) and j - i < 200000:
        c = src[j]
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return src[i + 1:j]
        j += 1
    return src[i + 1:j]


def scopes(src):
    """[(pos, 'A::B')] for every struct/class definition: the enclosing namespaces and classes."""
    ev = [(m.start(), "ns", m.group(1)) for m in re.finditer(r"\bnamespace\s+([A-Za-z_]\w*)\s*\{", src)]
    ev += [(m.end() - 1, "cls", m.group(2).split("::")[-1], m.start()) for m in DEF.finditer(src)]
    ev += [(i, "{", None) for i, c in enumerate(src) if c == "{"]
    ev += [(i, "}", None) for i, c in enumerate(src) if c == "}"]
    ev.sort(key=lambda e: (e[0], 0 if e[1] in ("ns", "cls") else 1))
    stack, out, claimed = [], {}, set()
    for e in ev:
        if e[1] == "ns":
            stack.append(e[2]); claimed.add(src.index("{", e[0]))
        elif e[1] == "cls":
            out[e[3]] = "::".join(n for n in stack if n)
            stack.append(e[2]); claimed.add(e[0])
        elif e[1] == "{":
            if e[0] not in claimed:
                stack.append(None)
        elif stack:
            stack.pop()
    return out


def verdict(kw, qual, pdb, mang, full):
    nm = short(qual)
    if full.get(qual):
        c, src = full[qual], "pdb-qualified"
    else:
        src, c = ("pdb-name", pdb.get(nm)) if pdb.get(nm) else ("mangled-name", mang.get(nm))
    if not c:
        return "unknown", ""
    if len(c) > 1:
        return "conflict", "%s %s" % (src, dict(c))
    orig = next(iter(c))
    if orig == kw:
        return "ok", "%s says %s" % (src, orig)
    # a name-only match may be an unrelated type that shares the short name (squish::Vec3 vs our Vec3)
    return ("MISMATCH" if src == "pdb-qualified" else "mismatch?"), "%s says %s" % (src, orig)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("paths", nargs="*", default=["match/slices", "src/game"])
    ap.add_argument("--tsv"); ap.add_argument("--all", action="store_true", help="list every definition, not only mismatches")
    a = ap.parse_args()
    pdb, mang, full = load_truth()
    files = []
    for p in a.paths:
        p = W(p) if not os.path.isabs(p) else p
        if os.path.isfile(p):
            files.append(p)
        else:
            for ext in ("cpp", "h", "hpp", "inl"):
                files += glob.glob(os.path.join(p, "**", "*." + ext), recursive=True)
    rows = []
    for f in sorted(x for x in set(files) if os.path.isfile(x)):
        src = strip_comments(open(f, errors="replace").read())
        sc = scopes(src)
        for m in DEF.finditer(src):
            kw, name, bases = m.group(1), m.group(2), (m.group(3) or "").strip()
            body = body_after(src, m.end() - 1)
            poly = bool(bases) or bool(re.search(r"\bvirtual\b", body))
            qual = "::".join(x for x in (sc.get(m.start(), ""), re.sub(r"<.*", "", name)) if x)
            v, why = verdict(kw, qual, pdb, mang, full)
            hint = ("class?" if poly and kw == "struct" else "") if v == "unknown" else ""
            line = src.count("\n", 0, m.start()) + 1
            rows.append((os.path.relpath(f, ROOT), line, kw, qual, v, why, "poly" if poly else "", hint))
    tally = collections.Counter(r[4] for r in rows)
    print("definitions %d: %s" % (len(rows), ", ".join("%s %d" % kv for kv in tally.most_common())))
    print("unknown and polymorphic struct (likely class, no record): %d" % sum(1 for r in rows if r[7]))
    by_file = collections.defaultdict(list)
    for r in rows:
        if a.all or r[4] in ("MISMATCH", "mismatch?") or r[7]:
            by_file[r[0]].append(r)
    worst = sorted(by_file.items(), key=lambda kv: -sum(1 for r in kv[1] if r[4] == "MISMATCH"))
    print("\nfiles with mismatches (struct->class or class->struct per the original):")
    for f, rs in worst:
        mm = [r for r in rs if r[4] == "MISMATCH"]
        if not mm and not a.all:
            continue
        print("  %-60s %3d  %s" % (f, len(mm), ", ".join("%s %s->%s" % (r[3], r[2], "class" if r[2] == "struct" else "struct")
                                                         for r in mm[:6]) + (" ..." if len(mm) > 6 else "")))
    if a.tsv:
        with open(a.tsv, "w") as o:
            o.write("file\tline\tkeyword\tname\tverdict\tevidence\tpolymorphic\thint\n")
            for r in rows:
                o.write("\t".join(map(str, r)) + "\n")
        print("\nwrote %s (%d rows)" % (os.path.relpath(a.tsv, ROOT) if a.tsv.startswith(ROOT) else a.tsv, len(rows)))


if __name__ == "__main__":
    sys.exit(main())
