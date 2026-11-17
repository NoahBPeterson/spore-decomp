// rbtree::DoInsertValue for unique keys (0x0068dc00): walk down to the insertion point; insert (DoInsertValueImpl
// 0x68daf0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_68dc00 { RBNodeBase_68dc00* mpNodeRight; RBNodeBase_68dc00* mpNodeLeft; RBNodeBase_68dc00* mpNodeParent; int mColor; };
RBNodeBase_68dc00* RBTreeDecrement_68dc00(const RBNodeBase_68dc00* pNode);   // 0x009215c0

struct Value_68dc00 { int32_t first; };
struct Node_68dc00 : RBNodeBase_68dc00 {
    Value_68dc00 mValue;                         // +0x10
};
struct Iterator_68dc00 {
    Node_68dc00* mpNode;
    explicit Iterator_68dc00(Node_68dc00* p) : mpNode(p) {}
};
struct InsertResult_68dc00 {
    Iterator_68dc00 first;
    bool second;
    InsertResult_68dc00(const Iterator_68dc00& it, bool b) : first(it), second(b) {}
};
struct TrueType_68dc00 {};
struct Tree_68dc00 {
    int mCompare;                             // +0x00
    RBNodeBase_68dc00 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_68dc00 DoInsertValueImpl(Node_68dc00* pNodeParent, const Value_68dc00& value, bool bForceToLeft);   // 0x0068daf0
    InsertResult_68dc00 DoInsertValue(const Value_68dc00& value, TrueType_68dc00);
};

// @ 0x0068dc00
InsertResult_68dc00 Tree_68dc00::DoInsertValue(const Value_68dc00& value, TrueType_68dc00)
{
    Node_68dc00* pCurrent = (Node_68dc00*)mAnchor.mpNodeParent;
    Node_68dc00* pLowerBound = (Node_68dc00*)&mAnchor;
    Node_68dc00* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_68dc00*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_68dc00*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_68dc00*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_68dc00*)RBTreeDecrement_68dc00(pLowerBound);
        else {
            const Iterator_68dc00 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_68dc00(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_68dc00 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_68dc00(itResult, true);
    }

    return InsertResult_68dc00(Iterator_68dc00(pLowerBound), false);
}
