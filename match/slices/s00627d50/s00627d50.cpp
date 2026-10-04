// slice s00627d50: camera update + depends, cSPPlayMode input forwarding / baby anim helpers
#include <new>
#include <string.h>
#include <math.h>
#include <float.h>
#include <intrin.h>
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);

__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

struct cSPVector3 {
    float x, y, z;
};
struct Vector3Copy {   // Math::Vector3 with a user copy ctor
    float x, y, z;
    Vector3Copy() {}
    Vector3Copy(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3Copy(const Vector3Copy& v) : x(v.x), y(v.y), z(v.z) {}
};
struct cSPQuaternion {
    float x, y, z, w;
};
static inline cSPVector3 MakeVec(float a, float b, float c)
{
    cSPVector3 r;
    r.x = a;
    r.y = b;
    r.z = c;
    return r;
}
struct cSPBoundingBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
};

extern float gCameraTurnRate;   // 0x15219dc
extern float kZoomRate;   // 0x13fdfb4 = 30.30303
extern float kZoomScale;  // 0x13f9324 = 0.015

namespace SP {

struct tAvatarData {
    Vector3Copy mPosition;      // +0x00
    cSPQuaternion mOrientaion;  // +0x0c
    cSPBoundingBox mLocalExtents;   // +0x1c
    cSPVector3 mVelocity;       // +0x34
    Vector3Copy mDestination;   // +0x40
    cSPVector3 mWASDDirection;  // +0x4c
    bool mbWASD;
    bool mbWASDTurning;
};

struct cEffectsHolder {
    char pad[0x17c];
    int** mIndex;   // +0x17c
};

struct cAnimatingCreature {
    int pad0;
    Vector3Copy mPos;      // +4
    char pad1[0x3c - 0x10];
    float mScale;          // +0x3c
    char pad2[0x17c - 0x40];
    int** mpIndexPtr;      // +0x17c
};

struct tModelInfo {   // *(**(creature+0x17c))
    char pad[0x364];
    float mWidth;     // +0x364
    float mDepth;     // +0x368
    float mHeight;    // +0x36c
};

class cCreatureCameraDepends {
public:
    tAvatarData mAvatar;                       // +0x00
    cSPVector3 mTargetCameraPositionOffset;    // +0x5c
    cSPVector3 mActualCameraPositionOffset;    // +0x68
    cAnimatingCreature* mAnimCreature;         // +0x74
    cCreatureCameraDepends();                  // 0x6281c0
    void SetTargetOffset(Vector3Copy v, bool snap);   // 0x6280d0
    void SetLocalExtents();                    // 0x628100
    void UpdateOffsets(float dt);              // 0x625750
    void OnKeyUp_SendMessage(int key, int unused);    // 0x628230
    void OnKeyDown_SendMessage(int key, int unused);  // 0x628340
};

struct IMessageServer {
    PV4 PV
    virtual void PostMessage(unsigned id, void* pMsg, int c);   // +0x14
};
IMessageServer* __cdecl MessageServer();

struct BehaviorMessageData {   // non-polymorphic base, laid out after the vptr
    int mnRefCount;      // +4
    int mField8;         // +8
    char padM[0x2c - 8];
    int mId;             // +0x30
    char padM2[4];
    BehaviorMessageData() : mId(0) {}
};
struct BehaviorMessageBase : BehaviorMessageData {
    virtual void bm0();
    virtual void AddRef();
    virtual void Release();
    BehaviorMessageBase() { _InterlockedExchange((volatile long*)&mnRefCount, 0); }
};
struct BehaviorMessage : BehaviorMessageBase {
    int mField38;
    char padM3[0x40 - 0x3c];
    BehaviorMessage() : mField38(0) {}
    virtual void AddRef();
    virtual void Release();
};

__forceinline void SendKeyMessage(int key, int down)
{
    BehaviorMessage* msg = 0;
    BehaviorMessage* p = new ("App", 0, 0, 0, 0) BehaviorMessage();
    if (p) {
        p->AddRef();
        msg = p;
    }
    msg->mField8 = down;
    switch (key) {
    case 0xbc:
        msg->mId = 0x3d72520;
        break;
    case 0xbe:
        msg->mId = 0x3d7252c;
        break;
    case 0x6d:
    case 0xbd:
        msg->mId = 0x3d72548;
        break;
    case 0x6b:
    case 0xbb:
        msg->mId = 0x3d7253e;
        break;
    }
    MessageServer()->PostMessage(msg->mId, msg, 0);
    msg->Release();
}

// @ 0x00628230
void cCreatureCameraDepends::OnKeyUp_SendMessage(int key, int unused)
{
    SendKeyMessage(key, 0);
}

// @ 0x00628340
void cCreatureCameraDepends::OnKeyDown_SendMessage(int key, int unused)
{
    SendKeyMessage(key, 1);
}

// @ 0x006281c0
cCreatureCameraDepends::cCreatureCameraDepends()
{
    mAvatar.mLocalExtents.mMin = MakeVec(FLT_MAX, FLT_MAX, FLT_MAX);
    mAvatar.mLocalExtents.mMax = MakeVec(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    mAnimCreature = 0;
}

// @ 0x006280d0
void cCreatureCameraDepends::SetTargetOffset(Vector3Copy v, bool snap)
{
    mTargetCameraPositionOffset = (const cSPVector3&)v;
    if (snap)
        mActualCameraPositionOffset = (const cSPVector3&)v;
}

// @ 0x00628100
void cCreatureCameraDepends::SetLocalExtents()
{
    float scale = mAnimCreature->mScale;
    const cSPVector3* pSize = (const cSPVector3*)((char*)**(int**)((char*)mAnimCreature + 0x17c) + 0x364);
    float ex = pSize->x * scale;
    float ey = pSize->y * scale;
    float ez = pSize->z * scale;
    float sx = ex * -0.5f;
    float sy = ey * -0.5f;
    mAvatar.mLocalExtents.mMax = MakeVec(-sx, -sy, ez);
    mAvatar.mLocalExtents.mMin = MakeVec(sx, sy, 0.0f);
}

class cICameraController { public: virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); };
class IRef2 { public: virtual void r0(); virtual void r1(); };

struct tCameraData {
    float dt;                                   // +0x00
    cSPVector3 platformPosition;                // +0x04
    cSPVector3 platformVelocity;                // +0x10
    cSPQuaternion platformOrientation;          // +0x1c
    cSPVector3 avatarPosition;                  // +0x2c
    float currentPlayerTheta;                   // +0x38
    float currentPlayerPitch;                   // +0x3c
    float currentPlayerDistance;                // +0x40
    cSPVector3 desiredPosition;                 // +0x44
    cSPVector3 desiredLookAt;                   // +0x50
    float mDesiredLookAtXOffset;                // +0x5c
    float mDesiredLookAtYOffset;                // +0x60
    cSPVector3 newPlatformPosition;             // +0x64
    cSPVector3 newPlatformVelocity;             // +0x70
    cSPQuaternion newPlatformOrientation;       // +0x7c
    float desiredPlayerTheta;                   // +0x8c
    float desiredPlayerPitch;                   // +0x90
    float desiredPlayerDistance;                // +0x94
    float nonPenetratingPhi;                    // +0x98
    bool bPenetrating;                          // +0x9c
    cSPVector3 currentPreTranslate;             // +0xa0
    cSPVector3 desiredPreTranslate;             // +0xac
    bool bTransitioning;                        // +0xb8
};

struct ICameraHelper {   // object passed to Update (field-of-view / projection owner)
    float GetFovBase();                         // 0x7c40a0
    float GetFovAspect();                       // 0x7c40e0
    void SetViewMatrix(void* pMatrix);          // 0x7c4d00
    void SetNearClip(float f);                  // 0x7c4ba0
    void SetFarClip(float f);                   // 0x7c4bc0
};

class cCreatureCameraBase : public cICameraController, public IRef2 {
public:
    int padA[2];
    cCreatureCameraDepends mDepends;            // +0x10
    int mCameraInputState;                      // +0x88
    int mCameraState;                           // +0x8c
    int mCameraMode;                            // +0x90
    int mDesiredCameraMode;                     // +0x94
    tCameraData mCameraData;                    // +0x98
    float mMouseSensitivityX;                   // +0x154
    float mMouseSensitivityY;                   // +0x158
    float mMouseSensitivityZ;                   // +0x15c
    float mMinCameraPhi;                        // +0x160
    float mMaxCameraPhi;                        // +0x164
    float mMinCameraDistance;                   // +0x168
    float mMaxCameraDistance;                   // +0x16c
    float mNearClip;                            // +0x170
    float mFarClip;                             // +0x174
    char padC[0x18c - 0x178];
    float mFieldOfViewX;                        // +0x18c
    float mFieldOfViewY;                        // +0x190
    char mCameraToWorld[0x38];                  // +0x194

    void UpdateCamera(float dt);                // 0x627d50
    void Update(unsigned ticks, ICameraHelper* pHelper);   // 0x627eb0
    void NormalizeTheta();                      // 0x6252c0
    void UpdateCamera_StandardControl(float dt);// 0x626ee0
    static void CalculateCameraToWorldMatrix(); // 0x6268a0
    void FUN_00627660();
};

// @ 0x00627d50
void cCreatureCameraBase::UpdateCamera(float dt)
{
    static float sRotateRate = gCameraTurnRate;
    switch (mCameraInputState) {
    case 1:
        mCameraData.desiredPlayerTheta = mCameraData.desiredPlayerTheta - sRotateRate * dt;
        break;
    case 2:
        mCameraData.desiredPlayerTheta = sRotateRate * dt + mCameraData.desiredPlayerTheta;
        break;
    case 4:
        {
            float z = dt * kZoomRate;
            z = z * kZoomScale;
            mCameraData.desiredPlayerDistance = (1.0f - z) * mCameraData.desiredPlayerDistance;
        }
        break;
    case 5:
        {
            float z = dt * kZoomRate;
            z = z * kZoomScale;
            mCameraData.desiredPlayerDistance = (z + 1.0f) * mCameraData.desiredPlayerDistance;
        }
        break;
    }
    float d = Clamp(mCameraData.desiredPlayerDistance, mMinCameraDistance, mMaxCameraDistance);
    int mode = mCameraMode;
    mCameraData.desiredPlayerDistance = d;
    if (mode == 0)
        UpdateCamera_StandardControl(dt);
}

// @ 0x00627eb0
void cCreatureCameraBase::Update(unsigned ticks, ICameraHelper* pHelper)
{
    float dt = (float)ticks * 0.001f;
    float a = pHelper->GetFovBase();
    float b = pHelper->GetFovAspect();
    mFieldOfViewX = b * a * 0.017453292f;
    mFieldOfViewY = pHelper->GetFovBase() * 0.017453292f;
    cCreatureCameraDepends* pDep = &mDepends;
    pDep->UpdateOffsets(dt);
    if (pDep->mAnimCreature)
        pDep->mAvatar.mPosition = pDep->mAnimCreature->mPos;
    if (mCameraData.bTransitioning) {
        float t = Clamp(dt, 0.01f, 0.1f);
        mCameraData.currentPreTranslate.y = (mCameraData.desiredPreTranslate.y - mCameraData.currentPreTranslate.y) * t * 3.0f + mCameraData.currentPreTranslate.y;
        mCameraData.currentPreTranslate.z = (mCameraData.desiredPreTranslate.z - mCameraData.currentPreTranslate.z) * t * 3.0f + mCameraData.currentPreTranslate.z;
        mCameraData.currentPreTranslate.x = mCameraData.currentPreTranslate.x + (mCameraData.desiredPreTranslate.x - mCameraData.currentPreTranslate.x) * t * 3.0f;
        float dx = mCameraData.desiredPreTranslate.x - mCameraData.currentPreTranslate.x;
        float dy = mCameraData.desiredPreTranslate.y - mCameraData.currentPreTranslate.y;
        float dz = mCameraData.desiredPreTranslate.z - mCameraData.currentPreTranslate.z;
        if (sqrtf(dz * dz + dy * dy + dx * dx) < 0.001f)
            mCameraData.bTransitioning = false;
    }
    UpdateCamera(dt);
    mCameraData.nonPenetratingPhi = mCameraData.currentPlayerPitch;
    NormalizeTheta();
    CalculateCameraToWorldMatrix();
    FUN_00627660();
    pHelper->SetViewMatrix(mCameraToWorld);
    pHelper->SetNearClip(mNearClip);
    pHelper->SetFarClip(mFarClip);
}

// ===========================================================================
// cSPPlayMode helpers
// ===========================================================================
struct ISubMode {
    PV4 PV2 PV
    virtual bool OnMouseUp(int a, float b, float c, int d);   // +0x1c
    virtual bool OnMouseMove(float a, float b, int c);        // +0x20
    virtual bool OnKeyDown(int a, int b);                     // +0x24
    virtual bool OnKeyUp(int a, int b);                       // +0x28
};

struct IWinMgrT {
    PV16 PV2
    virtual void* GetFocusedWindow(int a);          // +0x48
    virtual void SetFocusedWindow(int a, void* w);  // +0x4c
    PV8 PV4 PV
    virtual void* GetInputCapture();                // +0x84
};
IWinMgrT* __cdecl WindowManager();
void* __cdecl AssetBrowser();

struct IAnimator {   // cSPPlayModeAnimation (vtable at +0)
    PV2 PV
    virtual float PlayAnim(unsigned creatureId, unsigned animId, int a, int b, int c);   // +0x0c
    void ResetCurAnimWindow();    // 0x62e7a0
    void UpdatePageCount();       // 0x62e600
};
struct cSPPlayModeAnimation : IAnimator {
    char data[0x8c - 4];
};

struct IEventInfo {
    void Fire(int arg);           // 0x59aea0 (cSPEditorAnimatedEventInfo ctor)
};
struct ICreatureT {
    PV16 PV8 PV4 PV
    virtual int QueryPart(char* buf, int n, int h, void* pQuery, int z);   // +0x74
    char padC[0x17c - 4];
    int* mp17c;                   // +0x17c
};
struct cCreatureManager {
    ICreatureT* GetCreature(unsigned id);              // 0x59ca70
    IEventInfo* GetCreatureStructure(unsigned id);     // 0x59cac0
};
struct tElem48 {
    unsigned mId;
    char pad[0x30 - 4];
};
struct tEditorState {
    char pad[0x360];
    cCreatureManager* mpManager;   // +0x360
    unsigned mCreatureId;          // +0x364
    char pad2[0x36c - 0x368];
    tElem48* mpVecBegin;           // +0x36c
    tElem48* mpVecEnd;             // +0x370
    char pad3[0x378 - 0x374];
    float mHeightOffsetDummy;
};
struct cEditorCreatureStruct {
    char pad[0x74];
    float mHeightOffset;           // +0x74
};

struct cSPPlayModeUI {
    void* FindEditorUIWindow(unsigned id);   // 0x634e40
};
struct IWindowT {
    PV8 PV2
    virtual unsigned IsVisible();   // +0x28
};

namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    unsigned mnSeed;
    unsigned RandomUint32Uniform(unsigned n);
};
} }
extern EA::Random::RandomLinearCongruential sMathRandomA;   // 0x1601760

struct cPlayModeCommon {
    PV8 PV8 PV8 PV8 PV2 PV
    virtual void OnCommand(unsigned id);   // +0x24 (slot 9)
};

class cSPPlayMode {
public:
    char pad0[0x0c];
    cSPPlayModeUI* mpUI;                   // +0x0c
    char pad1[0x4e - 0x10];
    unsigned char mBabyPhotoMode[3];       // +0x4e
    char pad2[0xc8 - 0x51];
    ISubMode* mSubModes[4];                // +0xc8
    char pad3[0x3588 - 0xd8];
    cSPPlayModeAnimation mAnimation;       // +0x3588
    tEditorState* mpState;                 // +0x3614
    char pad4[0x36d0 - 0x3618];
    unsigned char mLevel;                  // +0x36d0
    char pad5[3];
    unsigned mLastEnvAnim;                 // +0x36d4
    int mBabyAnimIds[3];                   // +0x36d8

    unsigned char OnMouseUp(int a, float b, float c, int d);   // 0x628520
    unsigned char OnMouseMove(float a, float b, int c);        // 0x628570
    unsigned char OnKeyUp(int a, int b);                       // 0x6285c0
    static bool __stdcall IsWalkTypeAnim(unsigned id);         // 0x628610
    unsigned GetRandomEnvironmentReactionAnim();               // 0x6286a0
    int FindFreeBabyAnimSlot();                                // 0x628500
    int FindBabyAnimSlot(int id);                              // 0x628720
    unsigned char GetBabyPhotoMode(int id);                    // 0x628750
    float SetMomCelebrationAnim(bool* pOut);                   // 0x628780
    float SetMomCrouchAnimation();                             // 0x628830
    float SetBabyCrouchAnimation(unsigned creatureId);         // 0x628860
    void SetAllBabyPhotoModes(bool b);                         // 0x6288a0
    void ResetExpansionAnimWindow();                           // 0x6288f0
    float GetHeightOffset();                                   // 0x628a40
    int GetMouthPartIdx();                                     // 0x628a80
    unsigned char OnKeyDown(int key, int flag);                // 0x628af0
    void W6288d0(bool b);                                      // 0x6288d0
    bool W628940();                                            // 0x628940
};

// @ 0x00628520
unsigned char cSPPlayMode::OnMouseUp(int a, float b, float c, int d)
{
    unsigned char r = 0;
    ISubMode** p = mSubModes;
    int n = 4;
    do {
        if (*p)
            r |= (*p)->OnMouseUp(a, b, c, d);
        ++p;
        --n;
    } while (n != 0);
    return r;
}

// @ 0x00628570
unsigned char cSPPlayMode::OnMouseMove(float a, float b, int c)
{
    unsigned char r = 0;
    ISubMode** p = mSubModes;
    int n = 4;
    do {
        if (*p)
            r |= (*p)->OnMouseMove(a, b, c);
        ++p;
        --n;
    } while (n != 0);
    return r;
}

// @ 0x006285c0
unsigned char cSPPlayMode::OnKeyUp(int a, int b)
{
    unsigned char r = 0;
    ISubMode** p = mSubModes;
    int n = 4;
    do {
        if (*p)
            r |= (*p)->OnKeyUp(a, b);
        ++p;
        --n;
    } while (n != 0);
    return r;
}

// @ 0x00628610
bool __stdcall cSPPlayMode::IsWalkTypeAnim(unsigned id)
{
    switch (id) {
    case 0x44828e9:
    case 0x4482906:
    case 0x4482911:
    case 0x4482918:
    case 0x448291f:
    case 0x4485a08:
    case 0x4485a0f:
    case 0x452b634:
    case 0x452b64a:
    case 0x452b651:
        return true;
    }
    return false;
}

// @ 0x006286a0
unsigned cSPPlayMode::GetRandomEnvironmentReactionAnim()
{
    unsigned anim;
    do {
        switch (sMathRandomA.RandomUint32Uniform(6)) {
        case 0:
            anim = 0x431df93;
            break;
        case 1:
            anim = 0x431df9a;
            break;
        case 2:
            anim = 0x431df9f;
            break;
        case 3:
            anim = 0x431dfa6;
            break;
        case 4:
            anim = 0x44d798c;
            break;
        case 5:
            anim = 0x44d7999;
            break;
        }
    } while (mLastEnvAnim == anim);
    mLastEnvAnim = anim;
    return anim;
}

// @ 0x00628500
int cSPPlayMode::FindFreeBabyAnimSlot()
{
    unsigned i = 0;
    int* p = mBabyAnimIds;
    do {
        if (*p == 0)
            return i;
        ++i;
        ++p;
    } while (i < 3);
    return -1;
}

// @ 0x00628720
int cSPPlayMode::FindBabyAnimSlot(int id)
{
    unsigned i = 0;
    int* p = mBabyAnimIds;
    do {
        if (*p == id)
            return i;
        ++i;
        ++p;
    } while (i < 3);
    return -1;
}

// @ 0x00628750
unsigned char cSPPlayMode::GetBabyPhotoMode(int id)
{
    unsigned i = 0;
    int* p = mBabyAnimIds;
    do {
        if (*p == id)
            return mBabyPhotoMode[i];
        ++i;
        ++p;
    } while (i < 3);
    return 0;
}

// @ 0x00628780
float cSPPlayMode::SetMomCelebrationAnim(bool* pOut)
{
    *pOut = false;
    unsigned anim = 0x4335859;
    if (mLevel > 1) {
        if (sMathRandomA.RandomUint32Uniform(100) < 40) {
            anim = 0x4346928;
            *pOut = true;
        }
    }
    float r = mAnimation.PlayAnim(mpState->mCreatureId, anim, 0, 1, 0);
    mAnimation.PlayAnim(mpState->mCreatureId, 0x4330667, 1, 0, 0);
    return r;
}

// @ 0x00628830
float cSPPlayMode::SetMomCrouchAnimation()
{
    return mAnimation.PlayAnim(mpState->mCreatureId, 0x433585e, 0, 1, 0);
}

// @ 0x00628860
float cSPPlayMode::SetBabyCrouchAnimation(unsigned creatureId)
{
    return mAnimation.PlayAnim(creatureId, 0x43736cd, 0, 1, 0);
}

// @ 0x006288a0
void cSPPlayMode::SetAllBabyPhotoModes(bool b)
{
    unsigned char v = b;
    *(unsigned short*)&mBabyPhotoMode[0] = (unsigned short)((unsigned short)(v << 8) | (unsigned short)v);
    mBabyPhotoMode[2] = v;
}

// @ 0x006288f0
void cSPPlayMode::ResetExpansionAnimWindow()
{
    mAnimation.ResetCurAnimWindow();
    mAnimation.UpdatePageCount();
}

// @ 0x00628a40
float cSPPlayMode::GetHeightOffset()
{
    tEditorState* st = mpState;
    cCreatureManager* mgr = st->mpManager;
    mgr->GetCreature(st->mCreatureId);
    cEditorCreatureStruct* s = (cEditorCreatureStruct*)mgr->GetCreatureStructure(mpState->mCreatureId);
    if (s)
        return s->mHeightOffset;
    return 0.0f;
}

// @ 0x00628a80
int cSPPlayMode::GetMouthPartIdx()
{
    struct PartQuery {
        int a;
        unsigned name;
        int c;
        int outIndex;
    };
    char buf[0x3fc];
    PartQuery q;
    ICreatureT* creature = mpState->mpManager->GetCreature(mpState->mCreatureId);
    q.a = 0;
    q.name = 0x74756f6d;
    q.c = 0;
    q.outIndex = 0;
    if (creature->QueryPart(buf, 0xff, *creature->mp17c, &q, 0))
        return q.outIndex;
    return -1;
}

// @ 0x00628af0
unsigned char cSPPlayMode::OnKeyDown(int key, int flag)
{
    WindowManager()->GetInputCapture();
    AssetBrowser();
    if (key != 9) {
        if (key == 0x43 && flag == 0) {
            ((cPlayModeCommon*)this)->OnCommand(0x3a8ede4);
            return 1;
        }
    } else {
        IWindowT* pTab = (IWindowT*)mpUI->FindEditorUIWindow(0x3f67620);
        if (pTab) {
            if (pTab->IsVisible() & 1) {
                if (WindowManager()->GetFocusedWindow(0) == mpUI->FindEditorUIWindow(0x4581d50)) {
                    IWinMgrT* wm = WindowManager();
                    wm->SetFocusedWindow(0, mpUI->FindEditorUIWindow(0x4581d78));
                } else if (WindowManager()->GetFocusedWindow(0) == mpUI->FindEditorUIWindow(0x4581d78)) {
                    IWinMgrT* wm = WindowManager();
                    wm->SetFocusedWindow(0, mpUI->FindEditorUIWindow(0x4581d90));
                } else if (WindowManager()->GetFocusedWindow(0) == mpUI->FindEditorUIWindow(0x4581d90)) {
                    IWinMgrT* wm = WindowManager();
                    wm->SetFocusedWindow(0, mpUI->FindEditorUIWindow(0x4581d50));
                } else {
                    IWinMgrT* wm = WindowManager();
                    wm->SetFocusedWindow(0, mpUI->FindEditorUIWindow(0x4581d50));
                }
            }
        }
    }
    unsigned char r = 0;
    ISubMode** p = mSubModes;
    int n = 4;
    do {
        if (*p)
            r |= (*p)->OnKeyDown(key, flag);
        ++p;
        --n;
    } while (n != 0);
    return r;
}

// ===========================================================================
// misc
// ===========================================================================
// @ 0x00628450
struct IEffectsT {
    PV2
    virtual bool CreateEffect(unsigned id, int a, int b);   // +0x08
};
struct IEffectsMgrT {
    PV16 PV4 PV2 PV
    virtual IEffectsT* GetDefaultEffects();   // +0x5c (slot 23)
};
IEffectsMgrT* __cdecl EffectsManager();
void __cdecl CreateEffectSafe(IEffectsT* pEffects, unsigned effectId, int unused, int arg)
{
    if (!pEffects)
        pEffects = EffectsManager()->GetDefaultEffects();
    if (pEffects->CreateEffect(effectId, 0, arg) != 1)
        pEffects->CreateEffect(0xe18d6423, 0, arg);
}

// @ 0x006284b0
struct IStateObj {
    PV
    virtual void Enter(void* pOwnerData);   // +0x04
    virtual void Exit();                    // +0x08
};
struct cStateMachine {
    char pad[0xc0];
    int mCurrentState;                      // +0xc0
    char pad2[4];
    IStateObj* mStates[4];                  // +0xc8
    void SetState(int state);
};
void cStateMachine::SetState(int state)
{
    int cur = mCurrentState;
    if (cur != state) {
        if (cur < 4)
            mStates[cur]->Exit();
        mCurrentState = state;
        mStates[state]->Enter((char*)this + 0x98);
    }
}

// @ 0x00628810
struct cResetable {
    char pad[0x1f];
    bool mFlagA;    // +0x1f
    bool mFlagB;    // +0x20
    char pad2[0x34 - 0x21];
    float mValueA;  // +0x34
    float mValueB;  // +0x38
    void Reset();
};
void cResetable::Reset()
{
    mFlagA = false;
    mFlagB = false;
    mValueA = 0.0f;
    mValueB = 0.0f;
}

// @ 0x006288d0
struct cSPPlayModeAnimation2 : cSPPlayModeAnimation {
    void FUN_0062ebe0();
    void FUN_0062ec30();
};
void cSPPlayMode::W6288d0(bool b)
{
    if (b) {
        ((cSPPlayModeAnimation2*)&mAnimation)->FUN_0062ebe0();
        return;
    }
    ((cSPPlayModeAnimation2*)&mAnimation)->FUN_0062ec30();
}

// @ 0x00628910
void __cdecl FUN_00809db0(int a, void* b);
extern char gUnknown1522480;
void __cdecl W628910()
{
    FUN_00809db0(0, &gUnknown1522480);
}

// @ 0x00628940
struct cSubObj3618 {
    bool FUN_0062f6c0();
};
bool cSPPlayMode::W628940()
{
    return ((cSubObj3618*)((char*)this + 0x3618))->FUN_0062f6c0() == 0;
}

// @ 0x00628970
struct Quat4 {
    float x, y, z, w;
    Quat4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};
Quat4* ForceQuat(void* p, float a, float b, float c, float d) { return new (p) Quat4(a, b, c, d); }

// @ 0x006289a0
struct cTexturePreload {
    virtual void AddRef();
    virtual void Release();
    char pad[0x34 - 4];
    cTexturePreload(int a);                              // 0x7b07e0
    void PreloadTextureList(const unsigned* pKey);       // 0x7b1e90
};
struct cPreloadOwner {
    char pad[0x94];
    cTexturePreload* mpPreload;   // +0x94
    void EnsurePreload();
};
void cPreloadOwner::EnsurePreload()
{
    if (!mpPreload) {
        cTexturePreload* pNew = new ("Editor", 0, 0, 0, 0) cTexturePreload(-1);
        cTexturePreload* pOld = mpPreload;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            mpPreload = pNew;
            if (pOld)
                pOld->Release();
        }
        unsigned key[3] = { 0x7518573e, 0x510a95b, 0x40464100 };
        mpPreload->PreloadTextureList(key);
    }
}

// @ 0x00628ca0
struct cAppModeEditorBaseT {
    char pad[0x3614];
    tEditorState* mpState;
    void SendButtonEventToBabies(int arg);
};
void cAppModeEditorBaseT::SendButtonEventToBabies(int arg)
{
    tEditorState* st = mpState;
    cCreatureManager* mgr = st->mpManager;
    unsigned id = st->mCreatureId;
    if (mgr->GetCreatureStructure(id))
        mgr->GetCreatureStructure(id)->Fire(arg);
    st = mpState;
    int n = (int)(st->mpVecEnd - st->mpVecBegin);
    if (n != 0) {
        int off = 0;
        do {
            unsigned eid = *(unsigned*)((char*)st->mpVecBegin + off);
            if (mgr->GetCreatureStructure(eid))
                mgr->GetCreatureStructure(*(unsigned*)((char*)st->mpVecBegin + off))->Fire(arg);
            off += 0x30;
            --n;
        } while (n != 0);
    }
}
}   // namespace SP
