# g_len16 = (unsigned short)strlen(g_ptr) with strlen inlined by /O2 intrinsic.
PATTERN = 'mov eax, dword ptr [A] ; lea edx, [eax + N] ; mov cl, byte ptr [eax] ; inc eax ; test cl, cl ; jne +N ; sub eax, edx ; mov word ptr [A], ax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "#include <string.h>\n"
def emit(va, A, N):
    p, l = "g_%08x" % A[0], "g_%08x" % A[1]
    src = ("extern const char* %s;\nextern unsigned short %s;\n"
           "void FUN_%08x() { %s = (unsigned short)strlen(%s); }" % (p, l, va, l, p))
    return src, "?FUN_%08x@@YAXXZ" % va
