// rbtree::DoInsertValue for unique keys (0x006c3480): walk down to the insertion point; insert (DoInsertValueImpl
// 0x6c3330) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_6c3480 { RBNodeBase_6c3480* mpNodeRight; RBNodeBase_6c3480* mpNodeLeft; RBNodeBase_6c3480* mpNodeParent; int mColor; };
RBNodeBase_6c3480* RBTreeDecrement_6c3480(const RBNodeBase_6c3480* pNode);   // 0x009215c0

struct Value_6c3480 { int32_t first; };
struct Node_6c3480 : RBNodeBase_6c3480 {
    Value_6c3480 mValue;                         // +0x10
};
struct Iterator_6c3480 {
    Node_6c3480* mpNode;
    explicit Iterator_6c3480(Node_6c3480* p) : mpNode(p) {}
};
struct InsertResult_6c3480 {
    Iterator_6c3480 first;
    bool second;
    InsertResult_6c3480(const Iterator_6c3480& it, bool b) : first(it), second(b) {}
};
struct TrueType_6c3480 {};
struct Tree_6c3480 {
    int mCompare;                             // +0x00
    RBNodeBase_6c3480 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_6c3480 DoInsertValueImpl(Node_6c3480* pNodeParent, const Value_6c3480& value, bool bForceToLeft);   // 0x006c3330
    InsertResult_6c3480 DoInsertValue(const Value_6c3480& value, TrueType_6c3480);
};

// @ 0x006c3480
InsertResult_6c3480 Tree_6c3480::DoInsertValue(const Value_6c3480& value, TrueType_6c3480)
{
    Node_6c3480* pCurrent = (Node_6c3480*)mAnchor.mpNodeParent;
    Node_6c3480* pLowerBound = (Node_6c3480*)&mAnchor;
    Node_6c3480* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_6c3480*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_6c3480*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_6c3480*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_6c3480*)RBTreeDecrement_6c3480(pLowerBound);
        else {
            const Iterator_6c3480 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_6c3480(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_6c3480 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_6c3480(itResult, true);
    }

    return InsertResult_6c3480(Iterator_6c3480(pLowerBound), false);
}
