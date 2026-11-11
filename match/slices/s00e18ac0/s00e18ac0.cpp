// Flags: /O2 /MD /Gy /TP
// Walks the tree anchored at +0x3c. Each node's object gets the first argument
// through virtual slot 0x18. When +0x58 is set, it is updated with the second.
#include "types.h"

struct Thing {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v18(int value); // slot 0x18
};

struct Node {
    Node* mpRight;  // +0x00
    Node* mpLeft;   // +0x04
    Node* mpParent; // +0x08
    char mColor;    // +0x0c
    char mPad0d[3];
    int mKey;       // +0x10
    Thing* mpObj;   // +0x14
};

Node* RBTreeIncrement(Node* node); // 0x00921580

struct MgrVec {
    void update(int value); // 0x00e30990
};

struct cTreeOwner {
    char mPad00[0x3c];
    Node mAnchor; // +0x3c
    char mPad54[0x58 - 0x3c - sizeof(Node)];
    MgrVec* mpMgr; // +0x58
    void FUN_00e18ac0(int value, int updateArg);
};

// @ 0x00e18ac0
void cTreeOwner::FUN_00e18ac0(int value, int updateArg)
{
    if (mpMgr)
        mpMgr->update(updateArg);
    Node* n = mAnchor.mpLeft;
    Node* end = &mAnchor;
    while (n != end) {
        n->mpObj->v18(value);
        n = RBTreeIncrement(n);
    }
}
