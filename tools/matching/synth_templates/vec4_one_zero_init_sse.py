# Runtime initialization of a file-scope 4-float struct to (1,0,0,0) (Quaternion/Vector4 style), in an
# /arch:SSE module: movss xmm0,[one] ; movss [dst],xmm0 ; xorps xmm0,xmm0 ; 3x movss [dst+4/8/12],xmm0 ; ret
# The ctor form (Vector4 g(one_extern, 0,0,0)) does not reproduce: /O2 folds the three zero members
# into static data and only stores x at runtime (all ctor/aggregate variants, /Os, /Og tried).
# So a plain __cdecl function doing the four stores in operand order is emitted; the 1.0f source
# (likely __real@3f800000 at a fixed address) is an extern const float so its load is relocated.
PATTERN = 'movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; xorps xmm0, xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""
def emit(va, A, N):
    src = A[0]
    s = "extern const float g_%08x;\n" % src
    s += "".join("extern float g_%08x;\n" % a for a in sorted(set(A[1:]) - {src}))
    s += "void FUN_%08x() {\n    g_%08x = g_%08x;\n" % (va, A[1], src)
    s += "".join("    g_%08x = 0.0f;\n" % d for d in A[2:])
    s += "}"
    return s, "?FUN_%08x@@YAXXZ" % va
