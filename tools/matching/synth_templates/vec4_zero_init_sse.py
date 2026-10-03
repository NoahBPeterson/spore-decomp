# Dynamic initializer of a file-scope 4-float vector set to zero (Vector4 g(0,0,0,0);) in an
# /O2 /arch:SSE module: xorps xmm0,xmm0 ; 4x movss [g+k],xmm0 ; ret.
# MSVC /O2 folds plain ctors into static data; volatile members block the fold and give the
# exact runtime initializer. Non-contiguous destinations fall back to a plain function
# storing 0.0f to extern float globals.
PATTERN = 'xorps xmm0, xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = """struct Vector4Z { volatile float x, y, z, w; Vector4Z(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
"""
def emit(va, A, N):
    if A == [A[0], A[0] + 4, A[0] + 8, A[0] + 12]:
        return "Vector4Z g_%08x(0.0f, 0.0f, 0.0f, 0.0f);" % A[0], "??__Eg_%08x@@YAXXZ" % A[0]
    decl = "".join("extern float g_%08x;\n" % a for a in sorted(set(A)))
    body = "".join("g_%08x = 0.0f; " % a for a in A)
    return decl + "void FUN_%08x() { %s}" % (va, body), "?FUN_%08x@@YAXXZ" % va
