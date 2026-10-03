# Float product of two globals stored to a global, in an unoptimized (/Od /Ob1) /arch:SSE /fp:fast module (x87 without /fp:fast):
#   push ebp; mov ebp,esp; movss xmm0,[a]; mulss xmm0,[b]; movss [dst],xmm0; pop ebp; ret
# Typically the dynamic initializer of "float dst = a * b;" (e.g. 2*PI, deg-to-rad scale)
# where a/b are extern consts or __real@ literals; emitted as a plain function (shape-equivalent).
PATTERN = "push ebp ; mov ebp, esp ; movss xmm0, dword ptr [A] ; mulss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; pop ebp ; ret "
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/fp:fast"]
PRELUDE = ""
def emit(va, A, N):
    a, b, dst = A[0], A[1], A[2]
    s = ""
    for g in sorted(set([a, b, dst])):
        s += "extern float g_%08x;\n" % g
    s += "void FUN_%08x() { g_%08x = g_%08x * g_%08x; }" % (va, dst, a, b)
    return s, "?FUN_%08x@@YAXXZ" % va
