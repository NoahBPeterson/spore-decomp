# Assignment of a default-constructed 16-float object (4x4 matrix zeroed by its ctor) to a
# file-scope global in an /O2 /arch:SSE module: the temporary is built on the stack with
# 16x movss of xmm0=0 and then struct-copied with rep movsd (ecx=16).
# (A loop-based ctor does not match; explicit member-init list of 16 floats does.)
# Source shape: g = M4();  in a plain function (the global is extern, so no folding).
PATTERN = 'sub esp, N ; xorps xmm0, xmm0 ; push esi ; push edi ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; rep movsd dword ptr es:[edi], dword ptr [esi] ; pop edi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ("struct Matrix4Z { float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;\n"
           "  Matrix4Z() : a(0), b(0), c(0), d(0), e(0), f(0), g(0), h(0), i(0), j(0), k(0), l(0), m(0), n(0), o(0), p(0) {} };\n")

def emit(va, A, N):
    return ("extern Matrix4Z g_%08x;\nvoid FUN_%08x() { g_%08x = Matrix4Z(); }" % (A[0], va, A[0]),
            "?FUN_%08x@@YAXXZ" % va)
