// rbtree::DoInsertValue for unique keys (0x005bdbf0): walk down to the insertion point; insert (DoInsertValueImpl
// 0x5bdb60) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_5bdbf0 { RBNodeBase_5bdbf0* mpNodeRight; RBNodeBase_5bdbf0* mpNodeLeft; RBNodeBase_5bdbf0* mpNodeParent; int mColor; };
RBNodeBase_5bdbf0* RBTreeDecrement_5bdbf0(const RBNodeBase_5bdbf0* pNode);   // 0x009215c0

struct Value_5bdbf0 { uint32_t first; };
struct Node_5bdbf0 : RBNodeBase_5bdbf0 {
    Value_5bdbf0 mValue;                         // +0x10
};
struct Iterator_5bdbf0 {
    Node_5bdbf0* mpNode;
    explicit Iterator_5bdbf0(Node_5bdbf0* p) : mpNode(p) {}
};
struct InsertResult_5bdbf0 {
    Iterator_5bdbf0 first;
    bool second;
    InsertResult_5bdbf0(const Iterator_5bdbf0& it, bool b) : first(it), second(b) {}
};
struct TrueType_5bdbf0 {};
struct Tree_5bdbf0 {
    int mCompare;                             // +0x00
    RBNodeBase_5bdbf0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5bdbf0 DoInsertValueImpl(Node_5bdbf0* pNodeParent, const Value_5bdbf0& value, bool bForceToLeft);   // 0x005bdb60
    InsertResult_5bdbf0 DoInsertValue(const Value_5bdbf0& value, TrueType_5bdbf0);
};

// @ 0x005bdbf0
InsertResult_5bdbf0 Tree_5bdbf0::DoInsertValue(const Value_5bdbf0& value, TrueType_5bdbf0)
{
    Node_5bdbf0* pCurrent = (Node_5bdbf0*)mAnchor.mpNodeParent;
    Node_5bdbf0* pLowerBound = (Node_5bdbf0*)&mAnchor;
    Node_5bdbf0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_5bdbf0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_5bdbf0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_5bdbf0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_5bdbf0*)RBTreeDecrement_5bdbf0(pLowerBound);
        else {
            const Iterator_5bdbf0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_5bdbf0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_5bdbf0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_5bdbf0(itResult, true);
    }

    return InsertResult_5bdbf0(Iterator_5bdbf0(pLowerBound), false);
}
