# Scalar deleting dtor of D : B, Y, Z. B (+0) and Z (+off) have out-of-line virtual dtors, Y (+4) is
# polymorphic with a trivial dtor. D's three vptrs are stored, ~Z(this+off), ~B(this), delete.
PATTERN = 'push esi ; mov esi, ecx ; lea ecx, [esi + N] ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; mov dword ptr [ecx], A ; call EXT ; mov ecx, esi ; call EXT ; test byte ptr [esp + N], N ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off = N[0]
    c = "C_%08x" % va
    ysz = off - 4
    pad = (" char pad[%d];" % (ysz - 4)) if ysz > 4 else ""
    src = ("struct B_%(c)s { B_%(c)s(); virtual ~B_%(c)s(); };\n"
           "struct Y_%(c)s { virtual void fy();%(pad)s };\n"
           "struct Z_%(c)s { Z_%(c)s(); virtual ~Z_%(c)s(); };\n"
           "struct %(c)s : B_%(c)s, Y_%(c)s, Z_%(c)s { %(c)s(); virtual ~%(c)s() {} };\n"
           "%(c)s::%(c)s() {}" % dict(c=c, pad=pad))
    return src, "??_G%s@@UAEPAXI@Z" % c
