// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00c0eae0.
//
// Creature steering / target selection plus the combatant ring the creature
// keeps at the end of its object (0xe40..0xe44).

typedef unsigned int size_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef int intptr_t;
#define nullptr 0

float sqrtf(float fValue);
#define __builtin_sqrtf sqrtf

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

class IRefCounted {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);   // 0x0c
    virtual void v10();
    virtual uint32_t GetPoliticalID();        // 0x14
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58(int a, int b, int c, int d);
    virtual void* QueryTarget(const void* pType);   // 0x5c
};

class cSpatialObject {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual Vec3* GetPosition();          // 0x2c
    virtual Vec3* GetDirection();         // 0x30
    virtual bool IsVisible();             // 0x58
};

class cGameData : public IRefCounted {
public:
    uint8_t mPad60[0x1c];
};

class cCombatant : public cGameData {
public:
    uint8_t mPad7c[0x20];
};

class AnimatedCreature {
public:
    uint8_t mPad00[0x88];           // 0x00
    uint32_t mFlags;                // 0x88
    uint8_t mPad8c[0xc8];           // 0x8c
    uint32_t mState;                // 0x154
    Vec3 mOrientation;              // 0x158
    Vec3 mPosition;                 // 0x164
    uint8_t mPad170[0x10];
};

// 0x24-byte combatant slot: key, secondary key and the combatant pointer.
struct cCombatantSlot {
    int mKey;                       // 0x00
    int mSecondaryKey;              // 0x04
    uint8_t mPad08[0x18];           // 0x08
    cCombatant* mpCombatant;        // 0x20
};

// Random source used by the random-slot pick.
class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(int nRange);
};
RandomLinearCongruential RandomGet();

// Shared game services.
Vec3* GetCreaturePosition(cSpatialObject* pObject);
Vec3* GetCreatureDirection(cSpatialObject* pObject);
void CreatureSteerTo(const Vec3* pPosition, const Vec3* pDirection);
void CreatureUpdateTransform(const Vec3* pPosition, int bFlag);
Vec3* RotateVectorAround(Vec3* pOut, const Vec3* pVector, const Vec3* pAxis);
bool IsVectorValid(const Vec3* pVector);
void* GetCurrentGameMode();
extern uint8_t gGameModeTribe;
extern uint8_t gGameModeCity;
void CreatureAddRelation(cCombatant* pTarget);
uint32_t GetOwnPoliticalID(cSpatialObject* pObject);
void CreaturePlayAttackAnimation();
bool IsAnimationQueuedOrCurrent(void* pCreature);
void HideCreature(bool bHide);
void* MathConstantsVelocityDir();
void CreatureMoveStep(const Vec3* pDelta, int bFlag);
bool TraceTerrain(const Vec3* pFrom, const Vec3* pDirection, void* pWorld, float* pOut, int a, int b);
class cLocomotiveObject;

class Simulator_cCreatureBase : public cSpatialObject {
public:
    uint8_t mPad04[0xbc];           // 0x04
    uint8_t mLocomotiveFlags;       // 0xc0
    uint8_t mPadC1[0x76];           // 0xc1
    uint8_t mOrientationValid;      // 0x137
    uint8_t mPad138[0x9d8];         // 0x138
    uint32_t mFlags;                // 0xb10
    uint8_t mPadB14[0x04];          // 0xb14
    cCombatant* mpCombatantTarget;  // 0xb18
    int mIntentionTowardsTarget;    // 0xb1c
    void* mpSteeringModel;          // 0xb20
    uint8_t mPadB24[0x30];          // 0xb24
    AnimatedCreature* mpAnimatedCreature;   // 0xb54
    uint32_t mSteeringFlags;        // 0xb58
    uint8_t mTargetFlag;            // 0xb5c
    uint8_t mPadB5D[0x2ff];         // 0xb5d
    IRefCounted* mpSenseObject;     // 0xe5c
    uint8_t mPadE60[0x03];          // 0xe60
    uint8_t mPathValid;             // 0xe63
    uint32_t mSteeringTimer;        // 0xe64
    uint8_t mPadE68[0x14];          // 0xe68
    IRefCounted* mpSteeringTarget;  // 0xe7c
    uint8_t mPadE80[0x1c0];         // 0xe80
    cCombatantSlot* mpSlotsBegin;   // 0xe40
    cCombatantSlot* mpSlotsEnd;     // 0xe44

    void SteerTowards(const Vec3* pTarget, int nDelta);        // 0x00c0eae0
    void SetCreatureTarget(cCombatant* pTarget, bool bFlag, int nIntention);  // 0x00c0ed60
    void* GetTargetAsCreature();                                // 0x00c0ee70
    void ApplyCombatTarget();                                   // 0x00c0ee90
    void UpdateSteering(int nDelta, float fAmount);              // 0x00c0eec0
    void Hide();                                                // 0x00c0f280
    void Show();                                                // 0x00c0f2b0
    bool TraceTo(const Vec3* pFrom, const Vec3* pTo, Vec3* pOut);  // 0x00c0f2e0
    void ResetCombatants();                                     // 0x00c0f490
    bool IsSlotEmpty(uint32_t nIndex);                          // 0x00c0f510
    int CountValid();                                           // 0x00c0f570
    bool IsFull();                                              // 0x00c0f5f0
    uint32_t FindFirstEmpty();                                  // 0x00c0f620
    uint32_t FindRandomEmpty();                                 // 0x00c0f6b0
    uint32_t FindFirstValid();                                  // 0x00c0f780
    uint32_t FindNextValid(int nAfter);                         // 0x00c0f810
    cCombatant* GetAt(uint32_t nIndex);                         // 0x00c0f8a0
    uint32_t FindByCombatant(int nCombatant);                   // 0x00c0f8f0
    uint32_t FindByKey(int nKey);                               // 0x00c0f960
    cCombatantSlot* FindSlotByKey(int nKey, uint32_t* pIndex);  // 0x00c0f9b0
    cCombatantSlot* FindSlotByCombatant(int nCombatant, uint32_t* pIndex);  // 0x00c0fa10
};

// ---------------------------------------------------------------------------
// 0x00c0eae0  Simulator::cCreatureBase::SteerTowards
// ---------------------------------------------------------------------------
// @ 0x00c0eae0
void Simulator_cCreatureBase::SteerTowards(const Vec3* pTarget, int nDelta)
{
    (void)nDelta;
    Vec3* pPosition = GetPosition();
    Vec3 direction;
    direction.mX = pTarget->mX - pPosition->mX;
    direction.mY = pTarget->mY - pPosition->mY;
    direction.mZ = pTarget->mZ - pPosition->mZ;

    float fDistance = direction.mX * direction.mX + direction.mY * direction.mY +
                      direction.mZ * direction.mZ;
    fDistance = (float)__builtin_sqrtf(fDistance);

    if (fDistance <= 0.0001f) {
        Vec3 local;
        local.mX = -1.0f;
        local.mY = 0.0f;
        local.mZ = 0.0f;
        Vec3* pRotated = RotateVectorAround(&local, &local, &mpAnimatedCreature->mOrientation);
        if (!IsVectorValid(&local))
            (void)pRotated;
    } else {
        float fInv = 1.0f / fDistance;
        direction.mX *= fInv;
        direction.mY *= fInv;
        direction.mZ *= fInv;
    }

    if (mpAnimatedCreature != nullptr) {
        CreatureUpdateTransform(&direction, 1);
    }
}

// ---------------------------------------------------------------------------
// 0x00c0ed60  Simulator::cCreatureBase::SetCreatureTarget
// ---------------------------------------------------------------------------
// @ 0x00c0ed60
void Simulator_cCreatureBase::SetCreatureTarget(cCombatant* pTarget, bool bFlag, int nIntention)
{
    mTargetFlag = bFlag ? 1 : 0;
    mIntentionTowardsTarget = nIntention;

    if (mpCombatantTarget == pTarget)
        return;

    if (pTarget == nullptr) {
        if (mpCombatantTarget != nullptr) {
            IRefCounted* pOld = mpCombatantTarget;
            mpCombatantTarget = nullptr;
            pOld->Release();
        }
        if (mpAnimatedCreature != nullptr && mpAnimatedCreature->mState == 0)
            IsAnimationQueuedOrCurrent(this);
    } else {
        cCombatant* pOld = mpCombatantTarget;
        if (pTarget != pOld) {
            pTarget->AddRef();
            mpCombatantTarget = pTarget;
            if (pOld != nullptr)
                pOld->Release();
        }
    }

    if (IsVisible() && mpCombatantTarget != nullptr) {
        uint32_t nTargetPolitical = mpCombatantTarget->GetPoliticalID();
        if (nTargetPolitical != GetOwnPoliticalID(this) && GetCurrentGameMode() == &gGameModeTribe) {
            CreatureAddRelation(pTarget);
            CreaturePlayAttackAnimation();
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00c0ee70  Simulator::cCreatureBase::GetTargetAsCreature
// ---------------------------------------------------------------------------
// @ 0x00c0ee70
void* Simulator_cCreatureBase::GetTargetAsCreature()
{
    if (mpCombatantTarget != nullptr)
        return mpCombatantTarget->QueryTarget((const void*)0xce9f6639);
    return nullptr;
}

// ---------------------------------------------------------------------------
// 0x00c0ee90  Simulator::cCreatureBase::ApplyCombatTarget
// ---------------------------------------------------------------------------
// @ 0x00c0ee90
void Simulator_cCreatureBase::ApplyCombatTarget()
{
    if (mpSteeringTarget == nullptr)
        return;
    IRefCounted* pTarget = (IRefCounted*)mpSteeringTarget->Query(nullptr);
    if (pTarget == nullptr)
        return;
    if (GetCurrentGameMode() == &gGameModeCity)
        mpSteeringTarget = pTarget;
}

// ---------------------------------------------------------------------------
// 0x00c0eec0  Simulator::cCreatureBase::UpdateSteering
// ---------------------------------------------------------------------------
// @ 0x00c0eec0
void Simulator_cCreatureBase::UpdateSteering(int nDelta, float fAmount)
{
    mSteeringTimer += nDelta;

    if (fAmount == 0.0f) {
        mSteeringTimer = 0;
        mPathValid = 0;
        return;
    }

    if (mSteeringTimer > 1000u) {
        mSteeringTimer = 0;
        mPathValid = 0;
    }

    Vec3 offset;
    offset.mX = 0.0f;
    offset.mY = 0.0f;
    offset.mZ = 0.0f;

    float fScale = 1.0f;
    if ((mSteeringFlags >> 9 & 1) != 0 && mpSteeringModel != nullptr && mOrientationValid != 0) {
        Vec3* pDirection = GetDirection();
        if (pDirection->mX * pDirection->mX + pDirection->mY * pDirection->mY +
                pDirection->mZ * pDirection->mZ == 0.0f) {
            offset.mX = 0.0f;
            offset.mY = 1.0f;
        }
    }

    float fSpeed = *(float*)((uint8_t*)mpSteeringModel + 0x548);
    if (mOrientationValid == 0) {
        Vec3 velocity;
        Vec3* pDirection = GetDirection();
        float fLen = pDirection->mX * pDirection->mX + pDirection->mY * pDirection->mY +
                     pDirection->mZ * pDirection->mZ;
        float fInv = 1.0f / (float)__builtin_sqrtf(fLen + 1e-08f);
        velocity.mX = pDirection->mX * fInv;
        velocity.mY = pDirection->mY * fInv;
        velocity.mZ = pDirection->mZ * fInv;
        float fDot = velocity.mX * offset.mX + velocity.mY * offset.mY + velocity.mZ * offset.mZ;
        if (fDot < 0.0f)
            fSpeed += fDot;
    }

    Vec3* pForward = GetDirection();
    float fLen = pForward->mX * pForward->mX + pForward->mY * pForward->mY +
                 pForward->mZ * pForward->mZ;
    float fInv = 1.0f / (float)__builtin_sqrtf(fLen + 1e-08f);
    float fAmountScaled = (float)mSteeringTimer;
    offset.mX += pForward->mX * fInv * fSpeed * fAmountScaled * 0.001f * fScale;
    offset.mY += pForward->mY * fInv * fSpeed * fAmountScaled * 0.001f * fScale;
    offset.mZ += pForward->mZ * fInv * fSpeed * fAmountScaled * 0.001f * fScale;

    CreatureMoveStep(&offset, 0);
}

// ---------------------------------------------------------------------------
// 0x00c0f280  Simulator::cCreatureBase::Hide
// ---------------------------------------------------------------------------
// @ 0x00c0f280
void Simulator_cCreatureBase::Hide()
{
    if (mpAnimatedCreature != nullptr) {
        mpAnimatedCreature->mFlags &= ~1u;
        *(uint8_t*)((uint8_t*)mpAnimatedCreature + 0x64) = 0;
        HideCreature(true);
    }
}

// ---------------------------------------------------------------------------
// 0x00c0f2b0  Simulator::cCreatureBase::Show
// ---------------------------------------------------------------------------
// @ 0x00c0f2b0
void Simulator_cCreatureBase::Show()
{
    if (mpAnimatedCreature != nullptr) {
        mpAnimatedCreature->mFlags |= 1u;
        *(uint8_t*)((uint8_t*)mpAnimatedCreature + 0x64) = 1;
    }
}

// ---------------------------------------------------------------------------
// 0x00c0f2e0  Simulator::cCreatureBase::TraceTo
// ---------------------------------------------------------------------------
// @ 0x00c0f2e0
bool Simulator_cCreatureBase::TraceTo(const Vec3* pFrom, const Vec3* pTo, Vec3* pOut)
{
    Vec3 direction;
    direction.mX = pTo->mX - pFrom->mX;
    direction.mY = pTo->mY - pFrom->mY;
    direction.mZ = pTo->mZ - pFrom->mZ;

    float fLen = direction.mX * direction.mX + direction.mY * direction.mY +
                 direction.mZ * direction.mZ;
    float fInv = 1.0f / (float)__builtin_sqrtf(fLen + 1e-08f);
    direction.mX *= fInv;
    direction.mY *= fInv;
    direction.mZ *= fInv;

    Vec3 hit;
    hit.mX = 0.0f;
    hit.mY = 0.0f;
    hit.mZ = 0.0f;

    if (!TraceTerrain(pFrom, &direction, nullptr, &hit.mX, 0, 0))
        return false;

    *pOut = hit;

    float fToHit = (pFrom->mX - pOut->mX) * (pFrom->mX - pOut->mX) +
                   (pFrom->mY - pOut->mY) * (pFrom->mY - pOut->mY) +
                   (pFrom->mZ - pOut->mZ) * (pFrom->mZ - pOut->mZ);
    float fToEnd = (pFrom->mX - pTo->mX) * (pFrom->mX - pTo->mX) +
                   (pFrom->mY - pTo->mY) * (pFrom->mY - pTo->mY) +
                   (pFrom->mZ - pTo->mZ) * (pFrom->mZ - pTo->mZ);
    return __builtin_sqrtf(fToHit) <= __builtin_sqrtf(fToEnd);
}

// ---------------------------------------------------------------------------
// 0x00c0f490  Simulator::cCreatureBase::ResetCombatants
// ---------------------------------------------------------------------------
// @ 0x00c0f490
void Simulator_cCreatureBase::ResetCombatants()
{
    mIntentionTowardsTarget = 0;

    if (mpSenseObject != nullptr) {
        mpSenseObject->Query(nullptr);
        IRefCounted* pOld = mpSenseObject;
        mpSenseObject = nullptr;
        pOld->Release();
    }
    if (mpSteeringTarget != nullptr) {
        mpSteeringTarget->Query(nullptr);
        IRefCounted* pOld = mpSteeringTarget;
        mpSteeringTarget = nullptr;
        pOld->Release();
    }
    if (mpCombatantTarget != nullptr) {
        IRefCounted* pOld = mpCombatantTarget;
        mpCombatantTarget = nullptr;
        pOld->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x00c0f510  Simulator::cCreatureBase::IsSlotEmpty
// ---------------------------------------------------------------------------
// @ 0x00c0f510
bool Simulator_cCreatureBase::IsSlotEmpty(uint32_t nIndex)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    if (nCount <= nIndex)
        return true;
    if (mpSlotsBegin[nIndex].mpCombatant == nullptr && mpSlotsBegin[nIndex].mSecondaryKey == 0)
        return true;
    return false;
}

// ---------------------------------------------------------------------------
// 0x00c0f570  Simulator::cCreatureBase::CountValid
// ---------------------------------------------------------------------------
// @ 0x00c0f570
int Simulator_cCreatureBase::CountValid()
{
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    int nValid = 0;
    for (int i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant != nullptr || mpSlotsBegin[i].mSecondaryKey != 0)
            ++nValid;
    }
    return nValid;
}

// ---------------------------------------------------------------------------
// 0x00c0f5f0  Simulator::cCreatureBase::IsFull
// ---------------------------------------------------------------------------
// @ 0x00c0f5f0
bool Simulator_cCreatureBase::IsFull()
{
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    return CountValid() == nCount;
}

// ---------------------------------------------------------------------------
// 0x00c0f620  Simulator::cCreatureBase::FindFirstEmpty
// ---------------------------------------------------------------------------
// @ 0x00c0f620
uint32_t Simulator_cCreatureBase::FindFirstEmpty()
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant == nullptr && mpSlotsBegin[i].mSecondaryKey == 0)
            return i;
    }
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// 0x00c0f6b0  Simulator::cCreatureBase::FindRandomEmpty
// ---------------------------------------------------------------------------
// @ 0x00c0f6b0
uint32_t Simulator_cCreatureBase::FindRandomEmpty()
{
    int nValid = CountValid();
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    int nEmpty = nCount - nValid;
    uint32_t nPick = RandomGet().RandomUint32Uniform(nEmpty);
    int nSeen = 0;
    for (int i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant == nullptr && mpSlotsBegin[i].mSecondaryKey == 0) {
            if (nSeen == (int)nPick)
                return (uint32_t)i;
            ++nSeen;
        }
    }
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// 0x00c0f780  Simulator::cCreatureBase::FindFirstValid
// ---------------------------------------------------------------------------
// @ 0x00c0f780
uint32_t Simulator_cCreatureBase::FindFirstValid()
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant != nullptr || mpSlotsBegin[i].mSecondaryKey != 0)
            return i;
    }
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// 0x00c0f810  Simulator::cCreatureBase::FindNextValid
// ---------------------------------------------------------------------------
// @ 0x00c0f810
uint32_t Simulator_cCreatureBase::FindNextValid(int nAfter)
{
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    for (int i = nAfter + 1; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant != nullptr || mpSlotsBegin[i].mSecondaryKey != 0)
            return (uint32_t)i;
    }
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// 0x00c0f8a0  Simulator::cCreatureBase::GetAt
// ---------------------------------------------------------------------------
// @ 0x00c0f8a0
cCombatant* Simulator_cCreatureBase::GetAt(uint32_t nIndex)
{
    if (nIndex < (uint32_t)(mpSlotsEnd - mpSlotsBegin))
        return mpSlotsBegin[nIndex].mpCombatant;
    return nullptr;
}

// ---------------------------------------------------------------------------
// 0x00c0f8f0  Simulator::cCreatureBase::FindByCombatant
// ---------------------------------------------------------------------------
// @ 0x00c0f8f0
uint32_t Simulator_cCreatureBase::FindByCombatant(int nCombatant)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (nCombatant == 0)
            return 0xffffffff;
        if ((int)(intptr_t)mpSlotsBegin[i].mpCombatant == nCombatant)
            return i;
    }
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// 0x00c0f960  Simulator::cCreatureBase::FindByKey
// ---------------------------------------------------------------------------
// @ 0x00c0f960
uint32_t Simulator_cCreatureBase::FindByKey(int nKey)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mKey == nKey)
            return i;
    }
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// 0x00c0f9b0  Simulator::cCreatureBase::FindSlotByKey
// ---------------------------------------------------------------------------
// @ 0x00c0f9b0
cCombatantSlot* Simulator_cCreatureBase::FindSlotByKey(int nKey, uint32_t* pIndex)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mKey == nKey) {
            if (pIndex != nullptr)
                *pIndex = i;
            return &mpSlotsBegin[i];
        }
    }
    return nullptr;
}

// ---------------------------------------------------------------------------
// 0x00c0fa10  Simulator::cCreatureBase::FindSlotByCombatant
// ---------------------------------------------------------------------------
// @ 0x00c0fa10
cCombatantSlot* Simulator_cCreatureBase::FindSlotByCombatant(int nCombatant, uint32_t* pIndex)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if ((int)(intptr_t)mpSlotsBegin[i].mpCombatant == nCombatant) {
            if (pIndex != nullptr)
                *pIndex = i;
            return &mpSlotsBegin[i];
        }
    }
    return nullptr;
}
