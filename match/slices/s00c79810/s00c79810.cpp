// rbtree::DoInsertValue for unique keys (0x00c79810): walk down to the insertion point; insert (DoInsertValueImpl
// 0xc78390) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_c79810 { RBNodeBase_c79810* mpNodeRight; RBNodeBase_c79810* mpNodeLeft; RBNodeBase_c79810* mpNodeParent; int mColor; };
RBNodeBase_c79810* RBTreeDecrement_c79810(const RBNodeBase_c79810* pNode);   // 0x009215c0

struct Value_c79810 { uint32_t first; };
struct Node_c79810 : RBNodeBase_c79810 {
    Value_c79810 mValue;                         // +0x10
};
struct Iterator_c79810 {
    Node_c79810* mpNode;
    explicit Iterator_c79810(Node_c79810* p) : mpNode(p) {}
};
struct InsertResult_c79810 {
    Iterator_c79810 first;
    bool second;
    InsertResult_c79810(const Iterator_c79810& it, bool b) : first(it), second(b) {}
};
struct TrueType_c79810 {};
struct Tree_c79810 {
    int mCompare;                             // +0x00
    RBNodeBase_c79810 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_c79810 DoInsertValueImpl(Node_c79810* pNodeParent, const Value_c79810& value, bool bForceToLeft);   // 0x00c78390
    InsertResult_c79810 DoInsertValue(const Value_c79810& value, TrueType_c79810);
};

// @ 0x00c79810
InsertResult_c79810 Tree_c79810::DoInsertValue(const Value_c79810& value, TrueType_c79810)
{
    Node_c79810* pCurrent = (Node_c79810*)mAnchor.mpNodeParent;
    Node_c79810* pLowerBound = (Node_c79810*)&mAnchor;
    Node_c79810* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_c79810*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_c79810*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_c79810*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_c79810*)RBTreeDecrement_c79810(pLowerBound);
        else {
            const Iterator_c79810 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_c79810(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_c79810 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_c79810(itResult, true);
    }

    return InsertResult_c79810(Iterator_c79810(pLowerBound), false);
}
