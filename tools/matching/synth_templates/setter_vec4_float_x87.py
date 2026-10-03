# Member setter copying 4 floats from a pointer arg (x87 fld/fstp, /O2 no SSE)
PATTERN = 'mov eax, dword ptr [esp + N] ; fld dword ptr [eax] ; fstp dword ptr [ecx + N] ; fld dword ptr [eax + N] ; fstp dword ptr [ecx + N] ; fld dword ptr [eax + N] ; fstp dword ptr [ecx + N] ; fld dword ptr [eax + N] ; fstp dword ptr [ecx + N] ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[1]
    src = ("struct S_%08x { char pad[%d]; float a, b, c, d; void FUN_%08x(const float* p); };\n"
           "void S_%08x::FUN_%08x(const float* p) { a = p[0]; b = p[1]; c = p[2]; d = p[3]; }"
           % (va, off, va, va, va))
    return src, "?FUN_%08x@S_%08x@@QAEXPBM@Z" % (va, va)
