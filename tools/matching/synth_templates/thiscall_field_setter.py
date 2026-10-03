# Trivial __thiscall setter storing one 32-bit stack argument into a field:
#   mov eax, [esp+4*(k+1)]; mov [ecx+off], eax; ret 4*n
# /O2 out-of-line member "void C::Set(int a0,...,int an-1) { field = ak; }". Unused args just
# pad the parameter list so the ret immediate matches.
PATTERN = "mov eax, dword ptr [esp + N] ; mov dword ptr [ecx + N], eax ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    soff, off, ret = N
    k = soff // 4 - 1
    n = ret // 4
    c = "C_%08x" % va
    params = ", ".join("int a%d" % i for i in range(n))
    pad = "char pad[0x%x]; " % off if off else ""
    src = ("#pragma pack(push, 1)\nstruct %s { %sint field; void Set(%s); };\n#pragma pack(pop)\n"
           "void %s::Set(%s) { field = a%d; }" % (c, pad, params, c, params, k))
    return src, "?Set@%s@@QAEX%s@Z" % (c, "H" * n)
