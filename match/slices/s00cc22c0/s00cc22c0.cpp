// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00cc22c0.
//
// Projectile views: explosion handler, nearest-creature search, and the
// factory functions that build the beam / tool / deep-space / AoE views.

typedef unsigned int size_t;
typedef unsigned int uint;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned short ushort;
typedef short int16_t;
typedef int intptr_t;
#define nullptr 0

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};

class cEmpire : public IRefCounted {
public:
    void GetColor(void* pColor);
    uint8_t mPad14[0x30];
};

class cPlanetModel {
public:
    void* BuildSurfaceOrientation(void* pOut, const Vec3* pPosition);
};

class cSPCreatureBase {
public:
    bool PlayIdleAnimation(int nAnimation, int bLoop);
};

class cDefaultAoEArea : public IRefCounted {
public:
    virtual void v14();
    virtual uint32_t GetNoteEffectID();
    virtual void v1c();
    virtual void v20();
    uint8_t mPad18[0x1c];
};

class cEffectInfo : public IRefCounted {
public:
    uint8_t mPad14[0x10];
};

class cEffectsManager {
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
    virtual void CreateEffect(uint32_t id, int a, cEffectInfo** ppOut);   // 0x2c
};

class cSpatialObjectView : public IRefCounted {
public:
    cSpatialObjectView();
    ~cSpatialObjectView();
    void SetObject(void* pObject);                  // 0x24
    int UpdateState();
    void HandleSimulationUpdate(int a, int b);
    void CreateEffect(uint32_t id, int a);          // wrapper over the effect list

    uint8_t mPad04[0x10];           // 0x04
    void* mpObject;                 // 0x14
    uint8_t mPad18[0x1c];           // 0x18
    cEffectInfo* mpEffectInfo;      // 0x34
    uint8_t mFlag38;                // 0x38
    uint8_t mFlag39;                // 0x39
    uint8_t mFlag3a;                // 0x3a
    uint8_t mFlag3b;                // 0x3b
    uint8_t mFlag3c;                // 0x3c
    uint8_t mFlag3d;                // 0x3d
    uint8_t mPad3e[0x02];           // 0x3e
    int mViewState;                 // 0x40
};

class cDefaultBeamProjectileView : public cSpatialObjectView {
public:
    cDefaultBeamProjectileView();
    bool mbLoadingModel;            // 0x44
    bool mbAnimationsStarted;       // 0x45
};

class cSpaceDefenseMissileView : public cSpatialObjectView {
public:
    cSpaceDefenseMissileView();
    ~cSpaceDefenseMissileView();
    void HandleSimulationUpdate(int a, int b);
};

class cDefaultToolProjectile : public cSpatialObjectView {
public:
    void Explode(int nKind, void* pHit);
};

class cEmotionSource : public IRefCounted {
public:
    void* GetTarget();
};

class cCulturalProjectileView : public cSpatialObjectView {
public:
    static cSpatialObjectView* MakeView(void* pObject);   // 0x00cc3140
};

class cSpaceProjectile : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual uint32_t GetEffectId();                 // 0x1c
    virtual void v20();
    uint8_t mPad18[0x1c];
};

class cGameNounManager {
public:
    void* GetGameDataVector(void* pA, void* pB, void* pC, void* pD, const void* pType);
};

// Matrix used by the explosion orientation (9 floats).
struct Matrix33 {
    float mValue[9];
};

struct EffectSpawnInfo {
    uint16_t mFlags;                // 0x00
    int16_t  mCount;                // 0x02
    Vec3     mPosition;             // 0x04
    float    mScale;                // 0x10
};

void* operator_new(size_t nSize, const char* pName, int a, int b, int c, int d);
void* operator_new(size_t nSize, const char* pName, int a);
void* operator_new(size_t nSize, const char* pName, int a, int b);
cEffectsManager* EffectsManager();
cPlanetModel* PlanetModel(Vec3* pOut, const Vec3* pPosition);
void* Matrix3FromFacingAndUp(Matrix33* pOut, const Vec3* pDirection);
void* BuildOrientationMatrix(Matrix33* pOut, const void* pOrientation);
void* GetUniverseContext();
cEmpire* GetPlayerEmpire(Vec3* pOut);
cGameNounManager* NounManager();
void* NounManager(uint32_t id);
uint8_t* GetGameDataVectorCreatures();
void* GetCurrentGameMode();
uint32_t GetHitEffectIdA();
uint32_t GetHitEffectIdB();
uint32_t GetHitEffectIdC();
uint32_t GetBeamEffectId();
uint32_t GetMuzzleEffectId();
uint32_t GetChargeEffectId();
uint32_t GetTrailEffectId();
uint32_t GetProjectileKind();
uint32_t GetProjectileType();
bool IsWaterSurface();
uint32_t GetAoEKind();
bool IsAoEValid();
void* CreateHitInstance(uint32_t id);
void* FindEffect(uint32_t id);
void CreateEffectRef(uint32_t id, int a, uint32_t group);
void SetEffectScale(uint32_t id, uint32_t fScaleBits);
bool IsEmpireObjectValid(void* pObject);
void SpawnWorldDecal(const Vec3* pPosition);
void* FindObjectAt(void* pVector, const Vec3* pPosition, int a);
void ApplyDamageShake(const Vec3* pPosition);
void PlayExplosionSound(const Vec3* pPosition);
void CameraShake(const Vec3* pPosition, uint32_t id, uint32_t a, uint32_t b);
void SpawnHitParticles(void* pEffect);
void ApplyRadialDamage(const Vec3* pPosition, uint32_t id, uint32_t radius, uint32_t kind);
bool IsCinematicMode(int a);
bool IsAoEPreviewActive();
uint32_t GetAoEPreviewEffectId();
void* FindNounFromId(uint32_t id);
void UpdateMissileEffect(void* pView, void* pEffect, int a);
void UpdateBeamEffect(void* pView, void* pEffect, int a);
void NotifyProjectileHit();

extern uint8_t gGameModeTribe;
extern const float gDefaultOrientation;

// ---------------------------------------------------------------------------
// 0x00cc22c0  Simulator::cDefaultToolProjectile::Explode
// ---------------------------------------------------------------------------
// @ 0x00cc22c0
void cDefaultToolProjectile::Explode(int nKind, void* pHit)
{
    NotifyProjectileHit();

    uint32_t nEffectId;
    if (nKind == 0) {
        void* pObject = nullptr;
        void* pTarget = nullptr;
        if (pHit != nullptr)
            pTarget = ((IRefCounted*)pHit)->Query((const void*)0xb033b403);
        if (pTarget == nullptr || *(void**)((uint8_t*)pTarget + 0x714) == nullptr ||
            GetTrailEffectId() == 0)
            nEffectId = GetHitEffectIdC();
        else
            nEffectId = GetTrailEffectId();
    } else if (nKind == 1 || nKind != 2) {
        nEffectId = GetHitEffectIdA();
    } else {
        nEffectId = GetHitEffectIdB();
    }

    bool bInstant = false;
    bool bWater = false;
    if (*(void**)((uint8_t*)this + 0x518) != nullptr) {
        uint32_t nHitKind = GetProjectileKind();
        if (nHitKind == 0xeb54070u)
            bInstant = true;
        else
            bWater = IsWaterSurface() != 0;
    }

    cEffectInfo* pOldEffect = *(cEffectInfo**)((uint8_t*)this + 0x5cc);
    *(cEffectInfo**)((uint8_t*)this + 0x5cc) = nullptr;
    if (pOldEffect != nullptr)
        pOldEffect->Release();

    void* pTargetObject = nullptr;
    if (pHit != nullptr)
        pTargetObject = ((IRefCounted*)pHit)->Query((const void*)&gGameModeTribe);

    if (nKind == 0 && pTargetObject != nullptr) {
        void* pInstance = CreateHitInstance(nEffectId);
        cEffectInfo* pCurrent = *(cEffectInfo**)((uint8_t*)this + 0x5cc);
        if (pInstance != pCurrent) {
            if (pInstance != nullptr)
                ((IRefCounted*)pInstance)->AddRef();
            *(void**)((uint8_t*)this + 0x5cc) = pInstance;
            if (pCurrent != nullptr)
                pCurrent->Release();
        }
    } else {
        cEffectsManager* pEffects = EffectsManager();
        cEffectInfo* pCurrent = *(cEffectInfo**)((uint8_t*)this + 0x5cc);
        if (pCurrent != nullptr) {
            *(cEffectInfo**)((uint8_t*)this + 0x5cc) = nullptr;
            pCurrent->Release();
        }
        pEffects->CreateEffect(nEffectId, 0, (cEffectInfo**)((uint8_t*)this + 0x5cc));
    }

    if (*(cEffectInfo**)((uint8_t*)this + 0x5cc) != nullptr) {
        EffectSpawnInfo info;
        info.mPosition.mX = 0.0f;
        info.mPosition.mY = 0.0f;
        info.mPosition.mZ = 0.0f;
        info.mCount = 0;
        info.mFlags = 0;
        info.mScale = 1.0f;

        Matrix33 orientation;
        Vec3* pPosition = (Vec3*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x2c))
                                 ((uint8_t*)this + 0x34);
        info.mPosition = *pPosition;
        info.mFlags |= 4;
        info.mCount += 1;

        Matrix33* pSource;
        if (!bWater) {
            if (bInstant) {
                pSource = (Matrix33*)((uint8_t*)this + 0x5a8);
            } else {
                Vec3* pDir = (Vec3*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x2c))
                                       ((uint8_t*)this + 0x34);
                void* pFacing = ((void* (__thiscall*)(void*, void*, void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x5c))
                                       ((uint8_t*)this + 0x34, &orientation, pDir);
                pSource = (Matrix33*)Matrix3FromFacingAndUp(&orientation, (Vec3*)pFacing);
            }
        } else {
            Vec3* pDir = (Vec3*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x2c))
                                   ((uint8_t*)this + 0x34);
            cPlanetModel* pPlanet = PlanetModel(&info.mPosition, pDir);
            void* pSurface = pPlanet->BuildSurfaceOrientation(&orientation, pDir);
            pSource = (Matrix33*)BuildOrientationMatrix(&orientation, pSurface);
        }

        for (int i = 0; i < 9; ++i)
            orientation.mValue[i] = pSource->mValue[i];
        info.mFlags |= 2;
        info.mCount += 1;

        if (GetUniverseContext() != nullptr) {
            void* pOwner = *(void**)((uint8_t*)this + 0x518);
            info.mScale = ((cSpaceProjectile*)pOwner)->GetEffectId();
            info.mCount += 1;
        }

        if (GetProjectileKind() == 0xec439b3fu) {
            Vec3 color;
            cEmpire* pEmpire = GetPlayerEmpire(&color);
            pEmpire->GetColor(&color);
            ((IRefCounted*)*(void**)((uint8_t*)this + 0x5cc))->v10();
        }

        ((IRefCounted*)*(void**)((uint8_t*)this + 0x5cc))->AddRef();
        ((IRefCounted*)*(void**)((uint8_t*)this + 0x5cc))->Release();

        if (*(int*)((uint8_t*)this + 0x538) == 0xb) {
            void* pCreatures = GetGameDataVectorCreatures();
            Vec3* pPos = (Vec3*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x2c))
                                   ((uint8_t*)this + 0x34);
            void* pHitObject = FindObjectAt((uint8_t*)pCreatures + 4, pPos, 0);
            if (pHitObject != nullptr)
                SpawnHitParticles(*(void**)((uint8_t*)this + 0x5cc));
        }
    }

    int nProjectileKind = *(int*)((uint8_t*)this + 0x538);
    if (nProjectileKind == 0xe || nProjectileKind == 0xf || nProjectileKind == 10) {
        Vec3* pPosition = (Vec3*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)this + 0x34) + 0x2c))
                                 ((uint8_t*)this + 0x34);
        SpawnWorldDecal(pPosition);
        ApplyDamageShake(pPosition);
    }

    if (GetCurrentGameMode() == &gGameModeTribe) {
        void* pWeapon = *(void**)((uint8_t*)this + 0x504);
        uint32_t nOwner = 0xffffffffu;
        int nTarget = 0;
        if (((cEmotionSource*)pWeapon)->GetTarget() != nullptr)
            nTarget = 1;
        void* pSource = pWeapon;
        (void)pSource;
        uint32_t nGroup = *(uint32_t*)((uint8_t*)this + 0x534);
        uint32_t nResult = ((cSpaceProjectile*)pSource)->GetEffectId();
        CameraShake(nullptr, nGroup, (uint32_t)(nTarget == 0), nResult);
        (void)nOwner;
    }
}

// ---------------------------------------------------------------------------
// 0x00cc26a0  FindNearestCreature
// ---------------------------------------------------------------------------
// @ 0x00cc26a0
int FindNearestCreature(float fX, float fY, float fZ, bool bGround, bool bAir)
{
    cGameNounManager* pNouns = NounManager();
    uint8_t* pVector = (uint8_t*)pNouns->GetGameDataVector(nullptr, nullptr, nullptr, nullptr,
                                                          (const void*)&gGameModeTribe);
    int nCount = (*(int*)(pVector + 8) - *(int*)(pVector + 4)) >> 2;

    int pBest = 0;
    float fBestDistance = 0.0f;
    for (int i = 0; i < nCount; ++i) {
        int pCreature = *(int*)(*(int*)(pVector + 4) + i * 4);
        int nKind = *(int*)((uint8_t*)pCreature + 0x714);
        if (IsCinematicMode(1))
            continue;
        void* pAnimated = *(void**)((uint8_t*)pCreature + 0x6c8);
        if (pAnimated != nullptr && ((cSPCreatureBase*)((uint8_t*)pAnimated + 8))->PlayIdleAnimation(8, 0))
            continue;

        int pCandidate = 0;
        if (bAir && (nKind == 2 || nKind == 4 || nKind == 5))
            pCandidate = pCreature;
        if (bGround && (nKind == 0 || nKind == 3))
            pCandidate = pCreature;

        if (pCandidate != 0) {
            Vec3* pPosition = (Vec3*)(*(void* (__thiscall*)(void*))(**(uint32_t**)((uint8_t*)pCandidate + 0x34) + 0x2c))
                                     ((uint8_t*)pCandidate + 0x34);
            float fDistance = (fZ - pPosition->mZ) * (fZ - pPosition->mZ) +
                              (fY - pPosition->mY) * (fY - pPosition->mY) +
                              (fX - pPosition->mX) * (fX - pPosition->mX);
            if (pBest == 0 || fDistance < fBestDistance) {
                pBest = pCandidate;
                fBestDistance = fDistance;
            }
        }
    }
    return pBest;
}

// ---------------------------------------------------------------------------
// 0x00cc27f0  cProjectileView::UpdateState
// ---------------------------------------------------------------------------
// @ 0x00cc27f0
int cSpatialObjectView::UpdateState()
{
    if (mpObject == nullptr)
        return 0;

    int nState = mViewState;
    if (nState == 0) {
        UpdateMissileEffect(this, mpObject, 0);
    } else if (nState == 1) {
        Vec3* pDirection = (Vec3*)(*(void* (__thiscall*)(void*))(**(uint32_t**)mpObject + 0x18))(mpObject);
        if (pDirection->mX != gDefaultOrientation || pDirection->mY != 0.0f ||
            pDirection->mZ != 0.0f) {
            if (!IsWaterSurface())
                UpdateBeamEffect(this, mpObject, 0);
        }
        UpdateMissileEffect(this, mpObject, 1);
    } else if (nState == 2) {
        return (int)GetAoEKind();
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00cc28c0  Simulator::cDefaultBeamProjectileView::cDefaultBeamProjectileView
// ---------------------------------------------------------------------------
// @ 0x00cc28c0
cDefaultBeamProjectileView::cDefaultBeamProjectileView()
{
    mpEffectInfo = nullptr;         // 0x34
    mFlag38 = 0;
    mFlag39 = 0;
    mFlag3a = 0;
    mFlag3b = 0;
    mFlag3c = 0;
    mFlag3d = 0;
}

// ---------------------------------------------------------------------------
// 0x00cc28f0  MakeFlakProjectileView
// ---------------------------------------------------------------------------
// @ 0x00cc28f0
cSpatialObjectView* MakeFlakProjectileView(void* pObject)
{
    cSpatialObjectView* pView =
        (cSpatialObjectView*)operator_new(0x34, "Simulator/cFlakProjectileView", 0, 0, 0, 0);
    if (pView == nullptr)
        pView = nullptr;
    else
        pView->SetObject(nullptr);

    pView->SetObject(pObject);

    void* pData = nullptr;
    if (pObject != nullptr)
        pData = ((IRefCounted*)pObject)->Query((const void*)0x240e3b7);

    if (*(void**)((uint8_t*)pData + 0x518) != nullptr) {
        uint32_t nEffectId = GetTrailEffectId();
        CreateEffectRef(nEffectId, 0, 0);
    }
    SetEffectScale(0, 0x45000000u);
    return pView;
}

// ---------------------------------------------------------------------------
// 0x00cc2980  MakeDefaultToolProjectileView
// ---------------------------------------------------------------------------
// @ 0x00cc2980
cSpatialObjectView* MakeDefaultToolProjectileView(void* pObject)
{
    cSpatialObjectView* pView =
        (cSpatialObjectView*)operator_new(0x38, "Simulator/cDefaultToolProjectileView", 0);
    if (pView == nullptr)
        pView = nullptr;
    else
        pView->SetObject(nullptr);

    if (pObject == nullptr)
        return pView;

    void* pData = ((IRefCounted*)pObject)->Query((const void*)0x24270c4);
    if (pData == nullptr)
        return pView;

    pView->SetObject(pObject);
    pView->mFlag38 = 0;

    uint32_t nEffectId = GetMuzzleEffectId();
    if (nEffectId != 0) {
        uint32_t nKind = GetTrailEffectId();
        CreateEffectRef(nKind, 0, 0x500f162u);
        uint32_t fScale = (nKind == 0x203c5a15u || nKind == 0x992387aeu) ? 0x45000000u : 0x44800000u;
        SetEffectScale(0x500f162u, fScale);
    }

    if (GetChargeEffectId() != 0) {
        pView->mFlag39 = 0;
        uint32_t nCharge = GetChargeEffectId();
        CreateEffectRef(nCharge, 0, 0x6565ae1u);
        SetEffectScale(0x6565ae1u, 0x44800000u);
        uint32_t nChargeKind = GetTrailEffectId();
        if (nChargeKind == 0x79c7d671u || nChargeKind == 0x992387aeu || nChargeKind == 0xe8d95fb4u)
            pView->mFlag39 = 1;
    }

    float fScale = ((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x504))->GetEffectId();
    void* pEffect = FindEffect(0x500f162u);
    if (pEffect != nullptr) {
        UpdateBeamEffect(pEffect, &fScale, 1);
        if (GetProjectileType() == 0xe810d505u) {
            void* pTarget = (void*)(intptr_t)((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x504))->GetEffectId();
            if (pTarget != nullptr) {
                uint32_t nColor = ((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x504))->GetEffectId();
                if (IsEmpireObjectValid((void*)(intptr_t)nColor))
                    UpdateBeamEffect(pEffect, &nColor, 5);
            }
        }
    }
    return pView;
}

// ---------------------------------------------------------------------------
// 0x00cc2b60  MakeDeepSpaceProjectileView
// ---------------------------------------------------------------------------
// @ 0x00cc2b60
cSpatialObjectView* MakeDeepSpaceProjectileView(void* pObject)
{
    cSpatialObjectView* pView =
        (cSpatialObjectView*)operator_new(0x34, "Simulator/cDeepSpaceProjectileView", 0, 0, 0, 0);
    if (pView == nullptr)
        pView = nullptr;
    else
        pView->SetObject(nullptr);

    if (pObject == nullptr)
        return pView;

    void* pData = ((IRefCounted*)pObject)->Query((const void*)0x24270c6);
    if (pData == nullptr)
        return pView;

    pView->SetObject(pObject);
    uint32_t nEffect0 = GetTrailEffectId();
    CreateEffectRef(nEffect0, 0, 0);
    uint32_t nEffect1 = GetBeamEffectId();
    CreateEffectRef(nEffect1, 0, 1);
    uint32_t nEffect2 = GetMuzzleEffectId();
    CreateEffectRef(nEffect2, 0, 2);
    uint32_t nEffect3 = GetChargeEffectId();
    CreateEffectRef(nEffect3, 0, 3);
    SetEffectScale(0, 0x45000000u);
    SetEffectScale(1, 0x45000000u);
    SetEffectScale(2, 0x45000000u);
    SetEffectScale(3, 0x45000000u);
    return pView;
}

// ---------------------------------------------------------------------------
// 0x00cc2c90  Simulator::cSpaceDefenseMissileView::cSpaceDefenseMissileView
// ---------------------------------------------------------------------------
// @ 0x00cc2c90
cSpaceDefenseMissileView::cSpaceDefenseMissileView()
{
    mpEffectInfo = nullptr;
    mFlag38 = 0;
    mFlag39 = 0;
    mFlag3a = 0;
    mFlag3b = 0;
}

// ---------------------------------------------------------------------------
// 0x00cc2cb0  Simulator::cSpaceDefenseMissileView::~cSpaceDefenseMissileView
// ---------------------------------------------------------------------------
// @ 0x00cc2cb0
cSpaceDefenseMissileView::~cSpaceDefenseMissileView()
{
    if (mpEffectInfo != nullptr) {
        mpEffectInfo->Query(nullptr);
        cEffectInfo* pOld = mpEffectInfo;
        if (pOld != nullptr) {
            mpEffectInfo = nullptr;
            pOld->Release();
        }
    }

    if (mpObject != nullptr) {
        ((IRefCounted*)mpObject)->Query(nullptr);
        if (mpObject != nullptr) {
            void* pOld = mpObject;
            mpObject = nullptr;
            ((IRefCounted*)pOld)->Release();
        }
    }

    if (mpObject != nullptr)
        ((IRefCounted*)mpObject)->Release();
    if (mpEffectInfo != nullptr)
        mpEffectInfo->Release();
}

// ---------------------------------------------------------------------------
// 0x00cc2d30  Simulator::cSpaceDefenseMissileView::HandleSimulationUpdate
// ---------------------------------------------------------------------------
// @ 0x00cc2d30
void cSpaceDefenseMissileView::HandleSimulationUpdate(int a, int b)
{
    cSpatialObjectView::HandleSimulationUpdate(a, b);
    UpdateMissileEffect(mpObject, mpEffectInfo, 0);
    UpdateBeamEffect(mpObject, &mpEffectInfo, 0);
}

// ---------------------------------------------------------------------------
// 0x00cc2d70  MakeDefaultBeamProjectileView
// ---------------------------------------------------------------------------
// @ 0x00cc2d70
cSpatialObjectView* MakeDefaultBeamProjectileView(void* pObject)
{
    cDefaultBeamProjectileView* pView =
        (cDefaultBeamProjectileView*)operator_new(0x40, "Simulator/cDefaultBeamProjectileView", 0, 0);
    if (pView == nullptr) {
        pView = nullptr;
    } else {
        pView->mpEffectInfo = nullptr;
        pView->mFlag38 = 0;
        pView->mFlag39 = 0;
        pView->mFlag3a = 0;
        pView->mFlag3b = 0;
        pView->mbLoadingModel = false;
        pView->mbAnimationsStarted = false;
    }

    void* pData = nullptr;
    if (pObject != nullptr)
        pData = ((IRefCounted*)pObject)->Query((const void*)0x24630ce);

    pView->SetObject(pObject);
    pView->mFlag39 = 0;

    uint32_t nEffect0 = GetBeamEffectId();
    CreateEffectRef(nEffect0, 0, 0x246350au);
    uint32_t nEffect1 = GetMuzzleEffectId();
    CreateEffectRef(nEffect1, 0, 0x9138b729u);
    uint32_t nEffect2 = GetHitEffectIdA();
    pView->CreateEffect(nEffect2, 0);
    uint32_t nEffect3 = GetHitEffectIdB();
    pView->CreateEffect(nEffect3, 0);
    uint32_t nEffect4 = GetHitEffectIdC();
    pView->CreateEffect(nEffect4, 0);
    SetEffectScale(0x246350au, 0x45000000u);
    SetEffectScale(0x9138b729u, 0x45000000u);
    SetEffectScale(0x246350bu, 0x45000000u);
    SetEffectScale(0x246350cu, 0x45000000u);
    SetEffectScale(0x246350du, 0x45000000u);

    if (GetTrailEffectId() != 0) {
        uint32_t nTrail = GetTrailEffectId();
        pView->CreateEffect(nTrail, 0);
        SetEffectScale(0x47f791au, 0x44800000u);
    }

    pView->mpEffectInfo = nullptr;
    pView->mFlag38 = 0;

    float fScale = ((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x108))->GetEffectId();
    void* pEffect = FindEffect(0x246350au);
    if (pEffect != nullptr) {
        UpdateBeamEffect(pEffect, &fScale, 1);
        if (GetProjectileType() == 0xe810d505u) {
            uint32_t nTarget = ((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x108))->GetEffectId();
            if (nTarget != 0) {
                uint32_t nColor = ((cSpaceProjectile*)*(void**)((uint8_t*)pData + 0x108))->GetEffectId();
                if (IsEmpireObjectValid((void*)(intptr_t)nColor)) {
                    UpdateBeamEffect(pEffect, &nColor, 5);
                    void* pSecond = FindEffect(0x9138b729u);
                    if (pSecond != nullptr)
                        UpdateBeamEffect(pSecond, &nColor, 5);
                }
            }
        }
    }
    return pView;
}

// ---------------------------------------------------------------------------
// 0x00cc3000  MakeDefaultAoEAreaView
// ---------------------------------------------------------------------------
// @ 0x00cc3000
cSpatialObjectView* MakeDefaultAoEAreaView(void* pObject)
{
    cSpatialObjectView* pView =
        (cSpatialObjectView*)operator_new(0x34, "Simulator/cDefaultAoEAreaView", 0, 0, 0, 0);
    if (pView == nullptr)
        pView = nullptr;
    else
        pView->SetObject(nullptr);

    cDefaultAoEArea* pArea = nullptr;
    if (pObject != nullptr)
        pArea = (cDefaultAoEArea*)((IRefCounted*)pObject)->Query((const void*)0x4167194);

    pView->SetObject(pObject);

    if (IsAoEPreviewActive()) {
        uint32_t nPreviewEffect = GetAoEPreviewEffectId();
        CreateEffectRef(nPreviewEffect, 0, 0x4178e6eu);
    }

    uint32_t nNoteEffect = pArea->GetNoteEffectID();
    CreateEffectRef(nNoteEffect, 0, 0x4178e6fu);

    uint32_t nNounId = ((cSpaceProjectile*)pArea)->GetEffectId();
    if (nNounId != 0xffffffffu) {
        uint32_t nId = ((cSpaceProjectile*)pArea)->GetEffectId();
        NounManager(nId);
        if (FindNounFromId(nId) != nullptr) {
            void* pEffect = FindEffect(0x4178e6eu);
            if (pEffect != nullptr)
                UpdateBeamEffect(pEffect, &nId, 5);
            pEffect = FindEffect(0x4178e6fu);
            if (pEffect != nullptr)
                UpdateBeamEffect(pEffect, &nId, 5);
        }
    }
    return pView;
}

// ---------------------------------------------------------------------------
// 0x00cc3140  SP::cCulturalProjectileView::MakeView
// ---------------------------------------------------------------------------
// @ 0x00cc3140
cSpatialObjectView* cCulturalProjectileView::MakeView(void* pObject)
{
    cSpatialObjectView* pView =
        (cSpatialObjectView*)operator_new(0x38, "Simulator/cCulturalProjectileView", 0, 0, 0, 0);
    if (pView == nullptr)
        pView = nullptr;
    else
        pView->SetObject(nullptr);

    pView->SetObject(pObject);
    pView->mFlag38 = 0;

    CreateEffectRef(0x4cc9a429u, 0, 0);
    SetEffectScale(0, 0x44800000u);

    void* pEffect = FindEffect(0);
    if (pEffect != nullptr) {
        uint32_t nColor = ((cSpaceProjectile*)pObject)->GetEffectId();
        NounManager(nColor);
        if (FindNounFromId(nColor) != nullptr)
            UpdateBeamEffect(pEffect, &nColor, 5);
    }
    return pView;
}
