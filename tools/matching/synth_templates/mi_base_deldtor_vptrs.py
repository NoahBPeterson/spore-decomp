# Scalar deleting destructor (??_G) of a multiple-inheritance class: primary base with an out-of-line
# virtual dtor at offset 0, two further polymorphic bases at offsets o2 and o3. The inline ~D stores
# the three vptrs then calls ~Base, then tests the delete flag.
PATTERN = 'push esi ; mov esi, ecx ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; mov dword ptr [esi + N], A ; call EXT ; test byte ptr [esp + N], N ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    o2, o3 = N[0], N[1]
    c = "C_%08x" % va
    lo, hi = sorted((o2, o3))
    # Base occupies [0,lo), first extra base [lo,hi), second extra base [hi,hi+4)
    src = ("struct B_%s { B_%s(); virtual ~B_%s(); char pad[%d]; };\n" % (c, c, c, lo - 4) if lo > 4 else
           "struct B_%s { B_%s(); virtual ~B_%s(); };\n" % (c, c, c))
    src += ("struct X_%s { virtual void fx(); char pad[%d]; };\n" % (c, hi - lo - 4) if hi - lo > 4 else
            "struct X_%s { virtual void fx(); };\n" % c)
    src += "struct Y_%s { virtual void fy(); };\n" % c
    if o2 > o3:
        # reversed store order needs the extra bases to have inline virtual dtors
        src = src.replace("virtual void fx();", "virtual ~X_%s() {}" % c).replace("virtual void fy();", "virtual ~Y_%s() {}" % c)
    src += "struct %s : B_%s, X_%s, Y_%s { %s(); virtual ~%s() {} };\n" % (c, c, c, c, c, c)
    src += "%s::%s() {}" % (c, c)
    return src, "??_G%s@@UAEPAXI@Z" % c
