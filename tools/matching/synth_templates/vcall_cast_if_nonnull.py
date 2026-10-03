# "return p ? p->Cast(TYPE_ID) : 0;" -- /O2 cdecl free function taking an object pointer and making a
# virtual __thiscall call with a constant (type-id hash) argument, e.g. an object_cast<T>(obj) helper.
PATTERN = "mov ecx, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; push A ; call edx ; ret  ; xor eax, eax ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct VObj {\n" +
           "".join("    virtual void* v%d(unsigned int id) = 0;\n" % i for i in range(256)) +
           "};\n")
def emit(va, A, N):
    idx = N[1] // 4
    src = ("void* FUN_%08x(VObj* p) {\n"
           "    if (p) return p->v%d(0x%08xu);\n    return 0;\n}") % (va, idx, A[0])
    return src, "?FUN_%08x@@YAPAXPAUVObj@@@Z" % va
