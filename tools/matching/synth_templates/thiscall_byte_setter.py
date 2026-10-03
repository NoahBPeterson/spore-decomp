# Trivial __thiscall setter storing one 8-bit (bool/char) stack argument into a field:
#   mov al, [esp+4*(k+1)]; mov [ecx+off], al; ret 4*n
# /O2 out-of-line member "void C::Set(bool a0,...) { field = ak; }". Extra args pad the
# parameter list so the ret immediate matches (each bool arg occupies a 4-byte slot).
PATTERN = "mov al, byte ptr [esp + N] ; mov byte ptr [ecx + N], al ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    soff, off, ret = N
    k = soff // 4 - 1
    n = ret // 4
    c = "C_%08x" % va
    params = ", ".join("bool a%d" % i for i in range(n))
    pad = "char pad[0x%x]; " % off if off else ""
    src = ("#pragma pack(push, 1)\nstruct %s { %sbool field; void Set(%s); };\n#pragma pack(pop)\n"
           "void %s::Set(%s) { field = a%d; }" % (c, pad, params, c, params, k))
    return src, "?Set@%s@@QAEX%s@Z" % (c, "_N" * n)
