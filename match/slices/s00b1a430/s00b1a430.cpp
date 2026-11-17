// rbtree::DoInsertValue for unique keys (0x00b1a430): walk down to the insertion point; insert (DoInsertValueImpl
// 0xb1a3b0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_b1a430 { RBNodeBase_b1a430* mpNodeRight; RBNodeBase_b1a430* mpNodeLeft; RBNodeBase_b1a430* mpNodeParent; int mColor; };
RBNodeBase_b1a430* RBTreeDecrement_b1a430(const RBNodeBase_b1a430* pNode);   // 0x009215c0

struct Value_b1a430 { uint32_t first; };
struct Node_b1a430 : RBNodeBase_b1a430 {
    Value_b1a430 mValue;                         // +0x10
};
struct Iterator_b1a430 {
    Node_b1a430* mpNode;
    explicit Iterator_b1a430(Node_b1a430* p) : mpNode(p) {}
};
struct InsertResult_b1a430 {
    Iterator_b1a430 first;
    bool second;
    InsertResult_b1a430(const Iterator_b1a430& it, bool b) : first(it), second(b) {}
};
struct TrueType_b1a430 {};
struct Tree_b1a430 {
    int mCompare;                             // +0x00
    RBNodeBase_b1a430 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_b1a430 DoInsertValueImpl(Node_b1a430* pNodeParent, const Value_b1a430& value, bool bForceToLeft);   // 0x00b1a3b0
    InsertResult_b1a430 DoInsertValue(const Value_b1a430& value, TrueType_b1a430);
};

// @ 0x00b1a430
InsertResult_b1a430 Tree_b1a430::DoInsertValue(const Value_b1a430& value, TrueType_b1a430)
{
    Node_b1a430* pCurrent = (Node_b1a430*)mAnchor.mpNodeParent;
    Node_b1a430* pLowerBound = (Node_b1a430*)&mAnchor;
    Node_b1a430* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_b1a430*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_b1a430*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_b1a430*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_b1a430*)RBTreeDecrement_b1a430(pLowerBound);
        else {
            const Iterator_b1a430 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_b1a430(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_b1a430 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_b1a430(itResult, true);
    }

    return InsertResult_b1a430(Iterator_b1a430(pLowerBound), false);
}
