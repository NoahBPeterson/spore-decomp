# Runtime init of a file-scope 3-float vector to (0, c, 0) where c is an extern const float
# (in practice 0x1485720 == 1.0f, e.g. a Vector3(0, kOne, 0) / "up" axis initializer) in an
# /arch:SSE /O2 module: xorps xmm0,xmm0 ; movss xmm1,[c] ; movss [v],xmm0 ; [v+4],xmm1 ; [v+8],xmm0.
# The real source is almost certainly a ??__E dynamic initializer, but MSVC /O2 elides the 0.0f
# stores of a zero-initialized global in every initializer form tried (inline ctor, aggregate,
# static member, template static, selectany, file-static), emitting only the y store. A plain
# __cdecl function doing the three stores with extern globals reproduces the bytes exactly.
PATTERN = 'xorps xmm0, xmm0 ; movss xmm1, dword ptr [A] ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm1 ; movss dword ptr [A], xmm0 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""

def emit(va, A, N):
    c, d0, d1, d2 = A
    decls = "extern const float g_%08x;\n" % c
    decls += "".join("extern float g_%08x;\n" % a for a in sorted({d0, d1, d2} - {c}))
    body = "g_%08x = 0.0f; g_%08x = g_%08x; g_%08x = 0.0f;" % (d0, d1, c, d2)
    return "%svoid FUN_%08x() { %s }" % (decls, va, body), "?FUN_%08x@@YAXXZ" % va
