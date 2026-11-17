// rbtree::DoInsertValue for unique keys (0x00e3b950): walk down to the insertion point; insert (DoInsertValueImpl
// 0xe3b790) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_e3b950 { RBNodeBase_e3b950* mpNodeRight; RBNodeBase_e3b950* mpNodeLeft; RBNodeBase_e3b950* mpNodeParent; int mColor; };
RBNodeBase_e3b950* RBTreeDecrement_e3b950(const RBNodeBase_e3b950* pNode);   // 0x009215c0

struct Value_e3b950 { uint32_t first; };
struct Node_e3b950 : RBNodeBase_e3b950 {
    Value_e3b950 mValue;                         // +0x10
};
struct Iterator_e3b950 {
    Node_e3b950* mpNode;
    explicit Iterator_e3b950(Node_e3b950* p) : mpNode(p) {}
};
struct InsertResult_e3b950 {
    Iterator_e3b950 first;
    bool second;
    InsertResult_e3b950(const Iterator_e3b950& it, bool b) : first(it), second(b) {}
};
struct TrueType_e3b950 {};
struct Tree_e3b950 {
    int mCompare;                             // +0x00
    RBNodeBase_e3b950 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_e3b950 DoInsertValueImpl(Node_e3b950* pNodeParent, const Value_e3b950& value, bool bForceToLeft);   // 0x00e3b790
    InsertResult_e3b950 DoInsertValue(const Value_e3b950& value, TrueType_e3b950);
};

// @ 0x00e3b950
InsertResult_e3b950 Tree_e3b950::DoInsertValue(const Value_e3b950& value, TrueType_e3b950)
{
    Node_e3b950* pCurrent = (Node_e3b950*)mAnchor.mpNodeParent;
    Node_e3b950* pLowerBound = (Node_e3b950*)&mAnchor;
    Node_e3b950* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_e3b950*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_e3b950*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_e3b950*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_e3b950*)RBTreeDecrement_e3b950(pLowerBound);
        else {
            const Iterator_e3b950 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_e3b950(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_e3b950 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_e3b950(itResult, true);
    }

    return InsertResult_e3b950(Iterator_e3b950(pLowerBound), false);
}
