# Member decrement: --field at +N -> dec dword ptr [ecx+N]; ret
PATTERN = 'dec dword ptr [ecx + N] ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0]
    src = ("struct C_%08x { char pad[%d]; int cnt; void Dec(); };\n"
           "void C_%08x::Dec() { --cnt; }") % (va, off, va)
    return src, "?Dec@C_%08x@@QAEXXZ" % va
