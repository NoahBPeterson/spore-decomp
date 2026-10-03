# Forward copy-construct loop over a POD struct (null-checked placement new -> rep movsd), returns dest.
PATTERN = 'mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push ebx ; mov ebx, dword ptr [esp + N] ; cmp edx, ebx ; je +N ; push esi ; push edi ; test eax, eax ; je +N ; mov ecx, N ; mov esi, edx ; mov edi, eax ; rep movsd dword ptr es:[edi], dword ptr [esi] ; add edx, N ; add eax, N ; cmp edx, ebx ; jne +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "inline void* operator new(unsigned int, void* p) { return p; }\n"
def emit(va, A, N):
    n = N[3]
    s = "S_%08x" % va
    src = ("struct %s { int d[%d]; };\n"
           "%s* FUN_%08x(%s* first, %s* last, %s* dest) {\n"
           "    for (; first != last; ++first, ++dest) new (dest) %s(*first);\n"
           "    return dest;\n}\n") % (s, n, s, va, s, s, s, s)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@00@Z" % (va, s)
