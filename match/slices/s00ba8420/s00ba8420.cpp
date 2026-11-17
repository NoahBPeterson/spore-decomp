// rbtree::DoInsertValue for unique keys (0x00ba8420): walk down to the insertion point; insert (DoInsertValueImpl
// 0xba83a0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_ba8420 { RBNodeBase_ba8420* mpNodeRight; RBNodeBase_ba8420* mpNodeLeft; RBNodeBase_ba8420* mpNodeParent; int mColor; };
RBNodeBase_ba8420* RBTreeDecrement_ba8420(const RBNodeBase_ba8420* pNode);   // 0x009215c0

struct Value_ba8420 { uint32_t first; };
struct Node_ba8420 : RBNodeBase_ba8420 {
    Value_ba8420 mValue;                         // +0x10
};
struct Iterator_ba8420 {
    Node_ba8420* mpNode;
    explicit Iterator_ba8420(Node_ba8420* p) : mpNode(p) {}
};
struct InsertResult_ba8420 {
    Iterator_ba8420 first;
    bool second;
    InsertResult_ba8420(const Iterator_ba8420& it, bool b) : first(it), second(b) {}
};
struct TrueType_ba8420 {};
struct Tree_ba8420 {
    int mCompare;                             // +0x00
    RBNodeBase_ba8420 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_ba8420 DoInsertValueImpl(Node_ba8420* pNodeParent, const Value_ba8420& value, bool bForceToLeft);   // 0x00ba83a0
    InsertResult_ba8420 DoInsertValue(const Value_ba8420& value, TrueType_ba8420);
};

// @ 0x00ba8420
InsertResult_ba8420 Tree_ba8420::DoInsertValue(const Value_ba8420& value, TrueType_ba8420)
{
    Node_ba8420* pCurrent = (Node_ba8420*)mAnchor.mpNodeParent;
    Node_ba8420* pLowerBound = (Node_ba8420*)&mAnchor;
    Node_ba8420* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_ba8420*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_ba8420*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_ba8420*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_ba8420*)RBTreeDecrement_ba8420(pLowerBound);
        else {
            const Iterator_ba8420 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_ba8420(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_ba8420 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_ba8420(itResult, true);
    }

    return InsertResult_ba8420(Iterator_ba8420(pLowerBound), false);
}
