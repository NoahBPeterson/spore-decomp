# rbtree-style clear(): outer::f() { t.clear(); } where T::clear() { Nuke(static_cast<N*>(anchor.parent)); }
# inlined: mov eax,[ecx+f]; add ecx,s; push eax; call Nuke; ret  (anchor parent pointer at T+12)
PATTERN = 'mov eax, dword ptr [ecx + N] ; add ecx, N ; push eax ; call EXT ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    f, s = N[0], N[1]
    d = f - s
    pre = d - 8          # bytes before anchor inside T (anchor.parent at anchor+8)
    t = "T_%08x" % va; o = "O_%08x" % va
    src = ("struct Nb_%08x { Nb_%08x* r; Nb_%08x* l; Nb_%08x* p; int c; };\n"
           "struct N_%08x : Nb_%08x { int val; };\n"
           "struct %s { char pre[%d]; Nb_%08x anchor; void Nuke(N_%08x*); void clear() { Nuke(static_cast<N_%08x*>(anchor.p)); } };\n"
           "struct %s { char pad[%d]; %s t; void FUN_%08x(); };\n"
           "void %s::FUN_%08x() { t.clear(); }\n"
           % (va, va, va, va, va, va, t, pre, va, va, va, o, s, t, va, o, va))
    return src, "?FUN_%08x@%s@@QAEXXZ" % (va, o)
