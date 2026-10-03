# eastl::vector<4-byte T>::operator=(const vector&): realloc / assign+uninit-copy / assign+destroy-tail.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp ebx, esi ; je +N ; mov eax, dword ptr [ebx] ; mov ecx, dword ptr [esi] ; mov edx, dword ptr [esi + N] ; push ebp ; mov ebp, dword ptr [ebx + N] ; push edi ; mov edi, ebp ; sub edi, eax ; sub edx, ecx ; sar edi, N ; sar edx, N ; cmp edi, edx ; jbe +N ; push ebp ; push eax ; push edi ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esi] ; mov ebx, eax ; mov eax, dword ptr [esi + N] ; push eax ; push ecx ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; lea edx, [ebx + edi*N] ; mov dword ptr [esi + N], edx ; mov edx, ebx ; lea eax, [edx + edi*N] ; pop edi ; mov dword ptr [esi + N], eax ; pop ebp ; mov dword ptr [esi], ebx ; mov eax, esi ; pop esi ; pop ebx ; ret N ; mov edx, dword ptr [esi + N] ; sub edx, ecx ; sar edx, N ; push ecx ; cmp edi, edx ; jbe +N ; lea ecx, [eax + edx*N] ; push ecx ; push eax ; call EXT ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [ebx + N] ; mov ebx, dword ptr [ebx] ; mov edx, eax ; sub edx, dword ptr [esi] ; sar edx, N ; lea edx, [ebx + edx*N] ; mov ebx, dword ptr [esp + N] ; push ebx ; push eax ; push ecx ; push edx ; lea eax, [esp + N] ; push eax ; call EXT ; mov edx, dword ptr [esi] ; add esp, N ; lea eax, [edx + edi*N] ; pop edi ; mov dword ptr [esi + N], eax ; pop ebp ; mov eax, esi ; pop esi ; pop ebx ; ret N ; push ebp ; push eax ; call EXT ; mov ecx, dword ptr [esi + N] ; add esp, N ; push ecx ; push eax ; mov ecx, esi ; call EXT ; mov edx, dword ptr [esi] ; lea eax, [edx + edi*N] ; pop edi ; mov dword ptr [esi + N], eax ; pop ebp ; mov eax, esi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "struct Tag {};\nvoid EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    t = "%08x" % va
    src = ("struct V_%(t)s;\n" "struct V_%(t)s { unsigned* b; unsigned* e; unsigned* c;\n"
           " unsigned* Alloc(unsigned n, unsigned* f, unsigned* l); void Destroy(unsigned* f, unsigned* l);\n"
           " V_%(t)s& FUN_%(t)s(const V_%(t)s& o); };\n"
           "unsigned* Copy_%(t)s(unsigned* f, unsigned* l, unsigned* d);\n"
           "void UCopy_%(t)s(unsigned*& out, unsigned* f, unsigned* l, unsigned* d, Tag x);\n"
           "V_%(t)s& V_%(t)s::FUN_%(t)s(const V_%(t)s& o) {\n"
           "  if (&o != this) {\n"
           "    unsigned n = (unsigned)(o.e - o.b);\n"
           "    if (n > (unsigned)(c - b)) {\n"
           "      unsigned* p = Alloc(n, o.b, o.e); Destroy(b, e);\n"
           "      if (b && ((unsigned*)b)[-1]) EASTL_allocator_deallocate(b);\n"
           "      b = p; e = b + n; c = e;\n"
           "    } else if (n > (unsigned)(e - b)) {\n"
                      "      Copy_%(t)s(o.b, o.b + (e - b), b);\n"
           "      unsigned* out; Tag tg; UCopy_%(t)s(out, o.b + (e - b), o.e, e, tg); e = b + n;\n"
           "    } else {\n"
           "      unsigned* d = Copy_%(t)s(o.b, o.e, b); Destroy(d, e); e = b + n;\n"
           "    }\n"
           "  }\n  return *this;\n}") % {"t": t}
    return src, "?FUN_%(t)s@V_%(t)s@@QAEAAU1@ABU1@@Z" % {"t": t}
