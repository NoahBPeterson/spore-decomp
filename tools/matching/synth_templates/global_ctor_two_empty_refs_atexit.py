# Dynamic initializer of a global whose inline ctor forwards two const refs to one empty
# stack object (G derives from two empty bases, so both refs hit the same byte, no CSE'd lea):
#   push ecx; lea; push; lea; push; mov ecx,g; call Y::Y; push dtor; call atexit; add esp,8; ret
PATTERN = 'push ecx ; lea eax, [esp + N] ; push eax ; lea ecx, [esp + N] ; push ecx ; mov ecx, A ; call EXT ; push A ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct EA {}; struct EB {}; struct EG : EA, EB {};
"""
def emit(va, A, N):
    g = "g_%08x" % A[0]
    t = "T_%08x" % A[0]
    src = ("struct Y_%08x { Y_%08x(const EA&, const EB&) throw(); ~Y_%08x(); int pad; };\n"
           "struct %s : Y_%08x { %s() throw() : Y_%08x((EG()), (EG())) {} };\n"
           "%s %s;" % (A[0], A[0], A[0], t, A[0], t, A[0], t, g))
    return src, "??__E%s@@YAXXZ" % g
