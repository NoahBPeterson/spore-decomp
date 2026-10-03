PATTERN = 'push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov esi, ecx ; test edi, edi ; je +N ; push N ; push A ; push N ; push N ; lea eax, [edi*N] ; push A ; push eax ; call EXT ; add esp, N ; lea ecx, [eax + edi*N] ; mov dword ptr [esi], eax ; mov dword ptr [esi + N], eax ; pop edi ; mov dword ptr [esi + N], ecx ; mov eax, esi ; pop esi ; ret N ; xor eax, eax ; lea ecx, [eax + edi*N] ; mov dword ptr [esi], eax ; mov dword ptr [esi + N], eax ; pop edi ; mov dword ptr [esi + N], ecx ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* EAL(size_t size, const char* name, int flags, unsigned dbg, const char* file, int line);\n")
def emit(va, A, N):
    line = N[1]
    scale = N[4]
    fn, sn = "s_%08x" % A[0], "s_%08x" % A[1]
    src = ("extern const char %s[]; extern const char %s[];\n"
           "struct V_%08x { char* b; char* e; char* c;\n"
           "  V_%08x* init(size_t n, int a);\n};\n"
           "V_%08x* V_%08x::init(size_t n, int a) { b = n ? (char*)EAL(n * %d, %s, 0, 0, %s, %d) : 0; e = b; c = b + n * %d; return this; }\n"
           % (fn, sn, va, va, va, va, scale, sn, fn, line, scale))
    return src, "?init@V_%08x@@QAEPAU1@IH@Z" % va
