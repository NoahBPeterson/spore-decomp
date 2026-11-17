// rbtree::DoInsertValue for unique keys (0x00bb1fe0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xbb1f50) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_bb1fe0 { RBNodeBase_bb1fe0* mpNodeRight; RBNodeBase_bb1fe0* mpNodeLeft; RBNodeBase_bb1fe0* mpNodeParent; int mColor; };
RBNodeBase_bb1fe0* RBTreeDecrement_bb1fe0(const RBNodeBase_bb1fe0* pNode);   // 0x009215c0

struct Value_bb1fe0 { uint32_t first; };
struct Node_bb1fe0 : RBNodeBase_bb1fe0 {
    Value_bb1fe0 mValue;                         // +0x10
};
struct Iterator_bb1fe0 {
    Node_bb1fe0* mpNode;
    explicit Iterator_bb1fe0(Node_bb1fe0* p) : mpNode(p) {}
};
struct InsertResult_bb1fe0 {
    Iterator_bb1fe0 first;
    bool second;
    InsertResult_bb1fe0(const Iterator_bb1fe0& it, bool b) : first(it), second(b) {}
};
struct TrueType_bb1fe0 {};
struct Tree_bb1fe0 {
    int mCompare;                             // +0x00
    RBNodeBase_bb1fe0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_bb1fe0 DoInsertValueImpl(Node_bb1fe0* pNodeParent, const Value_bb1fe0& value, bool bForceToLeft);   // 0x00bb1f50
    InsertResult_bb1fe0 DoInsertValue(const Value_bb1fe0& value, TrueType_bb1fe0);
};

// @ 0x00bb1fe0
InsertResult_bb1fe0 Tree_bb1fe0::DoInsertValue(const Value_bb1fe0& value, TrueType_bb1fe0)
{
    Node_bb1fe0* pCurrent = (Node_bb1fe0*)mAnchor.mpNodeParent;
    Node_bb1fe0* pLowerBound = (Node_bb1fe0*)&mAnchor;
    Node_bb1fe0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_bb1fe0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_bb1fe0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_bb1fe0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_bb1fe0*)RBTreeDecrement_bb1fe0(pLowerBound);
        else {
            const Iterator_bb1fe0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_bb1fe0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_bb1fe0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_bb1fe0(itResult, true);
    }

    return InsertResult_bb1fe0(Iterator_bb1fe0(pLowerBound), false);
}
