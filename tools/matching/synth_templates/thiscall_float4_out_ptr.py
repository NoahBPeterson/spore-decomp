# __thiscall returning a 4-float struct by value built from four consecutive float members (x87):
# hidden return pointer in eax first, 4x fld/fstp, ret 4
PATTERN = 'mov eax, dword ptr [esp + N] ; fld dword ptr [ecx + N] ; fstp dword ptr [eax] ; fld dword ptr [ecx + N] ; fstp dword ptr [eax + N] ; fld dword ptr [ecx + N] ; fstp dword ptr [eax + N] ; fld dword ptr [ecx + N] ; fstp dword ptr [eax + N] ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct W4 { float x, y, z, w; };\n"
def emit(va, A, N):
    c = "C_%08x" % va
    s = "struct %s { char pad[0x%x]; float a, b, c, d; W4 f(); };\n" % (c, N[1])
    s += "W4 %s::f() { W4 r = {a, b, c, d}; return r; }" % c
    return s, "?f@%s@@QAE?AUW4@@XZ" % c
