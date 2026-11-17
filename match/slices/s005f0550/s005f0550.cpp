// rbtree::DoInsertValue for unique keys (0x005f0550): walk down to the insertion point; insert (DoInsertValueImpl
// 0x5f0420) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_5f0550 { RBNodeBase_5f0550* mpNodeRight; RBNodeBase_5f0550* mpNodeLeft; RBNodeBase_5f0550* mpNodeParent; int mColor; };
RBNodeBase_5f0550* RBTreeDecrement_5f0550(const RBNodeBase_5f0550* pNode);   // 0x009215c0

struct Value_5f0550 { uint32_t first; };
struct Node_5f0550 : RBNodeBase_5f0550 {
    Value_5f0550 mValue;                         // +0x10
};
struct Iterator_5f0550 {
    Node_5f0550* mpNode;
    explicit Iterator_5f0550(Node_5f0550* p) : mpNode(p) {}
};
struct InsertResult_5f0550 {
    Iterator_5f0550 first;
    bool second;
    InsertResult_5f0550(const Iterator_5f0550& it, bool b) : first(it), second(b) {}
};
struct TrueType_5f0550 {};
struct Tree_5f0550 {
    int mCompare;                             // +0x00
    RBNodeBase_5f0550 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5f0550 DoInsertValueImpl(Node_5f0550* pNodeParent, const Value_5f0550& value, bool bForceToLeft);   // 0x005f0420
    InsertResult_5f0550 DoInsertValue(const Value_5f0550& value, TrueType_5f0550);
};

// @ 0x005f0550
InsertResult_5f0550 Tree_5f0550::DoInsertValue(const Value_5f0550& value, TrueType_5f0550)
{
    Node_5f0550* pCurrent = (Node_5f0550*)mAnchor.mpNodeParent;
    Node_5f0550* pLowerBound = (Node_5f0550*)&mAnchor;
    Node_5f0550* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_5f0550*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_5f0550*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_5f0550*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_5f0550*)RBTreeDecrement_5f0550(pLowerBound);
        else {
            const Iterator_5f0550 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_5f0550(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_5f0550 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_5f0550(itResult, true);
    }

    return InsertResult_5f0550(Iterator_5f0550(pLowerBound), false);
}
