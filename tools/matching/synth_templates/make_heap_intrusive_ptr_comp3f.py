# make_heap over intrusive pointers (AddRef via vtable slot 0) with a 3-float comparator passed by value (/arch:SSE, no EH).
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; sub ebx, edi ; sar ebx, N ; cmp ebx, N ; jl +N ; lea esi, [ebx - N] ; sar esi, N ; inc esi ; jmp +N ; lea ecx, [ecx] ; movss xmm0, dword ptr [esp + N] ; sub esp, N ; mov eax, esp ; movss dword ptr [eax], xmm0 ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [eax + N], xmm0 ; movss xmm0, dword ptr [esp + N] ; dec esi ; push ecx ; mov ecx, dword ptr [edi + esi*N] ; movss dword ptr [eax + N], xmm0 ; mov eax, esp ; mov dword ptr [eax], ecx ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax] ; call edx ; push esi ; push ebx ; push esi ; push edi ; call EXT ; add esp, N ; test esi, esi ; jne +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP", "/arch:SSE"]
PRELUDE = """struct O { virtual void AddRef(); virtual void Release(); };
struct P { O* p; P(const P& o):p(o.p){ if(p) p->AddRef(); } ~P(){ if(p) p->Release(); } };
struct C { float a,b,c; C(const C& o):a(o.a),b(o.b),c(o.c){} };
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
