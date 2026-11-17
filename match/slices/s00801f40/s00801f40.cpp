// rbtree::DoInsertValue for unique keys (0x00801f40): walk down to the insertion point; insert (DoInsertValueImpl
// 0x801cf0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_801f40 { RBNodeBase_801f40* mpNodeRight; RBNodeBase_801f40* mpNodeLeft; RBNodeBase_801f40* mpNodeParent; int mColor; };
RBNodeBase_801f40* RBTreeDecrement_801f40(const RBNodeBase_801f40* pNode);   // 0x009215c0

struct Value_801f40 { uint32_t first; };
struct Node_801f40 : RBNodeBase_801f40 {
    Value_801f40 mValue;                         // +0x10
};
struct Iterator_801f40 {
    Node_801f40* mpNode;
    explicit Iterator_801f40(Node_801f40* p) : mpNode(p) {}
};
struct InsertResult_801f40 {
    Iterator_801f40 first;
    bool second;
    InsertResult_801f40(const Iterator_801f40& it, bool b) : first(it), second(b) {}
};
struct TrueType_801f40 {};
struct Tree_801f40 {
    int mCompare;                             // +0x00
    RBNodeBase_801f40 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_801f40 DoInsertValueImpl(Node_801f40* pNodeParent, const Value_801f40& value, bool bForceToLeft);   // 0x00801cf0
    InsertResult_801f40 DoInsertValue(const Value_801f40& value, TrueType_801f40);
};

// @ 0x00801f40
InsertResult_801f40 Tree_801f40::DoInsertValue(const Value_801f40& value, TrueType_801f40)
{
    Node_801f40* pCurrent = (Node_801f40*)mAnchor.mpNodeParent;
    Node_801f40* pLowerBound = (Node_801f40*)&mAnchor;
    Node_801f40* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_801f40*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_801f40*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_801f40*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_801f40*)RBTreeDecrement_801f40(pLowerBound);
        else {
            const Iterator_801f40 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_801f40(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_801f40 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_801f40(itResult, true);
    }

    return InsertResult_801f40(Iterator_801f40(pLowerBound), false);
}
