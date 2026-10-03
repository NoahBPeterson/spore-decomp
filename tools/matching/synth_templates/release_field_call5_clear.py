# "if (p) { this->p = 0; ext(p, a, b, c, d); }" with p,a,b,c,d consecutive dword fields; cdecl ext 5 args
PATTERN = 'mov eax, dword ptr [ecx + N] ; test eax, eax ; je +N ; mov edx, dword ptr [ecx + N] ; push edx ; mov edx, dword ptr [ecx + N] ; push edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [ecx + N], N ; mov ecx, dword ptr [ecx + N] ; push edx ; push ecx ; push eax ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    n = N[0]
    t = "%08x" % va
    pad = " unsigned pad[%d];" % (n // 4) if n else ""
    src = ("void __cdecl FUN_%s_ext(void*, unsigned, unsigned, unsigned, unsigned);\n"
           "struct C_%s {%s void* p; unsigned a, b, c, d; void FUN_%s(); };\n"
           "void C_%s::FUN_%s() { void* q = p; if (q) { p = 0; FUN_%s_ext(q, a, b, c, d); } }") % (t, t, pad, t, t, t, t)
    return src, "?FUN_%s@C_%s@@QAEXXZ" % (t, t)
