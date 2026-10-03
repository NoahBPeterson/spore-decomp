# Dynamic initializer of a file-scope global object whose class has an out-of-line default
# constructor and an out-of-line destructor:
#   mov ecx, &g; call T::T; push ??__Fg (atexit dtor stub); call atexit; pop ecx; ret
# Source shape: `struct T { T(); ~T(); }; T g;` at /O2. Constructor/destructor targets and the
# ??__F stub are relocations (masked), so one shared class type serves every instance.
PATTERN = 'mov ecx, A ; call EXT ; push A ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct GObj { GObj(); ~GObj(); int pad; };
"""
def emit(va, A, N):
    return "GObj g_%08x;" % A[0], "??__Eg_%08x@@YAXXZ" % A[0]
