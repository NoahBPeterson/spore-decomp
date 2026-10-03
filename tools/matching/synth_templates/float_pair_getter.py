# Thiscall getter copying two float members out through two float* out-params.
PATTERN = 'fld dword ptr [ecx + N] ; mov eax, dword ptr [esp + N] ; fstp dword ptr [eax] ; fld dword ptr [ecx + N] ; mov ecx, dword ptr [esp + N] ; fstp dword ptr [ecx] ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    o1, o2 = N[0], N[2]
    gap = o2 - o1 - 4
    pad2 = "unsigned pad2[%d];" % (gap // 4) if gap else ""
    src = ("struct C_%08x { unsigned pad1[%d]; float a; %s float b;\n"
           "  void FUN_%08x(float* x, float* y) { *x = a; *y = b; } };\n"
           "void (C_%08x::*p_%08x)(float*, float*) = &C_%08x::FUN_%08x;\n"
           % (va, o1 // 4, pad2, va, va, va, va, va))
    return src, "?FUN_%08x@C_%08x@@QAEXPAM0@Z" % (va, va)
