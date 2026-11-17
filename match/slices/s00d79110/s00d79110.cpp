// rbtree::DoInsertValue for unique keys (0x00d79110): walk down to the insertion point; insert (DoInsertValueImpl
// 0xd79080) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_d79110 { RBNodeBase_d79110* mpNodeRight; RBNodeBase_d79110* mpNodeLeft; RBNodeBase_d79110* mpNodeParent; int mColor; };
RBNodeBase_d79110* RBTreeDecrement_d79110(const RBNodeBase_d79110* pNode);   // 0x009215c0

struct Value_d79110 { uint32_t first; };
struct Node_d79110 : RBNodeBase_d79110 {
    Value_d79110 mValue;                         // +0x10
};
struct Iterator_d79110 {
    Node_d79110* mpNode;
    explicit Iterator_d79110(Node_d79110* p) : mpNode(p) {}
};
struct InsertResult_d79110 {
    Iterator_d79110 first;
    bool second;
    InsertResult_d79110(const Iterator_d79110& it, bool b) : first(it), second(b) {}
};
struct TrueType_d79110 {};
struct Tree_d79110 {
    int mCompare;                             // +0x00
    RBNodeBase_d79110 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_d79110 DoInsertValueImpl(Node_d79110* pNodeParent, const Value_d79110& value, bool bForceToLeft);   // 0x00d79080
    InsertResult_d79110 DoInsertValue(const Value_d79110& value, TrueType_d79110);
};

// @ 0x00d79110
InsertResult_d79110 Tree_d79110::DoInsertValue(const Value_d79110& value, TrueType_d79110)
{
    Node_d79110* pCurrent = (Node_d79110*)mAnchor.mpNodeParent;
    Node_d79110* pLowerBound = (Node_d79110*)&mAnchor;
    Node_d79110* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_d79110*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_d79110*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_d79110*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_d79110*)RBTreeDecrement_d79110(pLowerBound);
        else {
            const Iterator_d79110 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_d79110(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_d79110 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_d79110(itResult, true);
    }

    return InsertResult_d79110(Iterator_d79110(pLowerBound), false);
}
