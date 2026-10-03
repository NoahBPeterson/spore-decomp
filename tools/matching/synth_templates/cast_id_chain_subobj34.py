# Cast(id): 0x142db2a -> this?this+0x504:0; second id -> this; else chain of three callee Casts (sub at +0x34, this, sub at +0x34).
PATTERN = 'push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov esi, ecx ; cmp edi, A ; je +N ; cmp edi, A ; je +N ; push ebx ; lea ebx, [esi + N] ; push edi ; mov ecx, ebx ; call EXT ; test eax, eax ; jne +N ; push edi ; mov ecx, esi ; call EXT ; test eax, eax ; jne +N ; push edi ; mov ecx, ebx ; call EXT ; pop ebx ; pop edi ; pop esi ; ret N ; pop edi ; mov eax, esi ; pop esi ; ret N ; test esi, esi ; je +N ; pop edi ; lea eax, [esi + N] ; pop esi ; ret N ; pop edi ; xor eax, eax ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    a, b = A[:2]
    return ("struct S_%08x { void* P(unsigned); void* Q(unsigned); };\n"
            "struct C_%08x { int pad[13]; S_%08x s; int pad2[%d]; void* B(unsigned);\n"
            "  void* F(unsigned id) {\n"
            "    if (id != 0x%xu) {\n"
            "      if (id != 0x%xu) { void* r = s.P(id); if (!r) r = B(id); if (!r) r = s.Q(id); return r; }\n"
            "      return this;\n    }\n"
            "    return this ? (char*)this + 0x504 : 0;\n"
            "  } };\n"
            "void* (C_%08x::*p_%08x)(unsigned) = &C_%08x::F;"
            % (va, va, va, 1, a, b, va, va, va)), "?F@C_%08x@@QAEPAXI@Z" % va
