# __thiscall setter: (float a0, int a1) stored to two adjacent fields, /arch:SSE:
#   mov eax,[esp+8]; movss xmm0,[esp+4]; movss [ecx+o1],xmm0; mov [ecx+o2],eax; ret 8
PATTERN = 'mov eax, dword ptr [esp + N] ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [ecx + N], xmm0 ; mov dword ptr [ecx + N], eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""

def emit(va, A, N):
    s1, s2, o1, o2, ret = N
    c = "C_%08x" % va
    fl = sorted([("fa", o1, "int"), ("fb", o2, "float")], key=lambda x: x[1])
    fl = [("fa", o1, "float"), ("fb", o2, "int")]
    fl.sort(key=lambda x: x[1])
    members, pos = "", 0
    for name, off, ty in fl:
        if off > pos:
            members += "char pad%d[0x%x]; " % (pos, off - pos)
        members += "%s %s; " % (ty, name)
        pos = off + 4
    src = ("#pragma pack(push, 1)\nstruct %s { %svoid Set(float a0, int a1); };\n#pragma pack(pop)\n"
           "void %s::Set(float a0, int a1) { fa = a0; fb = a1; }" % (c, members, c))
    return src, "?Set@%s@@QAEXMH@Z" % c
