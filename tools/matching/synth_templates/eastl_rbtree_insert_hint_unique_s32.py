# (signed int key variant) eastl::rbtree<int key, ...>::DoInsertValue(iterator position, const value_type& value, true_type)
# (unique-key insert with a position hint, i.e. map/set::insert(hint, value)). EASTL source shape:
#   if position is neither begin-right (mAnchor.mpNodeRight) nor end (&mAnchor): itNext = ++position
#   (RBTreeIncrement); if pos.key < key && key < next.key -> DoInsertValueImpl(next or pos, value, bForceToLeft)
#   else if mnSize && rightmost.key < key -> DoInsertValueImpl(rightmost, value, false)
#   fallback: pair r = DoInsertValue(value, true_type()); return r.first;  -- a NAMED local is required
#   (returning the temporary's .first copies through the callee's eax instead of [esp+8]). The tag temp
#   reuses the dead value arg slot.
# Layout: compare +0, mAnchor +4 (right +4), mnSize +0x14; node value +0x10. `ret 0x10` = hidden ret,
# position, value, tag. Each instance gets its own tree class (callees are relocations).
PATTERN = 'sub esp, N ; push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esp + N] ; lea edx, [esi + N] ; push edi ; cmp ecx, eax ; je +N ; cmp ecx, edx ; je +N ; push ecx ; call EXT ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; mov edi, dword ptr [esp + N] ; add esp, N ; cmp dword ptr [edi + N], edx ; jge +N ; cmp edx, dword ptr [eax + N] ; jge +N ; cmp dword ptr [edi], N ; je +N ; mov edi, dword ptr [esp + N] ; push N ; push ecx ; push eax ; push edi ; mov ecx, esi ; call EXT ; mov eax, edi ; pop edi ; pop esi ; add esp, N ; ret N ; push N ; push ecx ; push edi ; mov edi, dword ptr [esp + N] ; push edi ; mov ecx, esi ; call EXT ; mov eax, edi ; pop edi ; pop esi ; add esp, N ; ret N ; cmp dword ptr [esi + N], N ; mov ecx, dword ptr [esp + N] ; je +N ; mov edx, dword ptr [eax + N] ; cmp edx, dword ptr [ecx] ; jge +N ; mov edi, dword ptr [esp + N] ; push N ; push ecx ; push eax ; push edi ; mov ecx, esi ; call EXT ; mov eax, edi ; pop edi ; pop esi ; add esp, N ; ret N ; mov byte ptr [esp + N], N ; mov eax, dword ptr [esp + N] ; push eax ; push ecx ; lea ecx, [esp + N] ; push ecx ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; pop edi ; mov dword ptr [eax], edx ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''
namespace eastl {
struct true_type {};
struct rbtree_node_base { rbtree_node_base* mpNodeRight; rbtree_node_base* mpNodeLeft; rbtree_node_base* mpNodeParent; char mColor; };
rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode);
struct rbtree_node_s32 : rbtree_node_base { int mValue; };
struct rbtree_iterator_s32 { rbtree_node_s32* mpNode;
    rbtree_iterator_s32(rbtree_node_s32* p) : mpNode(p) {}
    rbtree_iterator_s32(const rbtree_iterator_s32& x) : mpNode(x.mpNode) {}
    rbtree_iterator_s32& operator++() { mpNode = (rbtree_node_s32*)RBTreeIncrement(mpNode); return *this; } };
struct pair_iterator_bool { rbtree_iterator_s32 first; bool second; };
}
#define RBTREE_INSERT_HINT_UNIQUE(T) \
struct T { \
    typedef eastl::rbtree_node_s32 node_type; typedef eastl::rbtree_iterator_s32 iterator; \
    int mCompare; eastl::rbtree_node_base mAnchor; unsigned mnSize; \
    iterator DoInsertValueImpl(eastl::rbtree_node_base* pParent, const int& value, bool bForceToLeft); \
    eastl::pair_iterator_bool DoInsertValue(const int& value, eastl::true_type); \
    iterator DoInsertValue(iterator position, const int& value, eastl::true_type); \
}; \
T::iterator T::DoInsertValue(iterator position, const int& value, eastl::true_type) \
{ \
    if((position.mpNode != mAnchor.mpNodeRight) && (position.mpNode != &mAnchor)) { \
        iterator itNext(position); \
        ++itNext; \
        const bool bPositionLessThanValue = position.mpNode->mValue < value; \
        if(bPositionLessThanValue) { \
            const bool bValueLessThanNext = value < itNext.mpNode->mValue; \
            if(bValueLessThanNext) { \
                if(position.mpNode->mpNodeRight) \
                    return DoInsertValueImpl(itNext.mpNode, value, true); \
                return DoInsertValueImpl(position.mpNode, value, false); \
            } \
        } \
        { eastl::pair_iterator_bool r = DoInsertValue(value, eastl::true_type()); return r.first; } \
    } \
    if(mnSize && (((node_type*)mAnchor.mpNodeRight)->mValue < value)) \
        return DoInsertValueImpl(mAnchor.mpNodeRight, value, false); \
    { eastl::pair_iterator_bool r = DoInsertValue(value, eastl::true_type()); return r.first; } \
}
'''

def emit(va, A, N):
    t = "Tree_%08x" % va
    return ("RBTREE_INSERT_HINT_UNIQUE(%s)" % t,
            "?DoInsertValue@%s@@QAE?AUrbtree_iterator_s32@eastl@@U23@ABHUtrue_type@3@@Z" % t)
