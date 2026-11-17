// rbtree::DoInsertValue for unique keys (0x00e4b300): walk down to the insertion point; insert (DoInsertValueImpl
// 0xe4b280) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_e4b300 { RBNodeBase_e4b300* mpNodeRight; RBNodeBase_e4b300* mpNodeLeft; RBNodeBase_e4b300* mpNodeParent; int mColor; };
RBNodeBase_e4b300* RBTreeDecrement_e4b300(const RBNodeBase_e4b300* pNode);   // 0x009215c0

struct Value_e4b300 { int32_t first; };
struct Node_e4b300 : RBNodeBase_e4b300 {
    Value_e4b300 mValue;                         // +0x10
};
struct Iterator_e4b300 {
    Node_e4b300* mpNode;
    explicit Iterator_e4b300(Node_e4b300* p) : mpNode(p) {}
};
struct InsertResult_e4b300 {
    Iterator_e4b300 first;
    bool second;
    InsertResult_e4b300(const Iterator_e4b300& it, bool b) : first(it), second(b) {}
};
struct TrueType_e4b300 {};
struct Tree_e4b300 {
    int mCompare;                             // +0x00
    RBNodeBase_e4b300 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_e4b300 DoInsertValueImpl(Node_e4b300* pNodeParent, const Value_e4b300& value, bool bForceToLeft);   // 0x00e4b280
    InsertResult_e4b300 DoInsertValue(const Value_e4b300& value, TrueType_e4b300);
};

// @ 0x00e4b300
InsertResult_e4b300 Tree_e4b300::DoInsertValue(const Value_e4b300& value, TrueType_e4b300)
{
    Node_e4b300* pCurrent = (Node_e4b300*)mAnchor.mpNodeParent;
    Node_e4b300* pLowerBound = (Node_e4b300*)&mAnchor;
    Node_e4b300* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_e4b300*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_e4b300*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_e4b300*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_e4b300*)RBTreeDecrement_e4b300(pLowerBound);
        else {
            const Iterator_e4b300 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_e4b300(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_e4b300 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_e4b300(itResult, true);
    }

    return InsertResult_e4b300(Iterator_e4b300(pLowerBound), false);
}
