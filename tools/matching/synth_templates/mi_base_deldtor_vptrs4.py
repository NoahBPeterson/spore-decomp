# Scalar deleting destructor (??_G) of a multiple-inheritance class: primary base with an out-of-line
# virtual dtor at offset 0 plus three further polymorphic bases. Inline ~D stores the four vptrs then
# calls ~Base, then tests the delete flag.
PATTERN = 'push esi ; mov esi, ecx ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; mov dword ptr [esi + N], A ; mov dword ptr [esi + N], A ; call EXT ; test byte ptr [esp + N], N ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    offs = list(N[:3])
    c = "C_%08x" % va
    s = sorted(offs)
    bounds = s + [None]
    src = ""
    def pad(n):
        return " char pad[%d];" % (n - 4) if n > 4 else ""
    names = ["B", "X", "Y", "Z"]
    starts = [0] + s
    sizes = [starts[i + 1] - starts[i] for i in range(3)] + [4]
    rev = offs != s
    for i, nm in enumerate(names):
        t = "%s_%s" % (nm, c)
        if i == 0:
            src += "struct %s { %s(); virtual ~%s();%s };\n" % (t, t, t, pad(sizes[i]))
        elif rev and i > 1:
            src += "struct %s { virtual ~%s() {}%s };\n" % (t, t, pad(sizes[i]))
        else:
            src += "struct %s { virtual void f%s();%s };\n" % (t, nm.lower(), pad(sizes[i]))
    src += "struct %s : B_%s, X_%s, Y_%s, Z_%s { %s(); virtual ~%s() {} };\n" % (c, c, c, c, c, c, c)
    src += "%s::%s() {}" % (c, c)
    return src, "??_G%s@@UAEPAXI@Z" % c
