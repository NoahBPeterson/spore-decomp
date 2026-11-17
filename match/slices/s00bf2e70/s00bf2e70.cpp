// rbtree::DoInsertValue for unique keys (0x00bf2e70): walk down to the insertion point; insert (DoInsertValueImpl
// 0xbf27a0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_bf2e70 { RBNodeBase_bf2e70* mpNodeRight; RBNodeBase_bf2e70* mpNodeLeft; RBNodeBase_bf2e70* mpNodeParent; int mColor; };
RBNodeBase_bf2e70* RBTreeDecrement_bf2e70(const RBNodeBase_bf2e70* pNode);   // 0x009215c0

struct Value_bf2e70 { uint32_t first; };
struct Node_bf2e70 : RBNodeBase_bf2e70 {
    Value_bf2e70 mValue;                         // +0x10
};
struct Iterator_bf2e70 {
    Node_bf2e70* mpNode;
    explicit Iterator_bf2e70(Node_bf2e70* p) : mpNode(p) {}
};
struct InsertResult_bf2e70 {
    Iterator_bf2e70 first;
    bool second;
    InsertResult_bf2e70(const Iterator_bf2e70& it, bool b) : first(it), second(b) {}
};
struct TrueType_bf2e70 {};
struct Tree_bf2e70 {
    int mCompare;                             // +0x00
    RBNodeBase_bf2e70 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_bf2e70 DoInsertValueImpl(Node_bf2e70* pNodeParent, const Value_bf2e70& value, bool bForceToLeft);   // 0x00bf27a0
    InsertResult_bf2e70 DoInsertValue(const Value_bf2e70& value, TrueType_bf2e70);
};

// @ 0x00bf2e70
InsertResult_bf2e70 Tree_bf2e70::DoInsertValue(const Value_bf2e70& value, TrueType_bf2e70)
{
    Node_bf2e70* pCurrent = (Node_bf2e70*)mAnchor.mpNodeParent;
    Node_bf2e70* pLowerBound = (Node_bf2e70*)&mAnchor;
    Node_bf2e70* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_bf2e70*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_bf2e70*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_bf2e70*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_bf2e70*)RBTreeDecrement_bf2e70(pLowerBound);
        else {
            const Iterator_bf2e70 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_bf2e70(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_bf2e70 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_bf2e70(itResult, true);
    }

    return InsertResult_bf2e70(Iterator_bf2e70(pLowerBound), false);
}
