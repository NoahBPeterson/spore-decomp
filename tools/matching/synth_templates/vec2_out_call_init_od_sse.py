# Dynamic initializer (real ??__E form) of a file-scope Vector2 in an unoptimized /Od /Ob1
# /arch:SSE module, initialized from an inline helper that fills a local through an out-pointer
# cdecl function (e.g. FUN_00401160, a Vector2 SetZero/Unit-style filler) and returns it by value:
#   inline Vector2 mk() { Vector2 t; Fill(&t); return t; }   Vector2 g = mk();
# Vector2 needs a user copy-ctor copying per field (movss copies); constructed in place.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)

PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; lea eax, [ebp - N] ; push eax ; call EXT ; add esp, N ; movss xmm0, dword ptr [ebp - N] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [ebp - N] ; movss dword ptr [A], xmm0 ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/arch:SSE", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Vector2 { float x, y; Vector2() {} Vector2(const Vector2& o) : x(o.x), y(o.y) {} };
typedef void (*Vector2Fill)(Vector2*);
template<Vector2Fill F> inline Vector2 Vector2From() { Vector2 t; F(&t); return t; }
"""
def _target(va):
    rel = struct.unpack("<i", _pe.get_data(va + 10 - _pe.OPTIONAL_HEADER.ImageBase, 4))[0]
    return va + 15 + rel

def emit(va, A, N):
    t = _target(va)
    fn = "void FUN_%08x(Vector2*);\n" % t
    if A[1] == A[0] + 4 and N[-2:] == [8, 4]:
        return fn + "Vector2 g_%08x = Vector2From<FUN_%08x>();" % (A[0], t), "??__Eg_%08x@@YAXXZ" % A[0]
    decl = "".join("extern float g_%08x;\n" % a for a in sorted(set(A)))
    body = "Vector2 t; FUN_%08x(&t); " % t + "".join("g_%08x = t.%s; " % (a, c) for a, c in zip(A, "xy"))
    return fn + decl + "void FUN_%08x() { %s}" % (va, body), "?FUN_%08x@@YAXXZ" % va
