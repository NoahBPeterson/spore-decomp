PATTERN = 'mov eax, dword ptr [esp + N] ; push esi ; test eax, eax ; je +N ; push N ; push A ; lea ecx, [eax*N] ; push N ; sub ecx, eax ; push N ; add ecx, ecx ; add ecx, ecx ; push A ; push ecx ; call EXT ; add esp, N ; mov esi, eax ; jmp +N ; xor esi, esi ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; push edx ; push esi ; push eax ; push ecx ; lea edx, [esp + N] ; push edx ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* EAL(size_t size, const char* name, int flags, unsigned dbg, const char* file, int line);\n")
def emit(va, A, N):
    line = N[1]
    mul = 28
    sn, fn = "s_%08x" % A[1], "s_%08x" % A[0]
    src = ("extern const char %s[]; extern const char %s[];\n"
           "void F_%08x(int* n, unsigned a, unsigned b, void* p, int m);\n"
           "void* __stdcall FUN_%08x(int n, unsigned a, unsigned b) {\n"
           "  void* p = n ? EAL(n * %d, %s, 0, 0, %s, %d) : 0;\n"
           "  F_%08x(&n, a, b, p, *(volatile int*)&n);\n  return p;\n}"
           % (sn, fn, va, va, mul, sn, fn, line, va))
    return src, "?FUN_%08x@@YGPAXHII@Z" % va
