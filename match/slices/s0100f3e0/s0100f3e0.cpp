// Slice s0100f3e0: Spore's space-stage sim-universe event logic -- the pirate-raid plunder/ally and
// happiness-disaster event frequencies, the artifact creator, the happiness disaster mission factory,
// the planet/binheap helpers and the artifact-value accumulator.  Reconstructed from the retail
// disassembly; field offsets are the retail ones.
#include <math.h>

typedef unsigned char      uchar;
typedef unsigned int       uint;
typedef unsigned short     ushort;
typedef unsigned __int64   uint64;

struct Property;

// ---- property lists ------------------------------------------------------------------------
// A property list exposes GetProperty through vtable slot 9 (+0x24).
struct cPropertyList {
    virtual void vf0();
    virtual int  Release();                                   // +0x04
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual bool GetProperty(uint id, Property** out);        // +0x24
};

// A property: the payload pointer, the storage flags and the type tag at +0x10/+0x12.
struct Property {
    void*  mpData;                                            // +0x00
    char   mPad04[0x0c];                                      // +0x04
    ushort mFlags;                                            // +0x10
    ushort mType;                                             // +0x12
    float* GetFloat();                                        // 0x0041ea70
    int*   GetInt()                                           // 0x0041e990 (inlined here)
    {
        if (mFlags & 0x30)
            return (int*)mpData;
        if (mType)
            return (int*)this;
        return 0;
    }
};

// SP::GetPropertyT<int>(list, id, out)
void __cdecl GetPropertyT_int(cPropertyList* pList, uint id, int* pOut);   // 0x0040cf10

struct cSimulatorUniverse {
    virtual void vf0();
    virtual void vf1();
    char mPad08[8];                                           // +0x08
    cPropertyList* mpTuning;                                  // +0x10
    char mPad14[0x118 - 0x14];                                // +0x14
    int m118;                                                 // +0x118
    uchar HasVisibleAvatar(void* pNoun);                      // 0x0100fb00
};
extern cSimulatorUniverse* gSimUniverse;                      // 0x016dc798

// ---- game-object helpers -------------------------------------------------------------------
struct IntVector {
    int* mpBegin;                                             // +0x00
    int* mpEnd;                                               // +0x04
};

struct cGameNounManager {
    char   mPad70[0x70];                                      // +0x00
    void*  mpAvatar70;                                        // +0x70
    float* GetCities();                                       // 0x005c65e0
    void*  GetAvatar();                                       // 0x00b1fdb0
};

struct cGameNounOwner {
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
    int   GetNounType();                                      // 0x00b8dab0
    cGameNounManager* GetNounManager();                       // 0x00b8de30
    bool  FUN_00b8d9a0();                                     // 0x00b8d9a0
};
bool            FUN_00b8e040(void* pNoun, int id);            // 0x00b8e040
int             FUN_01021300();                               // 0x01021300 (player empire)

struct RandomLinearCongruential {
    unsigned RandomUint32Uniform(unsigned n);                 // 0x00a68fb0
};
extern RandomLinearCongruential g_random;                     // 0x01601760

struct cSpaceTradeRouteManager {
    bool FUN_01037d90();                                      // 0x01037d90
    int GetNumberOfPlayerTradeRoutes();                       // 0x01037f20
};

struct cStarManager {
    void* GetRecord();                                        // 0x00ba6dc0
    int   GetEmpireByID();                                    // 0x00ba9370
    void  GetOrActivatePlanet(void** out);                    // 0x00bb59b0
    cSpaceTradeRouteManager* GetTradeRouteManager();          // 0x00ba6490
};
cStarManager* __stdcall StarManager(void* pAvatar);           // 0x00b3d2a0 (one argument)
cStarManager* __cdecl StarManagerNoArg();                     // 0x00b3d2a0 (no argument)

struct cStarRecordRef {
    int   GetCommContext();                                   // 0x00ce6950
    void* GetGroup(int index);                                // 0x00b8dec0
};
struct cArtifactItem {
    double GetValue();                                        // 0x00fd9410
};

// Planet records are released through vtable slot 48 (+0xc0).
struct cPlanetRecord {
    char mPad1b8[0x1b8];                                      // +0x000
    char mUncolonized;                                        // +0x1b8
};
inline void PlanetRelease(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[0xc0 / 4])(p);
}
inline void ResetPlanet(void** slot)
{
    void* p = *slot;
    if (p) {
        *slot = 0;
        PlanetRelease(p);
    }
}
double FUN_0100d410(void* pPlanet);                           // 0x0100d410
double FUN_0100d500(float seconds, float rate);               // 0x0100d500

void* NounManager(uint id);                                   // 0x00b3d300
struct cTerrainSphere {
    double GetRadius();                                       // 0x00c75c30
};
struct cTerrainEditor {
    cTerrainSphere* GetCurrentTerrainSphere();                // 0x00f67d90
};

struct SpaceGameData {
    char mPad18[0x18];                                        // +0x00
    IntVector mList18;                                        // +0x18
    char mPad20[0x2c - 0x20];                                 // +0x20
    IntVector mPlanets;                                       // +0x2c
};

struct SpaceGame {
    char mPad30[0x30];                                        // +0x00
    SpaceGameData* mpData;                                    // +0x30
    char mPad34[0xc4 - 0x34];                                 // +0x34
    uint  mFlags;                                             // +0xc4
    double GetRaidSpeedFactor(int mode);                      // 0x01005c60
};
void* SpaceGameGet();                                         // 0x01002bd0

extern int  g_placeHappinessBooster;                          // 0x016dca7c

// ---- events --------------------------------------------------------------------------------
namespace SP {

struct PirateRaidPlunderEvent {
    virtual void vf0();
    char  mPad04[4];                                          // +0x04
    uint64 mTimeSinceLastRaidMSec;                            // +0x08
    double GetEventFrequency(uint64 deltaMs);                 // 0x0100f3e0
};

struct PirateRaidAllyEvent {
    virtual void vf0();
    char  mPad04[4];                                          // +0x04
    uint64 mTimeSinceLastRaidMSec;                            // +0x08
    double GetEventFrequency(uint64 deltaMs);                 // 0x0100f600
};

struct HappinessDisasterEvent {
    virtual void vf0();
    float mTimeSinceLastEvent;                                // +0x04
    int   m08;                                                // +0x08
    double GetEventFrequency(uint64 deltaMs);                 // 0x0100fbc0
    void*  TryCreateMission(void* pMission, int param);       // 0x0100fdb0
};

} // namespace SP

// ---- missions ------------------------------------------------------------------------------
struct IMission {
    virtual void vf0();
    virtual void* Create(void* pTarget, int param);           // +0x04
};

// ---- artifact creation ---------------------------------------------------------------------
struct ResKey {
    uint mId;                                                 // +0x00
    uint mType;                                               // +0x04
    uint mSub;                                                // +0x08
};
struct Vec3 {
    float x;
    float y;
    float z;
};

extern Vec3   g_planetEntryPos;                               // 0x016dc79c
extern ResKey g_nullResKey;                                   // 0x016dc7cc

struct cPropertyManager {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual bool GetPropertyList(uint a, uint b, void** out);  // +0x2c
};
cPropertyManager* __cdecl PropertyManager();                  // 0x0067de30

struct cSPToolManager {
    void GetRandomDiscoverableTool(ResKey* out);               // 0x010513a0
    int  GetChargesForDiscoverableTool(ResKey* key);           // 0x0104e470
};
cSPToolManager* __cdecl ToolManager();                        // 0x00b3d390

void BuildPlanetEntry(void* pSelf, int mode, ResKey* key, int charges, int a, Vec3 pos, int b);  // 0x00c731a0

inline void ReleaseVt4(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[1])(p);
}
inline void ResetRef(void** slot)
{
    void* p = *slot;
    if (p) {
        *slot = 0;
        ReleaseVt4(p);
    }
}

struct ArtifactSlot {
    char  mPad00[0x12];                                       // +0x00
    uchar mType;                                              // +0x12
    char  mPad13[0x28 - 0x13];                                // +0x13
    uchar mFlags;                                             // +0x28
    char  mPad29[0x2c - 0x29];                                // +0x29
};
struct CreateArtifact {
    char          mPad00[0x134];                              // +0x000
    ArtifactSlot* mpSlotsBegin;                               // +0x134
    ArtifactSlot* mpSlotsEnd;                                 // +0x138
    static int Start(CreateArtifact* pArtifact);              // 0x0100f7c0
};

// ---- heap helpers --------------------------------------------------------------------------
struct cRefCounted {
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
};
struct cAutoRef {
    cRefCounted* mpObject;                                    // +0x00
    cAutoRef() {}
    cAutoRef(const cAutoRef& other)
    {
        mpObject = other.mpObject;
        if (mpObject)
            mpObject->AddRef();
    }
    ~cAutoRef()
    {
        if (mpObject)
            mpObject->Release();
    }
};

struct BioProtectorSort {
    float mX;                                                 // +0x00
    float mY;                                                 // +0x04
    float mZ;                                                 // +0x08
    bool operator()(void* pLeft, void* pRight);               // 0x0100dc20
};

struct BioProtectorSortInline {
    float mX;                                                 // +0x00
    float mY;                                                 // +0x04
    float mZ;                                                 // +0x08
    float Distance(void* pNoun) const
    {
        float* pCities = ((cGameNounOwner*)pNoun)->GetNounManager()->GetCities();
        float dx = pCities[0] - mX;
        float dy = pCities[1] - mY;
        float dz = pCities[2] - mZ;
        return dx * dx + dy * dy + dz * dz;
    }
    bool operator()(void* pLeft, void* pRight)
    {
        return Distance(pLeft) > Distance(pRight);
    }
};

void SiftPlanetHeap(void** pArray, int nTop, int nHole, cAutoRef value, int (*pCompare)(void*, void*));  // 0x01022e50
void PromotePlanetHeap(void** pArray, int nTop, int nHole, cAutoRef value, BioProtectorSort compare);    // 0x0100f130
void PromotePlanetHeapDist(void** pArray, int nTop, int nHole, cAutoRef value, BioProtectorSortInline compare);  // 0x0100efc0

// ===========================================================================================
// @ 0x0100f3e0
double SP::PirateRaidPlunderEvent::GetEventFrequency(uint64 deltaMs)
{
    mTimeSinceLastRaidMSec += deltaMs;
    float fRate = 0.0f;
    Property* p;
    if (gSimUniverse->mpTuning && gSimUniverse->mpTuning->GetProperty(0x397a073, &p) && p->mType == 13)
        fRate = *p->GetFloat();
    if ((double)mTimeSinceLastRaidMSec <= (double)(fRate * 1000.0f))
        return 0.0f;
    fRate = 0.0f;
    if (gSimUniverse->mpTuning && gSimUniverse->mpTuning->GetProperty(0x397a072, &p) && p->mType == 13)
        fRate = *p->GetFloat();
    if (((SpaceGame*)SpaceGameGet())->mFlags & 0x200)
        fRate = ((SpaceGame*)SpaceGameGet())->GetRaidSpeedFactor(9) * fRate;
    fRate = ((cTerrainEditor*)NounManager(0xc42edf05))->GetCurrentTerrainSphere()->GetRadius() * fRate;
    SpaceGameData* pData = ((SpaceGame*)SpaceGameGet())->mpData;
    IntVector* pPlanets = &pData->mPlanets;
    int nPlanets = pPlanets->mpEnd - pPlanets->mpBegin;
    int nRoutes = StarManagerNoArg()->GetTradeRouteManager()->GetNumberOfPlayerTradeRoutes();
    int nTotal = nRoutes + nPlanets;
    if (nTotal <= 0)
        return 0.0f;
    fRate = fRate / (float)nTotal;
    if (0.0f < fRate) {
        fRate = (float)(1.0 - exp((double)deltaMs / fRate * -0.000301030028));
        return fRate;
    }
    return 0.0f;
}

// ===========================================================================================
// @ 0x0100f600
double SP::PirateRaidAllyEvent::GetEventFrequency(uint64 deltaMs)
{
    mTimeSinceLastRaidMSec += deltaMs;
    float fRate = 0.0f;
    Property* p;
    if (gSimUniverse->mpTuning && gSimUniverse->mpTuning->GetProperty(0x39620ae, &p) && p->mType == 13)
        fRate = *p->GetFloat();
    if ((double)(fRate * 1000.0f) < (double)mTimeSinceLastRaidMSec) {
        SpaceGameData* pData = ((SpaceGame*)SpaceGameGet())->mpData;
        IntVector* pNouns = &pData->mList18;
        if (pNouns->mpBegin != pNouns->mpEnd) {
            fRate = 0.0f;
            if (gSimUniverse->mpTuning && gSimUniverse->mpTuning->GetProperty(0x39620a6, &p) && p->mType == 13)
                fRate = *p->GetFloat();
            if (((SpaceGame*)SpaceGameGet())->mFlags & 0x200)
                fRate = ((SpaceGame*)SpaceGameGet())->GetRaidSpeedFactor(9) * fRate;
            double dRadius = ((cTerrainEditor*)NounManager(0xc42edf05))->GetCurrentTerrainSphere()->GetRadius();
            double dScale = dRadius * fRate;
            if (0.0 < dScale)
                return (float)(1.0 - exp((double)deltaMs / dScale * -0.000301030028));
        }
    }
    return 0.0f;
}

// ===========================================================================================
// @ 0x0100f7c0
int CreateArtifact::Start(CreateArtifact* pArtifact)
{
    int nSlots = (int)(pArtifact->mpSlotsEnd - pArtifact->mpSlotsBegin);
    int n = 0;
    uchar* p = (uchar*)pArtifact->mpSlotsBegin;
    for (int i = 0; i < nSlots; ++i, p += 0x2c) {
        if ((p[0x28] & 8) && p[0x12] == 2)
            ++n;
    }
    void* pList = 0;
    cPropertyManager* pManager = PropertyManager();
    ResetRef(&pList);
    pManager->GetPropertyList(0x3e9793b5, 0x2ae0c7e, &pList);
    int nMax = 1;
    if (pList != 0) {
        Property* pProperty;
        if (((cPropertyList*)pList)->GetProperty(0x2e05842, &pProperty) && pProperty->mType == 9)
            nMax = *pProperty->GetInt();
    }
    if (n < nMax) {
        cSPToolManager* pTools = ToolManager();
        ResKey key;
        pTools->GetRandomDiscoverableTool(&key);
        if (key.mId != g_nullResKey.mId || key.mType != g_nullResKey.mType || key.mSub != g_nullResKey.mSub) {
            int nCharges = pTools->GetChargesForDiscoverableTool(&key);
            BuildPlanetEntry(pArtifact, 2, &key, nCharges, 0, g_planetEntryPos, 0);
        }
    }
    if (pList)
        ReleaseVt4(pList);
    return 0;
}

// ===========================================================================================
// @ 0x0100fb00
uchar cSimulatorUniverse::HasVisibleAvatar(void* pNoun)
{
    if (!pNoun)
        return false;
    if (((cGameNounOwner*)pNoun)->GetNounType() != 5)
        return false;
    cGameNounManager* pNouns = ((cGameNounOwner*)pNoun)->GetNounManager();
    cStarManager* pStars = StarManager(pNouns->GetAvatar());
    int nEmpire = pStars->GetEmpireByID();
    if (!nEmpire)
        return false;
    if (nEmpire == (int)FUN_01021300()) {
        void* pPlanet = 0;
        StarManager(pNoun)->GetOrActivatePlanet(&pPlanet);
        double dValue = FUN_0100d410(pPlanet);
        if ((double)m118 <= dValue) {
            if (pPlanet)
                PlanetRelease(pPlanet);
            return true;
        }
        if (pPlanet)
            PlanetRelease(pPlanet);
        return false;
    }
    if ((*(uint*)(nEmpire + 0x50) >> 6) & 1)
        return false;
    return true;
}

// ===========================================================================================
// @ 0x0100fbc0
double SP::HappinessDisasterEvent::GetEventFrequency(uint64 deltaMs)
{
    float fDelta = (float)deltaMs;
    mTimeSinceLastEvent = mTimeSinceLastEvent + fDelta;
    SpaceGameData* pData = ((SpaceGame*)SpaceGameGet())->mpData;
    IntVector* pPlanets = &pData->mPlanets;
    int nPlanets = pPlanets->mpEnd - pPlanets->mpBegin;
    if (nPlanets <= 0)
        return 0.0f;
    void* pPlanet = (void*)pPlanets->mpBegin[g_random.RandomUint32Uniform(nPlanets)];
    if (!((cGameNounOwner*)pPlanet)->FUN_00b8d9a0())
        return 0.0f;
    void* pRef = 0;
    StarManager(pPlanet)->GetOrActivatePlanet(&pRef);
    if (((cPlanetRecord*)pRef)->mUncolonized != 0) {
        ResetPlanet(&pRef);
        return 0.0f;
    }
    float fRate = 0.0f;
    GetPropertyT_int(gSimUniverse->mpTuning, 0x4f3b63e, (int*)&fRate);
    if (mTimeSinceLastEvent <= fRate * 1000.0f) {
        ResetPlanet(&pRef);
        return 0.0f;
    }
    GetPropertyT_int(gSimUniverse->mpTuning, 0x4f3b63f, (int*)&fRate);
    if (FUN_00b8e040(pPlanet, g_placeHappinessBooster))
        fRate = fRate * 2.0f;
    if (((SpaceGame*)SpaceGameGet())->mFlags & 0x10)
        fRate = fRate * 3.0f;
    fRate = ((cTerrainEditor*)NounManager(0xc42edf05))->GetCurrentTerrainSphere()->GetRadius() * fRate;
    m08 = ((cStarRecordRef*)pPlanet)->GetCommContext();
    fRate = (float)FUN_0100d500(fDelta * 0.001f, fRate);
    if (pRef)
        PlanetRelease(pRef);
    return fRate;
}

// ===========================================================================================
// @ 0x0100fdb0
void* SP::HappinessDisasterEvent::TryCreateMission(void* pMission, int param)
{
    mTimeSinceLastEvent = 0.0f;
    int nEmpire = m08;
    void* pPlanet = 0;
    if (nEmpire != 0) {
        void* pRecord = StarManager((void*)nEmpire)->GetRecord();
        if (pRecord)
            ((cGameNounOwner*)pRecord)->AddRef();
        void* pResult = ((IMission*)pMission)->Create(pRecord, param);
        if (pRecord)
            ((cGameNounOwner*)pRecord)->Release();
        ResetPlanet(&pPlanet);
        return pResult;
    }
    SpaceGameData* pData = ((SpaceGame*)SpaceGameGet())->mpData;
    IntVector* pPlanets = &pData->mPlanets;
    int nPlanets = pPlanets->mpEnd - pPlanets->mpBegin;
    for (int i = 0; i < nPlanets; ++i) {
        void* pNoun = (void*)pPlanets->mpBegin[i];
        if (!((cGameNounOwner*)pNoun)->FUN_00b8d9a0())
            continue;
        ResetPlanet(&pPlanet);
        StarManager(pNoun)->GetOrActivatePlanet(&pPlanet);
        if (((cPlanetRecord*)pPlanet)->mUncolonized == 0) {
            void* pResult = ((IMission*)pMission)->Create(pNoun, param);
            if (pPlanet)
                PlanetRelease(pPlanet);
            return pResult;
        }
    }
    if (pPlanet)
        PlanetRelease(pPlanet);
    return 0;
}

// ===========================================================================================
// @ 0x0100fee0
void FUN_0100fee0(void** pArray, int nTop, int nLen, int nHole, cAutoRef value, int (*pCompare)(void*, void*))
{
    int nHoleIndex = nHole;
    int nChild = nHoleIndex * 2 + 2;
    while (nChild < nLen) {
        if (pCompare(pArray[nChild], pArray[nChild - 1]))
            --nChild;
        cRefCounted* pNew = (cRefCounted*)pArray[nChild];
        cRefCounted* pOld = (cRefCounted*)pArray[nHoleIndex];
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pArray[nHoleIndex] = pNew;
            if (pOld)
                pOld->Release();
        }
        nHoleIndex = nChild;
        nChild = nChild * 2 + 2;
    }
    if (nChild == nLen) {
        cRefCounted* pNew = (cRefCounted*)pArray[nChild - 1];
        cRefCounted* pOld = (cRefCounted*)pArray[nHoleIndex];
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pArray[nHoleIndex] = pNew;
            if (pOld)
                pOld->Release();
        }
        nHoleIndex = nChild - 1;
    }
    SiftPlanetHeap(pArray, nTop, nHoleIndex, value, pCompare);
}

// ===========================================================================================
// @ 0x0100ffc0
void AdjustPlanetHeapDist(void** pArray, int nTop, int nLen, int nHole, cAutoRef value, float x, float y, float z)
{
    BioProtectorSortInline compare;
    compare.mX = x;
    compare.mY = y;
    compare.mZ = z;
    int nHoleIndex = nHole;
    int nChild = nHoleIndex * 2 + 2;
    while (nChild < nLen) {
        if (compare(pArray[nChild], pArray[nChild - 1]))
            --nChild;
        cRefCounted* pNew = (cRefCounted*)pArray[nChild];
        cRefCounted* pOld = (cRefCounted*)pArray[nHoleIndex];
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pArray[nHoleIndex] = pNew;
            if (pOld)
                pOld->Release();
        }
        nHoleIndex = nChild;
        nChild = nChild * 2 + 2;
    }
    if (nChild == nLen) {
        cRefCounted* pNew = (cRefCounted*)pArray[nChild - 1];
        cRefCounted* pOld = (cRefCounted*)pArray[nHoleIndex];
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pArray[nHoleIndex] = pNew;
            if (pOld)
                pOld->Release();
        }
        nHoleIndex = nChild - 1;
    }
    PromotePlanetHeapDist(pArray, nTop, nHoleIndex, value, compare);
}

// ===========================================================================================
// @ 0x01010190
void AdjustPlanetHeap(void** pArray, int nTop, int nLen, int nHole, cAutoRef value, BioProtectorSort compare)
{
    int nHoleIndex = nHole;
    int nChild = nHoleIndex * 2 + 2;
    while (nChild < nLen) {
        if (compare(pArray[nChild], pArray[nChild - 1]))
            --nChild;
        cRefCounted* pNew = (cRefCounted*)pArray[nChild];
        cRefCounted* pOld = (cRefCounted*)pArray[nHoleIndex];
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pArray[nHoleIndex] = pNew;
            if (pOld)
                pOld->Release();
        }
        nHoleIndex = nChild;
        nChild = nChild * 2 + 2;
    }
    if (nChild == nLen) {
        cRefCounted* pNew = (cRefCounted*)pArray[nChild - 1];
        cRefCounted* pOld = (cRefCounted*)pArray[nHoleIndex];
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            pArray[nHoleIndex] = pNew;
            if (pOld)
                pOld->Release();
        }
        nHoleIndex = nChild - 1;
    }
    PromotePlanetHeap(pArray, nTop, nHoleIndex, value, compare);
}

// ===========================================================================================
// @ 0x010103f0
double FUN_010103f0(void* pObject)
{
    float fTotal = 0.0f;
    if (!gSimUniverse->HasVisibleAvatar(pObject))
        return 0.0f;
    int nGroups = (*(int*)((char*)pObject + 0x160) - *(int*)((char*)pObject + 0x15c)) >> 2;
    for (int i = 0; i < nGroups; ++i) {
        uchar* pGroup = (uchar*)((cStarRecordRef*)pObject)->GetGroup(i);
        int nItems = (*(int*)(pGroup + 0x40) - *(int*)(pGroup + 0x3c)) >> 2;
        for (int j = 0; j < nItems; ++j)
            fTotal = fTotal + ((cArtifactItem*)*(void**)(*(int*)(pGroup + 0x3c) + j * 4))->GetValue();
    }
    cGameNounManager* pNouns = ((cGameNounOwner*)pObject)->GetNounManager();
    void* pAvatar = pNouns->mpAvatar70;
    cStarManager* pStars = StarManager(pAvatar);
    cSpaceTradeRouteManager* pRoutes = pStars->GetTradeRouteManager();
    if (pRoutes->FUN_01037d90())
        fTotal = fTotal * 1.5f;
    return fTotal;
}
