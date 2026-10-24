// Slice s00d2aec0: SP::cCreatureCamera::Update(unsigned ticks, ICameraHelper* helper)  (retail layout, raw offsets)
// Frame: exponential-decay interpolation of the anchor/orientation/theta/pitch/distance targets, theta wrap
// (+-kWrap), planet-height effect hook, anchor-vector and orientation easing toward their targets, then the
// camera-to-world matrix and the helper (projection owner) updates.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include <math.h>
#include "types.h"

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

template<class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct cSPVector3 : Vector3 {
    cSPVector3() {}
    cSPVector3(const Vector3& v) : Vector3(v) {}
};
struct cSPQuaternion {
    float x, y, z, w;
    cSPQuaternion() {}
    cSPQuaternion(const cSPQuaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
};

extern float kWrap;   // 0x0169df68

namespace SP {
cSPVector3 normalized_safe(const cSPVector3& v);                                         // 0x00449c20
cSPVector3 RotateTowards(const cSPVector3& from, const cSPVector3& to, float t);        // 0x00b0fd00
cSPQuaternion SlerpWrap(const cSPQuaternion& a, const cSPQuaternion& b, float t);        // 0x005b26f0
void* GetCurrentGameMode();                                                              // 0x00b5b800
}
bool FUN_00809970();                                                                     // 0x00809970
bool FUN_00d21ca0(const Vector3& a, const Vector3& b, float tolerance);                  // 0x00d21ca0
float VectorLength(const Vector3* v);                                                    // 0x0040ae50
void ApplyStateFromProperty(void* obj, float h);                                         // 0x006f32e0
extern char g_Mode_1654c01;

struct ICameraHelper {
    float GetFovBase();                         // 0x7c40a0
    float GetFovAspect();                       // 0x7c40e0
    void SetViewMatrix(void* pMatrix);          // 0x7c4d00
    void SetNearClip(float f);                  // 0x7c4ba0
    void SetFarClip(float f);                   // 0x7c4bc0
};
struct cCreatureModeStrategy {
    static cCreatureModeStrategy* Instance();   // 0x00d38840
    bool FUN_00d38880();
};
struct IPlanetTerrain {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual float* GetRadiusInfo();             // +0x0c: floats at +0x34, +0x38, +0x3c
};
struct cPlanetModel {
    char pad[0x24];
    IPlanetTerrain* mpTerrain;                  // +0x24
};
cPlanetModel* PlanetModel();                    // 0x00b3d350

namespace SP {
class cCreatureCamera {
public:
    void Update(unsigned ticks, ICameraHelper* pHelper);
    void SetTransform(float dt);                // 0x00d2a980
    void CalculateCameraToWorldMatrix();        // 0x00d26c90
    void FUN_00d23320();                        // 0x00d23320
    void UpdateAvatarAlpha();                   // 0x00d25e10
    void PrintDebug(ICameraHelper* pHelper);    // 0x00d2a520

    char pad0[0xf8];
    /* 0f8 */ float mBoundMaxY;
    char pad0fc[0x180 - 0xfc];
    /* 180 */ cSPVector3 mAltPos;
    /* 18c */ float mDesiredTheta;
    /* 190 */ float mDesiredPitch;
    /* 194 */ float mDesiredDistance;
    /* 198 */ float mTargetTheta;
    char pad19c[0x1ac - 0x19c];
    /* 1ac */ cSPVector3 mVecB;
    /* 1b8 */ cSPQuaternion mQuatR;
    /* 1c8 */ cSPVector3 mVecA;
    /* 1d4 */ cSPQuaternion mQuatQ;
    char pad1e4[0x204 - 0x1e4];
    /* 204 */ float mMouseSensitivityY;
    char pad208[0x220 - 0x208];
    /* 220 */ float mInitialDistance;
    /* 224 */ float mInitialRotation;
    /* 228 */ float mTimeNear;
    /* 22c */ float mTimeFar;
    /* 230 */ float mTimeAnchor;
    /* 234 */ float mTimeOrientation;
    /* 238 */ float mTimeTheta;
    char pad23c[0x258 - 0x23c];
    /* 258 */ float mFovX;
    /* 25c */ float mFovY;
    /* 260 */ float mCameraToWorld[10];
    char pad288[0x308 - 0x288];
    /* 308 */ void* mpStateObj;
};

static inline float Decay(float dt, float time)
{
    return (float)exp((double)(dt / time) * (double)-0.30103f);
}

// @ 0x00d2aec0
void cCreatureCamera::Update(unsigned ticks, ICameraHelper* pHelper)
{
    if (FUN_00809970()) {
        if (GetCurrentGameMode() != &g_Mode_1654c01)
            return;
        if (!cCreatureModeStrategy::Instance()->FUN_00d38880())
            return;
    }
    float dt = (float)ticks * 0.001f;
    float a = pHelper->GetFovBase();
    float b = pHelper->GetFovAspect();
    mFovX = b * a * 0.017453292f;
    mFovY = pHelper->GetFovBase() * 0.017453292f;
    SetTransform(dt);
    cPlanetModel* pPlanet = PlanetModel();

    float aNear = 1.0f - Decay(dt, mTimeNear);
    float aFar = 1.0f - Decay(dt, mTimeFar);
    float aAnchor = 1.0f - Decay(dt, mTimeAnchor);
    mDesiredTheta = mDesiredTheta + (mAltPos.x - mDesiredTheta) * aAnchor;
    float aOri = 1.0f - Decay(dt, mTimeOrientation);
    float pitch = mDesiredPitch + (mAltPos.y - mDesiredPitch) * aOri;
    mDesiredPitch = pitch;
    mTargetTheta = pitch;
    float aTheta = 1.0f - Decay(dt, mTimeTheta);
    mDesiredDistance = mDesiredDistance + (mAltPos.z - mDesiredDistance) * aTheta;

    // wrap the three angles into +-kWrap
    float wrap = kWrap;
    if (Min(Min(mDesiredTheta, mAltPos.x), mBoundMaxY) > wrap) {
        mDesiredTheta = mDesiredTheta - wrap;
        mAltPos.x = mAltPos.x - wrap;
        mBoundMaxY = mBoundMaxY - wrap;
    } else if (-wrap > Max(Max(mDesiredTheta, mAltPos.x), mBoundMaxY)) {
        mDesiredTheta = mDesiredTheta + wrap;
        mAltPos.x = mAltPos.x + wrap;
        mBoundMaxY = wrap + mBoundMaxY;
    }

    if (pPlanet && pPlanet->mpTerrain) {
        float len = sqrtf((mCameraToWorld[1] * mCameraToWorld[1] + mCameraToWorld[2] * mCameraToWorld[2]) + mCameraToWorld[3] * mCameraToWorld[3]);
        float* info = pPlanet->mpTerrain->GetRadiusInfo();
        ApplyStateFromProperty(mpStateObj, len - (info[0x3c / 4] * info[0x38 / 4] + info[0x34 / 4]));

        if (mVecA.x * mVecA.x + mVecA.y * mVecA.y + mVecA.z * mVecA.z <= 1.5258789e-05f ||
            mVecB.x * mVecB.x + mVecB.y * mVecB.y + mVecB.z * mVecB.z <= 1.5258789e-05f) {
            mVecA = mVecB;
        } else {
            cSPVector3 nA = normalized_safe(mVecA);
            cSPVector3 nB = normalized_safe(mVecB);
            if (FUN_00d21ca0(nA, nB, 1.5258789e-05f)) {
                mVecA = mVecB;
            } else {
                float t = Clamp(aNear, 0.0f, 1.0f);
                cSPVector3 r = RotateTowards(cSPVector3(nA), nB, t);
                float la = VectorLength(&mVecA);
                float lb = VectorLength(&mVecB);
                float s = (lb - la) * aNear + la;
                mVecA.x = r.x * s;
                mVecA.y = r.y * s;
                mVecA.z = r.z * s;
            }
        }

        float dx = mVecA.x - mVecB.x;
        float dy = mVecA.y - mVecB.y;
        float dz = mVecA.z - mVecB.z;
        if (mMouseSensitivityY < sqrtf((dz * dz + dy * dy) + dx * dx)) {
            Vector3 d(mVecA.x - mVecB.x, mVecA.y - mVecB.y, mVecA.z - mVecB.z);
            cSPVector3 n = normalized_safe(d);
            mVecA.x = mMouseSensitivityY * n.x + mVecB.x;
            mVecA.y = mVecB.y + n.y * mMouseSensitivityY;
            mVecA.z = mVecB.z + n.z * mMouseSensitivityY;
        }

        float d0 = mQuatQ.x - mQuatR.x;
        if (d0 < 0.0f) d0 = -d0;
        bool same = false;
        if (d0 <= 1.5258789e-05f) {
            float d1 = mQuatQ.y - mQuatR.y;
            if (d1 < 0.0f) d1 = -d1;
            if (d1 <= 1.5258789e-05f) {
                float d2 = mQuatQ.z - mQuatR.z;
                if (d2 < 0.0f) d2 = -d2;
                if (d2 <= 1.5258789e-05f) {
                    float d3 = mQuatQ.w - mQuatR.w;
                    if (d3 < 0.0f) d3 = -d3;
                    if (d3 <= 1.5258789e-05f)
                        same = true;
                }
            }
        }
        if (same) {
            mQuatQ.x = mQuatR.x;
            mQuatQ.y = mQuatR.y;
            mQuatQ.z = mQuatR.z;
            mQuatQ.w = mQuatR.w;
        } else {
            mQuatQ = SlerpWrap(cSPQuaternion(mQuatQ), mQuatR, Clamp(aFar, 0.0f, 1.0f));
        }
    }

    CalculateCameraToWorldMatrix();
    FUN_00d23320();
    if (GetCurrentGameMode() == &g_Mode_1654c01)
        UpdateAvatarAlpha();
    pHelper->SetViewMatrix(&mCameraToWorld[0]);
    pHelper->SetNearClip(mInitialDistance);
    pHelper->SetFarClip(mInitialRotation);
    PrintDebug(pHelper);
}

}  // namespace SP

// ---------------------------------------------------------------------------------------------
// Achievement / UI / posse helpers that live next to the camera code.
struct cAchievementsController {
    void AwardAchievement(uint32_t id);                             // 0x00676710
    bool HasAchievement(uint32_t id);                               // 0x006766f0
    void AutoTest(uint32_t id, int value);                          // 0x00676e90
};
cAchievementsController* GetAchievementsController();               // 0x00675250

struct ITerrainSphere {
    int32_t GetSurfaceKind();                                       // 0x00c75420
};
struct cNounManagerTerrain {
    ITerrainSphere* GetCurrentTerrainSphere();                      // 0x00f67d90
};
cNounManagerTerrain* GetNounManagerTerrain();                       // 0x00b3d300

// @ 0x00d2b5f0
void AwardCreatureAchievements()
{
    cAchievementsController* ctrl = GetAchievementsController();
    ctrl->AwardAchievement(0x8f5e1285u);
    if (ctrl->HasAchievement(0x6e36e67fu))
        ctrl->AwardAchievement(0x6e36e67fu);
    if (ctrl->HasAchievement(0xba577381u))
        ctrl->AwardAchievement(0xba577381u);
    if (ctrl->HasAchievement(0x94f5e078u))
        ctrl->AwardAchievement(0x94f5e078u);
    if (ctrl->HasAchievement(0x838a3cf4u))
        ctrl->AwardAchievement(0x838a3cf4u);
    ctrl->AutoTest(0x8baf77deu, 1);
    if (GetNounManagerTerrain()->GetCurrentTerrainSphere()->GetSurfaceKind() == 2)
        ctrl->AwardAchievement(0x24545cdfu);
}

struct cSimBlob {
    float NodeRatio();                                              // 0x00bfc490
    uint8_t pad04[0x20];                                            // sizeof == 0x20
};
struct cSimBarHost {
    uint8_t  pad00[0x5a8];
    cSimBlob mSim;                                                  // +0x5a8
};
void FUN_00b69930(void* pOwner, float ratio, int flag);             // 0x00b69930

// @ 0x00d2b6b0
void __stdcall RefreshSimBar(cSimBarHost* pOwner)
{
    FUN_00b69930(pOwner, pOwner->mSim.NodeRatio(), 0);
}

struct Vec4;

struct cUIWindow {
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12();
    virtual Vec4* GetRect();                                        // +0x34
    virtual void V14(); virtual void V15(); virtual void V16(); virtual void V17();
    virtual void V18(); virtual void V19(); virtual void V20(); virtual void V21();
    virtual void V22(); virtual void V23();
    virtual void SetRect(Vec4* pRect);                              // +0x60
    virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30();
    virtual void SetSelected(bool selected, bool animate);          // +0x7c
};
struct cUIWindowHost {
    void* FindWindowByID(uint32_t id);                              // 0x00e012b0
};
struct cPosseUIState {
    uint8_t pad00[0xdc];
    uint8_t mVisibleFlag;                                           // +0xdc
};
extern cPosseUIState* g_pPosseUIState;                              // 0x0169e294

struct cCreatureDisplayStrategyA {
    uint8_t      pad00[0x58];
    cUIWindowHost* mpPosseUI;                                       // +0x58
    void SetPosseWindowState(uint32_t id, bool visible);
};

// @ 0x00d2b6e0
void cCreatureDisplayStrategyA::SetPosseWindowState(uint32_t id, bool visible)
{
    if (!mpPosseUI)
        return;
    cUIWindow* w = (cUIWindow*)mpPosseUI->FindWindowByID(id);
    if (!w)
        return;
    w->SetSelected(true, visible);
    if (id == 0x6455b55u)
        g_pPosseUIState->mVisibleFlag = (uint8_t)visible;
}

struct cPosseMessage {
    uint8_t pad00[8];
    void*   mpMember;                                               // +0x08
};
struct cPosseSimulator {
    static cPosseSimulator* Instance();                             // 0x00d539d0
    void RemovePosseMember(void* member, int a, int b);             // 0x00d53490
    uint32_t GetMemberCount();                                      // 0x00d52e10
};

// @ 0x00d2b8c0
bool __stdcall OnRemovePosseMemberMessage(uint32_t msg, cPosseMessage* pMsg)
{
    if (msg == 0x14051500u)
    {
        void* pMember = pMsg->mpMember;
        cPosseSimulator::Instance()->RemovePosseMember(pMember, 1, 0);
    }
    return false;
}

struct cGonzagoTimerLike {
    void ResetTimer();                                              // 0x00b63890
    void ShutdownTimer();                                           // 0x00b638b0
    uint8_t pad04[0x20];                                            // sizeof == 0x20
};
struct IRefV08 {
    virtual void V00(); virtual void V04();
    virtual void Release();                                         // +0x08
};
struct cTimerBarHost {
    uint8_t        mVisible;                                        // +0x00
    uint8_t        pad01[3];
    IRefV08*       mpRef;                                           // +0x04
    uint8_t        pad08[0x38 - 0x08];
    cGonzagoTimerLike mTimerA;                                      // +0x38
    cGonzagoTimerLike mTimerB;                                      // +0x58
    cTimerBarHost* Initialize();
    void Terminate();
};

// @ 0x00d2ba60
cTimerBarHost* cTimerBarHost::Initialize()
{
    mVisible = 1;
    mpRef = 0;
    mTimerA.ResetTimer();
    mTimerB.ResetTimer();
    return this;
}

// @ 0x00d2ba90
void cTimerBarHost::Terminate()
{
    mTimerB.ShutdownTimer();
    mTimerA.ShutdownTimer();
    IRefV08* pRef = mpRef;
    if (pRef)
        pRef->Release();
}

struct PosseItem {
    void* mpObject;
    void* mpWindow;
};

struct PosseItemVec {
    PosseItem* mpBegin;                                             // +0xa4
    PosseItem* mpEnd;                                               // +0xa8
    uint32_t Size() const { return (uint32_t)(mpEnd - mpBegin); }
};

struct cSPUIPosse {
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual void V32(); virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36(); virtual void V37(); virtual void V38(); virtual void V39();
    virtual void V40();
    virtual void AddItem(void* pItem);                              // +0xa4
    virtual void RemoveItem(void* pItem, bool animate);             // +0xa8
    virtual void V43(); virtual void V44(); virtual void V45(); virtual void V46();
    virtual void V47();
    virtual void SetSelectedItem(void* pItem);                      // +0xc0
    uint8_t  pad00[0xa4 - 4];
    PosseItemVec mItems;                                            // +0xa4
    void* FindItem(void* pKey);                                     // 0x00e24c90
};

struct cCreatureDisplayStrategyB {
    uint8_t      pad00[0x5c];
    cSPUIPosse*  mpPosse;                                           // +0x5c
    void RemoveUIForPosseMember(void* pMember);
};

// @ 0x00d2b8f0
void cCreatureDisplayStrategyB::RemoveUIForPosseMember(void* pMember)
{
    if (!mpPosse)
        return;
    void* pItem = mpPosse->FindItem(pMember);
    if (!pItem)
        return;
    mpPosse->RemoveItem(pItem, true);
    if (mpPosse->mItems.Size() != 0)
        return;
    mpPosse->SetSelectedItem(0);
}

struct cSPUILayoutBar {
    virtual void V00(); virtual void V04();
    virtual void Release();                                         // +0x08
    void Shutdown(int a);                                           // 0x00811ad0
    cUIWindow* FindWindowByIDPair(uint32_t id, int a);              // 0x008105b0
};
struct cCreatureTimerBar {
    uint8_t  mVisible;                                              // +0x00
    uint8_t  pad01[3];
    cSPUILayoutBar* mpLayout;                                       // +0x04
    void Shutdown();
    void SetVisibility(bool visible);
};

// @ 0x00d2bc60
void cCreatureTimerBar::Shutdown()
{
    if (mpLayout)
        mpLayout->Shutdown(1);
    cSPUILayoutBar* pLayout = mpLayout;
    if (pLayout)
    {
        mpLayout = 0;
        pLayout->Release();
    }
}

// @ 0x00d2bc90
void cCreatureTimerBar::SetVisibility(bool visible)
{
    mVisible = visible;
    if (!visible)
    {
        mpLayout->FindWindowByIDPair(0x738ff863u, 1)->SetSelected(true, false);
        mpLayout->FindWindowByIDPair(0x738ff864u, 1)->SetSelected(true, false);
        mpLayout->FindWindowByIDPair(0x738ff865u, 1)->SetSelected(true, false);
    }
}

struct IToggleWindow {
    virtual void V00(); virtual void V04();
    virtual void Show(int animate);                                 // +0x08
    virtual void Hide(int animate);                                 // +0x0c
    virtual bool IsVisible();                                       // +0x10
};
struct cTriggerMgrState {
    uint8_t pad00[0x2c];
    int32_t mState;                                                 // +0x2c
};
cTriggerMgrState* GetTriggerMgr();                                  // 0x00b3d4d0
bool FUN_00809970();                                                // 0x00809970

struct cTimerVisTarget {
    uint8_t  pad00[0x5a8];
    cSimBlob mSim;                                                  // +0x5a8
    uint8_t  pad5c8[0xb5e - 0x5c8];
    uint8_t  mSuppressed;                                           // +0xb5e
};

struct cCreatureDisplayStrategyC {
    uint8_t   pad00[0x188];
    IToggleWindow* mpTimerA;                                        // +0x188
    IToggleWindow* mpTimerB;                                        // +0x18c
    void UpdateTimerVisibility(cTimerVisTarget* pTarget);
};

extern const float kTimerRatioScale;                                // 0x01687a00
extern const float kTimerRatioMid;                                  // 0x01687a0c
extern const float kTimerRatioHigh;                                 // 0x01687a10

// @ 0x00d2b720
void cCreatureDisplayStrategyC::UpdateTimerVisibility(cTimerVisTarget* pTarget)
{
    if (pTarget->mSuppressed == 0)
    {
        cTriggerMgrState* pTrig = GetTriggerMgr();
        if (pTrig->mState != 1 && pTrig->mState != 2 && !FUN_00809970())
        {
            cSimBlob* pSim = &pTarget->mSim;
            if (pSim->NodeRatio() * kTimerRatioScale < kTimerRatioHigh)
            {
                if (mpTimerA->IsVisible())
                    mpTimerA->Hide(0);
                if (!mpTimerB->IsVisible())
                    mpTimerB->Show(0);
            }
            else if (pSim->NodeRatio() * kTimerRatioScale < kTimerRatioMid)
            {
                if (!mpTimerA->IsVisible())
                    mpTimerA->Show(0);
                if (mpTimerB->IsVisible())
                    mpTimerB->Hide(0);
            }
            else
            {
                if (mpTimerA->IsVisible())
                    mpTimerA->Hide(0);
                if (mpTimerB->IsVisible())
                    mpTimerB->Hide(0);
            }
            return;
        }
    }
    if (mpTimerA->IsVisible())
        mpTimerA->Hide(0);
    if (mpTimerB->IsVisible())
        mpTimerB->Hide(0);
}

struct cItemRange {
    void** mpBegin;                                                 // +0x00
    void** mpEnd;                                                   // +0x04
};
struct cNounManagerItems {
    cItemRange* GetItemIDRange();                                   // 0x00b1f9c0
};

struct cPosseItem {
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29(); virtual void V30(); virtual void V31();
    virtual void SetGhostState(int state, float ratio, int a, int b);   // +0x80
    cPosseItem* Init(uint32_t layoutId);                            // 0x00e25ad0
};

struct cPosseMemberObj {
    uint8_t  pad00[0x5a8];
    cSimBlob mSim;                                                  // +0x5a8
};

void*  FUN_009512c0();                                              // 0x009512c0
void*  FUN_009512d0(int size, int align, const char* pName, void* pAlloc);   // 0x009512d0
extern const char kPosseItemGhostShell[];                           // 0x0147a458
extern const float kPosseItemRatioScale;                            // 0x013ec4d0

struct cCreatureDisplayStrategyE {
    uint8_t      pad00[0x5c];
    cSPUIPosse*  mpPosse;                                           // +0x5c
    void UpdatePosseItemGhosts();
};
struct cPosseSimulatorCounts {
    static cPosseSimulator* Instance();                             // 0x00d539d0
};
int32_t FUN_00d52e10();                                             // member of the posse simulator

// @ 0x00d2b950
void cCreatureDisplayStrategyE::UpdatePosseItemGhosts()
{
    if (!mpPosse)
        return;

    cItemRange* pRange = ((cNounManagerItems*)GetNounManagerTerrain())->GetItemIDRange();
    void** it = pRange->mpBegin;
    void** end = pRange->mpEnd;
    if (it != end)
    {
        do
        {
            cPosseMemberObj* pMember = (cPosseMemberObj*)*it;
            cPosseItem* pItem = (cPosseItem*)mpPosse->FindItem(pMember);
            if (pItem)
                pItem->SetGhostState(0x3d99162, pMember->mSim.NodeRatio() * kPosseItemRatioScale, 1, 1);
            ++it;
        } while (it != end);
    }

    if (mpPosse->mItems.Size() >= cPosseSimulator::Instance()->GetMemberCount())
        return;

    void* pMem = FUN_009512d0(0x14c, 4, kPosseItemGhostShell, FUN_009512c0());
    cPosseItem* pNew = pMem ? ((cPosseItem*)pMem)->Init(0x15a5538u) : 0;
    mpPosse->AddItem(pNew);
    mpPosse->SetSelectedItem((void*)1);
}

struct Vec4 {
    float x, y, z, w;
};

// Placement rectangle handed to cUIWindow::SetRect; retail builds five floats here.
struct cTimerBarPlacement {
    float mHeight;                                                  // +0x00
    float mOffset;                                                  // +0x04
    float mLeft;                                                    // +0x08
    float mBottom;                                                  // +0x0c
    float mRight;                                                   // +0x10
};
void* FUN_00f473a0(int size, const char* pTag, int a, int b, int c, int d);  // 0x00f473a0
Vec4* SPUIHelpers_GetMainWindowArea(Vec4* pOut);                     // 0x00805ea0
extern const float kTimerBarAreaScale;                               // 0x01471064

struct cSPUILayoutFull {
    virtual void V00();
    virtual void AddRef();                                          // +0x04
    virtual void Release();                                         // +0x08
    virtual void V03(); virtual void V04(); virtual void V05(); virtual void V06();
    virtual void V07(); virtual void V08(); virtual void V09(); virtual void V10();
    virtual void V11(); virtual void V12();
    virtual Vec4* GetRect();                                        // +0x34
    virtual void V14(); virtual void V15(); virtual void V16(); virtual void V17();
    virtual void V18(); virtual void V19(); virtual void V20(); virtual void V21();
    virtual void V22(); virtual void V23();
    virtual void SetRect(Vec4* pRect);                              // +0x60
    cSPUILayoutFull* ctor();                                        // 0x00810000
    bool Init(const wchar_t* pName, uint32_t a, int b, uint32_t c); // 0x00812160
    cUIWindow* FindWindowByIDPair(uint32_t id, int a);              // 0x008105b0
};

struct cTimerBarFull {
    uint8_t          mVisible;                                      // +0x00
    uint8_t          pad01[3];
    cSPUILayoutFull* mpLayout;                                      // +0x04
    Vec4             mRectA;                                        // +0x08
    Vec4             mRectB;                                        // +0x18
    Vec4             mRectC;                                        // +0x28
    void Init();
};

static inline void CopyRect(Vec4& dst, const Vec4* src)
{
    dst.x = src->x;
    dst.y = src->y;
    dst.z = src->z;
    dst.w = src->w;
}

// @ 0x00d2bac0
void cTimerBarFull::Init()
{
    if (mpLayout)
        return;

    void* pMem = FUN_00f473a0(0x18, "Simulator", 0, 0, 0, 0);
    cSPUILayoutFull* pNew = pMem ? ((cSPUILayoutFull*)pMem)->ctor() : 0;
    cSPUILayoutFull* pOld = mpLayout;
    if (pNew != pOld)
    {
        if (pNew)
            pNew->AddRef();
        mpLayout = pNew;
        if (pOld)
            pOld->Release();
    }

    mpLayout->Init(L"CreatureTimerBar", 0x40464100u, 1, 0x5b598fau);

    cUIWindow* pWin = mpLayout->FindWindowByIDPair(0x33a11d87u, 1);
    Vec4* pRect = pWin->GetRect();
    float height = pRect->z - pRect->x;
    Vec4 placement;
    placement.x = height;
    Vec4 area;
    SPUIHelpers_GetMainWindowArea(&area);
    placement.y = (area.z - area.x) * kTimerBarAreaScale - height * kTimerBarAreaScale;
    placement.z = pRect->y;
    placement.w = placement.y + height;
    pWin->SetRect(&placement);

    CopyRect(mRectA, mpLayout->FindWindowByIDPair(0x938ff6d1u, 1)->GetRect());
    CopyRect(mRectB, mpLayout->FindWindowByIDPair(0x938ff6d2u, 1)->GetRect());
    CopyRect(mRectC, mpLayout->FindWindowByIDPair(0x938ff6d3u, 1)->GetRect());
}
