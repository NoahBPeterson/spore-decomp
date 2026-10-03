# Unoptimized (/Od) __thiscall getter returning a 32-bit field at a fixed offset.
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov eax, dword ptr [eax + N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off = N[-1]
    c = "C_%08x" % va
    src = ("#pragma pack(push, 1)\nstruct %s { char pad[0x%x]; int field; int Get(); };\n#pragma pack(pop)\n"
           "int %s::Get() { return field; }" % (c, off, c))
    return src, "?Get@%s@@QAEHXZ" % c
