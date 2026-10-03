# Forward uninitialized copy (new (dest) S(*first)) of struct { u32 a; [pad]; B b; } where B has an
# out-of-line copy ctor; implicit S copy ctor copies a then calls B's copy ctor at +off.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; cmp esi, ebx ; je +N ; push edi ; mov edi, dword ptr [esp + N] ; test edi, edi ; je +N ; mov eax, dword ptr [esi] ; lea ecx, [esi + N] ; push ecx ; lea ecx, [edi + N] ; mov dword ptr [edi], eax ; call EXT ; add esi, N ; add edi, N ; cmp esi, ebx ; jne +N ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret  ; mov eax, dword ptr [esp + N] ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "inline void* operator new(unsigned int, void* p) { return p; }\n"
def emit(va, A, N):
    off, size = N[3], N[5]
    s, b = "S_%08x" % va, "B_%08x" % va
    pad = "" if off == 8 else "".join("unsigned p%d; " % i for i in range((off - 4) // 4))
    al = "__declspec(align(8)) " if off == 8 else ""
    tail = "".join("unsigned q%d; " % i for i in range((size - off) // 4 - 1))
    src = ("%sstruct %s { %s(const %s&); unsigned x; %s };\n"
           "struct %s { unsigned a; %s %s b; };\n"
           "%s* FUN_%08x(%s* first, %s* last, %s* dest) {\n"
           "    for (; first != last; ++first, ++dest) new (dest) %s(*first);\n"
           "    return dest;\n}\n") % (al, b, b, b, tail, s, pad, b, s, va, s, s, s, s)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@00@Z" % (va, s)
