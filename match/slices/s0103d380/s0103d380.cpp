// Slice s0103d380 -- SP::cSPSpaceTrading Gonzago/trading serializers and
// container-reset helpers around 0x0103d380..0x0103df0c:
//   * the rbtree<(u32, cWorld)> deserializer (0103d380),
//   * a fixed_vector<AutoRefCount<cNPCStore>> ReadSTLSequence (0103d4a0),
//   * ConsiderBuyingRareGroup / CreateCommodityFromID (0103d580 / 0103d720),
//   * the palette-page reset helpers (0103d9b0 / 0103dbd0),
//   * ShutdownGonzagoSubsystem and the rbtree/fixed-vector teardown (0103dd20 /
//     0103dd80), the cGonzagoTimer push_back (0103de00) and the rbtree insert
//     helper (0103de50).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (Space trading TU).
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

inline void* operator new(unsigned int, void* p) { return p; }

#define VS(o, off)   (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)  ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1) \
    ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VS(o, off))((void*)(o), (a1), (a2), (a3))
#define FU8(p, off)  (*(u8*)((char*)(p) + (off)))
#define FU32(p, off) (*(u32*)((char*)(p) + (off)))

struct Vector3 { float x, y, z; };

// ---------------------------------------------------------------------------
// eastl rbtree<u32, cWorld> node header.  The tree object is at this+0xa0 in
// cSPSpaceTrading; mpRoot lives at +0xc and the anchor's self-links at +4/+8.
// ---------------------------------------------------------------------------
struct RBTree {
    u32    mField00;      // +0x00
    void*  mAnchorLeft;   // +0x04  (self pointer)
    void*  mAnchorRight;  // +0x08
    void*  mpRoot;        // +0x0c
    u8     mColor;        // +0x10
    u8     mPad11[3];
    u32    mSize;         // +0x14
    void   DoNukeSubtree(void* root);   // 0x009a9600
    u32*   FUN_0103bc40(void* key0, void* key1, u8 flag);  // 0x0103bc40
    void   FUN_00c7f560(void** out, void* key);            // 0x00c7f560
    void   FUN_0103c6b0(void* node, void* key, void* key2, u32 flag);  // 0x0103c6b0
    u32*   FUN_0103de50(u32* key);      // 0x0103de50
};

// ---------------------------------------------------------------------------
// IStream-ish reader whose vtable slots 0x1c / 0x20 / 0x28 drive the
// deserializers, plus the read helpers.
// ---------------------------------------------------------------------------
void FUN_00ae2ed0(void* stream, void* out12);           // 0x00ae2ed0
void ReadInt32(void* stream, void* dst, int n, int flags);  // 0x0093a780

struct cNPCStoreFixedVec {
    void* mpBegin;     // +0
    void* mpEnd;       // +4
    void* mpCapacity;  // +8
    void  clearRange(void* b, void* e);          // 0x0103c4f0
    void  pushSlow(void* pos, void* val);        // 0x0103c550
    void  FUN_00c77b60(u32 count);               // 0x00c77b60
};

// AutoRefCount payload: vtable at +8, AddRef = slot 0, Release = slot 4.
struct RefObj {
    u8    mPad0[8];
    void* mpVtbl;      // +8
};

// ---------------------------------------------------------------------------
// SpVector<Vector3>: mpBegin/mpEnd with erase(first,last).
// ---------------------------------------------------------------------------
struct SpVector3 {
    Vector3* mpBegin;      // +0
    Vector3* mpEnd;        // +4
    Vector3* mpCapacity;   // +8
    Vector3* erase(Vector3* first, Vector3* last);   // 0x0050f740
};

// ---------------------------------------------------------------------------
// fixed_vector<AutoRefCount<cNPCStore>,5,1>: clears a range.
// ---------------------------------------------------------------------------
struct cNPCStoreVec {
    void* mpBegin;     // +0
    void* mpEnd;       // +4
    void* mpCapacity;  // +8
    void  clearRange(void* first, void* last);   // 0x0103c4f0
};

// ---------------------------------------------------------------------------
// cGonzagoTimer is 0x20 bytes with out-of-line ctor/dtor.
// ---------------------------------------------------------------------------
struct cGonzagoTimer {
    u32 mData[8];           // +0x00 .. +0x20
    cGonzagoTimer();        // 0x00b63890
    ~cGonzagoTimer();       // 0x00b638b0
};

void FUN_00bf5420(void* where, cGonzagoTimer* val);   // 0x00bf5420
void FUN_00571db0(void* h, u32 a, u32 b, u32 c, u32 d);  // 0x00571db0 (EA::Messaging::RemoveHandler)

struct cGonzagoTimerVec {
    cGonzagoTimer* mpBegin;     // +0
    cGonzagoTimer* mpEnd;       // +4
    cGonzagoTimer* mpCapacity;  // +8
    void insert(cGonzagoTimer* pos, cGonzagoTimer* val);  // 0x00bf5420
    void push_back();           // 0x0103de00
};

// ---------------------------------------------------------------------------
// cSPSpaceTrading: the slice of the object touched by ShutdownGonzagoSubsystem
// / the reset helpers.  Only the referenced member offsets are modelled.
// ---------------------------------------------------------------------------
struct cSPSpaceTrading {
    u8             m00[0x20];        // +0x000
    SpVector3      mV20;             // +0x020
    u8             m2c[0x08];        // +0x02c
    SpVector3      mV34;             // +0x034
    u8             m40[0x08];        // +0x040
    cNPCStoreVec   m48;              // +0x048
    u8             m54[0x4c];        // +0x054
    RBTree         mTree;            // +0x0a0
    u8             mB8[0x18];        // +0x0b8
    void*          mpMsgD0;          // +0x0d0
    u32            mD4;              // +0x0d4
    u32            mD8;              // +0x0d8
    u32            mDC;              // +0x0dc
    u32            mE0;              // +0x0e0

    void ShutdownGonzagoSubsystem();          // 0x0103dd20
    void FUN_0103dd80();                      // 0x0103dd80
};

// ---------------------------------------------------------------------------
// The palette-page host reached by 0x0103dbd0: two sp_ref_vector<AutoRefCount>
// page lists plus a vector of page-groups whose property key is looked up.
// ---------------------------------------------------------------------------
struct SpRefVec {
    void** mpBegin;      // +0
    void** mpEnd;        // +4
    void** mpCapacity;   // +8
    void** erase(void** first, void** last);   // 0x005c2170
};

struct cPaletteItem {
    u8     m00[0x10];
    u32    m10;          // +0x10
    u8     m14[0x1c];
    u32    m30;          // +0x30
};

struct cPaletteGroup {
    u8     m00[0x10];
    u32    m10;          // +0x10
    u8     m14[0x20];    // +0x14 .. +0x34
    void** mpBegin34;    // +0x34
    void** mpEnd38;      // +0x38
};

struct cPaletteHost {
    u8         m00[0x48];
    void**     mVec48Begin;   // +0x48
    void**     mVec48End;     // +0x4c
    u8         m50[0x28];     // +0x50 .. +0x74
    SpRefVec   mV74;          // +0x74
    u8         m80[0x08];     // +0x80 .. +0x88
    SpRefVec   mV88;          // +0x88
    void FUN_0103dbd0(u8 param_2);   // 0x0103dbd0
};

void GetPropertyAsKey(u32 prop, u32 tag, void* out);   // 0x006a1250

struct RBNode {
    u32 m00;   // +0x00
    u32 m04;   // +0x04
    u32 m08;   // +0x08
    u32 m0c;   // +0x0c
    u32 m10;   // +0x10
    u32 m14;   // +0x14
    u32 m18;   // +0x18
};

// ---------------------------------------------------------------------------
// 0x0103dd20 -- ShutdownGonzagoSubsystem: clears the two SpVector<Vector3>,
// the fixed NPC-store vector, and resets the rare-group rbtree.
// ---------------------------------------------------------------------------
// @ 0x0103dd20
void cSPSpaceTrading::ShutdownGonzagoSubsystem()
{
    mV34.erase(mV34.mpBegin, mV34.mpEnd);
    mV20.erase(mV20.mpBegin, mV20.mpEnd);
    m48.clearRange(m48.mpBegin, m48.mpEnd);
    RBTree* t = &mTree;
    t->DoNukeSubtree(t->mpRoot);
    t->mAnchorLeft  = &t->mAnchorLeft;
    t->mAnchorRight = &t->mAnchorLeft;
    t->mpRoot       = 0;
    t->mColor       = 0;
    t->mSize        = 0;
}

// ---------------------------------------------------------------------------
// 0x0103dd80 -- rbtree + fixed-vector teardown plus an EA::Messaging handler
// unregister.
// ---------------------------------------------------------------------------
// @ 0x0103dd80
void cSPSpaceTrading::FUN_0103dd80()
{
    m48.clearRange(m48.mpBegin, m48.mpEnd);
    RBTree* t = &mTree;
    t->DoNukeSubtree(t->mpRoot);
    t->mAnchorLeft  = &t->mAnchorLeft;
    t->mAnchorRight = &t->mAnchorLeft;
    t->mpRoot       = 0;
    t->mColor       = 0;
    t->mSize        = 0;

    void* h = mpMsgD0;
    if (h != 0) {
        mpMsgD0 = 0;
        FUN_00571db0(h, mD4, mD8, mDC, mE0);
    }
}

// ---------------------------------------------------------------------------
// 0x0103de00 -- fixed_vector<cGonzagoTimer>::push_back.
// ---------------------------------------------------------------------------
// @ 0x0103de00
void cGonzagoTimerVec::push_back()
{
    cGonzagoTimer* pEnd = mpEnd;
    if (pEnd < mpCapacity) {
        mpEnd = pEnd + 1;
        if (pEnd != 0)
            new (pEnd) cGonzagoTimer();
    } else {
        cGonzagoTimer tmp;
        insert(mpEnd, &tmp);
    }
}

// ---------------------------------------------------------------------------
// 0x0103d380 -- rbtree<u32,cWorld> deserializer: nuke the tree, read a count,
// then per element read a 12-byte key (FUN_00ae2ed0) plus a u32 and link it in.
// ---------------------------------------------------------------------------
// @ 0x0103d380
void FUN_0103d380(void* stream, RBTree* tree)
{
    tree->DoNukeSubtree(tree->mpRoot);
    tree->mAnchorLeft  = &tree->mAnchorLeft;
    tree->mAnchorRight = &tree->mAnchorLeft;
    tree->mpRoot       = 0;
    tree->mColor       = 0;
    tree->mSize        = 0;

    u32 count = 0;
    void* reader = (void*)VC0(void*, stream, 0x20);
    ReadInt32((void*)VC0(void*, reader, 0x18), &count, 1, 0);

    u32 i = 0;
    if (count != 0) {
        do {
            u32 key[3];
            key[0] = 0; key[1] = 0; key[2] = 0;
            FUN_00ae2ed0(stream, key);
            VC0(void, stream, 0x1c);

            u32 val = 0;
            void* reader2 = (void*)VC0(void*, stream, 0x20);
            ReadInt32((void*)VC0(void*, reader2, 0x18), &val, 1, 0);
            VC0(void, stream, 0x1c);

            u32 key2[3];
            key2[0] = key[0]; key2[1] = key[1]; key2[2] = key[2];
            u8  flag = 0;
            u32* node = tree->FUN_0103bc40(key, key2, flag);
            if (flag == 0)
                *(u32*)((char*)node + 0x1c) = val;
            i++;
        } while (i < count);
    }
    VC0(void, stream, 0x1c);
}

// ---------------------------------------------------------------------------
// 0x0103d4a0 -- fixed_vector<AutoRefCount<cNPCStore>,5,1> deserializer: clear,
// read count, read n refcounted elements (vtable slot 0x28) and append them.
// ---------------------------------------------------------------------------
// @ 0x0103d4a0
void FUN_0103d4a0(void* stream, cNPCStoreFixedVec* vec)
{
    vec->clearRange(vec->mpBegin, vec->mpEnd);

    u32 count = 0;
    void* reader = (void*)VC0(void*, stream, 0x20);
    void* src = (void*)VC0(void*, reader, 0x18);
    ReadInt32(src, &count, 1, 0);
    vec->FUN_00c77b60(count);

    for (u32 i = 0; i < count; i++) {
        RefObj* val = 0;
        VC3(void, stream, 0x28, u32, 0x5b82ef9u, void**, (void**)&val, int, 0);

        void** pEnd = (void**)vec->mpEnd;
        if ((char*)pEnd < (char*)vec->mpCapacity) {
            vec->mpEnd = (char*)pEnd + 4;
            if (pEnd != 0) {
                *pEnd = val;
                if (val != 0)
                    VC0(void, (char*)val + 8, 0);
            }
        } else {
            vec->pushSlow(vec->mpEnd, &val);
        }

        if (val != 0)
            VC0(void, (char*)val + 8, 4);
    }
    VC0(void, stream, 0x1c);
}

// ---------------------------------------------------------------------------
// 0x0103dbd0 -- drop both palette-page lists, then (if param_2) walk every page
// group's items and clear the ones whose property key is a crafted item.
// ---------------------------------------------------------------------------
// @ 0x0103dbd0
void cPaletteHost::FUN_0103dbd0(u8 param_2)
{
    mV74.erase(mV74.mpBegin, mV74.mpEnd);
    mV88.erase(mV88.mpBegin, mV88.mpEnd);

    int n = (char*)mVec48End - (char*)mVec48Begin;
    if (param_2 != 0 && (n & 0xfffffffc) > 0) {
        for (int i = 0; i < n >> 2; i++) {
            cPaletteGroup* g = (cPaletteGroup*)mVec48Begin[i];
            int m = ((char*)g->mpEnd38 - (char*)g->mpBegin34) >> 2;
            for (int j = 0; j < m; j++) {
                u32 key[3];
                key[0] = 0; key[1] = 0; key[2] = 0;
                cPaletteItem* it = (cPaletteItem*)g->mpBegin34[j];
                GetPropertyAsKey(it->m30, 0x34f1a4fu, key);
                if (key[0] == 0x7ecbe6f5u || key[0] == 0xb978c47au)
                    it->m10 = 0;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 0x0103de50 -- rbtree insert-with-hint: locate the first node >= key and,
// unless the existing node already orders before it, splice a new node in.
// ---------------------------------------------------------------------------
// @ 0x0103de50
u32* RBTree::FUN_0103de50(u32* key)
{
    void* node = 0;
    FUN_00c7f560(&node, key);
    if ((char*)node != (char*)&mAnchorLeft) {
        RBNode* nd = (RBNode*)node;
        bool lt;
        if (key[0] != nd->m10)
            lt = key[0] < nd->m10;
        else if (key[2] != nd->m18)
            lt = key[2] < nd->m18;
        else
            lt = key[1] < nd->m14;
        if (!lt)
            return (u32*)node + 7;
    }
    u32 local[3];
    local[0] = key[0]; local[1] = key[1]; local[2] = key[2];
    FUN_0103c6b0(node, key, local, 0);
    return (u32*)node + 7;
}