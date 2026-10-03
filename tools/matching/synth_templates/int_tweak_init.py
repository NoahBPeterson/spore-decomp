# Dynamic initializer of a file-scope "int tweak" object, /O2: same as float_tweak_init_sse
# but the derived ctor stores an int immediate (no SSE). Name string read from the image.
import os, pefile
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

PATTERN = 'push N ; push A ; push A ; call EXT ; mov dword ptr [A], eax ; mov eax, dword ptr [A] ; push A ; mov dword ptr [A], eax ; mov dword ptr [A], A ; mov dword ptr [A], A ; mov dword ptr [A], N ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = """unsigned FNVHash(const char*, unsigned, int);
struct TweakBase {
    TweakBase(TweakBase*& head, const char* name) {
        hash = FNVHash(name, 0x811c9dc5, 1);
        next = head; head = this;
    }
    virtual ~TweakBase() {}
    unsigned hash; TweakBase* next;
};
struct IntTweak : TweakBase {
    IntTweak(TweakBase*& head, const char* name, int v) : TweakBase(head, name) { value = v; }
    virtual ~IntTweak() {}
    int value;
};
"""
def emit(va, A, N):
    name, head, obj = A[1], A[4], A[8]
    v = N[1]
    src = "extern TweakBase* g_%08x;\nIntTweak g_%08x(g_%08x, \"%s\", %d);" % (head, obj, head, _cstr(name), v)
    return src, "??__Eg_%08x@@YAXXZ" % obj
