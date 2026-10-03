# Factory __stdcall(int, Alloc* a): if(!a) a = GetDefault(); p = AllocNamed(size, align, "Name", a); return p ? new(p) T : 0
PATTERN = 'mov eax, dword ptr [esp + N] ; test eax, eax ; jne +N ; call EXT ; push eax ; push A ; push N ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, eax ; call EXT ; ret N ; xor eax, eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("inline void* operator new(unsigned, void* p) { return p; }\n"
           "struct Alloc;\nAlloc* GetDefaultAlloc();\n"
           "void* AllocNamed(int size, int align, const char* name, Alloc* a);\n")

def emit(va, A, N):
    align, size = N[1], N[2]
    t = "T_%08x" % va
    src = ("struct %s { %s(); char d[%d]; };\n"
           "void* __stdcall FUN_%08x(int, Alloc* a) {\n"
           "  if (!a) a = GetDefaultAlloc();\n"
           "  void* p = AllocNamed(%d, %d, (const char*)%d, a);\n"
           "  return p ? new(p) %s : 0;\n}"
           % (t, t, size, va, size, align, A[0], t))
    return src, "?FUN_%08x@@YGPAXHPAUAlloc@@@Z" % va
