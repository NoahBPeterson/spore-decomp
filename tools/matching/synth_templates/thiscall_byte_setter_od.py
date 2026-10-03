# Unoptimized (/Od) __thiscall setter storing an 8-bit stack argument into a field.
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov cl, byte ptr [ebp + N] ; mov byte ptr [eax + N], cl ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off, ret = N[-2], N[-1]
    n = ret // 4
    c = "C_%08x" % va
    params = ", ".join("bool a%d" % i for i in range(n))
    src = ("#pragma pack(push, 1)\nstruct %s { char pad[0x%x]; bool field; void Set(%s); };\n#pragma pack(pop)\n"
           "void %s::Set(%s) { field = a0; }" % (c, off, params, c, params))
    return src, "?Set@%s@@QAEX%s@Z" % (c, "_N" * n)
