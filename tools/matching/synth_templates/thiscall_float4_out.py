# thiscall getter copying four float members to four out pointers (ret 0x10)
PATTERN = 'fld dword ptr [ecx + N] ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; fstp dword ptr [eax] ; fld dword ptr [ecx + N] ; mov eax, dword ptr [esp + N] ; fstp dword ptr [edx] ; fld dword ptr [ecx + N] ; fstp dword ptr [eax] ; fld dword ptr [ecx + N] ; mov ecx, dword ptr [esp + N] ; fstp dword ptr [ecx] ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    o = [N[0], N[3], N[5], N[6]]
    s = "struct C_%08x { void f(float*, float*, float*, float*);\n" % va
    pos = 0
    for i, off in enumerate(o):
        s += "  char p%d[%d]; float m%d;\n" % (i, off - pos, i) if off > pos else "  float m%d;\n" % i
        pos = off + 4
    s += "};\n"
    s += "void C_%08x::f(float* p, float* q, float* r, float* s) { *p = m0; *q = m1; *r = m2; *s = m3; }" % va
    return s, "?f@C_%08x@@QAEXPAM000@Z" % va
