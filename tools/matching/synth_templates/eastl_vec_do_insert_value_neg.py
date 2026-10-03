# EASTL vector<T>::DoInsertValue(pos, const T&) fully inlined (T of arbitrary size, copy-ctor/assign/range helpers out of line).
PATTERN = 'sub esp, N ; push ebx ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; push edi ; cmp ecx, dword ptr [esi + N] ; je +N ; mov eax, dword ptr [esp + N] ; mov edi, dword ptr [esp + N] ; mov ebx, eax ; cmp eax, edi ; jb +N ; cmp eax, ecx ; jae +N ; lea ebx, [eax + N] ; test ecx, ecx ; je +N ; lea eax, [ecx - N] ; push eax ; call EXT ; mov eax, dword ptr [esi + N] ; push eax ; add eax, -N ; push eax ; push edi ; call EXT ; add esp, N ; push ebx ; mov ecx, edi ; call EXT ; add dword ptr [esi + N], N ; pop edi ; pop esi ; pop ebx ; add esp, N ; ret N ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; je +N ; add eax, eax ; mov dword ptr [esp + N], eax ; test eax, eax ; je +N ; push N ; imul eax, eax, N ; push A ; push N ; push N ; push A ; push eax ; call EXT ; add esp, N ; mov dword ptr [esp + N], eax ; jmp +N ; mov dword ptr [esp + N], N ; mov eax, dword ptr [esp + N] ; jmp +N ; mov dword ptr [esp + N], N ; mov ecx, dword ptr [esp + N] ; mov edi, dword ptr [esp + N] ; push ebp ; mov ebp, dword ptr [esi] ; push ecx ; push edi ; push ebp ; call EXT ; mov edx, dword ptr [esp + N] ; push edx ; push edi ; push ebp ; mov ebx, eax ; call EXT ; add esp, N ; test ebx, ebx ; je +N ; mov eax, dword ptr [esp + N] ; push eax ; mov ecx, ebx ; call EXT ; mov ebp, dword ptr [esi + N] ; add ebx, N ; push ebx ; push ebp ; push edi ; call EXT ; push ebx ; push ebp ; push edi ; mov dword ptr [esp + N], eax ; call EXT ; mov eax, dword ptr [esi] ; add esp, N ; pop ebp ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; imul eax, eax, N ; mov edx, dword ptr [esp + N] ; add eax, ecx ; pop edi ; mov dword ptr [esi], ecx ; mov dword ptr [esi + N], edx ; mov dword ptr [esi + N], eax ; pop esi ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int) throw();
void __cdecl EASTL_allocator_deallocate(void*);
}
inline void* operator new(unsigned, void* p) { return p; }
inline void operator delete(void*, void*) {}
"""
TPL = """extern const char s_@[]; extern const char n_@[];
struct E_@ { char d[SZ]; E_@(const E_@&) throw(); E_@& operator=(const E_@&) throw(); };
E_@* __cdecl h1_@(E_@*, E_@*, E_@*) throw();
void __cdecl h2_@(E_@*, E_@*, E_@*) throw();
E_@* __cdecl h3_@(E_@*, E_@*, E_@*) throw();
struct V_@ {
  E_@ *b, *e, *c;
  void f(E_@* pos, const E_@& v);
  static E_@* um(E_@* f, E_@* l, E_@* d) { E_@* r = h1_@(f, l, d); h2_@(f, l, d); return r; }
  static unsigned newcap(unsigned n) { return n ? 2 * n : 1; }
  static E_@* alloc(unsigned n) { return n ? (E_@*)EASTL_allocator_allocate(n * sizeof(E_@), n_@, 0, 0, s_@, 0xd1) : 0; }
};
void V_@::f(E_@* pos, const E_@& v) {
  if (e != c) {
    const E_@* pv = &v;
    if (pv >= pos && pv < e) ++pv;
    ::new((void*)e) E_@(*(e - 1));
    h3_@(pos, e - 1, e);
    *pos = *pv;
    ++e;
  } else {
    unsigned n = newcap(e - b);
    E_@* nb = alloc(n);
    E_@* np = um(b, pos, nb);
    if (np) ::new((void*)np) E_@(v);
    ++np;
    np = um(pos, e, np);
    if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
    b = nb; e = np; c = nb + n;
  }
}
"""
def emit(va, A, N):
    s = TPL.replace("SZ", str(N[5])).replace("@", "%08x" % va)
    return s, "?f@V_%08x@@QAEXPAUE_%08x@@ABU2@@Z" % (va, va)
