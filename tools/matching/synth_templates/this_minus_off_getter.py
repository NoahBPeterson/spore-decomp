# thiscall getter returning this - off (secondary-base subobject -> start of derived object)
PATTERN = 'lea eax, [ecx - N] ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0]
    return ("struct C_%08x { void* F() { return (char*)this - %d; } };\n"
            "void* (C_%08x::*p_%08x)() = &C_%08x::F;" % (va, off, va, va, va)), "?F@C_%08x@@QAEPAXXZ" % va
