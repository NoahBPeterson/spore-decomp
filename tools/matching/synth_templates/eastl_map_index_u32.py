# NEAR-MATCH only (15 diff bytes: the 'second=0' store schedules 2 instrs earlier than original; result read via slot ok).
# eastl::map<uint32_t, uint32_t>::operator[](const key&): inline lower_bound, then
# DoInsertValue(hint, value_type(k,0), true_type()) out of line (hidden ret ptr, iterator by value).
PATTERN = 'mov eax, dword ptr [ecx + N] ; sub esp, N ; push ebp ; push esi ; lea esi, [ecx + N] ; push edi ; mov edi, dword ptr [esp + N] ; mov edx, esi ; test eax, eax ; je +N ; mov ebp, dword ptr [edi] ; cmp dword ptr [eax + N], ebp ; jb +N ; mov edx, eax ; mov eax, dword ptr [eax + N] ; jmp +N ; mov eax, dword ptr [eax] ; test eax, eax ; jne +N ; cmp edx, esi ; je +N ; mov eax, dword ptr [edi] ; cmp eax, dword ptr [edx + N] ; jae +N ; mov eax, dword ptr [edi] ; mov dword ptr [esp + N], eax ; mov byte ptr [esp + N], N ; mov eax, dword ptr [esp + N] ; push eax ; lea eax, [esp + N] ; push eax ; push ecx ; mov eax, esp ; mov dword ptr [eax], edx ; lea edx, [esp + N] ; push edx ; mov dword ptr [esp + N], N ; call EXT ; mov eax, dword ptr [esp + N] ; add eax, N ; pop edi ; pop esi ; pop ebp ; add esp, N ; ret N ; pop edi ; pop esi ; lea eax, [edx + N] ; pop ebp ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''
namespace eastl {
struct true_type {};
struct nb { nb* r; nb* l; nb* p; char c; };
struct nu : nb { unsigned key; unsigned val; };
struct it { nu* n; it(nu* x) : n(x) {} it(const it& o) : n(o.n) {} };
struct vt { unsigned first; unsigned second; vt(unsigned a, unsigned b) : first(a), second(b) {} };
}
#define MAP_INDEX(T) \
struct T { \
    int cmp; eastl::nb anchor; unsigned sz; \
    eastl::it DoInsertValue(eastl::it pos, const eastl::vt& v, eastl::true_type); \
    unsigned& FUN(const unsigned& k); \
}; \
unsigned& T::FUN(const unsigned& k) { \
    eastl::nb* pend = &anchor; \
    eastl::nb* cur = anchor.p; \
    eastl::nb* best = pend; \
    while (cur) { \
        if (!(((eastl::nu*)cur)->key < k)) { best = cur; cur = cur->l; } else cur = cur->r; \
    } \
    eastl::it i((eastl::nu*)best); \
    if (i.n == (eastl::nu*)pend || k < i.n->key) { \
        eastl::it r(DoInsertValue(i, eastl::vt(k, 0), eastl::true_type())); \
        i = r; \
    } \
    return i.n->val; \
}
'''
def emit(va, A, N):
    t = "Map_%08x" % va
    src = "MAP_INDEX(%s)" % t
    src = src.replace("FUN", "FUN_%08x" % va) if False else src
    return ("#define FUN FUN_%08x\n%s\n#undef FUN\n" % (va, src),
            "?FUN_%08x@%s@@QAEAAIABI@Z" % (va, t))
