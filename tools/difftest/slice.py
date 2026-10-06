"""Slice bookkeeping for the equivalence harness: rows, flags, compile, symbol lookup.

Read-only with respect to match/: objects are compiled into work/difftest/obj/.
"""
import hashlib, os, re, subprocess, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))

from coff import Coff  # noqa: E402

DEFAULT_FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
INCLUDE = "/I" + "Z:" + os.path.join(ROOT, "match", "include").replace("/", "\\")
OBJDIR = os.path.join(ROOT, "work", "difftest", "obj")
CL = os.path.join(ROOT, "tools", "matching", "cl.sh")

FLAG_RE = re.compile(r"(?<![\w/])(/(?:O[12dxyst]-?|Ob\d|Oi-?|Oy-?|M[DT]d?|Gy-?|EH\w+|TP|TC|arch:\w+|fp:\w+|GS-?|GR-?|Gz|Gr|Gd|Zp\d+|GF|Gs\d*|J))(?![\w:])")


def winpath(p):
    return "Z:" + p.replace("/", "\\")


def slice_dir(sid):
    return os.path.join(ROOT, "match", "slices", sid)


def read_rows(path):
    """Rows of a nonmatching/partial file: [(va, diff, reason)]."""
    rows = []
    if not os.path.exists(path):
        return rows
    for line in open(path, encoding="utf-8", errors="replace"):
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        p = line.split(None, 2)
        try:
            va = int(p[0], 16)
        except ValueError:
            continue
        rows.append((va, p[1] if len(p) > 1 else "", p[2].strip() if len(p) > 2 else ""))
    return rows


def manifest_rows(sid):
    """[(src, symbol, va, flags-or-None)] from the slice manifest."""
    out = []
    path = os.path.join(slice_dir(sid), "manifest.txt")
    if not os.path.exists(path):
        return out
    for line in open(path):
        p = line.split("#", 1)[0].split()
        if len(p) >= 3:
            try:
                out.append((p[0], p[1], int(p[2], 16), p[3:] or None))
            except ValueError:
                pass
    return out


def flags_from_reason(reason):
    """Flags recorded in a nonmatching reason, merged onto the defaults when only extras are given.
    Returns None when the reason names no compiler flag."""
    if not reason:
        return None
    toks = []
    for m in FLAG_RE.finditer(reason):
        pre = reason[max(0, m.start() - 4):m.start()].lower()
        if pre.endswith("no ") or pre.endswith("not "):
            continue
        if m.group(1) not in toks:
            toks.append(m.group(1))
    if not toks:
        return None
    if not any(t.startswith(("/O1", "/O2", "/Od", "/Ox")) for t in toks):
        return _merge(toks, reason)
    if "/MD" in toks and "/Gy" in toks:
        flags = _dedupe(toks)
    else:
        flags = _merge(toks, reason)
    if re.search(r"\bno (/EHsc|EH)\b", reason) and "/EHsc" in flags:
        flags.remove("/EHsc")
    return flags


def _family(f):
    for p in ("/O1", "/O2", "/Od", "/Ox"):
        if f.startswith(p):
            return "/O"
    for p in ("/fp:", "/arch:", "/M", "/Ob", "/GS", "/Oy", "/EH"):
        if f.startswith(p):
            return p
    return f


def _dedupe(toks):
    seen, out = set(), []
    for t in toks:
        if _family(t) not in seen:
            seen.add(_family(t))
            out.append(t)
    return out


def _merge(toks, reason):
    toks = _dedupe(toks)
    flags = list(DEFAULT_FLAGS)
    for t in toks:
        if t.startswith(("/O1", "/O2", "/Od", "/Ox")):
            flags = [f for f in flags if not f.startswith(("/O1", "/O2", "/Od", "/Ox"))]
            flags.insert(0, t)
        elif t not in flags:
            flags.append(t)
    return flags


def flags_from_source(src):
    """Flags named in a 'Flags: ...' / 'flags /O2 ...' comment near the top of the source."""
    if not os.path.exists(src):
        return None
    head = open(src, encoding="utf-8", errors="replace").read().split("\n")[:80]
    for line in head:
        if "//" not in line:
            continue
        c = line.split("//", 1)[1]
        if re.search(r"\bflags?\b", c, re.I) and FLAG_RE.search(c):
            f = flags_from_reason(c[re.search(r"\bflags?\b", c, re.I).start():])
            if f:
                return f
    return None


def choose_flags(sid, va, override=None):
    """(flags, provenance): explicit override, the nonmatching reason, a 'Flags:' comment in the
    source, the slice manifest, then the defaults."""
    if override:
        return override.split(), "override"
    for rva, _d, reason in read_rows(os.path.join(slice_dir(sid), "nonmatching.txt")):
        if rva == va:
            m = re.search(r"\bflags?\b", reason, re.I)
            f = flags_from_reason(reason[m.start():]) if m else None
            if f:
                return f, "reason"
            f2 = flags_from_source(source_path(sid))
            if f2:
                return f2, "source comment"
            f = flags_from_reason(reason)
            if f:
                return f, "reason(loose)"
    rows = manifest_rows(sid)
    for _src, _sym, mva, fl in rows:
        if mva == va and fl:
            return fl, "manifest(va)"
    fls = [tuple(r[3]) for r in rows if r[3]]
    if fls:
        best = max(set(fls), key=fls.count)
        return list(best), "manifest(slice)"
    return list(DEFAULT_FLAGS), "default"


def source_path(sid):
    return os.path.join(slice_dir(sid), sid + ".cpp")


def compile_obj(src, flags):
    """Compile src with flags into work/difftest/obj (cached by source+headers+flags). -> (obj, log)."""
    os.makedirs(OBJDIR, exist_ok=True)
    h = hashlib.md5()
    h.update(open(src, "rb").read())
    for hdr in sorted(os.listdir(os.path.dirname(src))):
        if hdr.endswith((".h", ".hpp", ".inl")):
            h.update(open(os.path.join(os.path.dirname(src), hdr), "rb").read())
    h.update(" ".join(flags).encode())
    obj = os.path.join(OBJDIR, "%s_%s.obj" % (os.path.basename(src).rsplit(".", 1)[0], h.hexdigest()[:12]))
    if os.path.exists(obj):
        return obj, ""
    tmp = obj + ".part.obj"
    r = subprocess.run([CL, "/nologo", "/c", *flags, INCLUDE, "/Fo" + winpath(tmp), winpath(src)],
                       capture_output=True, text=True)
    if r.returncode or not os.path.exists(tmp):
        return None, (r.stdout + r.stderr)[-3000:]
    os.replace(tmp, obj)
    return obj, r.stdout[-500:]


# ---------------------------------------------------------------- symbol lookup

def demangle_qual(name):
    """Qualified name of an MSVC-mangled symbol ('?f@B@A@@...' -> 'A::B::f'); extern "C" '_f' -> 'f'.
    Returns None for names it does not understand (templates are kept raw)."""
    if name.startswith("?"):
        body = name[1:]
        special = None
        if body.startswith("?0"):
            special, body = "ctor", body[2:]
        elif body.startswith("?1"):
            special, body = "dtor", body[2:]
        elif body.startswith("?"):
            special, body = "op" + body[1], body[2:]
        if body.startswith("?$"):
            return None
        end = body.find("@@")
        if end < 0:
            return None
        parts = body[:end].split("@")
        if any(not p or p[0].isdigit() or p.startswith("?") for p in parts):
            return None
        if special:
            cls = parts[0]
            q = parts[::-1]
            if special == "ctor":
                return "::".join(q + [cls])
            if special == "dtor":
                return "::".join(q + ["~" + cls])
            return "::".join(q + ["operator" + special[2:]])
        return "::".join(parts[::-1])
    if name.startswith("@") and "@" in name[1:]:
        return name[1:name.index("@", 1)]
    if name.startswith("_"):
        return name[1:].split("@")[0]
    return name


def _def_name_after(lines, i):
    """Name of the first function *definition* (a '(' ... '{' before any ';') after line i."""
    buf = ""
    for j in range(i + 1, min(i + 80, len(lines))):
        l = lines[j].split("//")[0].strip()
        if not l or l.startswith(("#", "template", "/*", "*")):
            continue
        buf += " " + l
        if "{" in buf or ";" in buf:
            semi, brace = buf.find(";"), buf.find("{")
            if brace >= 0 and (semi < 0 or brace < semi) and "(" in buf[:brace]:
                head = buf[:buf.index("(")]
                m = re.search(r"((?:[A-Za-z_]\w*\s*::\s*)*~?(?:operator\s*\S+|[A-Za-z_]\w*))\s*$", head)
                if m:
                    return re.sub(r"\s+", "", m.group(1))
            if brace >= 0 and (semi < 0 or brace < semi) and "(" not in buf[:brace]:
                buf = ""   # class/namespace opening: keep looking
                continue
            buf = ""
    return None


def marker_names(src, va):
    """Candidate qualified names for the function at va: the definition right after a
    '// ... @ 0x<va>' marker, and names written next to the address in comments."""
    lines = open(src, encoding="utf-8", errors="replace").read().split("\n")
    marker = re.compile(r"//.*@\s*0x0*%x\b" % va, re.I)
    named = re.compile(r"//\s*(?:@\s*)?(?:0x)?0*%x\b[\s:,-]*((?:[A-Za-z_]\w*::)*~?[A-Za-z_]\w*)" % va, re.I)
    out = []
    for i, line in enumerate(lines):
        if marker.search(line):
            nm = _def_name_after(lines, i)
            if nm and nm not in out:
                out.append(nm)
        m = named.search(line)
        if m and m.group(1) not in out and m.group(1) not in ("complete", "flags", "the"):
            out.append(m.group(1))
    return out


def slice_symbol_name(sid, va):
    path = os.path.join(ROOT, "symbols", "slices", sid + ".txt")
    if os.path.exists(path):
        for line in open(path, encoding="utf-8", errors="replace"):
            p = line.split("#", 1)[0].strip().split(None, 1)
            if len(p) >= 2:
                try:
                    if int(p[0], 16) == va:
                        return p[1].strip()
                except ValueError:
                    pass
    return None


def base_ident(mangled):
    """Leading identifier of a symbol: '?f@C@@..'->'f', '??$f@..'->'f', '??0C@@'->'C', '_f'->'f'."""
    m = mangled
    if m.startswith("??$"):
        m = m[3:]
    elif m.startswith(("??0", "??1")):
        m = m[3:]
    elif m.startswith("?"):
        m = m[1:]
    elif m.startswith("@"):
        m = m[1:]
    elif m.startswith("_"):
        m = m[1:]
    return m.split("@", 1)[0]


def _clean_name(nm):
    nm = re.sub(r"<[^<>]*(<[^<>]*>[^<>]*)*>", "", nm)
    nm = nm.replace("`anonymous namespace'::", "").replace("anon::", "")
    return [p.lstrip("_") or p for p in nm.split("::") if p]


def _name_matches(mangled, nm):
    parts = _clean_name(nm)
    if not parts:
        return False
    last = parts[-1]
    b = base_ident(mangled).lstrip("_")
    if last.startswith("~"):
        if not mangled.startswith("??1") or b != last[1:]:
            return False
    elif len(parts) >= 2 and last == parts[-2]:      # constructor
        if not mangled.startswith("??0") or b != last:
            return False
    elif b != last or mangled.startswith(("??0", "??1")):
        return False
    if len(parts) >= 2 and not last.startswith("~") and last != parts[-2]:
        cls = parts[-2]
        if ("@" + cls + "@") not in mangled and ("?$" + cls + "@") not in mangled:
            return False
    return True


def find_symbol(coff, sid, va, src, orig_size=None):
    """-> (symbol name, how) | (list of candidates, 'ambiguous:...') | (None, reason).
    orig_size (bytes of the original function) rejects candidates of implausible size."""
    funcs = {n: f for n, f in coff.functions().items()
             if not n.startswith(("__ehhandler", "__unwindfunclet", "__catch", "__tryend", "$"))}
    for _src, sym, mva, _fl in manifest_rows(sid):
        if mva == va:
            if sym in funcs:
                return sym, "manifest"
            c = [n for n in funcs if sym in n]
            if len(c) == 1:
                return c[0], "manifest"
    names = marker_names(src, va)
    sn = slice_symbol_name(sid, va)
    if sn:
        names.insert(0, sn)

    def plausible(f):
        if not orig_size:
            return True
        _sec, a, b = coff.func_extent(funcs[f])
        return orig_size / 5 <= (b - a) <= orig_size * 5

    allc = []
    for nm in names:
        cands = [f for f in funcs if _name_matches(f, nm) and plausible(f)]
        if len(cands) == 1:
            return cands[0], "name %s" % nm
        for c in cands:
            if c not in allc:
                allc.append(c)
    if allc:
        return allc, "ambiguous: %s" % names
    return None, "no marker/name for 0x%08x matched an object symbol (names tried: %s)" % (va, names or "-")
