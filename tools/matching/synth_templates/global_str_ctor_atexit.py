# Dynamic initializer of a file-scope global built from a string pointer by an out-of-line
# ctor, with an out-of-line dtor registered via atexit:
#   push &str; mov ecx,&g; call T::T; push ??__F; call atexit; pop ecx; ret
PATTERN = 'push A ; mov ecx, A ; call EXT ; push A ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct GStr { GStr(const void* s); ~GStr(); int pad; };
"""
def emit(va, A, N):
    s, g = A[0], A[1]
    return ("extern const char s_%08x[];\nGStr g_%08x(s_%08x);" % (s, g, s)), "??__Eg_%08x@@YAXXZ" % g
