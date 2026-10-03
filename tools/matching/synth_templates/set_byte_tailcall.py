# Setter of a byte flag at this+N then tail-call (jmp) to another __fastcall function.
PATTERN = 'mov byte ptr [ecx + N], N ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, val = N[0], N[1]
    src = ("extern void __fastcall ext_%08x(void*);\n"
           "void __fastcall FUN_%08x(char* t) { t[%d] = %d; ext_%08x(t); }"
           % (va, va, off, val, va))
    return src, "?FUN_%08x@@YIXPAD@Z" % va
