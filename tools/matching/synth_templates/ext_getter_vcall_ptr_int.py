# "GetManager()->vfunc(&g_obj, k);" -- /O2 free function calling an external accessor that returns
# an interface pointer, then a virtual __thiscall method taking (global address, int immediate).
PATTERN = "call EXT ; mov edx, dword ptr [eax] ; push N ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; push A ; call eax ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ("struct VObjP {\n" +
           "".join("    virtual void v%d(void*, int) = 0;\n" % i for i in range(256)) +
           "};\nVObjP* ExtGetVObjP();\n")
def emit(va, A, N):
    g = "g_%08x" % A[0]
    src = ("extern char %s[];\nvoid FUN_%08x() {\n    ExtGetVObjP()->v%d(%s, %d);\n}") % (g, va, N[1] // 4, g, N[0])
    return src, "?FUN_%08x@@YAXXZ" % va
