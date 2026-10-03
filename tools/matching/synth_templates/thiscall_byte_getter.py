# Trivial __thiscall getter returning an 8-bit (bool/char) field at a fixed offset:
#   mov al, [ecx+off]; ret
# /O2 out-of-line member function "bool C::Get() { return field; }". Opaque layout: each
# instance gets its own struct with padding up to the field offset (offset 0 -> no pad).
PATTERN = "mov al, byte ptr [ecx + N] ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off = N[0]
    c = "C_%08x" % va
    pad = "char pad[0x%x]; " % off if off else ""
    src = ("struct %s { %sbool field; bool Get(); };\n"
           "bool %s::Get() { return field; }" % (c, pad, c))
    return src, "?Get@%s@@QAE_NXZ" % c
