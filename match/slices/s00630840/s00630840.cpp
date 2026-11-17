// rbtree::DoInsertValue for unique keys (0x00630840): walk down to the insertion point; insert (DoInsertValueImpl
// 0x6307a0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_630840 { RBNodeBase_630840* mpNodeRight; RBNodeBase_630840* mpNodeLeft; RBNodeBase_630840* mpNodeParent; int mColor; };
RBNodeBase_630840* RBTreeDecrement_630840(const RBNodeBase_630840* pNode);   // 0x009215c0

struct Value_630840 { uint32_t first; };
struct Node_630840 : RBNodeBase_630840 {
    Value_630840 mValue;                         // +0x10
};
struct Iterator_630840 {
    Node_630840* mpNode;
    explicit Iterator_630840(Node_630840* p) : mpNode(p) {}
};
struct InsertResult_630840 {
    Iterator_630840 first;
    bool second;
    InsertResult_630840(const Iterator_630840& it, bool b) : first(it), second(b) {}
};
struct TrueType_630840 {};
struct Tree_630840 {
    int mCompare;                             // +0x00
    RBNodeBase_630840 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_630840 DoInsertValueImpl(Node_630840* pNodeParent, const Value_630840& value, bool bForceToLeft);   // 0x006307a0
    InsertResult_630840 DoInsertValue(const Value_630840& value, TrueType_630840);
};

// @ 0x00630840
InsertResult_630840 Tree_630840::DoInsertValue(const Value_630840& value, TrueType_630840)
{
    Node_630840* pCurrent = (Node_630840*)mAnchor.mpNodeParent;
    Node_630840* pLowerBound = (Node_630840*)&mAnchor;
    Node_630840* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_630840*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_630840*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_630840*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_630840*)RBTreeDecrement_630840(pLowerBound);
        else {
            const Iterator_630840 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_630840(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_630840 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_630840(itResult, true);
    }

    return InsertResult_630840(Iterator_630840(pLowerBound), false);
}
