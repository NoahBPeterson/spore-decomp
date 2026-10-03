# __thiscall bool getter: xor eax,eax; cmp [ecx+off],eax; setne al; ret
# /O2 "bool C::Has() { return field != 0; }" on an opaque packed struct.
PATTERN = "xor eax, eax ; cmp dword ptr [ecx + N], eax ; setne al ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off = N[0]
    c = "C_%08x" % va
    src = ("#pragma pack(push, 1)\nstruct %s { char pad[0x%x]; int field; bool Has(); };\n#pragma pack(pop)\n"
           "bool %s::Has() { return field != 0; }" % (c, off, c))
    return src, "?Has@%s@@QAE_NXZ" % c
