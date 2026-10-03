# Dynamic initializer of a file-scope int copied from an extern int defined in another TU:
# mov eax,[src] ; mov [dst],eax ; ret
PATTERN = 'mov eax, dword ptr [A] ; mov dword ptr [A], eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    src, dst = A[0], A[1]
    return ("extern unsigned int g_%08x;\nunsigned int g_%08x = g_%08x;" % (src, dst, src),
            "??__Eg_%08x@@YAXXZ" % dst)
