# Scalar deleting destructor (??_G) of a class with a virtual, out-of-line destructor:
#   push esi; mov esi,ecx; call ~T; test [esp+8],1; je; push esi; call operator delete; add esp,4; mov eax,esi; pop esi; ret 4
# The ??_G is emitted alongside the vftable, which MSVC emits in the TU that defines a ctor.
# Call targets (dtor and operator delete) are relocations, so only the shape matters. Plain /O2.
PATTERN = "push esi ; mov esi, ecx ; call EXT ; test byte ptr [esp + N], N ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    c = "C_%08x" % va
    src = ("struct %s { %s(); virtual ~%s(); };\n"
           "%s::%s() {}" % (c, c, c, c, c))
    return src, "??_G%s@@UAEPAXI@Z" % c
