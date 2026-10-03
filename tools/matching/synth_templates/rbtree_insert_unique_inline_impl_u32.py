# rbtree<uint32_t>::DoInsertValue(const value_type&, true_type) with DoInsertValueImpl inlined:
# lower-bound walk, RBTreeDecrement, then node = DoCreateNode(value); RBTreeInsert(node, parent, &anchor, side);
# ++mnSize; return pair(iterator(node), true). side = (parent==&anchor || value<parent->key) ? 0 : 1.
# Layout: compare +0, anchor +4 (right +4, left +8, parent +0xc), size +0x14; node right +0, left +4, key +0x10.
PATTERN = 'push ecx ; push ebx ; push ebp ; push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; lea ebx, [esi + N] ; push edi ; mov edi, ebx ; mov cl, N ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; jmp +N ; lea ecx, [ecx] ; cmp edx, dword ptr [eax + N] ; mov edi, eax ; setb cl ; test cl, cl ; je +N ; mov eax, dword ptr [eax + N] ; jmp +N ; mov eax, dword ptr [eax] ; test eax, eax ; jne +N ; mov ebp, edi ; mov dword ptr [esp + N], ebp ; test cl, cl ; je +N ; cmp edi, dword ptr [esi + N] ; je +N ; push edi ; call EXT ; add esp, N ; mov edi, eax ; mov eax, dword ptr [esp + N] ; mov eax, dword ptr [eax] ; cmp dword ptr [edi + N], eax ; jae +N ; cmp ebp, ebx ; je +N ; cmp eax, dword ptr [ebp + N] ; jb +N ; mov ebp, N ; jmp +N ; cmp edi, ebx ; je +N ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [edx] ; mov dword ptr [esp + N], N ; cmp eax, dword ptr [edi + N] ; jae +N ; mov dword ptr [esp + N], N ; mov ecx, dword ptr [esp + N] ; push ecx ; mov ecx, esi ; call EXT ; mov edx, dword ptr [esp + N] ; push edx ; push ebx ; mov ebp, eax ; push edi ; push ebp ; call EXT ; mov eax, dword ptr [esp + N] ; add esp, N ; inc dword ptr [esi + N] ; pop edi ; pop esi ; mov dword ptr [eax], ebp ; pop ebp ; mov byte ptr [eax + N], N ; pop ebx ; pop ecx ; ret N ; xor ebp, ebp ; mov ecx, dword ptr [esp + N] ; push ecx ; mov ecx, esi ; call EXT ; mov edx, dword ptr [esp + N] ; push ebp ; push ebx ; mov edi, eax ; push edx ; push edi ; call EXT ; mov eax, dword ptr [esp + N] ; add esp, N ; inc dword ptr [esi + N] ; mov dword ptr [eax], edi ; pop edi ; pop esi ; pop ebp ; mov byte ptr [eax + N], N ; pop ebx ; pop ecx ; ret N ; mov eax, dword ptr [esp + N] ; mov dword ptr [eax], edi ; pop edi ; pop esi ; pop ebp ; mov byte ptr [eax + N], N ; pop ebx ; pop ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''
namespace eastl {
struct true_type {};
struct nb { nb* mpNodeRight; nb* mpNodeLeft; nb* mpNodeParent; char mColor; };
nb* RBTreeDecrement(const nb* pNode);
void RBTreeInsert(nb* pNode, nb* pParent, nb* pAnchor, int side);
struct node_u32 : nb { unsigned int mValue; };
struct iter_u32 { node_u32* mpNode; iter_u32(node_u32* p) : mpNode(p) {} };
struct pair_ib { iter_u32 first; bool second; pair_ib(const iter_u32& a, bool b) : first(a), second(b) {} };
}
#define RBT(T) \
struct T { \
    int mCompare; eastl::nb mAnchor; unsigned mnSize; \
    eastl::node_u32* DoCreateNode(const unsigned int& v); \
    eastl::iter_u32 Impl(eastl::nb* pParent, const unsigned int& value, bool bForceToLeft) { \
        eastl::node_u32* pNodeParent = (eastl::node_u32*)pParent; \
        int side = (bForceToLeft || pNodeParent == (eastl::node_u32*)&mAnchor || value < pNodeParent->mValue) ? 0 : 1; \
        eastl::node_u32* pNew = DoCreateNode(value); \
        eastl::RBTreeInsert(pNew, pParent, &mAnchor, side); \
        ++mnSize; \
        return eastl::iter_u32(pNew); \
    } \
    eastl::pair_ib DoInsertValue(const unsigned int& value, eastl::true_type); \
}; \
eastl::pair_ib T::DoInsertValue(const unsigned int& value, eastl::true_type) \
{ \
    eastl::node_u32* pCurrent = (eastl::node_u32*)mAnchor.mpNodeParent; \
    eastl::node_u32* pLowerBound = (eastl::node_u32*)&mAnchor; \
    eastl::node_u32* pParent; \
    bool less = true; \
    while(pCurrent) { \
        less = value < pCurrent->mValue; \
        pLowerBound = pCurrent; \
        if(less) pCurrent = (eastl::node_u32*)pCurrent->mpNodeLeft; \
        else pCurrent = (eastl::node_u32*)pCurrent->mpNodeRight; \
    } \
    pParent = pLowerBound; \
    if(less) { \
        if(pLowerBound != (eastl::node_u32*)mAnchor.mpNodeLeft) \
            pLowerBound = (eastl::node_u32*)eastl::RBTreeDecrement(pLowerBound); \
        else { \
            const eastl::iter_u32 it(Impl(pLowerBound, value, false)); \
            return eastl::pair_ib(it, true); \
        } \
    } \
    if(pLowerBound->mValue < value) { \
        const eastl::iter_u32 it(Impl(pParent, value, false)); \
        return eastl::pair_ib(it, true); \
    } \
    return eastl::pair_ib(eastl::iter_u32(pLowerBound), false); \
}
'''
def emit(va, A, N):
    t = "Tree_%08x" % va
    return ("RBT(%s)" % t, "?DoInsertValue@%s@@QAE?AUpair_ib@eastl@@ABIUtrue_type@3@@Z" % t)
