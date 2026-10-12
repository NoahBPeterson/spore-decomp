#!/usr/bin/env python3
"""Census of class/struct declarations across match/slices: which names are redeclared in how many
slices, and how many distinct bodies each has.  -> work/claude/layouts/census.json + census.md

A 'body' is the normalized member list of a top-level struct/class/union definition (comments,
whitespace and access specifiers stripped, method declarations dropped, so only data members and
padding count).  Distinct bodies for one name are candidate layout conflicts; an agent pass decides
which are real conflicts and which are compatible partial views.
"""
import collections, glob, hashlib, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
OUT = os.path.join(ROOT, "work", "claude", "layouts")
DECL = re.compile(r"^\s*(?:template\s*<[^>]*>\s*)?(struct|class|union)\s+(?:__declspec\([^)]*\)\s*)?([A-Za-z_]\w*)\s*(?::[^{;]*)?\{", re.M)


def strip_comments(t):
    t = re.sub(r"/\*.*?\*/", "", t, flags=re.S)
    return re.sub(r"//[^\n]*", "", t)


def bodies(text):
    """[(kind, name, body text)] for every brace-balanced top-level or nested definition."""
    out = []
    for m in DECL.finditer(text):
        i, d = m.end(), 1
        while i < len(text) and d:
            d += {"{": 1, "}": -1}.get(text[i], 0)
            i += 1
        out.append((m.group(1), m.group(2), text[m.end():i - 1]))
    return out


def normalize(body):
    """Data members only: drop method declarations/definitions, access labels, nested types' bodies."""
    b = re.sub(r"\{[^{}]*\}", "{}", body)          # nested bodies / inline method bodies
    b = re.sub(r"\{[^{}]*\}", "{}", b)
    lines = []
    for stmt in b.split(";"):
        s = " ".join(stmt.split())
        s = re.sub(r"\b(public|private|protected)\s*:\s*", "", s)
        if not s or "(" in s or s.startswith(("typedef", "using", "enum", "struct", "class", "union", "friend", "template", "static ")):
            continue
        s = re.sub(r"\s*\[\s*", "[", s).replace(" ]", "]")
        lines.append(s)
    return lines


def main():
    os.makedirs(OUT, exist_ok=True)
    by = collections.defaultdict(dict)   # name -> body hash -> {"members": [...], "slices": [...]}
    files = glob.glob(os.path.join(ROOT, "match", "slices", "*", "*.cpp")) + glob.glob(os.path.join(ROOT, "match", "slices", "*", "*.h"))
    for f in sorted(files):
        sid = os.path.basename(os.path.dirname(f))
        text = strip_comments(open(f, encoding="utf-8", errors="replace").read())
        for kind, name, body in bodies(text):
            mem = normalize(body)
            if not mem:
                continue                 # interface-only declarations (vtable stubs) carry no layout
            h = hashlib.md5("\n".join(mem).encode()).hexdigest()[:10]
            e = by[name].setdefault(h, {"members": mem, "slices": []})
            if sid not in e["slices"]:
                e["slices"].append(sid)
    rows = []
    for name, vs in by.items():
        nslices = len({s for v in vs.values() for s in v["slices"]})
        rows.append((name, nslices, len(vs)))
    rows.sort(key=lambda r: (-r[2], -r[1]))
    json.dump({n: v for n, v in by.items()}, open(os.path.join(OUT, "census.json"), "w"), indent=1)
    lines = ["# layout census", "", "names with a data-member body: %d; redeclared in >1 slice: %d; with >1 distinct body: %d" % (
        len(rows), sum(1 for r in rows if r[1] > 1), sum(1 for r in rows if r[2] > 1)), "",
        "| name | slices | distinct bodies |", "|---|---:|---:|"]
    lines += ["| %s | %d | %d |" % r for r in rows[:150]]
    open(os.path.join(OUT, "census.md"), "w").write("\n".join(lines) + "\n")
    print("\n".join(lines[:40]))


if __name__ == "__main__":
    sys.exit(main())
