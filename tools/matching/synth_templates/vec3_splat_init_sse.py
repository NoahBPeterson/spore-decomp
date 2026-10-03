# Dynamic initializer of a file-scope 3-float struct (e.g. Vector3(1,1,1)) whose three ctor args are the
# same extern const float (defined in another TU, so /O2 cannot fold it into static data), in an
# /arch:SSE module: movss xmm0,[src] ; movss [dst],xmm0 ; movss [dst+4],xmm0 ; movss [dst+8],xmm0 ; ret
# Non-contiguous destinations fall back to a plain function storing the const into each global.
PATTERN = 'movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = """struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
"""
def emit(va, A, N):
    src, dst = A[0], A[1]
    if A[2:] != [dst + 4, dst + 8]:
        s = "extern const float g_%08x;\n" % src
        s += "".join("extern float g_%08x;\n" % a for a in sorted(set(A[1:])))
        s += "void FUN_%08x() {\n" % va
        s += "".join("    g_%08x = g_%08x;\n" % (d, src) for d in A[1:])
        s += "}"
        return s, "?FUN_%08x@@YAXXZ" % va
    return ("extern const float g_%08x;\nVector3 g_%08x(g_%08x, g_%08x, g_%08x);"
            % (src, dst, src, src, src), "??__Eg_%08x@@YAXXZ" % dst)
