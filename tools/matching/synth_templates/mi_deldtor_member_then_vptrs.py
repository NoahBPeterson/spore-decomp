# Scalar deleting dtor, two polymorphic bases (second at +off); pointer member's virtual slot called first, then base vptrs reset.
PATTERN = 'push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; test byte ptr [esp + N], N ; mov dword ptr [esi + N], A ; mov dword ptr [esi], A ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = "struct Iface { " + " ".join("virtual void s%d();" % i for i in range(64)) + " };\n"

def emit(va, A, N):
    mem, slot, off = N[0], N[1], N[4]
    c = "C_%08x" % va
    pad1 = ("char pad1[%d]; " % (off - 4)) if off > 4 else ""
    pad2 = ("char pad2[%d]; " % (mem - off - 4)) if mem > off + 4 else ""
    k = slot // 4
    src = ("struct X_%(c)s { virtual ~X_%(c)s() {} %(pad1)s};\n"
           "struct Y_%(c)s { virtual ~Y_%(c)s() {} };\n"
           "struct P_%(c)s { Iface* p; ~P_%(c)s() { if (p) p->s%(k)d(); } };\n"
           "struct %(c)s : X_%(c)s, Y_%(c)s { %(pad2)sP_%(c)s m; %(c)s(); };\n"
           "%(c)s::%(c)s() {}\n"
           "void use_%(c)s(%(c)s* q) { delete q; }" % dict(c=c, pad1=pad1, pad2=pad2, k=k))
    return src, "??_G%s@@UAEPAXI@Z" % c
