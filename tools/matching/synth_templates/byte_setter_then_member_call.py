# __thiscall member: store 8-bit stack arg at [this+off], then call a no-arg thiscall member, ret 4.
PATTERN = 'mov al, byte ptr [esp + N] ; mov byte ptr [ecx + N], al ; call EXT ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    soff, off, ret = N
    n = ret // 4
    k = soff // 4 - 1
    c = "C_%08x" % va
    params = ", ".join("bool a%d" % i for i in range(n))
    src = ("#pragma pack(push, 1)\nstruct %s { char pad[0x%x]; bool field; void Ext(); void Set(%s); };\n#pragma pack(pop)\n"
           "void %s::Set(%s) { field = a%d; Ext(); }" % (c, off, params, c, params, k))
    return src, "?Set@%s@@QAEX%s@Z" % (c, "_N" * n)
