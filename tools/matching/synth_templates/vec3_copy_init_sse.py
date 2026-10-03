# Dynamic initializer of a file-scope Vector3 copied from another (extern) Vector3, with a
# user-defined copy ctor, in an /arch:SSE module: three movss load/store pairs, ret.
PATTERN = 'movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = """struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
"""
def emit(va, A, N):
    src, dst = A[0], A[1]
    if A != [src, dst, src + 4, dst + 4, src + 8, dst + 8]:
        # non-contiguous fields: copy individual floats
        s = "".join("extern float g_%08x;\n" % a for a in A[0::2])
        s += "".join("extern float g_%08x;\n" % a for a in A[1::2])
        s += "void FUN_%08x() {\n" % va
        s += "".join("    g_%08x = g_%08x;\n" % (d, sa) for sa, d in zip(A[0::2], A[1::2]))
        s += "}"
        return s, "?FUN_%08x@@YAXXZ" % va
    return ("extern Vector3 g_%08x;\nVector3 g_%08x = g_%08x;" % (src, dst, src),
            "??__Eg_%08x@@YAXXZ" % dst)
