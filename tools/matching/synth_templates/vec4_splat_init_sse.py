# Dynamic initializer of a file-scope 4-float struct (e.g. ColorRGBA(1,1,1,1)) whose four ctor args are
# the same extern const float (defined in another TU, so /O2 cannot fold it to static data), in an
# /arch:SSE module: movss xmm0,[src] ; 4x movss [dst+0/4/8/12],xmm0 ; ret
PATTERN = 'movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = """struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
};
"""
def emit(va, A, N):
    src, dst = A[0], A[1]
    if A[2:] != [dst + 4, dst + 8, dst + 12]:
        s = "extern const float g_%08x;\n" % src
        s += "".join("extern float g_%08x;\n" % a for a in A[1:])
        s += "void FUN_%08x() {\n" % va
        s += "".join("    g_%08x = g_%08x;\n" % (d, src) for d in A[1:])
        s += "}"
        return s, "?FUN_%08x@@YAXXZ" % va
    return ("extern const float g_%08x;\nVector4 g_%08x(g_%08x, g_%08x, g_%08x, g_%08x);"
            % (src, dst, src, src, src, src), "??__Eg_%08x@@YAXXZ" % dst)
