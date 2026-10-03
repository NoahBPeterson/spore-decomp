# int inc() { int t = v + 1; v = t; return t; }  -> mov eax,[ecx+N]; inc eax; mov [ecx+N],eax; ret
# (plain "return ++v" folds to inc [mem]; mov eax,[mem])
PATTERN = "mov eax, dword ptr [ecx + N] ; inc eax ; mov dword ptr [ecx + N], eax ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0]
    pad = "char pad[%d]; " % off if off else ""
    return ("struct S_%08x { %sint v; int f(); };\nint S_%08x::f() { int t = v + 1; v = t; return t; }" % (va, pad, va),
            "?f@S_%08x@@QAEHXZ" % va)
