# Plain function storing three function pointers and two ints into extern globals
# (shape-equivalent; original is likely a dynamic initializer or ctor of a global table).
PATTERN = 'mov dword ptr [A], A ; mov dword ptr [A], A ; mov dword ptr [A], A ; mov dword ptr [A], N ; mov dword ptr [A], N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    g = lambda a: "g_%08x" % a
    g0, f0, g1, f1, g2, f2, g3, g4 = A
    d = "".join("extern void (*%s)();\nvoid FN_%08x();\n" % (g(a), f) for a, f in ((g0, f0), (g1, f1), (g2, f2)))
    d += "extern int %s;\nextern int %s;\n" % (g(g3), g(g4))
    body = "%s = FN_%08x; %s = FN_%08x; %s = FN_%08x; %s = %d; %s = %d;" % (
        g(g0), f0, g(g1), f1, g(g2), f2, g(g3), N[0], g(g4), N[1])
    return "%svoid FUN_%08x() { %s }" % (d, va, body), "?FUN_%08x@@YAXXZ" % va
