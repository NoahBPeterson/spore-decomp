// rbtree::DoInsertValue for unique keys (0x0059c380): walk down to the insertion point; insert (DoInsertValueImpl
// 0x59c2f0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_59c380 { RBNodeBase_59c380* mpNodeRight; RBNodeBase_59c380* mpNodeLeft; RBNodeBase_59c380* mpNodeParent; int mColor; };
RBNodeBase_59c380* RBTreeDecrement_59c380(const RBNodeBase_59c380* pNode);   // 0x009215c0

struct Value_59c380 { uint32_t first; };
struct Node_59c380 : RBNodeBase_59c380 {
    Value_59c380 mValue;                         // +0x10
};
struct Iterator_59c380 {
    Node_59c380* mpNode;
    explicit Iterator_59c380(Node_59c380* p) : mpNode(p) {}
};
struct InsertResult_59c380 {
    Iterator_59c380 first;
    bool second;
    InsertResult_59c380(const Iterator_59c380& it, bool b) : first(it), second(b) {}
};
struct TrueType_59c380 {};
struct Tree_59c380 {
    int mCompare;                             // +0x00
    RBNodeBase_59c380 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_59c380 DoInsertValueImpl(Node_59c380* pNodeParent, const Value_59c380& value, bool bForceToLeft);   // 0x0059c2f0
    InsertResult_59c380 DoInsertValue(const Value_59c380& value, TrueType_59c380);
};

// @ 0x0059c380
InsertResult_59c380 Tree_59c380::DoInsertValue(const Value_59c380& value, TrueType_59c380)
{
    Node_59c380* pCurrent = (Node_59c380*)mAnchor.mpNodeParent;
    Node_59c380* pLowerBound = (Node_59c380*)&mAnchor;
    Node_59c380* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_59c380*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_59c380*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_59c380*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_59c380*)RBTreeDecrement_59c380(pLowerBound);
        else {
            const Iterator_59c380 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_59c380(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_59c380 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_59c380(itResult, true);
    }

    return InsertResult_59c380(Iterator_59c380(pLowerBound), false);
}
