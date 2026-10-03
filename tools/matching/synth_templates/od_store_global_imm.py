# /Od function storing an immediate into a global: push ebp; mov ebp,esp; mov [g],imm; pop ebp; ret
PATTERN = 'push ebp ; mov ebp, esp ; mov dword ptr [A], N ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    return ("extern unsigned int g_%08x;\nvoid FUN_%08x() { g_%08x = %du; }" % (A[0], va, A[0], N[0]),
            "?FUN_%08x@@YAXXZ" % va)
