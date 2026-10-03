# g_len = wcslen(g_ptr) with wcslen inlined by /O2 intrinsic.
PATTERN = 'mov eax, dword ptr [A] ; lea edx, [eax + N] ; jmp +N ; lea ebx, [ebx] ; mov cx, word ptr [eax] ; add eax, N ; test cx, cx ; jne +N ; sub eax, edx ; sar eax, N ; mov dword ptr [A], eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "#include <string.h>\n"
def emit(va, A, N):
    p, l = "g_%08x" % A[0], "g_%08x" % A[1]
    src = ("extern const wchar_t* %s;\nextern int %s;\n"
           "void FUN_%08x() { %s = (int)wcslen(%s); }" % (p, l, va, l, p))
    return src, "?FUN_%08x@@YAXXZ" % va
