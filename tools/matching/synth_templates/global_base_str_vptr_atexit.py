# Dynamic initializer of a file-scope global of a polymorphic class whose inline default ctor calls
# an out-of-line base ctor taking a string pointer, then stores the vptr; dtor registered via atexit:
#   push str; mov ecx,&g; call Base::Base; push ??__Fg; mov [g],vtbl; call atexit; pop ecx; ret
# Source shape: `struct D : B { D() : B("s") {} virtual ~D(); }; D g;` at /O2.
PATTERN = 'push A ; mov ecx, A ; call EXT ; push A ; mov dword ptr [A], A ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct GBase { GBase(const char*); int pad; };
struct GDer : GBase { GDer() : GBase("s") {} virtual ~GDer(); };
"""
def emit(va, A, N):
    return "GDer g_%08x;" % A[1], "??__Eg_%08x@@YAXXZ" % A[1]
