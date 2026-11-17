// rbtree::DoInsertValue for unique keys (0x00a17a70): walk down to the insertion point; insert (DoInsertValueImpl
// 0xa17890) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_a17a70 { RBNodeBase_a17a70* mpNodeRight; RBNodeBase_a17a70* mpNodeLeft; RBNodeBase_a17a70* mpNodeParent; int mColor; };
RBNodeBase_a17a70* RBTreeDecrement_a17a70(const RBNodeBase_a17a70* pNode);   // 0x009215c0

struct Value_a17a70 { uint32_t first; };
struct Node_a17a70 : RBNodeBase_a17a70 {
    Value_a17a70 mValue;                         // +0x10
};
struct Iterator_a17a70 {
    Node_a17a70* mpNode;
    explicit Iterator_a17a70(Node_a17a70* p) : mpNode(p) {}
};
struct InsertResult_a17a70 {
    Iterator_a17a70 first;
    bool second;
    InsertResult_a17a70(const Iterator_a17a70& it, bool b) : first(it), second(b) {}
};
struct TrueType_a17a70 {};
struct Tree_a17a70 {
    int mCompare;                             // +0x00
    RBNodeBase_a17a70 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_a17a70 DoInsertValueImpl(Node_a17a70* pNodeParent, const Value_a17a70& value, bool bForceToLeft);   // 0x00a17890
    InsertResult_a17a70 DoInsertValue(const Value_a17a70& value, TrueType_a17a70);
};

// @ 0x00a17a70
InsertResult_a17a70 Tree_a17a70::DoInsertValue(const Value_a17a70& value, TrueType_a17a70)
{
    Node_a17a70* pCurrent = (Node_a17a70*)mAnchor.mpNodeParent;
    Node_a17a70* pLowerBound = (Node_a17a70*)&mAnchor;
    Node_a17a70* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_a17a70*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_a17a70*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_a17a70*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_a17a70*)RBTreeDecrement_a17a70(pLowerBound);
        else {
            const Iterator_a17a70 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_a17a70(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_a17a70 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_a17a70(itResult, true);
    }

    return InsertResult_a17a70(Iterator_a17a70(pLowerBound), false);
}
