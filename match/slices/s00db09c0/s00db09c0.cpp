// Slice s00db09c0: the "TribeEat" behaviour-tree task objective / locomotion
// setup step (0x00db09c0..0x00db0b76).
//
// The task state block is the last stack argument.  It starts with the order
// phase, then four reference-counted slots (released at the end), a spot value
// and a few order-specific fields used by the sibling task functions.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include <stddef.h>

typedef unsigned int uint32_t;

struct IRef {
    virtual void v00();          // +0x00
    virtual void Release();      // +0x04
};

// Slot +0x1c is used for the +0x14 state holder (a different smart pointer).
struct IRef1c {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void Release();      // +0x1c
};

struct Spatial {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsBundle();     // +0x58
};

struct Tribe {
    void __thiscall FUN_00c97d40(int a, IRef* b);   // 0x00c97d40
    void __thiscall FindSpot(int type, int spot);   // 0x00c98750
};

struct AnimNode {
    char  pad00[8];
    float mf08;                  // +0x08 duration
    char  pad0c[0x2c - 0x0c];
    int   mWho;                  // +0x2c
};

struct AnimCtlSub {
    AnimNode* __thiscall Play(int a, int flags);                         // 0x00bc96a0
    void __thiscall Stim(int a, int flags, float f, int who);            // 0x00bc97f0
};

struct AnimPool;

struct AnimCtl {
    char       pad00[0x600];     // +0x08 is the behaviour object AnimCtlSub
    AnimPool*  mpPool;           // +0x600
    void __thiscall FUN_00bcb430();                                       // 0x00bcb430
};

struct PoolEntry {
    unsigned char mbActive;      // +0x00
    char   pad04[3];
    IRef*  mpObj;                // +0x04
    char   pad08[4];             // stride 0xc
};

// Behaviour node embedded in the pool at +0x1a4.
struct PoolNode {
    char   pad00[0x18];
    int    miCount;              // +0x18
    char   pad1c[0x28 - 0x1c];
    void*  mp28;                 // +0x28
    IRef*  mp2c;                 // +0x2c
    IRef*  mp30;                 // +0x30
};

struct AnimPool {
    char       pad00[0x10];
    int        mi10;             // +0x10
    char       pad14[0x18 - 0x14];
    uint32_t   mi18;             // +0x18
    char       pad1c[0x20 - 0x1c];
    PoolEntry  mEntries;         // +0x20, inline array of mi18 entries
    char       pad2c[0x1a4 - 0x20 - sizeof(PoolEntry)];
    PoolNode   mNode;            // +0x1a4
    PoolNode* GetNode() { return &mNode; }
    void* __thiscall FUN_00bc9b10();                                      // 0x00bc9b10
};

struct Manager {
    void __thiscall FUN_00bc2180(void* a);                                // 0x00bc2180
};

struct Strategy {
    char  pad00[0x1c8];
    Manager* mpMgr;              // +0x1c8
};
Strategy* __cdecl TribeModeStrategy_Instance();    // 0x00cd40b0

struct EatState {
    int     mPhase;              // +0x00
    IRef*   mpOwner;             // +0x04
    IRef*   mpTarget;            // +0x08
    IRef*   mp0c;                // +0x0c
    IRef*   mp10;                // +0x10
    IRef1c* mp14;                // +0x14
    char    pad18[0x24 - 0x18];
    int     mSpot;               // +0x24
};

struct Citizen {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80();
    virtual void vf84(int a, int b, int c);       // +0x84

    void __thiscall UpdateLocomotion(int a);      // 0x00c14750
    bool __thiscall FUN_00c0c120();               // 0x00c0c120
    void __thiscall SetSprinting(int a);          // 0x00c1ad10
    Tribe* __thiscall GetTribe();                 // 0x00c22f50

    char      pad04[0xc0 - 0x04];
    Spatial   mLoco;              // +0xc0
    char      padc4[0xb4c - 0xc0 - sizeof(Spatial)];
    AnimCtl*  mpAnim;             // +0xb4c
};

// @ 0x00db09c0
// Task objective: cancel the current locomotion, notify the citizen's base,
// pick a spot for the order phase, retarget every other citizen's idle
// stimulus at the freshly played animation, then drop the order references.
void __cdecl FUN_00db09c0(Citizen* c, int, int, int, int, EatState* st)
{
    c->UpdateLocomotion(0);
    c->vf84(0, 0, 0);

    if (st->mPhase == 4) {
        c->GetTribe()->FUN_00c97d40(0xd, (IRef*)c);
    } else if (st->mPhase == 5) {
        c->GetTribe()->FindSpot(0xd, st->mSpot);
    } else {
        if (((Spatial*)((char*)c + 0xc0))->IsBundle())
            ((Tribe*)st->mpTarget)->FindSpot(0xd, st->mSpot);
    }

    AnimPool* pool = c->mpAnim->mpPool;
    if (pool != 0) {
        AnimNode* anim = ((AnimCtlSub*)((char*)c->mpAnim + 8))->Play(0, 0x80);
        if (anim != 0) {
            // The pool keeps its entries in the inline array at +0x20 (stride 0xc),
            // and every entry but this citizen's own is retargeted at the new clip.
            for (uint32_t i = 0; i < pool->mi18; i++) {
                PoolEntry* e = (PoolEntry*)((char*)&pool->mEntries + i * 0xc);
                if (e->mbActive) {
                    IRef* obj = e->mpObj;
                    if (obj != (IRef*)c) {
                        AnimCtl* other = *(AnimCtl**)((char*)obj + 0xb4c);
                        ((AnimCtlSub*)((char*)other + 8))->Stim(
                            0, 0x80, anim->mf08, anim->mWho);
                    }
                }
            }
        }

        PoolNode* node = pool->GetNode();
        if ((void*)c == pool->FUN_00bc9b10()) {
            // The manager is reached through a reference to the strategy's
            // pointer member: that keeps the original's "form the member
            // address, then load the manager" sequence.
            Manager*& mgr = TribeModeStrategy_Instance()->mpMgr;
            mgr->FUN_00bc2180(node->mp28);
            node->mp28 = 0;
        }

        if (st->mPhase == 0x12)
            node->miCount--;

        if (pool->mi10 == 1) {
            if (node != 0) {
                IRef* a = node->mp30;
                if (a != 0)
                    a->Release();
                IRef* b = node->mp2c;
                if (b != 0)
                    b->Release();
            }
        }
        c->mpAnim->FUN_00bcb430();
    }

    if (c->FUN_00c0c120())
        c->SetSprinting(0);

    IRef1c* p14 = st->mp14;
    if (p14 != 0)
        p14->Release();
    IRef* p10 = st->mp10;
    if (p10 != 0)
        p10->Release();
    IRef* p0c = st->mp0c;
    if (p0c != 0)
        p0c->Release();
    IRef* pTarget = st->mpTarget;
    if (pTarget != 0)
        pTarget->Release();
    IRef* pOwner = st->mpOwner;
    if (pOwner != 0)
        pOwner->Release();
}
