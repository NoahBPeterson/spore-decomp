# vector<T>::erase(first, last) for POD T: copy tail down with struct copies, end -= (last-first), return first
PATTERN = 'push ecx ; push ebx ; mov ebx, dword ptr [ecx + N] ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; mov dword ptr [esp + N], ecx ; mov edx, esi ; mov eax, ebp ; cmp ebp, ebx ; je +N ; push edi ; lea esp, [esp] ; mov esi, eax ; mov edi, edx ; add eax, N ; mov ecx, N ; add edx, N ; rep movsd dword ptr es:[edi], dword ptr [esi] ; cmp eax, ebx ; jne +N ; mov ecx, dword ptr [esp + N] ; mov esi, dword ptr [esp + N] ; pop edi ; sub ebp, esi ; mov eax, A ; imul ebp ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; imul eax, eax, N ; add dword ptr [ecx + N], eax ; mov eax, esi ; pop esi ; pop ebp ; pop ebx ; pop ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    sz = max(n for n in N if n % 4 == 0 and n <= 0x400 and n >= 8 and n != 8) if False else None
    # element size: imul immediate (last-but-3 immediate before ret); find dword count = mov ecx imm
    sz = None
    for n in N:
        pass
    # N order: [ecx+off], esp offs..., size, ecx count, ...; use mov ecx count (index found by value*4 == imul imm)
    cands = [n for n in N if n * 4 in N]
    cnt = max(cands)
    sz = cnt * 4
    off = N[0]
    v = "%08x" % va
    src = ("struct E{v} {{ unsigned d[{n}]; }};\n"
           "template<class P> P* cp_{v}(P* a, P* b, P* c) {{ for (; a != b; ++c, ++a) *c = *a; return c; }}\n"
           "struct V{v} {{ unsigned pad[{o}]; E{v}* e;\n"
           "  E{v}* FUN_{v}(E{v}* f, E{v}* l); }};\n"
           "E{v}* V{v}::FUN_{v}(E{v}* f, E{v}* l) {{\n"
           "    cp_{v}(l, e, f);\n"
           "    e -= (l - f); return f; }}\n").format(
           v=v, n=cnt, o=off // 4)
    return src, "?FUN_%08x@V%08x@@QAEPAUE%08x@@PAU2@0@Z" % (va, va, va)
