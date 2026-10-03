# Cast(id): first id -> null, second id -> this, third id -> this, anything else -> null (as setne/dec/and).
PATTERN = 'mov edx, dword ptr [esp + N] ; mov eax, ecx ; cmp edx, A ; je +N ; cmp edx, A ; je +N ; xor ecx, ecx ; cmp edx, A ; setne cl ; dec ecx ; and eax, ecx ; ret N ; xor eax, eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    a, b, c = A[:3]
    return ("struct C_%08x { void* F(unsigned id) {\n"
            "  if (id != 0x%xu) { if (id == 0x%xu) return this; return id == 0x%xu ? this : 0; }\n"
            "  return 0;\n  } };\n"
            "void* (C_%08x::*p_%08x)(unsigned) = &C_%08x::F;" % (va, a, b, c, va, va, va)), "?F@C_%08x@@QAEPAXI@Z" % va
