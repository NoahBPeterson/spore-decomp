# Dynamic initializer (real ??__E form) of a file-scope Vector3 in an unoptimized /Od /Ob1
# /arch:SSE module, initialized from an inline helper that fills a local through an out-pointer
# cdecl function (Vector3_SetUnitY/SetZero/...) and returns it by value:
#   inline Vector3 mk() { Vector3 t; SetUnitY(&t); return t; }   Vector3 g = mk();
# Vector3 needs a user copy-ctor copying per field (movss copies); the ctor is constructed in place.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)

PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; lea eax, [ebp - N] ; push eax ; call EXT ; add esp, N ; movss xmm0, dword ptr [ebp - N] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [ebp - N] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [ebp - N] ; movss dword ptr [A], xmm0 ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/arch:SSE", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Vector3 { float x, y, z; Vector3() {} Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {} };
typedef void (*Vector3Fill)(Vector3*);
template<Vector3Fill F> inline Vector3 Vector3From() { Vector3 t; F(&t); return t; }
"""
def _target(va):
    rel = struct.unpack("<i", _pe.get_data(va + 11 - _pe.OPTIONAL_HEADER.ImageBase, 4))[0]
    return (va + 15 + rel) & 0xffffffff

def emit(va, A, N):
    t = _target(va)
    fn = "void FUN_%08x(Vector3*);\n" % t
    if A[1] == A[0] + 4 and A[2] == A[0] + 8 and N[-3:] == [0xc, 8, 4]:
        return fn + "Vector3 g_%08x = Vector3From<FUN_%08x>();" % (A[0], t), "??__Eg_%08x@@YAXXZ" % A[0]
    decl = "".join("extern float g_%08x;\n" % a for a in sorted(set(A)))
    body = "Vector3 t; FUN_%08x(&t); " % t + "".join("g_%08x = t.%s; " % (a, c) for a, c in zip(A, "xyz"))
    return fn + decl + "void FUN_%08x() { %s}" % (va, body), "?FUN_%08x@@YAXXZ" % va
