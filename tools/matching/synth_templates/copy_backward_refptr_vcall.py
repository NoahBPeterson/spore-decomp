# Backward copy loop assigning intrusive ref pointers (inlined operator=):
# while (last != first) { --last; --dest; T* n=*last; T* o=*dest; if (n!=o){ if(n) n->AddRef(); *dest=n; if(o) o->Release(); } }
PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; cmp ebp, dword ptr [esp + N] ; je +N ; push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; mov esi, dword ptr [ebp - N] ; mov edi, dword ptr [ebx - N] ; sub ebp, N ; sub ebx, N ; cmp esi, edi ; je +N ; test esi, esi ; je +N ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; mov ecx, esi ; call edx ; mov dword ptr [ebx], esi ; test edi, edi ; je +N ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax + N] ; mov ecx, edi ; call edx ; cmp ebp, dword ptr [esp + N] ; jne +N ; pop edi ; pop esi ; mov eax, ebx ; pop ebx ; pop ebp ; ret  ; mov eax, dword ptr [esp + N] ; pop ebp ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    a, r = N[7] // 4, N[8] // 4
    s = "S_%08x" % va
    virt = []
    for i in range(max(a, r) + 1):
        if i == a: virt.append("virtual void AddRef();")
        elif i == r: virt.append("virtual void Release();")
        else: virt.append("virtual void v%d();" % i)
    src = ("struct %s { %s };\n"
           "%s** FUN_%08x(%s** first, %s** last, %s** dest) {\n"
           "    while (last != first) {\n"
           "        --last; --dest;\n"
           "        %s* n = *last; %s* o = *dest;\n"
           "        if (n != o) { if (n) n->AddRef(); *dest = n; if (o) o->Release(); }\n"
           "    }\n    return dest;\n}\n") % (s, " ".join(virt), s, va, s, s, s, s, s)
    return src, "?FUN_%08x@@YAPAPAU%s@@PAPAU1@00@Z" % (va, s)
