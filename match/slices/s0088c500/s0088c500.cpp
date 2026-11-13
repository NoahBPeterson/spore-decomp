#include "game/types.h"

extern void __cdecl Free_00f47380(void*);

struct ListNode_0088c500 {
    ListNode_0088c500* mpNext;
    ListNode_0088c500* mpPrev;
};

struct ListIter_0088c500 {
    ListNode_0088c500* mpNode;
};

struct FixedList_0088c500 {
    ListNode_0088c500 mAnchor;   // +0x00
    ListNode_0088c500* mpFree;   // +0x08
    uint32_t mUnk0c;             // +0x0c
    void* mpPoolBegin;           // +0x10
    void* mpPoolEnd;             // +0x14

    // @ 0x0088c500
    ListIter_0088c500 erase(ListIter_0088c500 first, ListIter_0088c500 last);
};

// @ 0x0088c500
ListIter_0088c500 FixedList_0088c500::erase(ListIter_0088c500 first, ListIter_0088c500 last)
{
    while (first.mpNode != last.mpNode) {
        ListNode_0088c500* next = first.mpNode->mpNext;
        ListNode_0088c500* node = next->mpPrev;
        node->mpPrev->mpNext = node->mpNext;
        node->mpNext->mpPrev = node->mpPrev;
        if ((void*)node >= mpPoolBegin && (void*)node < mpPoolEnd) {
            node->mpNext = mpFree;
            mpFree = node;
        } else {
            Free_00f47380(node);
        }
        first.mpNode = next;
    }
    return last;
}
