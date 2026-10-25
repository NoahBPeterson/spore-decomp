// src/game/SPGonzago/SPAudioAmbienceLayerManager.cpp -- migrated from slice(s) s00e9fca0, s00e9e290 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioAmbienceLayerManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern uint32_t gAmbCheatArg;    // 0x01487138  (arg to CheatManager::s1c)
extern void* g_vtbl_01487150;
extern void* g_vtbl_01487140;
extern void* g_vtbl_0148713c;
extern void* g_vtbl_013eb394;
extern void* g_vtbl_013ef094;

// ---- items of slice s00e9e290 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
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
struct Config {
    virtual void s0();
    virtual void Release();                          // vtable slot 1 -> [eax+4]
    virtual void s2();
};
struct SubObj {
    void* a; void* b; void* c; void* d; void* e;
    void dtor();                                     // 0x00e9ddc0
};
struct RespCurve {
    void*   mBegin;      // +0x00
    void*   pad04[3];
    void*   mCap;        // +0x10
    uint8_t pad14[0x364 - 0x14];
};
struct FixedStr {
    char* mBegin;        // +0x00
    char* mEnd;          // +0x04
    char* mCap;          // +0x08
};
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
CheatManager* __cdecl SP_CheatManager();                     // 0x0067de20
void          __cdecl operator_delete_array(void*);           // 0x00f47380
void          __cdecl EA_Messaging_RemoveHandler(void*, uint, uint, uint, uint); // 0x00571db0
int           __stdcall FUN_00e9db10(void* key);              // 0x00e9db10
extern uint32_t gAmbCheatArg;    // 0x01487138  (arg to CheatManager::s1c)
extern cAmbienceTag* gTagFreeListHead;   // 0x016c6a04
extern void* g_vtbl_01487150;
extern void* g_vtbl_01487140;
extern void* g_vtbl_0148713c;
extern void* g_vtbl_013eb394;
extern void* g_vtbl_013ef094;
// ---- items of slice s00e9e290 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cAmbienceTag* gTagFreeListHead;   // 0x016c6a04

// ---- items of slice s00e9fca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t     gPropId015a8b78;  // 0x015a8b78
typedef unsigned int uintptr_t;
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct IWnd {
    virtual void AddRef();                        // 0x00
    virtual void Release();                       // 0x04
    PV                                            // 0x08
    virtual void* GetChild(uint id);              // 0x0c
    virtual IWnd* Slot10();                       // 0x10
    PV4 PV                                        // 0x14..0x24
    virtual void  Slot28(int a, int b);           // 0x28
    PV16 PV4                                      // 0x2c..0x78
    virtual void  Slot7c(int a, int b);           // 0x7c
    PV4 PV2                                       // 0x80..0x94
    virtual void  Slot98();                       // 0x98
    PV8 PV4                                       // 0x9c..0xc8
    virtual void  SlotCC(void** out);             // 0xcc
    virtual void  SlotD0(void** out);             // 0xd0
    PV4 PV                                        // 0xd4..0xe4
    virtual void  SlotE8(void* p);                // 0xe8
    PV                                            // 0xec
    virtual void* SlotF0(uint id, int a);         // 0xf0
    PV4                                           // 0xf4..0x100
    virtual void  Slot104(void* p);               // 0x104
    virtual void  Slot108(void* p);               // 0x108
};
struct IConfiguration {
    virtual void AddRef();                        // 0x00
    virtual void Release();                       // 0x04
    PV4 PV                                        // 0x08..0x18
    virtual void Slot1c(uint id, void** out);     // 0x1c
    PV2                                           // 0x20, 0x24
    virtual void Slot28(uint id, int* out);       // 0x28
    PV                                            // 0x2c
    virtual void Slot30(uint id, void** out);     // 0x30
};
struct AudioSystem {
    PV4 PV                                        // 0x00..0x10
    virtual bool Slot14(uint a, void** cfg, uint b);        // 0x14
    PV4 PV2                                       // 0x18..0x2c
    virtual void Slot30(void* id, uint hash, void** out);   // 0x30
    PV                                            // 0x34
    virtual void Slot38(uint a);                  // 0x38
    PV                                            // 0x3c
    virtual void Slot40(uint a, uint b);          // 0x40
    PV4 PV                                        // 0x44..0x54
    virtual void Slot58();                        // 0x58
};
struct AmbConfig {
    void*    mpBegin;                             // +0x00
    uint8_t  pad04[4];                            // +0x04
    void*    mpEnd;                               // +0x08
    uint8_t  pad0c[4];                            // +0x0c
    uint16_t mFlags;                              // +0x10
    uint16_t mCount;                              // +0x12
};
struct cAmbienceLayerManager {
    uint8_t         pad00[0x10];
    IConfiguration* mpConfiguration;              // +0x10
    uint8_t         pad14[0x14];                  // +0x14..+0x27
    int32_t         mNumCells;                    // +0x28
    uint8_t         pad2c[0xc0];                  // +0x2c..+0xeb
    uint8_t         mCurveA[0x364];               // +0xec (ResponseCurve)
    uint8_t         mCurveB[0x364];               // +0x450 (ResponseCurve)
    uint8_t         mItSamplePts[0x40];           // +0x7b4
};
void*       EA_GetSystemAT(void);                       // 0x00a206f0
void*       __cdecl EA_ConvertToString8(void*, const int*);   // 0x0093c570
bool __fastcall FUN_00e9fca0(cAmbienceLayerManager* self, void* edx);  // 0x00e9fca0 (defined below; used by a stub's inline body)
struct Thiscall {
    void  FUN_00e9e220();                        // 0x00e9e220
    void  FUN_00e9faa0(void* s);                 // 0x00e9faa0
    void  FUN_00e9fbc0();                        // 0x00e9fbc0
    void  FUN_00e9fca0();                        // 0x00e9fca0 (SetupLayers)
    void  SetWindow(IWnd* w);                    // 0x00e9fe90 (cWindowPulse::SetWindow)
    void  SetMusicNote(void* m);                 // 0x00ea2d50 (cCityMusicNoteEditor::SetMusic)
    void  SetMusicLoad(void* m);                 // 0x00ea23a0 (cCityMusicLoadSave::SetMusic)
    void  ResetUndoBuffer();                     // 0x00eb10d0
    unsigned char FUN_00ead820();                // 0x00ead820 (returns char)
    unsigned char FUN_00ead840();                // 0x00ead840 (returns char)
    void  FUN_00ea3b50();                        // 0x00ea3b50 (cCityMusicNoteEditor::Update)
    void  FUN_00ea3420(int b);                   // 0x00ea3420 (RedrawMelody)
    void  FUN_00ea3120();                        // 0x00ea3120 (LoopMelody)
    void  SetSoundProperty(int v);               // 0x00ea3040
    void  InitFromConfiguration(void* cfg, uint id);   // 0x00a1a9d0
    void  FUN_0095ea30(void* vec);               // 0x0095ea30
};
// ---- items of slice s00e9fca0 end

// @ 0x00e9e290
bool cAmbLayer::Shutdown()
{
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

// @ 0x00e9e2f0
bool cAmbLayer::RemoveTag(uint tag)
{
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

// @ 0x00e9e350
void cAmbLayer::DestroyCubeMap()
{
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

// @ 0x00e9e3a0
void cAmbLayer::Destroy()
{
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

// @ 0x00e9ed00
bool cAmbLayer::FUN_00e9ed00(cAmbienceTag* p)
{
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

// @ 0x00e9fca0
bool __fastcall FUN_00e9fca0(cAmbienceLayerManager* self, void* edx)
{
    (void)edx;
    ((Thiscall*)self)->FUN_00e9e220();
    AmbConfig c;
    self->mpConfiguration->Slot1c(0xc49b97a3, (void**)&c);
    bool dynamic = (c.mFlags & 0x30) != 0;
    if (!dynamic) {
        if (c.mCount == 0)
            return true;
    } else if (c.mpEnd == 0) {
        return true;
    }
    void* iter = dynamic ? c.mpBegin : (void*)&c;
    int count = dynamic ? (int)(uintptr_t)c.mpEnd : (c.mCount != 0 ? 1 : 0);
    for (int i = 0; i < count; ++i) {
        void* tmp = 0;
        void* s = EA_ConvertToString8(&tmp, (const int*)iter);
        ((Thiscall*)self)->FUN_00e9faa0(*(void**)s);
        if (tmp)
            operator_delete_array(tmp);
        iter = (char*)iter + 0x10;
    }
    return true;
}

// @ 0x00e9fd70
char __fastcall FUN_00e9fd70(cAmbienceLayerManager* self, void* edx)
{
    (void)edx;
    AudioSystem* sys = (AudioSystem*)EA_GetSystemAT();
    IConfiguration* cfg = self->mpConfiguration;
    if (cfg) {
        self->mpConfiguration = 0;
        cfg->Release();
    }
    if (!sys->Slot14(0x6ff1e689, (void**)&self->mpConfiguration, 0x21407ee))
        return 0;
    cfg = self->mpConfiguration;
    self->mNumCells = 10;
    cfg->Slot28(gPropId015a8b78, &self->mNumCells);
    self->mpConfiguration->Slot30(0xf5a18499, (void**)&self->mItSamplePts);
    ((Thiscall*)(void*)self->mCurveA)->InitFromConfiguration(self->mpConfiguration, 0xdc079eb6);
    ((Thiscall*)(void*)self->mCurveB)->InitFromConfiguration(self->mpConfiguration, 0x2f826725);
    ((Thiscall*)self)->FUN_00e9fbc0();
    ((Thiscall*)self)->FUN_00e9fca0();
    return 1;
}
