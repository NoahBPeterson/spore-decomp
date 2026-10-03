# Scalar deleting dtor, two polymorphic bases (second at +off), pointer member released via vcall, trailing member with out-of-line dtor.
PATTERN = 'push esi ; mov esi, ecx ; lea ecx, [esi + N] ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; call EXT ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; test byte ptr [esp + N], N ; mov dword ptr [esi + N], A ; mov dword ptr [esi], A ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP", "/GR-"]
PRELUDE = "struct Iface { " + " ".join("virtual void s%d();" % i for i in range(16)) + " };\n"

def emit(va, A, N):
    qoff, off, mem, slot = N[0], N[1], N[2], N[3]
    c = "C_%08x" % va
    k = slot // 4
    inbase = mem < off
    px = "P_%s m; " % c if inbase else ""
    pad1 = ("char pad1[%d]; " % (off - 4 - (4 if inbase else 0))) if off > 4 else ""
    if inbase:
        pad1 = "char pad0[%d]; P_%s m; " % (mem - 4, c) + ("char pad1[%d]; " % (off - mem - 4) if off > mem + 4 else "")
    start = off + 4
    pad2, pm = "", ""
    cur = start
    if not inbase:
        if mem > cur: pad2 += "uint32_t pad2[%d]; " % ((mem - cur) // 4)
        pad2 += "P_%s m; " % c
        cur = mem + 4
    if qoff > cur: pad2 += "uint32_t pad3[%d]; " % ((qoff - cur) // 4)
    src = ("typedef unsigned int uint32_t;\n"
           "struct Iface_%(c)s;\n"
           "struct P_%(c)s { Iface* p; ~P_%(c)s() { if (p) p->s%(k)d(); } };\n"
           "struct Q_%(c)s { ~Q_%(c)s(); };\n"
           "struct X_%(c)s { virtual ~X_%(c)s() {} %(pad1)s};\n"
           "struct Y_%(c)s { virtual ~Y_%(c)s() {} };\n"
           "struct %(c)s : X_%(c)s, Y_%(c)s { %(pad2)s%(pm)sQ_%(c)s q; %(c)s(); virtual ~%(c)s() {} };\n"
           "%(c)s::%(c)s() {}\n" % dict(c=c, pad1=pad1, pad2=pad2, pm='', k=k))
    src = src.replace("struct Iface_%s;\n" % c, "")
    return src, "??_G%s@@UAEPAXI@Z" % c
