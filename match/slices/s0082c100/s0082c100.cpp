// rbtree::DoInsertValue for unique keys (0x0082c100): walk down to the insertion point; insert (DoInsertValueImpl
// 0x82c080) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_82c100 { RBNodeBase_82c100* mpNodeRight; RBNodeBase_82c100* mpNodeLeft; RBNodeBase_82c100* mpNodeParent; int mColor; };
RBNodeBase_82c100* RBTreeDecrement_82c100(const RBNodeBase_82c100* pNode);   // 0x009215c0

struct Value_82c100 { uint32_t first; };
struct Node_82c100 : RBNodeBase_82c100 {
    Value_82c100 mValue;                         // +0x10
};
struct Iterator_82c100 {
    Node_82c100* mpNode;
    explicit Iterator_82c100(Node_82c100* p) : mpNode(p) {}
};
struct InsertResult_82c100 {
    Iterator_82c100 first;
    bool second;
    InsertResult_82c100(const Iterator_82c100& it, bool b) : first(it), second(b) {}
};
struct TrueType_82c100 {};
struct Tree_82c100 {
    int mCompare;                             // +0x00
    RBNodeBase_82c100 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_82c100 DoInsertValueImpl(Node_82c100* pNodeParent, const Value_82c100& value, bool bForceToLeft);   // 0x0082c080
    InsertResult_82c100 DoInsertValue(const Value_82c100& value, TrueType_82c100);
};

// @ 0x0082c100
InsertResult_82c100 Tree_82c100::DoInsertValue(const Value_82c100& value, TrueType_82c100)
{
    Node_82c100* pCurrent = (Node_82c100*)mAnchor.mpNodeParent;
    Node_82c100* pLowerBound = (Node_82c100*)&mAnchor;
    Node_82c100* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_82c100*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_82c100*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_82c100*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_82c100*)RBTreeDecrement_82c100(pLowerBound);
        else {
            const Iterator_82c100 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_82c100(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_82c100 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_82c100(itResult, true);
    }

    return InsertResult_82c100(Iterator_82c100(pLowerBound), false);
}
