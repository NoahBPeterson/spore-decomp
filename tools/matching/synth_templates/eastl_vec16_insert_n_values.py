# EASTL vector<16-byte POD>::DoInsertValues(pos, n, const T&): insert n copies; helpers out of line.
PATTERN = 'sub esp, N ; push ebx ; push ebp ; push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esi + N] ; sub ecx, eax ; push edi ; mov edi, dword ptr [esp + N] ; sar ecx, N ; cmp edi, ecx ; ja +N ; test edi, edi ; jbe +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; sub eax, dword ptr [esp + N] ; mov ebx, dword ptr [esi + N] ; mov dword ptr [esp + N], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [esp + N], edx ; mov edx, dword ptr [ecx + N] ; mov ecx, dword ptr [ecx + N] ; sar eax, N ; mov dword ptr [esp + N], edx ; mov edx, dword ptr [esp + N] ; mov ebp, eax ; mov dword ptr [esp + N], ecx ; push edx ; cmp edi, ebp ; jae +N ; push ebx ; shl edi, N ; mov ebp, ebx ; push ebx ; sub ebp, edi ; lea eax, [esp + N] ; push ebp ; push eax ; call EXT ; add dword ptr [esi + N], edi ; mov esi, dword ptr [esp + N] ; push ebx ; push ebp ; push esi ; call EXT ; lea ecx, [esp + N] ; push ecx ; add edi, esi ; push edi ; push esi ; call EXT ; add esp, N ; pop edi ; pop esi ; pop ebp ; pop ebx ; add esp, N ; ret N ; lea eax, [esp + N] ; push eax ; sub edi, ebp ; push edi ; push ebx ; call EXT ; mov ecx, dword ptr [esp + N] ; shl edi, N ; add dword ptr [esi + N], edi ; mov eax, dword ptr [esi + N] ; mov edi, dword ptr [esp + N] ; push ecx ; push eax ; push ebx ; lea edx, [esp + N] ; push edi ; push edx ; call EXT ; lea eax, [esp + N] ; push eax ; push ebx ; shl ebp, N ; add dword ptr [esi + N], ebp ; push edi ; call EXT ; add esp, N ; pop edi ; pop esi ; pop ebp ; pop ebx ; add esp, N ; ret N ; sub eax, dword ptr [esi] ; sar eax, N ; lea ecx, [eax + eax] ; test eax, eax ; ja +N ; mov ecx, N ; add eax, edi ; cmp ecx, eax ; jbe +N ; mov dword ptr [esp + N], ecx ; jmp +N ; mov dword ptr [esp + N], eax ; mov ecx, eax ; test ecx, ecx ; je +N ; push N ; push A ; push N ; push N ; shl ecx, N ; push A ; push ecx ; call EXT ; add esp, N ; mov ebp, eax ; jmp +N ; xor ebp, ebp ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; push ebp ; push ecx ; push eax ; call EXT ; mov edx, dword ptr [esp + N] ; mov ebx, eax ; mov eax, dword ptr [esp + N] ; push edx ; push eax ; push edi ; push ebx ; call EXT ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esp + N] ; shl edi, N ; add edi, ebx ; push edi ; push eax ; push ecx ; call EXT ; mov edi, eax ; mov eax, dword ptr [esi] ; add esp, N ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov eax, dword ptr [esp + N] ; shl eax, N ; add eax, ebp ; mov dword ptr [esi], ebp ; mov dword ptr [esi + N], edi ; mov dword ptr [esi + N], eax ; pop edi ; pop esi ; pop ebp ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int) throw();
void __cdecl EASTL_allocator_deallocate(void*);
}
"""
TPL = """extern const char s_@[]; extern const char n_@[];
struct E_@ { unsigned a, b, c, d; };
void __cdecl uc_@(const void*, E_@*, E_@*, E_@*, E_@*);
void __cdecl cb_@(E_@*, E_@*, E_@*);
void __cdecl fn_@(E_@*, unsigned, const E_@*, E_@*);
void __cdecl fl_@(E_@*, E_@*, const E_@*);
E_@* __cdecl um_@(E_@*, E_@*, E_@*);
struct V_@ {
  E_@ *b, *e, *c;
  void f(E_@* pos, unsigned n, const E_@* pv);
};
void V_@::f(E_@* pos, unsigned n, const E_@* pv) {
  if (n <= (unsigned)(c - e)) {
    if (n > 0) {
      const E_@ t = *pv;
      unsigned nx = (unsigned)(e - pos);
      E_@* oe = e;
      if (n < nx) {
        uc_@(&pv, oe - n, oe, oe, pos);
        e += n;
        cb_@(pos, oe - n, oe);
        fl_@(pos, pos + n, &t);
      } else {
        fn_@(oe, n - nx, &t, pos);
        e += n - nx;
        E_@* p0 = pos;
        uc_@(&pos, p0, oe, e, p0);
        e += nx;
        fl_@(p0, oe, &t);
      }
    }
  } else {
    unsigned old = e - b; unsigned nc = old > 0 ? 2 * old : 1;
    if (nc < old + n) nc = old + n;
    E_@* nb = nc ? (E_@*)EASTL_allocator_allocate(nc * sizeof(E_@), n_@, 0, 0, s_@, 0xd1) : 0;
    E_@* np = um_@(b, pos, nb);
    fn_@(np, n, pv, pos);
    np = um_@(pos, e, np + n);
    if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
    b = nb; e = np; c = nb + nc;
  }
}
"""
def emit(va, A, N):
    return TPL.replace("@", "%08x" % va), "?f@V_%08x@@QAEXPAUE_%08x@@IPBU2@@Z" % (va, va)
