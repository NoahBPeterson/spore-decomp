# Scalar deleting destructor (??_G) of a class with two polymorphic bases (offsets 0 and 4), both
# with inline empty virtual dtors; the flag test comes first, vptrs stored 4 then 0, delete after.
PATTERN = 'test byte ptr [esp + N], N ; push esi ; mov esi, ecx ; mov dword ptr [esi + N], A ; mov dword ptr [esi], A ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off = [n for n in N if n not in (1, 4)] or [4]
    off = off[0]
    c = "C_%08x" % va
    pad = ("char pad[%d]; " % (off - 4)) if off > 4 else ""
    src = ("struct X_%s { virtual ~X_%s() {} %s};\n"
           "struct Y_%s { virtual ~Y_%s() {} };\n"
           "struct %s : X_%s, Y_%s { %s(); virtual ~%s() {} };\n"
           "%s::%s() {}" % (c, c, pad, c, c, c, c, c, c, c, c, c))
    return src, "??_G%s@@UAEPAXI@Z" % c
