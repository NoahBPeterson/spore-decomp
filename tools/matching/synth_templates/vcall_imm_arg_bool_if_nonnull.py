# "return p && p->vN(imm);" -- cdecl bool function null-checking its arg and calling a virtual with one imm arg.
PATTERN = 'mov ecx, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; push A ; call edx ; test eax, eax ; je +N ; mov al, N ; ret  ; xor al, al ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct VObjQ {\n" +
           "".join("    virtual int v%d(unsigned id) = 0;\n" % i for i in range(512)) +
           "};\n")
def emit(va, A, N):
    # N: [esp+4], disp, ... ; slot from vtable disp
    disp = N[1]
    src = "bool FUN_%08x(VObjQ* p) {\n    if (p && p->v%d(0x%xu)) return true;\n    return false;\n}" % (va, disp // 4, A[0])
    return src, "?FUN_%08x@@YA_NPAUVObjQ@@@Z" % va
