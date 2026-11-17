// rbtree::DoInsertValue for unique keys (0x009dfb60): walk down to the insertion point; insert (DoInsertValueImpl
// 0x9dfae0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_9dfb60 { RBNodeBase_9dfb60* mpNodeRight; RBNodeBase_9dfb60* mpNodeLeft; RBNodeBase_9dfb60* mpNodeParent; int mColor; };
RBNodeBase_9dfb60* RBTreeDecrement_9dfb60(const RBNodeBase_9dfb60* pNode);   // 0x009215c0

struct Value_9dfb60 { uint32_t first; };
struct Node_9dfb60 : RBNodeBase_9dfb60 {
    Value_9dfb60 mValue;                         // +0x10
};
struct Iterator_9dfb60 {
    Node_9dfb60* mpNode;
    explicit Iterator_9dfb60(Node_9dfb60* p) : mpNode(p) {}
};
struct InsertResult_9dfb60 {
    Iterator_9dfb60 first;
    bool second;
    InsertResult_9dfb60(const Iterator_9dfb60& it, bool b) : first(it), second(b) {}
};
struct TrueType_9dfb60 {};
struct Tree_9dfb60 {
    int mCompare;                             // +0x00
    RBNodeBase_9dfb60 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_9dfb60 DoInsertValueImpl(Node_9dfb60* pNodeParent, const Value_9dfb60& value, bool bForceToLeft);   // 0x009dfae0
    InsertResult_9dfb60 DoInsertValue(const Value_9dfb60& value, TrueType_9dfb60);
};

// @ 0x009dfb60
InsertResult_9dfb60 Tree_9dfb60::DoInsertValue(const Value_9dfb60& value, TrueType_9dfb60)
{
    Node_9dfb60* pCurrent = (Node_9dfb60*)mAnchor.mpNodeParent;
    Node_9dfb60* pLowerBound = (Node_9dfb60*)&mAnchor;
    Node_9dfb60* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_9dfb60*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_9dfb60*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_9dfb60*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_9dfb60*)RBTreeDecrement_9dfb60(pLowerBound);
        else {
            const Iterator_9dfb60 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_9dfb60(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_9dfb60 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_9dfb60(itResult, true);
    }

    return InsertResult_9dfb60(Iterator_9dfb60(pLowerBound), false);
}
