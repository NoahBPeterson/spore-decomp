# fill: for (; first != last; ++first) *first = *value; with a struct copied via rep movsd
PATTERN = 'mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; cmp eax, edx ; je +N ; push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; mov edi, eax ; add eax, N ; mov ecx, N ; mov esi, ebx ; rep movsd dword ptr es:[edi], dword ptr [esi] ; cmp eax, edx ; jne +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = N[3]
    s = "S_%08x" % va
    src = ("struct %s { unsigned d[0x%x]; };\n"
           "void FUN_%08x(%s* first, %s* last, const %s* v) {\n"
           "    for (; first != last; ++first) *first = *v;\n}\n") % (s, size // 4, va, s, s, s)
    return src, "?FUN_%08x@@YAXPAU%s@@0PBU1@@Z" % (va, s)
