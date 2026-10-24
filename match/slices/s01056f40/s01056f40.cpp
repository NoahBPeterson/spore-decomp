// s01056f40 -- the space-stage tool strategies: the four weapon StartTool
// overrides (default projectile, turret defense missile, turret flak, drag-input
// projectile) and the place-object CanUseTool gate.
//
//   0x01056f40 cSPDefaultProjectileWeapon::StartTool
//   0x01057210 cSPTurretDefenseMissileWeapon::StartTool
//   0x01057460 cSPTurretFlakWeapon::StartTool
//   0x01057990 cSPDragInputProjectileToolStrategy::StartTool
//   0x01057bd0 cSPPlaceObjectToolStrategy::CanUseTool
//
// All five enter with three stack arguments and no live `this` in ecx: the
// strategy object itself is the first argument (the caller duplicates it into
// ecx only for the member calls it makes), so they are modelled as plain
// __stdcall functions and the object is threaded through explicitly.
#include "types.h"
#include <math.h>
#include <string.h>

#define nullptr 0

// ---------------------------------------------------------------------------
// engine objects
// ---------------------------------------------------------------------------

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Matrix3Rows {
    float m[9];
};

// one transform message: two tagged sub-records, the position, a scale and the
// row-major basis that follows them.
class XformMsg {
public:
    XformMsg();                 // 0x00434040

    uint16_t mFlags;            // +0x00
    uint16_t mCount;            // +0x02
    Vector3 mPosition;          // +0x04
    uint16_t mBasisFlags;       // +0x0c
    uint16_t mBasisCount;       // +0x0e
    float mScale;               // +0x10
    uint8_t mPad11[0x0b];       // +0x11
    Matrix3Rows mBasis;         // +0x20
};

class IEffect;

// the handle an effects manager hands back: the factory that fills an effect
// slot, then releases the previous handle.
class IEffectHandle {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void Release();                                         // +0x04
    virtual bool Create(uint32_t nType, int32_t nFlags, IEffect** ppEffect);   // +0x08
};

class IEffect {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void Release();                                         // +0x04
    virtual void Detach(int32_t nValue);                            // +0x08
    virtual void* Slot0c(void* pOut);                               // +0x0c
    virtual Vector3* Slot10(void* pOut);                            // +0x10
    virtual void* Slot14();                                         // +0x14
    virtual void Send(XformMsg* pMsg);                              // +0x18
    virtual void Slot44(int32_t nType, void* pValue, int32_t nFlags);   // +0x44
};

// every noun the star-stage makes: the slot numbers are the byte offsets.
class cSPNoun {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void Release();                                         // +0x04
    virtual bool Slot08();                                          // +0x08
    virtual void* Slot0c(uint32_t nNounId);                         // +0x0c
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
    virtual void* Slot24();
    virtual void* Slot28();
    virtual Vector3* GetPosition();                                 // +0x2c
    virtual Vector3* Slot30(Vector3* pOut);
    virtual void* Slot34();
    virtual void Slot38(void* pOut);                                // +0x38
    virtual void* Slot3c();
    virtual void* Slot40();
    virtual void* Slot44();
    virtual void Slot48(void* pOwner);                              // +0x48
    virtual void* Slot4c();                                         // +0x4c
    virtual void* Slot50();
    virtual void Slot54(void* pOwner);                              // +0x54
    virtual void* Slot58();
    virtual void* Slot5c(uint32_t nConfig);                         // +0x5c
    virtual void* Slot60();
};

// the aimer that lives at +0x114 of every weapon strategy
class cSPAimObject {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void* Slot04();
    virtual void* Slot08();
    virtual void* Slot0c();
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
    virtual void* Slot24();
    virtual void* Slot28();
    virtual Vector3* GetPosition();                                 // +0x2c
    virtual Vector3* GetTransform(Vector3* pOut);                   // +0x30
    virtual float GetScalar();                                      // +0x34
    virtual void* Slot38();
    virtual void* Slot3c();
    virtual void* Slot40();
    virtual void Slot44();
    virtual void* Slot48();
    virtual void* Slot4c();
    virtual void* Slot50();
    virtual void* Slot54();
    virtual void* Slot58();
    virtual void* Slot5c(uint32_t nConfig);                         // +0x5c
    virtual void* Slot60();
    virtual void* Slot64();
    virtual void* Slot68();
    virtual void* Slot6c();
    virtual float Slot70();                                         // +0x70
    virtual void* Slot74();
    virtual void* Slot78();
    virtual void* Slot7c();
    virtual void* Slot80();
    virtual void* Slot84();
    virtual void* Slot88();
    virtual void* Slot8c();
    virtual void* Slot90();
    virtual void* Slot94();
    virtual void* Slot98();
    virtual void* Slot9c();
    virtual void* SlotA0();
    virtual void* SlotA4();
    virtual void* SlotA8();
    virtual void* SlotAc();
    virtual void* SlotB0();
    virtual void* SlotB4();
    virtual void* Slotb8(const void* pName);                        // +0xb8
};

// the weapon strategy itself (the first argument of every function here)
class cSPToolStrategy {
public:
    uint8_t mPad000[0x114];     // +0x000
    cSPAimObject* mpAimer;      // +0x114
    cSPAimObject* mpTarget;     // +0x118
    uint8_t mPad11c[0x38];      // +0x11c
    Vector3 mPressedAt;         // +0x154
    Vector3 mReleasedAt;        // +0x160
    IEffect* mpEffect;          // +0x16c
};

// the effects manager singleton
class cEffectsManager {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void* Slot04();
    virtual void* Slot08();
    virtual void* Slot0c();
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
    virtual void* Slot24();
    virtual void* Slot28();
    virtual bool CreateEffect(void* pConfig, int32_t nFlags);       // +0x2c
    virtual void* Slot30();
    virtual void* Slot34();
    virtual void* Slot38();
    virtual void* Slot3c();
    virtual void* Slot40();
    virtual void* Slot44();
    virtual void* Slot48();
    virtual void* Slot4c();
    virtual void* Slot50();
    virtual IEffectHandle* Acquire(uint32_t nType);                 // +0x54
};

class cGameNounManager {
public:
    cSPNoun* CreateNoun(uint32_t nNounId);                          // 0x00b20c60
};

// a scan-list entry: the erase helper hands back the slot, the strategy asks it
// for the property value it should report.
class cScanIterator {
public:
    int32_t GetValue();                                             // 0x0104c4f0
};

// the inventory item the place-object strategy validates
class cSpaceItem {
public:
    uint32_t GetItemInstanceID();                                   // 0x00c87040
};

// the universe context the tool strategies talk to
class cUniverseContext {
public:
    bool IsPlanetUnlocked(void* pPlanet);                           // 0x00c70b20
    void* GetPlayerObject();                                        // 0x00c71e30
    int32_t GetEmpireState();                                       // 0x00c70e00
    cSpaceItem* GetPlayerItem();                                    // 0x00c30c60
    uint8_t mPad000[0x13c];     // +0x000
    void* mpObjectList;         // +0x13c
};

class cPlanetModel;

// the place-object strategy: only the two flags and the active-object slot
class cSPPlaceObjectToolStrategy {
public:
    virtual void* Slot00();                                         // +0x00
    virtual void* Slot04();
    virtual void* Slot08();
    virtual void* Slot0c();
    virtual void* Slot10();
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();                                         // +0x1c
    bool CanUseCheckA();                                            // 0x0104cc20
    bool CanUseCheckB();                                            // 0x0104cc30
};

// ---------------------------------------------------------------------------
// imports
// ---------------------------------------------------------------------------

bool __stdcall StartTool(cSPToolStrategy* pSelf, const Vector3* pTarget,
                         void* pParam);                             // 0x010568b0

cGameNounManager* __cdecl NounManager();                            // 0x00b3d300
cEffectsManager* __cdecl EffectsManagerPtr();                       // 0x0067ddd0
void __stdcall LaunchProjectile(cSPToolStrategy* pSelf, void* pProjectile,
                                const Vector3* pOrigin,
                                const Vector3* pTarget);            // 0x010543e0
void* __cdecl FUN_0104bf40(IEffect** ppEffect);                     // 0x0104bf40
void __stdcall FUN_00cb5140(void* pObject, void* pOut);             // 0x00cb5140
Matrix3Rows* __stdcall Matrix3FromFacingAndUp(Matrix3Rows* pOut,
                                              const Vector3* pFacing,
                                              const Vector3* pUp);  // 0x0069b440
void* __cdecl SP_GetUniverseContext();                              // 0x01021080
int32_t __stdcall FUN_0104bd80(void* pSelf);                        // 0x0104bd80
bool __stdcall GetCreatureColorProperty(void* pColor, void* pOut);  // 0x0102c720
float __cdecl FUN_0104be50();                                       // 0x0104be50
void __stdcall FUN_00cb8760(const Vector3* pDir, void* pTarget);    // 0x00cb8760
void __stdcall FUN_00cb7ba0(const Vector3* pDir, float fSpeed);     // 0x00cb7ba0
float __cdecl FUN_00e21850();                                       // 0x00e21850
float __cdecl FUN_00c41f20();                                       // 0x00c41f20
cPlanetModel* __cdecl PlanetModel(Vector3* pPosition);              // 0x00ba0cc0
float __fastcall GetRadiusAt(cPlanetModel* pModel, void*,
                             const Vector3* pPosition);             // 0x00ba0cc0
Vector3* __cdecl normalized_safe(Vector3* pOut, const Vector3* pIn);   // 0x00449c20
Vector3* __cdecl OrthogonalVector(Vector3* pOut, const Vector3* pIn);  // 0x006985b0

// the base tool-strategy gates used by CanUseTool
bool __stdcall BaseCanUseTool(cSPPlaceObjectToolStrategy* pSelf, bool bArg,
                              int32_t* pOut);                       // 0x01056160
void __cdecl SetErrorEvent(cSPPlaceObjectToolStrategy* pSelf, int32_t nId,
                           bool bArg);                              // 0x010527f0
void __cdecl AppendScanResult(int32_t nId, int32_t* pOut);          // 0x01052880
cScanIterator* __cdecl EraseScanItem(int32_t nIndex);               // 0x00b3d390
void* __cdecl FUN_01021260();                                       // 0x01021260
cSpaceItem* __cdecl FUN_01021240();                                 // 0x01021240
void* __stdcall FUN_01021300(int32_t nZero);                        // 0x01021300
bool __cdecl FUN_00b8e040(void* pObject, void* pOther);             // 0x00b8e040

extern Vector3 gZeroPoint;                  // 0x016e1b14 (three floats)
extern float gProjectileMinDistance2;       // 0x0149af90
extern uint32_t gAimHandleName;             // 0x013f94d4
extern uint32_t gMissileHandleName;         // 0x017f243b

// ---------------------------------------------------------------------------
// the weapon overrides
// ---------------------------------------------------------------------------

// @ 0x01056f40
bool __stdcall DefaultProjectile_StartTool(cSPToolStrategy* pSelf,
                                           const Vector3* pTarget, void* pParam)
{
    bool bResult = false;
    if (!StartTool(pSelf, pTarget, pParam))
        return bResult;
    if (pTarget->x == gZeroPoint.x && pTarget->y == gZeroPoint.y
        && pTarget->z == gZeroPoint.z)
        return bResult;

    cSPAimObject* pAimer = pSelf->mpAimer;
    Vector3 position = *pAimer->GetPosition();
    Vector3 local;
    cSPNoun* pAimHandle = (cSPNoun*)pAimer->Slotb8(&gAimHandleName);
    if (pAimHandle != nullptr)
        position = *pAimHandle->Slot30(&local);

    float fDX = pTarget->x - position.x;
    float fDY = pTarget->y - position.y;
    float fDZ = pTarget->z - position.z;
    if (fDX * fDX + fDY * fDY + fDZ * fDZ < gProjectileMinDistance2)
        return false;

    cSPNoun* pProjectile = NounManager()->CreateNoun(0x24270c5);
    void* pNoun = (pProjectile != nullptr) ? pProjectile->Slot0c(0x24270c4) : nullptr;
    LaunchProjectile(pSelf, pNoun, &position, pTarget);

    IEffect* pEffect = nullptr;
    cEffectsManager* pManager = EffectsManagerPtr();
    if (pEffect != nullptr) {
        pEffect = nullptr;
        pEffect->Release();
    }
    if (pManager->CreateEffect(FUN_0104bf40(&pEffect), 0)) {
        Matrix3Rows transform;
        FUN_00cb5140(pNoun, &transform);

        XformMsg msg;
        msg.mFlags |= 4;
        msg.mCount += 1;
        msg.mPosition = *pTarget;

        Vector3 facing;
        facing.x = position.x;
        facing.y = position.y;
        facing.z = position.z;
        Vector3 up;
        up.x = local.x;
        up.y = local.y;
        up.z = local.z;
        msg.mBasis = *Matrix3FromFacingAndUp(&msg.mBasis, &facing, &up);
        msg.mBasisFlags |= 2;
        msg.mBasisCount += 1;

        if (SP_GetUniverseContext() != nullptr) {
            msg.mScale = pAimer->GetScalar();
            msg.mCount += 1;
        }

        pEffect->Send(&msg);

        if (FUN_0104bd80(pSelf) == (int32_t)0xe810d505 && pEffect != nullptr) {
            uint8_t color[0x30];
            if (GetCreatureColorProperty(pEffect->Slot0c(color), color))
                pEffect->Slot44(5, color, 3);
        }
        pEffect->Detach(0);
    }

    if (pEffect != nullptr) {
        pEffect->Release();
        return true;
    }
    return true;
}

// @ 0x01057210
bool __stdcall TurretDefenseMissile_StartTool(cSPToolStrategy* pSelf,
                                             const Vector3* pTarget, void* pParam)
{
    if (!StartTool(pSelf, pTarget, pParam))
        return false;
    if (pTarget->x == gZeroPoint.x && pTarget->y == gZeroPoint.y
        && pTarget->z == gZeroPoint.z)
        return false;

    cSPAimObject* pAimer = pSelf->mpAimer;
    cSPNoun* pSource = nullptr;
    if (pAimer != nullptr)
        pSource = (cSPNoun*)pAimer->Slotb8(&gMissileHandleName);

    cSPNoun* pTargetObject = nullptr;
    if (pSelf->mpTarget != nullptr)
        pTargetObject = (cSPNoun*)pSelf->mpTarget->Slotb8(&gAimHandleName);

    float fLifetime = pAimer->Slot70() * 0.9f;

    Vector3 direction = *pAimer->GetPosition();
    float fInvLength = 1.0f / sqrtf(direction.x * direction.x
                                    + direction.y * direction.y
                                    + direction.z * direction.z);
    Vector3 velocity;
    velocity.x = direction.x * fInvLength * fLifetime;
    velocity.y = direction.y * fInvLength * fLifetime;
    velocity.z = direction.z * fInvLength * fLifetime;

    Vector3 origin = *pAimer->GetPosition();
    origin.x += velocity.x;
    origin.y += velocity.y;
    origin.z += velocity.z;

    cSPNoun* pMissile = NounManager()->CreateNoun(0x244d3c8);
    cSPNoun* pObject = (pMissile != nullptr) ? (cSPNoun*)pMissile->Slot0c(0x244d3c0)
                                             : nullptr;

    pObject->Slot54(pSelf);
    Vector3 launchPosition;
    pObject->Slot38(&launchPosition);

    float fSpeed = FUN_0104be50();
    Vector3 aim;
    aim.x = launchPosition.x;
    aim.y = launchPosition.y;
    aim.z = launchPosition.z;
    float fInvAim = 1.0f / sqrtf(aim.x * aim.x + aim.y * aim.y + aim.z * aim.z);
    Vector3 shot;
    shot.x = aim.x * fInvAim * fSpeed;
    shot.y = aim.y * fInvAim * fSpeed;
    shot.z = aim.z * fInvAim * fSpeed;

    FUN_00cb8760(&shot, pTargetObject);
    pObject->Slot48(pSource->Slot4c());
    return true;
}

// @ 0x01057460
bool __stdcall TurretFlak_StartTool(cSPToolStrategy* pSelf,
                                    const Vector3* pTarget, void* pParam)
{
    if (!StartTool(pSelf, pTarget, pParam))
        return false;
    if (pTarget->x == gZeroPoint.x && pTarget->y == gZeroPoint.y
        && pTarget->z == gZeroPoint.z)
        return false;

    cSPAimObject* pAimer = pSelf->mpAimer;
    if (pAimer != nullptr)
        pAimer->Slotb8(&gAimHandleName);

    cSPNoun* pTargetBase = nullptr;
    void* pConfig = nullptr;
    if (pSelf->mpTarget != nullptr) {
        pTargetBase = (cSPNoun*)pSelf->mpTarget->Slotb8(&gAimHandleName);
        if (pTargetBase != nullptr)
            pConfig = pTargetBase->Slot5c(0xb033b403);
    }

    float fLifetime = pAimer->Slot70() * 0.9f;
    Vector3 forward = *pAimer->GetPosition();
    float fInvLength = 1.0f / sqrtf(forward.x * forward.x
                                    + forward.y * forward.y
                                    + forward.z * forward.z);
    Vector3 velocity;
    velocity.x = forward.x * fInvLength * fLifetime;
    velocity.y = forward.y * fInvLength * fLifetime;
    velocity.z = forward.z * fInvLength * fLifetime;

    Vector3 muzzle = *pAimer->GetPosition();
    muzzle.x += velocity.x;
    muzzle.y += velocity.y;
    muzzle.z += velocity.z;

    Vector3 aim;
    aim.x = pTarget->x - muzzle.x;
    aim.y = pTarget->y - muzzle.y;
    aim.z = pTarget->z - muzzle.z;
    float fInvAim = 1.0f / sqrtf(aim.x * aim.x + aim.y * aim.y + aim.z * aim.z);
    aim.x *= fInvAim;
    aim.y *= fInvAim;
    aim.z *= fInvAim;

    cSPNoun* pOriginNoun = (cSPNoun*)pTargetBase->Slot08();
    Vector3 center = *pOriginNoun->GetPosition();
    if (pConfig != nullptr && *(bool*)((uint8_t*)pConfig + 0x74c))
        center = *(Vector3*)((uint8_t*)pConfig + 0x750);

    float fCenterLength2 = center.x * center.x + center.y * center.y
                           + center.z * center.z;
    float fInvCenter = 1.0f / sqrtf(fCenterLength2);
    Vector3 centerDir;
    centerDir.x = center.x * fInvCenter;
    centerDir.y = center.y * fInvCenter;
    centerDir.z = center.z * fInvCenter;

    cPlanetModel* pPlanet = PlanetModel(&centerDir);
    float fRadius = GetRadiusAt(pPlanet, nullptr, &centerDir);
    float fCenterLength = sqrtf(fCenterLength2);
    float fHigh = fRadius + FUN_00e21850();
    float fLow = fRadius + FUN_00c41f20();
    float fDistance = fCenterLength;
    if (fDistance <= fHigh)
        fDistance = fHigh;
    if (fLow <= fDistance)
        fDistance = fLow;

    Vector3 impact;
    impact.x = centerDir.x * fDistance;
    impact.y = centerDir.y * fDistance;
    impact.z = centerDir.z * fDistance;

    Vector3 offset;
    offset.x = impact.x - muzzle.x;
    offset.y = impact.y - muzzle.y;
    offset.z = impact.z - muzzle.z;

    float fDenominator = centerDir.x * aim.x + centerDir.y * aim.y
                         + centerDir.z * aim.z;
    float fT = (offset.x * centerDir.x + offset.y * centerDir.y
                + offset.z * centerDir.z) / fDenominator;

    Vector3 hit;
    hit.x = muzzle.x + aim.x * fT;
    hit.y = muzzle.y + aim.y * fT;
    hit.z = muzzle.z + aim.z * fT;

    float fDistanceA = hit.x * hit.x + hit.y * hit.y + hit.z * hit.z;
    float fDistanceB = offset.x * offset.x + offset.y * offset.y
                       + offset.z * offset.z;
    float fSpeed = FUN_0104be50();
    float fRatio = sqrtf(fDistanceA) / (sqrtf(fDistanceB) / fSpeed);

    Vector3 shot;
    shot.x = aim.x * fRatio;
    shot.y = aim.y * fRatio;
    shot.z = aim.z * fRatio;

    cSPNoun* pShell = NounManager()->CreateNoun(0x240e3bf);
    cSPNoun* pObject = (pShell != nullptr) ? (cSPNoun*)pShell->Slot0c(0x240e3b7)
                                           : nullptr;

    pObject->Slot54(pSelf);
    Vector3 launch;
    pObject->Slot38(&launch);
    pObject->Slot48(pShell->Slot10());
    FUN_00cb7ba0(&shot, fRatio);
    return true;
}

// @ 0x01057990
bool __stdcall DragInputProjectile_StartTool(cSPToolStrategy* pSelf,
                                             const Vector3* pTarget, void* pParam)
{
    if (!StartTool(pSelf, pTarget, pParam))
        return true;
    if (pSelf->mpEffect != nullptr)
        return true;

    pSelf->mPressedAt = *pTarget;
    pSelf->mReleasedAt = *pTarget;

    cEffectsManager* pManager = EffectsManagerPtr();
    IEffectHandle* pHandle = pManager->Acquire(0x3701a5c);
    if (pSelf->mpEffect != nullptr) {
        IEffect* pOld = pSelf->mpEffect;
        pSelf->mpEffect = nullptr;
        pOld->Release();
    }

    if (!pHandle->Create(0x23c4ca24, 0, &pSelf->mpEffect))
        return true;

    XformMsg msg;
    msg.mFlags |= 4;
    msg.mCount += 1;
    msg.mPosition = *pTarget;

    Vector3 facing;
    normalized_safe(&facing, pTarget);
    Vector3 up;
    OrthogonalVector(&up, &facing);
    Vector3 up2;
    normalized_safe(&up2, &up);

    Vector3 side;
    side.x = facing.y * up2.z - facing.z * up2.y;
    side.y = facing.z * up2.x - facing.x * up2.z;
    side.z = facing.x * up2.y - facing.y * up2.x;

    Vector3 realUp;
    realUp.x = up2.y * side.z - up2.z * side.y;
    realUp.y = up2.z * side.x - up2.x * side.z;
    realUp.z = up2.x * side.y - up2.y * side.x;

    msg.mBasis.m[0] = up2.x;
    msg.mBasis.m[1] = up2.y;
    msg.mBasis.m[2] = up2.z;
    msg.mBasis.m[3] = realUp.x;
    msg.mBasis.m[4] = realUp.y;
    msg.mBasis.m[5] = realUp.z;
    msg.mBasis.m[6] = side.x;
    msg.mBasis.m[7] = side.y;
    msg.mBasis.m[8] = side.z;

    msg.mBasisFlags |= 2;
    msg.mBasisCount += 1;

    pSelf->mpEffect->Send(&msg);
    pSelf->mpEffect->Detach(0);
    return true;
}

// @ 0x01057bd0
bool __stdcall PlaceObject_CanUseTool(cSPPlaceObjectToolStrategy* pSelf,
                                      bool bArg, int32_t* pOut)
{
    if (!BaseCanUseTool(pSelf, bArg, pOut))
        return false;

    cUniverseContext* pContext = (cUniverseContext*)FUN_01021260();
    if (pSelf->CanUseCheckA()) {
        if (!pContext->IsPlanetUnlocked(FUN_01021300(0))) {
            SetErrorEvent(pSelf, 0xb6cb3e94, bArg);
            if (pOut != nullptr)
                *pOut = EraseScanItem(6)->GetValue();
            return false;
        }
    }

    if (!pSelf->CanUseCheckB())
        goto check_planet;

    if ((FUN_01021240()->GetItemInstanceID() & 2) != 0) {
        if (pContext->GetPlayerItem() != FUN_01021240()) {
            SetErrorEvent(pSelf, 0x15589a01, bArg);
            AppendScanResult(5, pOut);
            return false;
        }
        goto check_empire;
    }

check_empire:
    if (pContext->GetPlayerObject() == FUN_01021300(0)) {
        SetErrorEvent(pSelf, 0x15589a01, bArg);
        if (pOut != nullptr)
            *pOut = EraseScanItem(5)->GetValue();
        return false;
    }
    if (pContext->GetEmpireState() != 5) {
        SetErrorEvent(pSelf, 0x15589a01, bArg);
        AppendScanResult(5, pOut);
        return false;
    }

check_planet:
    pContext = (cUniverseContext*)FUN_01021260();
    if (!FUN_00b8e040(*(void**)((uint8_t*)pContext + 0x13c), pSelf->Slot1c()))
        return true;

    SetErrorEvent(pSelf, 0x14a144d8, bArg);
    if (pOut != nullptr)
        *pOut = EraseScanItem(7)->GetValue();
    return false;
}
