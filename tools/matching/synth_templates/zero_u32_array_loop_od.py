# Unoptimized loop zeroing a global uint32 array: for (i = 0; i < n; i++) g[i] = 0;
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], N ; jmp +N ; mov eax, dword ptr [ebp - N] ; add eax, N ; mov dword ptr [ebp - N], eax ; cmp dword ptr [ebp - N], N ; jae +N ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ecx*N + A], N ; jmp +N ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    # N: 4,0 | 4,1 | 4 | 4,4 (cmp count) | 4 | 4(scale), 0
    cnt = N[7]
    return ("extern unsigned int g_%08x[];\nvoid FUN_%08x() { for (unsigned int i = 0; i < %d; i++) g_%08x[i] = 0; }"
            % (A[0], va, cnt, A[0]), "?FUN_%08x@@YAXXZ" % va)
