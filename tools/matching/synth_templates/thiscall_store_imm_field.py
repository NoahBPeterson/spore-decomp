# __thiscall member storing an immediate into a field: mov dword ptr [ecx+off], imm; ret
PATTERN = 'mov dword ptr [ecx + N], N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off, imm = N
    c = "C_%08x" % va
    pad = "char pad[0x%x]; " % off if off else ""
    src = ("#pragma pack(push, 1)\nstruct %s { %sint field; void Set(); };\n#pragma pack(pop)\n"
           "void %s::Set() { field = 0x%x; }" % (c, pad, c, imm))
    return src, "?Set@%s@@QAEXXZ" % c
