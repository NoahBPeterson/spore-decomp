// rbtree::DoInsertValue for unique keys (0x00d54b80): walk down to the insertion point; insert (DoInsertValueImpl
// 0xd54b00) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_d54b80 { RBNodeBase_d54b80* mpNodeRight; RBNodeBase_d54b80* mpNodeLeft; RBNodeBase_d54b80* mpNodeParent; int mColor; };
RBNodeBase_d54b80* RBTreeDecrement_d54b80(const RBNodeBase_d54b80* pNode);   // 0x009215c0

struct Value_d54b80 { uint32_t first; };
struct Node_d54b80 : RBNodeBase_d54b80 {
    Value_d54b80 mValue;                         // +0x10
};
struct Iterator_d54b80 {
    Node_d54b80* mpNode;
    explicit Iterator_d54b80(Node_d54b80* p) : mpNode(p) {}
};
struct InsertResult_d54b80 {
    Iterator_d54b80 first;
    bool second;
    InsertResult_d54b80(const Iterator_d54b80& it, bool b) : first(it), second(b) {}
};
struct TrueType_d54b80 {};
struct Tree_d54b80 {
    int mCompare;                             // +0x00
    RBNodeBase_d54b80 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_d54b80 DoInsertValueImpl(Node_d54b80* pNodeParent, const Value_d54b80& value, bool bForceToLeft);   // 0x00d54b00
    InsertResult_d54b80 DoInsertValue(const Value_d54b80& value, TrueType_d54b80);
};

// @ 0x00d54b80
InsertResult_d54b80 Tree_d54b80::DoInsertValue(const Value_d54b80& value, TrueType_d54b80)
{
    Node_d54b80* pCurrent = (Node_d54b80*)mAnchor.mpNodeParent;
    Node_d54b80* pLowerBound = (Node_d54b80*)&mAnchor;
    Node_d54b80* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_d54b80*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_d54b80*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_d54b80*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_d54b80*)RBTreeDecrement_d54b80(pLowerBound);
        else {
            const Iterator_d54b80 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_d54b80(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_d54b80 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_d54b80(itResult, true);
    }

    return InsertResult_d54b80(Iterator_d54b80(pLowerBound), false);
}
