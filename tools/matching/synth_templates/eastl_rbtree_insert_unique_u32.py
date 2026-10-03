# eastl::rbtree<uint32_t key, ...>::DoInsertValue(const value_type& value, true_type)  (unique-key insert,
# i.e. map/set::insert returning pair<iterator,bool>). Reproduced from EASTL's source shape:
#   walk from mAnchor.mpNodeParent comparing (unsigned) key < node key (setb), RBTreeDecrement on the
#   lower bound unless it is mAnchor.mpNodeLeft (begin), then DoInsertValueImpl(pParent, value, false).
# EASTL node layout: right +0, left +4, parent +8, color +0xc, value +0x10; tree: compare +0, mAnchor +4.
# The true_type tag argument is what makes the epilogue `ret 0xc` (hidden return ptr, value, tag).
# Each instance gets its own tree class (callee DoInsertValueImpl / RBTreeDecrement are relocations).
PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; push edi ; lea eax, [esi + N] ; mov dl, N ; test ecx, ecx ; je +N ; mov edi, dword ptr [ebp] ; cmp edi, dword ptr [ecx + N] ; mov eax, ecx ; setb dl ; test dl, dl ; je +N ; mov ecx, dword ptr [ecx + N] ; jmp +N ; mov ecx, dword ptr [ecx] ; test ecx, ecx ; jne +N ; mov edi, eax ; test dl, dl ; je +N ; cmp eax, dword ptr [esi + N] ; je +N ; push eax ; call EXT ; add esp, N ; mov edx, dword ptr [eax + N] ; cmp edx, dword ptr [ebp] ; jae +N ; push N ; push ebp ; push edi ; jmp +N ; push N ; push ebp ; push eax ; lea eax, [esp + N] ; push eax ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; pop edi ; pop esi ; mov dword ptr [eax], ecx ; mov byte ptr [eax + N], N ; pop ebp ; ret N ; mov ecx, dword ptr [esp + N] ; pop edi ; pop esi ; mov dword ptr [ecx], eax ; mov byte ptr [ecx + N], N ; mov eax, ecx ; pop ebp ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''
namespace eastl {
struct true_type {};
struct rbtree_node_base { rbtree_node_base* mpNodeRight; rbtree_node_base* mpNodeLeft; rbtree_node_base* mpNodeParent; char mColor; };
rbtree_node_base* RBTreeDecrement(const rbtree_node_base* pNode);
struct rbtree_node_u32 : rbtree_node_base { unsigned int mValue; };
struct rbtree_iterator_u32 { rbtree_node_u32* mpNode; rbtree_iterator_u32(rbtree_node_u32* p) : mpNode(p) {} };
struct pair_iterator_bool { rbtree_iterator_u32 first; bool second;
    pair_iterator_bool(const rbtree_iterator_u32& a, bool b) : first(a), second(b) {} };
}
#define RBTREE_INSERT_UNIQUE(T) \
struct T { \
    typedef eastl::rbtree_node_u32 node_type; typedef eastl::rbtree_iterator_u32 iterator; \
    int mCompare; eastl::rbtree_node_base mAnchor; unsigned mnSize; \
    iterator DoInsertValueImpl(eastl::rbtree_node_base* pParent, const unsigned int& value, bool bForceToLeft); \
    eastl::pair_iterator_bool DoInsertValue(const unsigned int& value, eastl::true_type); \
}; \
eastl::pair_iterator_bool T::DoInsertValue(const unsigned int& value, eastl::true_type) \
{ \
    node_type* pCurrent    = (node_type*)mAnchor.mpNodeParent; \
    node_type* pLowerBound = (node_type*)&mAnchor; \
    node_type* pParent; \
    bool bValueLessThanNode = true; \
    while(pCurrent) { \
        bValueLessThanNode = value < pCurrent->mValue; \
        pLowerBound = pCurrent; \
        if(bValueLessThanNode) pCurrent = (node_type*)pCurrent->mpNodeLeft; \
        else pCurrent = (node_type*)pCurrent->mpNodeRight; \
    } \
    pParent = pLowerBound; \
    if(bValueLessThanNode) { \
        if(pLowerBound != (node_type*)mAnchor.mpNodeLeft) \
            pLowerBound = (node_type*)eastl::RBTreeDecrement(pLowerBound); \
        else { \
            const iterator itResult(DoInsertValueImpl(pLowerBound, value, false)); \
            return eastl::pair_iterator_bool(itResult, true); \
        } \
    } \
    if(pLowerBound->mValue < value) { \
        const iterator itResult(DoInsertValueImpl(pParent, value, false)); \
        return eastl::pair_iterator_bool(itResult, true); \
    } \
    return eastl::pair_iterator_bool(iterator(pLowerBound), false); \
}
'''

def emit(va, A, N):
    t = "Tree_%08x" % va
    return ("RBTREE_INSERT_UNIQUE(%s)" % t,
            "?DoInsertValue@%s@@QAE?AUpair_iterator_bool@eastl@@ABIUtrue_type@3@@Z" % t)
