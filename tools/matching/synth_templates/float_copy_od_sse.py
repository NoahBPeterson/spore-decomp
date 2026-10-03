# Float global-to-global copy in an unoptimized (/Od /Ob1) /arch:SSE module:
#   push ebp; mov ebp,esp; movss xmm0,[src]; movss [dst],xmm0; pop ebp; ret
# Typically the dynamic initializer of "float dst = src;" (src from another TU or a
# non-constexpr constant such as numeric_limits<float>::infinity()); emitted here as a
# plain function since the symbol name is free.
PATTERN = "push ebp ; mov ebp, esp ; movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; pop ebp ; ret "
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""
def emit(va, A, N):
    src, dst = A[0], A[1]
    s = ("extern float g_%08x;\n" % src)
    if dst != src:
        s += "extern float g_%08x;\n" % dst
    s += "void FUN_%08x() { g_%08x = g_%08x; }" % (va, dst, src)
    return s, "?FUN_%08x@@YAXXZ" % va
