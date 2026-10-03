PATTERN = 'mov eax, dword ptr [A] ; test eax, eax ; jne +N ; push eax ; push eax ; push eax ; push eax ; push A ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, eax ; call EXT ; mov dword ptr [A], eax ; ret  ; xor eax, eax ; mov dword ptr [A], eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* EAL(size_t size, const char* name, int flags, unsigned dbg, const char* file, int line);\n"
           "inline void* operator new(size_t n, const char* s, int a, unsigned b, const char* c, int d) { return EAL(n, s, a, b, c, d); }\n")
def emit(va, A, N):
    g, s = "g_%08x" % A[0], "s_%08x" % A[1]
    src = ("struct T_%08x { T_%08x(); char pad[%d]; };\nextern T_%08x* %s; extern const char %s[];\n"
           "void FUN_%08x() {\n  T_%08x* p = %s; if (!p) { T_%08x* t = new (%s, (int)p, (unsigned)p, (const char*)p, (int)p) T_%08x; %s = t; }\n}"
           % (va, va, N[0], va, g, s, va, va, g, va, s, va, g))
    return src, "?FUN_%08x@@YAXXZ" % va
