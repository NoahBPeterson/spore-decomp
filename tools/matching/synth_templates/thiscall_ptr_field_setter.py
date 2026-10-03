# this->ptr(+N0)->field(+N2) = arg; /O2 __thiscall: mov eax,[ecx+N0]; mov ecx,[esp+4]; mov [eax+N2],ecx; ret 4
PATTERN = 'mov eax, dword ptr [ecx + N] ; mov ecx, dword ptr [esp + N] ; mov dword ptr [eax + N], ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    o1, soff, o2, ret = N
    n = ret // 4
    k = soff // 4 - 1
    c = "C_%08x" % va
    params = ", ".join("int a%d" % i for i in range(n))
    src = ("struct %s { void Set(%s); };\n"
           "void %s::Set(%s) { *(int*)(*(char**)((char*)this + 0x%x) + 0x%x) = a%d; }"
           % (c, params, c, params, o1, o2, k))
    return src, "?Set@%s@@QAEX%s@Z" % (c, "H" * n)
