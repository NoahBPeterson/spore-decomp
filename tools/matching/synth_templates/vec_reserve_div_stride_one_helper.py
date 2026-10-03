# EASTL vector<T>::reserve, sizeof(T)=(k+1)*4: capacity via magic divide, alloc, one 3-arg helper, free, reset pointers.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp ebx, eax ; jbe +N ; push edi ; test ebx, ebx ; je +N ; push N ; push A ; push N ; lea ecx, [ebx + ebx*N] ; push N ; add ecx, ecx ; add ecx, ecx ; push A ; push ecx ; call EXT ; add esp, N ; mov edi, eax ; jmp +N ; xor edi, edi ; mov edx, dword ptr [esi + N] ; mov eax, dword ptr [esi] ; push edi ; push edx ; push eax ; call EXT ; mov eax, dword ptr [esi] ; add esp, N ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov ecx, dword ptr [esi + N] ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; lea ecx, [eax + eax*N] ; lea edx, [edi + ecx*N] ; lea eax, [ebx + ebx*N] ; lea ecx, [edi + eax*N] ; mov dword ptr [esi], edi ; mov dword ptr [esi + N], edx ; mov dword ptr [esi + N], ecx ; pop edi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int);
void __cdecl EASTL_allocator_deallocate(void*);
}
"""
TPL = """extern const char s_@[]; extern const char n_@[];
struct E_@ { char d[SZ]; };
void __cdecl h1_@(E_@*, E_@*, E_@*);
struct V_@ {
  E_@ *b, *e, *c;
  void f(unsigned n);
};
void V_@::f(unsigned n) {
    if (n > (unsigned)(c - b)) {
      E_@* nb = n ? (E_@*)EASTL_allocator_allocate(n * sizeof(E_@), n_@, 0, 0, s_@, 0xd1) : 0;
      h1_@(b, e, nb);
      if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
      unsigned cnt = e - b;
      b = nb; e = nb + cnt; c = nb + n;
    }
}
"""
def emit(va, A, N):
    return TPL.replace("SZ", str((N[6] + 1) * 4)).replace("@", "%08x" % va), "?f@V_%08x@@QAEXI@Z" % va
