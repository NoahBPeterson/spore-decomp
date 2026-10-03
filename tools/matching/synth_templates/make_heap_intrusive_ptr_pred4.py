# make_heap over intrusive pointers (AddRef via vtable slot 0) with a 4-byte by-value predicate (/O2, no SSE).
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; sub ebx, edi ; sar ebx, N ; cmp ebx, N ; jl +N ; lea esi, [ebx - N] ; sar esi, N ; inc esi ; jmp +N ; lea ecx, [ecx] ; mov eax, dword ptr [esp + N] ; push eax ; dec esi ; push ecx ; mov ecx, dword ptr [edi + esi*N] ; mov eax, esp ; mov dword ptr [eax], ecx ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx] ; call eax ; push esi ; push ebx ; push esi ; push edi ; call EXT ; add esp, N ; test esi, esi ; jne +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = """struct O { virtual void AddRef(); virtual void Release(); };
struct P { O* p; P(const P& o):p(o.p){ if(p) p->AddRef(); } ~P(){ if(p) p->Release(); } };
struct C { int x; };
void adj(P* f, int i, int n, int j, P v, C c);
"""
def emit(va, A, N):
    src = ("void FUN_%08x(P* first, P* last, C comp) {\n"
           "  int len = last - first;\n"
           "  if (len >= 2) {\n"
           "    int parent = ((len - 2) >> 1) + 1;\n"
           "    do {\n"
           "      --parent;\n"
           "      adj(first, parent, len, parent, first[parent], comp);\n"
           "    } while (parent != 0);\n"
           "  }\n}") % va
    return src, "?FUN_%08x@@YAXPAUP@@0UC@@@Z" % va
