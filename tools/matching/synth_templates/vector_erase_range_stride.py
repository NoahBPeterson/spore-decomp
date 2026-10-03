# vector::erase(first,last)-style: copy tail, destroy, end += (last-first) elements; returns first
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; push ebx ; push eax ; push edi ; call EXT ; mov ecx, dword ptr [esi + N] ; add esp, N ; push ecx ; push eax ; mov ecx, esi ; call EXT ; sub edi, ebx ; mov eax, A ; imul edi ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; imul eax, eax, N ; add dword ptr [esi + N], eax ; pop edi ; pop esi ; mov eax, ebx ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    sz = N[7]
    s = "struct E_%08x { char b[%d]; };\n" % (va, sz)
    s += "E_%08x* X1_%08x(E_%08x*, E_%08x*, E_%08x*);\n" % (va, va, va, va, va)
    s += "struct V_%08x { int a; E_%08x* e; void X2(E_%08x*, E_%08x*); E_%08x* f(E_%08x*, E_%08x*); };\n" % ((va,)*7)
    s += "E_%08x* V_%08x::f(E_%08x* first, E_%08x* last) {\n" % ((va,)*4)
    s += "  E_%08x* p = X1_%08x(last, e, first); X2(p, e); e -= last - first; return first; }\n" % (va, va)
    return s, "?f@V_%08x@@QAEPAUE_%08x@@PAU2@0@Z" % (va, va)
