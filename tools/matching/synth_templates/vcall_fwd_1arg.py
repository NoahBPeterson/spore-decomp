# Free cdecl wrapper forwarding to a virtual thiscall member with one argument:
#   mov ecx,[esp+4]; mov eax,[ecx]; mov edx,[esp+8]; mov eax,[eax+off]; push edx; call eax; ret
PATTERN = "mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [eax + N] ; push edx ; call eax ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off = N[2]
    pads = "".join("virtual void p%d(); " % i for i in range(off // 4))
    cls = "C_%08x" % va
    if N[0] == 8:
        src = ("struct %s { %svirtual void m(int); };\n"
               "void FUN_%08x(int a, %s* p) { p->m(a); }") % (cls, pads, va, cls)
        return src, "?FUN_%08x@@YAXHPAU%s@@@Z" % (va, cls)
    src = ("struct %s { %svirtual void m(int); };\n"
           "void FUN_%08x(%s* p, int a) { p->m(a); }") % (cls, pads, va, cls)
    return src, "?FUN_%08x@@YAXPAU%s@@H@Z" % (va, cls)
