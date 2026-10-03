# EASTL vector<T>::reserve-style grow (T of 1<<shift bytes): allocate, two helper calls, free old, reset pointers.
PATTERN = 'mov eax, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; sub ecx, dword ptr [esi] ; sar ecx, N ; cmp eax, ecx ; jbe +N ; push edi ; test eax, eax ; je +N ; push N ; push A ; push N ; push N ; shl eax, N ; push A ; push eax ; call EXT ; add esp, N ; mov edi, eax ; jmp +N ; xor edi, edi ; push ebx ; mov ebx, dword ptr [esi + N] ; push ebp ; mov ebp, dword ptr [esi] ; push edi ; push ebx ; push ebp ; call EXT ; push edi ; push ebx ; push ebp ; call EXT ; mov eax, dword ptr [esi] ; add esp, N ; pop ebp ; pop ebx ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov eax, dword ptr [esi + N] ; sub eax, dword ptr [esi] ; mov dword ptr [esi], edi ; sar eax, N ; shl eax, N ; add eax, edi ; mov dword ptr [esi + N], eax ; mov eax, dword ptr [esp + N] ; shl eax, N ; add eax, edi ; mov dword ptr [esi + N], eax ; pop edi ; pop esi ; ret N'
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
    s = TPL.replace("SZ", str(1 << N[2])).replace("@", "%08x" % va)
    return s, "?f@V_%08x@@QAEXI@Z" % va
