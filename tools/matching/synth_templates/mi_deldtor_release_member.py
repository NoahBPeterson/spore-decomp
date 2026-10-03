# Scalar deleting dtor of a class with two polymorphic bases (second at +off), a pointer member whose
# virtual slot is called if non-null, then base vptrs reset (second base first), delete this.
PATTERN = 'push esi ; mov esi, ecx ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; test byte ptr [esp + N], N ; mov dword ptr [esi + N], A ; mov dword ptr [esi], A ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = "struct Iface { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); };\n"

def emit(va, A, N):
    off, mem, slot = N[0], N[1], N[2]
    c = "C_%08x" % va
    pad1 = ("char pad1[%d]; " % (off - 4)) if off > 4 else ""
    pad2 = ("char pad2[%d]; " % (mem - off - 4)) if mem > off + 4 else ""
    k = slot // 4
    src = ("struct X_%s { virtual ~X_%s() {} %s};\n"
           "struct Y_%s { virtual ~Y_%s() {} %s};\n"
           "struct P_%s { Iface* p; ~P_%s() { if (p) p->s%d(); } };\n"
           "struct %s : X_%s, Y_%s { P_%s m; %s(); virtual ~%s() {} };\n"
           "%s::%s() {}" % (c, c, pad1, c, c, pad2, c, c, k, c, c, c, c, c, c, c, c))
    return src, "??_G%s@@UAEPAXI@Z" % c
