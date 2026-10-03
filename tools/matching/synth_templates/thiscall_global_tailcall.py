# Thunk that tail-calls a __thiscall member function on a file-scope global object:
#   mov ecx, offset g; jmp Obj::method
# /O2 turns "void f() { g.method(); }" into a tail jump. Odd global addresses (e.g. 0x167bc4d)
# indicate 1-byte (empty) objects such as allocator/tag singletons; the object type is opaque here.
# The callee is a single extern member (relocation masked), globals are extern declarations.
PATTERN = "mov ecx, A ; jmp EXT"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct GlobalObj { void Method(); };\n"

def emit(va, A, N):
    g = "g_%08x" % A[0]
    src = "extern GlobalObj %s;\nvoid FUN_%08x() { %s.Method(); }" % (g, va, g)
    return src, "?FUN_%08x@@YAXXZ" % va
