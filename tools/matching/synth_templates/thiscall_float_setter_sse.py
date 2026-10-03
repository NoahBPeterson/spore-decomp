# Trivial __thiscall setter storing a float stack argument into a field, in an /arch:SSE module:
#   movss xmm0, [esp+4*(k+1)]; movss [ecx+off], xmm0; ret 4*n
# /O2 /arch:SSE out-of-line member "void C::Set(float a0,...) { field = ak; }" (without /arch:SSE
# the copy is a plain mov eax / mov [ecx+off], eax).
PATTERN = "movss xmm0, dword ptr [esp + N] ; movss dword ptr [ecx + N], xmm0 ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""

def emit(va, A, N):
    soff, off, ret = N
    k = soff // 4 - 1
    n = ret // 4
    c = "C_%08x" % va
    params = ", ".join("float a%d" % i for i in range(n))
    pad = "char pad[0x%x]; " % off if off else ""
    src = ("#pragma pack(push, 1)\nstruct %s { %sfloat field; void Set(%s); };\n#pragma pack(pop)\n"
           "void %s::Set(%s) { field = a%d; }" % (c, pad, params, c, params, k))
    return src, "?Set@%s@@QAEX%s@Z" % (c, "M" * n)
