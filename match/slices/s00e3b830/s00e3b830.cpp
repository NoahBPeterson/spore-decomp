// rbtree::DoInsertValue for unique keys (0x00e3b830): walk down to the insertion point; insert (DoInsertValueImpl
// 0xe3b670) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_e3b830 { RBNodeBase_e3b830* mpNodeRight; RBNodeBase_e3b830* mpNodeLeft; RBNodeBase_e3b830* mpNodeParent; int mColor; };
RBNodeBase_e3b830* RBTreeDecrement_e3b830(const RBNodeBase_e3b830* pNode);   // 0x009215c0

struct Value_e3b830 { int32_t first; };
struct Node_e3b830 : RBNodeBase_e3b830 {
    Value_e3b830 mValue;                         // +0x10
};
struct Iterator_e3b830 {
    Node_e3b830* mpNode;
    explicit Iterator_e3b830(Node_e3b830* p) : mpNode(p) {}
};
struct InsertResult_e3b830 {
    Iterator_e3b830 first;
    bool second;
    InsertResult_e3b830(const Iterator_e3b830& it, bool b) : first(it), second(b) {}
};
struct TrueType_e3b830 {};
struct Tree_e3b830 {
    int mCompare;                             // +0x00
    RBNodeBase_e3b830 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_e3b830 DoInsertValueImpl(Node_e3b830* pNodeParent, const Value_e3b830& value, bool bForceToLeft);   // 0x00e3b670
    InsertResult_e3b830 DoInsertValue(const Value_e3b830& value, TrueType_e3b830);
};

// @ 0x00e3b830
InsertResult_e3b830 Tree_e3b830::DoInsertValue(const Value_e3b830& value, TrueType_e3b830)
{
    Node_e3b830* pCurrent = (Node_e3b830*)mAnchor.mpNodeParent;
    Node_e3b830* pLowerBound = (Node_e3b830*)&mAnchor;
    Node_e3b830* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_e3b830*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_e3b830*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_e3b830*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_e3b830*)RBTreeDecrement_e3b830(pLowerBound);
        else {
            const Iterator_e3b830 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_e3b830(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_e3b830 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_e3b830(itResult, true);
    }

    return InsertResult_e3b830(Iterator_e3b830(pLowerBound), false);
}
