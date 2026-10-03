# "return p ? p->Cast(TYPE_ID) : 0;" where p is passed by reference/pointer to a (smart) pointer,
# e.g. object_cast<T>(const intrusive_ptr<U>&): /O2 cdecl free function loads *arg, null-tests it,
# then makes a virtual __thiscall call with a constant (type-id hash) argument.
PATTERN = "mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [eax] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; push A ; call eax ; ret  ; xor eax, eax ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct VObj {\n" +
           "".join("    virtual void* v%d(unsigned int id) = 0;\n" % i for i in range(256)) +
           "};\n")
def emit(va, A, N):
    idx = N[1] // 4
    src = ("void* FUN_%08x(VObj* const& p) {\n"
           "    if (p) return p->v%d(0x%08xu);\n    return 0;\n}") % (va, idx, A[0])
    return src, "?FUN_%08x@@YAPAXABQAUVObj@@@Z" % va
