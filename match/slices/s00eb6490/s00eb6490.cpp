// Slice s00eb6490 (batch hk2 slice 1).  One function: 00eb66c0, 152 bytes, __thiscall, no args.
// Clears an EASTL-style rbtree (3.02 layout: anchor at tree+4, node count at tree+0x14)
// whose node values are object pointers.  Before the nuke, each value gets a notification:
// one virtual call returning a helper object whose two flag fields are set, and one
// virtual call on the value's owned sub-object.  Then the tree is reset to empty.
// 32-bit MSVC 2008 SP1, /O2 /MD /Gy /EHsc /TP.

struct RbNodeBase {            // EASTL rbtree_node_base (16 bytes)
    RbNodeBase* mpNodeRight;   // +0
    RbNodeBase* mpNodeLeft;    // +4
    RbNodeBase* mpNodeParent;  // +8
    char        mColor;        // +0xc
};

struct RbNode : RbNodeBase {   // tree node: value at +0x10
    struct ObjA* mValue;
};

// Tree object (owner+0x2f0).  Declared only; defined in the original.
struct RbTree {
    char      pad0[4];
    RbNodeBase mAnchor;        // +4 (= owner+0x2f4)
    unsigned int mnNodeCount;  // +0x14
    void DoNukeSubtree(RbNodeBase* p);
};

RbNodeBase* RBTreeIncrement(RbNodeBase* p);   // eastl::RBTreeIncrement, __cdecl

struct Sub {                   // object at Inner+0xb54
    char pad0[0x64];
    unsigned char mFlag64;     // +0x64
};

struct Inner {                 // returned by ObjA slot 3
    char  pad0[0xb54];
    Sub*  mpSub;               // +0xb54
    char  pad1[0xf90 - 0xb58];
    unsigned char mFlagF90;    // +0xf90
};

struct Ctrl {                  // object at ObjA+0x14
    virtual void c0();
    virtual void c1();
    virtual void c2();
    virtual void c3();
    virtual void c4(int flag); // slot +0x10
};

struct ObjA {                  // tree value
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual Inner* v3(unsigned int id);  // slot +0xc
    virtual void v4();
    char  pad0[0x14 - 4];
    Ctrl* mpCtrl;              // +0x14
};

struct Owner {
    char   pad0[0x2f0];
    RbTree mTree;              // +0x2f0
    void ClearItems();
};

// 00eb66c0
void Owner::ClearItems() {
    RbNodeBase* node = mTree.mAnchor.mpNodeLeft;
    if (node != &mTree.mAnchor) {
        do {
            ObjA* value = static_cast<RbNode*>(node)->mValue;
            if (value) {
                Inner* in = value->v3(0xce9f6639u);
                if (in) {
                    in->mpSub->mFlag64 = 1;
                    in->mFlagF90 = 1;
                }
            }
            if (value->mpCtrl)
                value->mpCtrl->c4(1);
            node = RBTreeIncrement(node);
        } while (node != &mTree.mAnchor);
    }
    RbNodeBase* root = mTree.mAnchor.mpNodeParent;
    RbTree* t = &mTree;
    t->DoNukeSubtree(root);
    t->mAnchor.mpNodeLeft = &t->mAnchor;
    t->mAnchor.mpNodeParent = 0;
    t->mAnchor.mColor = 0;
    t->mnNodeCount = 0;
    t->mAnchor.mpNodeRight = &t->mAnchor;
}
