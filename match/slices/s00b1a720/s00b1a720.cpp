// rbtree::DoInsertValue for unique keys (0x00b1a720): walk down to the insertion point; insert (DoInsertValueImpl
// 0xb1a690) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_b1a720 { RBNodeBase_b1a720* mpNodeRight; RBNodeBase_b1a720* mpNodeLeft; RBNodeBase_b1a720* mpNodeParent; int mColor; };
RBNodeBase_b1a720* RBTreeDecrement_b1a720(const RBNodeBase_b1a720* pNode);   // 0x009215c0

struct Value_b1a720 { uint32_t first; };
struct Node_b1a720 : RBNodeBase_b1a720 {
    Value_b1a720 mValue;                         // +0x10
};
struct Iterator_b1a720 {
    Node_b1a720* mpNode;
    explicit Iterator_b1a720(Node_b1a720* p) : mpNode(p) {}
};
struct InsertResult_b1a720 {
    Iterator_b1a720 first;
    bool second;
    InsertResult_b1a720(const Iterator_b1a720& it, bool b) : first(it), second(b) {}
};
struct TrueType_b1a720 {};
struct Tree_b1a720 {
    int mCompare;                             // +0x00
    RBNodeBase_b1a720 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_b1a720 DoInsertValueImpl(Node_b1a720* pNodeParent, const Value_b1a720& value, bool bForceToLeft);   // 0x00b1a690
    InsertResult_b1a720 DoInsertValue(const Value_b1a720& value, TrueType_b1a720);
};

// @ 0x00b1a720
InsertResult_b1a720 Tree_b1a720::DoInsertValue(const Value_b1a720& value, TrueType_b1a720)
{
    Node_b1a720* pCurrent = (Node_b1a720*)mAnchor.mpNodeParent;
    Node_b1a720* pLowerBound = (Node_b1a720*)&mAnchor;
    Node_b1a720* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_b1a720*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_b1a720*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_b1a720*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_b1a720*)RBTreeDecrement_b1a720(pLowerBound);
        else {
            const Iterator_b1a720 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_b1a720(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_b1a720 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_b1a720(itResult, true);
    }

    return InsertResult_b1a720(Iterator_b1a720(pLowerBound), false);
}
