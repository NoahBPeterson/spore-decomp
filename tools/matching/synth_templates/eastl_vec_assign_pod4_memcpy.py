# eastl::vector<T> (sizeof(T)==4, POD) operator=(const vector&): realloc / grow-copy / shrink-copy via memcpy.
# NOT byte-exact yet: structure matches (forceinline copy helper, branch order) but register allocation of
# the prologue loads differs (orig loads x.e,x.b,this.c,this.b -> edx,eax,ecx,ebx; cl gives ecx,eax,edx,ebx).
PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp ebp, esi ; je +N ; mov edx, dword ptr [ebp + N] ; mov eax, dword ptr [ebp] ; mov ecx, dword ptr [esi + N] ; push ebx ; mov ebx, dword ptr [esi] ; push edi ; mov edi, edx ; sub edi, eax ; sub ecx, ebx ; sar edi, N ; sar ecx, N ; cmp edi, ecx ; jbe +N ; push edx ; push eax ; push edi ; mov ecx, esi ; call EXT ; mov ebx, eax ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov eax, ebx ; lea edx, [ebx + edi*N] ; lea ecx, [eax + edi*N] ; pop edi ; mov dword ptr [esi], ebx ; pop ebx ; mov dword ptr [esi + N], edx ; mov dword ptr [esi + N], ecx ; mov eax, esi ; pop esi ; pop ebp ; ret N ; mov ecx, dword ptr [esi + N] ; sub ecx, ebx ; sar ecx, N ; cmp edi, ecx ; jbe +N ; add ecx, ecx ; add ecx, ecx ; push ecx ; push eax ; push ebx ; call EXT ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [ebp] ; mov edx, eax ; sub edx, dword ptr [esi] ; sar edx, N ; lea ecx, [ecx + edx*N] ; mov edx, dword ptr [ebp + N] ; sub edx, ecx ; push edx ; push ecx ; push eax ; call EXT ; mov eax, dword ptr [esi] ; add esp, N ; lea ecx, [eax + edi*N] ; pop edi ; pop ebx ; mov dword ptr [esi + N], ecx ; mov eax, esi ; pop esi ; pop ebp ; ret N ; sub edx, eax ; push edx ; push eax ; push ebx ; call EXT ; mov eax, dword ptr [esi] ; add esp, N ; lea ecx, [eax + edi*N] ; pop edi ; mov dword ptr [esi + N], ecx ; pop ebx ; mov eax, esi ; pop esi ; pop ebp ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = """typedef unsigned int size_t;
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
void EASTL_allocator_deallocate(void* p);
"""
def emit(va, A, N):
    d = dict(t="%08x" % va)
    src = ("struct V_%(t)s { unsigned* b; unsigned* e; unsigned* c;\n"
           " unsigned* Alloc(unsigned n, const unsigned* f, const unsigned* l);\n"
           " V_%(t)s& FUN_%(t)s(const V_%(t)s& x); };\n"
           "static __forceinline unsigned* Cp_%(t)s(const unsigned* f, const unsigned* l, unsigned* d) {\n"
           "  memcpy(d, f, (char*)l - (char*)f); return d + (l - f); }\n"
           "V_%(t)s& V_%(t)s::FUN_%(t)s(const V_%(t)s& x) {\n"
           "  if (&x != this) {\n"
           "    const unsigned n = (unsigned)(x.e - x.b);\n"
           "    if (n > (unsigned)(c - b)) {\n"
           "      unsigned* p = Alloc(n, x.b, x.e);\n"
           "      if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);\n"
           "      b = p; c = p + n; e = p + n;\n"
           "    } else if (n > (unsigned)(e - b)) {\n"
           "      Cp_%(t)s(x.b, x.b + (e - b), b);\n"
           "      Cp_%(t)s(x.b + (e - b), x.e, e);\n"
           "      e = b + n;\n"
           "    } else {\n"
           "      Cp_%(t)s(x.b, x.e, b);\n"
           "      e = b + n;\n"
           "    }\n"
           "  }\n"
           "  return *this;\n}") % d
    return src, "?FUN_%(t)s@V_%(t)s@@QAEAAU1@ABU1@@Z" % d
