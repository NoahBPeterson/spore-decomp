# thiscall member setter copying a 12-byte struct (3 dwords) by const ref into this+off:
#   void C::f(const V3& v) { m = v; }  under /O2
PATTERN = "mov eax, dword ptr [esp + N] ; mov edx, dword ptr [eax] ; mov dword ptr [ecx + N], edx ; mov edx, dword ptr [eax + N] ; mov dword ptr [ecx + N], edx ; mov eax, dword ptr [eax + N] ; mov dword ptr [ecx + N], eax ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct V3_ { int a, b, c; };\n"
def emit(va, A, N):
    off = N[1]
    t = "%08x" % va
    cls = "C_%s" % t
    src = ("struct %s { char pad[%d]; V3_ m; void FUN_%s(const V3_& v); };\n"
           "void %s::FUN_%s(const V3_& v) { m = v; }") % (cls, off, t, cls, t)
    return src, "?FUN_%s@%s@@QAEXABUV3_@@@Z" % (t, cls)
