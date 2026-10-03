# for (p = v->first; p != v->last; ++p) if (p) a->f(p, &key, L"name"); return true;
PATTERN = 'mov eax, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [eax] ; push edi ; mov edi, dword ptr [eax + N] ; cmp esi, edi ; je +N ; push ebx ; mov ebx, dword ptr [esp + N] ; test esi, esi ; je +N ; push A ; push A ; push esi ; mov ecx, ebx ; call EXT ; add esi, N ; cmp esi, edi ; jne +N ; pop ebx ; pop edi ; mov al, N ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = N[3]
    t, al, v = "T_%08x" % va, "Al_%08x" % va, "V_%08x" % va
    src = ("struct %s { char d[0x%x]; };\n"
           "struct %s { void f(%s*, const void*, const wchar_t*); };\n"
           "struct %s { %s* first; %s* last; };\n"
           "extern const char g_%08x[]; extern const wchar_t s_%08x[];\n"
           "bool FUN_%08x(%s* a, %s* v) {\n"
           "    %s* last = v->last;\n    for (%s* p = v->first; p != last; ++p) if (p) a->f(p, g_%08x, s_%08x);\n"
           "    return true;\n}\n") % (t, size, al, t, v, t, t, A[1], A[0], va, al, v, t, t, A[1], A[0])
    return src, "?FUN_%08x@@YA_NPAU%s@@PAU%s@@@Z" % (va, al, v)
