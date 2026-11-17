// rbtree::DoInsertValue for unique keys (0x00b971b0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xb96820) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_b971b0 { RBNodeBase_b971b0* mpNodeRight; RBNodeBase_b971b0* mpNodeLeft; RBNodeBase_b971b0* mpNodeParent; int mColor; };
RBNodeBase_b971b0* RBTreeDecrement_b971b0(const RBNodeBase_b971b0* pNode);   // 0x009215c0

struct Value_b971b0 { uint32_t first; };
struct Node_b971b0 : RBNodeBase_b971b0 {
    Value_b971b0 mValue;                         // +0x10
};
struct Iterator_b971b0 {
    Node_b971b0* mpNode;
    explicit Iterator_b971b0(Node_b971b0* p) : mpNode(p) {}
};
struct InsertResult_b971b0 {
    Iterator_b971b0 first;
    bool second;
    InsertResult_b971b0(const Iterator_b971b0& it, bool b) : first(it), second(b) {}
};
struct TrueType_b971b0 {};
struct Tree_b971b0 {
    int mCompare;                             // +0x00
    RBNodeBase_b971b0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_b971b0 DoInsertValueImpl(Node_b971b0* pNodeParent, const Value_b971b0& value, bool bForceToLeft);   // 0x00b96820
    InsertResult_b971b0 DoInsertValue(const Value_b971b0& value, TrueType_b971b0);
};

// @ 0x00b971b0
InsertResult_b971b0 Tree_b971b0::DoInsertValue(const Value_b971b0& value, TrueType_b971b0)
{
    Node_b971b0* pCurrent = (Node_b971b0*)mAnchor.mpNodeParent;
    Node_b971b0* pLowerBound = (Node_b971b0*)&mAnchor;
    Node_b971b0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_b971b0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_b971b0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_b971b0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_b971b0*)RBTreeDecrement_b971b0(pLowerBound);
        else {
            const Iterator_b971b0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_b971b0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_b971b0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_b971b0(itResult, true);
    }

    return InsertResult_b971b0(Iterator_b971b0(pLowerBound), false);
}
