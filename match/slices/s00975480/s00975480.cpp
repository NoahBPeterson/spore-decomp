// rbtree::DoInsertValue for unique keys (0x00975480): walk down to the insertion point; insert (DoInsertValueImpl
// 0x973e60) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_975480 { RBNodeBase_975480* mpNodeRight; RBNodeBase_975480* mpNodeLeft; RBNodeBase_975480* mpNodeParent; int mColor; };
RBNodeBase_975480* RBTreeDecrement_975480(const RBNodeBase_975480* pNode);   // 0x009215c0

struct Value_975480 { int32_t first; };
struct Node_975480 : RBNodeBase_975480 {
    Value_975480 mValue;                         // +0x10
};
struct Iterator_975480 {
    Node_975480* mpNode;
    explicit Iterator_975480(Node_975480* p) : mpNode(p) {}
};
struct InsertResult_975480 {
    Iterator_975480 first;
    bool second;
    InsertResult_975480(const Iterator_975480& it, bool b) : first(it), second(b) {}
};
struct TrueType_975480 {};
struct Tree_975480 {
    int mCompare;                             // +0x00
    RBNodeBase_975480 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_975480 DoInsertValueImpl(Node_975480* pNodeParent, const Value_975480& value, bool bForceToLeft);   // 0x00973e60
    InsertResult_975480 DoInsertValue(const Value_975480& value, TrueType_975480);
};

// @ 0x00975480
InsertResult_975480 Tree_975480::DoInsertValue(const Value_975480& value, TrueType_975480)
{
    Node_975480* pCurrent = (Node_975480*)mAnchor.mpNodeParent;
    Node_975480* pLowerBound = (Node_975480*)&mAnchor;
    Node_975480* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_975480*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_975480*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_975480*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_975480*)RBTreeDecrement_975480(pLowerBound);
        else {
            const Iterator_975480 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_975480(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_975480 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_975480(itResult, true);
    }

    return InsertResult_975480(Iterator_975480(pLowerBound), false);
}
