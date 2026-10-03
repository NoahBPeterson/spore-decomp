PATTERN = 'push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; push edi ; mov edi, dword ptr [esp + N] ; add eax, edx ; cmp edi, eax ; jbe +N ; push ebx ; test edi, edi ; je +N ; push N ; mov ecx, edi ; imul ecx, ecx, N ; push A ; push N ; push N ; push A ; push ecx ; call EXT ; add esp, N ; mov ebx, eax ; jmp +N ; xor ebx, ebx ; mov edx, dword ptr [esi + N] ; mov eax, dword ptr [esi] ; push ebx ; push edx ; push eax ; call EXT ; mov eax, dword ptr [esi] ; add esp, N ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov ecx, dword ptr [esi + N] ; imul edi, edi, N ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; imul eax, eax, N ; add eax, ebx ; add edi, ebx ; mov dword ptr [esi], ebx ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], edi ; pop ebx ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int);
void __cdecl EASTL_allocator_deallocate(void*);
}
"""
TPL = """extern const char s_@[]; extern const char n_@[];
struct E_@ { char d[SZ]; };
void __cdecl mv_@(E_@*, E_@*, E_@*);
struct V_@ {
  E_@ *b, *e, *c;
  void f(unsigned n);
};
void V_@::f(unsigned n) {
    if (n > (unsigned)(c - b)) {
        E_@* p = n ? (E_@*)EASTL_allocator_allocate(n * sizeof(E_@), n_@, 0, 0, s_@, 0xd1) : 0;
        mv_@(b, e, p);
        if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
        int cnt = e - b;
        b = p;
        e = p + cnt;
        c = p + n;
    }
}
"""
def emit(va, A, N):
    from synth import bounds, load_funcs
    import capstone, re
    starts, _ = load_funcs()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    sz = None
    for i in md.disasm(bounds(va, starts), va):
        m = re.match(r"e.x, e.x, (0x[0-9a-f]+)$", i.op_str)
        if i.mnemonic == "imul" and m:
            sz = int(m.group(1), 16); break
    s = TPL.replace("SZ", str(sz)).replace("@", "%08x" % va)
    return s, "?f@V_%08x@@QAEXI@Z" % va
