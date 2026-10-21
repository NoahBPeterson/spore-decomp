#!/usr/bin/env python3
"""Rewrite struct/class keywords in a slice to the ones the original used (classkey_triage.py MISMATCH rows).

usage: classkey_fix.py <slice-id | src/game/<dir>/<obj>> [...] [--dry-run]   (one result line per unit)

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
OBJGATE = False
DEF = re.compile(r"(?m)^([ \t]*(?:template\s*<[^;{]*?>\s*)?)(struct|class)(\s+(?:__declspec\([^)]*\)\s*)?)"
                 r"((?:[A-Za-z_]\w*::)*[A-Za-z_]\w*)((?:\s|//[^\n]*)*(?:final\s*)?)(:[^;{]*)?\{")   # a `// note` may sit before a brace on the next line


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
        raw, comment = m.group(6) or "", ""
        if "//" in raw:   # `: Base   // note` with the brace on the next line: keep the note after the new brace
            raw, comment = raw.split("//", 1)
            comment = "  //" + comment.rstrip()
        bases = fix_bases(raw, access) if raw.strip() else ""
        rep = "%s%s%s%s%s%s{ %s:%s\n" % (m.group(1), new, m.group(3), m.group(4), m.group(5) if not bases else "", bases, access, comment) \
            if comment else "%s%s%s%s%s%s{ %s:" % (m.group(1), new, m.group(3), m.group(4), m.group(5) if not bases else "", bases, access)
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


def unit(u):
    """A slice id (sXXXXXXXX) or a migrated module (src/game/<dir>/<obj> or <dir>/<obj>)."""
    if re.fullmatch(r"s[0-9a-f]{8}", u):
        d = W("match/slices", u)
        srcs = sorted(os.path.join(d, f) for f in os.listdir(d) if f.endswith((".cpp", ".h", ".hpp", ".inl"))) if os.path.isdir(d) else []
        return dict(name=u, bk=d, srcs=srcs, main=os.path.join(d, u + ".cpp"), row="slices/",
                    paths=["match/slices/" + u, "symbols/slices/%s.txt" % u], symfile=W("symbols/slices", u + ".txt"))
    m = re.sub(r"^src/game/", "", u).rstrip("/").removesuffix(".cpp")
    main = W("src/game", m + ".cpp")   # only the object's own TU: shared headers in src/game/include are left alone
    bk = W("src/game", m)
    if os.path.isdir(main):   # an object named x.cpp: bookkeeping in src/game/<dir>/x.cpp/, source in x.cpp.cpp
        bk, m = main, m + ".cpp"
        main = W("src/game", m + ".cpp")
    return dict(name=m, bk=bk, srcs=[main] if os.path.isfile(main) else [], main=main, row="../src/game/",
                paths=["src/game/%s.cpp" % m, os.path.relpath(os.path.join(bk, "manifest.txt"), ROOT)], symfile=None)


def restore(U):
    for p in U["paths"]:
        if os.path.exists(W(p)):
            sh("git", "checkout", "--", p)


def obj_symbols(src, flags):
    """Symbol names of the object chk.py just compiled for (src, flags)."""
    import hashlib
    sys.path.insert(0, W("tools/matching"))
    from cmpobj import parse_coff
    tag = hashlib.md5((os.path.abspath(src) + flags).encode()).hexdigest()[:10]
    obj = W("work/match/chk", "%s_%s.obj" % (os.path.basename(src).rsplit(".", 1)[0], tag))
    try:   # EH funclets embed their function's name; run_all ignores them too
        return [n for n in parse_coff(obj)[1] if not n.startswith(("__ehhandler", "__unwindfunclet", "__catch", "__tryend", "$"))]
    except Exception:
        return []


def compile_sections(src, flags):
    """Compile src to a scratch object; return a sorted list of (code section data, relocation offsets), or None.
    Symbol names are left out on purpose: a class-key change renames symbols and must change nothing else."""
    import hashlib
    from run_all import INCLUDE, winpath, resolve_flags
    from cmpobj import parse_coff
    obj = W("work/match/chk", "classkey_%s.obj" % hashlib.md5((src + flags + str(os.getpid())).encode()).hexdigest()[:10])
    if os.path.exists(obj):
        os.remove(obj)
    r = subprocess.run([W("tools/matching/cl.sh"), "/nologo", "/c", *resolve_flags(flags.split()), INCLUDE,
                        "/Fo" + winpath(obj), winpath(src)], capture_output=True, text=True, cwd=ROOT)
    if r.returncode or not os.path.exists(obj):
        return None
    secs, _ = parse_coff(obj)
    os.remove(obj)
    # code only: .drectve, .debug$S and RTTI strings carry mangled names, which legitimately change with the keyword
    return sorted((bytes(sc["data"]), tuple(sorted(v for v, _s, _t in sc["relocs"])))
                  for sc in secs if sc and sc.get("name", "").startswith(".text"))


def unit_flags(U):
    """The first flags string found in the unit's bookkeeping (nonmatching/partial notes), else run_all's defaults."""
    for f in ("nonmatching.txt", "partial.txt"):
        p = os.path.join(U["bk"], f)
        if os.path.exists(p):
            m = re.search(r"((?:/vc\d+\s+)?/O[d12x](?:\s+/[A-Za-z][\w:=.-]*)+)", open(p, errors="replace").read())
            if m:
                fl = m.group(1).rstrip(".,;")
                if U["row"] != "slices/" and "/Isrc/game/include" not in fl:   # a module's headers live there
                    fl += " /Isrc/game/include"
                return fl
    return " ".join(DEFAULT_FLAGS)


def fix_by_object(U, rows):
    """No manifest to re-run: keep the edit only if every section of the compiled object is byte-identical."""
    flags = unit_flags(U)
    before = compile_sections(U["main"], flags)
    if before is None:
        return "skip (does not compile before, flags %s)" % flags
    by_file = collections.defaultdict(dict)
    for r in rows:
        by_file[r[0]][int(r[1])] = "class" if r[2] == "struct" else "struct"
    changed = {}
    for f, t in by_file.items():
        changed.update(edit_file(W(f), t))
    if len(changed) < len({r[3].split('::')[-1] for r in rows}):   # the editor missed a definition
        restore(U)
        return "skip (edited %d of %d definitions)" % (len(changed), len(rows))
    after = compile_sections(U["main"], flags)
    if after != before:
        if not KEEP:
            restore(U)
        return "REVERTED (object %s after the edit)" % ("does not compile" if after is None else "differs")
    sf = U["symfile"]
    if sf and os.path.exists(sf) and sh("git", "ls-files", "--", sf).stdout.strip():   # never an untracked file
        s = open(sf).read(); s2 = "\n".join(re.sub(r"(\S+)$", lambda m: swap(m.group(1), changed), l) for l in s.split("\n"))
        if s2 != s:
            open(sf, "w").write(s2)
    return "fixed %d definitions (%s); code sections identical" % (len(rows), ", ".join("%s->%s" % kv for kv in sorted(changed.items()))[:160])


def uv_only(old, new):
    """new is old with some U<->V letters swapped. Manifests also hold names cut at 100 characters and fragments
    of long template names (run_all matches a manifest symbol as a substring), so old may sit anywhere in new."""
    if len(new) < len(old) or old in new:
        return False
    for k in range(len(new) - len(old) + 1):
        if all(a == b or {a, b} == {"U", "V"} for a, b in zip(old, new[k:k + len(old)])):
            return True
    return False


def run_all(U):
    r = sh(PY, W("tools/matching/run_all.py"), "--manifest", os.path.relpath(os.path.join(U["bk"], "manifest.txt"), ROOT))
    last = (r.stdout.strip().splitlines() or [""])[-1]
    m = re.match(r"(\d+) / (\d+)", last)
    return (int(m.group(1)), int(m.group(2))) if m else (0, -1)


def fix_slice(sid, dry):
    U = unit(sid); d = U["bk"]
    if not U["srcs"] or not os.path.exists(U["main"]):
        return "skip (no source)"
    mf = os.path.join(d, "manifest.txt")
    # a manifest without rows checks nothing (run_all 0/0): such a unit goes through the object gate too
    nomanifest = not os.path.exists(mf) or not any(l.strip() and not l.startswith("#") for l in open(mf))
    if nomanifest and not OBJGATE:
        return "skip (no manifest)"
    if sh("git", "ls-files", "--", U["paths"][0]).stdout.strip() == "":
        return "skip (not tracked in git)"
    # an untracked symbols file a session wrote after its commit is not a reason to skip; tracked edits are
    if sh("git", "status", "--porcelain", "-uno", "--", *U["paths"]).stdout.strip():
        return "skip (uncommitted changes)"
    files = [os.path.relpath(f, ROOT) for f in U["srcs"]]
    rows = triage_rows(files)
    if not rows:
        return "nothing to fix"
    if nomanifest:
        return ("would fix %d definitions by the object gate" % len(rows)) if dry else fix_by_object(U, rows)
    ok0, n0 = run_all(U)
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
    if len(changed) < len({r[3].split('::')[-1] for r in rows}):   # the editor missed a definition
        restore(U)
        return "skip (edited %d of %d definitions)" % (len(changed), len(rows))
    # re-bind manifest rows whose mangled names carry a changed class-key
    mf = os.path.join(d, "manifest.txt")
    lines = open(mf).read().split("\n")
    need = collections.defaultdict(list)   # flags -> [(line index, va, old, expected)]
    for i, l in enumerate(lines):
        p = l.split()
        if len(p) >= 3 and l.startswith(U["row"]):
            # every row is re-checked: MSVC writes a repeated name as a digit back-reference (PAU12@) and a
            # template as U?$Name@, so the U/V positions cannot all be predicted from the name
            need[(os.path.normpath(W("match", p[0])), " ".join(p[3:]))].append((i, p[2], p[1], None))
    for (srcf, flags), items in need.items():   # each row compiles its own source file (slices can have several)
        cmd = [PY, W("tools/matching/chk.py"), srcf] + [it[1] for it in items]
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
                    syms = obj_symbols(srcf, flags or " ".join(DEFAULT_FLAGS))
                c = [x for x in syms if uv_only(old, x)]
                new = c[0] if len(c) == 1 else None
            # accept only a class-key change: same length, every differing character a U/V swap
            if new and uv_only(old, new):
                lines[i] = lines[i].replace(old, new, 1)
    open(mf, "w").write("\n".join(lines))
    sf = U["symfile"]
    if sf and os.path.exists(sf) and sh("git", "ls-files", "--", sf).stdout.strip():   # never an untracked file
        s = open(sf).read(); s2 = "\n".join(re.sub(r"(\S+)$", lambda m: swap(m.group(1), changed), l) for l in s.split("\n"))
        if s2 != s:
            open(sf, "w").write(s2)
    ok1, n1 = run_all(U)
    if (ok1, n1) != (ok0, n0) and not KEEP:
        restore(U)
        return "REVERTED (run_all %d/%d after, %d/%d before)" % (ok1, n1, ok0, n0)
    return "fixed %d definitions (%s); run_all %d/%d" % (len(rows), ", ".join("%s->%s" % kv for kv in sorted(changed.items()))[:160], ok1, n1)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("slices", nargs="+"); ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--keep", action="store_true", help="debug: leave a failed edit in place")
    ap.add_argument("--object-gate", action="store_true", help="units without a manifest: keep the edit only if "
                    "the compiled object's code sections are byte-identical before and after")
    a = ap.parse_args()
    global KEEP, OBJGATE; KEEP = a.keep; OBJGATE = a.object_gate
    for s in a.slices:
        print("%s %s" % (s, fix_slice(s, a.dry_run)), flush=True)


if __name__ == "__main__":
    sys.exit(main())
