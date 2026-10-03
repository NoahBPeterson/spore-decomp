# Forward copy-construct loop (uninitialized_copy) with placement new + matching placement delete declared:
# the new-expression gets an EH state (0 during ctor, -1 after), no catch block. Needs /GS- (old EH prolog).
PATTERN = 'mov eax, dword ptr fs:[N] ; push -N ; push A ; push eax ; mov dword ptr fs:[N], esp ; push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; cmp edi, ebx ; je +N ; mov esi, dword ptr [esp + N] ; jmp +N ; lea ebx, [ebx] ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], N ; test esi, esi ; je +N ; push edi ; mov ecx, esi ; call EXT ; add edi, N ; add esi, N ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], esi ; cmp edi, ebx ; jne +N ; mov eax, esi ; mov ecx, dword ptr [esp + N] ; mov dword ptr fs:[N], ecx ; pop edi ; pop esi ; pop ebx ; add esp, N ; ret  ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; pop edi ; pop esi ; mov dword ptr fs:[N], ecx ; pop ebx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "inline void* operator new(unsigned int, void* p) { return p; }\ninline void operator delete(void*, void*) {}\n"
def emit(va, A, N):
    size = N[9]
    s = "S_%08x" % va
    src = ("struct %s { char d[0x%x]; %s(const %s&); ~%s(); };\n"
           "%s* FUN_%08x(%s* first, %s* last, %s* dest) {\n"
           "    for (; first != last; ++first, ++dest) new (dest) %s(*first);\n"
           "    return dest;\n}\n") % (s, size, s, s, s, s, va, s, s, s, s)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@00@Z" % (va, s)
