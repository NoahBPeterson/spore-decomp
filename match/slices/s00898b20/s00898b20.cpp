// Slice s00898b20: eastl::rbtree<EA::Text::Rectangle, ...>::erase (dev public
// 0x010e0de0 -> retail 0x00898b20).  This is EA::Text::RectSet::erase from the
// sibling slices s0089b520 / s008eebb0 (EATextTypesetter): a node header of
// right/left/parent/colour, a sentinel anchor at tree+4, and a fixed node pool
// whose free-list head sits at +0x18.  The `erase(const_iterator)` overload
// returns the next iterator (in eax).
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int u32;

struct RectNode {
    RectNode* mpRight;                  // +0x00 (a freed node keeps its next-free link here)
    RectNode* mpLeft;                   // +0x04
    RectNode* mpParent;                 // +0x08
    int       mColor;                   // +0x0c
};

// eastl::rbtree<Rectangle,...>: allocator, sentinel anchor, size, node pool.
struct RectSet {
    void*     mpAllocator;              // +0x00
    RectNode  mAnchor;                  // +0x04  sentinel, leftmost at +0x08
    u32       mnSize;                   // +0x14
    RectNode* mpFreeList;               // +0x18
    u32       mPad1c;                   // +0x1c
    char*     mpNodeBegin;              // +0x20  fixed pool range
    char*     mpNodeEnd;                // +0x24

    void erase(RectNode* pos, u32* result);
};

RectNode* __cdecl RBTreeIncrement(RectNode* p);                       // 0x00921580
void __cdecl RBTree_RemoveNode(void* anchor, RectNode* p, void* allocator);   // 0x00921880
void __cdecl operator delete(void* p);                                // 0x00f47380

// @ 0x00898b20
// Unlinks one node, reports the next iterator, then hands the node's link word
// back to the fixed pool (or frees the node when it came from the heap).
// The original keeps `pos` in edi and the next node in the dead first stack
// slot, so it is spelled as a reused slot rather than an iterator local.
void RectSet::erase(RectNode* pos, u32* result)
{
    RectNode* p = pos;
    RectNode*& next = *(RectNode**)&pos;
    --mnSize;
    next = RBTreeIncrement(p);
    RBTree_RemoveNode(&mAnchor, p, &mpAllocator);
    if ((char*)p >= mpNodeBegin && (char*)p < mpNodeEnd) {
        p->mpRight = mpFreeList;
        mpFreeList = p;
    } else {
        operator delete(p);
    }
    *(RectNode**)result = next;
}
