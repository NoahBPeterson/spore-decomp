PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, ecx ; test esi, esi ; je +N ; push N ; push A ; push N ; push N ; mov eax, esi ; shl eax, N ; push A ; push eax ; call EXT ; add esp, N ; shl esi, N ; add esi, eax ; mov dword ptr [edi], eax ; mov dword ptr [edi + N], eax ; mov dword ptr [edi + N], esi ; mov eax, edi ; pop edi ; pop esi ; ret N ; xor eax, eax ; shl esi, N ; add esi, eax ; mov dword ptr [edi], eax ; mov dword ptr [edi + N], eax ; mov dword ptr [edi + N], esi ; mov eax, edi ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* EAL(size_t size, const char* name, int flags, unsigned dbg, const char* file, int line);\n")
def emit(va, A, N):
    line = N[1]
    shift = N[4]
    fn, sn = "s_%08x" % A[0], "s_%08x" % A[1]
    src = ("extern const char %s[]; extern const char %s[];\n"
           "struct V_%08x { char* b; char* e; char* c;\n"
           "  V_%08x* init(size_t n, int a);\n};\n"
           "V_%08x* V_%08x::init(size_t n, int a) { char* p = n ? (char*)EAL(n << %d, %s, 0, 0, %s, %d) : 0; b = p; e = p; c = (char*)((n << %d) + (size_t)p); return this; }\n"
           % (fn, sn, va, va, va, va, shift, sn, fn, line, shift))
    return src, "?init@V_%08x@@QAEPAU1@IH@Z" % va
