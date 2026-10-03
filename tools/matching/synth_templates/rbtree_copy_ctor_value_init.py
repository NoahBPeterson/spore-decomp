# EASTL rbtree copy constructor (anchor value-initialized, reset(), DoCopySubtree, min/max child, size copy).
# Key lever: the member init `a()` (value-init) keeps the first-phase zero stores that DSE would otherwise drop.
PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; xor eax, eax ; push esi ; push edi ; mov edi, ecx ; mov dword ptr [edi + N], eax ; lea esi, [edi + N] ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], eax ; mov dword ptr [esi], esi ; mov dword ptr [edi + N], esi ; mov dword ptr [edi + N], eax ; mov byte ptr [edi + N], al ; mov dword ptr [edi + N], eax ; mov eax, dword ptr [ebp + N] ; test eax, eax ; je +N ; push esi ; push eax ; call EXT ; mov ecx, eax ; mov dword ptr [edi + N], eax ; mov edx, dword ptr [ecx] ; test edx, edx ; je +N ; mov edi, edi ; mov ecx, edx ; mov edx, dword ptr [ecx] ; test edx, edx ; jne +N ; mov dword ptr [esi], ecx ; mov ecx, eax ; mov eax, dword ptr [ecx + N] ; test eax, eax ; je +N ; mov ecx, eax ; mov eax, dword ptr [ecx + N] ; test eax, eax ; jne +N ; mov dword ptr [edi + N], ecx ; mov eax, dword ptr [ebp + N] ; mov dword ptr [edi + N], eax ; mov eax, edi ; pop edi ; pop esi ; pop ebp ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct N { N* l; N* r; };
inline N* Min(N* n) { while (n->l) n = n->l; return n; }
inline N* Max(N* n) { while (n->r) n = n->r; return n; }
struct Anc2 { N* right; N* left; N* parent; int color; };
"""
def emit(va, A, N):
    src = ("struct T_%08x {\n"
           "  int pad; Anc2 a; unsigned size;\n"
           "  N* Copy(N* n, Anc2* p);\n"
           "  T_%08x(const T_%08x& o);\n"
           "};\n"
           "T_%08x::T_%08x(const T_%08x& o) : a() {\n"
           "  a.right = (N*)&a; a.left = (N*)&a; a.parent = 0; *(unsigned char*)&a.color = 0; size = 0;\n"
           "  if (o.a.parent) {\n"
           "    a.parent = Copy(o.a.parent, &a);\n"
           "    a.right = Min(a.parent);\n"
           "    a.left = Max(a.parent);\n"
           "    size = o.size; }\n"
           "}\n") % ((va,) * 6)
    return src, "??0T_%08x@@QAE@ABU0@@Z" % va
