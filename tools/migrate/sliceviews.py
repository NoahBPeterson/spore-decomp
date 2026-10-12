#!/usr/bin/env python3
"""sliceviews: every struct/class/union definition in every slice TU, with byte offsets.

Phase B of docs/migration.md.  Writes work/migrate/sliceviews.json:

  { "defs":     [ {"name", "slice", "file", "line", "kind", "bases": [names], "base_layout": [...],
                   "vptr": bool, "members": [{"name","offset","size","type","pad", ["bit"], ["anon"],
                   "exact_users", "equiv_users"}],
                   "size", "size_known", "align", "complete", "problems": [...], "pack", "parent",
                   "exact_users", "exact_name_users", "equiv_users", "equiv_name_users", "mentions"} ],
    "by_name":  {name: [indices into defs]},
    "conflicts":{name: [{"member", "views": [{"def","slice","offset","size","view_exact","member_exact"}]}]},
    "summary":  {...}, "failures": [{"file","line","reason","detail"}], "failure_counts": {reason: n} }

Layout rules (MSVC x86): natural alignment capped by #pragma pack in force at the definition;
long long/double align 8; pointers/enums 4; vptr (4 bytes at +0) when the class declares a virtual
function and no base has one; bases laid out after the vptr in declaration order (empty bases take 0
bytes); struct size rounded up to its alignment; empty struct = 1 byte; bitfields packed into
allocation units of the declared type size.  Whenever a size, alignment or construct is unknown the
affected offsets/sizes are null (None) and every offset after it is null as well, except that the
offset of the member right at an unknown type is kept when the running offset is a multiple of 8.

"exact_users" = manifest.txt (byte-exact) functions of the slice whose body (the text from its
"// @ 0x<va>" marker to the next marker, comments and struct definitions blanked) mentions the struct
name or any non-padding member name; "exact_name_users" = the subset that mentions the struct name
itself.  Same for nonmatching.txt ("equiv_*").  "mentions" = other marked functions.
Every member also carries its own exact_users/equiv_users (functions that mention the member name).
Member-name matching is lexical: common names (x, size, ...) over-report; use exact_name_users or
the per-member lists when that matters.
"""
import argparse, collections, glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SLICES = os.path.join(ROOT, "match", "slices")
OUT = os.path.join(ROOT, "work", "migrate", "sliceviews.json")

BUILTIN_WORDS = {"unsigned", "signed", "int", "char", "short", "long", "float", "double", "bool", "wchar_t", "void",
                 "__int8", "__int16", "__int32", "__int64", "char16_t", "char32_t"}
# well-known fixed typedefs used by the slices when they do not define them themselves
KNOWN = {"int8_t": 1, "uint8_t": 1, "int16_t": 2, "uint16_t": 2, "int32_t": 4, "uint32_t": 4, "int64_t": 8,
         "uint64_t": 8, "size_t": 4, "ptrdiff_t": 4, "intptr_t": 4, "uintptr_t": 4, "BYTE": 1, "WORD": 2,
         "DWORD": 4, "BOOL": 4, "UINT": 4, "ULONG": 4, "LONG": 4, "HANDLE": 4, "HRESULT": 4, "LPVOID": 4,
         "WCHAR": 2, "ULONGLONG": 8, "LONGLONG": 8, "UINT_PTR": 4, "DWORD_PTR": 4, "LPCSTR": 4, "LPSTR": 4,
         "va_list": 4, "uchar": 1, "uint": 4, "ushort": 2, "ulong": 4, "u8": 1, "u16": 2, "u32": 4, "u64": 8,
         "s8": 1, "s16": 2, "s32": 4, "s64": 8}
PAD_RE = re.compile(r"(?i)^(m_?)?(_?pad|padding|unk|unknown|reserved|gap|filler|dummy|field_?0x|unused|u_?[0-9a-f]{2,}$|_unk)|pad\d*$|unk_?[0-9a-f]+$|_pad")
STRIP_QUALS = re.compile(r"\b(const|volatile|mutable|register|static|extern|inline|__forceinline|__unaligned|__restrict|__ptr64|"
                         r"__ptr32|struct|class|union|enum|typename|__cdecl|__stdcall|__thiscall|__fastcall)\b")
DECL_RE = re.compile(r"\b(typedef\s+)?(struct|class|union)\b\s*(?:__declspec\s*\([^)]*\)\s*)?([A-Za-z_]\w*)?\s*(?:final\s*)?(:(?!:)[^{};]*)?\{")
ENUM_RE = re.compile(r"\b(typedef\s+)?enum\s+(?:class\s+|struct\s+)?([A-Za-z_]\w*)?\s*(?::\s*([\w\s]+?))?\s*\{")
MARK_RE = re.compile(r"//\s*@\s*0x([0-9a-fA-F]+)")
FPTR_RE = re.compile(r"\(\s*(?:__\w+\s+)?[\w:]*\s*\*+\s*(\w+)\s*(\[[^\]]*\])*\s*\)\s*\(")


def rd(path):
    return open(path, encoding="utf-8", errors="replace").read()


class Src:
    """One preprocessed source file: comments blanked (positions preserved), directives blanked."""

    def __init__(self, path, rel):
        self.path, self.rel = path, rel
        self.raw = rd(path)
        self.rawlines = self.raw.split("\n")
        self.text = self.strip(self.raw)
        self.packs = [(0, 8)]          # (pos, pack in force) - 8 = MSVC default
        self.cond_lines = []           # positions of unresolved #if/#else/#elif/#endif directives
        self.consts = {}
        self.text = self.preprocess(self.text)

    @staticmethod
    def strip(t):
        def rep(m):
            s = m.group(0)
            if s[0] in "\"'":
                return s
            return re.sub(r"[^\n]", " ", s)
        return re.sub(r"//[^\n]*|/\*.*?\*/|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])+'", rep, t, flags=re.S)

    def preprocess(self, t):
        pos, stack, cur_pack, pstack = 0, [], 8, []
        lines = t.split("\n")
        i = 0
        active_stack = []
        res_lines = []
        while i < len(lines):
            ln = lines[i]
            full = ln
            nl = 1
            while full.rstrip().endswith("\\") and i + nl < len(lines):
                full = full.rstrip()[:-1] + " " + lines[i + nl]
                nl += 1
            raw_chunk = "\n".join(lines[i:i + nl])
            is_pp = full.lstrip().startswith("#")
            active = all(active_stack)
            if is_pp:
                d = re.match(r"\s*#\s*(\w+)\s*(.*)", full, re.S)
                kw, rest = (d.group(1), d.group(2).strip()) if d else ("", "")
                if kw in ("if", "ifdef", "ifndef"):
                    if kw == "if" and rest in ("0", "false"):
                        active_stack.append(False)
                        stack.append(("zero", i))
                    elif kw == "if" and rest == "1":
                        active_stack.append(True)
                        stack.append(("one", i))
                    else:
                        active_stack.append(True)
                        stack.append(("var", i))
                        self.cond_lines.append((pos, "if"))
                elif kw in ("else", "elif"):
                    if stack:
                        k = stack[-1][0]
                        if k == "zero":
                            active_stack[-1] = True
                            stack[-1] = ("zero-else", stack[-1][1])
                        elif k == "one":
                            active_stack[-1] = False
                            stack[-1] = ("one-else", stack[-1][1])
                        else:
                            self.cond_lines.append((pos, kw))
                elif kw == "endif":
                    if stack:
                        k = stack.pop()[0]
                        active_stack.pop()
                        if k == "var":
                            self.cond_lines.append((pos, "endif"))
                elif active and kw == "pragma":
                    m = re.match(r"pack\s*\((.*)\)", rest)
                    if m:
                        a = [x.strip() for x in m.group(1).split(",") if x.strip()]
                        if not a:
                            cur_pack = 8
                        elif a[0] == "push":
                            pstack.append(cur_pack)
                            if len(a) > 1 and a[1].isdigit():
                                cur_pack = int(a[1])
                        elif a[0] == "pop":
                            cur_pack = pstack.pop() if pstack else 8
                        elif a[0].isdigit():
                            cur_pack = int(a[0])
                        self.packs.append((pos, cur_pack))
                elif active and kw == "define":
                    m = re.match(r"(\w+)\s+(.+)$", rest, re.S)
                    if m and not rest.startswith(m.group(1) + "("):
                        self.consts[m.group(1)] = m.group(2).strip()
                res_lines.append(re.sub(r"[^\n]", " ", raw_chunk))
            elif not active:
                res_lines.append(re.sub(r"[^\n]", " ", raw_chunk))
            else:
                res_lines.append(raw_chunk)
            pos += len(raw_chunk) + 1
            i += nl
        return "\n".join(res_lines)

    def pack_at(self, pos):
        p = 8
        for q, v in self.packs:
            if q <= pos:
                p = v
        return p

    def line(self, pos):
        return self.text.count("\n", 0, pos) + 1


def match_brace(t, i):
    """t[i] == '{'; return index just past the matching '}' (or None)."""
    d, n = 0, len(t)
    while i < n:
        c = t[i]
        if c == "{":
            d += 1
        elif c == "}":
            d -= 1
            if d == 0:
                return i + 1
        i += 1
    return None


def split_top(s, sep=","):
    """Split at depth-0 separators ((), [], {}, and template <> after an identifier)."""
    out, d, ang, cur = [], 0, 0, []
    for k, c in enumerate(s):
        if c in "([{":
            d += 1
        elif c in ")]}":
            d -= 1
        elif c == "<" and d == 0 and re.search(r"\w\s*$", s[:k]):
            ang += 1
        elif c == ">" and d == 0 and ang and not (k > 0 and s[k - 1] == "-"):
            ang -= 1
        if c == sep and d == 0 and ang == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(c)
    out.append("".join(cur))
    return out


class Ctx:
    """Per-slice type environment."""

    def __init__(self):
        self.types = {}        # name -> dict(size, align, empty, vptr)  (size may be None)
        self.consts = {}       # name -> expr text
        self.typedefs = {}     # name -> type text
        self.enums = {}        # name -> size
        self.econst = {}       # enum constant -> int or None
        self.reasons = []      # (reason, detail) from the current sizeof evaluation

    def evalx(self, expr, depth=0):
        if depth > 8:
            return None
        e = expr.strip()
        if not e:
            return None

        def sz(m):
            r = self.sizeof(m.group(1), quiet=True)
            return str(r[0]) if r and r[0] is not None else "None"
        e = re.sub(r"sizeof\s*\(\s*([^()]*(?:\([^()]*\)[^()]*)*)\)", sz, e)
        e = re.sub(r"\(\s*(?:unsigned|int|uint32_t|size_t|char|short|long)\s*\)", "", e)
        e = re.sub(r"\b(0[xX][0-9a-fA-F]+|\d+)[uUlL]+\b", r"\1", e)

        def ident(m):
            n = m.group(0)
            if n == "None" or re.fullmatch(r"0[xX][0-9a-fA-F]+", n):
                return n
            if n in self.econst:
                v = self.econst[n]
            elif n in self.consts:
                v = self.evalx(self.consts[n], depth + 1)
            else:
                return "None"
            return "None" if v is None else str(v)
        e = re.sub(r"\b[A-Za-z_]\w*\b|\b0[xX][0-9a-fA-F]+\b", ident, e)
        if "None" in e or not re.fullmatch(r"[\s0-9a-fA-FxX+\-*/%<>&|()~^]*", e):
            return None
        e = e.replace("/", "//")
        try:
            v = eval(e, {"__builtins__": {}}, {})
        except Exception:
            return None
        return v if isinstance(v, int) and v >= 0 else None

    def sizeof(self, text, quiet=False, depth=0):
        """(size, align); (None, None) when unknown."""
        t = re.sub(r"__declspec\s*\([^)]*\)", " ", text)
        t = STRIP_QUALS.sub(" ", t)
        t = " ".join(t.split())
        if not t:
            return (None, None)
        if "::*" in t:
            return self._unk("member-pointer", text, quiet)
        if re.search(r"[*&^]", t):
            return (4, 4)
        if "<" in t:
            if t in self.types:
                return self._ret(self.types[t])
            return self._unk("template-instance", text, quiet)
        words = t.split()
        if words and all(w in BUILTIN_WORDS for w in words):
            s = set(words)
            if "__int64" in s or words.count("long") == 2 or "double" in s:
                return (8, 8)
            if "float" in s:
                return (4, 4)
            if "char" in s or "__int8" in s or "bool" in s:
                return (1, 1)
            if "short" in s or "__int16" in s or "wchar_t" in s or "char16_t" in s:
                return (2, 2)
            if "void" in s:
                return self._unk("void-by-value", text, quiet)
            return (4, 4)
        name = t
        if name in self.types:
            return self._ret(self.types[name])
        last = name.split("::")[-1].strip()
        if last in self.types:
            return self._ret(self.types[last])
        if last in self.enums:
            return (self.enums[last], self.enums[last])
        if name in self.typedefs or last in self.typedefs:
            if depth > 6:
                return self._unk("typedef-loop", text, quiet)
            return self.sizeof(self.typedefs.get(name) or self.typedefs[last], quiet, depth + 1)
        if last in KNOWN:
            return (KNOWN[last], min(KNOWN[last], 8))
        return self._unk("unknown-type:" + last, text, quiet)

    def _ret(self, ty):
        if ty["size"] is None:
            self.reasons.append(("incomplete-or-unsized-type", ty.get("name") or "?"))
            return (None, None)
        return (ty["size"], ty["align"])

    def _unk(self, why, text, quiet):
        if not quiet:
            self.reasons.append((why, text.strip()))
        return (None, None)


def rnd(x, a):
    return (x + a - 1) // a * a


class Layout:
    def __init__(self, pack, union=False):
        self.off = 0
        self.maxalign = 1
        self.pack = pack
        self.union = union
        self.usize = 0
        self.bf = None          # (unit_off, unit_size, used_bits, unit_align)
        self.nodata = True
        self.bad = False

    def place(self, size, align):
        """Return the member offset (None if unknown) and advance."""
        if self.union:
            self.nodata = False
            if size is None or align is None:
                self.bad = True
                self.usize = None
                return 0
            self.maxalign = max(self.maxalign, min(align, self.pack))
            self.usize = None if self.usize is None else max(self.usize, size)
            return 0
        self.close_bf()
        self.nodata = False
        if size is None or align is None:
            self.bad = True
            off = self.off if (self.off is not None and self.off % 8 == 0) else None
            self.off = None
            return off
        a = min(align, self.pack)
        self.maxalign = max(self.maxalign, a)
        if self.off is None:
            return None
        self.off = rnd(self.off, a)
        o = self.off
        self.off += size
        return o

    def close_bf(self):
        if self.bf is not None:
            uo, us, used, ua = self.bf
            self.bf = None
            if self.off is not None:
                self.off = uo + us

    def bitfield(self, size, align, width):
        self.nodata = False
        if self.union:
            self.maxalign = max(self.maxalign, min(align, self.pack))
            self.usize = None if self.usize is None else max(self.usize, size)
            return 0, 0
        if self.off is None:
            return None, None
        a = min(align, self.pack)
        if width == 0:
            self.close_bf()
            self.off = rnd(self.off, a)
            return self.off, 0
        if self.bf is not None:
            uo, us, used, ua = self.bf
            if us == size and used + width <= us * 8:
                self.bf = (uo, us, used + width, ua)
                return uo, used
            self.close_bf()
        self.maxalign = max(self.maxalign, a)
        self.off = rnd(self.off, a)
        self.bf = (self.off, size, width, a)
        return self.bf[0], 0

    def finish(self):
        if self.union:
            if self.usize is None or self.bad:
                return None, self.maxalign
            if self.nodata:
                return 1, 1
            return rnd(self.usize, self.maxalign), self.maxalign
        self.close_bf()
        if self.off is None:
            return None, self.maxalign
        if self.nodata:
            return 1, 1
        return rnd(self.off, self.maxalign), self.maxalign


class Parser:
    def __init__(self, sl, ctx, fails):
        self.sl, self.ctx, self.fails = sl, ctx, fails
        self.defs = []
        self.spans = []

    def fail(self, src, pos, reason, detail=""):
        self.fails.append({"file": src.rel, "line": src.line(pos), "reason": reason, "detail": detail[:160]})

    def statements(self, body, base):
        """Statements of a class body: ('decl', text, pos) | ('def', head, istart, iend, trailer, pos) |
        ('method', head, pos) | ('broken'|'tail', text, pos)."""
        i, n = 0, len(body)
        res = []
        cur_start = None
        while i < n:
            c = body[i]
            if cur_start is None:
                if c.isspace():
                    i += 1
                    continue
                cur_start = i
            if c == ";":
                res.append(("decl", body[cur_start:i], base + cur_start))
                cur_start = None
                i += 1
                continue
            if c == "{":
                head = body[cur_start:i]
                end = match_brace(body, i)
                if end is None:
                    res.append(("broken", head, base + cur_start))
                    return res
                hs = re.sub(r"\[[^\]]*\]", "", head)
                hh = re.sub(r"^(?:\s*(?:public|private|protected)\s*:)*\s*", "", head)
                hh2 = re.sub(r"\b(typedef|friend)\b", "", hh).strip()
                is_def = re.match(r"(struct|class|union|enum)\b", hh2) and "(" not in hs
                if is_def:
                    j = end
                    while j < n and body[j] != ";":
                        j += 1
                    res.append(("def", head, base + i + 1, base + end - 1, body[end:j], base + cur_start))
                    cur_start = None
                    i = j + 1
                    continue
                if "(" in hs:
                    res.append(("method", head, base + cur_start))
                    cur_start = None
                    i = end
                    while i < n and body[i] in " \t\r\n":
                        i += 1
                    if i < n and body[i] == ";":
                        i += 1
                    continue
                body = body[:i] + " " * (end - i) + body[end:]     # brace initialiser on a data member
                continue
            i += 1
        if cur_start is not None and body[cur_start:].strip():
            res.append(("tail", body[cur_start:], base + cur_start))
        return res

    def parse_def(self, src, kind, name, bases_txt, inner_start, inner_end, pos, parent=None):
        ctx = self.ctx
        text = src.text
        body = text[inner_start:inner_end]
        pack = src.pack_at(pos)
        d = {"name": name, "slice": self.sl, "file": src.rel, "line": src.line(pos), "kind": kind, "bases": [],
             "base_layout": [], "vptr": False, "members": [], "size": None, "size_known": False, "align": None,
             "complete": False, "problems": [], "parent": parent, "pack": pack}
        lay = Layout(pack, union=(kind == "union"))
        problems = d["problems"]
        reasons_mark = len(ctx.reasons)
        uncertain = False
        if any(inner_start <= p <= inner_end for p, _ in src.cond_lines):
            problems.append("pp-conditional-in-body")
            uncertain = True
            self.fail(src, pos, "pp-conditional-in-body", name or "")
        if re.search(r"__declspec\s*\(\s*align|alignas", text[pos:inner_start]):
            problems.append("align-attribute")
            uncertain = True
            self.fail(src, pos, "align-attribute", name or "")
        base_infos = []
        if bases_txt:
            for b in split_top(bases_txt.lstrip(":")):
                b = b.strip()
                if not b:
                    continue
                virt = bool(re.search(r"\bvirtual\b", b))
                b = re.sub(r"\b(public|private|protected|virtual)\b", "", b).strip()
                d["bases"].append(b)
                if virt:
                    problems.append("virtual-base")
                    uncertain = True
                    self.fail(src, pos, "virtual-base", "%s : %s" % (name, b))
                base_infos.append(b)
        stmts = self.statements(body, inner_start)
        own_virtual = any(st[0] in ("method", "decl") and re.search(r"\bvirtual\b", st[1]) for st in stmts)
        base_vptr = 0
        base_recs = []
        for b in base_infos:
            nm = b.split("::")[-1].strip()
            info = ctx.types.get(b) or ctx.types.get(nm)
            base_recs.append((b, info))
            if info and info.get("vptr"):
                base_vptr += 1
        if base_vptr > 1:
            problems.append("multiple-vptr-bases")
            uncertain = True
            self.fail(src, pos, "multiple-vptr-bases", name or "")
        first_vptr = bool(base_recs and base_recs[0][1] and base_recs[0][1].get("vptr"))
        has_vptr = bool(base_vptr or own_virtual)
        d["vptr"] = has_vptr
        if kind != "union":
            if own_virtual and not first_vptr and base_vptr == 0:
                lay.place(4, 4)
            elif own_virtual and not first_vptr and base_vptr:
                problems.append("vptr-not-in-first-base")
                uncertain = True
                self.fail(src, pos, "vptr-not-in-first-base", name or "")
        for b, info in base_recs:
            if info is None or info["size"] is None:
                lay.place(None, None)
                d["base_layout"].append({"name": b, "offset": None, "size": None})
                problems.append("unknown-base:" + b)
                self.fail(src, pos, "unknown-base", "%s : %s" % (name, b))
                continue
            if info.get("empty"):
                d["base_layout"].append({"name": b, "offset": lay.off if not lay.union else 0, "size": 0})
                continue
            o = lay.place(info["size"], info["align"])
            d["base_layout"].append({"name": b, "offset": o, "size": info["size"]})
        for st in stmts:
            k = st[0]
            if k == "broken":
                self.fail(src, st[2], "unbalanced-braces", st[1][:60])
                uncertain = True
            elif k == "tail":
                if st[1].strip():
                    self.fail(src, st[2], "unterminated-statement", st[1].strip()[:60])
                    uncertain = True
            elif k == "def":
                self.member_def(src, d, lay, st[1], st[2], st[3], st[4], st[5], pack)
            elif k == "decl":
                self.member_decl(src, d, lay, st[1], st[2], pack)
        size, align = lay.finish()
        if kind != "union" and lay.nodata and not has_vptr and not base_recs:
            size, align = 1, 1
        empty = (kind != "union" and not has_vptr and lay.nodata and all((i and i.get("empty")) for _, i in base_recs))
        if uncertain:
            for m in d["members"]:
                m["offset"] = None
            for b in d["base_layout"]:
                b["offset"] = None
            size = None
        new = ctx.reasons[reasons_mark:]
        del ctx.reasons[reasons_mark:]
        seen = set()
        for why, detail in new:
            if (why, detail) in seen:
                continue
            seen.add((why, detail))
            problems.append(why if why.startswith("unknown-type") else why + ":" + detail)
            self.fail(src, pos, why.split(":")[0], (why + " " + detail) if why.startswith("unknown-type") else detail)
        d["size"] = size
        d["size_known"] = size is not None
        d["align"] = align if size is not None else None
        d["complete"] = bool(size is not None and not uncertain and
                             all(m["offset"] is not None and m["size"] is not None for m in d["members"]))
        rec = {"name": name, "size": size, "align": d["align"], "empty": bool(empty and size == 1), "vptr": has_vptr}
        if name:
            ctx.types[name] = rec
        d["_rec"] = rec
        return d

    def member_def(self, src, d, lay, head, istart, iend, trailer, spos, pack):
        ctx = self.ctx
        h = re.sub(r"^(?:\s*(?:public|private|protected)\s*:)*\s*", "", head).strip()
        h = re.sub(r"\b(typedef|friend)\b", "", h).strip()
        em = re.match(r"enum\b\s*(?:class\s+|struct\s+)?(\w+)?\s*(?::\s*([\w\s]+))?$", h)
        if em:
            nm = em.group(1)
            sz = 4
            if em.group(2):
                r = ctx.sizeof(em.group(2), quiet=True)
                sz = r[0] if r and r[0] else 4
            self.register_enum(nm, sz, src.text[istart:iend])
            if trailer.strip():
                self.member_decl(src, d, lay, "%s %s" % (nm if nm else "int", trailer), spos, pack)
            return
        m = re.match(r"(struct|class|union)\s*(?:__declspec\s*\([^)]*\)\s*)?([A-Za-z_]\w*)?\s*(:(?!:)[^{]*)?$", h)
        if not m:
            self.fail(src, spos, "unparsed-nested-definition", h[:60])
            return
        kind, nm, bases = m.group(1), m.group(2), m.group(3)
        sub = self.parse_def(src, kind, nm, bases, istart, iend, spos, parent=d["name"])
        self.defs.append(sub)
        tr = trailer.strip()
        if not tr:
            if nm is None:
                sz, al = sub["size"], sub["align"]
                if sz is None or al is None:
                    lay.place(None, None)
                    base_off = None
                else:
                    base_off = lay.place(sz, al)
                for mm in sub["members"]:
                    mm2 = {k: v for k, v in mm.items()}
                    mm2["offset"] = None if (base_off is None or mm["offset"] is None) else base_off + mm["offset"]
                    mm2["anon"] = True
                    d["members"].append(mm2)
            return
        tname = nm
        if tname is None:
            tname = "<anon-%s@%d>" % (kind, sub["line"])
            ctx.types[tname] = sub["_rec"]
        self.member_decl(src, d, lay, "%s %s" % (tname, tr), spos, pack)

    def register_enum(self, nm, sz, body):
        ctx = self.ctx
        if nm:
            ctx.enums[nm] = sz
        val = -1
        for ent in split_top(body):
            ent = ent.strip()
            if not ent:
                continue
            m = re.match(r"(\w+)\s*(?:=\s*(.+))?$", ent, re.S)
            if not m:
                continue
            if m.group(2):
                v = ctx.evalx(m.group(2))
            else:
                v = None if val is None else val + 1
            ctx.econst[m.group(1)] = v
            val = v

    def member_decl(self, src, d, lay, text, pos, pack):
        n0 = len(d["members"])
        self._member_decl(src, d, lay, text, pos, pack)
        ln = src.line(pos + len(text))
        raw = src.rawlines[ln - 1] if 0 < ln <= len(src.rawlines) else ""
        mc = re.search(r"//\s*(?:\+|off(?:set)?\s*)?0x([0-9a-fA-F]+)\b", raw)
        for m in d["members"][n0:]:
            m["line"] = ln
            if mc and len(d["members"]) - n0 == 1:
                m["comment_offset"] = int(mc.group(1), 16)

    def _member_decl(self, src, d, lay, text, pos, pack):
        ctx = self.ctx
        t = re.sub(r"^(?:\s*(?:public|private|protected)\s*:)*\s*", "", text).strip()
        t = re.sub(r"__declspec\s*\([^)]*\)", " ", t).strip()
        if not t:
            return
        if re.match(r"(typedef|using|friend|template)\b", t) or re.match(r"static\b", t):
            return
        if re.match(r"(struct|class|union|enum)\s+\w+(\s*,\s*\w+)*$", t) or re.match(r"(public|private|protected)\s*:?$", t):
            return
        fm = FPTR_RE.search(t)
        if fm:
            cnt = 1
            if fm.group(2):
                cnt = self.dims_count(src, pos, re.findall(r"\[([^\]]*)\]", t[fm.start():fm.end()]))
            self.emit(d, lay, fm.group(1), "fnptr", (4 * cnt if cnt is not None else None), 4, cnt)
            return
        if "(" in re.sub(r"\[[^\]]*\]", "[]", t):
            return                                    # method declaration
        if re.fullmatch(r"[\w:]+", t):
            self.fail(src, pos, "unparsed-statement", t[:60])
            return
        parts = split_top(t)
        first = parts[0]
        first = re.sub(r"\s*=[^\[\]]*$", "", first, flags=re.S)
        m = re.match(r"(?P<ty>.*?[\w>\]\*&\s])\s*(?P<pre>[\*&\s]*)(?P<name>[A-Za-z_]\w*)\s*(?P<dims>(?:\[[^\]]*\]\s*)*)(?:(?<!:):(?!:)\s*(?P<bits>[^,]+))?$",
                     first.strip(), re.S)
        if not m or not m.group("ty").strip():
            self.fail(src, pos, "unparsed-statement", t[:70])
            lay.place(None, None)
            return
        ty = m.group("ty").strip()
        mm = re.match(r"(.*?)((?:[\*&]\s*(?:const\s*|volatile\s*)*)*)$", ty, re.S)
        basety, stars0 = (mm.group(1).strip(), mm.group(2)) if mm else (ty, "")
        if not basety:
            self.fail(src, pos, "unparsed-statement", t[:70])
            lay.place(None, None)
            return
        decls = [(stars0 + m.group("pre"), m.group("name"), m.group("dims"), m.group("bits"))]
        for p in parts[1:]:
            p = re.sub(r"\s*=[^\[\]]*$", "", p, flags=re.S)
            m2 = re.match(r"\s*(?P<st>(?:[\*&]\s*(?:const\s*|volatile\s*)*)*)(?P<name>[A-Za-z_]\w*)\s*(?P<dims>(?:\[[^\]]*\]\s*)*)(?:(?<!:):(?!:)\s*(?P<bits>.+))?$", p, re.S)
            if not m2:
                self.fail(src, pos, "unparsed-declarator", p.strip()[:60])
                lay.place(None, None)
                continue
            decls.append((m2.group("st"), m2.group("name"), m2.group("dims"), m2.group("bits")))
        for stars, name, dims, bits in decls:
            ptr = bool(re.search(r"[\*&]", stars))
            esz, eal = (4, 4) if ptr else ctx.sizeof(basety)
            dl = re.findall(r"\[([^\]]*)\]", dims or "")
            tytxt = re.sub(r"\s+", " ", basety + (" " + stars.strip() if stars.strip() else "")).strip()
            pad = bool(PAD_RE.search(name))
            if bits is not None:
                w = ctx.evalx(bits)
                if w is None or esz is None or dl:
                    self.fail(src, pos, "bitfield-unsized", t[:70])
                    lay.place(None, None)
                    d["members"].append({"name": name, "offset": None, "size": None, "type": tytxt + ":" + bits.strip(), "pad": pad})
                    continue
                o, bp = lay.bitfield(esz, eal, w)
                d["members"].append({"name": name, "offset": o, "size": esz, "type": tytxt, "pad": pad, "bit": [bp, w]})
                continue
            cnt = self.dims_count(src, pos, dl) if dl else 1
            size = None if (esz is None or cnt is None) else esz * cnt
            self.emit(d, lay, name, tytxt + "".join("[%s]" % x.strip() for x in dl), size, eal, cnt)

    def dims_count(self, src, pos, dl):
        n = 1
        for x in dl:
            x = x.strip()
            if x == "":
                return 0
            v = self.ctx.evalx(x)
            if v is None:
                self.fail(src, pos, "unevaluable-array-dim", x[:60])
                return None
            n *= v
        return n

    def emit(self, d, lay, name, ty, size, align, cnt):
        off = lay.place(size, align)
        d["members"].append({"name": name, "offset": off, "size": size, "type": ty, "pad": bool(PAD_RE.search(name))})

    def scan(self, src):
        text = src.text
        for m in re.finditer(r"\btypedef\s+(?!(?:struct|union|class|enum)\b[^;]*\{)([^;{}]*?)\s*;", text):
            decl = m.group(1)
            fm = FPTR_RE.search(decl)
            if fm:
                self.ctx.typedefs[fm.group(1)] = "void*"
                continue
            if "(" in decl:
                continue
            mm = re.match(r"(.*?[\w>\s\*&])\s*(\w+)\s*((?:\[[^\]]*\]\s*)*)$", decl.strip(), re.S)
            if mm and not mm.group(3).strip():
                self.ctx.typedefs[mm.group(2)] = mm.group(1).strip()
        for m in re.finditer(r"\busing\s+(\w+)\s*=\s*([^;{}]+);", text):
            self.ctx.typedefs[m.group(1)] = m.group(2).strip()
        for m in re.finditer(r"\b(?:static\s+)?const(?:expr)?\s+(?:unsigned\s+|signed\s+)?(?:int|long|short|uint32_t|size_t|int32_t)\s+(\w+)\s*=\s*([^;{}]+);", text):
            self.ctx.consts.setdefault(m.group(1), m.group(2).strip())
        for k, v in src.consts.items():
            self.ctx.consts.setdefault(k, v)
        pos = 0
        while True:
            md = DECL_RE.search(text, pos)
            me = ENUM_RE.search(text, pos)
            cand = [x for x in (md, me) if x]
            if not cand:
                break
            m = min(cand, key=lambda x: x.start())
            end = match_brace(text, m.end() - 1)
            if end is None:
                self.fail(src, m.start(), "unbalanced-braces", "")
                pos = m.end()
                continue
            if m is me:
                sz = 4
                if m.group(3):
                    r = self.ctx.sizeof(m.group(3), quiet=True)
                    sz = r[0] if r and r[0] else 4
                self.register_enum(m.group(2), sz, text[m.end():end - 1])
                pos = end
                continue
            kind, name, bases = m.group(2), m.group(3), m.group(4)
            before = text[max(0, m.start() - 200):m.start()]
            if re.search(r"\b(enum|friend)\s+$", before):
                pos = m.end()
                continue
            if re.search(r"template\s*<[^;{}]*>\s*$", before):
                self.fail(src, m.start(), "template-definition", name or "")
                pos = end
                continue
            tail_end = text.find(";", end)
            trailer = text[end:tail_end] if tail_end != -1 and tail_end - end < 200 and "{" not in text[end:tail_end] else ""
            name2 = name
            if m.group(1) and not name:
                tn = re.findall(r"[A-Za-z_]\w*", trailer)
                name2 = tn[0] if tn else None
            if name2 is None:
                pos = end
                continue
            d = self.parse_def(src, kind, name2, bases, m.end(), end - 1, m.start())
            self.defs.append(d)
            self.spans.append((m.start(), end))
            if m.group(1) and name:
                for nm2 in re.findall(r"\b([A-Za-z_]\w*)\b", trailer):
                    if nm2 != name2:
                        self.ctx.typedefs.setdefault(nm2, name2)
            pos = end


def load_vas(path, col):
    out = []
    if not os.path.exists(path):
        return out
    for ln in rd(path).splitlines():
        p = ln.split()
        if len(p) > col:
            try:
                out.append("%08x" % int(p[col], 16))
            except ValueError:
                pass
    return out


def sections(srcs):
    """{va: identifier set} from definition-masked text, one section per '// @ 0x<va>' marker."""
    secs = {}
    for src, spans in srcs:
        t = src.text
        parts, last = [], 0
        for a, b in sorted(spans):
            if a < last:
                continue
            parts.append(t[last:a])
            parts.append(re.sub(r"[^\n]", " ", t[a:b]))
            last = b
        parts.append(t[last:])
        t = "".join(parts)
        marks = [(m.start(), "%08x" % int(m.group(1), 16)) for m in MARK_RE.finditer(src.raw)]
        for i, (p, va) in enumerate(marks):
            e = marks[i + 1][0] if i + 1 < len(marks) else len(t)
            secs.setdefault(va, set()).update(re.findall(r"[A-Za-z_]\w*", t[p:e]))
    return secs


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=OUT)
    ap.add_argument("--only", help="comma separated slice ids (debug)")
    ap.add_argument("--print", dest="show", help="comma separated struct names to print")
    a = ap.parse_args()
    ids = sorted(x for x in os.listdir(SLICES) if os.path.isdir(os.path.join(SLICES, x)))
    if a.only:
        ids = [x for x in ids if x in a.only.split(",")]
    defs, fails = [], []
    for sid in ids:
        sd = os.path.join(SLICES, sid)
        files = sorted(glob.glob(os.path.join(sd, "**", "*.h"), recursive=True) + glob.glob(os.path.join(sd, "**", "*.hpp"), recursive=True))
        files += sorted(glob.glob(os.path.join(sd, "*.cpp")))
        if not files:
            continue
        ctx = Ctx()
        srcs, slice_defs = [], []
        for f in files:
            rel = os.path.relpath(f, ROOT)
            try:
                sr = Src(f, rel)
            except Exception as ex:
                fails.append({"file": rel, "line": 0, "reason": "read-error", "detail": str(ex)})
                continue
            p = Parser(sid, ctx, fails)
            try:
                p.scan(sr)
            except RecursionError:
                fails.append({"file": rel, "line": 0, "reason": "recursion", "detail": ""})
            slice_defs += p.defs
            srcs.append((sr, p.spans))
        secs = sections(srcs)
        exact = set(load_vas(os.path.join(sd, "manifest.txt"), 2))
        equiv = set(load_vas(os.path.join(sd, "nonmatching.txt"), 0))
        for d in slice_defs:
            d.pop("_rec", None)
            nm = d["name"]
            ex_n, eq_n, ex, eq, me = set(), set(), set(), set(), set()
            mem_names = [m["name"] for m in d["members"] if not m["pad"]]
            for m in d["members"]:
                m["exact_users"], m["equiv_users"] = [], []
            for va, ids_ in secs.items():
                named = nm in ids_
                for m in d["members"]:
                    if not m["pad"] and m["name"] in ids_:
                        if va in exact:
                            m["exact_users"].append(va)
                        elif va in equiv:
                            m["equiv_users"].append(va)
                if not (named or any(x in ids_ for x in mem_names)):
                    continue
                if va in exact:
                    ex.add(va)
                    if named:
                        ex_n.add(va)
                elif va in equiv:
                    eq.add(va)
                    if named:
                        eq_n.add(va)
                else:
                    me.add(va)
            d["exact_users"], d["exact_name_users"] = sorted(ex), sorted(ex_n)
            d["equiv_users"], d["equiv_name_users"] = sorted(eq), sorted(eq_n)
            d["mentions"] = sorted(me)
        defs += slice_defs
    by_name = collections.defaultdict(list)
    for i, d in enumerate(defs):
        if d["name"]:
            by_name[d["name"]].append(i)
    conflicts = {}
    for nm, idxs in by_name.items():
        if len(idxs) < 2:
            continue
        mm = collections.defaultdict(list)
        for i in idxs:
            for m in defs[i]["members"]:
                if not m["pad"] and m["offset"] is not None:
                    mm[m["name"]].append((i, m))
        out = []
        for mname, lst in mm.items():
            if len(lst) < 2:
                continue
            offs = {m["offset"] for _, m in lst}
            szs = {m["size"] for _, m in lst if m["size"] is not None}
            if len(offs) < 2 and len(szs) < 2:
                continue
            views = [{"def": i, "slice": defs[i]["slice"], "offset": m["offset"], "size": m["size"],
                      "view_exact": bool(defs[i]["exact_users"]), "member_exact": bool(m["exact_users"])} for i, m in lst]
            if any(v["view_exact"] for v in views):
                out.append({"member": mname, "views": views})
        if out:
            conflicts[nm] = out
    fc = collections.Counter(f["reason"] for f in fails)

    def n_with(pred):
        return sum(1 for v in conflicts.values() if any(pred(c) for c in v))
    summary = {"definitions": len(defs), "complete": sum(1 for d in defs if d["complete"]),
               "size_known": sum(1 for d in defs if d["size_known"]),
               "names": len(by_name), "names_multi_view": sum(1 for v in by_name.values() if len(v) > 1),
               "exact_backed_defs": sum(1 for d in defs if d["exact_users"]),
               "names_conflict_view_level": len(conflicts),
               "names_conflict_member_exact_one_side": n_with(lambda c: any(x["member_exact"] for x in c["views"])),
               "names_conflict_member_exact_two_sides": n_with(lambda c: sum(1 for x in c["views"] if x["member_exact"]) >= 2
                                                              and len({x["offset"] for x in c["views"] if x["member_exact"]}) > 1),
               "members_with_offset_comment": sum(1 for d in defs for m in d["members"] if "comment_offset" in m and m["offset"] is not None),
               "offset_comment_mismatches": sum(1 for d in defs for m in d["members"] if "comment_offset" in m and m["offset"] is not None and m["offset"] != m["comment_offset"]),
               "failures": len(fails)}
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    json.dump({"summary": summary, "failure_counts": dict(fc.most_common()), "by_name": by_name, "conflicts": conflicts,
               "defs": defs, "failures": fails}, open(a.out, "w"), separators=(",", ":"))
    print(json.dumps(summary, indent=1))
    print("failure reasons:", dict(fc.most_common()))
    if a.show:
        for nm in a.show.split(","):
            for i in by_name.get(nm, []):
                d = defs[i]
                print("== %s [%s] %s:%d kind=%s size=%s vptr=%s bases=%s complete=%s exact=%s equiv=%s" % (
                    d["name"], d["slice"], d["file"], d["line"], d["kind"], d["size"] and hex(d["size"]), d["vptr"], d["bases"],
                    d["complete"], d["exact_users"], d["equiv_users"]))
                for m in d["members"]:
                    o = m["offset"]
                    print("   %-6s %-5s %-28s %s%s" % ("?" if o is None else hex(o), "?" if m["size"] is None else hex(m["size"]),
                                                       m["name"], m["type"], " pad" if m["pad"] else ""))


if __name__ == "__main__":
    sys.exit(main())
