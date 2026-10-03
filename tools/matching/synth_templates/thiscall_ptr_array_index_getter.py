# __thiscall "int C::Get(int i) { return arr[i].v; }" where arr is an element* member at a fixed offset.
# mov eax,[ecx+off]; mov ecx,[esp+4]; mov eax,[eax+ecx*S]; ret 4 (ret 8 when a second arg is unused).
# S is the element stride (4 -> plain int, 8 -> 8-byte struct whose first dword is returned).
PATTERN = "mov eax, dword ptr [ecx + N] ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [eax + ecx*N] ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off, scale, ret = N[0], N[2], N[-1]
    nargs = ret // 4
    c = "C_%08x" % va
    params = "int i" + "".join(", int u%d" % k for k in range(1, nargs))
    src = ("#pragma pack(push, 1)\nstruct E_%08x { int v; char p[%d]; };\n"
           "struct %s { char pad[0x%x]; E_%08x *arr; int Get(%s); };\n#pragma pack(pop)\n"
           "int %s::Get(%s) { return arr[i].v; }" % (va, scale - 4, c, off, va, params, c, params))
    return src, "?Get@%s@@QAEH%s@Z" % (c, "H" * nargs)
