// Slice s00c8c9d0: the planet population-reduction pass (trim every civ on the active planet down to
// a ratio of its population, then erode the colonies), the colonisation reducer that picks the planets
// to shrink, the noun sweep that clears city populations, plus the cTotemPole class (its game-data and
// spatial bases, the three model vectors and its serializer).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// externals (retail addresses in comments; call targets are masked during comparison)
// ---------------------------------------------------------------------------------------------
extern "C" void* __cdecl operator_new(uint32_t nSize, const char* pTag, int nA, int nB, const char* pFile, int nLine); // 0x00f473a0
extern "C" void  __cdecl operator_delete_array(void* pBlock);                                                          // 0x00f47380

extern char g_szSimulator[];        // 0x013f09b4 "Simulator"
extern char g_szEastlFile[];        // 0x013ebb38 ".../EASTL/allocator.h"
extern char g_nounListPlanet[];     // 0x018c43e8
extern char g_nounListTribe[];      // 0x018c816a
extern char g_varListBase[];        // 0x0157a9e0

extern "C" float __cdecl sqrtf(float fValue);   // x87 fsqrt

// noun vocabulary selectors handed to cGameNounManager::GetGameDataVector
void __cdecl FUN_00cd7d10();       // 0x00cd7d10
void __cdecl FUN_00d3d420();        // 0x00d3d420
void __cdecl FUN_00acdff0();        // 0x00acdff0
void __cdecl FUN_00b1e500();        // 0x00b1e500
void __cdecl FUN_00b21080();        // 0x00b21080
void __cdecl FUN_00b236c0();        // 0x00b236c0

class cPlanet;
class cCivData;
class cCity;
class cOutStream;

// ---------------------------------------------------------------------------------------------
// small vectors used by the noun manager
// ---------------------------------------------------------------------------------------------
struct tPtrVector {                 // plain vector of 4-byte pointers
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
};

struct tGameDataList {              // the noun manager's game-data vector (begin/end at +4/+8)
    void*      mPad00;              // +0x00
    tPtrVector mData;               // +0x04
    void*      mPad0c;              // +0x0c
    void*      mPad10;              // +0x10
};

// ref-counted noun (AddRef/Release are the first two virtual slots)
class tRefObject {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
};

class cGameDataNoun : public tRefObject {
public:
    uint8_t mPad04[0x98];           // +0x004
    tPtrVector mData;               // +0x09c
    uint8_t mPadA4[0x6a8];          // +0x0a4
    int32_t mn74c;                  // +0x74c
    float   mf748;                  // +0x748

    tPtrVector* GetDataVector();                            // 0x00bef6c0
    void FUN_00bd7d10(int32_t nValue, float fValue);        // 0x00bd7d10
};

// the position-tagged 12-byte element handled by the analysis vector
struct tAnalysisInfo {
    uint32_t mnKey;                 // +0x00
    uint32_t mnValue;               // +0x04
    uint32_t mnFlags;               // +0x08
};

class tAnalysisVector {             // eastl vector of 12-byte elements
public:
    tAnalysisInfo* mpBegin;         // +0x00
    tAnalysisInfo* mpEnd;           // +0x04
    tAnalysisInfo* mpCapacity;      // +0x08

    void Insert(tAnalysisInfo* pPosition, uint32_t nCount, const tAnalysisInfo& value); // 0x00c8d940
};

// ---------------------------------------------------------------------------------------------
// the planet (and the civs/cities it owns)
// ---------------------------------------------------------------------------------------------
class cCity {
public:
    uint8_t mPad00[0x24];           // +0x000
    int32_t mn24;                   // +0x024 population
    uint8_t mPad28[0x10];           // +0x028
    int32_t mn38;                   // +0x038 owning empire
    float   mf3c;                   // +0x03c

    int32_t GetPopulation();                            // 0x00ff35d0
    void    SetPopulation(int32_t nAmount, void* pOwner); // 0x00ff1da0
    void    FUN_00ff03b0(int32_t nValue);               // 0x00ff03b0 (mn38)
    void    FUN_00ff03c0(float fValue);                 // 0x00ff03c0 (mf3c)
    float   FUN_00b7e0a0();                             // 0x00b7e0a0 (mf3c)
    int32_t FUN_00a1ad10();                             // 0x00a1ad10 (mn38)
};

class cCivData {
public:
    uint8_t  mPad00[0x3c];          // +0x000
    cCity**  mpCityBegin;           // +0x03c
    cCity**  mpCityEnd;             // +0x040

    void EraseCity(int32_t nIndex); // 0x00ff1fb0
};

class cPlanet {
public:
    virtual void AddRef();          // +0x00
    virtual void Release();         // +0x04
    uint8_t   mPad00[0x24];         // +0x004
    int32_t   mn28;                 // +0x028
    uint32_t  mnFlags;              // +0x02c
    uint8_t   mPad30[0x24];         // +0x030
    void*     mpAvatar;             // +0x054
    uint8_t   mPad58[0x104];        // +0x058
    cCivData** mpCivBegin;          // +0x15c
    cCivData** mpCivEnd;            // +0x160
    uint8_t   mPad164[0x20];        // +0x164
    int32_t   mn184;                // +0x184 empire reference
    uint8_t   mPad188[0x0c];        // +0x188
    int32_t   mn194;                // +0x194 noun type

    tPtrVector* GetRelatedPlanets();        // 0x00bba790
    void*       GetAvatar();                // 0x00b1fdb0
    cCivData*   GetCiv(int32_t nIndex);     // 0x00b8dec0
    void        RemoveCiv(int32_t nIndex);  // 0x00b8df80
    int32_t     GetNounType();              // 0x00b8dab0 (mn194)
    bool        FUN_00b8d970();             // 0x00b8d970 (flag bit 8 of mnFlags)
    int32_t     GetOwnerID();               // 0x00b8de30
    void        FUN_00c8d060();             // 0x00c8d060
};

// the noun manager
class cGameNounManager {
public:
    uint8_t mPad00[0x54];           // +0x000
    void*   mpAvatar;               // +0x054

    void* GetAvatar();                                              // 0x00b1fdb0
    tGameDataList* GetGameDataVector(void* pF1, void* pF2, void* pF3, void* pF4, void* pAlloc); // 0x00b21340
    void  RemoveNoun(void* pNoun);                                  // 0x00b225d0
    void* GetCurrentTerrainSphere();                                // 0x00f67d90
};

class cStarManager {
public:
    void* GetEmpireByID(void* pAvatar);             // 0x00ba9370
};

cGameNounManager* __cdecl NounManager();            // 0x00b3d300
cStarManager*     __cdecl StarManager();            // 0x00b3d2a0
cGameNounManager* __cdecl SpaceGameGet();           // 0x01002bd0
int32_t  __cdecl GetPlayerEmpireID();               // 0x01021090
void*    __cdecl GetUniverseContext();              // 0x01021080
cPlanet* __cdecl GetActivePlanetRecord();           // 0x010212a0

// the ref-counted range a game-data vector is copied into
class tRefRange {
public:
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
    void Assign(void*** ppList);    // 0x00ba95a0
};

// the vector the reduced entries are collected in
class tEntryVector {
public:
    void** mpBegin;                 // +0x00
    void** mpEnd;                   // +0x04
    void** mpCapacity;              // +0x08

    tEntryVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(void** pEnd, void* const& pValue);   // 0x00aea5d0
};

int32_t __cdecl FUN_00c70420(cPlanet* pPlanet);                    // 0x00c70420
void*   __cdecl FUN_00829110(void** ppOut, void** pBegin, void** pEnd, void** pDst, int32_t nHint); // 0x00829110
void    __cdecl FUN_00c8c0f0(void* pEntry, float fRatio, int32_t nMin); // 0x00c8c0f0
void    __cdecl FUN_00c35240(cPlanet* pPlanet, int32_t nEmpire);    // 0x00c35240
bool    __cdecl FUN_00c35810(void* pEntry, int32_t nEmpire);        // 0x00c35810 (thiscall style)
void    __cdecl FUN_00c8c9d0(cPlanet* pPlanet);
void    __cdecl FUN_00c8cb20(cPlanet* pPlanet, float fRatio, int32_t nMin, float fCityRatio, int32_t nCityMin);
void    __cdecl FUN_00c8ce40(cPlanet* pPlanet, float fRatio, int32_t nMin, float fCityRatio, int32_t nCityMin,
                             float fCityRatio2, int32_t nCityMin2);
void    __cdecl FUN_00c8d000(cPlanet* pPlanet, int32_t nEmpire);

// space combat tuning (a process-wide singleton)
class cSPSpaceCombatTuning {
public:
    float GetMilitaryCaptureRemainingCityRatio();    // 0x01029f10
    float GetMilitaryCaptureRemainingPlanetRatio();  // 0x01029ec0
};
cSPSpaceCombatTuning* __cdecl GetSpaceCombatTuning(); // 0x01029940

// audio / terrain hooks used by the planet sweep
class tAudioSystem {
public:
    virtual void v00();     // 0x00
    virtual void v04();     // 0x04
    virtual void v08();     // 0x08
    virtual void v0c();     // 0x0c
    virtual void v10();     // 0x10
    virtual void v14();     // 0x14
    virtual void v18();     // 0x18
    virtual void v1c();     // 0x1c
    virtual int32_t v20();  // 0x20
    virtual void v24();     // 0x24
    virtual void v28();     // 0x28
    virtual void v2c();     // 0x2c
    virtual void v30();     // 0x30
    virtual void v34();     // 0x34
    virtual void v38(int32_t nEvent);                // 0x38
    virtual void v3c(int32_t nEvent);                // 0x3c
    virtual void v40(int32_t nEvent, int32_t nValue); // 0x40
    virtual void v44();     // 0x44
    virtual void v48();     // 0x48
    virtual void v4c();     // 0x4c
    virtual void v50();     // 0x50
    virtual void v54();     // 0x54
    virtual void v58();     // 0x58
};

tAudioSystem* __cdecl GetSystemAT();                // 0x00a206f0
void* __cdecl FUN_010666a0(uint32_t nKey);          // 0x010666a0
void  __cdecl FUN_0106dcd0(void* pObject);          // 0x0106dcd0 (thiscall on the returned object)

class cTerrainSphere {
public:
    bool FUN_00c772c0(uint32_t nKey);               // 0x00c772c0
    void FUN_00c77bf0(uint32_t nKey);               // 0x00c77bf0
};

int32_t __cdecl FUN_00ff5930(cPlanet* pPlanet);     // 0x00ff5930
class cSimPlanetHighLOD {
public:
    void CreateReplacement();                       // 0x00ffa780
};

// ---------------------------------------------------------------------------------------------
// the spatial object cTotemPole derives from
// ---------------------------------------------------------------------------------------------
struct tRefPtr {                    // 4-byte element of the model vectors
    void* mpObject;                 // +0x00
};

class tMWModelVector {              // eastl vector of AutoRefCount<cMWModel> (0x14 bytes on the record)
public:
    tRefPtr* mpBegin;               // +0x00
    tRefPtr* mpEnd;                 // +0x04
    tRefPtr* mpCapacity;            // +0x08
    uint8_t  mPad0c[0x08];          // +0x0c

    tMWModelVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoDestroyValues(tRefPtr* pBegin, tRefPtr* pEnd);   // 0x005f3680
};

struct tGameDataBase {              // first base subobject (vtable at +0x00)
    virtual ~tGameDataBase() {}
};

struct tGameDataRefBase {           // second base subobject (vtable at +0x04, count at +0x08)
    virtual ~tGameDataRefBase() {}
    virtual void AddRef();          // 0x04
    int32_t mnRefCount;             // +0x04 (absolute +0x08)
};

class cGameData : public tGameDataBase, public tGameDataRefBase {
public:
    cGameData();                    // 0x00b18660
    virtual ~cGameData();           // 0x00b184c0
    bool Write(cOutStream* pStream); // 0x00b18590
    uint8_t mPad0c[0x28];           // +0x00c
};

class cSpatialObject {
public:
    cSpatialObject();                                   // 0x00c89630
    virtual ~cSpatialObject();                          // 0x00c8a420
    bool Write(cOutStream* pStream);                    // 0x00c88a90
    void SetLocalExtents(float fMin, float fMax);       // 0x00c89160
    uint8_t  mPad04[0x50];                              // +0x004
    int32_t  mn54;                                      // +0x054
    uint8_t  mPad58[0x38];                              // +0x058
    uint32_t mn90;                                      // +0x090
    uint32_t mn94;                                      // +0x094
    uint32_t mn98;                                      // +0x098
    uint8_t  mPad9c[0x38];                              // +0x09c
};

// the byte sink a cOutStream hands out (the object whose slot 0x18 yields the IStream)
class tIStream {
public:
    virtual void v00();                                     // +0x00
};

class tStreamInner {
public:
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual tIStream* v18();                                // +0x18
};

// the stream every game-data object serializes itself into
class cOutStream {
public:
    virtual void v00();                                     // +0x00
    virtual void v04();                                     // +0x04
    virtual void v08();                                     // +0x08
    virtual void v0c();                                     // +0x0c
    virtual void v10();                                     // +0x10
    virtual void v14();                                     // +0x14
    virtual void v18();                                     // +0x18
    virtual void v1c();                                     // +0x1c
    virtual tStreamInner* v20();                            // +0x20
};

class cVarListSerializer {
public:
    uint32_t mPad00[0x05];                                  // +0x00
    void Construct(void* pOwner, void* pVarList, int32_t nLine); // 0x00692f90
    bool Serialize(cOutStream* pStream);                    // 0x00692900
};

// the frame retail reserves for the serializer: the little-endian tag, the serializer object and
// 0xa00 bytes of scratch behind them
struct tVarListFrame {
    uint32_t            mnValue;            // +0x000
    cVarListSerializer  mSerializer;        // +0x004
    uint32_t            mPad18[0x280];      // +0x018
};

bool __cdecl EA_IO_WriteUint32(tIStream* pStream, const uint32_t* pValue, int32_t nCount, int32_t nFlags); // 0x0093aa70

class cTotemPole : public cGameData, public cSpatialObject {
public:
    cTotemPole();                               // 0x00c8d6c0
    virtual ~cTotemPole();                      // 0x00c8d800
    bool Write(cOutStream* pStream);            // 0x00c8d330

    tMWModelVector mModels;                     // +0x108
    tMWModelVector mSegments;                   // +0x11c
    tMWModelVector mParts;                      // +0x130
    int32_t        mn144;                       // +0x144
    bool           mb148;                       // +0x148
};

// ---------------------------------------------------------------------------------------------
// the spatial object that owns the child list (00c8d460)
// ---------------------------------------------------------------------------------------------
class cSpatialNode {
public:
    uint8_t  mPad00[0x04];          // +0x000
    uint32_t mnFlags;               // +0x004
    uint8_t  mPad08[0x70];          // +0x008
    float    mf78;                  // +0x078
    uint8_t  mPad7c[0x08];          // +0x07c
    float    mf84;                  // +0x084
};

class cSimObject {
public:
    uint8_t      mPad00[0x38];      // +0x000
    float        mf38;              // +0x038
    float        mf3c;              // +0x03c
    float        mf40;              // +0x040
    float        mf44;              // +0x044
    float        mf48;              // +0x048
    float        mf4c;              // +0x04c
    uint8_t      mPad50[0x0c];      // +0x050
    float        mf5c;              // +0x05c
    uint8_t      mPad60[0x74];      // +0x060
    cSpatialNode** mpChildBegin;    // +0x0d4
    cSpatialNode** mpChildEnd;      // +0x0d8

    void SetLocalExtents(float fMin, float fMax);   // 0x00c89160
    void FUN_00c8d460(float fA, float fB);          // 0x00c8d460
};

// ---------------------------------------------------------------------------------------------
// vector insert helpers (with a struct return/parameter convention)
// ---------------------------------------------------------------------------------------------
void* __cdecl FUN_00951740(void** ppOut, tAnalysisInfo* pBegin, tAnalysisInfo* pEnd, tAnalysisInfo* pDst, tAnalysisInfo* pPos); // 0x00951740
void* __cdecl FUN_00abced0(tAnalysisInfo* pDstEnd, tAnalysisInfo* pBegin, tAnalysisInfo* pEnd);   // 0x00abced0
void  __cdecl FUN_00a177f0(tAnalysisInfo* pBegin, tAnalysisInfo* pEnd, const tAnalysisInfo* pValue); // 0x00a177f0
void* __cdecl FUN_006a4100(tAnalysisInfo* pDst, int32_t nCount, const tAnalysisInfo* pValue);     // 0x006a4100
void* __cdecl FUN_007ec550(void* pDst, const void* pSrc, uint32_t nBytes);                        // 0x007ec550

template <typename T>
inline const T& tMax(const T& a, const T& b)
{
    return a < b ? b : a;
}

// @ 0x00c8c9d0
void FUN_00c8c9d0(cPlanet* pPlanet)
{
    tPtrVector* pPlanets = pPlanet->GetRelatedPlanets();
    int32_t nCount = (int32_t)(pPlanets->mpEnd - pPlanets->mpBegin);
    int32_t i = 0;
    if (nCount > 0)
    {
        do
        {
            cPlanet* pCur = (cPlanet*)pPlanets->mpBegin[i];
            if (GetUniverseContext() == 0 && GetActivePlanetRecord() == pCur)
            {
                cGameNounManager* pManager = NounManager();
                tGameDataList* pList = pManager->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                                   (void*)FUN_00acdff0, (void*)FUN_00b1e500,
                                                                   g_nounListPlanet);
                tPtrVector* pNouns = &pList->mData;
                int32_t nNouns = (int32_t)(pNouns->mpEnd - pNouns->mpBegin);
                for (int32_t j = 0; j < nNouns; ++j)
                    ((cGameDataNoun*)pNouns->mpBegin[j])->FUN_00bd7d10(-1, 0.0f);
            }
            else if (pCur->mn28 != 1 && pCur->mn28 != 0 && !pCur->FUN_00b8d970())
            {
                int32_t c = 0;
                int32_t nCivs = (int32_t)(pCur->mpCivEnd - pCur->mpCivBegin);
                for (; c < nCivs; ++c)
                {
                    cCivData* pCiv = pCur->GetCiv(c);
                    int32_t nCities = (int32_t)(pCiv->mpCityEnd - pCiv->mpCityBegin);
                    for (int32_t k = 0; k < nCities; ++k)
                    {
                        cCity* pCity = pCiv->mpCityBegin[k];
                        pCity->FUN_00ff03b0(-1);
                        pCity->FUN_00ff03c0(0.0f);
                    }
                }
            }
            ++i;
        } while (i < nCount);
    }
}

// @ 0x00c8cb20
void FUN_00c8cb20(cPlanet* pPlanet, float fRatio, int32_t nMin, float fCityRatio, int32_t nCityMin)
{
    int32_t nTotal = FUN_00c70420(pPlanet);
    int32_t nRemaining = nTotal - (int32_t)((float)nTotal * fRatio);
    if (nTotal - nRemaining < nMin)
        nRemaining = nTotal - nMin;

    if (pPlanet == GetActivePlanetRecord() && GetUniverseContext() == 0)
    {
        cGameNounManager* pManager = NounManager();
        tGameDataList* pList = pManager->GetGameDataVector((void*)FUN_00b21080, (void*)FUN_00d3d420,
                                                           (void*)FUN_00b236c0, (void*)FUN_00b1e500,
                                                           g_nounListTribe);
        tRefRange range;
        range.Assign(&pList->mData.mpBegin);
        void** pBegin = range.mpBegin;
        void** pEnd = range.mpEnd;
        int32_t nNouns = (int32_t)(pEnd - pBegin);
        for (int32_t i = 0; i < nNouns; ++i)
        {
            cGameDataNoun* pNoun = (cGameDataNoun*)pBegin[i];
            tPtrVector* pData = pNoun->GetDataVector();
            int32_t nEntries = (int32_t)(pData->mpEnd - pData->mpBegin);
            void** pNew = 0;
            if (nEntries != 0)
                pNew = (void**)operator_new((uint32_t)nEntries * 4, g_szSimulator, 0, 0, g_szEastlFile, 0xd1);
            void* pNewEnd = 0;
            FUN_00829110(&pNewEnd, pData->mpBegin, pData->mpEnd, pNew, i);
            int32_t nCopied = (int32_t)((void**)pNewEnd - pNew);
            for (int32_t k = 0; k < nCopied; ++k)
            {
                void* pEntry = pNew[k];
                if (nRemaining > 0)
                {
                    NounManager()->RemoveNoun(pEntry);
                    --nRemaining;
                }
                else
                {
                    FUN_00c8c0f0(pEntry, fCityRatio, nCityMin);
                }
            }
            void** pSlot = pNew;
            while (pSlot < (void**)pNewEnd)
            {
                if (*pSlot != 0)
                    ((tRefObject*)*pSlot)->Release();
                ++pSlot;
            }
            if (pNew != 0 && ((int32_t*)pNew)[-1] != 0)
                operator_delete_array(pNew);
        }
        void** pSlot = pBegin;
        while (pSlot < pEnd)
        {
            if (*pSlot != 0)
                ((tRefObject*)*pSlot)->Release();
            ++pSlot;
        }
        if (pBegin != 0 && ((int32_t*)pBegin)[-1] != 0)
            operator_delete_array(pBegin);
    }
    else
    {
        int32_t nCivs = (int32_t)(pPlanet->mpCivEnd - pPlanet->mpCivBegin);
        for (int32_t c = 0; c < nCivs; ++c)
        {
            cCivData* pCiv = pPlanet->GetCiv(c);
            int32_t nCities = (int32_t)(pCiv->mpCityEnd - pCiv->mpCityBegin);
            for (int32_t k = 0; k < nCities; ++k)
            {
                if (nRemaining > 0)
                {
                    pCiv->EraseCity(k);
                    --nRemaining;
                }
                else
                {
                    cCity* pCity = pCiv->mpCityBegin[k];
                    int32_t nCur = pCity->GetPopulation();
                    int32_t nCut = (int32_t)((float)nCur * fCityRatio);
                    int32_t nNew = pCity->GetPopulation() - nCut;
                    if (pCity->GetPopulation() - nNew < nCityMin)
                        nNew = pCity->GetPopulation() - nCityMin;
                    if (nNew > 0)
                        pCity->SetPopulation(pCity->GetPopulation() - nNew, pPlanet);
                }
            }
        }
        for (int32_t c = 0; c < (int32_t)(pPlanet->mpCivEnd - pPlanet->mpCivBegin); )
        {
            cCivData* pCiv = pPlanet->mpCivBegin[c];
            if (pCiv->mpCityEnd == pCiv->mpCityBegin)
                pPlanet->RemoveCiv(c);
            else
                ++c;
        }
    }
}

// @ 0x00c8ce40
void FUN_00c8ce40(cPlanet* pPlanet, float fRatio, int32_t nMin, float fCityRatio, int32_t nCityMin,
                  float fCityRatio2, int32_t nCityMin2)
{
    void* pRef;
    tEntryVector vec;
    tPtrVector* pPlanets = pPlanet->GetRelatedPlanets();
    int32_t nPlanets = (int32_t)(pPlanets->mpEnd - pPlanets->mpBegin);
    for (int32_t i = 0; i < nPlanets; ++i)
    {
        cPlanet* pCur = (cPlanet*)pPlanets->mpBegin[i];
        if (pCur->GetNounType() == 5 && pCur->mpCivBegin != pCur->mpCivEnd)
        {
            pRef = pCur;
            if (pCur != 0)
                pCur->AddRef();
            if (vec.mpEnd < vec.mpCapacity)
            {
                *vec.mpEnd = pCur;
                ++vec.mpEnd;
                if (pCur != 0)
                    pCur->AddRef();
            }
            else
            {
                vec.DoInsertValue(vec.mpEnd, pRef);
            }
            if (pRef != 0)
                ((tRefObject*)pRef)->Release();
        }
    }

    int32_t nCount = (int32_t)(vec.mpEnd - vec.mpBegin);
    int32_t nRemaining = nCount - (int32_t)((float)nCount * fRatio);
    if (nCount - nRemaining < nMin)
        nRemaining = nCount - nMin;

    void* pAvatar = pPlanet->GetAvatar();
    StarManager()->GetEmpireByID(pAvatar);

    for (int32_t i = 0; i < nCount; ++i)
    {
        cPlanet* pCur = (cPlanet*)vec.mpBegin[i];
        if ((pCur == GetActivePlanetRecord() && GetUniverseContext() == 0) || nRemaining <= 0)
        {
            FUN_00c8cb20(pCur, fCityRatio, nCityMin, fCityRatio2, nCityMin2);
        }
        else
        {
            FUN_00c8cb20(pCur, 0.0f, 0, 0.0f, 0);
            FUN_00c35810(pCur, 0);
            --nRemaining;
        }
    }

    void** pSlot = vec.mpBegin;
    while (pSlot < vec.mpEnd)
    {
        if (*pSlot != 0)
            ((tRefObject*)*pSlot)->Release();
        ++pSlot;
    }
    if (vec.mpBegin != 0 && ((int32_t*)vec.mpBegin)[-1] != 0)
        operator_delete_array(vec.mpBegin);
}

// @ 0x00c8d000
void FUN_00c8d000(cPlanet* pPlanet, int32_t nEmpire)
{
    FUN_00c8c9d0(pPlanet);
    if (nEmpire == GetPlayerEmpireID())
    {
        FUN_00c8ce40(pPlanet, GetSpaceCombatTuning()->GetMilitaryCaptureRemainingPlanetRatio(), 1,
                     GetSpaceCombatTuning()->GetMilitaryCaptureRemainingCityRatio(), 1, 1.0, 1);
    }
    FUN_00c35240(pPlanet, nEmpire);
}

// @ 0x00c8d060
void cPlanet::FUN_00c8d060()
{
    tPtrVector* pPlanets = GetRelatedPlanets();
    int32_t nPlanets = (int32_t)(pPlanets->mpEnd - pPlanets->mpBegin);
    int32_t nEmpire = -1;
    int32_t i = 0;
    if (nPlanets > 0)
    {
        do
        {
            cPlanet* pCur = (cPlanet*)pPlanets->mpBegin[i];
            if (pCur->GetNounType() == 5 && pCur->mn28 != 1 && pCur->mn28 != 0 && !pCur->FUN_00b8d970())
            {
                int32_t nCivs = (int32_t)(pCur->mpCivEnd - pCur->mpCivBegin);
                if (nCivs == 0)
                    return;
                for (int32_t c = 0; c < nCivs; ++c)
                {
                    cCivData* pCiv = pCur->GetCiv(c);
                    int32_t nCities = (int32_t)(pCiv->mpCityEnd - pCiv->mpCityBegin);
                    if (nCities == 0)
                        return;
                    for (int32_t k = 0; k < nCities; ++k)
                    {
                        cCity* pCity = pCiv->mpCityBegin[k];
                        if (pCity->FUN_00b7e0a0() < 100.0f)
                            return;
                        if (nEmpire == -1)
                            nEmpire = pCity->FUN_00a1ad10();
                        if (nEmpire != pCity->FUN_00a1ad10())
                            return;
                    }
                }
            }
            ++i;
        } while (i < nPlanets);
    }
    if (nEmpire == -1)
        return;

    if (nEmpire == GetPlayerEmpireID())
    {
        if (GetActivePlanetRecord() == 0)
            return;
        tAudioSystem* pAudio = GetSystemAT();
        int32_t nHandle = pAudio != 0 ? pAudio->v20() : 0;
        pAudio = GetSystemAT();
        if (pAudio != 0)
        {
            pAudio->v38(0x03475365);
            pAudio->v40(0x03475381, 0xef7f5479);
            pAudio->v40(0x03475385, nHandle);
            pAudio->v58();
        }
        cTerrainSphere* pSphere = (cTerrainSphere*)NounManager()->GetCurrentTerrainSphere();
        if (pSphere != 0 && !pSphere->FUN_00c772c0(0x06627823))
        {
            pSphere->FUN_00c77bf0(0x06627823);
            FUN_0106dcd0(FUN_010666a0(0xee98e353));
        }
        return;
    }

    FUN_00c8d000(this, nEmpire);
    cPlanet* pActive = GetActivePlanetRecord();
    if (GetUniverseContext() == 0 && pActive->GetNounType() == 5 && pActive->GetOwnerID() == (int32_t)this)
    {
        int32_t nReplacements = FUN_00ff5930(GetActivePlanetRecord());
        if (nReplacements > 0)
        {
            do
            {
                cGameNounManager* pGame = SpaceGameGet();
                ((cSimPlanetHighLOD*)pGame->GetAvatar())->CreateReplacement();
            } while (--nReplacements != 0);
        }
    }
}

// @ 0x00c8d330
bool cTotemPole::Write(cOutStream* pStream)
{
    tVarListFrame frame;
    frame.mnValue = 0x055cf8e3;
    tIStream* pSink = pStream->v20()->v18();
    EA_IO_WriteUint32(pSink, &frame.mnValue, 1, 0);
    bool bOk = cGameData::Write(pStream) && cSpatialObject::Write(pStream);
    frame.mSerializer.Construct(this, g_varListBase, 0x1a80d26);
    if (bOk)
    {
        if (frame.mSerializer.Serialize(pStream))
            return true;
    }
    return false;
}

// @ 0x00c8d460
void cSimObject::FUN_00c8d460(float fA, float fB)
{
    SetLocalExtents(fA, fB);

    int32_t nCount = (int32_t)(mpChildEnd - mpChildBegin);
    for (int32_t i = 0; i < nCount; ++i)
    {
        cSpatialNode* pNode = mpChildBegin[i];
        if (pNode != 0)
        {
            uint32_t nFlags = pNode->mnFlags;
            if (((nFlags >> 14) & 1) != 0 || ((nFlags >> 16) & 1) != 0)
                mf4c = pNode->mf84 - pNode->mf78 + mf4c;
        }
    }

    float fMidX = (mf38 + mf44) * 0.5f;
    float fMidY = (mf48 + mf3c) * 0.5f;
    float fMidZ = (mf4c + mf40) * 0.5f;
    float fAx = mf44 - fMidX;
    float fAy = mf48 - fMidY;
    float fAz = mf4c - fMidZ;
    float fBx = mf38 - fMidX;
    float fBy = mf3c - fMidY;
    float fBz = mf40 - fMidZ;
    mf5c = tMax(sqrtf(fAx * fAx + fAy * fAy + fAz * fAz), sqrtf(fBx * fBx + fBy * fBy + fBz * fBz));
}

// @ 0x00c8d6c0
cTotemPole::cTotemPole()
    : mModels(), mSegments(), mParts(), mn144(5), mb148(true)
{
    mn54 = 2;
    mn90 = 0x093256ba;
    mn98 = 0xf37c24e6;
}

// @ 0x00c8d800
cTotemPole::~cTotemPole()
{
    tRefPtr* pParts = mParts.mpBegin;
    if (pParts != 0 && ((int32_t*)pParts)[-1] != 0)
        operator_delete_array(pParts);
    tRefPtr* pSegments = mSegments.mpBegin;
    if (pSegments != 0 && ((int32_t*)pSegments)[-1] != 0)
        operator_delete_array(pSegments);
    mModels.DoDestroyValues(mModels.mpBegin, mModels.mpEnd);
    tRefPtr* pModels = mModels.mpBegin;
    if (pModels != 0 && ((int32_t*)pModels)[-1] != 0)
        operator_delete_array(pModels);
}

// @ 0x00c8d940
void tAnalysisVector::Insert(tAnalysisInfo* pPosition, uint32_t nCount, const tAnalysisInfo& value)
{
    if ((uint32_t)(mpCapacity - mpEnd) < nCount)
    {
        uint32_t nOld = (uint32_t)((uint8_t*)mpEnd - (uint8_t*)mpBegin) / sizeof(tAnalysisInfo);
        uint32_t nCapacity = nOld * 2;
        if (nOld == 0)
            nCapacity = 1;
        uint32_t nNeeded = nOld + nCount;
        if (nCapacity < nNeeded)
            nCapacity = nNeeded;
        tAnalysisInfo* pNew = 0;
        if (nCapacity != 0)
            pNew = (tAnalysisInfo*)operator_new(nCapacity * sizeof(tAnalysisInfo), g_szSimulator, 0, 0, g_szEastlFile, 0xd1);
        void* pMid = FUN_007ec550(mpBegin, pPosition, (uint32_t)pNew);
        FUN_006a4100((tAnalysisInfo*)pMid, (int32_t)nCount, &value);
        uint32_t nBytes = nCount * sizeof(tAnalysisInfo);
        void* pEnd = FUN_007ec550(pPosition, mpEnd, (uint32_t)((uint8_t*)pMid + nBytes));
        if (mpBegin != 0 && ((int32_t*)mpBegin)[-1] != 0)
            operator_delete_array(mpBegin);
        mpBegin = pNew;
        mpEnd = (tAnalysisInfo*)pEnd;
        mpCapacity = (tAnalysisInfo*)((uint8_t*)pNew + nCapacity * sizeof(tAnalysisInfo));
        return;
    }
    if (nCount == 0)
        return;

    tAnalysisInfo copy = value;
    uint32_t nElements = (uint32_t)(mpEnd - pPosition);
    if (nCount < nElements)
    {
        uint32_t nBytes = nCount * sizeof(tAnalysisInfo);
        tAnalysisInfo* pMoveFrom = (tAnalysisInfo*)((uint8_t*)mpEnd - nBytes);
        void* pOut = 0;
        FUN_00951740(&pOut, pMoveFrom, mpEnd, mpEnd, pPosition);
        mpEnd = (tAnalysisInfo*)((uint8_t*)mpEnd + nBytes);
        tAnalysisInfo* pNew = (tAnalysisInfo*)pOut;
        FUN_00abced0(pNew, (tAnalysisInfo*)((uint8_t*)mpEnd - nBytes), mpEnd);
        FUN_00a177f0(pNew, (tAnalysisInfo*)((uint8_t*)pNew + nBytes), &copy);
    }
    else
    {
        uint32_t nExtra = nCount - nElements;
        FUN_006a4100(mpEnd, (int32_t)nExtra, &copy);
        tAnalysisInfo* pOldEnd = mpEnd;
        mpEnd = (tAnalysisInfo*)((uint8_t*)mpEnd + nExtra * sizeof(tAnalysisInfo));
        void* pOut = 0;
        FUN_00951740(&pOut, pPosition, pOldEnd, mpEnd, pPosition);
        mpEnd = (tAnalysisInfo*)((uint8_t*)mpEnd + nElements * sizeof(tAnalysisInfo));
        FUN_00a177f0(pPosition, pOldEnd, &copy);
    }
}
