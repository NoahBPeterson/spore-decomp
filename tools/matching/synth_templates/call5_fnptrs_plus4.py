# int f(){ return callee(fnA, fnB, fnC, fnD, data) + 4; } : 5 pushed addresses, stdcall callee, add eax,4
PATTERN = 'push A ; push A ; push A ; push A ; push A ; call EXT ; add eax, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "int __stdcall FUN_00b21340(void*, void*, void*, void*, void*);\n"
def emit(va, A, N):
    a = ", ".join("(void*)0x%08xu" % x for x in reversed(A))
    return ("int FUN_%08x() { return FUN_00b21340(%s) + %d; }" % (va, a, N[0])), "?FUN_%08x@@YAHXZ" % va
