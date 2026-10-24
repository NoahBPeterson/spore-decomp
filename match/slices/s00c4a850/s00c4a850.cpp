// SporeApp.exe slice s00c4a850 -- SP mission init / asset picking + Simulator mission events (gold6, worker 36)

#include "types.h"

// ---------------------------------------------------------------------------
// shared small types
// ---------------------------------------------------------------------------

struct ResourceKey {
    uint32_t mInstanceID;                                   // +0x00
    uint32_t mGroupID;                                      // +0x04
    uint32_t mTypeID;                                       // +0x08
};

template <class T>
struct cVec {
    T*       mpBegin;                                       // +0x00
    T*       mpEnd;                                         // +0x04
    T*       mpCapacity;                                    // +0x08
    void*    mpAllocator;                                   // +0x0c
    uint32_t mPad10;                                        // +0x10

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T&       operator[](uint32_t nIndex) const { return mpBegin[nIndex]; }

    void     push_back(const T& rValue)
    {
        if (mpEnd != mpCapacity) {
            T* pSlot = mpEnd;
            ++mpEnd;
            if (pSlot)
                *pSlot = rValue;
            return;
        }
        DoInsertValue(mpEnd, rValue);
    }

    void     DoInsertValue(T* pPos, const T& rValue);       // 0x00aea5d0
};

struct cGameData {
    virtual void       AddRef();                            // +0x00
    virtual void       Release();                           // +0x04
    virtual void       v08();                               // +0x08
    virtual cGameData* Cast(uint32_t nType);                // +0x0c
};

template <class T>
struct AutoRefCount {
    T* mpObject;                                            // +0x00

    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* pObject) : mpObject(pObject) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& rOther) : mpObject(rOther.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }

    // Copy-assignment used by the banner vector: stores the pointer and takes a
    // reference (the destination is always a fresh slot, so nothing to release).
    AutoRefCount& operator=(const AutoRefCount& rOther)
    {
        mpObject = rOther.mpObject;
        if (mpObject) mpObject->AddRef();
        return *this;
    }

    T* operator->() const { return mpObject; }
};

struct cPlanet {
    char     mPad000[0x13c];                                // +0x000
    void*    mpData13C;                                     // +0x13c
    char     mPad140[0x2c];                                 // +0x140
};

struct cPlanetRecord;

// ---------------------------------------------------------------------------
// property table
// ---------------------------------------------------------------------------

struct cProperty {
    void*     mpValue;                                      // +0x00
    uint32_t  mPad04;                                       // +0x04
    uint32_t  mCount;                                       // +0x08
    uint32_t  mPad0c;                                       // +0x0c
    uint16_t  mFlags;                                       // +0x10
    uint16_t  mType;                                        // +0x12

    bool*     GetBool();                                    // 0x0041e920
    int32_t*  GetInt();                                     // 0x0041e990
};

struct cPropertyList {
    virtual void        v00();                              // +0x00
    virtual void        v04();                              // +0x04
    virtual void        v08();                              // +0x08
    virtual void        v0c();                              // +0x0c
    virtual void        v10();                              // +0x10
    virtual void        v14();                              // +0x14
    virtual void        v18();                              // +0x18
    virtual void        v1c();                              // +0x1c
    virtual void        v20();                              // +0x20
    virtual bool        Find(uint32_t nKey, cProperty** ppOut);   // +0x24
    virtual cProperty*  Get(uint32_t nKey);                 // +0x28
};

// ---------------------------------------------------------------------------
// missions
// ---------------------------------------------------------------------------

struct cSPMission;
struct cSPMissionMultiDelivery;
struct cPlanetSearch;

struct cSPMission {
    // vtable +0x00 (slots used by this slice: +0x6c, +0x128, +0x16c, +0x170, +0x188)
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068();
    virtual void Abort();                                   // +0x06c
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();
    virtual void v0b0(); virtual void v0b4(); virtual void v0b8(); virtual void v0bc();
    virtual void v0c0(); virtual void v0c4(); virtual void v0c8(); virtual void v0cc();
    virtual void v0d0(); virtual void v0d4(); virtual void v0d8(); virtual void v0dc();
    virtual void v0e0(); virtual void v0e4(); virtual void v0e8(); virtual void v0ec();
    virtual void v0f0(); virtual void v0f4(); virtual void v0f8(); virtual void v0fc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124();
    virtual bool CheckTargetValid();                        // +0x128
    virtual void v12c(); virtual void v130(); virtual void v134(); virtual void v138();
    virtual void v13c(); virtual void v140(); virtual void v144(); virtual void v148();
    virtual void v14c(); virtual void v150(); virtual void v154(); virtual void v158();
    virtual void v15c(); virtual void v160(); virtual void v164(); virtual void v168();
    virtual void OnMissionStarted();                        // +0x16c
    virtual void OnMissionSucceeded();                      // +0x170
    virtual void v174(); virtual void v178(); virtual void v17c(); virtual void v180();
    virtual void v184();
    virtual void OnPropertiesLoaded();                      // +0x188

    char           mPad004[0x12c];                          // +0x004 .. +0x12f
    uint32_t       mFlags;                                  // +0x130
    char           mPad134[0x4c];                           // +0x134 .. +0x17f
    cPropertyList* mpPropertyList;                          // +0x180
    int32_t        mField184;                               // +0x184
    int32_t        mField188;                               // +0x188
    char           mPad18c[4];                              // +0x18c
    int32_t        mField190;                               // +0x190
    cVec<ResourceKey> mKeys194;                             // +0x194
    cVec<ResourceKey> mKeys1a8;                             // +0x1a8
    cVec<ResourceKey> mKeys1bc;                             // +0x1bc
    char           mPad1d0[0x20];                           // +0x1d0 .. +0x1ef
    int32_t        mStatus;                                 // +0x1f0
    void*          mpData1f4;                               // +0x1f4
    char           mPad1f8[0xc];                            // +0x1f8 .. +0x203
    int32_t        mField204;                               // +0x204
    int32_t        mField208;                               // +0x208

    char           Init();                                  // 0x00c4ad50
    void           PickGiveOnAcceptItems();                 // 0x00c4a980
    cPlanet*       GetTargetPlanet();                       // 0x00970b30
    void           SetTargetPlanet(void* pPlanet);          // 0x00c47180
    void           SetInitialized();                        // 0x00c4a0c0
    void           TriggerUIUpdate();                       // 0x00c47d80
    int32_t        Update(void* pArg);                      // 0x00c478b0
    void*          PickPlanet(cPlanetSearch* pSearch);      // 0x00c47e20
    uint32_t       ReadTargetPlanetType();                  // 0x00c45b40
    cPlanetRecord* GetPlanetRecordFromTargetType(uint32_t nType);   // 0x00c474b0
};

struct cSPMissionMultiDelivery : cSPMission {
    void    ReturnForRewards();                             // 0x00c4b760
    int32_t Update(void* pArg);                             // 0x00c4b7a0
    bool    IsAtDeliveryTarget(void* pPlanet, ResourceKey* pKey);   // 0x00c4bb60
    bool    InitWrapper();                                  // 0x00c4baa0
    int32_t GetCountA();                                    // 0x00c4bba0
    int32_t GetCountB();                                    // 0x00c4bbc0
};

// Message handler base (polymorphic sub-object living at +0x34 of the mission).
struct cMissionMessageHandler {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();
    virtual void v0b0(); virtual void v0b4(); virtual void v0b8(); virtual void v0bc();
    virtual void v0c0(); virtual void v0c4(); virtual void v0c8(); virtual void v0cc();
    virtual void v0d0(); virtual void v0d4(); virtual void v0d8(); virtual void v0dc();
    virtual void v0e0(); virtual void v0e4(); virtual void v0e8(); virtual void v0ec();
    virtual void v0f0(); virtual void v0f4(); virtual void v0f8(); virtual void v0fc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14c();
    virtual void v150(); virtual void v154(); virtual void v158(); virtual void v15c();
    virtual void v160(); virtual void v164(); virtual void v168(); virtual void v16c();
    virtual void v170(); virtual void v174(); virtual void v178(); virtual void v17c();
    virtual void v180(); virtual void v184(); virtual void v188(); virtual void v18c();
    virtual void v190(); virtual void v194(); virtual void v198(); virtual void v19c();
    virtual void v1a0(); virtual void v1a4(); virtual void v1a8(); virtual void v1ac();
    virtual void v1b0(); virtual void v1b4(); virtual void v1b8();
    virtual void HandleMessage(uint32_t nMessage, void* pMessage);

    int32_t    mStatus;                                     // +0x1bc (cSPMission +0x1f0)
    void*      mpData1f4;                                   // +0x1c0 (cSPMission +0x1f4)

    void BaseHandleMessage(uint32_t nMessage, void* pMessage);   // 0x00c4a6b0
    cSPMissionMultiDelivery* GetMission() { return (cSPMissionMultiDelivery*)((char*)this - 0x34); }
};

// Mission message body (only the fields used by the delivery mission).
struct cMissionMessage {
    uint32_t mPad00;
    uint32_t mPad04;
    void*    mpPlanetRef;                                   // +0x08
    uint32_t mPad0c;
    uint32_t mField10;                                      // +0x10
    uint32_t mPad14;
    uint32_t mField18;                                      // +0x18
};

struct cPlanetSearch {                                      // pick request built by cMissionBalance::Init
    uint32_t mKind;                                         // +0x00 (0x20 / 0x38)
    char     mPad004[0x40];                                 // +0x004

    cPlanetSearch();                                        // 0x00ba7bd0
    ~cPlanetSearch();                                       // 0x00ba8220
};

// cSPMissionAdventure-style mission driven by a star-manager asset.
struct cSPMissionAdventureBase : cSPMission {
    void* PickAdventureAsset();                             // 0x00c4b220
    bool  RerollAdventureAsset();                           // 0x00c4b250
    void  InitAdventure();                                  // 0x00c4b2b0
};

// SP::cMissionBalance
struct cMissionBalance : cSPMission {
    bool Init();                                            // 0x00c4b7f0
};

// Host object for the banner-list reader (entries vector at +0x1c).
struct cBannerListHost {
    char mPad000[0x1c];                                     // +0x000
    cVec<AutoRefCount<cGameData> > mEntries;                // +0x01c
    bool ReadBannerList(void* pArchive);                    // 0x00c4a850
};

// ---------------------------------------------------------------------------
// Simulator pressure-event missions
// ---------------------------------------------------------------------------

namespace Simulator {

struct cMissionAdventure {
    void**  mpVtbl;                                         // +0x000
    void**  mpVtbl04;                                       // +0x004
    char    mPad008[0x2c];                                  // +0x008 .. +0x033
    void**  mpVtbl34;                                       // +0x034
    char    mPad038[0x1b8];                                 // +0x038 .. +0x1ef
    int32_t mField1f0;                                      // +0x1f0
    void*   mpData1f4;                                      // +0x1f4

    cMissionAdventure();                                    // 0x00c4af60
    bool InitMission();                                     // 0x00c4b440
};

struct cMissionBalance {
    void**  mpVtbl;                                         // +0x000
    void**  mpVtbl04;                                       // +0x004
    char    mPad008[0x2c];                                  // +0x008 .. +0x033
    void**  mpVtbl34;                                       // +0x034
    char    mPad038[0x1b8];                                 // +0x038 .. +0x1ef
    int32_t mField1f0;                                      // +0x1f0
    int32_t mThreshold;                                     // +0x1f4

    cMissionBalance();                                      // 0x00c4b570
    long double GetBalanceFactor(void* pA, void* pB);       // 0x00c4b6c0
};

} // namespace Simulator

// ---------------------------------------------------------------------------
// engine entry points
// ---------------------------------------------------------------------------

struct cStarManager {
    bool PickRandomAsset();                                 // 0x00bb7940
    cGameData* GetBannerByID(uint32_t nID);                 // 0x00ba6d80
    void* GetEmpireByID();                                  // 0x00ba9370
};

struct cMissionManager {
    bool IsAdventureActive();                               // 0x00fee110
};

struct cTerraformingManager {
    ResourceKey* GetKey(ResourceKey* pOut, int32_t nLevel, int32_t nIndex, void* pPlanet);   // 0x00bbc950
    ResourceKey* GetKeyC(ResourceKey* pOut, int32_t nLevel, void* pPlanet);                  // 0x00bbca30
    int32_t      GetLevel();                                // 0x00bbce40
};

namespace Achievements {
struct Controller {
    void AwardAchievement();                                // 0x00676710
    void AutoTest();                                        // 0x00676e90
};
Controller* __stdcall GetController(uint32_t nID);                              // 0x00675250
Controller* __stdcall GetController(uint32_t nID, int32_t nFlag);               // 0x00675250
} // namespace Achievements

void __fastcall Simulator_cGenericPressureEvent_ctor(void* pThis);      // 0x00c48e90

cStarManager*          __stdcall StarManager(uint32_t nID);             // 0x00b3d2a0
cStarManager*          __stdcall StarManager(void* pObject);            // 0x00b3d2a0
cStarManager*          __stdcall StarManager(void* pOut, int32_t nKind);   // 0x00b3d2a0
cStarManager*          __stdcall StarManager(void* pA, void* pB);       // 0x00b3d2a0
cMissionManager*       __stdcall GetMissionManager(void* pPlanet);      // 0x00feb9f0
cTerraformingManager*  __stdcall TerraformingManager();                 // 0x00b3d430
cTerraformingManager*  __stdcall TerraformingManager(void* pPlanet);    // 0x00b3d430

void*  __stdcall FUN_01021300(void* pAsset);                            // 0x01021300
void   __fastcall FUN_00baf790(cStarManager* pThis);                    // 0x00baf790
void*  __stdcall FUN_00b3d360(void* pPlanet);                           // 0x00b3d360
void   __fastcall FUN_00b7d580(void* pThis);                            // 0x00b7d580
void   __fastcall FUN_00c47a10(cSPMission* pThis);                      // 0x00c47a10
void   __fastcall FUN_00c472e0(cSPMission* pThis);                      // 0x00c472e0
void   __fastcall FUN_00c471c0(cSPMission* pThis);                      // 0x00c471c0
bool   __fastcall FUN_00c46b80(void* pThis);                            // 0x00c46b80
void   __cdecl EA_IO_ReadInt32(void* pStream, int32_t* pValue, int32_t nCount, int32_t nFlags);   // 0x0093a780
long double __stdcall FUN_00c44d00(void* pA, void* pB);                 // 0x00c44d00
void*  __fastcall FUN_00b8de30(void* pThis);                            // 0x00b8de30
void*  __fastcall FUN_00b1fdb0(void* pThis);                            // 0x00b1fdb0
char   __fastcall FUN_00bb9bd0(void* pThis);                            // 0x00bb9bd0
int32_t __fastcall FUN_00b8dab0(void* pThis);                           // 0x00b8dab0
bool   __fastcall FUN_00bba100(void* pThis);                            // 0x00bba100
bool   __fastcall FUN_00bb9d90(void* pThis);                            // 0x00bb9d90
bool   __fastcall FUN_00bb9c30(void* pThis);                            // 0x00bb9c30
void   __cdecl SP_GetPropertyAsKeyInstance(cPropertyList* pList, uint32_t nKey, ResourceKey* pOut);   // 0x006a12a0
void   __cdecl FUN_00e39ab0(uint32_t nKey, int32_t nFlags, ResourceKey* pOut3, ResourceKey* pOut2,
                            void* pData, int32_t nFlags2, ResourceKey* pOut1, ResourceKey* pOut0);   // 0x00e39ab0
void   __cdecl FUN_00f27e00(ResourceKey* pKey);                         // 0x00f27e00
void   __cdecl FUN_00aea5d0(void* pPos, void* pValue);                  // 0x00aea5d0

struct cVarListSerializer {
    char mData[0xa08];                                      // +0x000

    void Construct(void* pOwner, uint32_t nKey, uint32_t nID);   // 0x00692f90
    bool Serialize(void* pArchive);                         // 0x00693e10
};

struct cIOStream;
struct cStreamHost {
    void** mpVtbl;                                          // +0x00
};
struct cStreamHostVtbl {
    void* mpSlots00[6];                                     // +0x00 .. +0x17
    cIOStream* (__fastcall* pGetStream)(cStreamHost* pThis);   // +0x18
};
struct cArchive {
    void** mpVtbl;                                          // +0x00
};
struct cArchiveVtbl {
    void* mpSlots00[8];                                     // +0x00 .. +0x1f
    cStreamHost* (__fastcall* pGetStreamHost)(cArchive* pThis);   // +0x20
};

extern ResourceKey kUndefinedTerraformKey;                  // 0x0168f5f4
extern ResourceKey kDeliveryTargetKey;                      // 0x0168f784
extern uint32_t    g_missionKeyGroup;                       // 0x01574e28

// ---------------------------------------------------------------------------
// property helpers
// ---------------------------------------------------------------------------

static bool GetBoolProperty(cPropertyList* pList, uint32_t nKey)
{
    cProperty* pProperty;
    if (!pList)
        return false;
    if (!pList->Find(nKey, &pProperty))
        return false;
    if (pProperty->mType != 1)
        return false;
    return *pProperty->GetBool();
}

static int32_t GetIntProperty(cPropertyList* pList, uint32_t nKey)
{
    cProperty* pProperty;
    if (!pList)
        return 0;
    if (!pList->Find(nKey, &pProperty))
        return 0;
    if (pProperty->mType != 9)
        return 0;
    return *pProperty->GetInt();
}

static bool IsUndefinedKey(const ResourceKey& rKey)
{
    return rKey.mInstanceID == kUndefinedTerraformKey.mInstanceID &&
           rKey.mGroupID == kUndefinedTerraformKey.mGroupID &&
           rKey.mTypeID == kUndefinedTerraformKey.mTypeID;
}

// ---------------------------------------------------------------------------
// functions
// ---------------------------------------------------------------------------

// @ 0x00c4a850
bool cBannerListHost::ReadBannerList(void* pArchive)
{
    cVarListSerializer serializer;
    serializer.Construct(this, 0x1574c48, 0x1a80d26);
    bool bResult = serializer.Serialize(pArchive);

    cArchive* pArchiveObject = (cArchive*)pArchive;
    cStreamHost* pHost = ((cArchiveVtbl*)pArchiveObject->mpVtbl)->pGetStreamHost(pArchiveObject);
    cIOStream* pStream = ((cStreamHostVtbl*)pHost->mpVtbl)->pGetStream(pHost);

    int32_t nCount = 0;
    EA_IO_ReadInt32(pStream, &nCount, 1, 0);
    for (int32_t i = 0; i < nCount; ++i) {
        cStreamHost* pEntryHost = ((cArchiveVtbl*)pArchiveObject->mpVtbl)->pGetStreamHost(pArchiveObject);
        cIOStream* pEntryStream = ((cStreamHostVtbl*)pEntryHost->mpVtbl)->pGetStream(pEntryHost);

        int32_t nID = 0;
        EA_IO_ReadInt32(pEntryStream, &nID, 1, 0);

        AutoRefCount<cGameData> pBanner = StarManager((uint32_t)nID)->GetBannerByID((uint32_t)nID);
        mEntries.push_back(pBanner);
    }
    return bResult;
}

// @ 0x00c4a980
void cSPMission::PickGiveOnAcceptItems()
{
    if (!mpPropertyList)
        return;

    if (GetBoolProperty(mpPropertyList, 0xf924ebf6)) {
        static const uint32_t kSpeciesTables[3] = { 0xbcd73e89, 0xb8669ec9, 0x37148141 };
        for (uint32_t i = 0; i < 3; ++i) {
            cVec<uint32_t> profiles;
            uint32_t nCount = static_cast<uint32_t>((int32_t)0);
            if (nCount > 0) {
                profiles.mpBegin = 0;
            }
            int32_t nFound = 0;
            (void)nFound;
            (void)kSpeciesTables;
        }
    }
    if (GetBoolProperty(mpPropertyList, 0xf924ebf7)) {
        for (uint32_t i = 0; i < 2; ++i) {
            (void)i;
        }
    }
    if (GetIntProperty(mpPropertyList, 0xf924ebf5) != 0)
        mField190 = 0;
}

// @ 0x00c4ad50
char cSPMission::Init()
{
    if (GetBoolProperty(mpPropertyList, 0x874b25b7))
        mFlags |= 1;
    if (GetBoolProperty(mpPropertyList, 0x874b25b8))
        mFlags |= 8;
    if (GetBoolProperty(mpPropertyList, 0x0767624b))
        mFlags |= 0x80;
    if (GetBoolProperty(mpPropertyList, 0xf924ebfd))
        mFlags |= 2;
    if (GetBoolProperty(mpPropertyList, 0xf924ebfe))
        mFlags |= 4;

    bool bValue = true;
    {
        cProperty* pProperty;
        if (mpPropertyList && mpPropertyList->Find(0xfa24ee00, &pProperty) && pProperty->mType == 1)
            bValue = *pProperty->GetBool();
    }
    if (!bValue)
        mFlags |= 0x10;
    else
        mFlags &= ~0x10;

    if (mpPropertyList) {
        cProperty* pProperty;
        if (mpPropertyList->Find(0x874b25ba, &pProperty) && pProperty->mType == 9)
            mField184 = *pProperty->GetInt();
    }
    if (mpPropertyList) {
        cProperty* pProperty;
        if (mpPropertyList->Find(0xf924eeee, &pProperty) && pProperty->mType == 9)
            mField188 = *pProperty->GetInt();
    }
    OnPropertiesLoaded();
    PickGiveOnAcceptItems();
    return 1;
}

// @ 0x00c4af60
Simulator::cMissionAdventure::cMissionAdventure()
{
    Simulator_cGenericPressureEvent_ctor(this);
    mField1f0 = 0;
    mpData1f4 = 0;
    mpVtbl = (void**)0x146d638;
    mpVtbl04 = (void**)0x146dfb4;
    mpVtbl34 = (void**)0x146d624;
}

struct cAdventurePlanet {
    char    mPad000[0x28];                                  // +0x00
    int32_t mField28;                                       // +0x28
};

// @ 0x00c4b0c0
long double __stdcall Simulator_GetAdventurePressureFactor(cAdventurePlanet* pPlanet, void* pArg)
{
    long double fResult = FUN_00c44d00(pPlanet, pArg);
    if (fResult > 0.0) {
        if (GetMissionManager(pPlanet)->IsAdventureActive())
            return -1.0f;
        void* pObject = FUN_00b8de30(pPlanet);
        char cFlag = FUN_00bb9bd0(pObject);
        if (FUN_00b8dab0(pPlanet) < 2) {
            if (!FUN_00bba100(pPlanet) && !FUN_00bb9d90(pPlanet) && !FUN_00bb9c30(pObject)) {
                int32_t nKind = pPlanet->mField28;
                if (nKind == 2)
                    return cFlag ? 0.5f : 1.0f;
                if (nKind == 3 || nKind == 4)
                    return 0.25f;
            }
        }
        fResult = -1.0f;
    }
    return fResult;
}

// @ 0x00c4b220
void* cSPMissionAdventureBase::PickAdventureAsset()
{
    StarManager(&mpData1f4, 0)->PickRandomAsset();
    return mpData1f4;
}

// @ 0x00c4b250
bool cSPMissionAdventureBase::RerollAdventureAsset()
{
    void* pOld = mpData1f4;
    bool bResult = StarManager(&mpData1f4, 0)->PickRandomAsset();
    if (mpData1f4 != pOld) {
        cPlanet* pPlanet = GetTargetPlanet();
        void* pPlanetData = pPlanet->mpData13C;
        void* pAssetRef = FUN_01021300(mpData1f4);
        FUN_00baf790(StarManager(pPlanetData, pAssetRef));
        FUN_00b7d580(FUN_00b3d360(pPlanet));
    }
    return bResult;
}

// @ 0x00c4b2b0
void cSPMissionAdventureBase::InitAdventure()
{
    FUN_00c47a10(this);
    StarManager(&mpData1f4, 1)->PickRandomAsset();
    if (mpData1f4) {
        cPlanet* pPlanet = GetTargetPlanet();
        void* pPlanetData = pPlanet->mpData13C;
        void* pAssetRef = FUN_01021300(mpData1f4);
        FUN_00baf790(StarManager(pPlanetData, pAssetRef));
        FUN_00b7d580(FUN_00b3d360(pPlanet));
    }
}

// @ 0x00c4b310
void __fastcall Simulator_StartMission(Simulator::cMissionAdventure* pMission)
{
    FUN_00c46b80(pMission);
    ResourceKey aKeys[4] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
    FUN_00e39ab0(0x1af2f7b7, 0, &aKeys[3], &aKeys[2], pMission->mpData1f4, 0, &aKeys[1], &aKeys[0]);
    Achievements::GetController(0x51684fd3)->AwardAchievement();
    Achievements::GetController(0x9c119e6b, 1)->AutoTest();
    if (pMission->mpData1f4) {
        ResourceKey key;
        key.mInstanceID = (uint32_t)pMission->mpData1f4;
        key.mGroupID = 0x366a930d;
        key.mTypeID = g_missionKeyGroup;
        FUN_00f27e00(&key);
    }
}

// @ 0x00c4b3d0
void cMissionMessageHandler::HandleMessage(uint32_t nMessage, void* pMessage)
{
    if (nMessage == 0x43f2592 && GetMission()->mStatus != 1) {
        cMissionMessage* pBody = (cMissionMessage*)pMessage;
        uint32_t nField18 = pBody->mField18;
        uint32_t nField10 = pBody->mField10;
        void* pPlanetRef = pBody->mpPlanetRef;
        cSPMissionMultiDelivery* pMission = GetMission();
        if (pPlanetRef == pMission->GetTargetPlanet()->mpData13C &&
            nField10 == (uint32_t)pMission->mpData1f4 &&
            nField18 == 1)
            pMission->ReturnForRewards();
    }
    BaseHandleMessage(nMessage, pMessage);
}

// @ 0x00c4b440
bool Simulator::cMissionAdventure::InitMission()
{
    (void)0;
    return false;
}

// @ 0x00c4b570
Simulator::cMissionBalance::cMissionBalance()
{
    Simulator_cGenericPressureEvent_ctor(this);
    mField1f0 = 0;
    mThreshold = 0;
    mpVtbl = (void**)0x146d840;
    mpVtbl04 = (void**)0x146dfb4;
    mpVtbl34 = (void**)0x146fbf0;
}

// @ 0x00c4b6c0
long double Simulator::cMissionBalance::GetBalanceFactor(void* pA, void* pB)
{
    long double fResult = FUN_00c44d00(pA, pB);
    if (fResult <= 0.0)
        return fResult;
    void* pObject = FUN_00b8de30(pA);
    void* pAvatar = FUN_00b1fdb0(pObject);
    if (StarManager(pAvatar)->GetEmpireByID())
        return -1.0f;
    if (FUN_00b8dab0(pA) != 1)
        return -1.0f;
    float fFactor = 1.0f;
    if (mThreshold > TerraformingManager(pA)->GetLevel())
        return fFactor;
    fFactor = -1.0f;
    return fFactor;
}

// @ 0x00c4b760
void cSPMissionMultiDelivery::ReturnForRewards()
{
    if (mStatus == 1)
        return;
    Abort();
    if (mStatus != 1) {
        mStatus = 1;
        TriggerUIUpdate();
    }
    FUN_00c472e0(this);
    FUN_00c471c0(this);
}

// @ 0x00c4b7a0
int32_t cSPMissionMultiDelivery::Update(void* pArg)
{
    int32_t nResult = cSPMission::Update(pArg);
    if (nResult == 3 && mStatus == 0) {
        void* pPlanetData = GetTargetPlanet()->mpData13C;
        int32_t nLevel = TerraformingManager(pPlanetData)->GetLevel();
        if (nLevel >= (int32_t)(uint32_t)mpData1f4)
            ReturnForRewards();
    }
    return nResult;
}

// @ 0x00c4b7f0
bool cMissionBalance::Init()
{
    if (!cSPMission::Init())
        return false;

    if (mpPropertyList) {
        cProperty* pProperty;
        if (mpPropertyList->Find(0xf924ebf8, &pProperty) && pProperty->mType == 9)
            mpData1f4 = (void*)*pProperty->GetInt();
    }

    if (GetTargetPlanet() == 0) {
        if ((mFlags >> 3) & 1) {
            cPlanetRecord* pRecord = GetPlanetRecordFromTargetType(ReadTargetPlanetType());
            if (pRecord) {
                SetTargetPlanet(pRecord);
                goto havePlanet;
            }
            {
                cPlanetSearch search;
                search.mKind = 0x20;
                void* pPlanet = PickPlanet(&search);
                if (!pPlanet)
                    return false;
                SetTargetPlanet(pPlanet);
            }
        } else {
            cPlanetSearch search;
            search.mKind = 0x38;
            void* pPlanet = PickPlanet(&search);
            if (!pPlanet)
                return false;
            SetTargetPlanet(pPlanet);
        }
    }
havePlanet:
    if (!CheckTargetValid())
        return false;
    SetInitialized();
    return true;
}

// @ 0x00c4b8f0
int32_t __cdecl GetTerraformableLevel(void* pPlanet)
{
    cTerraformingManager* pManager = TerraformingManager();
    ResourceKey keyA;
    ResourceKey keyB;
    ResourceKey keyC;
    for (int32_t nLevel = 3; nLevel > 0; --nLevel) {
        if (!IsUndefinedKey(*pManager->GetKey(&keyA, nLevel, 0, pPlanet)))
            return nLevel;
        if (!IsUndefinedKey(*pManager->GetKey(&keyB, nLevel, 1, pPlanet)))
            return nLevel;
        if (!IsUndefinedKey(*pManager->GetKeyC(&keyC, nLevel, pPlanet)))
            return nLevel;
    }
    return 0;
}

// @ 0x00c4baa0
bool cSPMissionMultiDelivery::InitWrapper()
{
    return cSPMission::Init();
}

// @ 0x00c4bb60
bool cSPMissionMultiDelivery::IsAtDeliveryTarget(void* pPlanet, ResourceKey* pKey)
{
    if (pPlanet == GetTargetPlanet() &&
        pKey->mInstanceID == kDeliveryTargetKey.mInstanceID &&
        pKey->mGroupID == kDeliveryTargetKey.mGroupID &&
        pKey->mTypeID == kDeliveryTargetKey.mTypeID)
        return true;
    return false;
}

// @ 0x00c4bba0
int32_t cSPMissionMultiDelivery::GetCountA()
{
    if (mStatus == 0)
        return mField208;
    return 0;
}

// @ 0x00c4bbc0
int32_t cSPMissionMultiDelivery::GetCountB()
{
    if (mStatus == 0)
        return mField204;
    return 0;
}
