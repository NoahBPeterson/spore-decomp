# Scalar deleting destructor (??_G) of a class with two polymorphic bases: primary base at offset 0 has an
# out-of-line virtual dtor, second base at offset 4 has an inline empty virtual dtor.
PATTERN = 'push esi ; mov esi, ecx ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; call EXT ; test byte ptr [esp + N], N ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    c = "C_%08x" % va
    src = ("struct B_%s { B_%s(); virtual ~B_%s(); };\n"
           "struct X_%s { virtual ~X_%s() {} };\n"
           "struct %s : B_%s, X_%s { %s(); virtual ~%s() {} };\n"
           "%s::%s() {}" % ((c,) * 3 + (c,) * 2 + (c,) * 5 + (c, c)))
    return src, "??_G%s@@UAEPAXI@Z" % c
