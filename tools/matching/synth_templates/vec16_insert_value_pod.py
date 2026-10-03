# EASTL vector<16-byte POD>::DoInsertValue (pos, const T&) with inline POD copy/assign; helpers out of line.
PATTERN = 'push ebx ; push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; push edi ; cmp eax, dword ptr [esi + N] ; je +N ; mov ebx, dword ptr [esp + N] ; mov edi, dword ptr [esp + N] ; cmp ebx, edi ; jb +N ; cmp ebx, eax ; jae +N ; add ebx, N ; test eax, eax ; je +N ; mov ecx, dword ptr [eax - N] ; mov dword ptr [eax], ecx ; mov edx, dword ptr [eax - N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [eax - N] ; mov dword ptr [eax + N], ecx ; mov edx, dword ptr [eax - N] ; mov dword ptr [eax + N], edx ; mov eax, dword ptr [esi + N] ; push eax ; add eax, -N ; push eax ; push edi ; call EXT ; mov eax, dword ptr [ebx] ; mov dword ptr [edi], eax ; mov ecx, dword ptr [ebx + N] ; mov dword ptr [edi + N], ecx ; mov edx, dword ptr [ebx + N] ; mov dword ptr [edi + N], edx ; mov eax, dword ptr [ebx + N] ; add esp, N ; mov dword ptr [edi + N], eax ; add dword ptr [esi + N], N ; pop edi ; pop esi ; pop ebx ; ret N ; sub eax, dword ptr [esi] ; sar eax, N ; test eax, eax ; jbe +N ; lea edi, [eax + eax] ; test edi, edi ; je +N ; push N ; push A ; push N ; push N ; mov ecx, edi ; shl ecx, N ; push A ; push ecx ; call EXT ; add esp, N ; mov ebx, eax ; jmp +N ; mov edi, N ; jmp +N ; xor ebx, ebx ; mov eax, dword ptr [esi] ; push ebp ; mov ebp, dword ptr [esp + N] ; push ebx ; push ebp ; push eax ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; mov dword ptr [eax], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [eax + N], ecx ; mov ecx, dword ptr [esi + N] ; add eax, N ; push eax ; push ecx ; push ebp ; call EXT ; mov ebp, eax ; mov eax, dword ptr [esi] ; add esp, N ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; shl edi, N ; add edi, ebx ; mov dword ptr [esi + N], ebp ; pop ebp ; mov dword ptr [esi + N], edi ; pop edi ; mov dword ptr [esi], ebx ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int) throw();
void __cdecl EASTL_allocator_deallocate(void*);
}
inline void* operator new(unsigned, void* p) { return p; }
inline void operator delete(void*, void*) {}
"""
TPL = """extern const char s_@[]; extern const char n_@[];
struct E_@ { unsigned a, b, c, d; };
E_@* __cdecl h1_@(E_@*, E_@*, E_@*);
void __cdecl h2_@(E_@*, E_@*, E_@*) throw();
E_@* __cdecl h3_@(E_@*, E_@*, E_@*) throw();
inline E_@* um_@(E_@* f, E_@* l, E_@* d) { return h1_@(f, l, d); }
struct V_@ {
  E_@ *b, *e, *c;
  void f(E_@* pos, const E_@& v);
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
    unsigned old = e - b; unsigned n = old > 0 ? 2 * old : 1;
    E_@* nb = n ? (E_@*)EASTL_allocator_allocate(n * sizeof(E_@), n_@, 0, 0, s_@, 0xd1) : 0;
    E_@* np = um_@(b, pos, nb);
    if (np) ::new((void*)np) E_@(v);
    ++np;
    np = um_@(pos, e, np);
    if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
    b = nb; e = np; c = nb + n;
  }
}
"""
def emit(va, A, N):
    return TPL.replace("@", "%08x" % va), "?f@V_%08x@@QAEXPAUE_%08x@@ABU2@@Z" % (va, va)
