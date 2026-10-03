# Scalar deleting destructor (??_G) of a class whose virtual destructor is inline and empty:
#   test [esp+4],1; push esi; mov esi,ecx; mov [esi],vftable; je; push esi; call operator delete; add esp,4; mov eax,esi; pop esi; ret 4
# The inlined ~T keeps its vptr store (the class's own vftable, or a base's when bases have empty
# inline dtors). ??_G is emitted with the vftable, i.e. in the TU defining an out-of-line ctor.
# vftable address and operator delete are relocations, so only the shape matters. Plain /O2.
PATTERN = "test byte ptr [esp + N], N ; push esi ; mov esi, ecx ; mov dword ptr [esi], A ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    c = "C_%08x" % va
    src = ("struct %s { %s(); virtual ~%s() {} };\n"
           "%s::%s() {}" % (c, c, c, c, c))
    return src, "??_G%s@@UAEPAXI@Z" % c
