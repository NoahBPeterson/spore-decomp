# Dynamic initializer storing {name, fn, firstdword} of a 16-aligned local temp built by an
# external one-arg thiscall ctor (Havok hkClass/typeinfo registration; and esp,-16 frame).
PATTERN = 'push ebp ; mov ebp, esp ; and esp, A ; sub esp, N ; xor eax, eax ; push eax ; lea ecx, [esp + N] ; call EXT ; mov eax, dword ptr [esp] ; mov dword ptr [A], A ; mov dword ptr [A], A ; mov dword ptr [A], eax ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/O2", "/GS-", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct F { int m; F():m(0){} };
struct Reg0 { const char* name; void (*fn)(); unsigned v; };
"""
def emit(va, A, N):
    _m, dest1, s, dest2, f, dest3 = A[:6]
    size = N[0]
    src = ("struct __declspec(align(16)) T_%08x { T_%08x(F); unsigned first; char pad[%d]; };\n"
           "extern const char s_%08x[]; void f_%08x();\n"
           "struct R_%08x : Reg0 { R_%08x(const char* n, void (*f)()) { T_%08x t((F())); name = n; fn = f; v = t.first; } };\n"
           "R_%08x g_%08x(s_%08x, f_%08x);"
           % (va, va, size - 16, s, f, va, va, va, va, dest1, s, f))
    return src, "??__Eg_%08x@@YAXXZ" % dest1
