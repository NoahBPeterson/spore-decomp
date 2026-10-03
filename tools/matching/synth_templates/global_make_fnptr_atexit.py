# Dynamic initializer of a file-scope object with out-of-line dtor whose inline ctor stores
# Make(id, fnptr): push fn; push id; call Make; push ??__F; mov [g],eax; call atexit.
PATTERN = 'push A ; push A ; call EXT ; push A ; mov dword ptr [A], eax ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef void (*Fn)();
unsigned Make(unsigned id, Fn f);
struct GObj { unsigned v; GObj(unsigned id, Fn f) : v(Make(id, f)) {} ~GObj(); };
"""
def emit(va, A, N):
    fn, imm, dt, g = A[0], A[1], A[2], A[3]
    return ("extern void fn_%08x();\nGObj g_%08x(0x%Xu, fn_%08x);" % (fn, g, imm, fn),
            "??__Eg_%08x@@YAXXZ" % g)
