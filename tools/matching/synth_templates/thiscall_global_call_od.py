# /Od /Ob1 thunk calling a __thiscall member on a file-scope global object:
#   push ebp; mov ebp,esp; mov ecx, offset g; call Obj::method; pop ebp; ret
PATTERN = 'push ebp ; mov ebp, esp ; mov ecx, A ; call EXT ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct GlobalObj { void Method(); };\n"

def emit(va, A, N):
    g = "g_%08x" % A[0]
    src = "extern GlobalObj %s;\nvoid FUN_%08x() { %s.Method(); }" % (g, va, g)
    return src, "?FUN_%08x@@YAXXZ" % va
