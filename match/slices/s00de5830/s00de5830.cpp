// rbtree::DoInsertValue for unique keys (0x00de5830): walk down to the insertion point; insert (DoInsertValueImpl
// 0xde57b0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_de5830 { RBNodeBase_de5830* mpNodeRight; RBNodeBase_de5830* mpNodeLeft; RBNodeBase_de5830* mpNodeParent; int mColor; };
RBNodeBase_de5830* RBTreeDecrement_de5830(const RBNodeBase_de5830* pNode);   // 0x009215c0

struct Value_de5830 { int32_t first; };
struct Node_de5830 : RBNodeBase_de5830 {
    Value_de5830 mValue;                         // +0x10
};
struct Iterator_de5830 {
    Node_de5830* mpNode;
    explicit Iterator_de5830(Node_de5830* p) : mpNode(p) {}
};
struct InsertResult_de5830 {
    Iterator_de5830 first;
    bool second;
    InsertResult_de5830(const Iterator_de5830& it, bool b) : first(it), second(b) {}
};
struct TrueType_de5830 {};
struct Tree_de5830 {
    int mCompare;                             // +0x00
    RBNodeBase_de5830 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_de5830 DoInsertValueImpl(Node_de5830* pNodeParent, const Value_de5830& value, bool bForceToLeft);   // 0x00de57b0
    InsertResult_de5830 DoInsertValue(const Value_de5830& value, TrueType_de5830);
};

// @ 0x00de5830
InsertResult_de5830 Tree_de5830::DoInsertValue(const Value_de5830& value, TrueType_de5830)
{
    Node_de5830* pCurrent = (Node_de5830*)mAnchor.mpNodeParent;
    Node_de5830* pLowerBound = (Node_de5830*)&mAnchor;
    Node_de5830* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_de5830*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_de5830*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_de5830*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_de5830*)RBTreeDecrement_de5830(pLowerBound);
        else {
            const Iterator_de5830 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_de5830(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_de5830 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_de5830(itResult, true);
    }

    return InsertResult_de5830(Iterator_de5830(pLowerBound), false);
}
