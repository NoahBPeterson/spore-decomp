# EASTL median(a,b,c,compare): compare is an empty by-value functor with out-of-line thiscall operator()(u32,u32).
PATTERN = 'push ebx ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; push edi ; mov edi, dword ptr [esp + N] ; mov ecx, dword ptr [edi] ; push eax ; push ecx ; lea ecx, [esp + N] ; call EXT ; mov ebx, dword ptr [esp + N] ; test al, al ; mov eax, dword ptr [ebx] ; push eax ; je +N ; mov ecx, dword ptr [esi] ; push ecx ; lea ecx, [esp + N] ; call EXT ; test al, al ; jne +N ; mov eax, dword ptr [ebx] ; mov ecx, dword ptr [edi] ; push eax ; push ecx ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; pop edi ; pop esi ; mov eax, ebx ; pop ebx ; ret  ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret  ; mov ecx, dword ptr [edi] ; push ecx ; lea ecx, [esp + N] ; call EXT ; test al, al ; jne +N ; mov eax, dword ptr [ebx] ; mov ecx, dword ptr [esi] ; push eax ; push ecx ; lea ecx, [esp + N] ; call EXT ; test al, al ; mov eax, ebx ; jne +N ; mov eax, esi ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct C { bool operator()(unsigned a, unsigned b) const; };\n"
def emit(va, A, N):
    # Per-branch locals for both compare args are what make MSVC hoist the shared push of *c.
    src = ("unsigned* FUN_%08x(unsigned* a, unsigned* b, unsigned* c, C cmp) {\n"
           "    if (cmp(*a, *b)) {\n"
           "        unsigned x = *c, y = *b;\n"
           "        if (cmp(y, x)) return b;\n"
           "        else { unsigned p = *c, q = *a; if (cmp(q, p)) return c; else return a; }\n"
           "    }\n"
           "    else {\n"
           "        unsigned x = *c, y = *a;\n"
           "        if (cmp(y, x)) return a;\n"
           "        else { unsigned p = *c, q = *b; if (cmp(q, p)) return c; else return b; }\n"
           "    }\n}\n") % va
    return src, "?FUN_%08x@@YAPAIPAI00UC@@@Z" % va
