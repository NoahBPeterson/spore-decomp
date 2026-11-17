// rbtree::DoInsertValue for unique keys (0x00cbae70): walk down to the insertion point; insert (DoInsertValueImpl
// 0xcb9780) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_cbae70 { RBNodeBase_cbae70* mpNodeRight; RBNodeBase_cbae70* mpNodeLeft; RBNodeBase_cbae70* mpNodeParent; int mColor; };
RBNodeBase_cbae70* RBTreeDecrement_cbae70(const RBNodeBase_cbae70* pNode);   // 0x009215c0

struct Value_cbae70 { uint32_t first; };
struct Node_cbae70 : RBNodeBase_cbae70 {
    Value_cbae70 mValue;                         // +0x10
};
struct Iterator_cbae70 {
    Node_cbae70* mpNode;
    explicit Iterator_cbae70(Node_cbae70* p) : mpNode(p) {}
};
struct InsertResult_cbae70 {
    Iterator_cbae70 first;
    bool second;
    InsertResult_cbae70(const Iterator_cbae70& it, bool b) : first(it), second(b) {}
};
struct TrueType_cbae70 {};
struct Tree_cbae70 {
    int mCompare;                             // +0x00
    RBNodeBase_cbae70 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_cbae70 DoInsertValueImpl(Node_cbae70* pNodeParent, const Value_cbae70& value, bool bForceToLeft);   // 0x00cb9780
    InsertResult_cbae70 DoInsertValue(const Value_cbae70& value, TrueType_cbae70);
};

// @ 0x00cbae70
InsertResult_cbae70 Tree_cbae70::DoInsertValue(const Value_cbae70& value, TrueType_cbae70)
{
    Node_cbae70* pCurrent = (Node_cbae70*)mAnchor.mpNodeParent;
    Node_cbae70* pLowerBound = (Node_cbae70*)&mAnchor;
    Node_cbae70* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_cbae70*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_cbae70*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_cbae70*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_cbae70*)RBTreeDecrement_cbae70(pLowerBound);
        else {
            const Iterator_cbae70 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_cbae70(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_cbae70 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_cbae70(itResult, true);
    }

    return InsertResult_cbae70(Iterator_cbae70(pLowerBound), false);
}
