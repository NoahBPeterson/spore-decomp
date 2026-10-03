# Runtime init of three file-scope floats (likely a Vector3 global initialized as
# Vector3(kOne, 0, 0), x read from another global) in an /arch:SSE module:
# movss xmm0,[src]; movss [x],xmm0; xorps xmm0,xmm0; movss [y],xmm0; movss [z],xmm0; ret.
# The ctor form `Vector3 g(src, 0, 0)` lets /O2 fold y,z into static data (only x stays at
# runtime), so a plain __cdecl function doing the stores in operand order is emitted instead.
PATTERN = 'movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; xorps xmm0, xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""

def emit(va, A, N):
    s = "".join("extern float g_%08x;\n" % a for a in sorted(set(A)))
    s += "void FUN_%08x() { g_%08x = g_%08x; g_%08x = 0.0f; g_%08x = 0.0f; }" % (va, A[1], A[0], A[2], A[3])
    return s, "?FUN_%08x@@YAXXZ" % va
