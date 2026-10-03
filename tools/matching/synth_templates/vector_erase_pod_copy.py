# eastl::vector<T>::erase(iterator) for POD T: shift tail down with struct copies, --end, return position
PATTERN = 'mov eax, ecx ; mov ecx, dword ptr [esp + N] ; push ebp ; mov ebp, dword ptr [eax + N] ; lea edx, [ecx + N] ; cmp edx, ebp ; jae +N ; push ebx ; push esi ; push edi ; lea ebx, [edx - N] ; mov esi, edx ; mov edi, ebx ; add edx, N ; mov ecx, N ; add ebx, N ; rep movsd dword ptr es:[edi], dword ptr [esi] ; cmp edx, ebp ; jne +N ; add dword ptr [eax + N], -N ; mov eax, dword ptr [esp + N] ; pop edi ; pop esi ; pop ebx ; pop ebp ; ret N ; add dword ptr [eax + N], -N ; mov eax, ecx ; pop ebp ; ret N'
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    sz = N[1] if len(N) > 1 else 0
    for n in N:
        if n >= 4 and n % 4 == 0 and n <= 0x100 and n != 4:
            sz = n; break
    off = N[0]
    src = ("struct E{v} {{ unsigned d[{n}]; }};\n"
           "struct V{v} {{ unsigned pad[{o}]; E{v}* e;\n"
           "  E{v}* FUN_{v}(E{v}* p) {{\n"
           "    E{v}* last = e; E{v}* s = p + 1;\n"
           "    if (s < last) {{ E{v}* d = p; for (; s != last; ++s, ++d) *d = *s; }}\n"
           "    --e; return p; }} }};\n"
           "E{v}* call_{v}(V{v}* v, E{v}* p) {{ return v->FUN_{v}(p); }}\n").format(
           v="%08x" % va, n=sz // 4, o=off // 4)
    return src, "?FUN_%08x@V%08x@@QAEPAUE%08x@@PAU2@@Z" % (va, va, va)
