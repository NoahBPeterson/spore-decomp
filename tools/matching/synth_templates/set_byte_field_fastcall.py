# this->byte_at_offset = imm; ret  (fastcall, this in ecx)
PATTERN = "mov byte ptr [ecx + N], N ; ret "
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, val = N[0], N[1]
    return ("void __fastcall FUN_%08x(char* p) { p[%d] = %d; }" % (va, off, val),
            "?FUN_%08x@@YIXPAD@Z" % va)
