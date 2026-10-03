# Dynamic initializer of a file-scope "float tweak" object, /O2 /arch:SSE:
#   hash = FNVHash(name, 0x811c9dc5, 1); next = head; head = this; vptr = FloatTweak vtbl; value = f;
#   atexit(??__F dtor)
# Real ??__E form reproduced: a polymorphic base whose inline ctor hashes the name and links the
# object into an intrusive list (head is a per-module global), and a derived class whose inline
# ctor stores the float (the base vptr store is dead and eliminated, so the derived vptr store
# lands after the list link). The float literal is loaded from __real@ via movss under /arch:SSE.
# Name string and float value are read from the image so the source carries the real literals.
import os, struct, pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = None
def _img(va, n):
    global _pe
    if _pe is None:
        _pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
    return _pe.get_data(va - _pe.OPTIONAL_HEADER.ImageBase, n)
def _cstr(va):
    b = _img(va, 512).split(b"\0")[0]
    return "".join(chr(c) if 32 <= c < 127 and chr(c) not in '"\\?' else "\\%03o" % c for c in b)
def _flt(va):
    v = struct.unpack("<f", _img(va, 4))[0]
    s = repr(v)
    if struct.unpack("<f", struct.pack("<f", float(s)))[0] != v or "inf" in s or "nan" in s:
        return "(*(const float*)\"%s\")" % "".join("\\x%02x" % c for c in _img(va, 4))
    if "e" not in s and "." not in s: s += ".0"
    return s + "f"

PATTERN = 'push N ; push A ; push A ; call EXT ; movss xmm0, dword ptr [A] ; mov dword ptr [A], eax ; mov eax, dword ptr [A] ; push A ; mov dword ptr [A], eax ; mov dword ptr [A], A ; mov dword ptr [A], A ; movss dword ptr [A], xmm0 ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/GR-"]
PRELUDE = """unsigned FNVHash(const char*, unsigned, int);
struct TweakBase {
    TweakBase(TweakBase*& head, const char* name) {
        hash = FNVHash(name, 0x811c9dc5, 1);
        next = head; head = this;
    }
    virtual ~TweakBase() {}
    unsigned hash; TweakBase* next;
};
struct FloatTweak : TweakBase {
    FloatTweak(TweakBase*& head, const char* name, float v) : TweakBase(head, name) { value = v; }
    virtual ~FloatTweak() {}
    float value;
};
"""
def emit(va, A, N):
    name, fconst, head, obj = A[1], A[2], A[4], A[8]
    src = "extern TweakBase* g_%08x;\nFloatTweak g_%08x(g_%08x, \"%s\", %s);" % (
        head, obj, head, _cstr(name), _flt(fconst))
    return src, "??__Eg_%08x@@YAXXZ" % obj
