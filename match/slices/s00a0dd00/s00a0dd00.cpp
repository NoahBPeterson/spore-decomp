// rbtree::DoInsertValue for unique keys (0x00a0dd00): walk down to the insertion point; insert (DoInsertValueImpl
// 0xa0dc70) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_a0dd00 { RBNodeBase_a0dd00* mpNodeRight; RBNodeBase_a0dd00* mpNodeLeft; RBNodeBase_a0dd00* mpNodeParent; int mColor; };
RBNodeBase_a0dd00* RBTreeDecrement_a0dd00(const RBNodeBase_a0dd00* pNode);   // 0x009215c0

struct Value_a0dd00 { uint32_t first; };
struct Node_a0dd00 : RBNodeBase_a0dd00 {
    Value_a0dd00 mValue;                         // +0x10
};
struct Iterator_a0dd00 {
    Node_a0dd00* mpNode;
    explicit Iterator_a0dd00(Node_a0dd00* p) : mpNode(p) {}
};
struct InsertResult_a0dd00 {
    Iterator_a0dd00 first;
    bool second;
    InsertResult_a0dd00(const Iterator_a0dd00& it, bool b) : first(it), second(b) {}
};
struct TrueType_a0dd00 {};
struct Tree_a0dd00 {
    int mCompare;                             // +0x00
    RBNodeBase_a0dd00 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_a0dd00 DoInsertValueImpl(Node_a0dd00* pNodeParent, const Value_a0dd00& value, bool bForceToLeft);   // 0x00a0dc70
    InsertResult_a0dd00 DoInsertValue(const Value_a0dd00& value, TrueType_a0dd00);
};

// @ 0x00a0dd00
InsertResult_a0dd00 Tree_a0dd00::DoInsertValue(const Value_a0dd00& value, TrueType_a0dd00)
{
    Node_a0dd00* pCurrent = (Node_a0dd00*)mAnchor.mpNodeParent;
    Node_a0dd00* pLowerBound = (Node_a0dd00*)&mAnchor;
    Node_a0dd00* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_a0dd00*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_a0dd00*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_a0dd00*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_a0dd00*)RBTreeDecrement_a0dd00(pLowerBound);
        else {
            const Iterator_a0dd00 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_a0dd00(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_a0dd00 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_a0dd00(itResult, true);
    }

    return InsertResult_a0dd00(Iterator_a0dd00(pLowerBound), false);
}
