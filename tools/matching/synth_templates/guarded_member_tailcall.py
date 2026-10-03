# int f() { return m_ptr ? m_ptr->callee() : 0; }  -> mov ecx,[ecx+off]; test; je; jmp callee; xor eax,eax; ret
PATTERN = "mov ecx, dword ptr [ecx + N] ; test ecx, ecx ; je +N ; jmp EXT ; xor eax, eax ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0]
    src = ("struct T_%08x { int callee_%08x(); };\n"
           "struct O_%08x { char pad[%d]; T_%08x* p; int FUN_%08x(); };\n"
           "int O_%08x::FUN_%08x() { if (p) return p->callee_%08x(); return 0; }"
           % (va, va, va, off, va, va, va, va, va))
    return src, "?FUN_%08x@O_%08x@@QAEHXZ" % (va, va)
