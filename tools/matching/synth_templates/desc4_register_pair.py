# cdecl void f(Obj* o): two stack descriptors {4 fn ptrs, 2 bool bytes}, each passed to thiscall o->reg(&d, a, b)
import re
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; push N ; push N ; lea eax, [esp + N] ; push eax ; mov ecx, esi ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov byte ptr [esp + N], N ; mov byte ptr [esp + N], N ; call EXT ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; mov ecx, esi ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov byte ptr [esp + N], N ; mov byte ptr [esp + N], N ; call EXT ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Desc { void* f0; void* f1; void* f2; void* f3; bool b0; bool b1; int pad; };
struct Obj { void reg(Desc* d, int a, int b); };
"""
def emit(va, A, N):
    decl = "".join("void f_%08x();\n" % a for a in sorted(set(A)))
    def blk(fs, b0, b1, x, y):
        return ("  d.f0 = (void*)f_%08x; d.f1 = (void*)f_%08x; d.f2 = (void*)f_%08x; d.f3 = (void*)f_%08x;\n"
                "  d.b0 = %s; d.b1 = %s; o->reg(&d, %d, %d);\n" % (fs + (("true" if b0 else "false"), ("true" if b1 else "false"), x, y)))
    src = (decl + "void FUN_%08x(Obj* o) {\n  Desc d;\n" % va
           + blk(tuple(A[0:4]), N[10], N[12], N[3], N[2])
           + blk(tuple(A[4:8]), N[21], N[23], N[14], N[13]) + "}")
    return src, "?FUN_%08x@@YAXPAUObj@@@Z" % va
