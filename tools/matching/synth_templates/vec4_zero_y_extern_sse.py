# Runtime init of a file-scope 4-float struct to (0, c, 0, 0) where c is an extern const float
# (in practice 0x1485720 == 1.0f; Vector4/quaternion-style "Y axis" value) in an /arch:SSE /O2 module:
# xorps xmm0,xmm0 ; movss xmm1,[c] ; movss [v],xmm0 ; [v+4],xmm1 ; [v+8],xmm0 ; [v+12],xmm0 ; ret.
# Real source is surely a ??__E dynamic initializer, but /O2 folds the 0.0f members of ctor/aggregate
# forms into static data (same finding as vec3_zero_y_extern_sse / vec4_one_zero_init_sse), so a plain
# __cdecl function doing the four stores on extern globals is emitted; it reproduces the bytes exactly.
PATTERN = 'xorps xmm0, xmm0 ; movss xmm1, dword ptr [A] ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm1 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""

def emit(va, A, N):
    c, d0, d1, d2, d3 = A
    decls = "extern const float g_%08x;\n" % c
    decls += "".join("extern float g_%08x;\n" % a for a in sorted({d0, d1, d2, d3} - {c}))
    body = "g_%08x = 0.0f; g_%08x = g_%08x; g_%08x = 0.0f; g_%08x = 0.0f;" % (d0, d1, c, d2, d3)
    return "%svoid FUN_%08x() { %s }" % (decls, va, body), "?FUN_%08x@@YAXXZ" % va
