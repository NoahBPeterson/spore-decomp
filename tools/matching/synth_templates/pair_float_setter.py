# NOT BYTE-EXACT (0/7): best attempt differs only in register allocation (mov ecx,eax extra / reloads).
# cdecl f(a,b,float v): calls helper returning a pair of pointers by hidden ptr, stores v at +off in each non-null.
PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; sub esp, N ; push eax ; push ecx ; lea edx, [esp + N] ; push edx ; call EXT ; mov ecx, dword ptr [esp + N] ; movss xmm0, dword ptr [esp + N] ; add esp, N ; test ecx, ecx ; je +N ; movss dword ptr [ecx + N], xmm0 ; mov eax, dword ptr [esp + N] ; test eax, eax ; je +N ; movss dword ptr [eax + N], xmm0 ; test ecx, ecx ; jne +N ; test eax, eax ; jne +N ; add esp, N ; ret  ; mov eax, N ; add esp, N ; ret '
import os
FLAGS = os.environ.get("PFS_FLAGS", "/O2 /MD /Gy /EHsc /TP /arch:SSE").split()
PRELUDE = """struct Obj { char pad[0x400]; };
struct PairP { Obj* a; Obj* b; };
extern PairP Helper(int, int);
"""
import os
BODY = os.environ.get("PFS_BODY", """    if (p.a) p.a->f = v;
    if (p.b) p.b->f = v;
    if (!p.a && !p.b) return 0;
    return 1;
""")
def emit(va, A, N):
    off = N[7]
    src = ("struct O { char pad[OFF]; float f; };\n"
           "struct P { O* a; O* b; };\n"
           "extern void H(P*, int, int);\n"
           "int F(int a, int b, float v) {\n    P p;\n    H(&p, a, b);\n" + BODY + "}")
    src = src.replace("OFF", str(off)).replace("struct O ", "struct O%08x " % va).replace("struct P ", "struct P%08x " % va)
    src = src.replace("O*", "O%08x*" % va).replace("P*", "P%08x*" % va).replace("P p;", "P%08x p;" % va)
    src = src.replace("H(", "H%08x(" % va).replace("int F(", "int FUN_%08x(" % va)
    return src, "?FUN_%08x@@YAHHHM@Z" % va
