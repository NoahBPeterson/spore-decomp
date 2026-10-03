# Member increment: ++field at +N -> inc dword ptr [ecx+N]; ret
PATTERN = 'inc dword ptr [ecx + N] ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0]
    src = ("struct C_%08x { char pad[%d]; int cnt; void Inc(); };\n"
           "void C_%08x::Inc() { ++cnt; }") % (va, off, va)
    return src, "?Inc@C_%08x@@QAEXXZ" % va
