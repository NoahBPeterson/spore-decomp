# Trivial __thiscall getter returning a float field at a fixed offset:
#   fld dword ptr [ecx+off]; ret
# /O2 out-of-line member function "float C::Get() { return field; }" (x87 return in ST0).
# Class layout is opaque, so each instance gets its own packed struct padded to the field offset.
PATTERN = "fld dword ptr [ecx + N] ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off = N[0]
    c = "C_%08x" % va
    src = ("#pragma pack(push, 1)\nstruct %s { char pad[0x%x]; float field; float Get(); };\n#pragma pack(pop)\n"
           "float %s::Get() { return field; }" % (c, off, c))
    return src, "?Get@%s@@QAEMXZ" % c
