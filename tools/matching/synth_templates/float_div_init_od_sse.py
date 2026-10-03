# Float quotient of two globals stored to a global, in an unoptimized (/Od /Ob1) /arch:SSE /fp:fast module:
#   push ebp; mov ebp,esp; movss xmm0,[a]; divss xmm0,[b]; movss [dst],xmm0; pop ebp; ret
# This is the real compiler-generated dynamic initializer ??__E<dst>@@YAXXZ of
#   float dst = a / b;
# with a/b extern floats (e.g. 1.0f / scale); /Od keeps it a runtime initializer.
PATTERN = "push ebp ; mov ebp, esp ; movss xmm0, dword ptr [A] ; divss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; pop ebp ; ret "
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/fp:fast"]
PRELUDE = ""
def emit(va, A, N):
    a, b, dst = A[0], A[1], A[2]
    s = ""
    for g in sorted(set([a, b]) - {dst}):
        s += "extern float g_%08x;\n" % g
    s += "float g_%08x = g_%08x / g_%08x;" % (dst, a, b)
    return s, "??__Eg_%08x@@YAXXZ" % dst
