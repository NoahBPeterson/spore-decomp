# Dynamic initializer of a file-scope float copied from an extern const float (defined in another TU),
# compiled with /arch:SSE: movss xmm0,[src] ; movss [dst],xmm0 ; ret
PATTERN = "movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""
def emit(va, A, N):
    src, dst = A[0], A[1]
    return ("extern const float g_%08x;\nfloat g_%08x = g_%08x;" % (src, dst, src),
            "??__Eg_%08x@@YAXXZ" % dst)
