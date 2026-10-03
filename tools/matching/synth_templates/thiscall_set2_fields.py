# __thiscall setter storing two 32-bit stack args into two fields:
#   mov eax,[esp+4]; mov edx,[esp+8]; mov [ecx+o1],eax; mov [ecx+o2],edx; ret 8
PATTERN = 'mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; mov dword ptr [ecx + N], eax ; mov dword ptr [ecx + N], edx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    s1, s2, o1, o2, ret = N
    c = "C_%08x" % va
    # fields laid out in offset order; assignments written in asm store order
    fl = sorted([("fa", o1), ("fb", o2)], key=lambda x: x[1])
    members, pos = "", 0
    for name, off in fl:
        if off > pos:
            members += "char pad%d[0x%x]; " % (pos, off - pos)
        members += "int %s; " % name
        pos = off + 4
    src = ("#pragma pack(push, 1)\nstruct %s { %svoid Set(int a0, int a1); };\n#pragma pack(pop)\n"
           "void %s::Set(int a0, int a1) { fa = a%d; fb = a%d; }"
           % (c, members, c, s1 // 4 - 1, s2 // 4 - 1))
    return src, "?Set@%s@@QAEXHH@Z" % c
