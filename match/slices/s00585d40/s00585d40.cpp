// slice s00585d40 -- SP::cAppModeEditorBase: save-in-progress state machine, undo-list init and a
// few small editor helpers.  Retail class layout differs slightly from the 2008 PDB; offsets are
// taken from the disassembly.  Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <intrin.h>

struct Vector3 { float x, y, z; };

extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchangeAdd)

void __cdecl operator delete[](void* p);                                    // 0x00f47380
void* __cdecl operator new(unsigned size, const char* name, int, int, int, int);  // 0x00f473a0

// Placeholder virtual slots so a stub interface can expose a method at a given vtable offset.
#define VP1(p, n) virtual void p##n() = 0;
#define VP4(p, n) VP1(p, n##0) VP1(p, n##1) VP1(p, n##2) VP1(p, n##3)
#define VP16(p, n) VP4(p, n##0) VP4(p, n##1) VP4(p, n##2) VP4(p, n##3)

namespace SP {

class cSPEditorUI {
public:
    void EnableUndoButton(bool b);
    void EnableRedoButton(bool b);
    void UpdateUIBasedOnModelSaveability();
};

// A vector-like container as used by the editor undo lists (begin/end at +0/+4, 0x14 bytes strided).
struct UndoVector {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    uint32_t mPad0c;    // +0x0c
    uint32_t mPad10;    // +0x10
    void erase(void* first, void* last);
};

// ---- stub types for the objects ContinueSaveInProgress talks to (offsets from the disassembly) ----

// Image resource: first dword is the pixel/resource handle, refcount at +8.
struct cImageRef {
    uint32_t mHandle;       // +0
    uint32_t mFlags;        // +4 (bit 0: already registered)
    long mnRefCount;        // +8
};

// Intrusive pointer release exactly as inlined at the call sites (nested atomic refcount traffic).
__forceinline void ReleaseImage(cImageRef*& slot)
{
    cImageRef* p = slot;
    if (p) {
        long* rc = &p->mnRefCount;
        slot = 0;
        _InterlockedExchangeAdd(rc, -1);
        long c = _InterlockedExchangeAdd(rc, 0);
        if (c < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
}

struct cImagePtr {
    cImageRef* p;
    void Assign(void* res);                                 // 0x00576650
};

struct Vec3U { uint32_t x, y, z; };

struct cPedestalModel {
    char pad0[0xc];
    Vec3U mPos;                 // +0x0c
    char pad18[0xdc - 0x18];
    uint32_t mScore;            // +0xdc
};

struct cEditorModelStub {
    char pad0[0x58];
    uint32_t mNameHash;         // +0x58
    bool UsingSymmetry() const;             // 0x004adc40
    void FUN_004adc20(int a);               // 0x004adc20
    bool SaveResource(void* save);          // 0x004af260
    void FUN_004adfc0(int a);               // 0x004adfc0
};

struct cEditorLaunchData {
    char pad0[0xc];
    uint32_t mConfig;           // +0x0c
    char pad10[0x60 - 0x10];
    float mShaderParam;         // +0x60
};

// Editor resource factories (thiscall helpers declared as members so ECX carries `this`).
struct cSkinFactoryStub {
    char pad0[0x5c];
    void* mpSub;                // +0x5c
    bool IsBusy();                          // 0x004c58b0
    char pad1[1];
    bool GetFlag84();                       // 0x004c4630 (reads byte +0x84)
    void* GetSub();                         // 0x004adfe0 (returns +0x5c)
    void UpdatePaintedSkin();               // 0x004c4290
    void Begin(char b);                     // 0x004c4650
    void Apply(cEditorModelStub* m);        // 0x004c5200
};
struct cGlobalMgr522 { void Handle(void* p); };                  // 0x00522a40
struct cMessageManager { void Post(uint32_t id, int arg); };     // 0x0045ae10

struct cPaletteSub { VP16(a, 0) VP4(b, 0) virtual void vfn50(int a) = 0; };
struct cPaletteUI { char pad0[0x38]; cPaletteSub* mpSub; };
struct cAnimCreatureMgr { void RemoveCreature(void* p); };       // 0x0059c6e0

struct cObj67dd40 { VP16(a, 0) VP16(b, 0) VP16(c, 0) VP1(d, 0) virtual void vfnC4(uint32_t* out) = 0; };
struct cObj67dda0 { VP4(a, 0) VP1(b, 0) VP1(c, 0) virtual void* vfn18(uint32_t a, uint32_t b) = 0; };
struct cObj67dd50 { VP16(a, 0) VP16(b, 0) VP1(c, 0) virtual void vfn84(int a) = 0; };
struct cObj67dd60 {
    VP4(a, 0) VP4(b, 0) VP1(c, 0)
    VP1(d, 0) VP1(e, 0) VP1(f, 0)
    VP1(g, 0)
    virtual void vfn34(cImageRef* img) = 0;                // +0x34 (13)
    virtual void vfn38_pad() = 0;
    virtual void* vfn3C(uint32_t a, uint32_t b, int c, int d, int e, int f, int g, int h) = 0;
    VP4(h, 0) VP4(i, 0) VP1(j, 0) VP1(k, 0)
    virtual void vfn68(cImageRef* img) = 0;                // +0x68 (26)
};
struct cResMgrStub {
    VP4(a, 0) VP4(b, 0)
    virtual void vfn20(void* msg, int a, void* area, uint32_t b, int c) = 0;   // +0x20 (8)
};
struct cMsgServerStub {
    VP4(a, 0) VP1(b, 0)
    virtual void vfn14(uint32_t id, void* data, int a) = 0;                    // +0x14 (5)
};

// The 0x30-byte request object created in stage 4: a refcounted base plus an embedded message at +8.
struct cReqBase {
    virtual void vfn0();         // +0 (called three times around the dispatch)
    virtual void vfn4();         // +4 (final release)
    void* mpImage;              // +4
};
struct cMsgSub {
    uint32_t mPad[2];
    uint32_t mTrans;            // +8
    uint32_t mMsgId;            // +0xc
    uint32_t mFlags;            // +0x10
};
struct cSaveRequest : cReqBase, cMsgSub {
    char mTail[0x30 - 0x1c];
    cSaveRequest();             // 0x009986e0
};

class cAppModeEditorBase;

struct EmptyStr { const char* mpBegin; const char* mpEnd; const char* mpCap; };
extern char gEmptyString[2];                                    // 0x01667bac

// Only the fields touched by this slice.
class cAppModeEditorBase {
public:
    char pad0[0x78];
    cSPEditorUI* mDevUI;                 // +0x78
    char pad7c[0x84 - 0x7c];
    void* mSaveModelWorld;               // +0x84
    char pad88[0x98 - 0x88];
    cEditorModelStub* mEditorSaveModel;  // +0x98
    cPedestalModel* mPedastalModel;      // +0x9c
    char padA0[0x150 - 0xa0];
    cSkinFactoryStub* mSaveLoadFactory;  // +0x150
    cSkinFactoryStub* mTextureFactory;   // +0x154
    char pad158[0x15c - 0x158];
    uint32_t mUndoStateRef;              // +0x15c
    UndoVector mUndoLocalStateList;      // +0x160
    UndoVector mUndoList;                // +0x174
    int mUndosLeft;                      // +0x188
    char pad18c[0x1a4 - 0x18c];
    int mAnimCaptureState;               // +0x1a4
    int mCurrentCreatureMode;            // +0x1a8
    char pad1ac[0x1cc - 0x1ac];
    cEditorLaunchData* mLaunchData;      // +0x1cc
    Vec3U mParentModelKey;               // +0x1d0
    char pad1dc[0x1f8 - 0x1dc];
    uint32_t mCurrencyIconGroup;         // +0x1f8
    char pad1fc[0x28c - 0x1fc];
    cImagePtr mSmallImage;               // +0x28c
    cImagePtr mLargeImage;               // +0x290
    char pad294[0x2ac - 0x294];
    uint32_t mSaveAreaId;                // +0x2ac
    char pad2b0[0x2f1 - 0x2b0];
    bool mPaintedSkinSave;               // +0x2f1
    char pad2f2[0x310 - 0x2f2];
    bool mTranslateModelOnSave;          // +0x310
    char pad311[3];
    float mShaderParam;                  // +0x314
    char pad318[0x360 - 0x318];
    cPaletteUI* mPaletteUILoaded;        // +0x360
    char pad364[4];
    void* mEffectsMaskViewer;            // +0x368
    char pad36c[0x38c - 0x36c];
    int mSaveState;                      // +0x38c
    char pad390[4];
    bool mLargeImageReady;               // +0x394
    bool mSmallImageReady;               // +0x395
    char pad396[0x3f0 - 0x396];
    uint32_t mDeleteValueFadeTime;       // +0x3f0 (frame count)
    char pad3f4[0x408 - 0x3f4];
    uint32_t mCurrentInstanceId;         // +0x408
    char pad40c[0x430 - 0x40c];
    bool mCaptureBusy;                   // +0x430
    char pad431[0x4d8 - 0x431];

    void GetState(void* state);                             // 0x00574080
    void BuildPartMask(void* out, void* a, void* b, int c); // 0x0057ac00
    void InitializeUndoList();                              // 0x00586690
    __declspec(noinline) void FUN_00586410(char a, void* b); // 0x00586410
    void FUN_00586700();                                    // 0x00586700
    uint8_t FUN_00586800(void* a);                          // 0x00586800
    void FUN_00586960();                                    // 0x00586960
    void ContinueSaveInProgress();                          // 0x00585d40

    int ScoreCreatureForZCorp();                            // 0x00574b40
    void SetAnimCaptureOn(char on);                         // 0x00583c50
    void CaptureGIF(EmptyStr* s);                           // 0x005809a0
    void FUN_00584070();
    void FUN_00580700(cPedestalModel* m, void* world, int size, uint32_t grp, uint32_t id, cImageRef* img);
    void RunSkinPaintOnEditorModel(int a, int b);           // 0x00582fe0
    void SaveSomething();                                   // 0x00577650
    void FUN_00585c10();
    void FUN_00573f70(char a);
};

// ---- types touched by the undo / limb-rebuild helpers (offsets from the disassembly) ----
struct cIntVec { void Resize(unsigned n); };                     // 0x00584160
struct cSPEditorHandle { void* GetEditorBlock(); };              // 0x0047e6c0
struct cSpine75 { void SetFlag(bool a, int b); };                // 0x005d1600

// eastl::vector<bool> as laid out in this build: begin/end at +0/+4, fill-insert helper at 0x5151b0.
struct EastlBitVector {
    void* mpBegin;      // +0
    void* mpEnd;        // +4
    void* mpCap;        // +8
    void DoFillInsert(void* pos, int n, void* value);            // 0x005151b0
};

struct cSPEditorLimbStructure {
    uint8_t pad[0x54];
    cSPEditorLimbStructure();                                    // 0x00488850
    ~cSPEditorLimbStructure();                                   // 0x00488900
    void* BuildLimb(void* block, void* parent, bool b);          // 0x004891a0
    void FUN_0048a4c0();                                         // 0x0048a4c0
    void FUN_00488980();                                         // 0x00488980
};

}  // namespace SP

// Global accessors / free helpers.
struct cPropList {
    int GetIntProperty(uint32_t id);                        // 0x006a2660
    float GetFloatProperty(uint32_t id);                    // 0x006a2710
};
extern cPropList* sAppProperties;                           // [0x015fd918]
SP::cObj67dd40* FUN_0067dd40();
SP::cObj67dda0* FUN_0067dda0();
SP::cObj67dd50* FUN_0067dd50();
SP::cObj67dd60* FUN_0067dd60();
SP::cResMgrStub* GetManager();                              // 0x0067dcd0
SP::cMsgServerStub* MessageServer();                        // 0x0067dcc0
SP::cGlobalMgr522* FUN_00401080();
SP::cMessageManager* MessageManager();                      // 0x00401050
uint32_t GetSaveArea(uint32_t id);                          // 0x006b1f90
uint32_t WriteAnimatedCSAGIF(void* gif, int a, const char* s, uint32_t x1, uint32_t x2, float f, int one, int zero);  // 0x007c3410
void shader(int id, const void* p, int n);                  // 0x00777ae0
void FUN_006b2350();
void VectorResize(void* vec, int n);                             // 0x005e77e0
void FUN_005c8480(void* vec, void* end, void* src);              // 0x005c8480
void FUN_006650c0(void* vec, void* end, void* src);              // 0x006650c0
void* FUN_004b9c70(void* p);                                     // 0x004b9c70
void* GetSetting6();                                             // 0x00401060
void DeleteInvalidBlocks(void* block, int a);                    // 0x004a6f10
void GetAllLimbs(void* block, void* limbVec, bool b);            // 0x004a0020
void FUN_0057e340(void* a, int b);                               // 0x0057e340
void EastlVectorBoolDoInsertValue(void* a, void* b, int c);      // 0x011e0744
void* cVarListSerializer_Construct(void* self, void* owner, void* ds, unsigned id);  // 0x00692f90
bool cVarListSerializer_Serialize(void* self, void* stream);     // 0x00693e10

using namespace SP;

// Grow/insert a bit vector to 0x23 elements (eastl::vector<bool> fixed-allocator path), then zero it.
static __forceinline void ResetBitsTo(EastlBitVector* v)
{
    void* begin = v->mpBegin;
    void* end = v->mpEnd;
    if ((uint32_t)((char*)end - (char*)begin) < 0x23) {
        uint8_t zero = 0;
        v->DoFillInsert(end, (int)((char*)begin - (char*)end) + 0x23, &zero);
    } else {
        void* pos = (char*)begin + 0x23;
        EastlVectorBoolDoInsertValue(pos, end, 0);
        v->mpEnd = (char*)v->mpEnd + ((char*)pos - (char*)end);
    }
    for (int i = 0; i < 0x23; ++i)
        ((uint8_t*)v->mpBegin)[i] = 0;
}

// Same, but without the trailing zero fill (used by the serialise-then-normalise path).
static __forceinline void ResizeBitsTo(EastlBitVector* v)
{
    void* begin = v->mpBegin;
    void* end = v->mpEnd;
    if ((uint32_t)((char*)end - (char*)begin) < 0x23) {
        uint8_t zero = 0;
        v->DoFillInsert(end, (int)((char*)begin - (char*)end) + 0x23, &zero);
    } else {
        void* pos = (char*)begin + 0x23;
        EastlVectorBoolDoInsertValue(pos, end, 0);
        v->mpEnd = (char*)v->mpEnd + ((char*)pos - (char*)end);
    }
}


// @ 0x00586690
void cAppModeEditorBase::InitializeUndoList()
{
    mUndosLeft = 0;
    UndoVector& undo = mUndoList;
    undo.erase(undo.mpBegin, undo.mpEnd);
    mUndoLocalStateList.erase(mUndoLocalStateList.mpBegin, mUndoLocalStateList.mpEnd);
    FUN_00586410(0, 0);
    mDevUI->EnableUndoButton(0);
    mDevUI->EnableRedoButton(0);
    *(bool*)((char*)this + 0x4b3) = 0;
    *(bool*)((char*)this + 0x4b4) = 0;
    mDevUI->UpdateUIBasedOnModelSaveability();
}

// @ 0x00586410
// Pushes a new editor resource onto the undo list: trims the list to mUndosLeft, creates or adds a
// reference to the resource, snapshots it via GetState, creates the save object, then refreshes the
// UI and the part mask.  (Reconstructed from the disassembly; /O2 codegen differs.)
void cAppModeEditorBase::FUN_00586410(char a, void* b)
{
    int count = (int)((char*)mUndoList.mpEnd - (char*)mUndoList.mpBegin) >> 2;
    if (mUndosLeft < count) {
        VectorResize(&mUndoList, mUndosLeft);                                   // 0x005e77e0
        ((cIntVec*)((char*)this + 0x160))->Resize((unsigned)mUndosLeft);        // 0x00584160
    }
    if (mUndosLeft > 0)
        *(bool*)((char*)this + 0x4b3) = true;

    void* state = 0;                                                            // AutoRefCount local
    if (b != 0) {
        (*(void(__thiscall**)(void*, int))(*(uint32_t*)b + 4))(b, 0);           // AddRef
        state = b;
    } else {
        void* obj = operator new(0x2c, "Editor", 0, 0, 0, 0);                   // 0x00f473a0
        if (obj != 0) {
            *(uint32_t*)((char*)obj + 4) = 0;
            *(uint32_t*)obj = 0x14774b0;
            *(uint32_t*)((char*)obj + 8) = 0;
            *(uint32_t*)((char*)obj + 0xc) = 0;
            *(uint32_t*)((char*)obj + 0x10) = 0;
            *(uint8_t*)((char*)obj + 0x14) = 0;
            *(uint8_t*)((char*)obj + 0x15) = 0;
            *(uint32_t*)((char*)obj + 0x18) = 0;
            *(uint32_t*)((char*)obj + 0x1c) = 0;
            *(uint32_t*)((char*)obj + 0x20) = 0;
            *(uint32_t*)((char*)obj + 0x24) = 0;
            *(uint32_t*)((char*)obj + 0x28) = 0;
            (*(void(__thiscall**)(void*))(*(uint32_t*)obj + 4))(obj);
            state = obj;
        }
        GetState(state);                                                        // 0x00574080
    }

    {   // push_back(state) into mUndoLocalStateList (+0x160)
        UndoVector& v = mUndoLocalStateList;
        if ((char*)v.mpEnd < (char*)v.mpCapacity) {
            void* slot = v.mpEnd;
            v.mpEnd = (char*)v.mpEnd + 4;
            if (slot != 0) {
                *(void**)slot = state;
                if (state)
                    (*(void(__thiscall**)(void*))(*(uint32_t*)state + 4))(state);
            }
        } else {
            FUN_005c8480(&v, v.mpEnd, &state);                                  // 0x005c8480
        }
    }

    void* save = 0;
    {
        void* p = operator new(0xac, "Editor", 0, 0, 0, 0);
        if (p != 0)
            save = FUN_004b9c70(p);                                             // 0x004b9c70
    }
    b = save;
    if (save != 0)
        (*(void(__thiscall**)(void*))(*(uint32_t*)save + 0))(save);
    mEditorSaveModel->SaveResource(save);                                       // 0x004af260

    {   // push_back(save) into mUndoList (+0x174)
        UndoVector& v = mUndoList;
        if ((char*)v.mpEnd < (char*)v.mpCapacity) {
            void* slot = v.mpEnd;
            v.mpEnd = (char*)v.mpEnd + 4;
            if (slot != 0) {
                *(void**)slot = save;
                if (save)
                    (*(void(__thiscall**)(void*))(*(uint32_t*)save + 0))(save);
            }
        } else {
            FUN_006650c0(&v, v.mpEnd, &save);                                   // 0x006650c0
        }
    }

    cSPEditorUI* ui = mDevUI;
    mUndosLeft += 1;
    if (ui != 0) {
        ui->EnableRedoButton(0);
        ui->EnableUndoButton(mUndosLeft > 1);
    }
    mEditorSaveModel->FUN_004adfc0(0);                                          // 0x004adfc0
    if (a != 0)
        SetAnimCaptureOn(0);                                                    // 0x00583c50

    if (*(int*)((char*)this + 0x31c) == 0) {
        if (*(int*)((char*)this + 0x360) != 0 && *(int*)((char*)this + 0x364) != 0) {
            if (*(uint8_t*)((char*)this + 0x385) != 0)
                FUN_0057e340(this, 0);                                          // 0x0057e340
            ((cAnimCreatureMgr*)*(void**)((char*)this + 0x360))
                ->RemoveCreature(*(void**)((char*)this + 0x364));               // 0x0059c6e0
            *(uint32_t*)((char*)this + 0x364) = 0;
        }
        *(uint8_t*)((char*)this + 0x39a) = 1;
    }

    {
        void* last = *(void**)((char*)mUndoList.mpEnd - 4);
        uint32_t r = (*(uint32_t(__thiscall**)(void*))(*(uint32_t*)mEditorSaveModel + 4))(mEditorSaveModel);
        uint32_t mask[4];
        BuildPartMask(mask, last, (void*)r, 1);                                 // 0x0057ac00
        *(uint32_t*)((char*)this + 0x48) = mask[0];
        *(uint32_t*)((char*)this + 0x4c) = mask[1];
        *(uint32_t*)((char*)this + 0x50) = mask[2];
        *(uint32_t*)((char*)this + 0x54) = mask[3];
    }
    if (mDevUI)
        mDevUI->UpdateUIBasedOnModelSaveability();                              // 0x005dd7a0

    if (save != 0)
        (*(void(__thiscall**)(void*))(*(uint32_t*)save + 4))(save);
    if (state != 0)
        (*(void(__thiscall**)(void*))(*(uint32_t*)state + 8))(state);
}

// @ 0x00586700
// Resets the main bit vector (+0x4d8) and the six per-slot bit vectors (+0x508, stride 0x14) to
// 0x23 zero bytes each, clearing the slot counters at +0x4f0 and the word at +0x4ec.
void cAppModeEditorBase::FUN_00586700()
{
    ResetBitsTo((EastlBitVector*)((char*)this + 0x4d8));
    *(uint32_t*)((char*)this + 0x4ec) = 0;
    for (int s = 0; s < 6; ++s) {
        *(uint32_t*)((char*)this + 0x4f0 + s * 4) = 0;
        ResetBitsTo((EastlBitVector*)((char*)this + 0x508 + s * 0x14));
    }
}

// @ 0x00586800
// Appends one zero element to every bit vector, serialises the editor state through
// cVarListSerializer, then normalises every bit vector back to 0x23 elements.  Returns the
// serialiser's success flag.
uint8_t cAppModeEditorBase::FUN_00586800(void* a)
{
    {
        EastlBitVector* v = (EastlBitVector*)((char*)this + 0x4d8);
        void* begin = v->mpBegin;
        void* end = v->mpEnd;
        EastlVectorBoolDoInsertValue(begin, end, 0);                            // 0x011e0744
        v->mpEnd = (char*)v->mpEnd + ((char*)begin - (char*)end);
    }
    for (int s = 0; s < 6; ++s) {
        EastlBitVector* v = (EastlBitVector*)((char*)this + 0x508 + s * 0x14);
        void* begin = v->mpBegin;
        void* end = v->mpEnd;
        EastlVectorBoolDoInsertValue(begin, end, 0);
        v->mpEnd = (char*)v->mpEnd + ((char*)begin - (char*)end);
    }

    uint8_t ser[0xa14];
    cVarListSerializer_Construct(ser, this, (void*)0x150d100, 0x1a80d26);       // 0x00692f90
    bool ok = cVarListSerializer_Serialize(ser, a);                             // 0x00693e10

    {
        EastlBitVector* v = (EastlBitVector*)((char*)this + 0x4d8);
        if ((uint32_t)((char*)v->mpEnd - (char*)v->mpBegin) != 0x23)
            ResizeBitsTo(v);
    }
    for (int s = 0; s < 6; ++s) {
        EastlBitVector* v = (EastlBitVector*)((char*)this + 0x508 + s * 0x14);
        if ((uint32_t)((char*)v->mpEnd - (char*)v->mpBegin) != 0x23)
            ResizeBitsTo(v);
    }
    return ok ? 1 : 0;
}

// @ 0x00586960
// SP::cAppModeEditorBase::ScaleBlock.  Clears the current block, rebuilds the limb structure from
// the surviving limbs (respecting the symmetry mode), resets the block handles and re-initialises
// the undo state.
void cAppModeEditorBase::FUN_00586960()
{
    *(uint8_t*)((char*)this + 0x472) = 0;
    {
        void* s = GetSetting6();                                                // 0x00401060
        if (s != 0)
            (*(void(__thiscall**)(void*, unsigned, float, float, int))(*(uint32_t*)s + 0x1c))
                (s, 0x1002u, 0.0f, 0.0f, 1);
    }

    bool doRebuild;
    void* block = *(void**)((char*)this + 0x48c);
    if (block != 0) {
        DeleteInvalidBlocks(block, 0);                                          // 0x004a6f10
        uint32_t flags = *(uint32_t*)((char*)block + 0xdc8);
        doRebuild = ((flags >> 7) & 1) != 0 || ((flags >> 0xb) & 1) != 0;
    } else if (*(void**)((char*)this + 0x490) != 0) {
        void* b2 = ((cSPEditorHandle*)*(void**)((char*)this + 0xe4))->GetEditorBlock();  // 0x0047e6c0
        if (b2 != 0)
            DeleteInvalidBlocks(b2, 0);
        void* o = *(void**)((char*)this + 0x490);
        uint32_t id = (*(uint32_t(__thiscall**)(void*))(*(uint32_t*)o + 0x10))(o);
        doRebuild = (id == 0x50e8e23);
    } else {
        doRebuild = false;
    }

    if (doRebuild) {
        bool sym = mEditorSaveModel->UsingSymmetry();                           // 0x004adc40
        mEditorSaveModel->FUN_004adc20(0);                                      // 0x004adc20
        void* limbs[3] = { 0, 0, 0 };
        GetAllLimbs(*(void**)((char*)*(void**)((char*)this + 0x14c) + 0xec), limbs, sym);  // 0x004a0020
        int n;
        {
            cSPEditorLimbStructure ls;                                          // 0x00488850
            n = (int)((char*)limbs[1] - (char*)limbs[0]) >> 2;
            for (int i = 0; i < n; ++i) {
                ls.BuildLimb(*(void**)((char*)limbs[0] + i * 4), 0, false);     // 0x004891a0
                ls.FUN_0048a4c0();                                              // 0x0048a4c0
                ls.FUN_00488980();                                              // 0x00488980
            }
            mEditorSaveModel->FUN_004adc20(sym ? 1 : 0);
        }                                                                       // ~cSPEditorLimbStructure
        if (limbs[0] != 0 && *(int*)((char*)limbs[0] - 4) != 0)
            operator delete[](limbs[0]);                                        // 0x00f47380
    }

    *(void**)((char*)this + 0x48c) = 0;
    *(void**)((char*)this + 0x490) = 0;
    if (*(void**)((char*)this + 0x14c) != 0)
        ((cSpine75*)*(void**)((char*)this + 0x14c))->SetFlag(0, 1);             // 0x005d1600
    FUN_00586410(1, 0);
}

// @ 0x00585d40
// Multi-stage "save in progress" state machine (mSaveState 1..5): score the creature, capture the
// animated GIF, paint the skin, then render the large and small thumbnails and finish.
void cAppModeEditorBase::ContinueSaveInProgress()
{
    if (mSaveState == 1) {
        mLargeImageReady = false;
        mSmallImageReady = false;
        cPaletteUI* pal = mPaletteUILoaded;
        if (pal && pal->mpSub)
            pal->mpSub->vfn50(0);
        cPedestalModel* ped = mPedastalModel;
        ped->mScore = ScoreCreatureForZCorp();
        if (mDeleteValueFadeTime > 0) {
            int n = sAppProperties->GetIntProperty(0x5893ee8);
            if (mDeleteValueFadeTime - 1 > (uint32_t)(n * n))
                SetAnimCaptureOn(1);
        }
        mSaveState = 2;
    }
    if (mSaveState == 2) {
        if (mDeleteValueFadeTime > 0) {
            if (mCaptureBusy)
                return;
            uint32_t size[2] = { 0xffffffff, 0xffffffff };
            int prop = sAppProperties->GetIntProperty(0x5893ed4);
            FUN_0067dd40()->vfnC4(size);
            EmptyStr name = { gEmptyString, gEmptyString, gEmptyString + 1 };
            CaptureGIF(&name);
            int n = sAppProperties->GetIntProperty(0x5893ee8);
            uint32_t area = n * n;
            float rate = sAppProperties->GetFloatProperty(0x6243d0a);
            uint32_t x1, x2;
            cObj67dda0* o;
            if (mDeleteValueFadeTime - 1 < area) {
                o = FUN_0067dda0();
                x1 = 0;
                x2 = mDeleteValueFadeTime;
            } else {
                o = FUN_0067dda0();
                x1 = mCurrentInstanceId;
                x2 = area;
            }
            WriteAnimatedCSAGIF(o->vfn18(size[0], size[1]), prop, name.mpBegin, x1, x2, rate, 1, 0);
            FUN_00584070();
            if (name.mpCap - name.mpBegin > 1 && name.mpBegin)
                operator delete[]((void*)name.mpBegin);
        }
        if (mPaintedSkinSave && mTextureFactory) {
            if (mSaveLoadFactory && mSaveLoadFactory->IsBusy())
                FUN_00401080()->Handle(mSaveLoadFactory->GetSub());
            mTextureFactory->Begin(1);
            mTextureFactory->Apply((cEditorModelStub*)mPedastalModel);
        }
        if (mPaletteUILoaded && mEffectsMaskViewer) {
            ((cAnimCreatureMgr*)mPaletteUILoaded)->RemoveCreature(mEffectsMaskViewer);
            mEffectsMaskViewer = 0;
        }
        RunSkinPaintOnEditorModel(2, 0);
        mSaveState = 3;
    }
    if (mSaveState == 3) {
        if (mPaintedSkinSave && mTextureFactory && mTextureFactory->IsBusy())
            { FUN_0067dd50()->vfn84(0x7fffffff); return; }
        if (mTextureFactory)
            mTextureFactory->UpdatePaintedSkin();
        if (mLaunchData && mEditorSaveModel->mNameHash == 0xdfad9f51) {
            float* p = &mShaderParam;
            *p = sAppProperties->GetFloatProperty(0x678aff6);
            shader(0x236, p, 1);
        }
        mLargeImage.Assign(FUN_0067dd60()->vfn3C(0x4694e41, 0x4694e48, 0x100, 0x100, 1, 0x208, 0x15, 8));
        FUN_00580700(mPedastalModel, mSaveModelWorld, 0x100, mCurrencyIconGroup, 0x1c94703, mLargeImage.p);
        mSaveState = 4;
    }
    if (mSaveState == 4) {
        if (!mLargeImageReady) { FUN_0067dd50()->vfn84(0x7fffffff); return; }
        cResMgrStub* mgr = GetManager();
        uint32_t area = GetSaveArea(mSaveAreaId);
        FUN_0067dd60()->vfn68(mLargeImage.p);
        cImageRef* img = mLargeImage.p;
        if (!(img->mFlags & 1))
            FUN_0067dd60()->vfn34(img);
        cPedestalModel* ped = mPedastalModel;
        void* handle = (void*)img->mHandle;
        Vec3U pos = ped->mPos;
        if (handle && mgr) {
            cSaveRequest* req = new ("Editor", 0, 0, 0, 0) cSaveRequest();
            cMsgSub* sub = req;
            req->vfn0();
            req->mpImage = handle;
            req->vfn0();
            sub->mTrans = pos.x;
            sub->mMsgId = 0x2f7d0004;
            sub->mFlags = (pos.z & 0xffffff01) | 1;
            mgr->vfn20(sub, 0, (void*)area, mUndoStateRef, 0);
            req->mpImage = 0;
            req->vfn0();
            req->vfn4();
        }
        ReleaseImage(mLargeImage.p);
        uint32_t cfg = mLaunchData ? mLaunchData->mConfig : 0x4694e35;
        mSmallImage.Assign(FUN_0067dd60()->vfn3C(cfg, 0x4694e3b, 0x80, 0x80, 1, 0x208, 0x15, 8));
        FUN_00580700(mPedastalModel, mSaveModelWorld, 0x80, mCurrencyIconGroup, 0x1c94708, mSmallImage.p);
        mSaveState = 5;
    }
    if (mSaveState != 5)
        return;
    if (mSmallImageReady) {
        SaveSomething();
        bool translate = mTranslateModelOnSave;
        Vec3U pos = mPedastalModel->mPos;
        if (translate)
            mParentModelKey = pos;
        else {
            mParentModelKey.x = 0;
            mParentModelKey.y = 0;
            mParentModelKey.z = 0;
        }
        FUN_00585c10();
        if (mCurrentCreatureMode == 1)
            mAnimCaptureState = 0;
        else
            FUN_00573f70(1);
        MessageServer()->vfn14(0x165e841, &pos, 0);
        if (mSaveLoadFactory && mSaveLoadFactory->GetFlag84()) {
            cSkinFactoryStub* sub = (cSkinFactoryStub*)mSaveLoadFactory->GetSub();
            if (sub && ((char*)sub)[0x6b]) {
                cEditorModelStub* model = mEditorSaveModel;
                if ((!mTextureFactory || !mTextureFactory->IsBusy()) && model && mSaveLoadFactory)
                    mSaveLoadFactory->Apply(model);
            }
        }
        ReleaseImage(mSmallImage.p);
        FUN_006b2350();
        if (mLaunchData && mEditorSaveModel->mNameHash == 0xdfad9f51)
            shader(0x236, &mLaunchData->mShaderParam, 1);
        MessageManager()->Post(0x3f1bf53, 0);
        return;
    }
    FUN_0067dd50()->vfn84(0x7fffffff);
}
