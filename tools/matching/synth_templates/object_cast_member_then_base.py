# Object::Cast(id): returns this for own id, else tries member at +0x34 Cast(id), else base Cast(id).
PATTERN = 'push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov esi, ecx ; cmp edi, A ; jne +N ; pop edi ; mov eax, esi ; pop esi ; ret N ; push edi ; lea ecx, [esi + N] ; call EXT ; test eax, eax ; jne +N ; push edi ; mov ecx, esi ; call EXT ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Sub { void* SCast(int id); };
struct Base { void* BCast(int id); };
"""
def emit(va, A, N):
    return ("struct D_%08x : Base { int pad[13]; Sub sub; void* F(int id); };\n"
            "void* D_%08x::F(int id) {\n"
            "  if (id == 0x%x) return this;\n"
            "  void* p = sub.SCast(id);\n"
            "  if (!p) p = BCast(id);\n"
            "  return p;\n}" % (va, va, A[0])), "?F@D_%08x@@QAEPAXH@Z" % va
