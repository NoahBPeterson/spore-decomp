# EASTL deque<T*,...>::DoInit(nElements) with 64-element (256 byte) subarrays and 8 minimum ptr array.
PATTERN = 'sub esp, N ; push ebx ; push ebp ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; shr edi, N ; inc edi ; lea eax, [edi + N] ; mov dword ptr [esp + N], eax ; cmp eax, N ; mov esi, ecx ; mov dword ptr [esp + N], N ; lea eax, [esp + N] ; ja +N ; lea eax, [esp + N] ; mov eax, dword ptr [eax] ; push N ; push A ; push N ; mov dword ptr [esi + N], eax ; add eax, eax ; push N ; add eax, eax ; push A ; push eax ; call EXT ; mov ecx, dword ptr [esi + N] ; sub ecx, edi ; shr ecx, N ; lea ebx, [eax + ecx*N] ; lea ebp, [ebx + edi*N] ; add esp, N ; mov dword ptr [esi], eax ; mov edi, ebx ; cmp ebx, ebp ; jae +N ; jmp +N ; lea esp, [esp] ; push N ; push A ; push N ; push N ; push A ; push N ; call EXT ; mov dword ptr [edi], eax ; add edi, N ; add esp, N ; cmp edi, ebp ; jb +N ; mov eax, dword ptr [esp + N] ; mov dword ptr [esi + N], ebx ; mov ebx, dword ptr [ebx] ; mov dword ptr [esi + N], ebx ; add ebx, N ; mov dword ptr [esi + N], ebx ; mov edx, dword ptr [esi + N] ; mov dword ptr [esi + N], edx ; add ebp, -N ; mov dword ptr [esi + N], ebp ; mov ebp, dword ptr [ebp] ; mov dword ptr [esi + N], ebp ; add ebp, N ; mov dword ptr [esi + N], ebp ; mov ecx, dword ptr [esi + N] ; and eax, N ; pop edi ; lea edx, [ecx + eax*N] ; mov dword ptr [esi + N], edx ; pop esi ; pop ebp ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int);
"""
TPL = """extern const char s_@[]; extern const char n_@[];
struct T_@ { char d[ESZ]; };
struct It_@ { T_@* cur; T_@* beg; T_@* end; T_@** arr;
  void SetSub(T_@** p) { arr = p; beg = *p; end = beg + CNT; } };
template<class T> inline const T& mx_@(const T& a, const T& b) { return (a < b) ? b : a; }
struct D_@ { T_@** pa; unsigned n; It_@ b, e; void f(unsigned cnt); };
void __thiscall D_@::f(unsigned cnt) {
    unsigned nn = cnt / CNT + 1;
    n = mx_@((unsigned)8, nn + 2);
    unsigned sz = n * 4;
    pa = (T_@**)EASTL_allocator_allocate(sz, n_@, 0, 0, s_@, 0xd1);
    T_@** pb = pa + ((n - nn) / 2);
    T_@** pe = pb + nn;
    for (T_@** c = pb; c < pe; ++c) *c = (T_@*)EASTL_allocator_allocate(256, n_@, 0, 0, s_@, 0xd1);
    b.SetSub(pb); b.cur = b.beg;
    e.SetSub(pe - 1); e.cur = e.beg + (cnt % CNT);
}
"""
def emit(va, A, N):
    t = TPL.replace("ESZ", str(N[39])).replace("CNT", str(1 << N[2])).replace("@", "%08x" % va)
    return t, "?f@D_%08x@@QAEXI@Z" % va
