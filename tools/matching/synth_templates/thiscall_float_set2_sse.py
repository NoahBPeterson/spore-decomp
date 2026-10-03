# __thiscall setter copying two float stack args into two fields, /arch:SSE:
#   movss xmm0,[esp+s1]; movss [ecx+o1],xmm0; movss xmm0,[esp+s2]; movss [ecx+o2],xmm0; ret 4*n
PATTERN = 'movss xmm0, dword ptr [esp + N] ; movss dword ptr [ecx + N], xmm0 ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [ecx + N], xmm0 ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""

def emit(va, A, N):
    s1, o1, s2, o2, ret = N
    n = ret // 4
    c = "C_%08x" % va
    params = ", ".join("float a%d" % i for i in range(n))
    fl = sorted([("fa", o1, s1 // 4 - 1), ("fb", o2, s2 // 4 - 1)], key=lambda x: x[1])
    members, pos = "", 0
    for name, off, _ in fl:
        if off > pos:
            members += "char pad%d[0x%x]; " % (pos, off - pos)
        members += "float %s; " % name
        pos = off + 4
    body = "fa = a%d; fb = a%d;" % (s1 // 4 - 1, s2 // 4 - 1)
    src = ("#pragma pack(push, 1)\nstruct %s { %svoid Set(%s); };\n#pragma pack(pop)\n"
           "void %s::Set(%s) { %s }" % (c, members, params, c, params, body))
    return src, "?Set@%s@@QAEX%s@Z" % (c, "M" * n)
