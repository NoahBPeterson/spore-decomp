# "VObjL* p = Lookup(ID1); if (p) return p->vN(ID2); return 0;" -- /O2 cdecl free function that
# looks up an object via a __stdcall lookup by a constant id/hash (e.g. FUN_00b20c60) and, when found, returns a virtual
# __thiscall call on it taking a second constant id (e.g. a factory/class-registry query).
PATTERN = "push A ; call EXT ; test eax, eax ; je +N ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; push A ; call eax ; ret  ; xor eax, eax ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct VObjL {\n" +
           "".join("    virtual void* v%d(unsigned int id) = 0;\n" % i for i in range(256)) +
           "};\nVObjL* __stdcall LookupById(unsigned int id);\n")
def emit(va, A, N):
    src = ("void* FUN_%08x() {\n"
           "    VObjL* p = LookupById(0x%08xu);\n"
           "    if (p) return p->v%d(0x%08xu);\n    return 0;\n}") % (va, A[0], N[0] // 4, A[1])
    return src, "?FUN_%08x@@YAPAXXZ" % va
