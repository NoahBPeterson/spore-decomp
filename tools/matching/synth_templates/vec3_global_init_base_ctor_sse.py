# Dynamic initializer of a global Vector3-like class (empty base with out-of-line ctor, user
# ctor copying three floats from a POD temp): "V3 g = mkV();" where mkV inlines
# "P t; Make(&t); return V3(t);". Emits temp call, base ctor on g, then 3 movss copies.
PATTERN = "lea eax, [esp - N] ; sub esp, N ; push eax ; call EXT ; add esp, N ; mov ecx, A ; call EXT ; movss xmm0, dword ptr [esp] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [A], xmm0 ; add esp, N ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = """struct B { B(); };
struct P { float x, y, z; };
struct V3 : B { float x, y, z; V3(const P &o) : x(o.x), y(o.y), z(o.z) {} };
"""
def emit(va, A, N):
    g = A[0]
    s = ("void Make_%08x(P *);\n"
         "V3 g_%08x = ([]{ return 0; }, V3(*(P *)0));\n") if False else ""
    s = ("void Make_%08x(P *);\n"
         "inline V3 mk_%08x() { P t; Make_%08x(&t); return V3(t); }\n"
         "V3 g_%08x = mk_%08x();" % (va, va, va, g, va))
    return s, "??__Eg_%08x@@YAXXZ" % g
