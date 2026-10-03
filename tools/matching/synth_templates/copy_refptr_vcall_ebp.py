# Forward copy of intrusive ref pointers (AddRef via vslot, Release via vslot), std::copy shape.
PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; cmp ebp, dword ptr [esp + N] ; je +N ; push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; mov esi, dword ptr [ebp] ; mov edi, dword ptr [ebx] ; cmp esi, edi ; je +N ; test esi, esi ; je +N ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; mov ecx, esi ; call edx ; mov dword ptr [ebx], esi ; test edi, edi ; je +N ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax + N] ; mov ecx, edi ; call edx ; add ebp, N ; add ebx, N ; cmp ebp, dword ptr [esp + N] ; jne +N ; pop edi ; pop esi ; mov eax, ebx ; pop ebx ; pop ebp ; ret  ; mov eax, dword ptr [esp + N] ; pop ebp ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    # find the two vtable offsets: values not in the stack/step set
    add, rel = N[3], N[4]
    s = "S_%08x" % va
    def slot(o): return "v%d" % (o // 4)
    n = max(add, rel) // 4 + 1
    decl = "".join("virtual void v%d(){}\n" % i for i in range(n))
    # declare slots as pure virtual to avoid bodies
    decl = "".join("virtual void v%d()=0;\n" % i for i in range(n))
    src = ("struct %s { %s };\n"
           "%s** FUN_%08x(%s** first, %s** last, %s** dest) {\n"
           "    for (; first != last; ++first, ++dest) {\n"
           "        %s* n = *first; %s* o = *dest;\n"
           "        if (n != o) { if (n) n->%s(); *dest = n; if (o) o->%s(); }\n"
           "    }\n    return dest;\n}\n") % (s, decl, s, va, s, s, s, s, s, slot(add), slot(rel))
    return src, "?FUN_%08x@@YAPAPAU%s@@PAPAU1@00@Z" % (va, s)
