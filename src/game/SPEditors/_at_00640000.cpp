// src/game/SPEditors/_at_00640000.cpp -- migrated from slice(s) s0064dbd0, s0064bc50, s00647f40 by tools/migrate/rewrite.py
// Object file: SPEditors/_at_00640000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUIAssetGrid.h"
#include "SP/cPollinator.h"
#include "SP/cSPUIAssetBrowser.h"
#include "SP/cSPUIAssetVerbs.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void FUN_0093a560();        // EA::Stopwatch::Stopwatch(this, units, running)  @ 0x93a560
extern "C" void FUN_0066a5e0();        // FlagKey::FlagKey(this, fill, value)              @ 0x66a5e0
extern uint32_t g_140042c;             // 0x0140042c: value word written into a fresh FlagKey
extern void* gEmptyBucketArray;                                                  // 0x154df28 (empty hashtable sentinel)

// ---- items of slice s00647f40 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define AT(T, off) (*(T*)((char*)this + (off)))
extern "C" void FUN_0093a560();        // EA::Stopwatch::Stopwatch(this, units, running)  @ 0x93a560
extern "C" void FUN_0066a5e0();        // FlagKey::FlagKey(this, fill, value)              @ 0x66a5e0
extern uint32_t g_140042c;             // 0x0140042c: value word written into a fresh FlagKey
extern void* gEmptyBucketArray;                                                  // 0x154df28 (empty hashtable sentinel)
struct cSPUIAssetGrid {
    void Dtor();       // @ 0x00647f40
    void* Ctor();      // @ 0x00648730
};
// ---- items of slice s00647f40 end

// ---- items of slice s0064bc50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AssetEntry {
    char pad[0x10];
    void* mpObject;
};
struct StopwatchData {
    uint32_t f00, f04, f08, f0c;
};
struct AssetKey {
    uint32_t mInstance;   // +0x00
    uint32_t mType;       // +0x04
    uint32_t mGroup;      // +0x08
};
struct EaHashIter {
    void* mpNode;         // +0x00 (buckets[count] means "not found")
    void* mpBucket;       // +0x04
};
struct EaMap {
    void* mpAllocator;    // +0x00
    void** mpBuckets;     // +0x04
    uint32_t mBucketCount;// +0x08
    uint32_t mSize;       // +0x0c
    EaHashIter find(const uint32_t& key) const;  // 0x00645ed0
    void** FindOrInsert(const uint32_t& key);    // 0x00646f40
};
struct cSPUIAssetBrowserLayout {
    char pad00[0x14];
    void* mpAnimator;             // +0x14
    void* mpSomething18;          // +0x18
    unsigned char mActive;        // +0x1c
    char pad1d[2];
    unsigned char mField1f;       // +0x1f
    char pad20[0x1c];
    float mTimer;                 // +0x3c
    StopwatchData mStopwatch;     // +0x40
    char pad50[0xc];
    void* mpSomething5c;          // +0x5c
    char pad60[4];
    void* mpSomething64;          // +0x64
    char pad68[0x18];
    void* mpSomething80;          // +0x80
    void* mpSomething84;          // +0x84
    char pad88[0x30];
    void* mpSomethingB8;          // +0xb8
    void* mpSomethingBC;          // +0xbc
    void* mpSomethingC0;          // +0xc0
    char padC4[4];
    void* mpSomethingC8;          // +0xc8
    AssetEntry* mpEntriesBegin;   // +0xcc
    AssetEntry* mpEntriesEnd;     // +0xd0
    AssetEntry* mpEntriesCap;     // +0xd4
    char padD8[0xc];
    AssetKey* mpVec2Begin;        // +0xe4 (key vector)
    AssetKey* mpVec2End;          // +0xe8
    AssetKey* mpVec2Cap;          // +0xec
    char padF0[0x68];
    void* mpSomething158;         // +0x158
    EaMap mMap;                   // +0x15c
    char pad16C[0x10];
    void* mpSomething17c;         // +0x17c
    char pad180[0x20];
    void* mpServer;               // +0x1a0
    void* mpHandler;              // +0x1a4
    uint32_t mMsgId;              // +0x1a8
    unsigned char mField1ac;      // +0x1ac
    char pad1AD[0x1a];
    unsigned char mField1c7;      // +0x1c7
    unsigned char mExpanded;      // +0x1c8
    char pad1C9[0x5f];
    void* mpSomething228;         // +0x228 (= handler's +0x224)
    char pad22C[4];
    int mState230;                // +0x230 (= handler's +0x22c)
    unsigned char mField234;      // +0x234
    char pad235[0x17];
    unsigned char mField24c;      // +0x24c
    char pad24D[1];
    unsigned char mField24e;      // +0x24e

    void* Get_10();                           // 0x00645300
    void Fn_e20(char one);                    // 0x00644e20
    void BanItem();                           // 0x0064b4b0
    void SetVisibility(int a, int b, int c);  // 0x0064a400
    void LaunchEditorEnd();                   // 0x0064acd0
};
typedef void (__fastcall *VCall_IntInt)(void*, int, int, int);
typedef unsigned int (__fastcall *VCall_UInt)(void*);
typedef void (__fastcall *VCall_Ptr)(void*, int, void*);
static void** VTableOf(void* p) { return *(void***)p; }
void* __cdecl FUN_0067cab0(void);                                         // 0x0067cab0
void* __cdecl FUN_00401010(void);                                         // 0x00401010
struct SpVector {
    AssetKey* mpBegin;    // +0x00
    AssetKey* mpEnd;      // +0x04
    AssetKey* mpCap;      // +0x08
    void DoInsertKey(AssetKey* pos, const AssetKey* value);  // 0x004e3e10
    AssetKey* Erase(AssetKey* first, AssetKey* last);        // 0x0050f740
};
struct cSPUIAssetVerbs {
    bool IsVerb(int verb);                     // 0x00656740
    void SetSelection(int a, int b, int c);    // 0x006571e0
};
void  __fastcall FUN_00801360(void* self);                        // 0x00801360
void* __cdecl App();                                              // 0x0067dd10
bool  __cdecl FUN_004bbe90(uint32_t id);                          // 0x004bbe90
bool  __cdecl FUN_004bbed0(uint32_t id);                          // 0x004bbed0
uint32_t __cdecl FNVHash(const char* text, uint32_t seed, int mode);// 0x00932e80
typedef AssetKey* (__fastcall *VCall_Key)(void*);
typedef bool (__fastcall *VCall_Bool_Ptr)(void*, int, void*);
typedef bool (__fastcall *VCall_Bool_PtrIdx)(void*, int, void*, void*);
typedef bool (__fastcall *VCall_Bool_PtrInt)(void*, int, void*, int);
__declspec(noinline) void __fastcall sub_64c280(cSPUIAssetBrowserLayout* self);
struct OutKey {
    uint32_t mInstance;   // +0x00
    uint16_t mType;       // +0x04
    uint16_t mGroup;      // +0x06
};
// ---- items of slice s0064bc50 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __fastcall sub_64c0d0(cSPUIAssetBrowserLayout* self);  // 0x0064c0d0 (stays in the slice: not this object's)

// ---- items of slice s0064dbd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void** VT(void* p) { return *(void***)p; }
struct PBase1 {
    virtual void pv();
};
struct PBase2 {
    virtual void pv();
    int mRef;
    PBase2() : mRef(0) {}
};
struct FrameSet {
    void* GetFrame(void* id);                     // FUN_00996d40
    void  Params(int, int, int, int);             // FUN_00996280
    bool  LoadFrame(void* win, uint32_t key);     // FUN_009979f0
    bool  HandleLocationChange(void*, void*, void*, void*); // FUN_00997730
    bool  HandleFormSubmit(void*, void*);         // FUN_009978b0
    void  Construct(void* arg);                   // FUN_00996cc0
    void  Destroy();                              // FUN_009968a0
};
namespace SP {
class cSPUIAssetComments_s0064_dbd0 : public PBase1, public PBase2 { public:
    char mFrameSet[0x64];     // +0x0c  (retail size)
    void* mpContentWin;       // +0x70
    void* mpXHTMLWin;         // +0x74

    cSPUIAssetComments_s0064_dbd0();
    bool Init(void* win);  // 0x0064e230 (SP::cSPUIAssetComments::Init)
    void SetVisibility(int visible);  // 0x0064e400 (SP::cSPUIAssetComments::SetVisibility)
    bool LoadAssetComments(uint64_t id);  // 0x0064e460 (SP::cSPUIAssetComments::LoadAssetComments)
    bool DoMessage(void* sender, int* msg);  // 0x0064e300 (SP::cSPUIAssetComments::DoMessage)
    void* deleting_dtor(unsigned flags);  // 0x0064e1d0 (SP::cSPUIAssetComments::deleting_dtor)
};  // namespace SP
}
// ---- items of slice s0064dbd0 end

// @ 0x00648730
void* cSPUIAssetGrid::Ctor()
{
    AT(void*, 8) = (void*)0x14426a0;
    AT(void*, 0xc) = (void*)0x13ec458;
    AT(void*, 0x10) = 0;
    AT(void*, 0) = (void*)0x13ff844;
    AT(void*, 4) = (void*)0x13ff838;
    AT(void*, 8) = (void*)0x13ff81c;
    AT(void*, 0xc) = (void*)0x13ff80c;
    AT(void*, 0x14) = 0;
    AT(void*, 0x18) = 0;
    AT(uint8_t, 0x1c) = 0;
    AT(uint8_t, 0x1d) = 0;
    AT(uint8_t, 0x1e) = 0;
    AT(uint8_t, 0x1f) = 0;
    AT(uint32_t, 0x20) = 1;
    AT(uint8_t, 0x24) = 0;
    AT(uint8_t, 0x25) = 0;
    AT(uint8_t, 0x26) = 0;
    AT(uint8_t, 0x27) = 0;
    AT(uint8_t, 0x28) = 0;
    AT(uint8_t, 0x29) = 0;
    AT(uint8_t, 0x2a) = 1;
    AT(float, 0x3c) = 0.0f;
    ((void(__thiscall*)(void*, int, int))FUN_0093a560)((char*)this + 0x40, 4, 0);    AT(void*, 0x58) = 0;
    AT(void*, 0x5c) = 0;
    AT(void*, 0x60) = 0;
    AT(void*, 0x64) = 0;
    AT(void*, 0x68) = 0;
    AT(void*, 0x6c) = 0;
    AT(void*, 0x70) = 0;
    AT(void*, 0x74) = 0;
    AT(void*, 0x78) = 0;
    AT(void*, 0x7c) = 0;
    AT(void*, 0x80) = 0;
    AT(void*, 0x84) = 0;
    AT(void*, 0x88) = 0;
    AT(void*, 0x8c) = 0;
    AT(void*, 0x90) = 0;
    AT(void*, 0x94) = 0;
    AT(void*, 0x98) = 0;
    AT(void*, 0x9c) = 0;
    AT(void*, 0xa0) = 0;
    AT(void*, 0xa4) = 0;
    AT(void*, 0xa8) = 0;
    AT(void*, 0xac) = 0;
    AT(void*, 0xb0) = 0;
    AT(void*, 0xb4) = 0;
    AT(void*, 0xb8) = 0;
    AT(void*, 0xbc) = 0;
    AT(void*, 0xc0) = 0;
    AT(void*, 0xc4) = 0;
    AT(void*, 0xc8) = 0;
    AT(void*, 0xcc) = 0;
    AT(void*, 0xd0) = 0;
    AT(void*, 0xd4) = 0;
    AT(void*, 0xe4) = 0;
    AT(void*, 0xe8) = 0;
    AT(void*, 0xec) = 0;
    AT(float, 0x108) = 1.0f;
    AT(float, 0x10c) = 2.0f;
    AT(uint32_t, 0x100) = 1;
    AT(void*, 0xfc) = &gEmptyBucketArray;
    AT(uint32_t, 0x104) = 0;
    AT(void*, 0x110) = 0;
    AT(float, 0x128) = 1.0f;
    AT(float, 0x12c) = 2.0f;
    AT(uint32_t, 0x120) = 1;
    AT(void*, 0x11c) = &gEmptyBucketArray;
    AT(uint32_t, 0x124) = 0;
    AT(void*, 0x130) = 0;
    AT(float, 0x148) = 1.0f;
    AT(float, 0x14c) = 2.0f;
    AT(uint32_t, 0x140) = 1;
    AT(void*, 0x13c) = &gEmptyBucketArray;
    AT(uint32_t, 0x144) = 0;
    AT(void*, 0x150) = 0;
    AT(void*, 0x158) = 0;
    AT(float, 0x16c) = 1.0f;
    AT(float, 0x170) = 2.0f;
    AT(uint32_t, 0x164) = 1;
    AT(void*, 0x160) = &gEmptyBucketArray;
    AT(uint32_t, 0x168) = 0;
    AT(void*, 0x174) = 0;
    AT(void*, 0x17c) = 0;
    AT(void*, 0x180) = 0;
    AT(void*, 0x184) = 0;
    AT(void*, 0x188) = 0;
    AT(void*, 0x18c) = 0;
    AT(void*, 0x190) = 0;
    AT(void*, 0x194) = 0;
    AT(void*, 0x198) = 0;
    AT(void*, 0x1a0) = 0;
    AT(void*, 0x1a4) = 0;
    AT(void*, 0x1a8) = 0;
    AT(uint8_t, 0x1ac) = 0;
    AT(void*, 0x1b0) = 0;
    AT(void*, 0x1b4) = 0;
    AT(void*, 0x1b8) = 0;
    AT(void*, 0x1bc) = 0;
    AT(void*, 0x1c0) = 0;
    AT(uint8_t, 0x1c4) = 0;
    AT(uint8_t, 0x1c5) = 0;
    AT(uint8_t, 0x1c6) = 0;
    AT(uint8_t, 0x1c7) = 0;
    AT(uint8_t, 0x1c8) = 0;
    AT(void*, 0x1cc) = 0;
    AT(void*, 0x1d0) = 0;
    AT(void*, 0x1d4) = 0;
    AT(void*, 0x1d8) = 0;
    AT(void*, 0x1dc) = 0;
    AT(void*, 0x1e0) = 0;
    AT(void*, 0x1e4) = 0;
    AT(void*, 0x1e8) = 0;
    AT(uint8_t, 0x1ec) = 0;
    AT(uint8_t, 0x1ed) = 0;
    ((void(__thiscall*)(void*, int, uint32_t))FUN_0066a5e0)((char*)this + 0x1f0, 1, g_140042c);
    AT(void*, 0x210) = 0;
    AT(float, 0x214) = 24.0f;
    AT(void*, 0x218) = 0;
    AT(void*, 0x21c) = 0;
    AT(void*, 0x220) = 0;
    AT(void*, 0x224) = 0;
    AT(void*, 0x228) = 0;
    AT(uint32_t, 0x22c) = 1;
    AT(void*, 0x230) = 0;
    AT(uint8_t, 0x234) = 0;
    AT(uint8_t, 0x235) = 0;
    AT(uint8_t, 0x236) = 0;
    AT(void*, 0x238) = 0;
    AT(uint8_t, 0x23c) = 0;
    AT(uint8_t, 0x23d) = 0;
    AT(void*, 0x240) = 0;
    AT(void*, 0x244) = 0;
    AT(void*, 0x248) = 0;
    AT(uint8_t, 0x24c) = 0;
    AT(uint8_t, 0x24d) = 0;
    AT(uint8_t, 0x24e) = 0;
    AT(uint8_t, 0x24f) = 0;
    return this;
}

// @ 0x0064c6b0
void __fastcall sub_64c6b0(cSPUIAssetBrowserLayout* self)
{
    if (self->mMsgId == 0x54acb9f1) {
        void* app = App();
        if (((VCall_UInt)VTableOf(app)[0x38 / 4])(app) != 0xdbdba1) {
            ((cSPUIAssetVerbs*)self->mpSomethingC8)->SetSelection(0, 0, 0);
            if (self->mpServer || self->mpHandler)
                self->mField24c = 1;
            sub_64c0d0(self);
            return;
        }
    }
    if (self->mField1c7) {
        ((SpVector*)&self->mpVec2Begin)->Erase(self->mpVec2Begin, self->mpVec2End);
        if ((int)(self->mpEntriesEnd - self->mpEntriesBegin) != 0) {
            for (int i = 0; i < (int)(self->mpEntriesEnd - self->mpEntriesBegin); ++i) {
                void* obj = self->mpEntriesBegin[i].mpObject;
                if (!obj)
                    continue;
                AssetKey* src = ((VCall_Key)VTableOf(obj)[0x40 / 4])(obj);
                if (!FUN_004bbe90(src->mType) && !FUN_004bbed0(src->mType))
                    continue;
                OutKey out;
                out.mInstance = FNVHash("AssetBrowser", 0x811c9dc5, 1);
                out.mType = 0x101;
                out.mGroup = 0;
                void* tracker = FUN_00401010();
                if (!((VCall_Bool_Ptr)VTableOf(tracker)[0x18 / 4])(tracker, 0, src)) {
                    if (self->mpVec2End < self->mpVec2Cap) {
                        AssetKey* dst = self->mpVec2End;
                        self->mpVec2End = dst + 1;
                        if (dst) {
                            dst->mInstance = src->mInstance;
                            dst->mType = src->mType;
                            dst->mGroup = src->mGroup;
                        }
                    } else {
                        ((SpVector*)&self->mpVec2Begin)->DoInsertKey(self->mpVec2End, src);
                    }
                }
                void* tracker2 = FUN_00401010();
                if (((VCall_Bool_PtrIdx)VTableOf(tracker2)[0x4c / 4])(tracker2, 0, src, &out)) {
                    void* tracker3 = FUN_00401010();
                    if (!((VCall_Bool_PtrInt)VTableOf(tracker3)[0x1c / 4])(tracker3, 0, src, 1))
                        self->mExpanded = 1;
                }
            }
        }
        if (self->mExpanded) {
            FUN_00801360(FUN_0067cab0());
            if (self->mpSomething80 && self->mpSomething5c) {
                ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 1, 1);
                ((VCall_IntInt)VTableOf(self->mpSomething80)[0x7c / 4])(self->mpSomething80, 0, 0x40, 1);
                ((VCall_Ptr)VTableOf(self->mpSomething5c)[0xe8 / 4])(self->mpSomething5c, 0, self->mpSomething80);
                self->mField1f = 1;
            }
            return;
        }
    }
    sub_64c280(self);
}

// @ 0x0064e170
SP::cSPUIAssetComments_s0064_dbd0::cSPUIAssetComments_s0064_dbd0()
{
    ((FrameSet*)((char*)this + 0xc))->Construct((void*)0x623f40);
    mpContentWin = 0;
    mpXHTMLWin = 0;
    _ReadWriteBarrier();
    ((void(__thiscall*)(void*))VT((char*)this + 0xc)[0])((char*)this + 0xc);
}
