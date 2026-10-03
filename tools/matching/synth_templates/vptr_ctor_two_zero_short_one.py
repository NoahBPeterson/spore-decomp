# thiscall ctor of a polymorphic class: vptr, two zeroed dwords at +0xc/+0x10, u16 flag = 1 at +0x14
PATTERN = 'mov eax, ecx ; xor ecx, ecx ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], ecx ; mov ecx, N ; mov dword ptr [eax], A ; mov word ptr [eax + N], cx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    c = "C_%08x" % va
    src = ("struct %s { virtual void f(); unsigned pad[2]; unsigned a; unsigned b; unsigned short s; %s(); };\n"
           "void %s::f() {}\n"
           "%s::%s() : a(0), b(0), s(1) {}\n") % (c, c, c, c, c)
    return src, "??0%s@@QAE@XZ" % c
