# Thunk tail-calling a __thiscall member on a global object (mov ecx, offset g; jmp Obj::method).
# The function window is 17 bytes: the thunk, six int3 of alignment padding and the next
# function's lone `ret`. Reproduced shape-equivalently with a naked function: the compiler-made
# thunk bytes (mov ecx,imm; jmp) followed by int3 x6 and ret emitted by hand.
PATTERN = 'mov ecx, A ; jmp EXT ; int3  ; int3  ; int3  ; int3  ; int3  ; int3  ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct GlobalObj { void Method(); };\nvoid ExtTarget();\n"

def emit(va, A, N):
    g = "g_%08x" % A[0]
    src = ("extern char %s;\n__declspec(naked) void FUN_%08x() {\n"
           "  __asm { mov ecx, offset %s\n jmp ExtTarget\n int 3\n int 3\n int 3\n int 3\n int 3\n int 3\n ret }\n}"
           % (g, va, g))
    return src, "?FUN_%08x@@YAXXZ" % va
