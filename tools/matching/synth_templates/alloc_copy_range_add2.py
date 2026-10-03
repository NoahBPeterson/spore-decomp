PATTERN = 'mov eax, dword ptr [esp + N] ; push esi ; test eax, eax ; je +N ; push N ; push A ; push N ; push N ; add eax, eax ; add eax, eax ; push A ; push eax ; call EXT ; add esp, N ; mov esi, eax ; jmp +N ; xor esi, esi ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; sub ecx, eax ; push ecx ; push eax ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "extern \"C\" void* __cdecl memcpy(void*, const void*, size_t);\n"
           "void* EAL(size_t size, const char* name, int flags, unsigned dbg, const char* file, int line);\n")
def emit(va, A, N):
    line = N[1]
    sn, fn = "s_%08x" % A[1], "s_%08x" % A[0]
    src = ("extern const char %s[]; extern const char %s[];\n"
           "void* __stdcall FUN_%08x(int n, const char* a, const char* b) {\n"
           "  void* p = n ? EAL(n * 4, %s, 0, 0, %s, %d) : 0;\n"
           "  memcpy(p, a, b - a);\n  return p;\n}"
           % (sn, fn, va, sn, fn, line))
    return src, "?FUN_%08x@@YGPAXHPBD0@Z" % va
