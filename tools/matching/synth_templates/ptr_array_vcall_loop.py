# Loop over stride-sized elements calling virtual slot on element's first pointer (if non-null); returns advanced dest.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; cmp esi, ebx ; je +N ; push edi ; mov edi, dword ptr [esp + N] ; mov ecx, dword ptr [esi] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; add esi, N ; add edi, N ; cmp esi, ebx ; jne +N ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret  ; mov eax, dword ptr [esp + N] ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    voff, stride = N[-4], N[-3]
    slot = voff // 4
    v = "".join("virtual void v%d(); " % i for i in range(slot + 1))
    src = ("struct I_%08x { %s};\nstruct E_%08x { I_%08x* p; char pad[%d]; };\n"
           "E_%08x* FUN_%08x(E_%08x* a, E_%08x* b, E_%08x* d) {\n"
           "  for (; a != b; ++a, ++d) if (a->p) a->p->v%d();\n  return d;\n}"
           % (va, v, va, va, stride - 4, va, va, va, va, va, slot))
    return src, "?FUN_%08x@@YAPAUE_%08x@@PAU1@00@Z" % (va, va)
