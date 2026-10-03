# /Od: global vector-like {begin,end}; empty element-dtor loop then member call on the global.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov eax, dword ptr [A] ; mov dword ptr [ebp - N], eax ; jmp +N ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; cmp edx, dword ptr [A] ; jae +N ; jmp +N ; mov ecx, A ; call EXT ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    sz = N[3]
    a = A[0]
    src = ("struct E_%08x { char d[%d]; };\n"
           "struct V_%08x { E_%08x* b; E_%08x* e; void Free(); };\n"
           "V_%08x g_%08x;\n"
           "void FUN_%08x() {\n"
           "  E_%08x* p; char pad[%d];\n  for (p = g_%08x.b; p < g_%08x.e; ++p) {}\n"
           "  g_%08x.Free();\n}" % ((va, sz) + (va,)*3 + (va, a, va, va, N[0]-8, a, a, a)))
    return src, "?FUN_%08x@@YAXXZ" % va
