# Thunk: extern global object, call member ctor-like fn with (const char* name, 0,4,0,1,0,0,0,0,0)
PATTERN = 'push N ; push N ; push N ; push N ; push N ; push N ; push N ; push N ; push N ; push A ; mov ecx, A ; call EXT ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct HkReg { void __thiscall Reg(const char*, int, int, int, int, int, int, int, int, int); };
"""
def emit(va, A, N):
    a = ", ".join(str(n) for n in reversed(N))
    return ("extern const char s_%08x[];\nextern HkReg g_%08x;\nvoid FUN_%08x() { g_%08x.Reg(s_%08x, %s); }"
            % (A[0], A[1], va, A[1], A[0], a)), "?FUN_%08x@@YAXXZ" % va
