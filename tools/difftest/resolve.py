"""Resolve the relocations of OUR compiled function to ORIGINAL image addresses.

For every symbol our function (and the local helpers/data it pulls in) references, find the
address the original binary uses for it, so both versions call the same real callees and touch
the same real globals. Methods, tried in order (the report records which one fired):

  import        __imp_X -> the IAT slot of X; a direct reference to an import -> its image thunk
  crt           compiler helpers (__chkstk, __ftol2_sse, ___security_cookie, ...) from lib_names.txt
  symbols       exact mangled name in symbols/*.txt, symbols/slices/*.txt, pdb_globals.json, or a
                unique qualified name there (only when our object has no overload of that name)
  hex-name      an address embedded in the name (FUN_00abcdef, Fn9467b0, g_01582df8, ..._0167a6d0)
  annotation    a '// 0x...' comment on the declaration line (or a '// @ 0x...' marker above it)
                in the slice source, matched by identifier and enclosing class
  rdata-literal string literals found byte-identical in the image's .rdata
  align         the N-th call/global reference of ours vs the original's N-th one, between
                already-resolved anchors, when gap lengths and instruction mnemonics agree
A reference that none of these resolves makes the function UNSUPPORTED (never guessed).
Locally defined helpers/constants with no original address are loaded from our object.
"""
import bisect, difflib, glob, json, os, re, struct, sys
from collections import defaultdict

import capstone
from capstone import x86_const as X

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(ROOT, "tools", "matching"))
sys.path.insert(0, HERE)
import imgcache  # noqa: E402
from coff import REL_DIR32, REL_REL32, REL_DIR32NB, REL_SECREL, REL_SECTION  # noqa: E402
from slice import base_ident, demangle_qual  # noqa: E402
from machine import BUILTIN_ADDR  # noqa: E402

EH_PREFIXES = ("??_R", "__ehhandler$", "__unwindfunclet$", "__ehfuncinfo$", "__unwindtable$", "__catchsym$",
               "__tryblocktable$", "__catch$", "__tryend$", "__catchblock", "$unwind", "__ehvec", "__TI", "__CT", "__CTA")
LOCAL_CONST_PREFIXES = ("__real@", "__xmm@", "__mask@", "__int64@", "??_C@", "__fltused")
HEX_RE = re.compile(r"(?<![0-9A-Fa-f])(?:0x)?([0-9A-Fa-f]{6,8})(?![0-9A-Fa-f])")
ADDR_IN_COMMENT = re.compile(r"(?:\b0x([0-9A-Fa-f]{6,8})|(?:\b|DAT_|FUN_|PTR_|LAB_|g_|_)([0-9A-Fa-f]{8}))\b")

_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
_md.detail = True


# ------------------------------------------------------------------ the original image

class Image:
    """Static facts about the analysis image shared by every test."""

    def __init__(self, path=os.path.join(ROOT, "work", "SporeApp.analysis.bin")):
        import pefile
        from card import load_funcs
        self.path = path
        self.pe = pefile.PE(path, fast_load=True)
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.size = (self.pe.OPTIONAL_HEADER.SizeOfImage + 0xFFF) & ~0xFFF
        self.sections = []
        for s in self.pe.sections:
            nm = s.Name.rstrip(b"\0").decode()
            self.sections.append((nm, self.base + s.VirtualAddress, max(s.Misc_VirtualSize, s.SizeOfRawData),
                                  s.Characteristics))
        self.relocs = imgcache.relocs(path)            # sorted RVAs of HIGHLOW base relocations
        self.imports = imgcache.imports(path)          # {IAT VA: "dll!name"}
        self.import_by_name = {}
        for va, nm in self.imports.items():
            self.import_by_name.setdefault(nm.split("!", 1)[1], va)
        self.starts, self.names = load_funcs()
        self.start_set = set(self.starts)
        self._mem = {}
        self._thunks = None

    def section(self, name):
        for nm, va, size, ch in self.sections:
            if nm == name:
                return va, size
        return None

    def read(self, va, n):
        return self.pe.get_data(va - self.base, n)

    def u32(self, va):
        return struct.unpack("<I", self.read(va, 4))[0]

    def in_image(self, va):
        return self.base <= va < self.base + self.size

    def in_text(self, va):
        t = self.section(".text")
        return t[0] <= va < t[0] + t[1]

    def in_data(self, va):
        for nm, a, size, ch in self.sections:
            if nm in (".rdata", ".data", ".tls", "CONST") and a <= va < a + size:
                return True
        return False

    def is_reloc(self, va):
        rva = va - self.base
        i = bisect.bisect_left(self.relocs, rva)
        return i < len(self.relocs) and self.relocs[i] == rva

    def reloc_positions(self, va, n):
        rva = va - self.base
        i = bisect.bisect_left(self.relocs, rva - 3)
        out = []
        while i < len(self.relocs) and self.relocs[i] < rva + n:
            out.append(self.relocs[i] + self.base)
            i += 1
        return out

    def func_extent(self, va):
        i = bisect.bisect_right(self.starts, va)
        end = self.starts[i] if i < len(self.starts) else va + 0x1000
        data = self.read(va, end - va)
        n = len(data)
        while n > 0 and data[n - 1] == 0xCC:
            n -= 1
        return va, va + n

    def thunks(self):
        """{import name: VA of a 'jmp [IAT]' thunk in .text}."""
        if self._thunks is None:
            self._thunks = {}
            t0, tn = self.section(".text")
            text = self.read(t0, tn)
            i = text.find(b"\xff\x25")
            while i >= 0:
                if i + 6 <= len(text):
                    iat = struct.unpack_from("<I", text, i + 2)[0]
                    nm = self.imports.get(iat)
                    if nm:
                        name = nm.split("!", 1)[1]
                        va = t0 + i
                        if name not in self._thunks or (va in self.start_set and self._thunks[name] not in self.start_set):
                            self._thunks[name] = va
                i = text.find(b"\xff\x25", i + 1)
        return self._thunks

    def rdata_find(self, blob):
        """VA of blob in .rdata at a string start (preceded by a NUL), or None."""
        r = self.section(".rdata")
        if r is None or not blob:
            return None
        key = ("rdata",)
        if key not in self._mem:
            self._mem[key] = self.read(r[0], r[1])
        data = self._mem[key]
        i = data.find(blob)
        while i >= 0:
            if i == 0 or data[i - 1] == 0:
                return r[0] + i
            i = data.find(blob, i + 1)
        return None


# ------------------------------------------------------------------ symbol databases

class SymbolDB:
    def __init__(self, image):
        self.mangled = defaultdict(set)   # exact mangled name -> {va}
        self.qual = defaultdict(set)      # qualified name -> {va}
        self.lib = {}                     # lib_crt helper short name -> va
        files = glob.glob(os.path.join(ROOT, "symbols", "*.txt")) + glob.glob(os.path.join(ROOT, "symbols", "slices", "*.txt"))
        for f in files:
            for line in open(f, encoding="utf-8", errors="replace"):
                p = line.split("#", 1)[0].strip().split(None, 1)
                if len(p) < 2:
                    continue
                try:
                    va = int(p[0], 16)
                except ValueError:
                    continue
                nm = p[1].strip()
                m = re.match(r"lib_(\w+)::(.*)", nm)
                if m:
                    nm = m.group(2)
                    if m.group(1) == "crt":
                        self.lib[nm.lstrip("_")] = va
                if nm.startswith(("?", "@")) or (nm.startswith("_") and "::" not in nm):
                    self.mangled[nm].add(va)
                    q = demangle_qual(nm)
                    if q:
                        self.qual[q].add(va)
                else:
                    self.qual[nm].add(va)
        try:
            for k, v in json.load(open(os.path.join(ROOT, "symbols", "pdb_globals.json"))).items():
                nm = v["name"]
                (self.mangled if nm.startswith("?") else self.qual)[nm].add(int(k, 16))
        except (OSError, ValueError):
            pass
        try:
            for k, v in json.load(open(os.path.join(ROOT, "symbols", "pdb_names.json"))).items():
                self.qual[v["name"]].add(int(k, 16))
        except (OSError, ValueError):
            pass


# ------------------------------------------------------------------ source annotations

def source_annotations(paths):
    """[(ident, scopes tuple, va, line)] from '// 0x...' comments on declaration lines and
    '// @ 0x...' markers (which name the next definition)."""
    out = []
    for path in paths:
        if not os.path.exists(path):
            continue
        lines = open(path, encoding="utf-8", errors="replace").read().split("\n")
        scopes = []        # [(name, depth at which it opened)]
        depth = 0
        pending = None     # class/struct/namespace name waiting for its '{'
        marker_va = None
        in_block_comment = False
        logical = []       # (line no, code, comment): physical lines joined while '(' is open
        buf = None
        for ln, raw in enumerate(lines, 1):
            line = raw
            if in_block_comment:
                if "*/" in line:
                    line = line[line.index("*/") + 2:]
                    in_block_comment = False
                else:
                    continue
            code, _, comment = line.partition("//")
            code = re.sub(r"/\*.*?\*/", "", code)
            if "/*" in code:
                code = code[:code.index("/*")]
                in_block_comment = True
            code = re.sub(r'"(\\.|[^"\\])*"', '""', code)
            if buf is not None:
                buf = (buf[0], buf[1] + " " + code.strip(), buf[2] + " " + comment)
            else:
                buf = (ln, code, comment)
            if buf[1].count("(") > buf[1].count(")") and ln - buf[0] < 12:
                continue
            logical.append(buf)
            buf = None
        if buf is not None:
            logical.append(buf)
        for ln, code, comment in logical:
            va = None
            for m in ADDR_IN_COMMENT.finditer(comment):
                v = int(m.group(1) or m.group(2), 16)
                if 0x401000 <= v < 0x1900000:
                    va = v
                    break
            if re.search(r"@\s*0x[0-9A-Fa-f]{6,8}", comment) and not code.strip():
                marker_va = va
            cm = re.search(r"\b(class|struct|union|namespace)\s+(?:__declspec\([^)]*\)\s*)?([A-Za-z_]\w*)?[^;()]*$", code)
            if cm and "(" not in code.split(cm.group(0))[0][-1:]:
                pending = cm.group(2) or "<anon>"
            ident = None
            if code.strip() and va is not None:
                ident = _decl_ident(code)
            elif code.strip() and marker_va is not None and "(" in code:
                ident = _decl_ident(code)
                if ident:
                    va = marker_va
                    marker_va = None
            if ident:
                cls = [s for s, _d in scopes]
                if "::" in ident:
                    parts = ident.split("::")
                    cls = cls + parts[:-1]
                    ident = parts[-1]
                out.append((ident, tuple(cls), va, "%s:%d" % (os.path.basename(path), ln), _decl_params(code)))
            for ch in code:
                if ch == "{":
                    depth += 1
                    if pending:
                        scopes.append((pending, depth))
                        pending = None
                elif ch == "}":
                    if scopes and scopes[-1][1] == depth:
                        scopes.pop()
                    depth -= 1
            if ";" in code and pending and "{" not in code:
                pending = None
    return out


def _decl_params(code):
    """Text inside the first top-level parentheses of a function declaration, or None."""
    c = code
    i = c.find("(")
    if i < 0:
        return None
    if re.match(r"\(\s*(?:__\w+\s+)?\*", c[i:]):        # function-pointer variable
        return None
    d, j = 0, i
    while j < len(c):
        if c[j] == "(":
            d += 1
        elif c[j] == ")":
            d -= 1
            if d == 0:
                return c[i + 1:j]
        j += 1
    return None


BUILTIN_TYPES = {
    "int": "int", "signed": "int", "long": "int", "int32_t": "int", "i32": "int", "s32": "int", "INT": "int",
    "unsigned": "uint", "uint": "uint", "uint32_t": "uint", "u32": "uint", "UINT": "uint", "DWORD": "uint",
    "size_t": "uint", "eastl_size_t": "uint",
    "char": "char", "int8_t": "char", "uchar": "uchar", "uint8_t": "uchar", "u8": "uchar", "BYTE": "uchar",
    "short": "short", "int16_t": "short", "ushort": "ushort", "uint16_t": "ushort", "u16": "ushort",
    "wchar_t": "wchar_t", "char16_t": "wchar_t", "bool": "bool", "float": "float", "f32": "float",
    "double": "double", "f64": "double", "void": "void", "int64_t": "int64", "__int64": "int64",
    "uint64_t": "uint64", "u64": "uint64",
}


def norm_text_params(text):
    """'const wchar_t* p, unsigned n = 0' -> [('wchar_t', '*'), ('uint', '')]."""
    if text is None:
        return None
    t = text.strip()
    if t in ("", "void"):
        return []
    parts, d, cur = [], 0, ""
    for ch in t:
        if ch in "<(":
            d += 1
        elif ch in ">)":
            d -= 1
        if ch == "," and d == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    parts.append(cur)
    out = []
    for p in parts:
        p = p.split("=")[0]
        if p.strip() == "...":
            out.append(("...", ""))
            continue
        arr = p.count("[")
        p = re.sub(r"\[[^\]]*\]", "", p)
        p = re.sub(r"<[^<>]*(<[^<>]*>[^<>]*)*>", "", p)
        suffix = "".join(ch for ch in p if ch in "*&") + "*" * arr
        words = [w for w in re.findall(r"[A-Za-z_][\w:]*", p)
                 if w not in ("const", "volatile", "struct", "class", "enum", "union", "typename", "__restrict")]
        if "unsigned" in words:
            rest = [w for w in words if w != "unsigned"]
            base = {"char": "uchar", "short": "ushort", "__int64": "uint64"}.get(rest[0] if rest else "", "uint")
            out.append((base, suffix))
            continue
        if len(words) >= 2 and words[0] in ("long", "short") and words[1] == "int":
            words = words[:1] + words[2:]
        if len(words) >= 2 and words[0] == "long" and words[1] == "long":
            words = ["int64"] + words[2:]
        base = words[0].split("::")[-1] if words else "?"
        out.append((BUILTIN_TYPES.get(base, base), suffix))
    return out


def params_match(mangled_types, text_types):
    if text_types is None or mangled_types is None or len(mangled_types) != len(text_types):
        return False
    for mt, (tb, ts) in zip(mangled_types, text_types):
        ms = "".join(ch for ch in mt if ch in "*&")
        mb = mt.rstrip("*&").replace("enum ", "")
        if ms != ts:
            return False
        if mb == tb:
            continue
        mb_builtin = mb in BUILTIN_TYPES.values()
        tb_builtin = tb in BUILTIN_TYPES.values()
        if mb_builtin and tb_builtin:
            if {mb, tb} <= {"int", "uint"} or {mb, tb} <= {"char", "uchar"}:
                continue       # signedness spelled via typedefs differs too often
            return False
        if mb_builtin != tb_builtin or (not mb_builtin and not tb_builtin):
            continue           # typedef or class alias on one side: do not reject
    return True


OPS = {"2": "new", "3": "delete", "4": "=", "5": ">>", "6": "<<", "7": "!", "8": "==", "9": "!=", "A": "[]",
       "C": "->", "D": "*", "E": "++", "F": "--", "G": "-", "H": "+", "I": "&", "J": "->*", "K": "/", "L": "%",
       "M": "<", "N": "<=", "O": ">", "P": ">=", "Q": ",", "R": "()", "S": "~", "T": "^", "U": "|", "V": "&&",
       "W": "||", "X": "*=", "Y": "+=", "Z": "-=", "_0": "/=", "_1": "%=", "_2": ">>=", "_3": "<<=", "_4": "&=",
       "_5": "|=", "_6": "^=", "_U": "new[]", "_V": "delete[]"}


def operator_of(name):
    """('operator=', [scopes]) for an operator symbol, else None."""
    import sig as SIG
    tmpl = name.startswith("??$?")
    body = name[4:] if tmpl else name[2:]
    code = body[:2] if body.startswith("_") else body[:1]
    if code not in OPS:
        return None
    p = SIG._P(name, (4 if tmpl else 2) + len(code))
    scopes = []
    try:
        if tmpl:
            p.template_args()
        while p.peek() != "@":
            scopes.append(p.name_fragment())
    except Exception:
        pass
    return "operator" + OPS[code], [x for x in scopes if x and x != "?"]


def _decl_ident(code):
    c = code.strip()
    fp = re.search(r"\(\s*(?:__\w+\s+)?\*\s*([A-Za-z_]\w*)\s*\)\s*\(", c)
    if fp:
        return fp.group(1)
    if "(" in c:
        head = c[:c.index("(")]
        m = re.search(r"((?:[A-Za-z_]\w*\s*::\s*)*~?(?:operator\s*[^\s(]+|[A-Za-z_]\w*))\s*$", head)
        return re.sub(r"\s+", "", m.group(1)) if m else None
    m = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*(?:=[^;]*)?[;,]", c)
    if m and m.group(1) not in ("const", "int", "float", "char", "void"):
        return m.group(1)
    return None


def mangled_scopes(name):
    """Plain identifier fragments of a mangled name after its leading identifier."""
    if not name.startswith("?"):
        return []
    body = name.lstrip("?")
    if body[:1] in "01" and name.startswith("??"):
        body = body[1:]
    end = body.find("@@")
    frags = body[:end if end >= 0 else len(body)].split("@")
    return [f.lstrip("?$") for f in frags[1:] if f and not f[0].isdigit()]


# ------------------------------------------------------------------ disassembly

def recursive_descent(read, lo, hi, entry, table_target):
    """Instructions reachable from entry inside [lo, hi). read(a, n) -> bytes;
    table_target(a) -> branch target stored at a (a relocated dword) or None.
    -> {addr: insn} (capstone insns), set of jump-table data addresses."""
    insns, tables = {}, set()
    work = [entry]
    while work:
        a = work.pop()
        while lo <= a < hi and a not in insns:
            code = read(a, min(16, hi - a))
            try:
                ins = next(_md.disasm(code, a, 1))
            except StopIteration:
                break
            insns[a] = ins
            nxt = a + ins.size
            g = ins.group
            if ins.id in (X.X86_INS_RET, X.X86_INS_RETF, X.X86_INS_INT3, X.X86_INS_HLT, X.X86_INS_UD2):
                break
            if ins.id == X.X86_INS_JMP:
                op = ins.operands[0]
                if op.type == X.X86_OP_IMM:
                    a = op.imm
                    continue
                if op.type == X.X86_OP_MEM and op.mem.index != 0 and op.mem.scale == 4:
                    t = op.mem.disp & 0xFFFFFFFF
                    k = 0
                    while k < 2048:
                        tgt = table_target(t + 4 * k)
                        if tgt is None or not lo <= tgt < hi:
                            break
                        tables.update(range(t + 4 * k, t + 4 * k + 4))
                        work.append(tgt)
                        k += 1
                break
            if ins.group(capstone.CS_GRP_JUMP):
                op = ins.operands[0]
                if op.type == X.X86_OP_IMM:
                    work.append(op.imm)
            a = nxt
    return insns, tables


def imm_value(ins, pos_in_insn):
    return struct.unpack_from("<I", bytes(ins.bytes), pos_in_insn)[0]


# ------------------------------------------------------------------ the resolver

class Resolution:
    def __init__(self):
        self.addr = {}            # symbol index -> absolute address in the original image
        self.method = {}          # symbol name -> method
        self.local_sections = set()   # our section indexes to load
        self.unresolved = []      # required symbol names that could not be resolved
        self.eh_unresolved = []   # unresolved but only reachable from EH metadata (trapped)
        self.notes = []


class Resolver:
    def __init__(self, image, symdb):
        self.img = image
        self.db = symdb
        self._crt = None

    # --- single-symbol methods -------------------------------------------------
    def crt_helpers(self):
        if self._crt is None:
            c = {}
            lib = self.db.lib
            for k, v in lib.items():
                c[k] = v
            if "chkstk" in lib:
                c.setdefault("alloca_probe", lib["chkstk"])
            # __ftol2_sse: 'cmp [___sse2_available],0; je __ftol2' right before ftol2_pentium4
            p4 = lib.get("ftol2_pentium4")
            if p4:
                b = self.img.read(p4 - 9, 9)
                if b[:2] == b"\x83\x3d" and b[7] == 0x74:
                    c["ftol2_sse"] = p4 - 9
            chk = lib.get("@__security_check_cookie@4")
            if chk:
                b = self.img.read(chk, 6)
                if b[:2] == b"\x3b\x0d":
                    c["security_cookie"] = struct.unpack_from("<I", b, 2)[0]
                c["security_check_cookie@4"] = chk
            self._crt = c
        return self._crt

    def by_import(self, name):
        if name.startswith("__imp_"):
            n = name[6:]
            cands = [n]
            if n.startswith("_"):
                cands.append(re.sub(r"@\d+$", "", n[1:]))
            for c in cands:
                if c in self.img.import_by_name:
                    return self.img.import_by_name[c]
            return None
        n = name[1:] if name.startswith("_") else name
        n = re.sub(r"@\d+$", "", n)
        th = self.img.thunks()
        for c in (n, name):
            if c in th:
                return th[c]
        return None

    def by_crt(self, name):
        key = name.lstrip("_@")
        h = self.crt_helpers()
        if name in h:
            return h[name]
        if key in h:
            return h[key]
        key2 = re.sub(r"@\d+$", "", key)
        return h.get(key2)

    def plausible(self, va, want_func):
        if want_func:
            return va in self.img.start_set or (self.img.in_text(va) and va in self.img.names)
        return self.img.in_data(va) or va in self.img.start_set

    def by_symbols(self, name, our_quals, want_func):
        vas = self.db.mangled.get(name)
        if vas and len(vas) == 1:
            va = next(iter(vas))
            if self.plausible(va, want_func):
                return va, "symbols(mangled)"
        q = demangle_qual(name)
        if q and our_quals.get(q, 0) == 1 and "::" in q:
            vas = self.db.qual.get(q)
            if vas and len(vas) == 1:
                va = next(iter(vas))
                if self.plausible(va, want_func):
                    return va, "symbols(qualified %s)" % q
        return None, None

    def by_hex_name(self, name, want_func):
        ident = base_ident(name)
        for m in HEX_RE.finditer(ident):
            s = m.group(1)
            if not re.search(r"\d", s):
                continue
            va = int(s, 16)
            if 0x401000 <= va < 0x1900000 and self.plausible(va, want_func):
                return va
        return None

    def by_annotation(self, name, annots, want_func):
        op = operator_of(name) if name.startswith("??") and not name.startswith(("??0", "??1")) and \
            (not name.startswith("??_") or name.startswith(("??_U", "??_V", "??_0", "??_1", "??_2", "??_3", "??_4", "??_5", "??_6"))) else None
        if op:
            ident_cands = {op[0]}
            scopes = set(op[1])
        else:
            ident = base_ident(name)
            if name.startswith("??0"):
                ident_cands = {ident}
            elif name.startswith("??1"):
                ident_cands = {"~" + ident}
            elif name.startswith("??"):
                return None, "special member"
            else:
                ident_cands = {ident}
            scopes = set(mangled_scopes(name))
            if name.startswith(("??0", "??1")):
                scopes.add(ident)
        hits = []
        for a_ident, a_scopes, va, loc, ptext in annots:
            if a_ident not in ident_cands:
                continue
            real = [x for x in a_scopes if x != "<anon>"]
            if real:
                if real[-1] not in scopes:
                    continue
            elif scopes and not op:
                continue
            hits.append((va, loc, ptext))
        vas = {h[0] for h in hits}
        how = ""
        if len(vas) > 1:
            try:
                import sig as SIG
                mt = SIG.parse(name).ptypes
            except Exception:
                mt = None
            sel = [h for h in hits if params_match(mt, norm_text_params(h[2]))]
            if sel and len({h[0] for h in sel}) == 1:
                hits, vas, how = sel, {sel[0][0]}, ",params"
        if len(vas) == 1:
            va = next(iter(vas))
            if self.plausible(va, want_func):
                return va, "annotation(%s%s)" % (hits[0][1], how)
            return None, "annotation-implausible %08x" % va
        if len(vas) > 1:
            return None, "annotation-ambiguous %s" % ",".join("%08x" % v for v in sorted(vas))
        return None, None

    def thunk_import(self, va):
        """Import name if va is a 'jmp [IAT]' thunk."""
        if not self.img.in_text(va):
            return None
        b = self.img.read(va, 6)
        if b[:2] == b"\xff\x25":
            return self.img.imports.get(struct.unpack_from("<I", b, 2)[0])
        return None

    # --- whole-object resolution --------------------------------------------------
    def resolve(self, coff, func_sym, orig_va, annots):
        r = Resolution()
        syms = coff.syms
        our_quals = defaultdict(int)
        seen_q = set()
        for s in syms.values():
            if s.name in seen_q:
                continue
            seen_q.add(s.name)
            q = demangle_qual(s.name)
            if q:
                our_quals[q] += 1

        func_sec = func_sym.secno - 1
        usage = defaultdict(set)   # symbol index -> {"call", "data"}
        for sec in coff.sections:
            for (off, si, typ) in sec.relocs:
                if typ == REL_REL32 and off >= 1 and sec.data[off - 1] in (0xE8, 0xE9):
                    usage[si].add("call")
                else:
                    usage[si].add("data")

        def want_func(s):
            return s.is_func or usage[s.index] == {"call"}

        def try_single(s):
            name = s.name
            wf = want_func(s)
            if name.startswith("__imp_"):
                va = self.by_import(name)
                return (va, "import") if va else (None, None)
            va = self.by_crt(name)
            if va:
                return va, "crt"
            va, how = self.by_symbols(name, our_quals, wf)
            if va:
                return va, how
            va = self.by_hex_name(name, wf)
            if va:
                return va, "hex-name"
            va, how = self.by_annotation(name, annots, wf)
            if va:
                return va, how
            note = how
            va = self.by_import(name)
            if va:
                return va, "import-thunk"
            if name in BUILTIN_ADDR:
                return BUILTIN_ADDR[name], "builtin"
            return None, note

        required_secs, eh_secs = set(), set()
        pending = {}   # symbol index -> note
        vtables = {}   # defined vtable symbol index -> (section, eh): resolved by alignment or loaded
        work = [(func_sec, False)]

        def close(work):
          while work:
            si_sec, eh = work.pop()
            if si_sec in (eh_secs if eh else required_secs):
                continue
            if not eh and si_sec in eh_secs:
                eh_secs.discard(si_sec)
            (eh_secs if eh else required_secs).add(si_sec)
            sec = coff.sections[si_sec]
            sec_is_vtable = any(x.secno - 1 == si_sec and x.name.startswith("??_7") for x in syms.values())
            for (off, si, typ) in sec.relocs:
                s = syms[si]
                sub_eh = eh or sec_is_vtable or s.name.startswith(EH_PREFIXES)
                if si in r.addr:
                    continue
                if s.defined:
                    tsec = s.secno - 1
                    if s.index == func_sym.index or tsec == func_sec:
                        continue
                    if s.cls == 3 and s.value == 0 and s.naux:      # section symbol: local
                        work.append((tsec, sub_eh))
                        continue
                    va, how = (None, None)
                    if not s.name.startswith(EH_PREFIXES) and s.cls == 2 and not s.name.startswith(LOCAL_CONST_PREFIXES[:4]):
                        va, how = try_single(s)
                    if va is None and s.name.startswith("??_C@"):
                        tsec_o = coff.sections[tsec]
                        blob = tsec_o.data[s.value:]
                        va = self.img.rdata_find(blob)
                        how = "rdata-literal" if va else None
                    if va is not None:
                        r.addr[si] = va
                        r.method[s.name] = how
                    elif s.name.startswith("??_7") and si_sec == func_sec and si not in vtables:
                        vtables[si] = (tsec, sub_eh)        # decide after alignment
                    elif si not in vtables:
                        work.append((tsec, sub_eh))
                    continue
                if s.name in ("__fltused", "__ldused"):
                    continue
                va, note = try_single(s)
                if va is not None:
                    r.addr[si] = va
                    r.method[s.name] = note
                else:
                    if sub_eh:
                        pending.setdefault(si, ("eh", note))
                    else:
                        pending[si] = ("req", note)
        close(work)
        r.local_sections = required_secs | eh_secs

        # alignment fallback for required unresolved symbols
        req = {si for si, (k, _n) in pending.items() if k == "req"} | set(vtables)
        got, check = self.align(coff, func_sym, orig_va, r, req)
        for si, va in got.items():
            r.addr[si] = va
            r.method[syms[si].name] = "align"
        for si, (tsec, _eh) in vtables.items():
            if si in r.addr:
                continue
            va = self.vtable_by_content(coff, syms[si], r, try_single)
            if va:
                r.addr[si] = va
                r.method[syms[si].name] = "vtable-content"
        rest = [(tsec, True) for si, (tsec, _eh) in vtables.items() if si not in r.addr]
        if rest:   # vtables we could not map: load ours; their slots and RTTI are trapped, not required
            close(rest)
            r.local_sections = required_secs | eh_secs
        r.conflicts = []
        for si, va in check.items():
            nm = syms[si].name
            how = r.method.get(nm)
            if si not in r.addr or r.addr[si] == va or how == "align":
                continue
            old = r.addr[si]
            if how == "rdata-literal":
                s_ = syms[si]
                blob = coff.sections[s_.secno - 1].data[s_.value:]
                if self.img.in_data(va) and self.img.read(va, len(blob)) == blob:
                    r.addr[si] = va
                    r.method[nm] = "rdata-literal(aligned copy)"
                    continue
            if how in ("import-thunk", "crt", "import"):
                if self.thunk_import(va) is not None and self.thunk_import(va) == self.thunk_import(old):
                    r.addr[si] = va
                    r.method[nm] = how + "(aligned copy)"
                    continue
            r.conflicts.append((nm, old, how, va))
        for si, (kind, note) in pending.items():
            if si in r.addr:
                continue
            nm = syms[si].name + (" [%s]" % note if note else "")
            (r.eh_unresolved if kind == "eh" else r.unresolved).append(nm)
        return r

    def vtable_by_content(self, coff, vsym, r, try_single):
        """Our vtable mapped to the original's: every slot resolves to an image address and that
        exact dword sequence occurs once (4-aligned) in .rdata."""
        sec = coff.sections[vsym.secno - 1]
        slots = []
        rel = {off: si for off, si, typ in sec.relocs if typ == REL_DIR32}
        for off in range(vsym.value, len(sec.data) - 3, 4):
            si = rel.get(off)
            if si is None:
                return None
            if si not in r.addr:
                va, _how = try_single(coff.syms[si])
                if va is None:
                    return None
                r.addr[si] = va
                r.method[coff.syms[si].name] = _how
            slots.append((r.addr[si] + struct.unpack_from("<I", sec.data, off)[0]) & 0xFFFFFFFF)
        if not slots:
            return None
        blob = struct.pack("<%dI" % len(slots), *slots)
        ro = self.img.section(".rdata")
        key = ("rdata",)
        if key not in self.img._mem:
            self.img._mem[key] = self.img.read(ro[0], ro[1])
        data = self.img._mem[key]
        hits = []
        i = data.find(blob)
        while i >= 0 and len(hits) < 2:
            if i % 4 == 0:
                hits.append(ro[0] + i)
            i = data.find(blob, i + 1)
        return hits[0] if len(hits) == 1 else None

    # --- alignment ------------------------------------------------------------------
    def orig_refs(self, va):
        lo, hi = self.img.func_extent(va)
        code = self.img.read(lo, hi - lo)
        relset = set(self.img.reloc_positions(lo, hi - lo))

        def rd(a, n):
            return code[a - lo:a - lo + n]

        def tt(a):
            if a in relset and lo <= a < hi - 3:
                return struct.unpack_from("<I", code, a - lo)[0]
            return None
        insns, tables = recursive_descent(rd, lo, hi, va, tt)
        refs = []
        for a in sorted(insns):
            ins = insns[a]
            if ins.bytes[0] in (0xE8,) and ins.size == 5:
                t = ins.operands[0].imm & 0xFFFFFFFF
                refs.append(("call", ins.mnemonic, t))
                continue
            if ins.bytes[0] == 0xE9 and ins.size == 5:
                t = ins.operands[0].imm & 0xFFFFFFFF
                if not lo <= t < hi:
                    refs.append(("call", "jmp", t))
                continue
            for p in relset:
                if a <= p < a + ins.size:
                    v = struct.unpack_from("<I", code, p - lo)[0]
                    if lo <= v < hi:
                        continue
                    kind = "call" if ins.mnemonic in ("call", "jmp") else "data"
                    refs.append((kind, ins.mnemonic, v))
        return refs, insns, tables, (lo, hi)

    def our_refs(self, coff, func_sym, r):
        sec = coff.sections[func_sym.secno - 1]
        data = sec.data
        rel = {off: (si, typ) for (off, si, typ) in sec.relocs}
        lo, hi = 0, len(data)

        def rd(a, n):
            return data[a:a + n]

        def tt(a):
            x = rel.get(a)
            if x is None:
                return None
            s = coff.syms[x[0]]
            if s.defined and s.secno - 1 == func_sym.secno - 1:
                return (s.value + struct.unpack_from("<I", data, a)[0]) & 0xFFFFFFFF
            return None
        insns, _t = recursive_descent(rd, lo, hi, func_sym.value, tt)
        refs = []
        for a in sorted(insns):
            ins = insns[a]
            for p in range(a, a + ins.size):
                if p not in rel:
                    continue
                si, typ = rel[p]
                s = coff.syms[si]
                if s.defined and s.secno == func_sym.secno:
                    continue
                if typ == REL_REL32:
                    refs.append(("call", "call" if ins.mnemonic == "call" else "jmp", si))
                else:
                    kind = "call" if ins.mnemonic in ("call", "jmp") else "data"
                    refs.append((kind, ins.mnemonic, si))
        return refs

    def align(self, coff, func_sym, orig_va, r, wanted):
        """-> ({si: va} for wanted symbols, {si: va} alignment evidence for resolved ones).
        Iterative: symbols resolved in one round become anchors that split longer gaps in the next."""
        o_all, _i, _t, _b = self.orig_refs(orig_va)
        u_all = self.our_refs(coff, func_sym, r)
        known = dict(r.addr)
        out = {}
        for _round in range(12):
            cands, weak = self._align_round(o_all, u_all, known)
            new = {}
            for si, c in cands.items():
                if si in wanted and si not in out and len(c) == 1 and weak.get(si, c) <= c:
                    new[si] = next(iter(c))
            if not new:
                break
            out.update(new)
            known.update(new)
        check = {}
        for si, c in cands.items():
            if si not in wanted and len(c) == 1 and weak.get(si, c) <= c:
                check[si] = next(iter(c))
        return out, check

    def _align_round(self, o_all, u_all, known):
        cands = defaultdict(set)
        weak = defaultdict(set)
        for kind in ("call", "data"):
            O = [x for x in o_all if x[0] == kind]
            U = [x for x in u_all if x[0] == kind]
            ko = [("v", x[2]) for x in O]
            ku = [("v", known[x[2]]) if x[2] in known else ("u", x[2], j) for j, x in enumerate(U)]
            sm = difflib.SequenceMatcher(None, ko, ku, autojunk=False)
            prev_o, prev_u = 0, 0
            for (bo, bu, n) in sm.get_matching_blocks():
                for k in range(n):
                    cands[U[bu + k][2]].add(O[bo + k][2])
                go, gu = O[prev_o:bo], U[prev_u:bu]
                if go and len(go) == len(gu) and all(x[1] == y[1] for x, y in zip(go, gu)):
                    # measured on op1 (resolved symbols held out): a 1-reference gap between
                    # anchors pairs correctly 99% of the time, 2: 89%, longer gaps far less, so
                    # only 1-gaps propose an address; longer gaps can only veto one.
                    for x, y in zip(go, gu):
                        (cands if len(go) == 1 else weak)[y[2]].add(x[2])
                prev_o, prev_u = bo + n, bu + n
        return cands, weak
