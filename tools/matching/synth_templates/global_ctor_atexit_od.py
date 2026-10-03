# Dynamic initializer of a file-scope global with out-of-line ctor/dtor in an unoptimized
# (/Od /Ob1) module: push ebp; mov ebp,esp; mov ecx,&g; call T::T; push ??__Fg; call atexit; add esp,4; pop ebp; ret
PATTERN = 'push ebp ; mov ebp, esp ; mov ecx, A ; call EXT ; push A ; call EXT ; add esp, N ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct GObj { GObj(); ~GObj(); int pad; };
"""
def emit(va, A, N):
    return "GObj g_%08x;" % A[0], "??__Eg_%08x@@YAXXZ" % A[0]
