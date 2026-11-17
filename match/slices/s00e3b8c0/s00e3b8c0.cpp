// rbtree::DoInsertValue for unique keys (0x00e3b8c0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xe3b700) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_e3b8c0 { RBNodeBase_e3b8c0* mpNodeRight; RBNodeBase_e3b8c0* mpNodeLeft; RBNodeBase_e3b8c0* mpNodeParent; int mColor; };
RBNodeBase_e3b8c0* RBTreeDecrement_e3b8c0(const RBNodeBase_e3b8c0* pNode);   // 0x009215c0

struct Value_e3b8c0 { uint32_t first; };
struct Node_e3b8c0 : RBNodeBase_e3b8c0 {
    Value_e3b8c0 mValue;                         // +0x10
};
struct Iterator_e3b8c0 {
    Node_e3b8c0* mpNode;
    explicit Iterator_e3b8c0(Node_e3b8c0* p) : mpNode(p) {}
};
struct InsertResult_e3b8c0 {
    Iterator_e3b8c0 first;
    bool second;
    InsertResult_e3b8c0(const Iterator_e3b8c0& it, bool b) : first(it), second(b) {}
};
struct TrueType_e3b8c0 {};
struct Tree_e3b8c0 {
    int mCompare;                             // +0x00
    RBNodeBase_e3b8c0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_e3b8c0 DoInsertValueImpl(Node_e3b8c0* pNodeParent, const Value_e3b8c0& value, bool bForceToLeft);   // 0x00e3b700
    InsertResult_e3b8c0 DoInsertValue(const Value_e3b8c0& value, TrueType_e3b8c0);
};

// @ 0x00e3b8c0
InsertResult_e3b8c0 Tree_e3b8c0::DoInsertValue(const Value_e3b8c0& value, TrueType_e3b8c0)
{
    Node_e3b8c0* pCurrent = (Node_e3b8c0*)mAnchor.mpNodeParent;
    Node_e3b8c0* pLowerBound = (Node_e3b8c0*)&mAnchor;
    Node_e3b8c0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_e3b8c0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_e3b8c0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_e3b8c0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_e3b8c0*)RBTreeDecrement_e3b8c0(pLowerBound);
        else {
            const Iterator_e3b8c0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_e3b8c0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_e3b8c0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_e3b8c0(itResult, true);
    }

    return InsertResult_e3b8c0(Iterator_e3b8c0(pLowerBound), false);
}
