# Cast(id) on a secondary-base subobject (this = base at +off inside derived D):
# ids ee3f516e/2f009dd0 return this if the adjusted derived ptr is non-null; other ids return the derived ptr.
PATTERN = 'mov eax, dword ptr [esp + N] ; cmp eax, A ; je +N ; cmp eax, A ; je +N ; cmp eax, A ; je +N ; xor eax, eax ; ret N ; lea eax, [ecx - N] ; ret N ; lea eax, [ecx - N] ; neg eax ; sbb eax, eax ; and eax, ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    a, b, c = A[:3]
    kind = ''.join('X' if i in (0xee3f516e, 0x2f009dd0) else 'Y' for i in A[:3])
    off = N[2]
    nc = "dd() ? this : 0"
    if kind == "XXY":
        body = ("  if (id == 0x%xu || id == 0x%xu) return %s;\n  if (id != 0x%xu) return 0;\n  return dd();\n" % (a, b, nc, c))
    elif kind == "XYX":
        body = ("  if (id == 0x%xu || id != 0x%xu && id == 0x%xu) return %s;\n  if (id == 0x%xu) return dd();\n  return 0;\n" % (a, b, c, nc, b))
    else:
        body = ("  if (id != 0x%xu) { if (id == 0x%xu || id == 0x%xu) return dd(); return 0; }\n  return %s;\n" % (a, b, c, nc))
    return ("struct D_%08x { int pad[%d]; struct S {\n  D_%08x* dd() { return (D_%08x*)((char*)this - %d); }\n"
            "  void* F(unsigned id) {\n%s  } } s; };\n"
            "void* (D_%08x::S::*p_%08x)(unsigned) = &D_%08x::S::F;"
            % (va, off // 4, va, va, off, body, va, va, va)), "?F@S@D_%08x@@QAEPAXI@Z" % va
