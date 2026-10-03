# Forward copy-construct loop (std::uninitialized_copy shape) over a struct with an
# out-of-line copy constructor; MSVC 2008 null-checks placement new (test edi,edi; je):
#   for (; first != last; ++first, ++dest) new (dest) T(*first); return dest;
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; cmp esi, ebx ; je +N ; push edi ; mov edi, dword ptr [esp + N] ; test edi, edi ; je +N ; push esi ; mov ecx, edi ; call EXT ; add esi, N ; add edi, N ; cmp esi, ebx ; jne +N ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret  ; mov eax, dword ptr [esp + N] ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "inline void* operator new(unsigned int, void* p) { return p; }\n"
def emit(va, A, N):
    size = N[3]
    s = "S_%08x" % va
    src = ("struct %s { char d[0x%x]; %s(const %s&); };\n"
           "%s* FUN_%08x(%s* first, %s* last, %s* dest) {\n"
           "    for (; first != last; ++first, ++dest) new (dest) %s(*first);\n"
           "    return dest;\n}\n") % (s, size, s, s, s, va, s, s, s, s)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@00@Z" % (va, s)
