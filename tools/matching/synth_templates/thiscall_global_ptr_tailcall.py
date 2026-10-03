# Thunk tail-calling a __thiscall member on the object a global pointer points to:
#   mov ecx, [g]; jmp Obj::method
PATTERN = 'mov ecx, dword ptr [A] ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct GlobalObj { void Method(); };\n"

def emit(va, A, N):
    g = "g_%08x" % A[0]
    src = "extern GlobalObj* %s;\nvoid FUN_%08x() { %s->Method(); }" % (g, va, g)
    return src, "?FUN_%08x@@YAXXZ" % va
