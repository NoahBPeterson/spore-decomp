# Unoptimized (/Od) __thiscall setter storing a 32-bit stack argument into a field.
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp + N] ; mov dword ptr [eax + N], ecx ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off, ret = N[-2], N[-1]
    n = ret // 4
    c = "C_%08x" % va
    params = ", ".join("int a%d" % i for i in range(n))
    pad = "char pad[0x%x]; " % off if off else ""
    src = ("#pragma pack(push, 1)\nstruct %s { %sint field; void Set(%s); };\n#pragma pack(pop)\n"
           "void %s::Set(%s) { field = a0; }" % (c, pad, params, c, params))
    return src, "?Set@%s@@QAEX%s@Z" % (c, "H" * n)
