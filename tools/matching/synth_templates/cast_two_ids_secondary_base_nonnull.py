# Cast(id) on a secondary-base subobject: two ids -> this if adjusted ptr non-null, else 0.
PATTERN = 'mov eax, dword ptr [esp + N] ; cmp eax, A ; je +N ; cmp eax, A ; je +N ; xor eax, eax ; ret N ; lea eax, [ecx - N] ; neg eax ; sbb eax, eax ; and eax, ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    a, b = A[:2]
    off = N[2]
    return ("struct D_%08x { int pad[%d]; struct S {\n  D_%08x* dd() { return (D_%08x*)((char*)this - %d); }\n"
            "  void* F(unsigned id) {\n  if (id == 0x%xu || id == 0x%xu) return dd() ? this : 0;\n  return 0;\n  } } s; };\n"
            "void* (D_%08x::S::*p_%08x)(unsigned) = &D_%08x::S::F;"
            % (va, off // 4, va, va, off, a, b, va, va, va)), "?F@S@D_%08x@@QAEPAXI@Z" % va
