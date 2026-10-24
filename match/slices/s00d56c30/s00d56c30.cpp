// Slice s00d56c30 - citizen spawning / tribe bookkeeping of the city simulator.
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// A tribe (CTribe) owns a small inline table of 0x198-byte scenario slots (+0x390) and the city it
// belongs to (+0xaf0).  A citizen (CCitizen) drives a grid queue (+0xb4c), an animating creature
// (+0xb54), its owner tribe (+0xfb8) and a handful of flags; the manager (CCitizenManager) keeps the
// live citizens in a pointer array (+0xa64/+0xa68) and a parallel table of 12-byte records (+0xb6c).
// Spawning a citizen seeds the tool, places the model (random angle inside the tribe's range),
// attaches it to the behaviour manager and bumps the tribe slot's counter.
//
// Byte-exact: GetEntry, SeedCitizenTool, DeactivateCitizen and ComputeVisualizedPopulation (the last
// one needs the reference-taking MaxValue: both operands are spilled and the winner is reloaded).
// The remaining four keep the retail call shapes but cl15 picks different induction pointers (see
// nonmatching.txt).  The scenario-slot table is modelled with the four entries that fit below +0xaf0.

typedef unsigned int uint;

namespace EA {
struct RandomLinearCongruential {
    uint   RandomUint32Uniform(uint nRange);     // 0x00a68fb0
    double RandomDouble();                       // 0x009360d0
};
}
extern EA::RandomLinearCongruential g_random;    // 0x01601760

struct CGridQueue;                               // 0x01593270 (s_TribeQueue)

// ---------------------------------------------------------------------------
// Animation plumbing.
struct CModel {
    char mPad00[4];
    uint mFlags;                                 // +0x04, 0x800 = hidden
};

struct CAnimatingCreature {                      // CCitizen::mpAnim (+0xb54)
    char mPad00[0x64];
    bool mbField64;                              // +0x64
    char mPad65[0x180 - 0x65];
    CModel* mpModel;                             // +0x180
    bool Detach(int nMode);                      // 0x00a02b00
};

// The citizen object (vvvv) created from a tracker/building; only the slots this file calls are named.
struct CVisualSub;                               // CCitizen sub-object at +0xc0

struct CCitizenBase {                            // virtual slots 0x00..0xe8
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();   // +0x00
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();   // +0x10
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();   // +0x20
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();   // +0x30
    virtual void s16(); virtual void s17();                                          // +0x40
    virtual void SetState(int nState);                                               // +0x48
    virtual int  GetState();                                                         // +0x4c
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();   // +0x50
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();   // +0x60
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();   // +0x70
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();   // +0x80
    virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();   // +0x90
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();   // +0xa0
    virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();   // +0xb0
    virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();   // +0xc0
    virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();   // +0xd0
    virtual void s56();                                                              // +0xe0
    virtual void SetInfo(void* pInfo);                                               // +0xe4
    virtual void InitFrom(void* pCity, int nMode, int nFlags, int nExtra);            // +0xe8
};

// Position/orientation helper that the citizen exposes at +0xc0.
struct CVisualSub {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();   // +0x00
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();   // +0x10
    virtual void s08(); virtual void s09(); virtual void s10();                      // +0x20
    virtual void* Resolve();                                                         // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();   // +0x30
    virtual void SetAngle(float fAngle);                                             // +0x40
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();   // +0x44
    virtual void s21();                                                              // +0x54
    virtual bool IsReady();                                                          // +0x58
    char mData[0x4c];
};

struct CRecord12 { char mData[12]; };

// Entry of the tribe's scenario-slot table (stride 0x198).
struct CEntry {
    char mPad00[4];
    int  mnCount;                                // +0x04
    char mPad08[0x198 - 0x08];
};

// The behaviour plumbing owner inside the citizen (passed to SP::BehaviorManager::Attach).
struct CBehaviorOwner { char mData[0x68]; };

struct CGrid;
struct CTribe;

struct CCitizen : CCitizenBase {
    char mPad004[0x58 - 0x04];                   // +0x004
    CBehaviorOwner mBehavior;                    // +0x058
    CVisualSub mVisual;                          // +0x0c0
    uint mFlags;                                 // +0x110
    char mPad114[0xb4c - 0x114];
    CGrid* mpGrid;                               // +0xb4c
    char mPadB50[4];
    CAnimatingCreature* mpAnim;                  // +0xb54
    char mPadB58[0xf90 - 0xb58];
    bool mbFieldF90;                             // +0xf90
    char mPadF91[0xfb8 - 0xf91];
    CTribe* mpTribe;                             // +0xfb8
    bool mbFieldFBC;                             // +0xfbc
    char mPadFBD[0xff0 - 0xfbd];
    int  mnState;                                // +0xff0 (last state applied to the model)

    void SetSpecializedTool(int nTool);          // 0x00c279a0
    void SetFlag(int nFlag);                     // 0x00c0d950
    void UpdateEntry(int nEntry);                // 0x00c227a0
    void ClearEntry();                           // 0x00c227c0
};

// The tribe / city-side owner of the citizen slots.
struct CTribe {
    char mPad000[0x390];
    CEntry mEntries[4];                          // +0x390, stride 0x198
    char mPad9F0[0xaf0 - 0x9f0];
    void* mpCity;                                // +0xaf0

    CEntry* GetEntry(int nIndex);                // 0x00d576b0
};

// Grid queue owned by the citizen (+0xb4c): a render/occupancy queue plus the property block at +8.
struct CGridRange {
    char mData[0x14];
    void SetRange(uint nId, int nArg, float fMax, int nArg2);   // 0x00bc97f0
};

struct CGrid {
    char mPad00[8];
    CGridRange mRange;                           // +0x08
    char mPad1C[0x5fc - 0x1c];
    int  mnField5fc;                             // +0x5fc
    void ResetQueue(CGridQueue* pQueue);         // 0x00bcb660
    void ResetQueue();                           // 0x00bcb3d0
};

extern CGridQueue g_tribeQueue;                  // 0x01593270
extern CGridQueue g_cityQueue;                   // 0x01592928
extern bool g_bTribeQueueInit;                   // 0x0169ec24
void __cdecl GridInitQueue(CGridQueue* pQueue);                     // 0x00bc8fa0
void __cdecl UpdateTimeScaled(CCitizen* pCitizen);                  // 0x00c0d3a0

struct CAnimShortcut {
    void SetTarget(CCitizen* pCitizen, int nMode);                  // 0x00b48770
};
CAnimShortcut* __cdecl GetAnimShortcut();                           // 0x00b3d310

namespace SP {
struct cCity;
struct BehaviorManager {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();   // +0x00
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();   // +0x10
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();   // +0x20
    virtual void s12(); virtual void s13(); virtual void s14();                       // +0x30
    virtual void Attach(void* pOwner);                                               // +0x3c
};
BehaviorManager* __cdecl GetBehaviorManager();                      // 0x00b3d260

struct cCityVisualizer;
cCityVisualizer* __cdecl GetVisualizer();                           // 0x00b3d480

struct cDirectPropertyList {
    float GetFloatProperty(uint nPropertyId) const;                 // 0x006a2710
};
extern cDirectPropertyList* g_pAppProperties;                       // 0x015fd918

struct cCityVisualizer {
    char mPad000[0xaf0];
    cCity* mpCity;                               // +0xaf0
    int ComputeVisualizedPopulation();           // 0x00d57a00
    void SetupCultureStages(CCitizen* pTemplate);// 0x00accf80
};

struct cCity {
    int GetCreatureCount();                      // 0x00bd8120
};
}

// Descriptor of the citizen that is pushed onto every live citizen.
struct CInfoSub { char mData[0x40]; };

struct CCitizenInfo {
    char mPad00[0x89];
    bool mbFlag89;                               // +0x89
    char mPad8A[0xc4 - 0x8a];
    CInfoSub mSub;                               // +0xc4
};

extern CInfoSub g_defaultInfo;                   // 0x01583e08

struct CCitizenManager {
    char mPad000[0xa64];
    CCitizen** mpCitizens;                       // +0xa64
    CCitizen** mpCitizensEnd;                    // +0xa68
    char mPadA6C[0xb6c - 0xa6c];
    CRecord12* mpRecords;                        // +0xb6c

    CRecord12* FindSlot(CCitizen* pCitizen);                       // 0x00d579a0
    void ApplyToAll(CCitizen* pTemplate, CCitizenInfo* pInfo);     // 0x00d57a60
};

// Spore's reference-taking clamp helper: both operands are spilled and the selected one is reloaded.
template <class T> const T& MaxValue(const T& a, const T& b)
{
    return a < b ? b : a;
}

// 16-byte element copied by CopyElems16 (an id plus three floats).
struct Elem16 {
    uint  mnId;                                  // +0x00
    float mf0;                                   // +0x04
    float mf1;                                   // +0x08
    float mf2;                                   // +0x0c
};

// @ 0x00d576b0
// Returns the scenario slot with the given index.
CEntry* CTribe::GetEntry(int nIndex)
{
    return &mEntries[nIndex];
}

// @ 0x00d576d0
// Seeds the citizen's specialised tool: makes sure the shared tribe queue exists, hands the queue
// to the citizen's grid, opens a 0x1000-unit range of unlimited height and picks a random tool.
void __cdecl SeedCitizenTool(CCitizen* pCitizen)
{
    if (!g_bTribeQueueInit) {
        GridInitQueue(&g_tribeQueue);
        g_bTribeQueueInit = true;
    }
    UpdateTimeScaled(pCitizen);
    pCitizen->mpGrid->ResetQueue(&g_tribeQueue);
    pCitizen->mpGrid->mRange.SetRange(0x1000, 0, 3.402823466e+38F, 0);
    pCitizen->SetSpecializedTool((int)g_random.RandomUint32Uniform(3) + 1);
}

// @ 0x00d577b0
// Copies a range of 16-byte elements; each element is skipped when the destination is null.
void __cdecl CopyElems16(const Elem16* pFirst, const Elem16* pLast, Elem16* pDest)
{
    while (pFirst != pLast) {
        if (pDest != 0) {
            pDest->mnId = pFirst->mnId;
            pDest->mf0 = pFirst->mf0;
            pDest->mf1 = pFirst->mf1;
            pDest->mf2 = pFirst->mf2;
        }
        ++pFirst;
        ++pDest;
    }
}

// @ 0x00d57800
// Places a freshly spawned citizen: initialises the model from the city, orients it at a random
// angle inside [fBase, fBase + fRange) scaled by fScale, attaches it to the behaviour manager and
// bumps the tribe slot counter.
void __cdecl PlaceCitizen(CCitizen* pCitizen, CTribe* pTribe, int nUnusedA, int nState,
                          int nEntry, int nExtra, float fBase, float fRange, float fScale)
{
    (void)nUnusedA;
    pCitizen->InitFrom(pTribe->mpCity, 0, 1, nExtra);
    pCitizen->mFlags |= 0x80;
    GetAnimShortcut()->SetTarget(pCitizen, 1);
    pCitizen->mbFieldFBC = true;
    double fRand = g_random.RandomDouble();
    float fAngle = (float)((fBase + fRand * fRange - fRange * 0.5) * fScale);
    pCitizen->mVisual.SetAngle(fAngle);
    pCitizen->SetState(nState);
    pCitizen->mnState = nState;
    if (!pCitizen->mVisual.IsReady())
        pCitizen->mpAnim->mpModel->mFlags |= 0x800;
    pCitizen->UpdateEntry(nEntry);
    SP::GetBehaviorManager()->Attach(&pCitizen->mBehavior);
    pCitizen->mpTribe = pTribe;
    UpdateTimeScaled(pCitizen);
    pCitizen->mpGrid->ResetQueue(&g_cityQueue);
    pCitizen->mpGrid->mnField5fc = 0;
    if (pCitizen->mpAnim != 0) {
        pCitizen->mpAnim->mbField64 = false;
        pCitizen->mpAnim->Detach(1);
    }
    pTribe->GetEntry(nEntry)->mnCount++;
    pCitizen->mbFieldF90 = false;
}

// @ 0x00d57940
// Takes a citizen out of the city: clears the "hidden" flag of its model, resets its grid queue and
// rebuilds the culture stages of the visualizer.
void __stdcall DeactivateCitizen(CCitizen* pCitizen)
{
    pCitizen->SetState(-1);
    if (pCitizen->mpAnim != 0) {
        CModel* pModel = pCitizen->mpAnim->mpModel;
        if (pModel != 0)
            pModel->mFlags &= ~0x800;
    }
    UpdateTimeScaled(pCitizen);
    pCitizen->mpGrid->ResetQueue();
    SP::GetVisualizer()->SetupCultureStages(pCitizen);
    pCitizen->ClearEntry();
}

// @ 0x00d579a0
// Looks the citizen up in the manager's index array and returns its 12-byte record, or asks the
// citizen's visual sub-object to resolve one.
CRecord12* CCitizenManager::FindSlot(CCitizen* pCitizen)
{
    int nCount = (int)(mpCitizensEnd - mpCitizens);
    if (nCount > 0) {
        CCitizen** pCitizen2 = mpCitizens;
        for (int i = 0; i < nCount; ++i, ++pCitizen2) {
            if (*pCitizen2 == pCitizen)
                return &mpRecords[i];
        }
    }
    return (CRecord12*)pCitizen->mVisual.Resolve();
}

// @ 0x00d57a00
// Number of citizens that the city visualiser shows: creature count times the display ratio,
// clamped from below to 15.
int SP::cCityVisualizer::ComputeVisualizedPopulation()
{
    float fRatio = g_pAppProperties->GetFloatProperty(0x5cad54a);
    int nCount = (int)((float)mpCity->GetCreatureCount() * fRatio);
    return MaxValue(nCount, 15);
}

// @ 0x00d57a60
// Applies the template citizen's state to every live citizen, showing or hiding each model.
void CCitizenManager::ApplyToAll(CCitizen* pTemplate, CCitizenInfo* pInfo)
{
    int nState = pTemplate->GetState();
    bool bHide = pInfo->mbFlag89;
    CInfoSub* pSub = &pInfo->mSub;
    int nCount = (int)(mpCitizensEnd - mpCitizens);
    for (int i = 0; i < nCount; ++i) {
        CCitizen* pCitizen = mpCitizens[i];
        pCitizen->SetState(nState);
        pCitizen->mnState = nState;
        if (!bHide) {
            pCitizen->SetInfo(pSub);
            pCitizen->SetFlag(1);
            pCitizen->mpAnim->mpModel->mFlags |= 0x800;
        } else {
            pCitizen->SetInfo(&g_defaultInfo);
            pCitizen->SetFlag(0);
            pCitizen->mpAnim->mpModel->mFlags &= ~0x800;
        }
    }
}
