# int inc() { return ++m; } at member offset N[0]
PATTERN = "inc dword ptr [ecx + N] ; mov eax, dword ptr [ecx + N] ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0]
    pad = "char pad[%d]; " % off if off else ""
    return ("struct S_%08x { %sint v; int f(); };\nint S_%08x::f() { return ++v; }" % (va, pad, va),
            "?f@S_%08x@@QAEHXZ" % va)
