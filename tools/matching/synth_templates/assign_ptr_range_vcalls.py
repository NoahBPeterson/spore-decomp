# Fill-assign range of intrusive refcounted ptrs: for(; first!=last; ++first) { n=*val; o=*first; if(n!=o){ if(n) n->a(); *first=n; if(o) o->b(); } }
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; cmp ebx, dword ptr [esp + N] ; je +N ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; mov esi, dword ptr [ebp] ; mov edi, dword ptr [ebx] ; cmp esi, edi ; je +N ; test esi, esi ; je +N ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; mov ecx, esi ; call edx ; mov dword ptr [ebx], esi ; test edi, edi ; je +N ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax + N] ; mov ecx, edi ; call edx ; add ebx, N ; cmp ebx, dword ptr [esp + N] ; jne +N ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    a, b = N[3] // 4, N[4] // 4
    n = max(a, b) + 1
    virt = "".join("virtual void v%d(); " % i for i in range(n))
    src = ("struct O_%08x { %s};\n"
           "void FUN_%08x(O_%08x** first, O_%08x** last, O_%08x* const* val) {\n"
           "  for (; first != last; ++first) {\n"
           "    O_%08x* n = *val; O_%08x* o = *first;\n"
           "    if (n != o) { if (n) n->v%d(); *first = n; if (o) o->v%d(); }\n"
           "  }\n}") % (va, virt, va, va, va, va, va, va, a, b)
    return src, "?FUN_%08x@@YAXPAPAUO_%08x@@0PBQAU1@@Z" % (va, va)
