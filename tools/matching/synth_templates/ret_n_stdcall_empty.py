# Empty __stdcall function popping N bytes: ret N (void body, N/4 int args)
PATTERN = 'ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    n = N[0]
    args = ", ".join("int" for _ in range(n // 4)) or "void"
    return ('extern "C" void __stdcall FUN_%08x(%s) {}' % (va, args),
            "_FUN_%08x@%d" % (va, n))
