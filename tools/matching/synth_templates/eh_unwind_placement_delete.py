# EH unwind funclet of "new(\"Name\",0,0,0,0) T(...)" where T's ctor may throw: the compiler calls the
# matching placement operator delete(ptr, name, 0, 0, 0, 0) (cdecl) with ptr read from the EH slot [ebp-N]:
#   push 0 x4 ; push "Name" ; mov eax,[ebp-N] ; push eax ; call delete ; add esp,18h ; ret ; __ehhandler
# The parent is a stand-in function; only the funclet + __ehhandler bytes are verified (symbol $0).
PATTERN = 'push N ; push N ; push N ; push N ; push A ; mov eax, dword ptr [ebp - N] ; push eax ; call EXT ; add esp, N ; ret  ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t, const char*, int, unsigned, const char*, int);\n"
           "void operator delete(void*, const char*, int, unsigned, const char*, int);\n")

def emit(va, A, N):
    sp = N[4]
    k = (sp - 0x10) // 4
    t = "T_%08x" % va
    ex = "void E_%08x(void*);\n" % va
    loc = "unsigned buf[%d]; E_%08x(buf);\n  " % (k, va) if k > 0 else ""
    src = ("extern const char s_%08x[];\n%s"
           "struct %s { %s(); int d; };\n"
           "void* F_%08x() {\n  %sreturn new(s_%08x, 0, 0u, (const char*)0, 0) %s; }"
           % (A[0], ex, t, t, va, loc, A[0], t))
    return src, "__unwindfunclet$?F_%08x@@YAPAXXZ$0" % va
