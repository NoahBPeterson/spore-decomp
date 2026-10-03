# thiscall member setter copying a 16-byte struct (4 dwords) by const ref: void C::f(const V4& v) { m = v; } /O2
PATTERN = "mov eax, dword ptr [esp + N] ; mov edx, dword ptr [eax] ; mov dword ptr [ecx + N], edx ; mov edx, dword ptr [eax + N] ; mov dword ptr [ecx + N], edx ; mov edx, dword ptr [eax + N] ; mov dword ptr [ecx + N], edx ; mov eax, dword ptr [eax + N] ; mov dword ptr [ecx + N], eax ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct V4_ { int a, b, c, d; };\n"
def emit(va, A, N):
    off = N[1]
    t = "%08x" % va
    cls = "C_%s" % t
    src = ("struct %s { char pad[%d]; V4_ m; void FUN_%s(const V4_& v); };\n"
           "void %s::FUN_%s(const V4_& v) { m = v; }") % (cls, off, t, cls, t)
    return src, "?FUN_%s@%s@@QAEXABUV4_@@@Z" % (t, cls)
