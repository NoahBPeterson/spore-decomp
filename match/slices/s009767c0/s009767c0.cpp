// rbtree::DoInsertValue for unique keys (0x009767c0): walk down to the insertion point; insert (DoInsertValueImpl
// 0x9764c0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_9767c0 { RBNodeBase_9767c0* mpNodeRight; RBNodeBase_9767c0* mpNodeLeft; RBNodeBase_9767c0* mpNodeParent; int mColor; };
RBNodeBase_9767c0* RBTreeDecrement_9767c0(const RBNodeBase_9767c0* pNode);   // 0x009215c0

struct Value_9767c0 { int32_t first; };
struct Node_9767c0 : RBNodeBase_9767c0 {
    Value_9767c0 mValue;                         // +0x10
};
struct Iterator_9767c0 {
    Node_9767c0* mpNode;
    explicit Iterator_9767c0(Node_9767c0* p) : mpNode(p) {}
};
struct InsertResult_9767c0 {
    Iterator_9767c0 first;
    bool second;
    InsertResult_9767c0(const Iterator_9767c0& it, bool b) : first(it), second(b) {}
};
struct TrueType_9767c0 {};
struct Tree_9767c0 {
    int mCompare;                             // +0x00
    RBNodeBase_9767c0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_9767c0 DoInsertValueImpl(Node_9767c0* pNodeParent, const Value_9767c0& value, bool bForceToLeft);   // 0x009764c0
    InsertResult_9767c0 DoInsertValue(const Value_9767c0& value, TrueType_9767c0);
};

// @ 0x009767c0
InsertResult_9767c0 Tree_9767c0::DoInsertValue(const Value_9767c0& value, TrueType_9767c0)
{
    Node_9767c0* pCurrent = (Node_9767c0*)mAnchor.mpNodeParent;
    Node_9767c0* pLowerBound = (Node_9767c0*)&mAnchor;
    Node_9767c0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_9767c0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_9767c0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_9767c0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_9767c0*)RBTreeDecrement_9767c0(pLowerBound);
        else {
            const Iterator_9767c0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_9767c0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_9767c0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_9767c0(itResult, true);
    }

    return InsertResult_9767c0(Iterator_9767c0(pLowerBound), false);
}
