# EASTL vector<8-byte POD>::DoInsertValue(pos, const T&) with inline backward copy loop, range-move helper out of line, allocator-name string per instance.
PATTERN = 'push ebx ; push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; push edi ; cmp eax, dword ptr [esi + N] ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; mov edi, ecx ; cmp ecx, edx ; jb +N ; cmp ecx, eax ; jae +N ; lea edi, [ecx + N] ; test eax, eax ; je +N ; mov ecx, dword ptr [eax - N] ; mov dword ptr [eax], ecx ; mov ecx, dword ptr [eax - N] ; mov dword ptr [eax + N], ecx ; mov ecx, dword ptr [esi + N] ; lea eax, [ecx - N] ; cmp eax, edx ; je +N ; jmp +N ; lea ecx, [ecx] ; mov ebx, dword ptr [eax - N] ; sub eax, N ; sub ecx, N ; mov dword ptr [ecx], ebx ; mov ebx, dword ptr [eax + N] ; mov dword ptr [ecx + N], ebx ; cmp eax, edx ; jne +N ; mov eax, dword ptr [edi] ; mov dword ptr [edx], eax ; mov ecx, dword ptr [edi + N] ; pop edi ; mov dword ptr [edx + N], ecx ; add dword ptr [esi + N], N ; pop esi ; pop ebx ; ret N ; sub eax, dword ptr [esi] ; push ebp ; sar eax, N ; test eax, eax ; jbe +N ; lea ebp, [eax + eax] ; test ebp, ebp ; je +N ; push N ; push A ; push N ; push N ; lea edx, [ebp*N] ; push A ; push edx ; call EXT ; add esp, N ; mov edi, eax ; jmp +N ; mov ebp, N ; jmp +N ; xor edi, edi ; mov ebx, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; push edi ; push ebx ; push eax ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; mov dword ptr [eax], edx ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [eax + N], ecx ; mov edx, dword ptr [esi + N] ; add eax, N ; push eax ; push edx ; push ebx ; call EXT ; mov ebx, eax ; mov eax, dword ptr [esi] ; add esp, N ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; lea eax, [edi + ebp*N] ; pop ebp ; mov dword ptr [esi], edi ; pop edi ; mov dword ptr [esi + N], ebx ; mov dword ptr [esi + N], eax ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int) throw();
void __cdecl EASTL_allocator_deallocate(void*);
}
"""
TPL = """extern const char s_@[]; extern const char n_@[];
struct E_@ { unsigned a, b; };
E_@* __cdecl h_@(E_@*, E_@*, E_@*) throw();
struct V_@ {
  E_@ *b, *e, *c;
  void f(E_@* pos, const E_@& v);
};
void V_@::f(E_@* pos, const E_@& v) {
  if (e != c) {
    const E_@* pv = &v;
    if (pv >= pos && pv < e) ++pv;
    if (e) *e = *(e - 1);
    E_@* d = e;
    E_@* s = e - 1;
    while (s != pos) { --s; --d; *d = *s; }
    *pos = *pv;
    ++e;
  } else {
    unsigned cnt = e - b;
    unsigned n = cnt > 0 ? 2 * cnt : 1;
    E_@* nb = n ? (E_@*)EASTL_allocator_allocate(n * sizeof(E_@), n_@, 0, 0, s_@, 0xd1) : 0;
    E_@* np = h_@(b, pos, nb);
    if (np) *np = v;
    E_@* ne = h_@(pos, e, np + 1);
    if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
    b = nb; e = ne; c = nb + n;
  }
}
"""
def emit(va, A, N):
    s = TPL.replace("@", "%08x" % va)
    return s, "?f@V_%08x@@QAEXPAUE_%08x@@ABU2@@Z" % (va, va)
