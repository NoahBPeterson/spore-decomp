#!/usr/bin/env python3
"""Rewrite struct/class keywords in a slice to the ones the original used (classkey_triage.py MISMATCH rows).

usage: classkey_fix.py <slice-id> [...] [--dry-run]   (prints one result line per slice)

Per slice, for every definition the triage marks MISMATCH (the PDB type with the same qualified name used the
other keyword):
  * the keyword is swapped, and the old default access is written out so nothing else changes: a struct that
    becomes a class gets `public:` after its brace and `public` on each base; a class that becomes a struct
    gets `private:` and `private` bases (MSVC mangles member access, so access must not move);
  * forward declarations and elaborated uses (`struct X;`, `struct X*`) of the same name in the slice's files
    follow, because MSVC mangles with the keyword of the first declaration it sees;
  * the class-key also appears in mangled parameter types (PAU = struct, PAV = class), so manifest rows and
    symbols/slices/<id>.txt names are re-bound: chk.py recompiles, binds each VA by its // @ marker, and a row is
    rewritten only when the new symbol differs from the old one in U<->V letters alone.
The slice must be clean in git and fully MATCH before; the edit is kept only if run_all still matches every row,
otherwise every file is restored. Committing is left to work/claude/commit_slice.sh.
"""
import argparse, collections, csv, json, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
W = lambda *p: os.path.join(ROOT, *p)
PY = W(".venv/bin/python")
sys.path.insert(0, W("tools/matching"))
from run_all import DEFAULT_FLAGS  # noqa: E402
KEEP = False
DEF = re.compile(r"(?m)^([ \t]*(?:template\s*<[^;{]*?>\s*)?)(struct|class)(\s+(?:__declspec\([^)]*\)\s*)?)"
                 r"((?:[A-Za-z_]\w*::)*[A-Za-z_]\w*)(\s*(?:final\s*)?)(:[^;{]*)?\{")


def sh(*a):
    return subprocess.run(a, capture_output=True, text=True, cwd=ROOT)


def triage_rows(files):
    out = sh(PY, W("tools/classkey_triage.py"), *files, "--all", "--tsv", "/dev/stdout").stdout
    rows = [l.split("\t") for l in out.splitlines() if l.count("\t") >= 7 and not l.startswith("file\t")]
    return [r for r in rows if r[4] == "MISMATCH"]


def fix_bases(bases, access):
    """': A, B<T,U>' -> ': public A, public B<T,U>' for bases with no access specifier (top-level commas only)."""
    body, parts, depth, cur = bases.strip()[1:], [], 0, ""
    for c in body:
        if c == "<": depth += 1
        elif c == ">": depth -= 1
        if c == "," and depth == 0:
            parts.append(cur); cur = ""
        else:
            cur += c
    parts.append(cur)
    fixed = []
    for p in parts:
        s = p.strip()
        if not re.match(r"(?:virtual\s+)?(?:public|private|protected)\b", s) and not re.match(r"(public|private|protected)\s+virtual\b", s):
            s = re.sub(r"^(virtual\s+)?", lambda m: (m.group(1) or "") + access + " ", s, count=1)
        fixed.append(s)
    return " : " + ", ".join(fixed) + " "


def edit_file(path, targets):
    """targets: {line: new_keyword}. Returns {short name: new keyword} actually changed."""
    src = open(path, errors="replace").read()
    changed = {}
    out, last = [], 0
    for m in DEF.finditer(src):
        line = src.count("\n", 0, m.start()) + 1
        new = targets.get(line)
        if not new or m.group(2) == new:
            continue
        access = "public" if new == "class" else "private"
        bases = fix_bases(m.group(6), access) if m.group(6) else ""
        rep = "%s%s%s%s%s%s{ %s:" % (m.group(1), new, m.group(3), m.group(4), m.group(5) if not bases else "", bases, access)
        out.append(src[last:m.start()]); out.append(rep); last = m.end()
        changed[re.sub(r"<.*", "", m.group(4)).split("::")[-1]] = new
    out.append(src[last:]); src = "".join(out)
    # forward declarations / elaborated type specifiers of the same names (not definitions: no '{' or ':' follows)
    for nm, new in changed.items():
        old = "struct" if new == "class" else "class"
        src = re.sub(r"\b%s(\s+)%s\b(?!\s*(?:[:{<]|::))" % (old, re.escape(nm)), lambda m: new + m.group(1) + nm, src)
    open(path, "w").write(src)
    return changed


def swap(sym, changed):
    for nm, new in changed.items():
        a, b = ("U", "V") if new == "class" else ("V", "U")
        # pointer/reference (PAU, ABU, ...), by-value parameter (HUname@@), by-value return (?AUname@)
        sym = re.sub(r"(?<=[A-Z0-9_@?$])%s((?:\?\$)?%s@)" % (a, re.escape(nm)), b + r"\1", sym)
    return sym


def restore(sid):
    sh("git", "checkout", "--", "match/slices/" + sid)
    if os.path.exists(W("symbols/slices", sid + ".txt")):
        sh("git", "checkout", "--", "symbols/slices/%s.txt" % sid)


def obj_symbols(src, flags):
    """Symbol names of the object chk.py just compiled for (src, flags)."""
    import hashlib
    sys.path.insert(0, W("tools/matching"))
    from cmpobj import parse_coff
    tag = hashlib.md5((os.path.abspath(src) + flags).encode()).hexdigest()[:10]
    obj = W("work/match/chk", "%s_%s.obj" % (os.path.basename(src).rsplit(".", 1)[0], tag))
    try:
        return list(parse_coff(obj)[1])
    except Exception:
        return []


def uv_only(old, new):
    return new != old and len(new) == len(old) and all(a == b or {a, b} == {"U", "V"} for a, b in zip(old, new))


def run_all(sid):
    r = sh(PY, W("tools/matching/run_all.py"), "--manifest", "match/slices/%s/manifest.txt" % sid)
    last = (r.stdout.strip().splitlines() or [""])[-1]
    m = re.match(r"(\d+) / (\d+)", last)
    return (int(m.group(1)), int(m.group(2))) if m else (0, -1)


def fix_slice(sid, dry):
    d = W("match/slices", sid)
    if not os.path.isdir(d) or not os.path.exists(os.path.join(d, "manifest.txt")):
        return "skip (no manifest)"
    if sh("git", "status", "--porcelain", "--", "match/slices/" + sid, "symbols/slices/%s.txt" % sid).stdout.strip():
        return "skip (uncommitted changes)"
    files = sorted(os.path.relpath(os.path.join(d, f), ROOT) for f in os.listdir(d) if f.endswith((".cpp", ".h", ".hpp", ".inl")))
    rows = triage_rows(files)
    if not rows:
        return "nothing to fix"
    ok0, n0 = run_all(sid)
    if ok0 != n0:
        return "skip (baseline %d/%d)" % (ok0, n0)
    if dry:
        return "would fix %d definitions: %s" % (len(rows), ", ".join(sorted({r[3] for r in rows}))[:200])
    by_file = collections.defaultdict(dict)
    for r in rows:
        by_file[r[0]][int(r[1])] = "class" if r[2] == "struct" else "struct"
    changed = {}
    for f, t in by_file.items():
        changed.update(edit_file(W(f), t))
    # re-bind manifest rows whose mangled names carry a changed class-key
    mf = os.path.join(d, "manifest.txt")
    lines = open(mf).read().split("\n")
    need = collections.defaultdict(list)   # flags -> [(line index, va, old, expected)]
    for i, l in enumerate(lines):
        p = l.split()
        if len(p) >= 3 and l.startswith("slices/"):
            # every row is re-checked: MSVC writes a repeated name as a digit back-reference (PAU12@) and a
            # template as U?$Name@, so the U/V positions cannot all be predicted from the name
            need[" ".join(p[3:])].append((i, p[2], p[1], None))
    for flags, items in need.items():
        cmd = [PY, W("tools/matching/chk.py"), os.path.join(d, sid + ".cpp")] + [it[1] for it in items]
        if flags:
            cmd += ["--flags", flags]
        out = sh(*cmd).stdout
        got = {l.split()[0].lstrip("0"): l.split()[5] for l in out.splitlines()
               if re.match(r"^[0-9a-f]{8} ", l) and len(l.split()) > 5 and l.split()[2] == "0"}
        syms = None
        for i, va, old, _ in items:
            new = got.get(va.lower().replace("0x", "").lstrip("0"))
            if not (new and uv_only(old, new)):
                # templates and anonymous namespaces defeat the marker binding: take the object's one symbol that
                # differs from the old name in U<->V letters alone
                if syms is None:
                    syms = obj_symbols(os.path.join(d, sid + ".cpp"), flags or " ".join(DEFAULT_FLAGS))
                c = [x for x in syms if uv_only(old, x)]
                new = c[0] if len(c) == 1 else None
            # accept only a class-key change: same length, every differing character a U/V swap
            if new and uv_only(old, new):
                lines[i] = lines[i].replace(old, new, 1)
    open(mf, "w").write("\n".join(lines))
    sf = W("symbols/slices", sid + ".txt")
    if os.path.exists(sf):
        s = open(sf).read(); s2 = "\n".join(re.sub(r"(\S+)$", lambda m: swap(m.group(1), changed), l) for l in s.split("\n"))
        if s2 != s:
            open(sf, "w").write(s2)
    ok1, n1 = run_all(sid)
    if (ok1, n1) != (ok0, n0) and not KEEP:
        restore(sid)
        return "REVERTED (run_all %d/%d after, %d/%d before)" % (ok1, n1, ok0, n0)
    return "fixed %d definitions (%s); run_all %d/%d" % (len(rows), ", ".join("%s->%s" % kv for kv in sorted(changed.items()))[:160], ok1, n1)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("slices", nargs="+"); ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--keep", action="store_true", help="debug: leave a failed edit in place")
    a = ap.parse_args()
    global KEEP; KEEP = a.keep
    for s in a.slices:
        print("%s %s" % (s, fix_slice(s, a.dry_run)), flush=True)


if __name__ == "__main__":
    sys.exit(main())
