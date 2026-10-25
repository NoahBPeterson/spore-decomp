// slice s00639bd0: cSPPlayModeSubModeAction key handling.
#include "../s00636320/s00636320.h"
#include <math.h>

struct cAssetBrowser { char pad[0x1c]; bool mActive; };        // +0x1C
cAssetBrowser* GetAssetBrowser();                              // 0x00401030

struct IWindowManager {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03(); virtual void w04();
    virtual void w05(); virtual void w06(); virtual void w07(); virtual void w08(); virtual void w09();
    virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14();
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24();
    virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29();
    virtual void w30(); virtual void w31(); virtual void w32();
    virtual int  v33();                                        // +0x84
};
IWindowManager* GetWindowManager();                            // 0x0067CAA0

struct IAnimCreature {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual float SetAnim(uint32_t id, uint32_t anim, int a, int b, int c);   // +0x0C
};
struct cCreatureStructure;
struct Vector3;
struct cAnimatingCreature;
struct cCreatureAnimMgr {
    bool IsAnimationPlaying(uint32_t creatureID, uint32_t animID);   // 0x0059CC40
    cCreatureStructure* GetCreatureStructure(uint32_t id);                    // 0x0059CAC0
    void GetCreaturePosition(uint32_t id, Vector3* out);                      // 0x0059D110
    void SetCreatureTargetPosition(uint32_t id, Vector3 pos, int a, int b);   // 0x0059CF00
    cAnimatingCreature* GetCreature(uint32_t id);                             // 0x0059CA70
};
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3 operator*(float f) const { Vector3 r; r.x = x * f; r.y = y * f; r.z = z * f; return r; }
    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3& operator+=(const Vector3& v)
    {
        float nx = x + v.x, ny = y + v.y, nz = z + v.z;
        x = nx; y = ny; z = nz;
        return *this;
    }
};
extern Vector3 gZeroVector3;                                   // 0x01523E7C
extern float gBabyRotateSpeed;                                 // 0x015F81B4
float VectorLength(const Vector3* v);                          // 0x0040AE50
bool RayPlaneIntersectZ(const Vector3* start, const Vector3* dir, Vector3* hit, float z);  // 0x00638E10
void __stdcall ReleaseCreatureHandler(void* creature, uint32_t id);   // 0x00629D90

namespace EA {
class Stopwatch { public:
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int      mnUnits;
    float    mfStopwatchCyclesToUnitsCoefficient;
    void Stop();                                               // 0x0093A2E0
    uint64_t GetElapsedTimeCycles() const;                     // 0x0093A3A0
    void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
    float GetElapsedTimeFloat() const { return (float)(int64_t)GetElapsedTimeCycles() * mfStopwatchCyclesToUnitsCoefficient; }
};
namespace Random {
class RandomLinearCongruential { public:
    uint32_t mnSeed;
    RandomLinearCongruential(uint32_t seed = 0xffffffff) { SetSeed(seed); }
    void SetSeed(uint32_t seed);                               // 0x00936090
    uint32_t RandomUint32Uniform(uint32_t limit);              // 0x00A68FB0
    double RandomDoubleUniform();                              // 0x009360D0
};
}
template <typename T> class AutoRefCount { public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T** AsPPTypeParam();                                       // 0x00A16F40
};
}

struct XformMsg {
    uint16_t flags;
    uint16_t count;
    Vector3  pos;
    float    scale;
    float    rot[9];
    XformMsg();                                                // 0x00434040
    void SetPos(const Vector3& v) { pos = v; flags |= 4; ++count; }
};

struct cIVisualEffect {
    virtual void e00();
    virtual int  Release();                                    // +0x04
    virtual void Start(int flags);                             // +0x08
    virtual void e03(); virtual void e04(); virtual void e05();
    virtual void SetTransform(const XformMsg& x);              // +0x18
};
// The "movement cursor" effect object used by Init's effect block.  Only the slots it
// calls are modelled (7, 30, 33, 40).
struct IMovementCursorEffect {
    virtual void f00();  virtual void f01();  virtual void f02();  virtual void f03();
    virtual void f04();  virtual void f05();  virtual void f06();  virtual void f07();
    virtual void f08();  virtual void f09();  virtual void f10();  virtual void f11();
    virtual void f12();  virtual void f13();  virtual void f14();  virtual void f15();
    virtual void f16();  virtual void f17();  virtual void f18();  virtual void f19();
    virtual void f20();  virtual void f21();  virtual void f22();  virtual void f23();
    virtual void f24();  virtual void f25();  virtual void f26();  virtual void f27();
    virtual void f28();  virtual void f29();
    virtual void f30(int a);                                   // +0x78
    virtual void f31();  virtual void f32();
    virtual void f33(void* viewer, int b);                     // +0x84
    virtual void f34();  virtual void f35();  virtual void f36();  virtual void f37();
    virtual void f38();  virtual void f39();
    virtual void* f40(int a, int b);                           // +0xA0
};
struct IEffectWorld {
    virtual void w00(); virtual void w01();
    virtual bool CreateVisualEffect(uint32_t id, int a, cIVisualEffect** out);   // +0x08
};
// Effect-world object returned by FUN_0067dd50 (slots 7 and 19 are used by Init).
struct IEffectWorldObj {
    virtual void h00(); virtual void h01(); virtual void h02(); virtual void h03();
    virtual void h04(); virtual void h05(); virtual void h06();
    virtual void h07(void* arg);                              // +0x1c
    virtual void h08(); virtual void h09(); virtual void h10(); virtual void h11();
    virtual void h12(); virtual void h13(); virtual void h14(); virtual void h15();
    virtual void h16(); virtual void h17(); virtual void h18();
    virtual void h19(void* arg);                              // +0x4c
};
// Effects manager (slot 19 = CreateEffectWorld).
struct IEffectsManagerObj {
    virtual void k00(); virtual void k01(); virtual void k02(); virtual void k03();
    virtual void k04(); virtual void k05(); virtual void k06(); virtual void k07();
    virtual void k08(); virtual void k09(); virtual void k10(); virtual void k11();
    virtual void k12(); virtual void k13(); virtual void k14(); virtual void k15();
    virtual void k16(); virtual void k17(); virtual void k18();
    virtual void* k19(uint32_t id, const char* name);         // +0x4c
};
struct IEffectsManager {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03(); virtual void m04();
    virtual void m05(); virtual void m06(); virtual void m07(); virtual void m08(); virtual void m09();
    virtual void m10();
    virtual bool CreateVisualEffect(uint32_t id, int a, cIVisualEffect** out);   // +0x2C
};
IEffectsManager* EffectsManager();                             // 0x0067DDD0

struct cViewer {
    void GetWorldRayFromScreenCoords(float x, float y, Vector3& start, Vector3& dir);   // 0x007C4730
};
struct IApp {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03(); virtual void a04();
    virtual void a05(); virtual void a06(); virtual void a07(); virtual void a08(); virtual void a09();
    virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14();
    virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual void a20(); virtual void a21();
    virtual cViewer* GetViewer();                              // +0x58
};
IApp* App();                                                   // 0x0067DD10
struct IModelManager {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03(); virtual void m04();
    virtual void m05(); virtual void m06(); virtual void m07(); virtual void m08(); virtual void m09();
    virtual uint32_t GetGroupIndex(uint32_t id, int a);        // +0x28
};
IModelManager* ModelManager();                                 // 0x0067DD80

// ---- Init-only declarations -------------------------------------------------------------
// Params block passed to Init; the base Init caches the animation living at +0x20.
struct SubModeParams_t {
    char pad00[0x20];
    IAnimCreature* mAnim;              // +0x20
};
struct cSPUICursorTable;

// Base of every play-mode sub-mode.  Only the vtable is modelled; the derived class's
// fields start immediately after it.
struct cSPPlayModeSubModeBase {
    virtual ~cSPPlayModeSubModeBase();
    virtual void b1();
    void Init(SubModeParams_t* params);                        // 0x0063B270
};

// Local view of cSPPlayModeUI used only for the SetEnabled call (the shared header's
// cSPPlayModeUI is a different, larger layout).
struct cSPPlayModeUIAction {
    void SetEnabled(uint32_t id, bool on);                     // 0x00634EF0
};
struct CursorTable {
    uint32_t AddCursor(uint32_t id, const wchar_t* name, char load, int a, int b);  // 0x00802050
};
CursorTable* GetCursorTable();                                 // 0x0067CAB0
extern float gNextRandomIdleTime;                              // 0x01470F1C (2.0f)
void* FUN_0067dd50();                                          // 0x0067DD50 (world/camera accessor)
void* FUN_006eea10();                                          // 0x0066EEA10 (camera accessor)
// cSPPlayMode::GetMouthPartIdx is a thiscall on the play mode.
struct IMessageServer {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void PostMSG(uint32_t a, uint32_t b, int c);       // +0x14
};
IMessageServer* MessageServer();                               // 0x0067DCC0
struct cGuide { char pad[0x1c]; bool mActive; };
cGuide* SporeGuide();                                          // 0x00401040

// EASTL bitset<64> (two 32-bit words).
struct bitset64 {
    uint32_t mWord[2];
    bitset64() { mWord[0] = 0; mWord[1] = 0; }
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline void set(uint32_t i)
    {
        if (i < 64)
            DoGetWord(i) |= (uint32_t)1 << (i & 31);
    }
};
// Graphics::FilterSettings (ModAPI); built on the stack but never consumed (dead in retail too).
struct FilterSettings {
    bitset64 requiredGroupFlags;   // +0x00
    bitset64 excludedGroupFlags;   // +0x08
    void*    filterFunction;       // +0x10
    uint8_t  collisionMode;        // +0x14
    uint8_t  flags;                // +0x15
    FilterSettings() : filterFunction(0), flags(0) {}
    __forceinline void SetRequiredGroup(uint32_t group) { requiredGroupFlags.set(group); }
};

struct cPlayModePath { char pad[0x2a]; bool mbFlag; };         // +0x2A
struct cSPPlayMode_Creature {
    char pad[0x3c];
    uint32_t* mPathBegin;              // +0x3C
    uint32_t* mPathEnd;                // +0x40
    uint32_t PathSize() const { return mPathEnd - mPathBegin; }
    cPlayModePath* CreatePath(const Vector3* pos, float a, int b, float c);   // 0x0062CB20
    int  GetPathCount();                                       // 0x0062CB10
    bool IsAtPosition(const Vector3* pos);                     // 0x0062CBC0
    void ClearPathList();                                      // 0x0062CB90
    void AddPathTarget(cPlayModePath* p, int a);               // 0x0062CE00
};

struct cSPPlayMode {
    char pad00[0x0c];
    cSPPlayModeUIAction* mUI;          // +0x0C
    char pad10[0x14 - 0x10];
    float mSleepTimer;                 // +0x14
    float mIdleTime;                   // +0x18
    char pad1c;
    uint8_t mSleepState;               // +0x1D
    uint8_t mCallState;                // +0x1E
    uint8_t mCelebrateState;           // +0x1F
    uint8_t mCrouchState;              // +0x20
    char pad21[0x24 - 0x21];
    uint32_t mCrouchingBabyID;         // +0x24
    float mSleepAnimTime;              // +0x28
    float mSitAnimTime;                // +0x2C
    float mCallAnimTime;               // +0x30
    float mCelebrateTime;              // +0x34
    float mCrouchTime;                 // +0x38
    char pad3c[0x40 - 0x3c];
    float mBabyCelebrateTime[4];       // +0x40
    bool  mb50;
    bool  mBabyPhotoMode;              // +0x51
    char pad52[0x7c - 0x52];
    EA::AutoRefCount<cSPPlayMode_Creature>* mCreatures;   // +0x7C (vector mpBegin)

    void WakeupCreature();                                     // 0x0062A760
    void MakeCreaturesFaceCamera();                            // 0x0062ABD0
    float SetMomCelebrationAnim(bool* babySpawned);            // 0x00628780
    float SetBabyCelebrationAnim();                            // 0x006294E0
    int  GetLatestBabyIndex();                                 // 0x00629150
    void SetBabySpawned(int idx, int b);                       // 0x00629380
    float SetMomCrouchAnimation();                             // 0x00628830
    float SetBabyCrouchAnimation(uint32_t id);                 // 0x00628860
    bool BabiesReachedTargetAngle();                           // 0x00629A90
    void SetAllBabyRotateSpeeds(float s);                      // 0x00629B30
    void ResetBabyRotation();                                  // 0x00628890
    void UpdateBabyButtonEventState(uint32_t dt);              // 0x00629960
    void ForceBabiesToIdle(int idx);                           // 0x006296E0
    void SetAllBabyPhotoModes(int on);                         // 0x006288A0
    bool SwitchToCrouchAnim();                                 // 0x00629590
    uint32_t GetMouthPartIdx();                                // 0x00628A80
};

struct cCreatureStructure { char pad[0x4c]; float mRotateAccel; float mRotateSpeed; };  // +0x4C/+0x50
struct cAnimatingCreature {
    char pad[0x14c];
    int  m14c;                         // +0x14C
    char pad150[0x154 - 0x150];
    int  m154;                         // +0x154
    char pad158[0x164 - 0x158];
    Vector3 m164;                      // +0x164
    char pad170[0x17c - 0x170];
    struct cEffectSlots* mEffectSlots; // +0x17C
    bool IsEventActiveA(int a);                                // 0x00A04940
    bool IsEventActiveB(int a);                                // 0x00A02B20
    bool IsEventActiveC(int a);                                // 0x00A04990
};
struct cEffectSlot {
    void Attach(cIVisualEffect* e, uint32_t id, int a);       // 0x009CAA40
};
struct cEffectSlots {
    cEffectSlot* Find(uint32_t id, int a, int b);             // 0x009CB300
};


struct cEditorBase {
    char pad[0x84];
    void* mModelWorld;                                         // +0x84
    uint32_t EmitEmotion(uint32_t event, int a, float b, float c);   // 0x00574110
};

struct cSPPlayModeSubModeAction : cSPPlayModeSubModeBase {
    cEditorBase*   mEditorBase;        // +0x04
    IAnimCreature* mAnim;              // +0x08
    char pad0c[0x4];
    cSPPlayMode*   mPlayMode;          // +0x10
    bool mIsMouseDown;                 // +0x14
    bool mIsFirstClick;                // +0x15
    bool mIsPickingUp;                 // +0x16
    bool mIsGoingToPickUp;             // +0x17
    bool mIsThrowing;                  // +0x18
    bool mHoopsModeOn;                 // +0x19
    bool mIsWalking;                   // +0x1A
    char pad1b[0x1c - 0x1b];
    void* mCurrItemInAir;              // +0x1C
    char pad20[0x24 - 0x20];
    uint8_t mActionButtonAnimRotation; // +0x24
    uint8_t mEmotionButtonAnimRotation;// +0x25
    char pad26[0x30 - 0x26];
    float mX;                          // +0x30
    float mY;                          // +0x34
    EA::AutoRefCount<cIVisualEffect> mCursorEffect;   // +0x38
    float mClickTime;                  // +0x3C
    float mKeyClickTime;               // +0x40
    EA::AutoRefCount<cIVisualEffect> mHitEffect;      // +0x44
    cCreatureAnimMgr* mAnimCreatureMgr; // +0x48
    uint32_t mCreatureID;              // +0x4C
    cAnimatingCreature* mAnimCreature; // +0x50
    char pad54[0x68 - 0x54];
    int  mCurrIdleAnimState;           // +0x68
    uint32_t mMagicAnimID;             // +0x6c
    Vector3 mCurrTargetPosition;       // +0x70
    bool mMouthBidx;                   // +0x7C
    char pad7d[0x80 - 0x7d];
    uint32_t mSocCallEffectID;         // +0x80
    uint32_t mLastLookAroundIdleID;    // +0x84
    uint32_t mKeyInputButtonState[2];  // +0x88 (both initialised to 0xffffffff)
    float mRandomIdleTimer;            // +0x90
    float mRandomIdleSwitchTimer;      // +0x94
    float mNextRandomIdleTime;         // +0x98
    uint32_t mQueuedBoredAnimID;       // +0x9C
    uint32_t mBabyActionEventIDs[6];   // +0xA0
    uint32_t mBabyEmotionEventIDS[6];  // +0xB8
    uint32_t mKeyInputButtonStateD0[2];// +0xD0 (second key-input state pair)
    uint32_t mMagicD8;                 // +0xD8
    union {
        uint32_t mMagicDC;             // +0xDC
        struct { uint8_t mDC0; uint8_t mbDD; uint8_t mDC2; uint8_t mDC3; };
    };
    union {
        uint16_t mMagicE0;             // +0xE0
        struct { uint8_t mE00; uint8_t mbDF; };
    };
    char padE2[0xe8 - 0xe2];
    EA::Stopwatch mFaceUserTimer;      // +0xE8
    void* mEffectWorldUnk100;          // +0x100
    IEffectWorld* mEffectWorld;        // +0x104
    cViewer* mViewer;                  // +0x108
    EA::AutoRefCount<void> mEffectRef; // +0x10c

    void Init(SubModeParams_t* params);
    bool OnKeyDown(int keyCode, int arg2);
    void Update(uint32_t deltaTime);
    void UpdateKeyInput();               // 0x00639350
    bool ReachedMomTargetAngle(uint32_t dt);       // 0x00638810
    void UpdateBabyCelebrationTimes(uint32_t dt);  // 0x00638790
    bool IsIdle();                       // 0x00638D90
    void StartBoredAnimation(uint32_t id);         // 0x006392E0
    float SetIdleAnimation(cAnimatingCreature* c, uint32_t id, int a, int b);  // 0x00638FD0
    void MarkKeyInputKeyDown(int idx);   // 0x006398F0
    void CaptureGIF();                   // 0x00639A10
    bool HasRequiredPart(int idx);       // 0x00638E90
};

// @ 0x00639EC0
bool cSPPlayModeSubModeAction::OnKeyDown(int keyCode, int arg2)
{
    if (GetAssetBrowser()->mActive)
        return false;
    if (GetWindowManager()->v33())
        return false;

    switch (keyCode) {
    case ' ':
        if (mAnimCreatureMgr && mAnimCreatureMgr->IsAnimationPlaying(mCreatureID, 0x44859f9))
            break;
        mPlayMode->WakeupCreature();
        if (mCurrIdleAnimState != 0)
            mMouthBidx = true;
        mAnim->SetAnim(mCreatureID, 0x44859f9, 0, 1, 0);
        mAnim->SetAnim(mCreatureID, 0x4330667, 1, 0, 0);
        mEditorBase->EmitEmotion(mBabyEmotionEventIDS[0], -1, 1.0f, 0.0f);
        return false;

    case '&': case 'W': case 'h':
        if (arg2 == 0) { MarkKeyInputKeyDown(0); return false; }
        break;
    case '(': case 'S': case 'b':
        if (arg2 == 0) { MarkKeyInputKeyDown(2); return false; }
        break;
    case 'Q': case 'g':
        if (arg2 == 0) { MarkKeyInputKeyDown(4); return false; }
        break;
    case 'E': case 'i':
        if (arg2 == 0) { MarkKeyInputKeyDown(5); return false; }
        break;
    case '%': case 'A': case 'd':
        if (arg2 == 0) { MarkKeyInputKeyDown(1); return false; }
        break;
    case '\'': case 'D': case 'f':
        if (arg2 == 0) { MarkKeyInputKeyDown(3); return false; }
        break;
    case 'J':
        if (arg2 == 6)
            CaptureGIF();
        break;
    }
    return false;
}

// @ 0x00639BD0  SP::cSPPlayModeSubModeAction::Init(SubModeParams_t*)
// Resets the action's per-submode state, calls the base Init, caches the creature /
// editor references, wires the pickup/throw cursors and the movement-cursor effect.
void cSPPlayModeSubModeAction::Init(SubModeParams_t* params) {
    cSPPlayModeSubModeAction* self = this;

    self->mClickTime = 0.0f;
    self->mIsMouseDown = false;
    self->mIsFirstClick = false;
    self->mIsPickingUp = false;
    self->mIsGoingToPickUp = false;
    self->mIsThrowing = false;
    self->mHoopsModeOn = false;
    self->mIsWalking = false;
    self->mEffectWorldUnk100 = 0;
    self->mActionButtonAnimRotation = 5;
    self->mEmotionButtonAnimRotation = 10;
    self->mCurrItemInAir = 0;

    // Release the two effect handles held by the action.
    if (self->mCursorEffect.mpObject) {
        cIVisualEffect* p = self->mCursorEffect.mpObject; self->mCursorEffect.mpObject = 0; p->Release();
    }
    if (self->mHitEffect.mpObject) {
        cIVisualEffect* p = self->mHitEffect.mpObject; self->mHitEffect.mpObject = 0; p->Release();
    }

    self->mFaceUserTimer.mnStartTime = 0;
    self->mFaceUserTimer.mnTotalElapsedTime = 0;

    // Base Init: caches the animation and editor references.
    self->cSPPlayModeSubModeBase::Init(params);

    cEditorBase* eb = self->mEditorBase;
    self->mAnimCreatureMgr = *(cCreatureAnimMgr**)((char*)eb + 0x360);
    self->mCreatureID = *(uint32_t*)((char*)eb + 0x364);
    self->mAnimCreature = self->mAnimCreatureMgr->GetCreature(self->mCreatureID);

    // cSPPlayModeUI lives at cSPPlayMode+0xc.
    if (self->HasRequiredPart(1))
        self->mPlayMode->mUI->SetEnabled(0x3e99d8c, true);
    else
        self->mPlayMode->mUI->SetEnabled(0x3e99d8c, false);
    self->mSocCallEffectID = self->mPlayMode->GetMouthPartIdx();
    self->mLastLookAroundIdleID = 0xffffffff;
    self->mCurrIdleAnimState = 0;
    self->mMagicAnimID = 0x4330667;
    self->mAnim = *(IAnimCreature**)((char*)params + 0x20);
    self->mMouthBidx = false;

    // Register the two interaction cursors.
    GetCursorTable()->AddCursor(0x3b360dc, L"cursor-crg-pickup", 1, 0, 0);
    GetCursorTable()->AddCursor(0x3b360e4, L"cursor-crg-throw", 1, 0, 0);

    self->mRandomIdleTimer = 0.0f;
    self->mNextRandomIdleTime = gNextRandomIdleTime;
    self->mRandomIdleSwitchTimer = 0.0f;
    self->mKeyInputButtonState[0] = 0xffffffff;
    self->mKeyInputButtonState[1] = 0xffffffff;
    self->mQueuedBoredAnimID = 0xffffffff;
    self->mPlayMode->mIdleTime = 0.0f;

    self->mBabyActionEventIDs[0] = 0x3bd9a6f8;
    self->mBabyActionEventIDs[1] = 0xbac2d74f;
    self->mBabyActionEventIDs[2] = 0x8b2f58fe;
    self->mBabyActionEventIDs[3] = 0x167d2885;
    self->mBabyActionEventIDs[4] = 0x5c4d694c;
    self->mBabyActionEventIDs[5] = 0xf77c2e23;
    self->mBabyEmotionEventIDS[0] = 0x1d9547b2;
    self->mBabyEmotionEventIDS[1] = 0xb0a9f0f9;
    self->mBabyEmotionEventIDS[2] = 0x9e341470;
    self->mBabyEmotionEventIDS[3] = 0x43773b7b;
    self->mBabyEmotionEventIDS[4] = 0x622c20c4;
    self->mBabyEmotionEventIDS[5] = 0xe646113d;
    self->mKeyInputButtonStateD0[0] = 0x22b31636;
    self->mKeyInputButtonStateD0[1] = 0xe7782027;
    self->mMagicD8 = 0x6035c10;
    self->mMagicDC = 0;
    self->mMagicE0 = 0;

    if (self->mEffectRef.mpObject != 0)
        return;

    self->mViewer = App()->GetViewer();
    void* cam = FUN_006eea10();
    void* old = self->mEffectRef.mpObject;
    if (cam != old) {
        if (cam) (*(void(__thiscall**)(void*))*(void**)cam)(cam);
        self->mEffectRef.mpObject = (void*)cam;
        if (old) (*(void(__thiscall**)(void*))((*(void***)old)[1]))(old);
    }
    ((IMovementCursorEffect*)self->mEffectRef.mpObject)->f30(0);
    ((IMovementCursorEffect*)self->mEffectRef.mpObject)->f33(self->mViewer, 0);
    IMovementCursorEffect* eff = (IMovementCursorEffect*)self->mEffectRef.mpObject;
    IEffectWorldObj* world = (IEffectWorldObj*)FUN_0067dd50();
    void* arg = eff->f40(0x1c, 0);
    world->h19(arg);

    if (self->mEffectWorld != 0)
        return;

    IEffectsManagerObj* em = (IEffectsManagerObj*)EffectsManager();
    IEffectWorldObj* newWorld = (IEffectWorldObj*)em->k19(0x61c8236, "Movement Cursor Effects World");
    self->mEffectWorld = (IEffectWorld*)newWorld;
    // Tail call: world->slot7(effectRef).
    newWorld->h07(self->mEffectRef.mpObject);
}
// @ 0x0063A0A0
void cSPPlayModeSubModeAction::Update(uint32_t deltaTime)
{
    UpdateKeyInput();
    float fDeltaTime = (float)deltaTime;
    float dt = fDeltaTime * 0.001f;
    mPlayMode->mSleepTimer = dt + mPlayMode->mSleepTimer;
    mRandomIdleTimer = dt + mRandomIdleTimer;

    if (mFaceUserTimer.GetElapsedTimeFloat() > 0.5f) {
        mFaceUserTimer.Stop();
        mFaceUserTimer.Reset();
        mPlayMode->MakeCreaturesFaceCamera();
    }

    if (mPlayMode->mSleepState == 1 || mPlayMode->mSleepState == 2) {
        mPlayMode->mSleepAnimTime -= dt;
        if (mPlayMode->mSleepAnimTime < 0.0f) {
            mAnim->SetAnim(mCreatureID, 0x4079851, 1, 0, 0);
            mPlayMode->mSleepAnimTime = 0.0f;
            mPlayMode->mSleepState = 3;
        } else {
            mPlayMode->mSleepState = 2;
        }
    } else if (mPlayMode->mCallState == 1) {
        mPlayMode->mCallAnimTime -= dt;
        if (mPlayMode->mCallAnimTime <= 0.0f) {
            if (mSocCallEffectID != 0xffffffff) {
                EA::AutoRefCount<cIVisualEffect> effect;
                if (mLastLookAroundIdleID != 0xffffffff) {
                    ReleaseCreatureHandler(mAnimCreature, mLastLookAroundIdleID);
                    mLastLookAroundIdleID = 0xffffffff;
                }
                if (EffectsManager()->CreateVisualEffect(0xe1b24ddb, 0, effect.AsPPTypeParam())) {
                    effect->Start(0);
                    cEffectSlot* slot = mAnimCreature->mEffectSlots->Find(0xe1b24ddb, 0, 0);
                    if (slot) {
                        slot->Attach(effect, mSocCallEffectID, 0);
                        mLastLookAroundIdleID = 0xe1b24ddb;
                    }
                }
            }
            mPlayMode->mCallState = 2;
        }
    } else if (mPlayMode->mCallState == 2) {
        mPlayMode->mSitAnimTime -= dt;
        if (mPlayMode->mSitAnimTime < 0.0f) {
            if (mLastLookAroundIdleID != 0xffffffff) {
                ReleaseCreatureHandler(mAnimCreature, mLastLookAroundIdleID);
                mLastLookAroundIdleID = 0xffffffff;
            }
            mPlayMode->mSitAnimTime = 0.0f;
            mPlayMode->mCallAnimTime = 0.0f;
            mPlayMode->mCallState = 0;
        }
    } else if (mPlayMode->mCelebrateState == 1) {
        if (ReachedMomTargetAngle(deltaTime)) {
            bool babySpawned;
            mPlayMode->mCelebrateTime = mPlayMode->SetMomCelebrationAnim(&babySpawned);
            if (!babySpawned) {
                mPlayMode->SetBabyCelebrationAnim();
                mPlayMode->mCelebrateState = 2;
            } else {
                int idx = mPlayMode->GetLatestBabyIndex();
                mPlayMode->SetBabySpawned(idx, 0);
                mPlayMode->mBabyCelebrateTime[idx] = 0.0f;
                mPlayMode->mCelebrateState = 2;
            }
        }
    } else if (mPlayMode->mCelebrateState == 2) {
        mPlayMode->mCelebrateTime -= dt;
        if (mPlayMode->mCelebrateTime <= 0.0f)
            mPlayMode->mCelebrateState = 0;
    } else if (mPlayMode->mCrouchState == 1) {
        if (ReachedMomTargetAngle(deltaTime)) {
            mPlayMode->mCrouchTime = mPlayMode->SetMomCrouchAnimation();
            mPlayMode->SetBabyCrouchAnimation(mPlayMode->mCrouchingBabyID);
            mPlayMode->mCrouchState = 2;
        }
    } else if (mPlayMode->mCrouchState == 2) {
        mPlayMode->mCrouchTime -= dt;
        if (mPlayMode->mCrouchTime <= 0.0f)
            mPlayMode->mCrouchState = 0;
    }

    if (mPlayMode->mBabyPhotoMode && ReachedMomTargetAngle(deltaTime) &&
        mPlayMode->BabiesReachedTargetAngle()) {
        cCreatureStructure* cs = mAnimCreatureMgr->GetCreatureStructure(mCreatureID);
        cs->mRotateAccel = 2.5f;
        cs->mRotateSpeed = gBabyRotateSpeed;
        mPlayMode->SetAllBabyRotateSpeeds(gBabyRotateSpeed);
        mPlayMode->ResetBabyRotation();
    }

    UpdateBabyCelebrationTimes(deltaTime);
    mPlayMode->UpdateBabyButtonEventState(deltaTime);
    mClickTime += fDeltaTime;
    mKeyClickTime += fDeltaTime;

    if (mEditorBase->mModelWorld && mAnimCreatureMgr && mIsMouseDown &&
        !GetAssetBrowser()->mActive && !SporeGuide()->mActive) {
        FilterSettings filter;
        Vector3 rayStart, rayDir;
        App()->GetViewer()->GetWorldRayFromScreenCoords(mX, mY, rayStart, rayDir);
        rayStart += rayDir * -500.0f;
        filter.collisionMode = 4;
        filter.SetRequiredGroup(ModelManager()->GetGroupIndex(0x3e97417, 0));
        Vector3 hit;
        if (RayPlaneIntersectZ(&rayStart, &rayDir, &hit, -0.13f)) {
            if (mIsMouseDown) {
                bool wasNear = VectorLength(&mCurrTargetPosition) < 5.6f;
                bool isNear = sqrtf(hit.x * hit.x + hit.y * hit.y) < 5.6f;
                cPlayModePath* path = mPlayMode->mCreatures[0]->CreatePath(&hit, 1.0f, 0, 0.5f);
                path->mbFlag = true;
                if (mPlayMode->mCreatures[0]->GetPathCount() != 1 ||
                    !mPlayMode->mCreatures[0]->IsAtPosition(&hit)) {
                    mPlayMode->mCreatures[0]->ClearPathList();
                    mPlayMode->mCreatures[0]->AddPathTarget(path, 0);
                }
                mCurrTargetPosition = hit;
                mCurrTargetPosition.z = 0.0f;
                if (!mCursorEffect || wasNear != isNear) {
                    if (isNear)
                        mEffectWorld->CreateVisualEffect(0x384e54a4, 0, mCursorEffect.AsPPTypeParam());
                    else
                        mEffectWorld->CreateVisualEffect(0x8660a7f4, 0, mCursorEffect.AsPPTypeParam());
                }
                if (mCursorEffect) {
                    mCursorEffect->SetTransform(XformMsg());
                    mCursorEffect->Start(0);
                    XformMsg xform;
                    xform.SetPos(hit);
                    mCursorEffect->SetTransform(xform);
                }
                MessageServer()->PostMSG(0x52f180, 0x19, 0);
            }
            if (mIsFirstClick && !mIsPickingUp) {
                if (mPlayMode->mBabyPhotoMode) {
                    cCreatureStructure* cs = mAnimCreatureMgr->GetCreatureStructure(mCreatureID);
                    cs->mRotateAccel = 2.5f;
                    cs->mRotateSpeed = gBabyRotateSpeed;
                    mPlayMode->ResetBabyRotation();
                }
                mPlayMode->ForceBabiesToIdle(-1);
                mPlayMode->SetAllBabyPhotoModes(0);
                mPlayMode->SetAllBabyRotateSpeeds(gBabyRotateSpeed);
                mIsFirstClick = false;
                mIsWalking = true;
            }
        }
    } else if (mIsWalking && mPlayMode->mCreatures[0]->PathSize() == 0 && !mIsPickingUp &&
               !mbDD && !mbDF) {
        mIsWalking = false;
    } else if ((mMouthBidx && (mAnimCreature->IsEventActiveA(0) || mAnimCreature->IsEventActiveB(0) ||
                               mAnimCreature->IsEventActiveC(0))) ||
               GetAssetBrowser()->mActive || SporeGuide()->mActive) {
        mIsWalking = false;
        SetIdleAnimation(mAnimCreature, mCreatureID, 0, 0);
        if (mMouthBidx || GetAssetBrowser()->mActive || SporeGuide()->mActive) {
            Vector3 pos;
            mAnimCreatureMgr->GetCreaturePosition(mCreatureID, &pos);
            mCurrTargetPosition = pos;
            mCurrTargetPosition.z = 0.0f;
            mAnimCreatureMgr->SetCreatureTargetPosition(mCreatureID, pos, 0, 1);
            mAnimCreature->m154 = 1;
            mAnimCreature->m164 = gZeroVector3;
            mMouthBidx = false;
        }
    } else if (!IsIdle()) {
        mRandomIdleSwitchTimer = 0.0f;
        mRandomIdleTimer = 0.0f;
    } else if (mRandomIdleSwitchTimer > 0.0f) {
        mRandomIdleSwitchTimer -= dt;
        if (mRandomIdleSwitchTimer <= 0.0f) {
            mRandomIdleSwitchTimer = 0.0f;
            mRandomIdleTimer = 0.0f;
            if (mQueuedBoredAnimID != 0xffffffff) {
                StartBoredAnimation(mQueuedBoredAnimID);
                mQueuedBoredAnimID = 0xffffffff;
            } else {
                SetIdleAnimation(mAnimCreature, mCreatureID, 0, 0);
            }
        }
    } else if (mRandomIdleTimer > mNextRandomIdleTime) {
        EA::Random::RandomLinearCongruential rng;
        if (!mPlayMode->SwitchToCrouchAnim()) {
            float animLength = SetIdleAnimation(mAnimCreature, mCreatureID, 1, 1);
            uint32_t loops = rng.RandomUint32Uniform(2);
            if (loops == 0)
                loops = 1;
            mRandomIdleSwitchTimer = (float)loops * animLength;
        }
        mRandomIdleTimer = 0.0f;
        mNextRandomIdleTime = (float)(rng.RandomDoubleUniform() * 1.5) + 0.5f;
    }
    mAnimCreature->m14c = 0;
}
// MarkKeyInputKeyDown (0x006398F0) and CaptureGIF (0x00639A10) are called
// out-of-line by the original; leave them undefined here for byte codegen.
