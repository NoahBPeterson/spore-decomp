# eastl::vector<T>::operator=(const vector&) for sizeof(T) = N[12] (non-power-of-2): realloc / shrink-copy / grow-copy.
PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp ebp, esi ; je +N ; mov edx, dword ptr [ebp + N] ; mov ecx, dword ptr [ebp] ; sub edx, ecx ; mov eax, A ; imul edx ; sar edx, N ; push ebx ; mov ebx, dword ptr [esi] ; push edi ; mov edi, edx ; shr edi, N ; add edi, edx ; mov edx, dword ptr [esi + N] ; sub edx, ebx ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp edi, eax ; jbe +N ; mov edx, dword ptr [ebp + N] ; push edx ; push ecx ; push edi ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esi] ; mov ebx, eax ; mov eax, dword ptr [esi + N] ; push eax ; push ecx ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov edx, edi ; imul edi, edi, N ; imul edx, edx, N ; add edx, ebx ; add edi, ebx ; mov dword ptr [esi + N], edi ; pop edi ; mov dword ptr [esi], ebx ; pop ebx ; mov dword ptr [esi + N], edx ; mov eax, esi ; pop esi ; pop ebp ; ret N ; mov edx, dword ptr [esi + N] ; sub edx, ebx ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; push ebx ; cmp edi, eax ; jbe +N ; imul eax, eax, N ; add eax, ecx ; push eax ; push ecx ; call EXT ; mov ebx, dword ptr [esi + N] ; mov eax, dword ptr [ebp + N] ; mov dword ptr [esp + N], eax ; mov ecx, ebx ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; sar edx, N ; mov ecx, edx ; shr ecx, N ; add ecx, edx ; mov edx, dword ptr [esp + N] ; mov eax, ecx ; mov ecx, dword ptr [esp + N] ; imul eax, eax, N ; add eax, dword ptr [ebp] ; push edx ; push ebx ; push ecx ; push eax ; lea edx, [esp + N] ; push edx ; call EXT ; imul edi, edi, N ; add esp, N ; add edi, dword ptr [esi] ; mov eax, esi ; mov dword ptr [esi + N], edi ; pop edi ; pop ebx ; pop esi ; pop ebp ; ret N ; mov eax, dword ptr [ebp + N] ; push eax ; push ecx ; call EXT ; mov ecx, dword ptr [esi + N] ; add esp, N ; push ecx ; push eax ; mov ecx, esi ; call EXT ; imul edi, edi, N ; add edi, dword ptr [esi] ; mov dword ptr [esi + N], edi ; pop edi ; pop ebx ; mov eax, esi ; pop esi ; pop ebp ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    d = dict(t="%08x" % va, z=N[12])
    src = ("struct T_%(t)s { char d[%(z)d]; };\n"
           "struct R_%(t)s { T_%(t)s* p; };\n"
           "struct V_%(t)s { T_%(t)s* b; T_%(t)s* e; T_%(t)s* c;\n"
           " T_%(t)s* Alloc(unsigned n, T_%(t)s* f, T_%(t)s* l);\n"
           " void Destroy(T_%(t)s* f, T_%(t)s* l);\n"
           " V_%(t)s& FUN_%(t)s(const V_%(t)s& x); };\n"
           "T_%(t)s* Cp_%(t)s(T_%(t)s* f, T_%(t)s* l, T_%(t)s* d);\n"
           "R_%(t)s* Uc_%(t)s(R_%(t)s* o, T_%(t)s* f, T_%(t)s* l, T_%(t)s* d, T_%(t)s* e);\n"
           "V_%(t)s& V_%(t)s::FUN_%(t)s(const V_%(t)s& x) {\n"
           "  if (&x != this) {\n"
           "    unsigned n = x.e - x.b;\n"
           "    if (n > (unsigned)(c - b)) {\n"
           "      T_%(t)s* p = Alloc(n, x.b, x.e);\n"
           "      Destroy(b, e);\n"
           "      if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);\n"
           "      b = p; e = p + n; c = p + n;\n"
           "    } else if ((unsigned)(e - b) >= n) {\n"
           "      T_%(t)s* q = Cp_%(t)s(x.b, x.e, b);\n"
           "      Destroy(q, e);\n"
           "      e = b + n;\n"
           "    } else {\n"
           "      unsigned m = e - b;\n"
           "      Cp_%(t)s(x.b, x.b + m, b);\n"
           "      R_%(t)s r; Uc_%(t)s(&r, x.b + m, x.e, e, x.e);\n"
           "      e = b + n;\n"
           "    }\n"
           "  }\n"
           "  return *this;\n}") % d
    return src, "?FUN_%(t)s@V_%(t)s@@QAEAAU1@ABU1@@Z" % d
