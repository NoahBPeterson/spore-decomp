// Slice s00e49a40 -- mission panel update: a window slides/rotates in and out through an 8-state machine.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- data types
struct Key12 { uint32_t a, b, c; };
struct Vec4 {
    float x, y, z, w;
    Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
    Vec4(const Vec4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};

// ---------------------------------------------------------------- globals
extern float g_15a5b54;                // 0x015a5b54: rotation angle
extern float g_15a5b58;                // 0x015a5b58: extra rotation offset

// ---------------------------------------------------------------- external objects
struct IWindow {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4();
    virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9();
    virtual void w10(); virtual void w11(); virtual void w12();
    virtual const float* GetOffset();                   // +0x34 (two floats)
    virtual void w14(); virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18();
    virtual void w19(); virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
    virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
    virtual void SetAnchor(float x, float y);           // +0x70
    virtual void w29(); virtual void w30();
    virtual void SetFlag(int flag, bool value);         // +0x7c
};
struct IReleasable { virtual void w0(); virtual void Release(); };   // Release at +4

struct cModel {                                         // result of cMission::GetModel
    virtual void w0();  virtual void w1();  virtual void w2();  virtual void w3();  virtual void w4();
    virtual void w5();  virtual void w6();  virtual void w7();  virtual void w8();  virtual void w9();
    virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14();
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
    virtual int GetKind();                              // +0x60
};
struct cMission {
    cModel*  GetModel();                                // 0x00c45ce0
    IWindow* GetPanelWindow();                          // 0x00ff35d0
};
struct cModelPanel {                                    // FUN_00e19cf0(model)
    virtual void w0();  virtual void w1();  virtual void w2();  virtual void w3();  virtual void w4();
    virtual void w5();  virtual void w6();  virtual void w7();  virtual void w8();  virtual void w9();
    virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14();
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24();
    virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29();
    virtual void Notify();                              // +0x78
};
cModelPanel* __cdecl FUN_00e19cf0(cModel* model);       // 0x00e19cf0

struct cSink {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4();
    virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9();
    virtual void SetActive(int on);                     // +0x28
};
extern cSink* g_169e230;                                // 0x0169e230

struct cImage { uint32_t pad0; uint8_t flags; };        // flags at +4, bit 0 = loaded
struct cResourceManager {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4();
    virtual void w5(); virtual void w6();
    virtual cImage* GetImage(Key12 key, int flags);     // +0x1c
};
cResourceManager* __cdecl FUN_0067dd60();               // 0x0067dd60
int __cdecl GetCurrentGameMode();                       // 0x00b5b800

struct cImageRef {
    cImage* p;
    void Set(cImage* img);                              // 0x00576650
};

struct AnimBuf {
    uint32_t d[0x80 / 4];
    void Destroy();                                     // 0x0059a1e0: ~cSPUIWindowAnimation
};
struct cAnimator {
    void RemoveAnimation(IWindow* win, int channel);    // 0x007f6210
    void AddAnimation(AnimBuf* anim, IWindow* win, int flags);   // 0x007f8d10
    void Update();                                      // 0x007f63b0
};
AnimBuf* __cdecl SPUICreateWindowAnimationRotation(AnimBuf* out, IWindow* win, Vec4 rot,
                                                   float duration, float from, int type);   // 0x007f8140
float __cdecl GetElapsedSeconds();                      // 0x00805080
struct Quat { float x, y, z, w; };
void __cdecl SetWindowRotation(IWindow* win, const Quat* quat);   // 0x00808230

struct cSubPanel { void FUN_00e49db0(); };              // 0x00e49db0

// ---------------------------------------------------------------- the panel
struct cMissionPanel {
    char       pad0[0xc];
    char       mbFlag;            // +0x0c
    char       pad1[0x18 - 0xd];
    cMission*  mpMission;         // +0x18
    cImageRef  mImage;            // +0x1c
    IWindow*   mpWindow;          // +0x20
    char       pad2[0x38 - 0x24];
    cSubPanel  mSub;              // +0x38
    char       pad3[0x40 - 0x39];
    Key12*     mpTarget;          // +0x40
    char       pad4[0x50 - 0x44];
    Key12*     mpShown;           // +0x50
    char       pad5[0x88 - 0x54];
    int        mState;            // +0x88
    float      mTimer;            // +0x8c
    cAnimator* mpAnimator;        // +0x90
    float      mDuration;         // +0x94
    float      mDuration2;        // +0x98
    float      mDuration3;        // +0x9c

    void FUN_00e493c0(Key12 key);                       // 0x00e493c0
    void Update(float dt);                              // 0x00e49f80
};

// @ 0x00e49f80
void cMissionPanel::Update(float dt)
{
    AnimBuf animA, animB, animC, animD, animE;
    Key12 key;
    Quat qB, qC;
    IWindow* panelWin = 0;
    mpWindow->SetAnchor(4.0f, 10.0f);
    if (mpMission != 0) {
        panelWin = mpMission->GetPanelWindow();
        if (panelWin != 0) {
            const float* off = panelWin->GetOffset();
            mpWindow->SetAnchor(off[0], off[1]);
        }
    }
    mTimer = dt + mTimer;

    switch (mState)
    {
    case 0:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mbFlag) {
            cMission* m = mpMission;
            if (m != 0) {
                mpMission = 0;
                ((IReleasable*)m)->Release();
            }
            mbFlag = 1;
        }
        if (mpTarget != mpShown) {
            if (mbFlag != 1) {
                if (mpMission->GetModel()->GetKind() == 5) break;
            }
            key = *mpTarget;
            key.b = 0x2f7d0004;
            key.c = (GetCurrentGameMode() != 0x1654c00) ? 0x02231c8b : 0xb1b0f42e;
            mImage.Set(FUN_0067dd60()->GetImage(key, 0));
            if (mImage.p != 0) mState = 1;
            else               mSub.FUN_00e49db0();
        }
        break;

    case 1:
        if (panelWin) panelWin->SetFlag(1, true);
        if (!(mImage.p->flags & 1)) break;
        if (mbFlag != 0) {
            FUN_00e493c0(*mpTarget);
            mSub.FUN_00e49db0();
            mpAnimator->RemoveAnimation(mpWindow, -1);
            qB.x = 0.0f; qB.y = 1.0f; qB.z = 0.0f; qB.w = g_15a5b54 + g_15a5b58;
            SetWindowRotation(mpWindow, &qB);
            mpWindow->SetFlag(1, true);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animB, mpWindow, Vec4(0.0f, 1.0f, 0.0f, g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 2),
                mpWindow, 0);
            animB.Destroy();
            mTimer = 0.0f;
            mState = 3;
        } else {
            mpAnimator->RemoveAnimation(panelWin, -1);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animA, panelWin, Vec4(0.0f, 1.0f, 0.0f, g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 1),
                panelWin, 0);
            animA.Destroy();
            mTimer = 0.0f;
            mState = 2;
        }
        break;

    case 2:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mTimer > mDuration) {
            FUN_00e493c0(*mpTarget);
            mSub.FUN_00e49db0();
            mpAnimator->RemoveAnimation(mpWindow, -1);
            qC.x = 0.0f; qC.y = 1.0f; qC.z = 0.0f; qC.w = g_15a5b54 + g_15a5b58;
            SetWindowRotation(mpWindow, &qC);
            mpWindow->SetFlag(1, true);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animC, mpWindow, Vec4(0.0f, 1.0f, 0.0f, g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 2),
                mpWindow, 0);
            animC.Destroy();
            mTimer = 0.0f;
            mState = 3;
        }
        break;

    case 3:
        if (panelWin) panelWin->SetFlag(1, false);
        if (mTimer > mDuration) {
            mTimer = 0.0f;
            mState = 4;
        }
        break;

    case 4:
        if (panelWin) panelWin->SetFlag(1, false);
        if (mTimer > mDuration2) {
            mpAnimator->RemoveAnimation(mpWindow, -1);
            mpAnimator->AddAnimation(
                SPUICreateWindowAnimationRotation(&animD, mpWindow, Vec4(0.0f, 1.0f, 0.0f, -g_15a5b54),
                                                  GetElapsedSeconds(), mDuration, 1),
                mpWindow, 0);
            animD.Destroy();
            mTimer = 0.0f;
            mState = 5;
        }
        break;

    case 5:
        if (panelWin) panelWin->SetFlag(1, false);
        if (mTimer > mDuration) {
            if (mbFlag == 0) {
                mpWindow->SetFlag(1, false);
                mpAnimator->RemoveAnimation(panelWin, -1);
                mpAnimator->AddAnimation(
                    SPUICreateWindowAnimationRotation(&animE, panelWin, Vec4(0.0f, 1.0f, 0.0f, -g_15a5b54),
                                                      GetElapsedSeconds(), mDuration, 2),
                    panelWin, 0);
                animE.Destroy();
                mTimer = 0.0f;
                mState = 6;
            } else {
                mState = 0;
            }
        }
        break;

    case 6:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mTimer > mDuration) {
            mTimer = 0.0f;
            mState = 7;
            cModel* model = mpMission->GetModel();
            if (model->GetKind() == 4) {
                cModelPanel* panel = FUN_00e19cf0(model);
                if (panel != 0) {
                    panel->Notify();
                    if (GetCurrentGameMode() == 0x1654c01)
                        g_169e230->SetActive(0);
                }
            }
        }
        break;

    case 7:
        if (panelWin) panelWin->SetFlag(1, true);
        if (mTimer > mDuration3) {
            mTimer = 0.0f;
            mState = 0;
            mImage.Set(0);
        }
        break;
    }
    mpAnimator->Update();
}

// ================================================================================================
// The rest of the panel's own code.  Init (0x00e49a40), the destructor (0x00e49e80) and the
// constructor (0x00e4a6e0) all agree on the layout modelled below; cMissionPanel above is the
// older partial model that FUN_00e49f80 was written against and puts other fields at some of the
// same offsets, so the real layout gets its own type here.
// ================================================================================================

#include <intrin.h>

extern char g_vtbl_01482478[];      // 0x01482478 primary vtable of the panel
extern char g_vtbl_01482468[];      // 0x01482468 secondary vtable of the panel
extern char g_vtbl_013eb394[];      // 0x013eb394 PaintSystem vtable (first base)
extern char g_vtbl_013ec458[];      // 0x013ec458 cContentValidationSummarizer vtable (second base)
extern char g_vtbl_014824ec[];      // 0x014824ec vtable of cRefHolder

extern void* __cdecl FUN_00f473a0(int size, const char* tag, int a, int b, const char* file, int line);  // 0x00f473a0 operator_new
extern void  __cdecl FUN_00f47380(void* p);                                                 // 0x00f47380 operator_delete
extern void* __cdecl FUN_00926020(int size, const char* tag, int a, int b, int c, int d);   // 0x00926020 ZoneObject_new
extern uint32_t __cdecl FNVHash(const char* s, uint32_t seed, uint32_t flags);              // 0x00932e80

struct Vec4P { float x, y, z, w; };                    // POD vector (Vec4 above has constructors)
struct Key { uint32_t mTypeId, mGroupId, mInstanceId; };                        // EA::ResourceMan::Key

struct IRefCounted {                                    // AddRef +0x00, Release +0x04
    virtual void AddRef();
    virtual void Release();
};
struct IRefCounted2 {                                   // AddRef +0x04, Release +0x08
    virtual void s0();
    virtual void AddRef();
    virtual void Release();
};
struct IWindowRef {                                     // the panel's windows
    virtual void AddRef();                                              // +0x00
    virtual void Release();                                             // +0x04
    virtual void w2();  virtual void w3();  virtual void w4();  virtual void w5();  virtual void w6();
    virtual void w7();  virtual void w8();  virtual void w9();  virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13();                             // +0x34
    virtual const Vec4P* GetPosition();                                 // +0x38
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24();
    virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29();
    virtual void w30();                                                 // +0x78
    virtual void SetFlag(int flag, bool value);                         // +0x7c
};

template <class T> struct RefPtr {                      // ref-counted pointer assignment
    T* mp;
    void Set(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p != 0) p->AddRef();
            mp = p;
            if (old != 0) old->Release();
        }
    }
};

struct cSPUILayout : IRefCounted2 {
    cSPUILayout* Construct();                                           // 0x00810000 (thiscall, returns this)
    bool Init(const Key& key, bool b, uint32_t id);                     // 0x008120d0 (ret 0xc)
    IWindowRef* FindWindowByID(uint32_t id, bool recursive) const;       // 0x008105b0 (ret 8)
};
struct cVehicleAbilities : IRefCounted2 {
    cVehicleAbilities* Init(int mode);                                  // 0x0059f9e0 (ret 4)
};
struct cMissionCardAnimator {
    cMissionCardAnimator* Init();                                       // 0x007f83e0 (returns this)
};
struct cMessage {                                       // event object handed to FUN_00e49d80
    uint32_t mpad00[6];                                                 // +0x00
    uint32_t mEventType;                                                // +0x18
};
struct IMessageServer {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();  // +0x00..0x1c
    virtual void AddHandler(void* handler, uint32_t id);                // +0x20
};
namespace SP { IMessageServer* MessageServer(); }                       // 0x0067dcc0

struct cKeyQueue {                                      // +0x38: deque of Key12, pages of 16 items (0xc0 bytes)
    Key12**  mppBase;                                   // +0x00  page map
    int32_t  mnCapacity;                                // +0x04  page map size
    Key12*   mpCur;                                     // +0x08
    Key12*   mpCurPage;                                 // +0x0c
    Key12*   mpCurEnd;                                  // +0x10
    Key12**  mppCurSlot;                                // +0x14
    Key12*   mpBack;                                    // +0x18
    Key12*   mpBackPage;                                // +0x1c
    Key12*   mpBackEnd;                                 // +0x20
    Key12**  mppBackSlot;                               // +0x24
    void FUN_00e49950(int n);                           // 0x00e49950 (ret 4)      constructor
    void FUN_00e49820(int a, int b);                    // 0x00e49820 (ret 8)      grow the page map
    void Destroy();                                     // 0x00996640
    void FUN_00e49db0();
    void FUN_00e49df0(Key12* key);
};

struct cRefBlock {                                      // object at +0x1c: vtable, then its reference count
    void*   mpVtbl;                                     // +0x00
    int32_t mf04;                                       // +0x04
    volatile long mnRefCount;                           // +0x08
};

struct cUnlockPanel {
    void*        mpVtbl;                                // +0x00  PaintSystem vtable
    void*        mpVtbl2;                               // +0x04  cContentValidationSummarizer vtable
    int32_t      mf08;                                  // +0x08  (a member of the second base)
    bool         mbNoMission;                           // +0x0c
    uint8_t      mpad0d[3];                             // +0x0d
    RefPtr<IRefCounted2> mLayout;                       // +0x10
    RefPtr<IRefCounted2> mAbilities;                    // +0x14
    RefPtr<IRefCounted>  mMission;                      // +0x18
    cRefBlock*   mpImage;                               // +0x1c
    RefPtr<IWindowRef> mW20;                            // +0x20
    RefPtr<IWindowRef> mW24;                            // +0x24
    RefPtr<IWindowRef> mW28;                            // +0x28
    RefPtr<IWindowRef> mW2c;                            // +0x2c
    RefPtr<IWindowRef> mW30;                            // +0x30
    RefPtr<IWindowRef> mW34;                            // +0x34
    cKeyQueue    mQueue;                                // +0x38
    uint32_t     mf60;                                  // +0x60
    Vec4P        mPosA;                                 // +0x64  position of mW30
    Vec4P        mPosB;                                 // +0x74  position of mW20
    float        mWidth;                                // +0x84  width difference of the two positions
    int32_t      mState;                                // +0x88
    float        mTimer;                                // +0x8c
    cMissionCardAnimator* mpAnimator;                   // +0x90
    float        mDuration;                             // +0x94
    float        mDuration2;                            // +0x98
    float        mDuration3;                            // +0x9c

    void FUN_00e496d0();                                // 0x00e496d0
    void FUN_00e49a40(IRefCounted* mission);
    bool FUN_00e49d80(int type, cMessage* msg);
    void FUN_00e49e80();
    cUnlockPanel* FUN_00e4a6e0();
    void FUN_00e4a790(Key12 key);
};

// @ 0x00e49a40
void cUnlockPanel::FUN_00e49a40(IRefCounted* mission)
{
    mMission.Set(mission);
    mbNoMission = (mMission.mp == 0);
    bool inSpace = (GetCurrentGameMode() == 0x1654c00);
    if (mLayout.mp == 0) {
        cSPUILayout* layout = (cSPUILayout*)FUN_00f473a0(0x18, "Simulator", 0, 0, 0, 0);
        layout = layout != 0 ? layout->Construct() : 0;
        mLayout.Set(layout);
        Key key;
        key.mTypeId = 0x2d2eb184;
        key.mGroupId = 0x0510a95b;
        key.mInstanceId = 0x40464100;
        ((cSPUILayout*)mLayout.mp)->Init(key, true, 0xec2fd2c3);
    }
    if (mAbilities.mp == 0) {
        cVehicleAbilities* abilities = (cVehicleAbilities*)FUN_00f473a0(0x70, "UI", 0, 0, 0, 0);
        abilities = abilities != 0
                  ? abilities->Init(0x9ea3031a + (inSpace ? 0x410a9c37 : 0))
                  : 0;
        mAbilities.Set(abilities);
    }
    if (mpAnimator == 0) {
        cMissionCardAnimator* animator =
            (cMissionCardAnimator*)FUN_00f473a0(0x20, "UI/UnlockCardAnimator", 0, 0, 0, 0);
        mpAnimator = animator != 0 ? animator->Init() : 0;
    }
    cSPUILayout* layout = (cSPUILayout*)mLayout.mp;
    mW20.Set(layout->FindWindowByID(0x9554487e, true));
    mW24.Set(layout->FindWindowByID(0xf554489d, true));
    mW28.Set(layout->FindWindowByID(0x3554489e, true));
    mW2c.Set(layout->FindWindowByID(0x9554489f, true));
    mW30.Set(layout->FindWindowByID(0x755448a0, true));
    mW34.Set(layout->FindWindowByID(0x755ab697, true));
    mW20.mp->SetFlag(1, false);
    const Vec4P* posA = mW30.mp->GetPosition();
    mPosA.x = posA->x;
    mPosA.y = posA->y;
    mPosA.z = posA->z;
    mPosA.w = posA->w;
    const Vec4P* posB = mW20.mp->GetPosition();
    mPosB.x = posB->x;
    mPosB.y = posB->y;
    mPosB.z = posB->z;
    mPosB.w = posB->w;
    mWidth = (mPosB.z - mPosB.x) - (mPosA.z - mPosA.x);
    IMessageServer* server = SP::MessageServer();
    server->AddHandler(this, 0xf62def);
    FUN_00e496d0();
}

// @ 0x00e49d80
bool cUnlockPanel::FUN_00e49d80(int type, cMessage* msg)
{
    if (type == 0xf62def && msg->mEventType == 0x5c770db7)
        FUN_00e496d0();
    return false;
}

// @ 0x00e49db0
void cKeyQueue::FUN_00e49db0()
{
    Key12* next = mpCur + 1;
    if (next == mpCurEnd) {
        if (mpCurPage != 0)
            FUN_00f47380(mpCurPage);
        Key12** slot = mppCurSlot + 1;
        mppCurSlot = slot;
        mpCurPage = *slot;
        mpCurEnd = mpCurPage + 16;
        next = mpCurPage;
    }
    mpCur = next;
}

// @ 0x00e49df0
void cKeyQueue::FUN_00e49df0(Key12* key)
{
    Key12 copy = *key;
    if ((mppBackSlot - mppBase) + 1 >= mnCapacity)
        FUN_00e49820(1, 1);
    Key12* page = (Key12*)FUN_00f473a0(0xc0, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    mppBackSlot[1] = page;
    if (mpBack != 0) *mpBack = copy;
    Key12** slot = mppBackSlot + 1;
    mppBackSlot = slot;
    mpBackPage = *slot;
    mpBackEnd = mpBackPage + 16;
    mpBack = mpBackPage;
}

// @ 0x00e49e80
void cUnlockPanel::FUN_00e49e80()
{
    // the two stores the compiler emits for a destructor of a two-base class
    mpVtbl = g_vtbl_01482478;
    mpVtbl2 = g_vtbl_01482468;
    mQueue.Destroy();
    IWindowRef* window = mW34.mp;
    if (window != 0) window->Release();
    window = mW30.mp;
    if (window != 0) window->Release();
    window = mW2c.mp;
    if (window != 0) window->Release();
    window = mW28.mp;
    if (window != 0) window->Release();
    window = mW24.mp;
    if (window != 0) window->Release();
    window = mW20.mp;
    if (window != 0) window->Release();
    if (mpImage != 0) {                                 // inlined EA::RefCountTemplate<int>::Release
        volatile long* count = &mpImage->mnRefCount;
        _InterlockedDecrement(count);
        if (_InterlockedExchangeAdd(count, 0) < 1)
            _InterlockedExchangeAdd(count, 1);
        else
            _InterlockedExchangeAdd(count, 0);
    }
    if (mMission.mp != 0) mMission.mp->Release();
    if (mAbilities.mp != 0) mAbilities.mp->Release();
    if (mLayout.mp != 0) mLayout.mp->Release();
    // and the two base-class stores at the end of a destructor
    mpVtbl2 = g_vtbl_013ec458;
    mpVtbl = g_vtbl_013eb394;
}

// @ 0x00e4a6e0
cUnlockPanel* cUnlockPanel::FUN_00e4a6e0()
{
    // the base-class constructor and the two derived-class stores of the real constructor
    mpVtbl2 = g_vtbl_013ec458;
    mf08 = 0;
    mpVtbl = g_vtbl_01482478;
    mpVtbl2 = g_vtbl_01482468;
    mbNoMission = false;
    mLayout.mp = 0;
    mAbilities.mp = 0;
    mMission.mp = 0;
    mpImage = 0;
    mW20.mp = 0;
    mW24.mp = 0;
    mW28.mp = 0;
    mW2c.mp = 0;
    mW30.mp = 0;
    mW34.mp = 0;
    cKeyQueue* queue = &mQueue;
    queue->mppBase = 0;
    queue->mnCapacity = 0;
    queue->mpCur = 0;
    queue->mpCurPage = 0;
    queue->mpCurEnd = 0;
    queue->mppCurSlot = 0;
    queue->mpBack = 0;
    queue->mpBackPage = 0;
    queue->mpBackEnd = 0;
    queue->mppBackSlot = 0;
    queue->FUN_00e49950(0);
    mTimer = 0.0f;
    mDuration = 0.5f;
    mDuration2 = 5.0f;
    mDuration3 = 2.0f;
    mState = 0;
    mpAnimator = 0;
    return this;
}

// @ 0x00e4a790
void cUnlockPanel::FUN_00e4a790(Key12 key)
{
    cKeyQueue* queue = &mQueue;
    Key12* slot = queue->mpBack;
    if (slot + 1 != queue->mpBackEnd) {
        queue->mpBack = slot + 1;
        if (slot != 0) *slot = key;
    } else {
        queue->FUN_00e49df0(&key);
    }
}

// ================================================================================================
// Reflection/type-description helpers that share the TU.
// ================================================================================================

struct cFieldDef {                                      // 0x28 bytes; mf08 == -1 ends the array
    uint32_t mf00;                                      // +0x00
    uint32_t mf04;                                      // +0x04
    int32_t  mf08;                                      // +0x08
    uint32_t mf0c;                                      // +0x0c
    int32_t  mChild;                                    // +0x10  a type reference
    uint32_t mf14;                                      // +0x14  (4 = flag tested by FUN_00e4a960)
    uint32_t mf18;                                      // +0x18
    uint32_t mf1c;                                      // +0x1c
    uint32_t mf20;                                      // +0x20
    uint32_t mf24;                                      // +0x24
};
namespace SP {
struct cTypeDef {
    const char* mpName;                                 // +0x00
    cFieldDef*  mpFields;                               // +0x04
    uint32_t    mTypeHash;                              // +0x08
    uint32_t    mSize;                                  // +0x0c
    uint32_t    mTypeFlags;                             // +0x10
    uint32_t    mVersion;                               // +0x14
    void*       mpVersioningFunction;                   // +0x18
    void*       mpPostProcessFunction;                  // +0x1c
    void*       mpPostLoadFunction;                     // +0x20
    void*       mpPostUnloadFunction;                   // +0x24
    cTypeDef*   mpNext;                                 // +0x28
    cTypeDef(const char* name, cFieldDef* fields, uint32_t typeHash, uint32_t size,
             uint32_t typeFlags, uint32_t version, void* versioningFunction,
             void* postProcessFunction, void* postLoadFunction, void* postUnloadFunction);
};
cTypeDef* g_pTypeList;                                  // 0x016ad064
uint32_t sHash(const char* s);
}

// @ 0x00e4a7d0
SP::cTypeDef::cTypeDef(const char* name, cFieldDef* fields, uint32_t typeHash, uint32_t size,
                       uint32_t typeFlags, uint32_t version, void* versioningFunction,
                       void* postProcessFunction, void* postLoadFunction, void* postUnloadFunction)
    : mpName(name), mpFields(fields), mTypeHash(typeHash), mSize(size), mTypeFlags(typeFlags),
      mVersion(version), mpVersioningFunction(versioningFunction),
      mpPostProcessFunction(postProcessFunction), mpPostLoadFunction(postLoadFunction),
      mpPostUnloadFunction(postUnloadFunction)
{
    if (mTypeFlags & 1) {
        mpNext = SP::g_pTypeList;
        SP::g_pTypeList = this;
    }
}

struct cRefBase { void FUN_008dde10(); };               // 0x008dde10 base destructor (thiscall)
struct cCallbackTable {                                 // object pointed to by cRefHolder::mpCallbacks
    uint32_t mpad00[9];                                 // +0x00..0x23
    void (*mpfn24)(void* arg);                          // +0x24
};
struct cRefHolder : cRefBase {
    void*           mpVtbl;                             // +0x00
    uint32_t        mpad04[4];                          // +0x04..0x13
    void*           mpArg;                              // +0x14
    uint32_t        mf18;                               // +0x18
    cCallbackTable* mpCallbacks;                        // +0x1c
    void* FUN_00e4a860(int deleteFlag);
};

// @ 0x00e4a860
void* cRefHolder::FUN_00e4a860(int deleteFlag)
{
    mpVtbl = g_vtbl_014824ec;                           // the vtable store of the deleting destructor
    if (mpCallbacks != 0 && mpCallbacks->mpfn24 != 0)
        mpCallbacks->mpfn24(mpArg);
    FUN_008dde10();
    if (deleteFlag & 1)
        FUN_00f47380(this);
    return this;
}

// @ 0x00e4a8a0
int32_t FUN_00e4a8a0(int32_t type)
{
    if (type > 0xc)
        return ((const SP::cTypeDef*)type)->mSize;
    switch (type) {
    case 1: case 2: case 3: case 5: case 6: case 7: return 4;
    case 8:  return 0xc;
    case 10: return 0xa0;
    case 9:  return 0x24;
    case 11: return 8;
    default: break;
    }
    return 0;
}

// @ 0x00e4a910
bool FUN_00e4a910(int32_t type)
{
    if (type <= 0xc)
        return false;
    const cFieldDef* field = ((const SP::cTypeDef*)type)->mpFields;
    if (field->mf08 == -1)
        return false;
    uint32_t offset = 0;
    do {
        int32_t child = field->mChild;
        if (child == 3)
            return true;
        if (FUN_00e4a910(child) == true)
            return true;
        offset += sizeof(cFieldDef);
        field = (const cFieldDef*)((const char*)((const SP::cTypeDef*)type)->mpFields + offset);
    } while (field->mf08 != -1);
    return false;
}

// @ 0x00e4a960
bool FUN_00e4a960(int32_t type)
{
    if (type <= 0xc)
        return false;
    const cFieldDef* field = ((const SP::cTypeDef*)type)->mpFields;
    if (field->mf08 == -1)
        return false;
    uint32_t offset = 0;
    do {
        int32_t child = field->mChild;
        if (child == 3 || field->mf14 == 4)
            return true;
        if (FUN_00e4a960(child) == true)
            return true;
        offset += sizeof(cFieldDef);
        field = (const cFieldDef*)((const char*)((const SP::cTypeDef*)type)->mpFields + offset);
    } while (field->mf08 != -1);
    return false;
}

// @ 0x00e4a9d0
uint32_t SP::sHash(const char* s)
{
    if (s == 0)
        return 0;
    return FNVHash(s, 0x811c9dc5, 1);
}

struct IDatabaseFiles {
    virtual void s0();                                  // +0x00
    virtual void Release();                             // +0x04
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void SetMode(int a, int b, void* c);         // +0x18
};
struct cDatabaseDirectoryFiles : IDatabaseFiles {
    cDatabaseDirectoryFiles* Construct(const wchar_t* path, void* allocator);  // 0x008d7400 (ret 8)
};
struct IResManager {
    virtual void m0();  virtual void m1();  virtual void m2();  virtual void m3();  virtual void m4();
    virtual void m5();  virtual void m6();  virtual void m7();  virtual void m8();  virtual void m9();
    virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14();
    virtual void m15(); virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void AddDirectory(int a, void* dir, int priority);              // +0x50
};
extern IResManager* __cdecl GetManager();               // 0x0067dcd0

// @ 0x00e4a9f0
void* FUN_00e4a9f0(const wchar_t* path)
{
    cDatabaseDirectoryFiles* files =
        (cDatabaseDirectoryFiles*)FUN_00926020(0x168, "Simulator", 0, 0, 0, 0);
    files = files != 0 ? files->Construct(path, 0) : 0;
    files->Release();
    files->SetMode(3, 4, 0);
    GetManager()->AddDirectory(1, files, 100);
    return files;
}
