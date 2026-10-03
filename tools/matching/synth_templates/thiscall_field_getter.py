# Trivial __thiscall getter returning a 32-bit field at a fixed offset:
#   mov eax, [ecx+off]; ret
# /O2 out-of-line member function "int C::Get() { return field; }". The class layout is opaque,
# so each instance gets its own packed struct with padding up to the field offset.
PATTERN = "mov eax, dword ptr [ecx + N] ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off = N[0]
    c = "C_%08x" % va
    src = ("#pragma pack(push, 1)\nstruct %s { char pad[0x%x]; int field; int Get(); };\n#pragma pack(pop)\n"
           "int %s::Get() { return field; }" % (c, off, c))
    return src, "?Get@%s@@QAEHXZ" % c
