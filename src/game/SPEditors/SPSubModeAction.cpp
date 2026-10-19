// src/game/SPEditors/SPSubModeAction.cpp -- migrated from slice(s) s0063aa90, s00639bd0, s00638e90, s00637f80 by tools/migrate/rewrite.py
// Object file: SPEditors/SPSubModeAction.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPlayModeSubModeAction.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cSPEditorAnimatedCreatureManager.h"
#include "SP/cSPEditorUI.h"
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayModeAnimation.h"
#include "SP/cSPPlayModeUI.h"
#include "SP/cString.h"
#include "EA/Swarm/cIVisualEffect.h"
#include "SP/cSPEditorNaming.h"
#include "cSPUILayout.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Stopwatch.h"
#include "cSPVector3.h"
#include "SP/cPlayModePath.h"
#include "SP/cSPPlayMode_Creature.h"
#include "SP/cViewer.h"
#include <math.h>
#include "EA/AutoRefCount.h"
#include "SP/cSPPlayModeSubModeBase.h"
#include "SP/cSPPlayModeSubModeDance.h"
#include "SP/cSPPlayModeSubModeMovie.h"

// unnamed retail callees and globals (address in the comment)
extern float gDefaultSpeedB;                                            // 0x015F81B4

// ---- items of slice s00637f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cSPPlayMode_s0063_7f80;
}
namespace SP {
class cSPPlayMode_s0063_7f80 {
public:
    void SetBabySpawned(int idx, bool spawned);                         // 0x00629380
    char pad0[0x1c];
    bool mSleepB1c, mSleepB1d, mSleepB1e, mSleepB1f, mSleepB20;         // +0x1c..+0x20
    char pad1[0x3c - 0x21];
    float mMomCrouchChangeTime;                                         // +0x3c
    float mBabyCelebratingChangeTime[3];                                // +0x40
    char pad2[0x51 - 0x4c];
    bool mBabyPhotoMode;                                                // +0x51
};
}
struct cEditorBaseStub { char pad[0x84]; void* mpModelWorld; };
class cVisualEffect {
public:
    virtual int AddRef(); virtual int Release(); virtual void v2();
    virtual void Stop(int a);                                           // +0xc
};
class cSPPlayModeAnimation_s0063_7f80 {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual float PlayAnimation(uint32_t creatureID, uint32_t animID, int a, int b, void* c);  // +0xc
    bool GetExpansionAnimInfo(uint32_t id, int* animID, int* a, float* b, float* c);    // 0x0062E4F0
    char pad[4]; uint32_t mCurrAnimID;
};
struct cCreatureStructure {
    char pad[0x48]; float f48; char pad2[4]; float f50;
    void FUN_0059b2f0(float v, int b);                                  // 0x0059B2F0
};
class cSPEditorAnimatedCreatureManager_s0063_7f80 {
public:
    cCreatureStructure* GetCreatureStructure(uint32_t id);              // 0x0059CAC0
    void SetCreatureSpeeds(uint32_t id, float a, float b);              // 0x0059D0B0
    void SetCreatureIsTurning(uint32_t id, bool turning);               // 0x0059D010
};
struct cAnimatingCreatureSub { void FUN_00a006f0(int v); };             // 0x00A006F0
class cAnimatingCreature_s0063_7f80 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void GetAnimInfo(int* out, int a, int b, int c);            // +0x58
    char pad[0x154 - 4]; int mState;                   // +0x154
    char pad2[0x184 - 0x158]; cAnimatingCreatureSub* mpSub;             // +0x184
    void FUN_00a04ad0(uint32_t state);                                  // 0x00A04AD0
};
struct cIdleObj { char pad[0x8c]; cVisualEffect* mpEffect; };
struct cIdleObjMgr { cIdleObj* FUN_009cab60(uint32_t id); void FUN_009cb460(cIdleObj* o); };  // 0x009CAB60 / 0x009CB460
struct cEffectsMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual int GetEffectsWorldHandle();             // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void RemoveEffect(uint32_t id);                             // +0x50
};
cEffectsMgr* GetEffectsManager();                                       // 0x0067DDD0
struct cWorldObj { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void SetEffectsHandle(int h); };         // +0x1c
struct cStopObj {
    virtual int AddRef(); virtual int Release(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void Flush();                           // +0x7c
};
struct cPlayModeFlagStub { void FUN_0062ab80(); };                      // 0x0062AB80
struct AssetBrowserStub { char pad[0x1c]; bool mFlag1c; };
AssetBrowserStub* GetAssetBrowser();                                    // 0x00401030
float FUN_0069b840(float a, float b, float c);                          // 0x0069B840
struct cEditorStub2 { void FUN_00574110(uint32_t id, int a, float b, float c); };                         // 0x00574110
struct cAnimCreatureHelper { bool FUN_00a02b20(int a); };               // 0x00A02B20
extern float gDefaultSpeedB;                                            // 0x015F81B4
namespace SP {
class cSPPlayModeSubModeAction_s0063_7f80 {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    bool OnMouseUp(int btn, float x, float y, int flags);  // 0x00638750 (SP::cSPPlayModeSubModeAction::OnMouseUp)
    bool OnMouseMove(float x, float y, int flags);  // 0x00638770 (SP::cSPPlayModeSubModeAction::OnMouseMove)
    void UpdateBabyCelebrationTimes(uint32_t dtMs);
    bool ReachedMomTargetAngle(uint32_t dtMs);  // 0x00638810 (SP::cSPPlayModeSubModeAction::ReachedMomTargetAngle)
    bool IsLookAroundIdle(uint32_t animID);  // 0x00638890 (SP::cSPPlayModeSubModeAction::IsLookAroundIdle)
    void SetWalkAnimation(cAnimatingCreature_s0063_7f80* creature, uint32_t id);  // 0x006388e0 (SP::cSPPlayModeSubModeAction::SetWalkAnimation)
    bool AnyKeyDown();
    void HandleExpansionAnim(uint32_t id);  // 0x00638a00 (SP::cSPPlayModeSubModeAction::HandleExpansionAnim)
    void Shutdown();  // 0x00638ad0 (SP::cSPPlayModeSubModeAction::Shutdown)
    bool OnMouseDown(int btn, float x, float y, int flags);  // 0x00638ba0 (SP::cSPPlayModeSubModeAction::OnMouseDown)
    bool OnKeyUp(uint32_t key, uint32_t mods);  // 0x00638c90 (SP::cSPPlayModeSubModeAction::OnKeyUp)
    bool IsIdle();  // 0x00638d90 (SP::cSPPlayModeSubModeAction::IsIdle)

    cEditorBaseStub* mEditorBaseMode;                                   // +0x4
    cSPPlayModeAnimation_s0063_7f80* mAnim;                                        // +0x8
    void* mSubModeParams;                                               // +0xc
    cSPPlayMode_s0063_7f80* mPlayMode;                                             // +0x10
    bool mIsMouseDown, mIsFirstClick, mIsPickingUp, mIsGoingToPickUp;   // +0x14
    bool mIsThrowing, mHoopsModeOn, mIsWalking, mHoopsMode_state;       // +0x18
    char pad1c[0x30 - 0x1c];
    float mX, mY;                                                       // +0x30
    cVisualEffect* mCursorEffect;                                       // +0x38
    float mClickTime;                                                   // +0x3c
    char pad40[0x48 - 0x40];
    cSPEditorAnimatedCreatureManager_s0063_7f80* mAnimCreatureMgr;                 // +0x48
    uint32_t mCreatureID;                                               // +0x4c
    cAnimatingCreature_s0063_7f80* mAnimCreature;                                  // +0x50
    char pad54[0x68 - 0x54];
    uint32_t mCurrIdleAnimState;                                        // +0x68
    char pad6c[0x7c - 0x6c];
    uint8_t mMouthBidx;                                                 // +0x7c
    char pad7d[0x84 - 0x7d];
    uint32_t mLastLookAroundIdleID;                                     // +0x84
    char pad88[0xdc - 0x88];
    bool mKeyInputButtonState[6];                                       // +0xdc
    char pade2[0x104 - 0xe2];
    cWorldObj* mpField104;                                                   // +0x104
    void* mpField108;                                                   // +0x108
    cStopObj* mpField10c;                                                   // +0x10c
};
}
struct Vec3f {
    float x, y, z;
    Vec3f() {}
    Vec3f(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3f operator*(float s) const { return Vec3f(x * s, y * s, z * s); }
    Vec3f operator+(const Vec3f& o) const { return Vec3f(x + o.x, y + o.y, z + o.z); }
};
// ---- items of slice s00637f80 end

// ---- items of slice s00638e90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPPlayModeSubModeAction {
    char pad[0x200];
    bool HasRequiredPart();
    float SetIdleAnimation(void* a, uint32_t b, int c, int d);
    void StartBoredAnimation(float t);
    void FUN_00639350();
    void MarkKeyInputKeyDown(int idx);
    void CaptureGIF();
    void FUN_00639b70();
};
// ---- items of slice s00638e90 end

// ---- items of slice s00639bd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gBabyRotateSpeed;                                 // 0x015F81B4
struct cAssetBrowser { char pad[0x1c]; bool mActive; };        // +0x1C
cAssetBrowser* GetAssetBrowser_s0063_9bd0();                              // 0x00401030
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
struct cCreatureStructure_s0063_9bd0;
struct Vector3;
struct cCreatureAnimMgr {
    bool IsAnimationPlaying(uint32_t creatureID, uint32_t animID);   // 0x0059CC40
    cCreatureStructure_s0063_9bd0* GetCreatureStructure(uint32_t id);                    // 0x0059CAC0
    void GetCreaturePosition(uint32_t id, Vector3* out);                      // 0x0059D110
    void SetCreatureTargetPosition(uint32_t id, Vector3 pos, int a, int b);   // 0x0059CF00
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
float VectorLength(const Vector3* v);                          // 0x0040AE50
bool RayPlaneIntersectZ(const Vector3* start, const Vector3* dir, Vector3* hit, float z);  // 0x00638E10
void __stdcall ReleaseCreatureHandler(void* creature, uint32_t id);   // 0x00629D90
namespace EA {
struct Stopwatch_s0063_9bd0 {
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int      mnUnits;
    float    mfStopwatchCyclesToUnitsCoefficient;
    void Stop();                                               // 0x0093A2E0
    uint64_t GetElapsedTimeCycles() const;                     // 0x0093A3A0
    void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
    float GetElapsedTimeFloat() const { return (float)(int64_t)GetElapsedTimeCycles() * mfStopwatchCyclesToUnitsCoefficient; }
};
}
namespace EA {
namespace Random {
struct RandomLinearCongruential_s0063_9bd0 {
    uint32_t mnSeed;
    RandomLinearCongruential_s0063_9bd0(uint32_t seed = 0xffffffff) { SetSeed(seed); }
    void SetSeed(uint32_t seed);                               // 0x00936090
    uint32_t RandomUint32Uniform(uint32_t limit);              // 0x00A68FB0
    double RandomDoubleUniform();                              // 0x009360D0
};
}
}
namespace EA {
template <typename T> struct AutoRefCount_s0063_9bd0 {
    T* mpObject;
    AutoRefCount_s0063_9bd0() : mpObject(0) {}
    ~AutoRefCount_s0063_9bd0() { if (mpObject) mpObject->Release(); }
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
struct IEffectWorld {
    virtual void w00(); virtual void w01();
    virtual bool CreateVisualEffect(uint32_t id, int a, cIVisualEffect** out);   // +0x08
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
struct IMessageServer {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void PostMSG(uint32_t a, uint32_t b, int c);       // +0x14
};
IMessageServer* MessageServer();                               // 0x0067DCC0
struct cGuide { char pad[0x1c]; bool mActive; };
cGuide* SporeGuide();                                          // 0x00401040
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
    char pad00[0x14];
    float mSleepTimer;                 // +0x14
    char pad18[0x1d - 0x18];
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
    EA::AutoRefCount_s0063_9bd0<cSPPlayMode_Creature>* mCreatures;   // +0x7C (vector mpBegin)

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
};
struct cCreatureStructure_s0063_9bd0 { char pad[0x4c]; float mRotateAccel; float mRotateSpeed; };  // +0x4C/+0x50
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
struct cSPPlayModeSubModeAction_s0063_9bd0 {
    char pad04[0x4];
    cEditorBase*   mEditorBase;        // +0x04
    IAnimCreature* mAnim;              // +0x08
    char pad0c[0x4];
    cSPPlayMode*   mPlayMode;          // +0x10
    bool mIsMouseDown;                 // +0x14
    bool mIsFirstClick;                // +0x15
    bool mIsPickingUp;                 // +0x16
    char pad17[0x1a - 0x17];
    bool mIsWalking;                   // +0x1A
    char pad1b[0x30 - 0x1b];
    float mX;                          // +0x30
    float mY;                          // +0x34
    EA::AutoRefCount_s0063_9bd0<cIVisualEffect> mCursorEffect;   // +0x38
    float mClickTime;                  // +0x3C
    float mKeyClickTime;               // +0x40
    char pad44[0x48 - 0x44];
    cCreatureAnimMgr* mAnimCreatureMgr; // +0x48
    uint32_t mCreatureID;              // +0x4C
    cAnimatingCreature* mAnimCreature; // +0x50
    char pad54[0x68 - 0x54];
    int  mCurrIdleAnimState;           // +0x68
    char pad6c[0x70 - 0x6c];
    Vector3 mCurrTargetPosition;       // +0x70
    bool mMouthBidx;                   // +0x7C
    char pad7d[0x80 - 0x7d];
    uint32_t mSocCallEffectID;         // +0x80
    uint32_t mLastLookAroundIdleID;    // +0x84
    char pad88[0x90 - 0x88];
    float mRandomIdleTimer;            // +0x90
    float mRandomIdleSwitchTimer;      // +0x94
    float mNextRandomIdleTime;         // +0x98
    uint32_t mQueuedBoredAnimID;       // +0x9C
    char padA0[0xb8 - 0xa0];
    uint32_t mBabyEmotionEventIDS[6];  // +0xB8
    char padD0[0xdd - 0xd0];
    bool mbDD;                         // +0xDD
    char padDE;
    bool mbDF;                         // +0xDF
    char padE0[0xe8 - 0xe0];
    EA::Stopwatch_s0063_9bd0 mFaceUserTimer;      // +0xE8
    char pad100[4];
    IEffectWorld* mEffectWorld;        // +0x104

    void Init();  // 0x00639bd0 (cSPPlayModeSubModeAction::Init)
    bool OnKeyDown(int keyCode, int arg2);  // 0x00639ec0 (cSPPlayModeSubModeAction::OnKeyDown)
    void Update(uint32_t deltaTime);  // 0x0063a0a0 (cSPPlayModeSubModeAction::Update)
    void UpdateKeyInput();               // 0x00639350
    bool ReachedMomTargetAngle(uint32_t dt);       // 0x00638810
    void UpdateBabyCelebrationTimes(uint32_t dt);  // 0x00638790
    bool IsIdle();                       // 0x00638D90
    void StartBoredAnimation(uint32_t id);         // 0x006392E0
    float SetIdleAnimation(cAnimatingCreature* c, uint32_t id, int a, int b);  // 0x00638FD0
    void MarkKeyInputKeyDown(int idx);   // 0x006398F0
    void CaptureGIF();                   // 0x00639A10
};
// ---- items of slice s00639bd0 end

// ---- items of slice s0063aa90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Stopwatch {
    Stopwatch(int units, int b);                                        // 0x0093A560
    float GetElapsedTimeFloat();                                        // 0x005FF1A0
    void StartIfUnset();                                                // 0x00435480
    uint32_t mField[4];
    uint32_t pad[2];
};
void KillSetiEffects(uint32_t id, int v);                               // 0x00435ED0 (cdecl)
int GetRecorderState();                                                 // 0x00435E90
struct cAudioSys { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual int GetState(); };    // +0x20
cAudioSys* GetSystemAT();                                               // 0x00A206F0
struct cRandom { int RandomUint32Uniform(int n); };                     // 0x00A68FB0
extern cRandom sMathRandom;                                             // 0x01601760
class cEditorMode2 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual char* GetSaveInfo();   // +0x40
    void SaveModel(char* p, bool b);                                    // 0x0057F6C0
    void FUN_00574110(uint32_t id, int a, float b, float c);            // 0x00574110
    void OnLayout(int a, int b);                                        // 0x00B267F0
};
class cPlayModeUI2 { public: void SetEnabled(uint32_t id, bool b); };   // 0x00634EF0
class cSPPlayMode_s0063_aa90 {
public:
    void WakeupCreature();                                              // 0x0062A760
    void FUN_00628810();                                                // 0x00628810
    void SetAllBabySitUp();                                             // 0x00629220
    char pad0[0xc]; cPlayModeUI2* mpUI;                                 // +0xc
    char pad1[0x1d - 0x10]; uint8_t mB1d, mB1e;                         // +0x1d, +0x1e
    char pad2[0x28 - 0x1f]; float mF28, mF2c, mF30;                     // +0x28..
};
class cSPPlayModeAnimation2 {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual float PlayAnimation(uint32_t creatureID, uint32_t animID, int a, int b, void* c);  // +0xc
};
class cSPPlayModeSubModeBase {
public:
    virtual void v0();
    void Init(void* params);                                            // 0x0063B270 (called out of line from other TUs; body below as InitCopy)
    void InitCopy(void* params);
    cEditorMode2* mEditorBaseMode;                                      // +0x4
    cSPPlayModeAnimation2* mAnim;                                       // +0x8
    void* mSubModeParams;                                               // +0xc
    cSPPlayMode_s0063_aa90* mPlayMode;                                             // +0x10
};
struct PtrZ { void* p; PtrZ() : p(0) {} };
struct Vec3Z { uint32_t a, b, c; Vec3Z() : a(0), b(0), c(0) {} };
class cSPPlayModeSubModeAction_s0063_aa90 : public cSPPlayModeSubModeBase {
public:
    cSPPlayModeSubModeAction_s0063_aa90();
    bool HandleButton(int id);  // 0x0063aa90 (cSPPlayModeSubModeAction::HandleButton)
    void HandleExpansionAnim(uint32_t id);                              // 0x00638A00
    void CaptureGIF();                                                  // 0x00639A10

    char pad14[0x16 - 0x14];
    bool mIsPickingUp;                                                  // +0x16
    char pad17[0x38 - 0x17];
    PtrZ mCursorEffect;                                                // +0x38
    char pad3c[0x44 - 0x3c];
    PtrZ mHitEffect;                                                   // +0x44
    char pad48[0x4c - 0x48];
    uint32_t mCreatureID;                                               // +0x4c
    char pad50[0x54 - 0x50];
    Vec3Z mGrasperList;                                           // +0x54
    char pad60[0x68 - 0x60];
    uint32_t mCurrIdleAnimState;                                        // +0x68
    char pad6c[0x7c - 0x6c];
    uint8_t mMouthBidx;                                                 // +0x7c
    char pad7d[0x80 - 0x7d];
    uint32_t mSocCallEffectID;                                          // +0x80
    char pad84[0x9c - 0x84];
    uint32_t mBabyActionEventIDs[7];                                    // +0x9c
    uint32_t mBabyEmotionEventIDs[9];                                   // +0xb8
    char padDC[0xe8 - 0xdc];
    Stopwatch mFaceUserTimer;                                           // +0xe8
    char pad100[0x104 - 0x100];
    void* mField104; void* mField108; void* mField10c;                  // +0x104
};
#define KILL_SETI_REC() KillSetiEffects(0xa03e74b2, GetRecorderState())
#define KILL_SETI_AT() { cAudioSys* at = GetSystemAT(); KillSetiEffects(0xa03e74b2, at ? at->GetState() : 0); }
// ---- items of slice s0063aa90 end

// @ 0x00638750
bool SP::cSPPlayModeSubModeAction::OnMouseUp(unsigned int btn, float x, float y, unsigned int flags)
{
    if (btn == 1000) {
        mIsMouseDown = false;
        mIsFirstClick = false;
    }
    return false;
}

// @ 0x00638770
bool SP::cSPPlayModeSubModeAction::OnMouseMove(float x, float y, unsigned int flags)
{
    mX = x;
    mY = y;
    return false;
}

// @ 0x00638790
void SP::cSPPlayModeSubModeAction::UpdateBabyCelebrationTimes(unsigned int dtMs)
{
    SP::cSPPlayMode* pm = mPlayMode;
    int i = 0;
    uint32_t off = 0x40;
    do {
        if (*(float*)((char*)pm + off) > 0.0f) {
            float* p = (float*)((char*)mPlayMode + off);
            *p -= (float)dtMs * 0.001f;
            if (*p <= 0.0f) {
                pm->SetBabySpawned(i, false);
                pm = mPlayMode;
                *(float*)((char*)pm + off) = 0.0f;
            }
        }
        off += 4;
        i++;
    } while (off < 0x4c);
}

// @ 0x00638810
bool SP::cSPPlayModeSubModeAction_s0063_7f80::ReachedMomTargetAngle(uint32_t dtMs)
{
    cCreatureStructure* cs = mAnimCreatureMgr->GetCreatureStructure(mCreatureID);
    float a = cs->f48;
    float b = cs->f50;
    float f = FUN_0069b840(a, mPlayMode->mMomCrouchChangeTime, b * ((float)dtMs * 0.001f));
    cs->FUN_0059b2f0(f, 1);
    if (f == mPlayMode->mMomCrouchChangeTime) return true;
    return false;
}

// @ 0x00638890
bool SP::cSPPlayModeSubModeAction::IsLookAroundIdle(unsigned int animID)
{
    if (animID == 0x4112345) return true;
    if (animID == 0x44d7f20) return true;
    if (animID == 0x411238e) return true;
    if (animID == 0x41123a5) return true;
    if (animID == 0x407986c) return true;
    if (animID == 0x4079862) return true;
    if (animID == 0x4079874) return true;
    if (animID == 0x4079879) return true;
    if (animID == 0x4330317) return true;
    return false;
}

// @ 0x006388e0
void SP::cSPPlayModeSubModeAction_s0063_7f80::SetWalkAnimation(cAnimatingCreature_s0063_7f80* creature, uint32_t id)
{
    int curAnim;
    creature->GetAnimInfo(&curAnim, 0, 0, 0);
    if (curAnim == 0x4079859)
        mAnim->PlayAnimation(id, 0x452b634, 0, 0, 0);
    else
        mAnim->PlayAnimation(id, 0x452b634, 0, 1, 0);
    creature->mState = 2;
    int tmp = 0;
    mAnim->PlayAnimation(id, 0x452b64a, 1, 0, &tmp);
    if (creature->mpSub) creature->mpSub->FUN_00a006f0(tmp);
    creature->FUN_00a04ad0(mCurrIdleAnimState);
    uint32_t idleAnim = 0x4485a08;
    if (!(mCurrIdleAnimState - 2)) idleAnim = 0x4485a0f;
    mAnim->PlayAnimation(id, idleAnim, 1, 2, 0);
}

// @ 0x006389b0
bool SP::cSPPlayModeSubModeAction_s0063_7f80::AnyKeyDown()
{
    bool r = false;
    if (mKeyInputButtonState[0]) r = true;
    if (mKeyInputButtonState[1]) r = true;
    if (mKeyInputButtonState[2]) r = true;
    if (mKeyInputButtonState[3]) r = true;
    if (mKeyInputButtonState[4]) r = true;
    if (mKeyInputButtonState[5]) r = true;
    return r;
}

// @ 0x00638a00
void SP::cSPPlayModeSubModeAction_s0063_7f80::HandleExpansionAnim(uint32_t id)
{
    int animID = 0;
    int a = 0;
    float b = 1.0f, c = 0.0f;
    if (mAnim->GetExpansionAnimInfo(id, &animID, &a, &b, &c) && animID != -1) {
        if (mCurrIdleAnimState != 0) mMouthBidx = 1;
        mAnim->PlayAnimation(mCreatureID, animID, 0, 1, 0);
        mAnim->PlayAnimation(mCreatureID, 0x4330667, 1, 0, 0);
        ((cEditorStub2*)mEditorBaseMode)->FUN_00574110(0x4878ee8, a, b, c);
    }
}

// @ 0x00638ad0
void SP::cSPPlayModeSubModeAction_s0063_7f80::Shutdown()
{
    if (mLastLookAroundIdleID != (uint32_t)-1) {
        cIdleObjMgr* m = *(cIdleObjMgr**)((char*)mAnimCreature + 0x17c);
        cIdleObj* o = m->FUN_009cab60(mLastLookAroundIdleID);
        if (o) {
            cVisualEffect* e = o->mpEffect;
            if (e) e->Stop(1);
            m = *(cIdleObjMgr**)((char*)mAnimCreature + 0x17c);
            m->FUN_009cb460(o);
        }
        mLastLookAroundIdleID = (uint32_t)-1;
    }
    ((cPlayModeFlagStub*)mPlayMode)->FUN_0062ab80();
    *((uint8_t*)mPlayMode + 0x4c) = 0;
    mpField104->SetEffectsHandle(GetEffectsManager()->GetEffectsWorldHandle());
    mpField10c->Flush();
    cStopObj* p = mpField10c;
    if (p) {
        mpField10c = 0;
        p->Release();
    }
    GetEffectsManager()->RemoveEffect(0x61c8236);
    mpField104 = 0;
    mpField108 = 0;
}

// @ 0x00638ba0
bool SP::cSPPlayModeSubModeAction_s0063_7f80::OnMouseDown(int btn, float x, float y, int flags)
{
    if (btn == 1000) {
        void* world = mEditorBaseMode->mpModelWorld;
        if (mClickTime > 0.0f && 400.0f > mClickTime) {
            if (world && mAnimCreatureMgr) {
                mAnimCreatureMgr->SetCreatureSpeeds(mCreatureID, 4.0f, gDefaultSpeedB);
                mCurrIdleAnimState = 2;
            }
        } else {
            mClickTime = 0.0f;
            if (world && mAnimCreatureMgr) {
                mAnimCreatureMgr->SetCreatureSpeeds(mCreatureID, 2.5f, gDefaultSpeedB);
                mCurrIdleAnimState = 1;
            }
        }
        mX = x;
        mY = y;
        if (!mIsMouseDown) mIsFirstClick = true;
        mIsMouseDown = true;
    }
    if (mCursorEffect) {
        mCursorEffect->Stop(0);
        cVisualEffect* e = mCursorEffect;
        if (e) {
            mCursorEffect = 0;
            e->Release();
        }
    }
    return false;
}

// @ 0x00638c90
bool SP::cSPPlayModeSubModeAction_s0063_7f80::OnKeyUp(uint32_t key, uint32_t mods)
{
    if (!GetAssetBrowser()->mFlag1c) {
        switch (key) {
        case 0x26: case 0x57: case 0x68:
            mKeyInputButtonState[0] = false;
            return false;
        case 0x28: case 0x53: case 0x62:
            mKeyInputButtonState[2] = false;
            mMouthBidx = 1;
            return false;
        case 0x51: case 0x67:
            mKeyInputButtonState[4] = false;
            return false;
        case 0x45: case 0x69:
            mKeyInputButtonState[5] = false;
            return false;
        case 0x25: case 0x41: case 100:
            mKeyInputButtonState[1] = false;
            mAnimCreatureMgr->SetCreatureIsTurning(mCreatureID, false);
            return false;
        case 0x27: case 0x44: case 0x66:
            mKeyInputButtonState[3] = false;
            mAnimCreatureMgr->SetCreatureIsTurning(mCreatureID, false);
            break;
        }
    }
    return false;
}

// @ 0x00638d90
bool SP::cSPPlayModeSubModeAction_s0063_7f80::IsIdle()
{
    SP::cSPPlayMode_s0063_7f80* p = mPlayMode;
    if (p->mSleepB1c) return false;
    if (p->mSleepB1e) return false;
    if (p->mSleepB1d) return false;
    if (p->mSleepB1f) return false;
    if (p->mSleepB20) return false;
    if (p->mBabyPhotoMode) return false;
    if (mIsMouseDown) return false;
    if (mIsPickingUp) return false;
    if (mIsGoingToPickUp) return false;
    if (mIsThrowing) return false;
    if (mIsWalking) return false;
    if (AnyKeyDown()) return false;
    if (((cAnimCreatureHelper*)mAnimCreature)->FUN_00a02b20(0) || IsLookAroundIdle(mAnim->mCurrAnimID)) return true;
    return false;
}

// @ 0x00638e10
bool RayPlaneIntersectZ(const Vec3f* origin, const Vec3f* dir, Vec3f* out, float planeZ)
{
    if (dir->z == 0.0f) return false;
    float t = -((origin->z - planeZ) / dir->z);
    Vec3f r = *origin + *dir * t;
    out->x = r.x; out->y = r.y; out->z = r.z;
    return true;
}

// @ 0x00638e90
bool SP::cSPPlayModeSubModeAction::HasRequiredPart(int a1)
{ return false; }

// @ 0x00638fd0
float SP::cSPPlayModeSubModeAction::SetIdleAnimation(SP::cAnimatingCreature * a, unsigned int b, bool c, bool d)
{ (void)a; (void)b; (void)c; (void)d; return 0.0f; }

// @ 0x006392e0
void SP::cSPPlayModeSubModeAction::StartBoredAnimation(unsigned int t)
{ (void)t; }

// @ 0x00639350
void cSPPlayModeSubModeAction::FUN_00639350()
{}

// @ 0x006398f0
void SP::cSPPlayModeSubModeAction::MarkKeyInputKeyDown(unsigned int idx)
{ (void)idx; }

// @ 0x00639a10
void SP::cSPPlayModeSubModeAction::CaptureGIF()
{}

// @ 0x00639b70
void cSPPlayModeSubModeAction::FUN_00639b70()
{}

// @ 0x00639bd0
void SP::cSPPlayModeSubModeAction::Init(SP::SubModeParams_t * a1)
{}

// @ 0x00639ec0
bool cSPPlayModeSubModeAction_s0063_9bd0::OnKeyDown(int keyCode, int arg2)
{
    if (GetAssetBrowser_s0063_9bd0()->mActive)
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

// @ 0x0063a0a0
void cSPPlayModeSubModeAction_s0063_9bd0::Update(uint32_t deltaTime)
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
                EA::AutoRefCount_s0063_9bd0<cIVisualEffect> effect;
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
        cCreatureStructure_s0063_9bd0* cs = mAnimCreatureMgr->GetCreatureStructure(mCreatureID);
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
        !GetAssetBrowser_s0063_9bd0()->mActive && !SporeGuide()->mActive) {
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
                    cCreatureStructure_s0063_9bd0* cs = mAnimCreatureMgr->GetCreatureStructure(mCreatureID);
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
               GetAssetBrowser_s0063_9bd0()->mActive || SporeGuide()->mActive) {
        mIsWalking = false;
        SetIdleAnimation(mAnimCreature, mCreatureID, 0, 0);
        if (mMouthBidx || GetAssetBrowser_s0063_9bd0()->mActive || SporeGuide()->mActive) {
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
        EA::Random::RandomLinearCongruential_s0063_9bd0 rng;
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

// @ 0x0063aa90
bool cSPPlayModeSubModeAction_s0063_aa90::HandleButton(int id)
{
    cSPPlayMode_s0063_aa90* pm = mPlayMode;
    uint8_t btn = 0xff;
    uint32_t ev = 0xffffffff;
    mIsPickingUp = false;
    bool wasSleeping = false;
    if (pm->mB1d == 3) wasSleeping = true;
    pm->WakeupCreature();
    mPlayMode->FUN_00628810();
    if (id <= 0x3fc431c) {
        if (id == 0x3fc431c) {
            mEditorBaseMode->OnLayout(3, 5);
            KILL_SETI_AT();
            ev = mBabyEmotionEventIDs[8 - 0];   // +0xd8
            btn = 0xf;
        } else if (id <= 0x3e99e98) {
            if (id == 0x3e99e98) {
                KILL_SETI_AT();
                ev = mBabyActionEventIDs[3];
                btn = 2;
                mEditorBaseMode->OnLayout(0, 2);
            } else {
                switch (id) {
                case 0x3e99d88:
                    KILL_SETI_REC();
                    ev = mBabyActionEventIDs[1]; btn = 0;
                    mEditorBaseMode->OnLayout(0, 0);
                    break;
                case 0x3e99d8c:
                    KILL_SETI_REC();
                    ev = mBabyActionEventIDs[4]; btn = 3;
                    mEditorBaseMode->OnLayout(0, 3);
                    break;
                case 0x3e99d90:
                    KILL_SETI_REC();
                    ev = mBabyActionEventIDs[6]; btn = 5;
                    mEditorBaseMode->OnLayout(0, 5);
                    break;
                case 0x3e99d94:
                    KILL_SETI_REC();
                    ev = mBabyActionEventIDs[2]; btn = 1;
                    mEditorBaseMode->OnLayout(0, 1);
                    break;
                case 0x3e99de4:
                    KILL_SETI_REC();
                    ev = mBabyActionEventIDs[5]; btn = 4;
                    mEditorBaseMode->OnLayout(0, 4);
                    break;
                }
            }
        } else {
            switch (id) {
            case 0x3fc42e4:
                mEditorBaseMode->OnLayout(3, 0);
                KILL_SETI_REC();
                ev = mBabyEmotionEventIDs[3]; btn = 10;
                break;
            case 0x3fc4300:
                mEditorBaseMode->OnLayout(3, 1);
                KILL_SETI_REC();
                ev = mBabyEmotionEventIDs[4]; btn = 0xb;
                break;
            case 0x3fc4304:
                mEditorBaseMode->OnLayout(3, 2);
                KILL_SETI_REC();
                ev = mBabyEmotionEventIDs[5]; btn = 0xc;
                break;
            case 0x3fc4310:
                mEditorBaseMode->OnLayout(3, 3);
                KILL_SETI_REC();
                ev = mBabyEmotionEventIDs[6]; btn = 0xd;
                break;
            case 0x3fc4314:
                mEditorBaseMode->OnLayout(3, 4);
                KILL_SETI_REC();
                ev = mBabyEmotionEventIDs[7]; btn = 0xe;
                break;
            }
        }
    } else if (id <= 0x4866b6d) {
        if (id >= 0x4866b68) {
            HandleExpansionAnim(id);
            return true;
        }
        if (id <= 0x48669cc) {
            if (id >= 0x48669c8) {
                HandleExpansionAnim(id);
                return true;
            }
            if (id == 0x44eec00) {
                KILL_SETI_REC();
                if (mFaceUserTimer.GetElapsedTimeFloat() > 0.0f)
                    return true;
                mFaceUserTimer.mField[0] = 0;
                mFaceUserTimer.mField[1] = 0;
                mFaceUserTimer.mField[2] = 0;
                mFaceUserTimer.mField[3] = 0;
                mFaceUserTimer.StartIfUnset();
                return true;
            }
            if (id == 0x48669a8) {
                HandleExpansionAnim(id);
                return true;
            }
        } else {
            switch (id) {
            case 0x4866a98: case 0x4866a99: case 0x4866a9a: case 0x4866a9b: case 0x4866a9c: case 0x4866a9d:
            case 0x4866b10: case 0x4866b11: case 0x4866b12: case 0x4866b13: case 0x4866b14: case 0x4866b15:
                HandleExpansionAnim(id);
                return true;
            }
        }
    } else if (id <= 0x7034070) {
        if (id == 0x7034070) {
            KILL_SETI_AT();
            ev = mBabyEmotionEventIDs[2]; btn = 0x11;
        } else if (id == 0x58b74e8) {
            mPlayMode->mpUI->SetEnabled(0x58b74e8, false);
            CaptureGIF();
        } else if (id == 0x5b02188) {
            mPlayMode->mpUI->SetEnabled(0x5b02188, false);
            char* info = mEditorBaseMode->GetSaveInfo();
            mEditorBaseMode->SaveModel(info + 0xc, true);
        }
    } else if (id == 0x7034071) {
        KILL_SETI_AT();
        ev = mBabyEmotionEventIDs[1]; btn = 0x10;
    }
    uint32_t animID;
    switch (btn) {
    case 0: animID = 0x42dd0e8; break;
    case 1: animID = 0x42dd0e2; break;
    case 2:
        if (wasSleeping) return true;
        if (mPlayMode->mB1d == 0) {
            float len = mAnim->PlayAnimation(mCreatureID, 0x4079846, 0, 1, 0);
            mPlayMode->mF28 = len * 0.5f;
            mPlayMode->mB1d = 1;
            goto sendEvent;
        }
        mAnim->PlayAnimation(mCreatureID, 0x4079859, 0, 1, 0);
        mPlayMode->mF28 = 0.0f;
        mPlayMode->mB1d = 0;
        mPlayMode->SetAllBabySitUp();
        return true;
    case 3: {
        int r = sMathRandom.RandomUint32Uniform(3);
        if (r == 0) animID = 0x4330328;
        else if (r == 1) animID = 0x42dd0ee;
        else if (r == 2) animID = 0x4373686;
        else return true;
        break;
    }
    case 4:
        if (mPlayMode->mB1e != 0) return true;
        mPlayMode->mF2c = mAnim->PlayAnimation(mCreatureID, 0x42dd0f4, 0, 1, 0);
        if (mSocCallEffectID != (uint32_t)-1) {
            mPlayMode->mF30 = 0.5f;
            mPlayMode->mB1e = 1;
        } else {
            mPlayMode->mB1e = 2;
        }
        goto sendEvent;
    case 5: animID = 0x42dd0d5; break;
    case 10: animID = 0x42dd196; break;
    case 0xb: animID = 0x42dd19c; break;
    case 0xc: animID = 0x42dd1a9; break;
    case 0xd: animID = 0x42dd1ae; break;
    case 0xe: animID = 0x42dd1b3; break;
    case 0xf: animID = 0x42dd1b8; break;
    case 0x10: animID = 0x6f8a609; break;
    case 0x11: animID = 0x6f8a61b; break;
    default:
        return true;
    }
    if (mCurrIdleAnimState != 0) mMouthBidx = 1;
    mAnim->PlayAnimation(mCreatureID, animID, 0, 1, 0);
    mAnim->PlayAnimation(mCreatureID, 0x4330667, 1, 0, 0);
    if (ev != (uint32_t)-1) {
sendEvent:
        mEditorBaseMode->FUN_00574110(ev, -1, 1.0f, 0.0f);
    }
    return true;
}

// @ 0x0063b210
cSPPlayModeSubModeAction_s0063_aa90::cSPPlayModeSubModeAction_s0063_aa90()
: mFaceUserTimer(5, 0)
{
    mField104 = 0;
    mField108 = 0;
    mField10c = 0;
}
