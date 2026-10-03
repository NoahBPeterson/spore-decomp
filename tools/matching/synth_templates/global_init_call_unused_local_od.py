# Dynamic initializer of a file-scope global in an /Od /Ob1 module, whose inlined ctor calls an
# external __thiscall member and has an unused local of N bytes (reserved stack slot):
#   push ebp; mov ebp,esp; sub esp,N; mov ecx, offset g; call Obj::Init; mov esp,ebp; pop ebp; ret
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov ecx, A ; call EXT ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    g = "g_%08x" % A[0]
    n = N[0]
    src = ("struct T_%08x { void Init(); T_%08x() { Init(); unsigned unused[%d]; } };\n"
           "T_%08x %s;" % (va, va, n // 4, va, g))
    return src, "??__E%s@@YAXXZ" % g
