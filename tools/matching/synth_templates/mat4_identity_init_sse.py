# Runtime initialization of a file-scope 4x4 float matrix to identity (Matrix4 style), in an /arch:SSE
# module: xorps xmm0,xmm0 ; movss xmm1,[one] ; 16x movss [dst+4k], xmm1/xmm0 (diagonal = one) ; ret
# Same situation as mat3_identity_init_sse: ctor/SetIdentity forms let /O2 fold into static data, so a
# plain __cdecl function doing the sixteen stores in operand order is emitted (shape-equivalent; needs
# explicit .CRT$XCU registration on relink). The 1.0f source (__real@3f800000) is an extern const float.
PATTERN = 'xorps xmm0, xmm0 ; movss xmm1, dword ptr [A] ; movss dword ptr [A], xmm1 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm1 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm1 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm1 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""
def emit(va, A, N):
    src, dsts = A[0], A[1:]
    s = "extern const float g_%08x;\n" % src
    s += "".join("extern float g_%08x;\n" % a for a in sorted(set(dsts) - {src}))
    s += "void FUN_%08x() {\n" % va
    for k, d in enumerate(dsts):
        s += "    g_%08x = %s;\n" % (d, ("g_%08x" % src) if k in (0, 5, 10, 15) else "0.0f")
    s += "}"
    return s, "?FUN_%08x@@YAXXZ" % va
