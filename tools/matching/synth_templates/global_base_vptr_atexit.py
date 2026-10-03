# Dynamic initializer of a file-scope global of a polymorphic class whose inline default ctor calls
# an out-of-line base default ctor, then stores the vptr; dtor registered via atexit:
#   mov ecx,&g; call Base::Base; push ??__Fg; mov [g],vtbl; call atexit; pop ecx; ret
# Source shape: `struct D : B { D() {} virtual ~D(); }; D g;` at /O2.
PATTERN = 'mov ecx, A ; call EXT ; push A ; mov dword ptr [A], A ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct GBase { GBase(); int pad; };
struct GDer : GBase { GDer() {} virtual ~GDer(); };
"""
def emit(va, A, N):
    return "GDer g_%08x;" % A[0], "??__Eg_%08x@@YAXXZ" % A[0]
