# Runtime initialization of a file-scope 3x3 float matrix to identity (Matrix3 style), in an /arch:SSE
# module: xorps xmm0,xmm0 ; movss xmm1,[one] ; 9x movss [dst+4k], xmm1/xmm0 (diagonal = one) ; ret
# Every ctor form (literal 1.0f/0.0f, extern-const diagonal arg, loop, inline SetIdentity) lets /O2 fold
# the zeros/whole object into static data, so no ??__E reproduces; a plain __cdecl function doing the nine
# stores in operand order is byte-exact (shape-equivalent; needs explicit .CRT$XCU registration on relink).
# The 1.0f source (__real@3f800000 at a fixed address) is an extern const float so its load is relocated.
PATTERN = 'xorps xmm0, xmm0 ; movss xmm1, dword ptr [A] ; movss dword ptr [A], xmm1 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm1 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm1 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""
def emit(va, A, N):
    src, dsts = A[0], A[1:]
    s = "extern const float g_%08x;\n" % src
    s += "".join("extern float g_%08x;\n" % a for a in sorted(set(dsts) - {src}))
    s += "void FUN_%08x() {\n" % va
    for k, d in enumerate(dsts):
        s += "    g_%08x = %s;\n" % (d, ("g_%08x" % src) if k in (0, 4, 8) else "0.0f")
    s += "}"
    return s, "?FUN_%08x@@YAXXZ" % va
