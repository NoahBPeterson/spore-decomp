"""Minimal MSVC (VC9) decorated-name signature parser.

Only what the harness needs: calling convention, whether there is a `this`, the return kind and,
per parameter, a coarse kind (int / ptr / float / double / i64 / bool / small / struct?) with its
size in stack dwords. Unknown constructs raise SigError so callers can fall back.
"""


class SigError(Exception):
    pass


class Sig:
    def __init__(self):
        self.conv = None        # cdecl / thiscall / stdcall / fastcall
        self.member = False     # has `this`
        self.ret = None         # kind of the return value
        self.params = []        # [(kind, dwords)]
        self.variadic = False
        self.ptypes = []        # readable parameter type names

    def __repr__(self):
        return "Sig(%s member=%s ret=%s params=%s)" % (self.conv, self.member, self.ret, self.params)


CONV = {"A": "cdecl", "B": "cdecl", "E": "thiscall", "F": "thiscall", "G": "stdcall", "H": "stdcall",
        "I": "fastcall", "J": "fastcall"}
SIMPLE = {"C": ("small", 1), "D": ("small", 1), "E": ("small", 1), "F": ("small", 1), "G": ("small", 1),
          "H": ("int", 1), "I": ("int", 1), "J": ("int", 1), "K": ("int", 1), "M": ("float", 1),
          "N": ("double", 2), "O": ("double", 2), "X": ("void", 0), "Z": ("varargs", 0)}
SIMPLE_NAMES = {"C": "char", "D": "char", "E": "uchar", "F": "short", "G": "ushort", "H": "int", "I": "uint",
                "J": "int", "K": "uint", "M": "float", "N": "double", "O": "double", "X": "void", "Z": "..."}
UNDERSCORE_NAMES = {"N": "bool", "J": "int64", "K": "uint64", "W": "wchar_t", "D": "char", "E": "uchar",
                    "F": "int64", "G": "uint64"}
UNDERSCORE = {"N": ("bool", 1), "J": ("i64", 2), "K": ("i64", 2), "W": ("small", 1), "D": ("small", 1),
              "E": ("small", 1), "F": ("int", 1), "G": ("int", 1)}


class _P:
    def __init__(self, s, i):
        self.s, self.i = s, i
        self.type_backrefs = []
        self.name_backrefs = []
        self.tname = None          # readable name of the last type parsed

    def peek(self, n=1):
        return self.s[self.i:self.i + n]

    def take(self, n=1):
        t = self.s[self.i:self.i + n]
        if len(t) < n:
            raise SigError("truncated")
        self.i += n
        return t

    def number(self):
        c = self.take()
        if c.isdigit():
            return int(c) + 1
        if c == "?":
            return -self.number()
        v = 0
        while c != "@":
            if not "A" <= c <= "P":
                raise SigError("bad number")
            v = v * 16 + ord(c) - ord("A")
            c = self.take()
        return v

    def name_fragment(self):
        c = self.peek()
        if c.isdigit():
            self.take()
            k = int(c)
            return self.name_backrefs[k] if k < len(self.name_backrefs) else "?"
        if self.peek(2) == "?$":
            self.take(2)
            nm = self.simple_name()
            saved = self.name_backrefs
            self.name_backrefs = []
            self.template_args()
            self.name_backrefs = saved
            return nm
        if c == "?":
            self.take()
            if self.peek(2) == "?_" or self.peek() in "0123456789":
                self.take(2 if self.peek(2) == "?_" else 1)
                return "?"
            if self.peek(2) == "A0":    # anonymous namespace ?A0x1234abcd@
                self.simple_name()
                return "?"
            self.qualified_name()
            return "?"
        nm = self.simple_name()
        if len(self.name_backrefs) < 10 and nm not in self.name_backrefs:
            self.name_backrefs.append(nm)
        return nm

    def simple_name(self):
        j = self.s.index("@", self.i)
        nm = self.s[self.i:j]
        self.i = j + 1
        return nm

    def qualified_name(self):
        first = None
        while True:
            if self.peek() == "@":
                self.take()
                return first
            nm = self.name_fragment()
            if first is None:
                first = nm

    def template_args(self):
        while self.peek() != "@":
            c = self.peek()
            if c == "$":
                self.take()
                k = self.take()
                if k in "0":
                    self.number()
                elif k in "1":
                    self.take()          # '?' + mangled symbol; give up precise parsing
                    raise SigError("template symbol arg")
                elif k == "$":
                    self.take()
                    self.type()
                else:
                    raise SigError("template arg $%s" % k)
            else:
                self.type()
        self.take()

    def cv(self):
        c = self.take()
        if c not in "ABCDEFGHIJ":
            raise SigError("cv %s" % c)

    def type(self):
        """Returns (kind, dwords); self.tname holds a readable type name ('char*', 'Vector3&')."""
        c = self.take()
        if c.isdigit():
            k = int(c)
            if k >= len(self.type_backrefs):
                raise SigError("type backref %d" % k)
            r, self.tname = self.type_backrefs[k]
            return r
        if c in SIMPLE:
            self.tname = SIMPLE_NAMES[c]
            return SIMPLE[c]
        if c == "_":
            d = self.take()
            if d in UNDERSCORE:
                self.tname = UNDERSCORE_NAMES.get(d, "?")
                return UNDERSCORE[d]
            raise SigError("_%s" % d)
        if c in "PQRSAB":
            ref = c in "AB"
            if self.peek() == "6":                    # function pointer
                self.take()
                self.function_type()
                self.tname = "fnptr"
                return ("ptr", 1)
            if self.peek() == "E":
                self.take()
            self.cv()
            arr = False
            if self.peek() == "Y":
                self.take()
                n = self.number()
                for _ in range(n):
                    self.number()
                arr = True
            self.type()
            self.tname = (self.tname or "?") + ("*" if arr else "") + ("&" if ref else "*")
            return ("ptr", 1)
        if c in "TUV":
            self.tname = self.qualified_name() or "?"
            return ("struct", None)
        if c == "W":
            self.take()
            self.tname = "enum " + (self.qualified_name() or "?")
            return ("int", 1)
        if c == "$":
            d = self.take(2)
            if d in ("$C",):
                self.cv()
                return self.type()
            if d == "$A":
                return self.type()
            raise SigError("$%s" % d)
        if c == "?":
            self.cv()
            return self.type()
        raise SigError("type code %s" % c)

    def _backref(self, start, r):
        pass   # MSVC records only top-level parameter types (see param_list)

    def function_type(self):
        conv = CONV.get(self.take())
        if conv is None:
            raise SigError("conv")
        self.ret_type()
        self.param_list()

    def ret_type(self):
        if self.peek() == "?":
            self.take()
            self.cv()
            k = self.type()
            return ("hidden", 1) if k[0] == "struct" else k
        if self.peek() == "@":
            self.take()
            return ("void", 0)
        return self.type()

    def param_list(self):
        out = []
        self.ptypes = []
        variadic = False
        if self.peek() == "X":
            self.take()
            if self.peek() == "Z":
                self.take()
            return out, False
        while True:
            c = self.peek()
            if c == "@":
                self.take()
                if self.peek() == "Z":
                    self.take()
                break
            if c == "Z":
                self.take()
                variadic = True
                break
            start = self.i
            t = self.type()
            if self.i - start > 1 and len(self.type_backrefs) < 10:
                self.type_backrefs.append((t, self.tname))
            out.append(t)
            self.ptypes.append(self.tname)
        return out, variadic


def parse(name):
    """Parse a decorated function name. Raises SigError when not understood."""
    sig = Sig()
    if not name.startswith("?"):
        if name.startswith("@"):
            sig.conv = "fastcall"
            raise SigError("fastcall C name: params unknown")
        if "@" in name:
            sig.conv = "stdcall"
            n = int(name.rsplit("@", 1)[1])
            sig.params = [("unknown", 1)] * (n // 4)
            sig.ret = "unknown"
            return sig
        sig.conv = "cdecl"
        sig.ret = "unknown"
        sig.params = None          # unknown count
        return sig
    p = _P(name, 1)
    if p.peek() == "?":
        p.take()
        c = p.take()
        if c == "$":
            p.simple_name()
            p.template_args()
        elif c == "_":
            p.take()
    else:
        p.name_backrefs.append(p.simple_name())
    p.qualified_name()
    code = p.take()
    if code in "3245":
        raise SigError("data symbol")
    if code == "Y" or code == "Z":
        sig.member = False
    elif code in "ABIJQR" or code in "EFMNUV":
        sig.member = True
        p.cv()
    elif code in "CDKLST":
        sig.member = False
    else:
        raise SigError("function class %s" % code)
    c = p.take()
    sig.conv = CONV.get(c)
    if sig.conv is None:
        raise SigError("conv %s" % c)
    if name.startswith(("??0", "??1")):
        sig.ret = "void" if p.peek() == "@" else None
        if p.peek() == "@":
            p.take()
    if sig.ret is None:
        r = p.ret_type()
        sig.ret = r[0]
    params, variadic = p.param_list()
    sig.params = params
    sig.ptypes = p.ptypes
    sig.variadic = variadic
    return sig
