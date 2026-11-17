// rbtree::DoInsertValue for unique keys (0x00ec91c0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xec9140) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_ec91c0 { RBNodeBase_ec91c0* mpNodeRight; RBNodeBase_ec91c0* mpNodeLeft; RBNodeBase_ec91c0* mpNodeParent; int mColor; };
RBNodeBase_ec91c0* RBTreeDecrement_ec91c0(const RBNodeBase_ec91c0* pNode);   // 0x009215c0

struct Value_ec91c0 { int32_t first; };
struct Node_ec91c0 : RBNodeBase_ec91c0 {
    Value_ec91c0 mValue;                         // +0x10
};
struct Iterator_ec91c0 {
    Node_ec91c0* mpNode;
    explicit Iterator_ec91c0(Node_ec91c0* p) : mpNode(p) {}
};
struct InsertResult_ec91c0 {
    Iterator_ec91c0 first;
    bool second;
    InsertResult_ec91c0(const Iterator_ec91c0& it, bool b) : first(it), second(b) {}
};
struct TrueType_ec91c0 {};
struct Tree_ec91c0 {
    int mCompare;                             // +0x00
    RBNodeBase_ec91c0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_ec91c0 DoInsertValueImpl(Node_ec91c0* pNodeParent, const Value_ec91c0& value, bool bForceToLeft);   // 0x00ec9140
    InsertResult_ec91c0 DoInsertValue(const Value_ec91c0& value, TrueType_ec91c0);
};

// @ 0x00ec91c0
InsertResult_ec91c0 Tree_ec91c0::DoInsertValue(const Value_ec91c0& value, TrueType_ec91c0)
{
    Node_ec91c0* pCurrent = (Node_ec91c0*)mAnchor.mpNodeParent;
    Node_ec91c0* pLowerBound = (Node_ec91c0*)&mAnchor;
    Node_ec91c0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_ec91c0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_ec91c0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_ec91c0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_ec91c0*)RBTreeDecrement_ec91c0(pLowerBound);
        else {
            const Iterator_ec91c0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_ec91c0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_ec91c0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_ec91c0(itResult, true);
    }

    return InsertResult_ec91c0(Iterator_ec91c0(pLowerBound), false);
}
