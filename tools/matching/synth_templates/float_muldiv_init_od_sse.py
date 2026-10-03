# Float a*b/c of three globals stored to a global, in an unoptimized (/Od /Ob1) /arch:SSE /fp:fast module:
#   push ebp; mov ebp,esp; movss xmm0,[a]; mulss xmm0,[b]; divss xmm0,[c]; movss [dst],xmm0; pop ebp; ret
# Real compiler-generated dynamic initializer ??__E<dst>@@YAXXZ of
#   float dst = a * b / c;
# with a/b/c extern floats (e.g. degrees * PI / 180); /Od keeps it a runtime initializer.
PATTERN = "push ebp ; mov ebp, esp ; movss xmm0, dword ptr [A] ; mulss xmm0, dword ptr [A] ; divss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; pop ebp ; ret "
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/fp:fast"]
PRELUDE = ""
def emit(va, A, N):
    a, b, c, dst = A[0], A[1], A[2], A[3]
    s = ""
    for g in sorted(set([a, b, c]) - {dst}):
        s += "extern float g_%08x;\n" % g
    s += "float g_%08x = g_%08x * g_%08x / g_%08x;" % (dst, a, b, c)
    return s, "??__Eg_%08x@@YAXXZ" % dst
