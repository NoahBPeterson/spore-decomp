# EASTL fixed_vector<T>::assign(first,last) range assign; sizeof(T) from the signed-divide magic constant (20, 12, 24).
PATTERN = 'push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; mov ebx, dword ptr [esi] ; sub ecx, ebp ; mov eax, A ; imul ecx ; mov ecx, dword ptr [esi + N] ; sar edx, N ; push edi ; mov edi, edx ; shr edi, N ; add edi, edx ; sub ecx, ebx ; mov eax, A ; imul ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp edi, eax ; jbe +N ; mov ecx, dword ptr [esp + N] ; push ecx ; push ebp ; push edi ; mov ecx, esi ; call EXT ; mov ebx, eax ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp eax, dword ptr [esi + N] ; je +N ; push eax ; call EXT ; add esp, N ; lea edx, [edi + edi*N] ; lea eax, [ebx + edx*N] ; pop edi ; mov dword ptr [esi], ebx ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], eax ; pop esi ; pop ebp ; pop ebx ; ret N ; mov ecx, dword ptr [esi + N] ; sub ecx, ebx ; mov eax, A ; imul ecx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; push ebx ; cmp edi, eax ; ja +N ; mov eax, dword ptr [esp + N] ; push eax ; push ebp ; call EXT ; add esp, N ; pop edi ; mov dword ptr [esi + N], eax ; pop esi ; pop ebp ; pop ebx ; ret N ; lea ecx, [eax + eax*N] ; lea edi, [ebp + ecx*N] ; push edi ; push ebp ; call EXT ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esi + N] ; push edx ; push eax ; mov eax, dword ptr [esp + N] ; push eax ; lea ecx, [esp + N] ; push edi ; push ecx ; call EXT ; mov edx, dword ptr [esp + N] ; add esp, N ; pop edi ; mov dword ptr [esi + N], edx ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" void __cdecl EASTL_allocator_deallocate(void*);
"""
def emit(va, A, N):
    sz = {(0x66666667, 3): 20, (0x2aaaaaab, 1): 12, (0x2aaaaaab, 2): 24}[(A[0], N[3])]
    t = """struct EE { char b[SZ]; };
EE* __cdecl cp_X(EE*, EE*, EE*);
void __cdecl uc_X(EE* volatile*, EE*, EE*, EE*, EE*);
struct VV {
    EE *b, *e, *c; int pad; EE* buf;
    EE* alloc(unsigned n, EE* f, EE* l);
    void assign(EE* f, EE* volatile l, int tag);
};
void VV::assign(EE* f, EE* volatile l, int tag) {
    unsigned n = l - f;
    if (n > (unsigned)(c - b)) {
        EE* p = alloc(n, f, l);
        if (b && b != buf) EASTL_allocator_deallocate(b);
        b = p; e = p + n; c = e;
        return;
    }
    unsigned m = e - b;
    if (n <= m) { e = cp_X(f, l, b); return; }
    cp_X(f, f + m, b);
    uc_X(&l, f + m, l, e, l);
    e = l;
}
"""
    x = "%08x" % va
    t = t.replace("SZ", str(sz)).replace("EE", "E_" + x).replace("VV", "V_" + x).replace("cp_X", "cp_" + x).replace("uc_X", "uc_" + x)
    return t, "?assign@V_%s@@QAEXPAUE_%s@@RAU2@H@Z" % (x, x)
