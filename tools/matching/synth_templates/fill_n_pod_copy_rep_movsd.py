# for (; n > 0; --n, ++q) new (q) T(a) with a local cursor q, POD T copied via rep movsd (null-checked placement new).
PATTERN = 'mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; test edx, edx ; jbe +N ; push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; test eax, eax ; je +N ; mov ecx, N ; mov esi, ebx ; mov edi, eax ; rep movsd dword ptr es:[edi], dword ptr [esi] ; dec edx ; add eax, N ; test edx, edx ; ja +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "inline void* operator new(unsigned int, void* p) { return p; }\n"
def emit(va, A, N):
    n = N[3]
    s = "S_%08x" % va
    src = ("struct %s { int d[%d]; };\n"
           "void FUN_%08x(%s* p, unsigned n, const %s& a) {\n"
           "    %s* q = p;\n"
           "    for (; n > 0; --n, ++q) new (q) %s(a);\n}\n") % (s, n, va, s, s, s, s)
    return src, "?FUN_%08x@@YAXPAU%s@@IABU1@@Z" % (va, s)
