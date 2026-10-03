# rbtree<Key3 (a,b,c compared a,c,b)>::DoInsertValue(const value&, true_type): unique insert walk, RBTreeDecrement,
# out-of-line DoInsertValueImpl for the begin() case, inline create-node + RBTreeInsert + ++size otherwise.
PATTERN = 'push ebx ; mov ebx, ecx ; mov ecx, dword ptr [ebx + N] ; push ebp ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; lea eax, [ebx + N] ; mov dl, N ; test ecx, ecx ; je +N ; mov edi, dword ptr [esi] ; mov eax, dword ptr [ecx + N] ; cmp edi, eax ; jne +N ; mov eax, dword ptr [esi + N] ; mov edx, dword ptr [ecx + N] ; cmp eax, edx ; jne +N ; mov eax, dword ptr [esi + N] ; cmp eax, dword ptr [ecx + N] ; setb dl ; mov eax, ecx ; test dl, dl ; je +N ; mov ecx, dword ptr [ecx + N] ; jmp +N ; mov ecx, dword ptr [ecx] ; test ecx, ecx ; jne +N ; mov ebp, eax ; test dl, dl ; je +N ; cmp eax, dword ptr [ebx + N] ; je +N ; push eax ; call EXT ; add esp, N ; mov ecx, dword ptr [eax + N] ; mov edi, dword ptr [esi] ; cmp ecx, edi ; jne +N ; mov ecx, dword ptr [eax + N] ; mov edx, dword ptr [esi + N] ; cmp ecx, edx ; jne +N ; mov ecx, dword ptr [eax + N] ; cmp ecx, dword ptr [esi + N] ; setb cl ; test cl, cl ; je +N ; lea eax, [ebx + N] ; cmp ebp, eax ; je +N ; mov eax, dword ptr [ebp + N] ; cmp edi, eax ; jne +N ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [ebp + N] ; cmp eax, ecx ; jne +N ; mov edx, dword ptr [esi + N] ; cmp edx, dword ptr [ebp + N] ; setb al ; test al, al ; jne +N ; mov edi, N ; jmp +N ; push N ; push esi ; push eax ; lea ecx, [esp + N] ; push ecx ; mov ecx, ebx ; call EXT ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; pop edi ; pop esi ; pop ebp ; mov dword ptr [eax], edx ; mov byte ptr [eax + N], N ; pop ebx ; ret N ; xor edi, edi ; push esi ; mov ecx, ebx ; call EXT ; mov esi, eax ; push edi ; lea eax, [ebx + N] ; push eax ; push ebp ; push esi ; call EXT ; mov eax, dword ptr [esp + N] ; add esp, N ; inc dword ptr [ebx + N] ; pop edi ; mov dword ptr [eax], esi ; pop esi ; pop ebp ; mov byte ptr [eax + N], N ; pop ebx ; ret N ; mov ecx, dword ptr [esp + N] ; pop edi ; pop esi ; pop ebp ; mov dword ptr [ecx], eax ; mov byte ptr [ecx + N], N ; mov eax, ecx ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''
namespace eastl {
struct true_type {};
struct nb { nb* r; nb* l; nb* p; char c; };
nb* RBTreeDecrement(const nb* n);
void __cdecl RBTreeInsert(nb* n, nb* parent, nb* anchor, int side);
struct K3 { unsigned a, b, c; };
struct node3 : nb { K3 v; };
struct iter3 { node3* n; iter3(node3* p) : n(p) {} };
struct pair_ib { iter3 first; bool second; pair_ib(const iter3& a, bool b) : first(a), second(b) {} };
inline bool Less(const K3& x, const K3& y) { if (x.a != y.a) return x.a < y.a; if (x.c != y.c) return x.c < y.c; return x.b < y.b; }
}
#define RBT3(T) \
struct T { \
    int cmp; eastl::nb anchor; unsigned size; \
    eastl::node3* Create(const eastl::K3& v); \
    eastl::iter3 Impl(eastl::nb* parent, const eastl::K3& v, bool left); \
    eastl::pair_ib Ins(const eastl::K3& v, eastl::true_type); \
}; \
eastl::pair_ib T::Ins(const eastl::K3& value, eastl::true_type) \
{ \
    using namespace eastl; \
    node3* cur = (node3*)anchor.p; \
    node3* lb = (node3*)&anchor; \
    bool lt = true; \
    while(cur) { lt = Less(value, cur->v); lb = cur; if(lt) cur = (node3*)cur->l; else cur = (node3*)cur->r; } \
    node3* parent = lb; \
    if(lt) { \
        if(lb != (node3*)anchor.l) lb = (node3*)RBTreeDecrement(lb); \
        else { const iter3 it(Impl(lb, value, false)); return pair_ib(it, true); } \
    } \
    if(Less(lb->v, value)) { \
        int side = (parent == (node3*)&anchor || Less(value, parent->v)) ? 0 : 1; \
        node3* nn = Create(value); \
        RBTreeInsert(nn, parent, &anchor, side); \
        ++size; \
        return pair_ib(iter3(nn), true); \
    } \
    return pair_ib(iter3(lb), false); \
}
'''
def emit(va, A, N):
    t = "Tree_%08x" % va
    return ("RBT3(%s)" % t, "?Ins@%s@@QAE?AUpair_ib@eastl@@ABUK3@3@Utrue_type@3@@Z" % t)
