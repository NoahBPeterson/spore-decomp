# Trivial __thiscall getter returning the address of a member at a fixed offset:
#   lea eax, [ecx+off]; ret
# /O2 out-of-line member function "T* C::Get() { return &field; }". Class layout is opaque,
# so each instance gets its own packed struct with padding up to the member offset.
PATTERN = "lea eax, [ecx + N] ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off = N[0]
    c = "C_%08x" % va
    pad = ("char pad[0x%x]; " % off) if off else ""
    src = ("#pragma pack(push, 1)\nstruct %s { %sint field; int* Get(); };\n#pragma pack(pop)\n"
           "int* %s::Get() { return &field; }" % (c, pad, c))
    return src, "?Get@%s@@QAEPAHXZ" % c
