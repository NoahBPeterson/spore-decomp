# Scalar deleting dtor, two polymorphic bases (second at +off); two pointer members' virtual slots called
# (higher offset first), then both base vptrs reset (second then first), then delete via ext operator delete.
PATTERN = 'push esi ; mov esi, ecx ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; test byte ptr [esp + N], N ; mov dword ptr [esi + N], A ; mov dword ptr [esi], A ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = "struct Iface { " + " ".join("virtual void s%d();" % i for i in range(64)) + " };\n"

def emit(va, A, N):
    off, m2, s2, m1, s1 = N[0], N[1], N[2], N[3], N[4]
    c = "C_%08x" % va
    pad1 = ("char pad1[%d]; " % (off - 4)) if off > 4 else ""
    pad2 = ("char pad2[%d]; " % (m1 - off - 4)) if m1 > off + 4 else ""
    pad3 = ("char pad3[%d]; " % (m2 - m1 - 4)) if m2 > m1 + 4 else ""
    src = ("struct X_%(c)s { virtual ~X_%(c)s() {} %(pad1)s};\n"
           "struct Y_%(c)s { virtual ~Y_%(c)s() {} };\n"
           "struct P_%(c)s { Iface* p; ~P_%(c)s() { if (p) p->s%(k1)d(); } };\n"
           "struct Q_%(c)s { Iface* p; ~Q_%(c)s() { if (p) p->s%(k2)d(); } };\n"
           "struct %(c)s : X_%(c)s, Y_%(c)s { %(pad2)sP_%(c)s a; %(pad3)sQ_%(c)s b; %(c)s(); virtual ~%(c)s() {} };\n"
           "%(c)s::%(c)s() {}\n"
           "void use_%(c)s(%(c)s* q) { delete q; }" % dict(c=c, pad1=pad1, pad2=pad2, pad3=pad3, k1=s1 // 4, k2=s2 // 4))
    return src, "??_G%s@@UAEPAXI@Z" % c
