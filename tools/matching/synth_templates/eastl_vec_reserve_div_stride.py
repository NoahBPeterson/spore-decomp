# EASTL vector<T>::reserve with non-power-of-2 sizeof(T): capacity via (e-b)/SZ (magic multiply), alloc, two helpers, free.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp ebx, eax ; jbe +N ; push edi ; test ebx, ebx ; je +N ; push N ; mov ecx, ebx ; imul ecx, ecx, N ; push A ; push N ; push N ; push A ; push ecx ; call EXT ; add esp, N ; mov edi, eax ; jmp +N ; xor edi, edi ; mov eax, dword ptr [esi] ; push ebp ; mov ebp, dword ptr [esi + N] ; push edi ; push ebp ; push eax ; mov dword ptr [esp + N], eax ; call EXT ; mov edx, dword ptr [esp + N] ; push edi ; push ebp ; push edx ; call EXT ; mov eax, dword ptr [esi] ; add esp, N ; pop ebp ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov ecx, dword ptr [esi + N] ; imul ebx, ebx, N ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; imul eax, eax, N ; add eax, edi ; add ebx, edi ; mov dword ptr [esi], edi ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], ebx ; pop edi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int);
void __cdecl EASTL_allocator_deallocate(void*);
}
"""
TPL = """extern const char s_@[]; extern const char n_@[];
struct E_@ { char d[SZ]; };
void __cdecl h1_@(E_@*, E_@*, E_@*);
void __cdecl h2_@(E_@*, E_@*, E_@*);
struct V_@ {
  E_@ *b, *e, *c;
  void f(unsigned n);
};
void V_@::f(unsigned n) {
    if (n > (unsigned)(c - b)) {
      E_@* nb = n ? (E_@*)EASTL_allocator_allocate(n * sizeof(E_@), n_@, 0, 0, s_@, 0xd1) : 0;
      E_@* oe = e; E_@* ob = b;
      h1_@(ob, oe, nb);
      h2_@(ob, oe, nb);
      if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
      unsigned cnt = e - b;
      b = nb; e = nb + cnt; c = nb + n;
    }
}
"""
def emit(va, A, N):
    s = TPL.replace("SZ", str(N[5])).replace("@", "%08x" % va)
    return s, "?f@V_%08x@@QAEXI@Z" % va
