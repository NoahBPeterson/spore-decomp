// rbtree::DoInsertValue for unique keys (0x00e2c200): walk down to the insertion point; insert (DoInsertValueImpl
// 0xe2b6c0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_e2c200 { RBNodeBase_e2c200* mpNodeRight; RBNodeBase_e2c200* mpNodeLeft; RBNodeBase_e2c200* mpNodeParent; int mColor; };
RBNodeBase_e2c200* RBTreeDecrement_e2c200(const RBNodeBase_e2c200* pNode);   // 0x009215c0

struct Value_e2c200 { uint32_t first; };
struct Node_e2c200 : RBNodeBase_e2c200 {
    Value_e2c200 mValue;                         // +0x10
};
struct Iterator_e2c200 {
    Node_e2c200* mpNode;
    explicit Iterator_e2c200(Node_e2c200* p) : mpNode(p) {}
};
struct InsertResult_e2c200 {
    Iterator_e2c200 first;
    bool second;
    InsertResult_e2c200(const Iterator_e2c200& it, bool b) : first(it), second(b) {}
};
struct TrueType_e2c200 {};
struct Tree_e2c200 {
    int mCompare;                             // +0x00
    RBNodeBase_e2c200 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_e2c200 DoInsertValueImpl(Node_e2c200* pNodeParent, const Value_e2c200& value, bool bForceToLeft);   // 0x00e2b6c0
    InsertResult_e2c200 DoInsertValue(const Value_e2c200& value, TrueType_e2c200);
};

// @ 0x00e2c200
InsertResult_e2c200 Tree_e2c200::DoInsertValue(const Value_e2c200& value, TrueType_e2c200)
{
    Node_e2c200* pCurrent = (Node_e2c200*)mAnchor.mpNodeParent;
    Node_e2c200* pLowerBound = (Node_e2c200*)&mAnchor;
    Node_e2c200* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_e2c200*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_e2c200*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_e2c200*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_e2c200*)RBTreeDecrement_e2c200(pLowerBound);
        else {
            const Iterator_e2c200 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_e2c200(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_e2c200 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_e2c200(itResult, true);
    }

    return InsertResult_e2c200(Iterator_e2c200(pLowerBound), false);
}
