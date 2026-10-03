# EASTL merge_sort_buffer over 4-byte elements (recursive, quarter split, merge helper extern cdecl).
PATTERN = 'sub esp, N ; mov ecx, dword ptr [esp + N] ; push ebp ; mov ebp, dword ptr [esp + N] ; sub ecx, ebp ; sar ecx, N ; cmp ecx, N ; mov dword ptr [esp + N], ecx ; jle +N ; mov eax, ecx ; cdq  ; push ebx ; sub eax, edx ; push esi ; mov esi, eax ; sar esi, N ; cmp esi, N ; lea eax, [ebp + esi*N] ; push edi ; mov edi, dword ptr [esp + N] ; mov dword ptr [esp + N], eax ; jle +N ; mov ecx, dword ptr [esp + N] ; mov eax, esi ; cdq  ; sub eax, edx ; mov ebx, eax ; push ecx ; sar ebx, N ; lea eax, [ebp + ebx*N] ; push edi ; push eax ; push ebp ; mov dword ptr [esp + N], eax ; call +N ; mov edx, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; push edx ; lea eax, [edi + ebx*N] ; mov ebx, dword ptr [esp + N] ; push eax ; push ecx ; push ebx ; call +N ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push edx ; push edi ; push eax ; push ebx ; push ebx ; push ebp ; call EXT ; mov ecx, dword ptr [esp + N] ; add esp, N ; jmp +N ; mov edx, dword ptr [ebp] ; mov dword ptr [edi], edx ; mov eax, ecx ; sub eax, esi ; cmp eax, N ; jle +N ; lea eax, [esi + ecx] ; mov ecx, dword ptr [esp + N] ; cdq  ; sub eax, edx ; mov edx, dword ptr [esp + N] ; mov ebx, eax ; push ecx ; sar ebx, N ; lea esi, [edi + esi*N] ; push esi ; lea ebp, [ebp + ebx*N] ; push ebp ; push edx ; call +N ; mov eax, dword ptr [esp + N] ; push eax ; lea ecx, [edi + ebx*N] ; mov ebx, dword ptr [esp + N] ; push ecx ; push ebx ; push ebp ; call +N ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push edx ; push esi ; push ebx ; push ebp ; push ebp ; push eax ; call EXT ; mov ebp, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; add esp, N ; jmp +N ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [edx] ; lea esi, [edi + esi*N] ; mov dword ptr [esi], eax ; mov edx, dword ptr [esp + N] ; push edx ; push ebp ; lea eax, [edi + ecx*N] ; push eax ; push esi ; push esi ; push edi ; call EXT ; add esp, N ; pop edi ; pop esi ; pop ebx ; pop ebp ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef unsigned int u32;
struct Cmp { int x; };
u32* merge_ext(u32*, u32*, u32*, u32*, u32*, Cmp);
"""
BODY = """void NAME(u32* first, u32* last, u32* buf, Cmp c) {
    const int n = last - first;
    if (n > 1) {
        const int mid = n / 2;
        u32* half = first + mid;
        if (mid > 1) {
            const int q = mid / 2;
            u32* quarter = first + q;
            NAME(first, quarter, buf, c);
            NAME(quarter, half, buf + q, c);
            merge_ext(first, quarter, quarter, half, buf, c);
        } else
            *buf = *first;
        if ((n - mid) > 1) {
            const int q = (mid + n) / 2;
            u32* q3 = first + q;
            NAME(half, q3, buf + mid, c);
            NAME(q3, last, buf + q, c);
            merge_ext(half, q3, q3, last, buf + mid, c);
        } else
            *(buf + mid) = *half;
        merge_ext(buf, buf + mid, buf + mid, buf + n, first, c);
    }
}"""
def emit(va, A, N):
    return BODY.replace("NAME", "FUN_%08x" % va), "?FUN_%08x@@YAXPAI00UCmp@@@Z" % va
