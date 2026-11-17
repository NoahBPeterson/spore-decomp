// rbtree::DoInsertValue for unique keys (0x0091c010): walk down to the insertion point; insert (DoInsertValueImpl
// 0x91bf80) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_91c010 { RBNodeBase_91c010* mpNodeRight; RBNodeBase_91c010* mpNodeLeft; RBNodeBase_91c010* mpNodeParent; int mColor; };
RBNodeBase_91c010* RBTreeDecrement_91c010(const RBNodeBase_91c010* pNode);   // 0x009215c0

struct Value_91c010 { uint32_t first; };
struct Node_91c010 : RBNodeBase_91c010 {
    Value_91c010 mValue;                         // +0x10
};
struct Iterator_91c010 {
    Node_91c010* mpNode;
    explicit Iterator_91c010(Node_91c010* p) : mpNode(p) {}
};
struct InsertResult_91c010 {
    Iterator_91c010 first;
    bool second;
    InsertResult_91c010(const Iterator_91c010& it, bool b) : first(it), second(b) {}
};
struct TrueType_91c010 {};
struct Tree_91c010 {
    int mCompare;                             // +0x00
    RBNodeBase_91c010 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_91c010 DoInsertValueImpl(Node_91c010* pNodeParent, const Value_91c010& value, bool bForceToLeft);   // 0x0091bf80
    InsertResult_91c010 DoInsertValue(const Value_91c010& value, TrueType_91c010);
};

// @ 0x0091c010
InsertResult_91c010 Tree_91c010::DoInsertValue(const Value_91c010& value, TrueType_91c010)
{
    Node_91c010* pCurrent = (Node_91c010*)mAnchor.mpNodeParent;
    Node_91c010* pLowerBound = (Node_91c010*)&mAnchor;
    Node_91c010* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_91c010*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_91c010*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_91c010*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_91c010*)RBTreeDecrement_91c010(pLowerBound);
        else {
            const Iterator_91c010 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_91c010(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_91c010 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_91c010(itResult, true);
    }

    return InsertResult_91c010(Iterator_91c010(pLowerBound), false);
}
