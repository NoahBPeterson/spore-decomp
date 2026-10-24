// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00ddf990.
//
// The interface transition / fade controller: object lifetime, the global
// transition defaults, the matrix push used by the renderer and the timed
// fade ramps that drive the message-driven interface.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long long uint64_t;
typedef int int32_t;
typedef int intptr_t;
#define nullptr 0

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

class IRefCounted {
public:
    virtual void AddRef();
    virtual void Release();
    virtual void v08();
    virtual void* Query(const void* pType);
    virtual void v10();
};

struct cMethodTable {
    void* mSlots[0x40];
};

// A renderable / message driven object with an indirect dispatch table.
struct cDispatchObject {
    cMethodTable* mpMethods;                    // 0x00

    void* Call(int nSlot) {
        return ((void* (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    void* Call(int nSlot, uint32_t nArg1) {
        return ((void* (*)(void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1);
    }
    void* Call(int nSlot, uint32_t nArg1, uint32_t nArg2) {
        return ((void* (*)(void*, uint32_t, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1, nArg2);
    }
    void* Call(int nSlot, void* pArg1) {
        return ((void* (*)(void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1);
    }
    void* Call(int nSlot, void* pArg1, int nArg2) {
        return ((void* (*)(void*, void*, int))mpMethods->mSlots[nSlot >> 2])(this, pArg1, nArg2);
    }
};

class cInterfaceState {
public:
    cInterfaceState(cDispatchObject* pTarget);
    ~cInterfaceState();
    bool ResetDefaults();
    void PushMatrix(uint32_t nKey);
    void UpdateTransition(unsigned int nElapsed, uint32_t nFlags);
    void UpdateFade(float fDelta);
    void UpdateSequence(int nDelta);
    void UpdateAlpha(int nDelta);
    void BeginSequence(uint8_t bFirst, uint8_t bSecond);
    void ResetSequence();
    void NotifySequence();
    bool IsIdle();

    uint32_t mpVftable;                         // 0x00
    int mnTimer;                                // 0x04
    uint8_t mPad08[0x18];                       // 0x08
    float mfValue20;                            // 0x20
    float mfValue24;                            // 0x24
    float mfValue28;                            // 0x28
    float mfValue2c;                            // 0x2c
    float mfValue30;                            // 0x30
    float mfTolerance;                          // 0x34
    float mfStart38;                            // 0x38
    float mfStart3c;                            // 0x3c
    uint8_t mbFlag40;                           // 0x40
    uint8_t mPad41[0x03];                       // 0x41
    float mfTo44;                               // 0x44
    float mfTo48;                               // 0x48
    float mfTo4c;                               // 0x4c
    float mfFrom50;                             // 0x50
    float mfFrom54;                             // 0x54
};

struct cInterfaceDefaults {
    float mfUnknown00;                          // 0x00
    float mfUnknown04;                          // 0x04
    float mfX;                                  // 0x08
    float mfY;                                  // 0x0c
    float mfZ;                                  // 0x10
};

extern cDispatchObject* gInterfaceNotifier;
extern cInterfaceDefaults gInterfaceFrom;
extern float gInterfaceValue;
extern float gInterfaceBlend;
extern float gInterfaceAngle;
extern float gInterfaceAlpha;
extern float gInterfaceTargetX;
extern float gInterfaceTargetY;
extern float gInterfaceTargetZ;
extern float gInterfaceStep;
extern float gInterfaceSpeed;
extern uint32_t gInterfaceTimer;
extern uint8_t gInterfaceStarted;
extern Vec3 gInterfaceCameraA;
extern Vec3 gInterfaceCameraB;
extern uint8_t gInterfaceVtable[0x40];

void* MessageServer();
float FastSin(float fAngle);
void SetCameraPitch(float fPitch);
void SetCameraYaw(float fYaw);
void SetCameraRoll(float fRoll);
void SetCameraTransform(const float* pMatrix);
void SetCameraFov(float fFov);
void ResetCameraNotifier(uint32_t nMode);
void ApplyInterfaceMatrix(const float* pMatrix);
void InterpolateGlobals(float fAlpha);
void PostInterfaceMessage(uint32_t nId, int nValue);
int RoundToInt(float fValue);

// ---------------------------------------------------------------------------
// 0x00ddf990  cInterfaceState::cInterfaceState
// ---------------------------------------------------------------------------
// @ 0x00ddf990
cInterfaceState::cInterfaceState(cDispatchObject* pTarget)
{
    mpVftable = 0;
    mnTimer = 0;
    mfValue20 = 1.0f;
    mfValue24 = 0.0f;
    mfValue28 = 0.0f;
    mfValue2c = -1.0f;
    mfValue30 = -1.0f;
    mfTolerance = 0.0f;
    mfStart38 = -1.0f;
    mfStart3c = -1.0f;
    mfTo44 = 0.001f;
    mfTo48 = 20.0f;
    mfTo4c = 0.0f;
    mfFrom50 = 0.0f;
    mfFrom54 = 0.0f;
    mbFlag40 = 0;

    (void)pTarget;

    gInterfaceSpeed = 0.01f;
    gInterfaceFrom.mfX = 0.0f;
    gInterfaceFrom.mfY = 0.0f;
    gInterfaceFrom.mfZ = 0.0f;
    gInterfaceValue = 0.0f;
    gInterfaceBlend = 0.0f;
    gInterfaceAngle = 0.0f;
    gInterfaceTimer = 20;

    if (gInterfaceNotifier != nullptr)
        ResetCameraNotifier(0);
}

// ---------------------------------------------------------------------------
// 0x00ddfaa0  cInterfaceState::~cInterfaceState
// ---------------------------------------------------------------------------
// @ 0x00ddfaa0
cInterfaceState::~cInterfaceState()
{
    if (gInterfaceNotifier != nullptr)
        gInterfaceNotifier->Call(0x04);
}

// ---------------------------------------------------------------------------
// 0x00ddfaf0  cInterfaceState::ResetDefaults
// ---------------------------------------------------------------------------
// @ 0x00ddfaf0
bool cInterfaceState::ResetDefaults()
{
    Vec3 position;
    position.mX = 0.0f;
    position.mY = 0.0f;
    position.mZ = -100.0f;
    gInterfaceCameraA = position;
    gInterfaceCameraB = position;
    gInterfaceNotifier = (cDispatchObject*)&gInterfaceVtable[0];
    return false;
}

// ---------------------------------------------------------------------------
// 0x00ddfb50  cInterfaceState::PushMatrix
// ---------------------------------------------------------------------------
// @ 0x00ddfb50
void cInterfaceState::PushMatrix(uint32_t nKey)
{
    float matrix[9];
    matrix[0] = gInterfaceFrom.mfX;
    matrix[1] = gInterfaceFrom.mfY;
    matrix[2] = gInterfaceFrom.mfZ;
    matrix[3] = gInterfaceValue;
    matrix[4] = gInterfaceBlend;
    matrix[5] = gInterfaceAngle;
    matrix[6] = gInterfaceSpeed;
    matrix[7] = 0.0f;
    matrix[8] = 1.0f;

    if (gInterfaceNotifier != nullptr)
        gInterfaceNotifier->Call(0x04, (void*)matrix);

    gInterfaceStarted = 0;
    (void)nKey;
}

// ---------------------------------------------------------------------------
// 0x00ddfbe0  cInterfaceState::UpdateTransition
// ---------------------------------------------------------------------------
// @ 0x00ddfbe0
void cInterfaceState::UpdateTransition(unsigned int nElapsed, uint32_t nFlags)
{
    if (gInterfaceNotifier != nullptr)
        gInterfaceNotifier->Call(0x00, nElapsed, nFlags);

    float fTime = (float)nElapsed;
    mfValue20 = ((gInterfaceTargetX - mfValue20) * fTime) * 0.001f + mfValue20;
    mfValue24 = ((gInterfaceAngle - mfValue24) * fTime) * 0.01f + mfValue24;

    if (mbFlag40 != 0) {
        gInterfaceAlpha = ((gInterfaceTargetX - mfValue20) * gInterfaceSpeed) * 0.0025f;
        gInterfaceTargetZ = -(((gInterfaceAngle - mfValue24) * gInterfaceStep) * 0.0025f);
    }

    cDispatchObject* pAudio = (cDispatchObject*)MessageServer();
    if (pAudio != nullptr) {
        pAudio->Call(0x38, 0x3cdd1a9);
        pAudio->Call(0x40, 0x34753a7, 0x6f62c88d);
        pAudio->Call(0x3c, 0x34753aa);
        pAudio->Call(0x58);
    }

    if (0.0f < mfValue28)
        SetCameraPitch(mfValue28 * 57.29578f);
    if (0.0f < mfStart38)
        SetCameraYaw(mfStart38);
    if (0.0f < mfStart3c)
        SetCameraRoll(mfStart3c);

    if (gInterfaceNotifier != nullptr)
        gInterfaceNotifier->Call(0x04, (void*)&mfTo44);
    SetCameraTransform(&mfTo44);

    float fCurrent = mfValue28;
    if (fCurrent == -1.0f && 0.0f < mfValue2c) {
        mfValue28 = mfValue2c;
        return;
    }
    if (mfValue2c == -1.0f && 0.0f < fCurrent) {
        mfValue2c = fCurrent;
        return;
    }
    float fDelta = mfValue2c - mfValue28;
    if (fDelta < 0.0f)
        fDelta = -fDelta;
    if (fDelta < mfTolerance) {
        mfValue28 = mfValue2c;
        return;
    }
    mfValue28 = (mfValue2c - mfValue28) * 0.1f + mfValue28;
}

// ---------------------------------------------------------------------------
// 0x00ddfef0  cInterfaceState::UpdateFade
// ---------------------------------------------------------------------------
// @ 0x00ddfef0
void cInterfaceState::UpdateFade(float fDelta)
{
    mnTimer = mnTimer + (int)fDelta;
    float fElapsed = (float)mnTimer;
    if (mnTimer < 0)
        fElapsed = fElapsed + 4294967296.0f;
    float fDuration = gInterfaceSpeed + gInterfaceSpeed;
    fElapsed = fElapsed / (fDuration * 1000.0f);

    if (mfTo4c == 0.0f || mfFrom50 == 0.0f) {
        if (1.0f < fElapsed) {
            PostInterfaceMessage(0x625e26a, 1);
            if (mfTo4c == 0.0f)
                mfTo4c = 1.0f;
            else
                gInterfaceStarted = 0;
            fElapsed = 1.0f;
        }
        if (mfFrom50 == 0.0f)
            fElapsed = 1.0f - fElapsed;

        float fBlend = fElapsed;
        InterpolateGlobals(fElapsed);
        mfValue28 = (mfValue2c - mfValue24) * fBlend + mfValue24;
        mfValue20 = (-0.43633232f - mfValue2c) * fBlend + mfValue2c;
        mfTolerance = mfFrom54 + (mfTo44 - mfFrom54) * fBlend;
        mfStart38 = mfValue30 + (mfTo48 - mfValue30) * fBlend;
        mfStart3c = mfValue2c + (mfTo4c - mfValue2c) * fBlend;
        gInterfaceTargetX = mfValue20;
        gInterfaceTargetY = mfValue30;
        gInterfaceTargetZ = mfValue28;
    }
}

// ---------------------------------------------------------------------------
// 0x00de00e0  cInterfaceState::UpdateSequence
// ---------------------------------------------------------------------------
// @ 0x00de00e0
void cInterfaceState::UpdateSequence(int nDelta)
{
    mnTimer = mnTimer + nDelta;
    float fElapsed = (float)mnTimer;
    if (mnTimer < 0)
        fElapsed = fElapsed + 4294967296.0f;
    float fDuration = gInterfaceStep + gInterfaceStep;
    fElapsed = fElapsed / (fDuration * 1000.0f);

    if (mfValue24 == 0.0f && 1.0f < fElapsed) {
        mfValue24 = 1.0f;
        PostInterfaceMessage(0x7be7df5, 2);
        fElapsed = 1.0f;
    }
    if (mfValue24 == 1.0f)
        fElapsed = 1.0f;
    if (mfValue24 == 2.0f) {
        if (1.0f < fElapsed) {
            PostInterfaceMessage(0x7be7df5, 4);
            gInterfaceStarted = 0;
            fElapsed = 1.0f;
        }
        fElapsed = 1.0f - fElapsed;
    }

    float fScaled = fElapsed * 2.0f;
    float fCurve;
    if (1.0f <= fScaled) {
        float fInverse = (2.0f - fScaled) * gInterfaceStep;
        fCurve = 1.0f - (fInverse * (gInterfaceStep * fInverse)) * 0.5f;
    } else {
        float fInverse = gInterfaceStep * fScaled;
        fCurve = (fInverse * (gInterfaceStep * fInverse)) * 0.5f;
    }

    if (mfValue24 == 2.0f) {
        if (gInterfaceBlend <= 1.0f - fCurve) {
            if (mbFlag40 == 0) {
                mbFlag40 = 1;
                PostInterfaceMessage(0x7be7df5, 5);
            }
        } else {
            mbFlag40 = 0;
        }
    }
    if (mfValue24 == 0.0f) {
        if (gInterfaceBlend <= fCurve) {
            if (mbFlag40 == 0) {
                mbFlag40 = 1;
                PostInterfaceMessage(0x7be7df5, 1);
            }
        } else {
            mbFlag40 = 0;
        }
    }

    if (mfValue24 != 1.0f) {
        float fRamp = fCurve * 3.0f;
        if (fRamp <= 0.0f)
            fRamp = 0.0f;
        if (1.0f <= fRamp)
            fRamp = 1.0f;
        mfValue20 = (mfValue28 - mfValue24) * fCurve + mfValue24;
        mfValue30 = (-gInterfaceAlpha - mfTolerance) * fRamp + mfTolerance;
        mfStart38 = (1.0f - fCurve) * mfValue30;
    }
}

// ---------------------------------------------------------------------------
// 0x00de0450  cInterfaceState::UpdateAlpha
// ---------------------------------------------------------------------------
// @ 0x00de0450
void cInterfaceState::UpdateAlpha(int nDelta)
{
    mnTimer = mnTimer + nDelta;
    float fElapsed = (float)mnTimer;
    if (mnTimer < 0)
        fElapsed = fElapsed + 4294967296.0f;
    float fDuration = gInterfaceSpeed + gInterfaceSpeed;
    fElapsed = fElapsed / (fDuration * 1000.0f);

    if (mfValue24 == 0.0f && 1.0f < fElapsed) {
        mfValue24 = 1.0f;
        PostInterfaceMessage(0x7c3cd3d, 2);
        fElapsed = 1.0f;
    }
    if (mfValue24 == 1.0f)
        fElapsed = 1.0f;
    if (mfValue24 == 2.0f) {
        if (1.0f < fElapsed) {
            PostInterfaceMessage(0x7c3cd3d, 4);
            gInterfaceStarted = 0;
            fElapsed = 1.0f;
        }
        fElapsed = 1.0f - fElapsed;
    }

    float fScaled = fElapsed * 2.0f;
    float fCurve;
    if (1.0f <= fScaled) {
        float fInverse = (2.0f - fScaled) * gInterfaceSpeed;
        fCurve = 1.0f - (fInverse * (gInterfaceSpeed * fInverse)) * 0.5f;
    } else {
        float fInverse = gInterfaceSpeed * fScaled;
        fCurve = (fInverse * (gInterfaceSpeed * fInverse)) * 0.5f;
    }

    mfValue20 = (mfValue28 - mfValue24) * fCurve + mfValue24;
    mfValue30 = (gInterfaceAlpha - mfTolerance) * fCurve + mfTolerance;
    mfStart38 = (mfValue2c - mfValue30) * fCurve + mfValue30;
}

// ---------------------------------------------------------------------------
// 0x00de0670  cInterfaceState::BeginSequence
// ---------------------------------------------------------------------------
// @ 0x00de0670
void cInterfaceState::BeginSequence(uint8_t bFirst, uint8_t bSecond)
{
    if (bSecond != 0) {
        gInterfaceTimer = (uint32_t)RoundToInt((gInterfaceStep + gInterfaceStep) * 1000.0f);
        return;
    }

    gInterfaceTargetX = gInterfaceTargetY;
    gInterfaceTargetY = gInterfaceTargetY;
    gInterfaceTargetZ = gInterfaceTargetY;
    gInterfaceFrom.mfX = gInterfaceTargetX;
    gInterfaceFrom.mfY = gInterfaceTargetX;
    gInterfaceFrom.mfZ = (bFirst != 0) ? 1.0f : 2.0f;
    gInterfaceValue = gInterfaceTargetZ;
    gInterfaceTimer = 0;
    gInterfaceSpeed = gInterfaceStep;

    PostInterfaceMessage(0x7c3cd3d, (bFirst != 0) ? 1.0f : 2.0f);
    gInterfaceStarted = 0;
}

// ---------------------------------------------------------------------------
// 0x00de07a0  cInterfaceState::ResetSequence
// ---------------------------------------------------------------------------
// @ 0x00de07a0
void cInterfaceState::ResetSequence()
{
    gInterfaceAlpha = 0.0f;
    gInterfaceStep = 0.0f;
    gInterfaceValue = gInterfaceTargetY;
    gInterfaceBlend = gInterfaceTargetY;
    if (gInterfaceTargetY < gInterfaceAlpha || gInterfaceTargetX + gInterfaceAlpha < gInterfaceTargetY)
        gInterfaceAngle = gInterfaceTargetX;
    else
        gInterfaceAngle = 0.0f;
    gInterfaceTargetZ = gInterfaceTargetX;
    gInterfaceFrom.mfX = gInterfaceTargetX;
    gInterfaceSpeed = 0.0f;
    gInterfaceFrom.mfZ = gInterfaceTargetZ;
    gInterfaceStarted = 0;

    PostInterfaceMessage(0x7be7df5, 0);
}

// ---------------------------------------------------------------------------
// 0x00de0890  cInterfaceState::NotifySequence
// ---------------------------------------------------------------------------
// @ 0x00de0890
void cInterfaceState::NotifySequence()
{
    gInterfaceSpeed = 2.0f;
    gInterfaceStep = 0.0f;
    PostInterfaceMessage(0x7be7df5, 3);
}

// ---------------------------------------------------------------------------
// 0x00de0900  cInterfaceState::IsIdle
// ---------------------------------------------------------------------------
// @ 0x00de0900
bool cInterfaceState::IsIdle()
{
    return *(uint8_t*)((uint8_t*)&mnTimer) == 0;
}
