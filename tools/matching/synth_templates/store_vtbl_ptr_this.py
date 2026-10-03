# thiscall: *(this) = address constant (vtable store) ; ret
PATTERN = "mov dword ptr [ecx], A ; ret "
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    v = (A + N)[0]
    s = "S_%08x" % va
    if v < 0x2000000:
        src = "extern char g_%08x[];\nstruct %s { int v; void f(); };\nvoid %s::f() { v = (int)g_%08x; }" % (v, s, s, v)
    else:
        src = "struct %s { int v; void f(); };\nvoid %s::f() { v = (int)0x%x; }" % (s, s, v)
    return src, "?f@%s@@QAEXXZ" % s
