// rbtree::DoInsertValue for unique keys (0x00ed2b30): walk down to the insertion point; insert (DoInsertValueImpl
// 0xed2a50) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_ed2b30 { RBNodeBase_ed2b30* mpNodeRight; RBNodeBase_ed2b30* mpNodeLeft; RBNodeBase_ed2b30* mpNodeParent; int mColor; };
RBNodeBase_ed2b30* RBTreeDecrement_ed2b30(const RBNodeBase_ed2b30* pNode);   // 0x009215c0

struct Value_ed2b30 { uint32_t first; };
struct Node_ed2b30 : RBNodeBase_ed2b30 {
    Value_ed2b30 mValue;                         // +0x10
};
struct Iterator_ed2b30 {
    Node_ed2b30* mpNode;
    explicit Iterator_ed2b30(Node_ed2b30* p) : mpNode(p) {}
};
struct InsertResult_ed2b30 {
    Iterator_ed2b30 first;
    bool second;
    InsertResult_ed2b30(const Iterator_ed2b30& it, bool b) : first(it), second(b) {}
};
struct TrueType_ed2b30 {};
struct Tree_ed2b30 {
    int mCompare;                             // +0x00
    RBNodeBase_ed2b30 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_ed2b30 DoInsertValueImpl(Node_ed2b30* pNodeParent, const Value_ed2b30& value, bool bForceToLeft);   // 0x00ed2a50
    InsertResult_ed2b30 DoInsertValue(const Value_ed2b30& value, TrueType_ed2b30);
};

// @ 0x00ed2b30
InsertResult_ed2b30 Tree_ed2b30::DoInsertValue(const Value_ed2b30& value, TrueType_ed2b30)
{
    Node_ed2b30* pCurrent = (Node_ed2b30*)mAnchor.mpNodeParent;
    Node_ed2b30* pLowerBound = (Node_ed2b30*)&mAnchor;
    Node_ed2b30* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_ed2b30*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_ed2b30*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_ed2b30*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_ed2b30*)RBTreeDecrement_ed2b30(pLowerBound);
        else {
            const Iterator_ed2b30 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_ed2b30(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_ed2b30 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_ed2b30(itResult, true);
    }

    return InsertResult_ed2b30(Iterator_ed2b30(pLowerBound), false);
}
