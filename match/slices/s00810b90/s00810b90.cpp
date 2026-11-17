// rbtree::DoInsertValue for unique keys (0x00810b90): walk down to the insertion point; insert (DoInsertValueImpl
// 0x810af0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_810b90 { RBNodeBase_810b90* mpNodeRight; RBNodeBase_810b90* mpNodeLeft; RBNodeBase_810b90* mpNodeParent; int mColor; };
RBNodeBase_810b90* RBTreeDecrement_810b90(const RBNodeBase_810b90* pNode);   // 0x009215c0

struct Value_810b90 { uint32_t first; };
struct Node_810b90 : RBNodeBase_810b90 {
    Value_810b90 mValue;                         // +0x10
};
struct Iterator_810b90 {
    Node_810b90* mpNode;
    explicit Iterator_810b90(Node_810b90* p) : mpNode(p) {}
};
struct InsertResult_810b90 {
    Iterator_810b90 first;
    bool second;
    InsertResult_810b90(const Iterator_810b90& it, bool b) : first(it), second(b) {}
};
struct TrueType_810b90 {};
struct Tree_810b90 {
    int mCompare;                             // +0x00
    RBNodeBase_810b90 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_810b90 DoInsertValueImpl(Node_810b90* pNodeParent, const Value_810b90& value, bool bForceToLeft);   // 0x00810af0
    InsertResult_810b90 DoInsertValue(const Value_810b90& value, TrueType_810b90);
};

// @ 0x00810b90
InsertResult_810b90 Tree_810b90::DoInsertValue(const Value_810b90& value, TrueType_810b90)
{
    Node_810b90* pCurrent = (Node_810b90*)mAnchor.mpNodeParent;
    Node_810b90* pLowerBound = (Node_810b90*)&mAnchor;
    Node_810b90* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_810b90*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_810b90*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_810b90*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_810b90*)RBTreeDecrement_810b90(pLowerBound);
        else {
            const Iterator_810b90 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_810b90(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_810b90 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_810b90(itResult, true);
    }

    return InsertResult_810b90(Iterator_810b90(pLowerBound), false);
}
