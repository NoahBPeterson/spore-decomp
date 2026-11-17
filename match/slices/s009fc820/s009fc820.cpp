// rbtree::DoInsertValue for unique keys (0x009fc820): walk down to the insertion point; insert (DoInsertValueImpl
// 0x9fc530) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_9fc820 { RBNodeBase_9fc820* mpNodeRight; RBNodeBase_9fc820* mpNodeLeft; RBNodeBase_9fc820* mpNodeParent; int mColor; };
RBNodeBase_9fc820* RBTreeDecrement_9fc820(const RBNodeBase_9fc820* pNode);   // 0x009215c0

struct Value_9fc820 { uint32_t first; };
struct Node_9fc820 : RBNodeBase_9fc820 {
    Value_9fc820 mValue;                         // +0x10
};
struct Iterator_9fc820 {
    Node_9fc820* mpNode;
    explicit Iterator_9fc820(Node_9fc820* p) : mpNode(p) {}
};
struct InsertResult_9fc820 {
    Iterator_9fc820 first;
    bool second;
    InsertResult_9fc820(const Iterator_9fc820& it, bool b) : first(it), second(b) {}
};
struct TrueType_9fc820 {};
struct Tree_9fc820 {
    int mCompare;                             // +0x00
    RBNodeBase_9fc820 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_9fc820 DoInsertValueImpl(Node_9fc820* pNodeParent, const Value_9fc820& value, bool bForceToLeft);   // 0x009fc530
    InsertResult_9fc820 DoInsertValue(const Value_9fc820& value, TrueType_9fc820);
};

// @ 0x009fc820
InsertResult_9fc820 Tree_9fc820::DoInsertValue(const Value_9fc820& value, TrueType_9fc820)
{
    Node_9fc820* pCurrent = (Node_9fc820*)mAnchor.mpNodeParent;
    Node_9fc820* pLowerBound = (Node_9fc820*)&mAnchor;
    Node_9fc820* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_9fc820*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_9fc820*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_9fc820*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_9fc820*)RBTreeDecrement_9fc820(pLowerBound);
        else {
            const Iterator_9fc820 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_9fc820(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_9fc820 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_9fc820(itResult, true);
    }

    return InsertResult_9fc820(Iterator_9fc820(pLowerBound), false);
}
