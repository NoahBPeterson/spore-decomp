// Slice s0100e150: SP simulator-universe event helpers (universe events, raid bookkeeping and the
// weighted-index helper).  Reconstructed from the retail disassembly; the universe keeps its tuning
// property list in a smart pointer at +0x10 and its event sub-objects inline from +0x34 on.
// Field offsets are the retail ones.
#include "types.h"
#include <math.h>

typedef unsigned int size_t;

// ---- property access ---------------------------------------------------------------------
struct Property {
    char mPad[0x12];
    uint16_t mType;                                           // +0x12
    int* GetInt();                                            // 0x0041e990
    float* GetFloat();                                        // 0x0041ea70
};
struct cPropertyList {
    virtual void vf0();
    virtual int Release();                                    // +0x04
    virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5(); virtual void vf6();
    virtual void vf7(); virtual void vf8();
    virtual bool GetProperty(uint32_t id, Property** out);    // +0x24
};
struct PropListPtr {
    cPropertyList* mpObject;
};

// ---- random / global helpers ---------------------------------------------------------------
struct RandomLinearCongruential {
    unsigned RandomUint32Uniform(unsigned n);                 // 0x00a68fb0
    double RandomDoubleUniform();                             // 0x009360d0
};
extern RandomLinearCongruential g_random;                     // 0x01601760

void* SpaceGameGet();                                         // 0x01002bd0
int __stdcall GetPlayerHomePlanet(int arg);                   // 0x01021370

// ---- game-object helpers -------------------------------------------------------------------
struct cGameNounManager {
    void* GetAvatar();                                        // 0x00b1fdb0
    float* GetCities();                                       // 0x005c65e0
};
struct cGameNounOwner {
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
    cGameNounManager* GetNounManager();                       // 0x00b8de30
};
struct cStarRecordRef {
    int GetCommContext();                                     // 0x00ce6950
};
struct cStarManager {
    void* GetEmpireByID();                                    // 0x00ba9370
    void* GetRelationshipCore();                              // 0x00885c90
};
struct cRelationshipManager {
    bool IsAtWar(void* core);                                 // 0x00d01b50
};
void* RelationshipManager(void* core);                        // 0x00b3d2c0
struct cPlayerEmpire {
    char mPad70[0x70];
    int mHostileCount;                                        // +0x70
    int mHostileEnd;                                          // +0x74
    char mPad78[0x84 - 0x78];
    int mEmpireId;                                            // +0x84
};
cPlayerEmpire* FUN_01021300();                                // 0x01021300
float RaidFrequencyFromTime(float seconds, int thresholdMSec);   // 0x0100d500
void GetPropertyInt(cPropertyList* list, uint32_t id, int* out);   // 0x0040cf10
struct cSPMission {
    void Init(int);                                           // 0x00c5b370
    void SetTarget(int);                                      // 0x00c47180
    void SetEmpire(int);                                      // 0x00c5b390
    void Accept();                                            // 0x00c485b0
};
struct IMission;
struct cSPMissionManager {
    IMission* CreateMissionFromID(unsigned id, int source, void* empire, int flag);   // 0x00fec590
};
void* GetMissionManager();                                    // 0x00feb9f0
cStarManager* __stdcall StarManager(void* avatar);            // 0x00b3d2a0

// ---- simulator universe --------------------------------------------------------------------
struct SimUniverseBase {
    virtual void vf0();
    virtual void vf1();
};
struct SimUniverseSecond {
    virtual void vf0();
    virtual void vf1();
};

struct cSimulatorUniverse : SimUniverseBase, SimUniverseSecond {
    char mPad08[8];                                           // +0x08
    PropListPtr mTuning;                                      // +0x10
    int m14;                                                  // +0x14
    char mPad18[0x110 - 0x18];                                // +0x18
    void* mProperty;                                          // +0x110
    uint32_t mPropertyId;                                     // +0x114
    char mPad118[0x128 - 0x118];                              // +0x118
    char* mp128;                                              // +0x128
    char* mp12c;                                              // +0x12c

    void SetPropertyRef(void* def);                           // 0x0100e6e0
    bool FindEmbassyEntry(char* pUniverse, cStarRecordRef* pRef);   // 0x0100e730
    bool RemoveRaid(int param1, int pNoun, int pEmpire);      // 0x0100e780
};
extern cSimulatorUniverse* gSimUniverse;                      // 0x016dc798

// ---- event sub-objects ---------------------------------------------------------------------
struct GrobWarAttackEvent {
    virtual void f();
    int a;                                                    // +0x04
    float mFreqGrobExtremelyAware;                            // +0x08
    float mFreqGrobVeryAware;                                 // +0x0c
    float mFreqGrobAware;                                     // +0x10
    int mMinTimeBetweenAttacksMSec;                           // +0x14
    bool Init();                                              // 0x0100e150
};

struct GrobTeaseRaidEvent {
    virtual void f();
    unsigned __int64 mTimeSinceLastRaidMSec;                  // +0x08
    float GetEventFrequency(unsigned __int64 deltaMs);        // 0x0100e270
};

struct ArtifactEvent {
    virtual void f();
    unsigned mTimeSinceLastArtifactMSec;                      // +0x04
    float GetEventFrequency(unsigned __int64 deltaMs);        // 0x0100e550
};

struct PirateRaidEvent {
    virtual void f();
    unsigned __int64 mTimeSinceLastRaidMSec;                  // +0x08
    float GetEventFrequency(unsigned __int64 deltaMs);        // 0x0100f1e0
};

struct cTerrainSphere {
    float GetRadius();                                        // 0x00c75c30
};
struct cTerrainEditor {
    cTerrainSphere* GetCurrentTerrainSphere();                // 0x00f67d90
};
cTerrainEditor* NounManager(unsigned id);                     // 0x00b3d300

struct SpaceGame {
    char mPadC4[0xc4];
    uint32_t mFlags;                                          // +0xc4
    float GetRaidSpeedFactor(int mode);                       // 0x01005c60
};

struct IntVector {
    int* mpBegin;                                             // +0x00
    int* mpEnd;                                               // +0x04
};

struct IMission {
    virtual void vf0();
    virtual int Create(int a, int b);                         // +0x04
    virtual void vf2();                                       // +0x08
    virtual cSPMission* GetSPMission(unsigned id);            // +0x0c
};

struct SpaceGameData {
    char mPad[0x18];
    IntVector mList;                                          // +0x18
};

struct PirateRaidAllyEvent {
    virtual void f();
    char mPad04[4];
    int mTimeLo;                                              // +0x08
    int mTimeHi;                                              // +0x0c
    int TryCreateMission(IMission* pMission, int param);      // 0x0100e3c0
};

struct IPlanetMission {
    virtual void vf0();
    virtual int Create(int planet);                           // +0x04
};

struct BiosphereCollapseEvent {
    virtual void f();
    float mTimeSinceLastEvent;                                // +0x04
    int TryCreateMission(IPlanetMission* pMission, int param);   // 0x0100e690
};

// @ 0x0100e150
bool GrobWarAttackEvent::Init()
{
    Property* p;
    {
        cPropertyList* pList = gSimUniverse->mTuning.mpObject;
        if (pList && pList->GetProperty(0x31e94c1, &p) && p->mType == 13)
            mFreqGrobExtremelyAware = *p->GetFloat();
    }
    {
        cPropertyList* pList = gSimUniverse->mTuning.mpObject;
        if (pList && pList->GetProperty(0x31e94c2, &p) && p->mType == 13)
            mFreqGrobVeryAware = *p->GetFloat();
    }
    {
        cPropertyList* pList = gSimUniverse->mTuning.mpObject;
        if (pList && pList->GetProperty(0x31e94c3, &p) && p->mType == 13)
            mFreqGrobAware = *p->GetFloat();
    }
    float secs;
    {
        cPropertyList* pList = gSimUniverse->mTuning.mpObject;
        if (pList && pList->GetProperty(0x31e94c4, &p) && p->mType == 13)
            secs = *p->GetFloat();
    }
    mMinTimeBetweenAttacksMSec = (int)(secs * 1000.0f);
    return true;
}

// @ 0x0100e270
float GrobTeaseRaidEvent::GetEventFrequency(unsigned __int64 deltaMs)
{
    mTimeSinceLastRaidMSec += deltaMs;
    cPlayerEmpire* pEmpire = FUN_01021300();
    cStarManager* stars = StarManager((void*)pEmpire->mEmpireId);
    void* core = stars->GetRelationshipCore();
    bool atWar = ((cRelationshipManager*)RelationshipManager(core))->IsAtWar(core);
    float secs = 0.0f;
    if (pEmpire->mHostileCount != pEmpire->mHostileEnd && !atWar) {
        Property* p;
        if (gSimUniverse->mTuning.mpObject &&
            gSimUniverse->mTuning.mpObject->GetProperty(0x31e94c0, &p) && p->mType == 13)
            secs = *p->GetFloat();
        if ((double)mTimeSinceLastRaidMSec > (double)secs * 1000.0) {
            int threshold = 0;
            GetPropertyInt(gSimUniverse->mTuning.mpObject, 0x31e94b9, &threshold);
            return RaidFrequencyFromTime((float)((double)mTimeSinceLastRaidMSec * 0.001f), threshold);
        }
    }
    return 0.0f;
}

// @ 0x0100e3c0
int PirateRaidAllyEvent::TryCreateMission(IMission* pMission, int param)
{
    char* p = (char*)SpaceGameGet();
    IntVector* list = &(*(SpaceGameData**)(p + 0x30))->mList;
    if ((list->mpEnd - list->mpBegin) != 0 && list->mpBegin != list->mpEnd) {
        int v = list->mpBegin[g_random.RandomUint32Uniform(list->mpEnd - list->mpBegin)];
        if (v) {
            mTimeLo = 0;
            mTimeHi = 0;
            return pMission->Create(v, param);
        }
    }
    return 0;
}

// @ 0x0100e690
int BiosphereCollapseEvent::TryCreateMission(IPlanetMission* pMission, int param)
{
    mTimeSinceLastEvent = 0.0f;
    char* p = (char*)SpaceGameGet();
    char* u = *(char**)(p + 0x30);
    if ((unsigned)((*(int*)(u + 0x30) - *(int*)(u + 0x2c)) >> 2) <= 1 &&
        *(int*)(u + 0x18) == *(int*)(u + 0x1c))
        return 0;
    return pMission->Create(GetPlayerHomePlanet(param));
}

// @ 0x0100e6e0
void cSimulatorUniverse::SetPropertyRef(void* def)
{
    if (mTuning.mpObject) {
        Property* pResult;
        mTuning.mpObject->GetProperty(0x5a5e5bc, &pResult);
        mProperty = pResult;
        mPropertyId = 0x5a5e5bc;
        return;
    }
    mProperty = def;
    mPropertyId = 0x5a5e5bc;
}

// @ 0x0100e730
bool cSimulatorUniverse::FindEmbassyEntry(char* pUniverse, cStarRecordRef* pRef)
{
    char* p = mp128;
    char* end = mp12c;
    while (p != end) {
        if (*(int*)(p + 4) == pRef->GetCommContext() &&
            *(unsigned*)p == *(unsigned*)(pUniverse + 0x84))
            return true;
        p += 0x28;
    }
    return false;
}

// @ 0x0100e430
struct GenericDisaster {
    float GetEventFrequency(unsigned __int64 deltaMs);        // 0x0100e430
};

float GenericDisaster::GetEventFrequency(unsigned __int64 deltaMs)
{
    float secs = 0.0f;
    char* pGame = (char*)SpaceGameGet();
    char* pData = *(char**)(pGame + 0x30);
    int count = (*(int*)(pData + 0x30) - *(int*)(pData + 0x2c)) >> 2;
    if (count < 1)
        return 0.0f;
    float fraction = (float)(count - *(int*)(pData + 0x104)) / (float)count;
    Property* p;
    if (gSimUniverse->mTuning.mpObject &&
        gSimUniverse->mTuning.mpObject->GetProperty(0x319266b, &p) && p->mType == 13)
        secs = *p->GetFloat();
    float area = ((cTerrainEditor*)NounManager(0xc42edf05))->GetCurrentTerrainSphere()->GetRadius() * secs;
    if (0.0f < area)
        return (float)(1.0 - exp((double)deltaMs / area * -0.000301030028)) * fraction;
    return 0.0f * fraction;
}

// @ 0x0100e550
float ArtifactEvent::GetEventFrequency(unsigned __int64 deltaMs)
{
    mTimeSinceLastArtifactMSec += (unsigned)deltaMs;
    float secs = 0.0f;
    Property* p;
    if (gSimUniverse->mTuning.mpObject &&
        gSimUniverse->mTuning.mpObject->GetProperty(0x2e0583d, &p) && p->mType == 13)
        secs = *p->GetFloat();
    if ((double)mTimeSinceLastArtifactMSec <= (double)secs * 1000.0f)
        return 0.0f;
    if (gSimUniverse->mTuning.mpObject &&
        gSimUniverse->mTuning.mpObject->GetProperty(0x2e057f0, &p) && p->mType == 13) {
        float scale = *p->GetFloat();
        if (0.0f < scale)
            return (float)(1.0 - exp((double)deltaMs / scale * -0.000301030028));
    }
    return 0.0f;
}

// @ 0x0100e780
bool cSimulatorUniverse::RemoveRaid(int param1, int pNoun, int pEmpire)
{
    void* mgr = GetMissionManager();
    if (!mgr)
        return false;
    if (pNoun) {
        cGameNounManager* nouns = ((cGameNounOwner*)pNoun)->GetNounManager();
        void* avatar = nouns->GetAvatar();
        cStarManager* stars = StarManager(avatar);
        void* empire = stars->GetEmpireByID();
        IMission* mission = ((cSPMissionManager*)mgr)->CreateMissionFromID(0xa4b0a2df, pNoun, empire, 0);
        if (mission) {
            cSPMission* sp = mission->GetSPMission(0x3960c0a);
            if (sp) {
                sp->Init(0);
                sp->SetTarget(pNoun);
                sp->SetEmpire(pEmpire);
                sp->Accept();
            }
        }
    }
    return true;
}

// @ 0x0100e970
// Weighted pick: choose an index whose weight window contains a uniform draw from the total weight.
int PickWeightedIndex(IntVector* pWeights)
{
    double total = 0.0;
    for (int* it = pWeights->mpBegin; it != pWeights->mpEnd; ++it)
        total += (unsigned)*it;
    if (0.0 < total) {
        double draw = (double)g_random.RandomDoubleUniform() * total;
        if (draw < total) {
            double sum = 0.0;
            int index = 0;
            for (int* it = pWeights->mpBegin; it != pWeights->mpEnd; ++it, ++index) {
                sum += (unsigned)*it;
                if (draw < sum)
                    return index;
            }
        }
        return (int)(pWeights->mpEnd - pWeights->mpBegin) - 1;
    }
    return (int)(pWeights->mpEnd - pWeights->mpBegin);
}

// @ 0x0100ea20
// Insertion sort of noun references by squared distance of their city position to a world point.
void SortNounsByDistance(cGameNounOwner** pBegin, cGameNounOwner** pEnd, float x, float y, float z)
{
    if (pBegin == pEnd)
        return;
    for (cGameNounOwner** pInsert = pBegin + 1; pInsert != pEnd; ++pInsert) {
        cGameNounOwner* pCurrent = *pInsert;
        if (pCurrent)
            pCurrent->AddRef();
        cGameNounOwner** pSlot = pInsert;
        while (pSlot != pBegin) {
            float* pC = pCurrent->GetNounManager()->GetCities();
            float dx = pC[0] - x;
            float dy = pC[1] - y;
            float dz = pC[2] - z;
            cGameNounOwner* pPrevious = pSlot[-1];
            float* pP = pPrevious->GetNounManager()->GetCities();
            float px = pP[0] - x;
            float py = pP[1] - y;
            float pz = pP[2] - z;
            if (pz * pz + py * py + px * px <= dz * dz + dx * dx + dy * dy)
                break;
            if (pPrevious != *pSlot) {
                if (pPrevious)
                    pPrevious->AddRef();
                cGameNounOwner* pOld = *pSlot;
                *pSlot = pPrevious;
                if (pOld)
                    pOld->Release();
            }
            --pSlot;
        }
        cGameNounOwner* pOld = *pSlot;
        if (pCurrent != pOld) {
            if (pCurrent)
                pCurrent->AddRef();
            *pSlot = pCurrent;
            if (pOld)
                pOld->Release();
        }
        if (pCurrent)
            pCurrent->Release();
    }
}

// @ 0x0100ebb0
// Same distance ordering, written as a make-room loop over the whole range.
void SortNounsByDistanceInPlace(cGameNounOwner** pBegin, cGameNounOwner** pEnd, float x, float y, float z)
{
    for (; pBegin != pEnd; ++pBegin) {
        cGameNounOwner* pCurrent = *pBegin;
        if (pCurrent)
            pCurrent->AddRef();
        cGameNounOwner** pSlot = pBegin;
        for (;;) {
            float* pC = pCurrent->GetNounManager()->GetCities();
            float dx = pC[0] - x;
            float dy = pC[1] - y;
            float dz = pC[2] - z;
            cGameNounOwner* pPrevious = pSlot[-1];
            float* pP = pPrevious->GetNounManager()->GetCities();
            float px = pP[0] - x;
            float py = pP[1] - y;
            float pz = pP[2] - z;
            if (pz * pz + py * py + px * px <= dz * dz + dx * dx + dy * dy)
                break;
            if (pPrevious != *pSlot) {
                if (pPrevious)
                    pPrevious->AddRef();
                cGameNounOwner* pOld = *pSlot;
                *pSlot = pPrevious;
                if (pOld)
                    pOld->Release();
            }
            --pSlot;
        }
        cGameNounOwner* pOld = *pSlot;
        if (pCurrent != pOld) {
            if (pCurrent)
                pCurrent->AddRef();
            *pSlot = pCurrent;
            if (pOld)
                pOld->Release();
        }
        if (pCurrent)
            pCurrent->Release();
    }
}

// @ 0x0100ed20
struct NounCompare {
    bool Less(cGameNounOwner* pA, cGameNounOwner* pB);          // 0x0100dc20
};

void SortNounsByCompare(cGameNounOwner** pBegin, cGameNounOwner** pEnd)
{
    if (pBegin == pEnd)
        return;
    for (cGameNounOwner** pInsert = pBegin + 1; pInsert != pEnd; ++pInsert) {
        cGameNounOwner* pCurrent = *pInsert;
        if (pCurrent)
            pCurrent->AddRef();
        NounCompare compare;
        cGameNounOwner** pSlot = pInsert;
        while (pSlot != pBegin && compare.Less(pCurrent, pSlot[-1])) {
            cGameNounOwner* pPrevious = pSlot[-1];
            if (pPrevious != *pSlot) {
                if (pPrevious)
                    pPrevious->AddRef();
                cGameNounOwner* pOld = *pSlot;
                *pSlot = pPrevious;
                if (pOld)
                    pOld->Release();
            }
            --pSlot;
        }
        cGameNounOwner* pOld = *pSlot;
        if (pCurrent != pOld) {
            if (pCurrent)
                pCurrent->AddRef();
            *pSlot = pCurrent;
            if (pOld)
                pOld->Release();
        }
        if (pCurrent)
            pCurrent->Release();
    }
}

// @ 0x0100edf0
// Same comparator ordering, written as a make-room loop over the whole range.
void SortNounsByCompareInPlace(cGameNounOwner** pBegin, cGameNounOwner** pEnd)
{
    for (; pBegin != pEnd; ++pBegin) {
        cGameNounOwner* pCurrent = *pBegin;
        if (pCurrent)
            pCurrent->AddRef();
        NounCompare compare;
        bool less = compare.Less(pCurrent, pBegin[-1]);
        cGameNounOwner** pSlot = pBegin;
        while (less) {
            cGameNounOwner* pPrevious = pSlot[-1];
            if (pPrevious != *pSlot) {
                if (pPrevious)
                    pPrevious->AddRef();
                cGameNounOwner* pOld = *pSlot;
                *pSlot = pPrevious;
                if (pOld)
                    pOld->Release();
            }
            less = compare.Less(pCurrent, pSlot[-2]);
            --pSlot;
        }
        cGameNounOwner* pOld = *pSlot;
        if (pCurrent != pOld) {
            if (pCurrent)
                pCurrent->AddRef();
            *pSlot = pCurrent;
            if (pOld)
                pOld->Release();
        }
        if (pCurrent)
            pCurrent->Release();
    }
}

// @ 0x0100efc0
// Sift the value at pArray[nHole] up towards the root of the distance heap.
void PromoteHeap(cGameNounOwner** pArray, int topIndex, int nHole, cGameNounOwner* pValue,
                 float x, float y, float z)
{
    while (nHole > topIndex) {
        int nParent = (nHole - 1) / 2;
        float* pP = pArray[nParent]->GetNounManager()->GetCities();
        float px = pP[0] - x;
        float py = pP[1] - y;
        float pz = pP[2] - z;
        float* pC = pValue->GetNounManager()->GetCities();
        float dx = pC[0] - x;
        float dy = pC[1] - y;
        float dz = pC[2] - z;
        if (pz * pz + py * py + px * px <= dz * dz + dx * dx + dy * dy)
            break;
        cGameNounOwner* pParent = pArray[nParent];
        if (pParent != pArray[nHole]) {
            if (pParent)
                pParent->AddRef();
            cGameNounOwner* pOld = pArray[nHole];
            pArray[nHole] = pParent;
            if (pOld)
                pOld->Release();
        }
        nHole = nParent;
    }
    if (pValue != pArray[nHole]) {
        if (pValue)
            pValue->AddRef();
        cGameNounOwner* pOld = pArray[nHole];
        pArray[nHole] = pValue;
        if (pOld)
            pOld->Release();
    }
    if (pValue)
        pValue->Release();
}

// @ 0x0100f1e0
float PirateRaidEvent::GetEventFrequency(unsigned __int64 deltaMs)
{
    mTimeSinceLastRaidMSec += deltaMs;
    float secs = 0.0f;
    Property* p;
    if (gSimUniverse->mTuning.mpObject &&
        gSimUniverse->mTuning.mpObject->GetProperty(0x31e761f, &p) && p->mType == 13)
        secs = *p->GetFloat();
    if ((double)mTimeSinceLastRaidMSec <= (double)secs * 1000.0)
        return 0.0f;
    char* pGame = (char*)SpaceGameGet();
    char* pData = *(char**)(pGame + 0x30);
    float averageSeconds = (float)((*(int*)(pData + 0x30) - *(int*)(pData + 0x2c)) >> 2);
    if (gSimUniverse->mTuning.mpObject &&
        gSimUniverse->mTuning.mpObject->GetProperty(0x31e7620, &p) && p->mType == 13)
        secs = *p->GetFloat();
    SpaceGame* pSpaceGame = (SpaceGame*)SpaceGameGet();
    if (pSpaceGame->mFlags & 0x200)
        secs *= ((SpaceGame*)SpaceGameGet())->GetRaidSpeedFactor(9);
    float radius = ((cTerrainEditor*)NounManager(0xc42edf05))->GetCurrentTerrainSphere()->GetRadius() * secs;
    if (0.0f < averageSeconds) {
        averageSeconds = radius / averageSeconds;
        if (0.0f < averageSeconds)
            return (float)(1.0 - exp((double)deltaMs / averageSeconds * -0.000301030028));
    }
    return 0.0f;
}
