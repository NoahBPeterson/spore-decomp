// s00e9e290.cpp -- gold6 batch, worker 25
// Reconstructed from the annotated disassembly + Ghidra decompiles in
// work/match/scratch_s00e9e290_cards.txt.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Every field touched is a named member of cAmbLayer (which is
// SP::Audio::cAmbienceLayerManager); callees are declared-only externals so cl
// emits the masked direct-call relocation instead of inlining a stub.

#include "types.h"

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// Small value types.
// ---------------------------------------------------------------------------
struct cAmbienceTag {
    void*    mpVtbl;   // +0x00  (vtable slot 0, overwritten with a free-list link)
    void*    mpUnk4;   // +0x04
    uint32_t mKey8;    // +0x08  (rbtree key passed to FUN_00e9db10)
};

struct InnerVec {
    void** mpBegin;    // +0x00
    void** mpEnd;      // +0x04
    void** mpCap;      // +0x08
    void DoInsertValue(void** position, cAmbienceTag* const& value);  // 0x00ea9440, thiscall ret 8
};

// ---------------------------------------------------------------------------
// Interfaces reached virtually.  Declaration order == vtable order.
// ---------------------------------------------------------------------------
struct CheatManager {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c(void* arg);
};

// ---------------------------------------------------------------------------
// The id -> tag map (eastl::rbtree).  Lives at cAmbLayer +0x80.
// ---------------------------------------------------------------------------
struct TagMapNode {
    uint8_t       pad00[0x14];
    cAmbienceTag* mpValue;   // +0x14
};

struct TagMap {
    uint32_t mUnk00;     // +0x00
    void*    mAnchor;    // +0x04  (end() sentinel; self-referential)
    void*    mRoot;      // +0x08
    void*    mRootNode;  // +0x0c  (passed to DoNukeSubtree)
    uint8_t  mUnk10;     // +0x10
    uint8_t  pad11[3];
    uint32_t mUnk14;     // +0x14
    void find(void* result, void* key);              // 0x00e5c780
    void DoNukeSubtree(void* node);                  // 0x009a9600
};

// Configuration object released by vtable slot 1 during teardown.
struct Config {
    virtual void s0();
    virtual void Release();                          // vtable slot 1 -> [eax+4]
    virtual void s2();
};

// Anonymous 0x14-byte sub-object at cAmbLayer +0xb0 (has its own destructor).
struct SubObj {
    void* a; void* b; void* c; void* d; void* e;
    void dtor();                                     // 0x00e9ddc0
};

// eastl ResponseCurve: inline buffer begin at +0, capacity at +0x10.
struct RespCurve {
    void*   mBegin;      // +0x00
    void*   pad04[3];
    void*   mCap;        // +0x10
    uint8_t pad14[0x364 - 0x14];
};

// eastl fixed_string inline buffer: begin/end/capacity.
struct FixedStr {
    char* mBegin;        // +0x00
    char* mEnd;          // +0x04
    char* mCap;          // +0x08
};

// ---------------------------------------------------------------------------
// SP::Audio::cAmbienceLayerManager.  Only the members we touch are named.
// ---------------------------------------------------------------------------
class cAmbLayer {
public:
    void*     mpVtbl;             // +0x00
    void*     mpVtbl4;            // +0x04
    void*     mpVtbl8;            // +0x08
    uint8_t   pad0c[4];           // +0x0c
    Config*   mpConfiguration;     // +0x10
    void*     mpAutoMsgHandler;    // +0x14
    uint32_t  mAutoMsg18;          // +0x18
    uint32_t  mAutoMsg1c;          // +0x1c
    uint32_t  mAutoMsg20;          // +0x20
    uint32_t  mAutoMsg24;          // +0x24
    int32_t   mNumCells;           // +0x28
    InnerVec** mMapBegin;          // +0x2c
    InnerVec** mMapEnd;            // +0x30
    InnerVec** mMapCap;            // +0x34
    uint8_t   pad38[8];            // +0x38..+0x3f
    void*     mViewIdxBegin;       // +0x40
    int32_t   mViewIdxEnd;         // +0x44
    int32_t   mViewIdxCap;         // +0x48
    uint8_t   pad4c[8];            // +0x4c..+0x53
    void*     mViewTagsBegin;      // +0x54
    int32_t   mViewTagsEnd;        // +0x58
    int32_t   mViewTagsCap;        // +0x5c
    uint8_t   pad60[8];            // +0x60..+0x67
    void*     mDynTagsBegin;       // +0x68
    int32_t   mDynTagsEnd;         // +0x6c
    int32_t   mDynTagsCap;         // +0x70
    uint8_t   pad74[0xc];          // +0x74..+0x7f
    TagMap    mIdToTagMap;         // +0x80..+0x97
    uint8_t   pad98[4];            // +0x98..+0x9b
    float     mOriginX;            // +0x9c
    float     mOriginY;            // +0xa0
    float     mOriginZ;            // +0xa4
    float     mRadius;             // +0xa8
    uint8_t   mbSphereChanged;     // +0xac
    uint8_t   padad[3];
    SubObj    mSubB0;              // +0xb0..+0xc3  (has a destructor)
    void*     mpC4;                // +0xc4
    uint8_t   padc8[0x24];         // +0xc8..+0xeb
    RespCurve mCurveA;             // +0xec
    RespCurve mCurveB;             // +0x450
    uint8_t   pad7b4[8];           // +0x7b4..+0x7bb
    FixedStr  mStr;                // +0x7bc
    uint8_t   pad7c8[4];           // +0x7c8..+0x7cb
    uint32_t  mFlags;              // +0x7cc

    // methods of this class (declaration-only; call sites are masked relocs)
    void FUN_00e9e220();                    // 0x00e9e220
    void FUN_00e9dcc0(cAmbienceTag* t);     // 0x00e9dcc0

    // functions reconstructed in this slice
    bool Shutdown();
    bool RemoveTag(uint tag);
    void DestroyCubeMap();
    bool FUN_00e9ed00(cAmbienceTag* p);
    void Destroy();                         // 0x00e9e3a0
};

// ---------------------------------------------------------------------------
// Undefined external callees (direct calls stay direct + masked).
// ---------------------------------------------------------------------------
CheatManager* __cdecl SP_CheatManager();                     // 0x0067de20
void          __cdecl operator_delete_array(void*);           // 0x00f47380
void          __cdecl EA_Messaging_RemoveHandler(void*, uint, uint, uint, uint); // 0x00571db0
int           __stdcall FUN_00e9db10(void* key);              // 0x00e9db10

extern uint32_t gAmbCheatArg;    // 0x01487138  (arg to CheatManager::s1c)
extern cAmbienceTag* gTagFreeListHead;   // 0x016c6a04

// vtable addresses written during teardown; declared extern so the stores stay
// as masked `mov dword ptr [this+N], offset <vtbl>` relocations.
extern void* g_vtbl_01487150;
extern void* g_vtbl_01487140;
extern void* g_vtbl_0148713c;
extern void* g_vtbl_013eb394;
extern void* g_vtbl_013ef094;

// ===========================================================================
// 0x00e9e290 - SP::Audio::cAmbienceLayerManager::Shutdown
// ===========================================================================
// @ 0x00e9e290
bool cAmbLayer::Shutdown() {
    mFlags |= 1;
    CheatManager* cm = SP_CheatManager();
    if (cm != 0) {
        cm->s1c(&gAmbCheatArg);
    }
    void* h = mpAutoMsgHandler;
    if (h != 0) {
        mpAutoMsgHandler = 0;
        EA_Messaging_RemoveHandler(h, mAutoMsg18, mAutoMsg1c, mAutoMsg20, mAutoMsg24);
    }
    FUN_00e9e220();
    return false;
}

// ===========================================================================
// 0x00e9e2f0 - SP::Audio::cAmbienceLayerManager::RemoveTag
// ===========================================================================
// @ 0x00e9e2f0
bool cAmbLayer::RemoveTag(uint tag) {
    void* it;
    mIdToTagMap.find(&it, &tag);
    if (it == &mIdToTagMap.mAnchor) {
        return false;
    }
    cAmbienceTag* t = ((TagMapNode*)it)->mpValue;
    if (t == 0) {
        return false;
    }
    FUN_00e9dcc0(t);
    t->mpVtbl = gTagFreeListHead;
    gTagFreeListHead = t;
    return true;
}

// ===========================================================================
// 0x00e9e350 - SP::Audio::cAmbienceLayerManager::DestroyCubeMap
// ===========================================================================
// @ 0x00e9e350
void cAmbLayer::DestroyCubeMap() {
    int n = (int)(mMapEnd - mMapBegin);
    for (int i = 0; i < n; i++) {
        InnerVec* e = mMapBegin[i];
        if (e != 0) {
            if (e->mpBegin != 0) {
                operator_delete_array(e->mpBegin);
            }
            operator_delete_array(e);
        }
        mMapBegin[i] = 0;
    }
}

// ===========================================================================
// 0x00e9ed00 - insert an ambience tag into its cell's vector
// ===========================================================================
// @ 0x00e9ed00
bool cAmbLayer::FUN_00e9ed00(cAmbienceTag* p) {
    if (p == 0) {
        return false;
    }
    int idx = FUN_00e9db10(&p->mKey8);
    InnerVec* v = mMapBegin[idx];
    void** end = v->mpEnd;
    void** it = v->mpBegin;
    int n = (int)(end - it);
    void** w = it;
    for (int k = 0; k < n; k++, w++) {
        if (*w == 0) {
            it[k] = p;
            return true;
        }
    }
    void** cur = v->mpEnd;
    if (cur < v->mpCap) {
        v->mpEnd = cur + 1;
        if (cur != 0) {
            *cur = p;
        }
    } else {
        v->DoInsertValue(cur, p);
    }
    return true;
}

// ===========================================================================
// 0x00e9e3a0 - teardown: reset vtables, free owned buffers, release config
// ===========================================================================
// @ 0x00e9e3a0
void cAmbLayer::Destroy() {
    mpVtbl  = &g_vtbl_01487150;
    mpVtbl4 = &g_vtbl_01487140;
    mpVtbl8 = &g_vtbl_0148713c;
    if ((mStr.mCap - mStr.mBegin) > 1 && mStr.mBegin != 0)
        operator_delete_array(mStr.mBegin);
    if (mCurveB.mBegin != 0 && mCurveB.mBegin != mCurveB.mCap)
        operator_delete_array(mCurveB.mBegin);
    if (mCurveA.mBegin != 0 && mCurveA.mBegin != mCurveA.mCap)
        operator_delete_array(mCurveA.mBegin);
    if (mpC4 != 0)
        operator_delete_array(mpC4);
    mSubB0.dtor();
    mIdToTagMap.DoNukeSubtree(mIdToTagMap.mRootNode);
    if (mDynTagsBegin != 0)
        operator_delete_array(mDynTagsBegin);
    if (mViewTagsBegin != 0)
        operator_delete_array(mViewTagsBegin);
    if (mViewIdxBegin != 0)
        operator_delete_array(mViewIdxBegin);
    if (mMapBegin != 0)
        operator_delete_array(mMapBegin);
    if (mpAutoMsgHandler != 0) {
        void* h = mpAutoMsgHandler;
        mpAutoMsgHandler = 0;
        EA_Messaging_RemoveHandler(h, mAutoMsg18, mAutoMsg1c, mAutoMsg20, mAutoMsg24);
    }
    if (mpConfiguration != 0)
        mpConfiguration->Release();
    mpVtbl4 = &g_vtbl_013eb394;
    mpVtbl8 = &g_vtbl_013ef094;
}