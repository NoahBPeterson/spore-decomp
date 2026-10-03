# Cast(id): two ids return this+off (null-checked); anything else tail-calls base Cast(id).
PATTERN = 'mov eax, dword ptr [esp + N] ; cmp eax, A ; je +N ; cmp eax, A ; je +N ; mov dword ptr [esp + N], eax ; jmp EXT ; test ecx, ecx ; je +N ; lea eax, [ecx + N] ; ret N ; test ecx, ecx ; je +N ; lea eax, [ecx + N] ; ret N ; xor eax, eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct Base { void* BCast(unsigned id); };\n"
def emit(va, A, N):
    a, b = A[:2]
    off = lambda i: 4 if i == 0xeec58382 else 0xc
    oa, ob = off(a), off(b)
    return ("struct D_%08x : Base { void* F(unsigned id); };\n"
            "void* D_%08x::F(unsigned id) {\n"
            "  if (id != 0x%xu) {\n    if (id != 0x%xu) return BCast(id);\n    return this ? (char*)this + 0x%x : 0;\n  }\n"
            "  return this ? (char*)this + 0x%x : 0;\n}\n" % (va, va, a, b, ob, oa)), "?F@D_%08x@@QAEPAXI@Z" % va
