// rbtree::DoInsertValue for unique keys (0x00e64640): walk down to the insertion point; insert (DoInsertValueImpl
// 0xe645b0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_e64640 { RBNodeBase_e64640* mpNodeRight; RBNodeBase_e64640* mpNodeLeft; RBNodeBase_e64640* mpNodeParent; int mColor; };
RBNodeBase_e64640* RBTreeDecrement_e64640(const RBNodeBase_e64640* pNode);   // 0x009215c0

struct Value_e64640 { int32_t first; };
struct Node_e64640 : RBNodeBase_e64640 {
    Value_e64640 mValue;                         // +0x10
};
struct Iterator_e64640 {
    Node_e64640* mpNode;
    explicit Iterator_e64640(Node_e64640* p) : mpNode(p) {}
};
struct InsertResult_e64640 {
    Iterator_e64640 first;
    bool second;
    InsertResult_e64640(const Iterator_e64640& it, bool b) : first(it), second(b) {}
};
struct TrueType_e64640 {};
struct Tree_e64640 {
    int mCompare;                             // +0x00
    RBNodeBase_e64640 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_e64640 DoInsertValueImpl(Node_e64640* pNodeParent, const Value_e64640& value, bool bForceToLeft);   // 0x00e645b0
    InsertResult_e64640 DoInsertValue(const Value_e64640& value, TrueType_e64640);
};

// @ 0x00e64640
InsertResult_e64640 Tree_e64640::DoInsertValue(const Value_e64640& value, TrueType_e64640)
{
    Node_e64640* pCurrent = (Node_e64640*)mAnchor.mpNodeParent;
    Node_e64640* pLowerBound = (Node_e64640*)&mAnchor;
    Node_e64640* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_e64640*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_e64640*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_e64640*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_e64640*)RBTreeDecrement_e64640(pLowerBound);
        else {
            const Iterator_e64640 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_e64640(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_e64640 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_e64640(itResult, true);
    }

    return InsertResult_e64640(Iterator_e64640(pLowerBound), false);
}
