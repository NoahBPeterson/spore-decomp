// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 43 / slice s00bf4170.
//
// Civilization community editor: city list maintenance (add / remove / reduce),
// city-music editor creation, vehicle creation from a stored terrain-sphere model
// type, and the small keyed-vector helpers shared by those paths.

typedef unsigned int size_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef int intptr_t;
#define nullptr 0

class cCity;
class cCommunityEditor;
class cTerrainSphere;
class cPlayerCityMusic;
void operator_delete__(void* pMemory);
cPlayerCityMusic* CreateMusicForSpecialty(int nSpecialty);
void MapInsertNode(int* pParent, uint32_t key, const void* pValue);

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

// ---------------------------------------------------------------------------
// Minimal object model
// ---------------------------------------------------------------------------

class IRefCounted {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);   // 0x0c
    virtual void v10();
};

class cGameData : public IRefCounted {
public:
    uint8_t mPad14[0x20];
};

class cEditorObject : public cGameData {
public:
    Vec3 mPosition;                 // 0x34
    uint8_t mPad40[0x10];
    void* GetIcon();                // 0x50
    uint8_t mPad54[0xac8];
    int mCityKind;                  // 0xb1c
    int mCityLevel;                 // 0xb20
};

class cCity : public cEditorObject {
public:
    int GetVehicleSpecialty();      // 0x94 via terrain sphere, direct here
    void* GetCityHall();            // 0xa4
};

class cPlayerCityMusic : public IRefCounted {
public:
    cPlayerCityMusic();
    void PlayMelody(int bLoop);
    uint8_t mPad14[0x20c];
};

class cTerrainEditor : public IRefCounted {
public:
    cTerrainSphere* GetCurrentTerrainSphere();
};

// Terrain sphere stores the last decoded "city model" record at 0x1150.
class cTerrainSphere {
public:
    uint8_t mPad00[0x1150];         // 0x00
    uint32_t mModelKind;            // 0x1150
    uint32_t mModelA;               // 0x1154
    uint32_t mModelB;               // 0x1158
    Vec3 mModelPosition;            // 0x115c
    uint32_t mModelFlags;           // 0x1168
};

class cGameNounManager : public IRefCounted {
public:
    cCommunityEditor* GetPlayerCivilization();
    void RemoveNoun(void* pNoun);
};

class cBehaviorManager {
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
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void AddRemoveObject(void* pObject);   // 0x3c
};

class cMessageServer {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SendMessage(uint32_t msgId, void* pMessage, int bSync);  // 0x14
};

class cSPUIEventLog {
public:
    void RemoveAllEventsOfSameType(int type);
};

cSPUIEventLog* EventLog(int type, ...);
cGameNounManager* NounManager();
cGameNounManager* NounManager(int type);
cBehaviorManager* BehaviorManager();
cMessageServer* MessageServer();
void* GetCurrentGameMode();
void* GetTerrainEditorObject();
void* cTerrainEditorStatic();

extern uint8_t gGameModeCivilization;
extern uint8_t gGameModeSpace;

// A small fixed-capacity map used by the terrain-sphere model records.
class cVector3Map {
public:
    uint8_t mPad00[0x04];           // 0x00
    int* mpRoot;                    // 0x04
    int* mpNil;                     // 0x08
    int* mpHead;                    // 0x0c
    uint8_t mPad10[0x08];           // 0x10
    int mCount;                     // 0x18

    Vec3* FindOrInsert(uint32_t key);   // 0x00bf5050
};

// ---------------------------------------------------------------------------
// Community editor
// ---------------------------------------------------------------------------

class cCommunityEditor : public cEditorObject {
public:
    // Editor flags used by the city-reduction paths.
    uint8_t mBadgeToasterShown;      // 0x89
    uint8_t mCityBadgeReady;         // 0x8a
    uint8_t mOneCityBadgeShown;      // 0x8b
    uint8_t mPad8c[0x06];
    uint8_t mCitiesInitialized;      // 0x92
    uint8_t mPad93[0x09];
    cCity** mpCitiesBegin;           // 0x9c
    cCity** mpCitiesEnd;             // 0xa0
    cCity** mpCitiesCap;             // 0xa4
    uint8_t mPadA8[0x08];
    void** mpRemovedBegin;           // 0xb0
    void** mpRemovedEnd;             // 0xb4
    uint8_t mPadB8[0x0c];
    Vec3 mSpawnPosition;             // 0xc4
    uint8_t mPadD0[0x1a4];
    cPlayerCityMusic* mpCityMusicEditor;  // 0x274
    uint8_t mPad278[0x1e0];
    IRefCounted* mpTrackedRefA;      // 0x458
    IRefCounted* mpTrackedRefB;      // 0x45c
    IRefCounted* mpTrackedRefC;      // 0x460
    uint8_t mPad464[0x6c];
    int mMaxCityCount;               // 0x4d0

    void InsertCityAt(int* pPosition, cCity* pCity, int nCount);   // 0x00bf4170
    cCommunityEditor* AttachCity(cCity* pCity);                     // 0x00bf4350
    void ReduceCitiesOnPlanet(cCity* pCity);                        // 0x00bf4370
    void DetachCity(cCity* pCity, int bRemoving);                   // 0x00bf45f0
    void NotifySubEditor();                                         // 0x00bf49e0
    void CreateVehicleFromModelType(cCity* pCity, const Vec3* pPosition);  // 0x00bf4b10
    void RemoveAllCities(cCity* pCity);                             // 0x00bf4e50
    void RebuildCityFromTerrainSphere();                            // 0x00bf4eb0
    void CreateVehicleFromTerrainSphere();                          // 0x00bf4fc0
};

void CityAddRef(cCity* pCity);
void CityRelease(cCity* pCity);
void CityDestroyContents(cCity* pCity);
void CompanionReleaseContents(void* pObject);
void CityListAppend(cCommunityEditor* pEditor, cCity** pPosition, cCity* pCity);
void CityVectorGrow(cCommunityEditor* pEditor, int nCount);
void CityVectorShift(cCity** pSource, cCity** pDest, cCity** pEnd);
void CityVectorCopyFill(cCity** pDest, cCity** pSource, cCity** pEnd);
void CityVectorShiftDown(cCity** pDest, cCity** pSource, cCity** pEnd, cCity** pSlot);

void SetModelTypeKey(int* pKey, const Vec3* pValue);         // 0x00bf4a60
void ResetVector3Map(cCommunityEditor* pEditor);              // 0x00bf4a90
void ReduceCitiesForPlanet(cCommunityEditor* pEditor);        // 0x00be1150
void RefreshCityBadges();                                     // 0x00bf0f90
void RefreshCityCount();                                      // 0x00bf23d0
void RefreshCityStatistics(cCommunityEditor* pEditor);        // 0x00bf3b50
void RecomputeCommunityScore(cCommunityEditor* pEditor);      // 0x00be45b0
uint32_t GetCityCountTarget();                                // 0x00befd30
void SetCityDensity(int nDensity);                            // 0x00bef770
void ClearCitySelection();                                    // 0x00cf74c0
void ShowCityLimitToast();                                    // 0x00cf7510
void ShowCityLimitToastLong();                                // 0x00cf7500
void ShowOneCityBadge();                                      // 0x00cf7920
void UpdateCityInfoPanel(cCommunityEditor* pEditor);          // 0x00e06630
void UpdateCityBoundaries(uint32_t id);                       // 0x00c77bf0
int GetActivePlanetTier();                                    // 0x00b8dab0
int GetCityHallIcon();                                        // 0x00c710c0
void* GetCityHallEntry(int nIndex);                           // 0x00c71030
void* GetNodeParent(void* pNode);                             // 0x00c710c0
void RemoveCityHallEntry(int nIndex);                         // 0x00c71150
void UpdateCommunityCamera(cCommunityEditor* pEditor);        // 0x00e052d0
void MessageServerPost(uint32_t msgId, void* pMessage);       // inlined message post
void* SpaceGameGet();
bool IsSpaceLevelReady();                                     // 0x00b18e40
void CityVehicleCreateHook(void* pUnused);                    // 0x00be4a10

// ---------------------------------------------------------------------------
// 0x00bf4170  cCommunityEditor::InsertCityAt
// ---------------------------------------------------------------------------
// @ 0x00bf4170
void cCommunityEditor::InsertCityAt(int* pPosition, cCity* pCity, int nCount)
{
    uint32_t nCapacityLeft = (uint32_t)(mpCitiesCap - mpCitiesBegin);
    if (nCapacityLeft < (uint32_t)nCount) {
        uint32_t nSize = (uint32_t)(mpCitiesEnd - mpCitiesBegin);
        uint32_t nGrow = nSize * 2;
        if (nSize == 0)
            nGrow = 1;
        uint32_t nNewCap = nSize + (uint32_t)nCount;
        if (nNewCap < nGrow)
            nNewCap = nGrow;

        cCity** pNew = nullptr;
        if (nNewCap != 0)
            pNew = (cCity**)new uint8_t[nNewCap * 4];

        cCity** pSlot = pNew + ((cCity**)pPosition - mpCitiesBegin);
        for (cCity** pCur = mpCitiesBegin; pCur != (cCity**)pPosition; ++pCur)
            *pSlot++ = *pCur;

        for (int i = 0; i < nCount; ++i)
            *pSlot++ = pCity;

        for (cCity** pCur = (cCity**)pPosition; pCur != mpCitiesEnd; ++pCur)
            *pSlot++ = *pCur;

        if (mpCitiesBegin != nullptr)
            operator_delete__(mpCitiesBegin);

        mpCitiesBegin = pNew;
        mpCitiesEnd = pSlot;
        mpCitiesCap = pNew + nNewCap;
        return;
    }

    if (nCount == 0)
        return;

    CityAddRef(pCity);

    uint32_t nTail = (uint32_t)(mpCitiesEnd - (cCity**)pPosition);
    if ((uint32_t)nCount < nTail) {
        cCity** pMove = mpCitiesEnd - nCount;
        CityVectorShift(pMove, mpCitiesEnd, mpCitiesEnd);
        mpCitiesEnd += nCount;
        CityVectorCopyFill((cCity**)pPosition + nCount, (cCity**)pPosition, pMove);
        CityVectorShiftDown((cCity**)pPosition, (cCity**)pPosition + nCount, pMove, (cCity**)pPosition);
    } else {
        for (int i = 0; i < nCount - (int)nTail; ++i)
            mpCitiesEnd[i] = pCity;
        mpCitiesEnd += nCount - nTail;
        CityVectorShift((cCity**)pPosition, mpCitiesEnd, mpCitiesEnd);
        mpCitiesEnd += nTail;
        CityVectorCopyFill((cCity**)pPosition, (cCity**)pPosition + nCount, mpCitiesEnd);
    }

    if (pCity != nullptr)
        CityRelease(pCity);
}

// ---------------------------------------------------------------------------
// 0x00bf4350  cCommunityEditor::AttachCity
// ---------------------------------------------------------------------------
// @ 0x00bf4350
cCommunityEditor* cCommunityEditor::AttachCity(cCity* pCity)
{
    CityAddRef(pCity);
    return this;
}

// ---------------------------------------------------------------------------
// 0x00bf4370  cCommunityEditor::ReduceCitiesOnPlanet
// ---------------------------------------------------------------------------
// @ 0x00bf4370
void cCommunityEditor::ReduceCitiesOnPlanet(cCity* pCity)
{
    if (pCity == nullptr)
        return;

    if (mpCityMusicEditor == nullptr) {
        if (mBadgeToasterShown == 0) {
            cPlayerCityMusic* pMusic = new cPlayerCityMusic();
            mpCityMusicEditor = pMusic;
        } else {
            int nSpecialty = pCity->GetVehicleSpecialty();
            mpCityMusicEditor = (cPlayerCityMusic*)CreateMusicForSpecialty(nSpecialty);
        }
    }

    if (mpCitiesBegin == mpCitiesEnd) {
        if (mpCityMusicEditor != nullptr)
            mpCityMusicEditor->PlayMelody(0);
    }

    CityAddRef(pCity);

    if (mpCitiesEnd < mpCitiesCap) {
        *mpCitiesEnd++ = pCity;
    } else {
        CityListAppend(this, mpCitiesEnd, pCity);
    }

    CityRelease(pCity);

    ReduceCitiesForPlanet(this);
    RefreshCityBadges();

    if (mpCityMusicEditor != nullptr && mpCityMusicEditor->Query((void*)0x4223298) != nullptr)
        mpCityMusicEditor->PlayMelody(0);

    uint32_t nCount = (uint32_t)(mpCitiesEnd - mpCitiesBegin);
    uint32_t nTarget = GetCityCountTarget();
    if (nCount < nTarget) {
        if (nCount > 3)
            SetCityDensity(3);
        else if (nCount != 0)
            SetCityDensity(2);
    } else {
        SetCityDensity(4);
    }

    if (GetCurrentGameMode() == &gGameModeCivilization) {
        void* pCityHall = pCity->GetCityHall();
        IRefCounted* pIcon = nullptr;
        if (pCityHall != nullptr)
            pIcon = (IRefCounted*)GetCityHallIcon();
        ClearCitySelection();
        ShowCityLimitToastLong();

        cGameNounManager* pNouns = NounManager();
        cCommunityEditor* pPlayer = pNouns->GetPlayerCivilization();
        if (pPlayer != this && mOneCityBadgeShown == 0 && (mpCitiesEnd - mpCitiesBegin) == 2) {
            mOneCityBadgeShown = 1;
            ClearCitySelection();
            ShowCityLimitToast();
            UpdateCityInfoPanel(this);
            uint32_t nSphere = (uint32_t)GetTerrainEditorObject();
            UpdateCityBoundaries(nSphere);
            pNouns = NounManager();
            pPlayer = pNouns->GetPlayerCivilization();
            if (pPlayer->mpCitiesBegin != pPlayer->mpCitiesEnd) {
                ClearCitySelection();
                ShowOneCityBadge();
            }
        }
    }

    mCitiesInitialized = 1;

    if (GetCurrentGameMode() != &gGameModeCivilization) {
        if (GetActivePlanetTier() != 4)
            goto done;
    }
    RefreshCityCount();

done:
    if (mMaxCityCount < (mpCitiesEnd - mpCitiesBegin))
        mMaxCityCount = (int)(mpCitiesEnd - mpCitiesBegin);
}

// ---------------------------------------------------------------------------
// 0x00bf45f0  cCommunityEditor::DetachCity
// ---------------------------------------------------------------------------
// @ 0x00bf45f0
void cCommunityEditor::DetachCity(cCity* pCity, int bRemoving)
{
    if (this != nullptr)
        AddRef();

    if (pCity == nullptr) {
        Release();
        return;
    }

    if (mpTrackedRefA == pCity) {
        IRefCounted* pOld = mpTrackedRefA;
        mpTrackedRefA = nullptr;
        pOld->Release();
    }
    if (mpTrackedRefB == pCity) {
        IRefCounted* pOld = mpTrackedRefB;
        mpTrackedRefB = nullptr;
        pOld->Release();
    }
    if (mpTrackedRefC == pCity) {
        IRefCounted* pOld = mpTrackedRefC;
        mpTrackedRefC = nullptr;
        pOld->Release();
    }

    if (GetCurrentGameMode() == &gGameModeCivilization && bRemoving == 0 &&
        (mpCitiesEnd - mpCitiesBegin) == 1) {
        static const int sEventIds[5] = {0, 0, 0, 0, 0};
        for (int i = 0; i < 5; ++i) {
            uint32_t nId = (uint32_t)sEventIds[i];
            uint32_t nTag = (uint32_t)(intptr_t)this->Query((void*)0x4c);
            EventLog((int)nId, 0, (int)nTag)->RemoveAllEventsOfSameType((int)nId);
        }
    }

    cCity** pSlot = mpCitiesBegin;
    while (pSlot != mpCitiesEnd && *pSlot != pCity)
        ++pSlot;
    if (pSlot != mpCitiesEnd) {
        for (cCity** pCur = pSlot; pCur + 1 != mpCitiesEnd; ++pCur)
            *pCur = pCur[1];
        --mpCitiesEnd;
    }

    ReduceCitiesForPlanet(this);

    CityAddRef(pCity);
    const void* pKey = (const void*)pCity;
    (void)pKey;
    CityRelease(pCity);

    if (mpCitiesBegin == mpCitiesEnd && GetCurrentGameMode() != &gGameModeSpace)
        RefreshCityCount();

    if (mpCitiesBegin == mpCitiesEnd && mpTrackedRefC != nullptr)
        CompanionReleaseContents(mpTrackedRefC);
    else
        RefreshCityBadges();

    if (bRemoving == 0) {
        if (mpCitiesBegin != mpCitiesEnd)
            RefreshCityStatistics(this);

        RecomputeCommunityScore(this);
        if (mpCitiesBegin == mpCitiesEnd && mpRemovedBegin != mpRemovedEnd) {
            while (mpRemovedBegin != mpRemovedEnd) {
                void* pNoun = mpRemovedEnd[-1];
                void* pTarget = nullptr;
                if (pNoun != nullptr) {
                    ((IRefCounted*)pNoun)->AddRef();
                    pTarget = (uint8_t*)pNoun + 0x5d0;
                }
                BehaviorManager()->AddRemoveObject(pTarget);
                RefreshCityStatistics((cCommunityEditor*)pNoun);
                NounManager()->RemoveNoun(pTarget);
                if (pNoun != nullptr)
                    ((IRefCounted*)pNoun)->Release();
            }
        }

        if (mpCitiesBegin == mpCitiesEnd && mBadgeToasterShown == 0) {
            ClearCitySelection();
            ShowCityLimitToast();
            UpdateCommunityCamera(this);

            if (GetCurrentGameMode() == &gGameModeSpace) {
                int nCount = GetCityHallIcon();
                for (int i = 0; i < nCount; ++i) {
                    void* pNode = GetCityHallEntry(i);
                    void* pParent = GetNodeParent(pNode);
                    if (pParent == this->Query((void*)0x4c)) {
                        RemoveCityHallEntry(i);
                        break;
                    }
                }
            }

            uint32_t msgId = 0x4b33710;
            MessageServerPost(msgId, this);
            NounManager()->RemoveNoun(this);
        }
    }

    Release();
}

// ---------------------------------------------------------------------------
// 0x00bf49e0  cCommunityEditor::NotifySubEditor
// ---------------------------------------------------------------------------
// @ 0x00bf49e0
void cCommunityEditor::NotifySubEditor()
{
    if (this == nullptr)
        return;
    void* pSub = Query((void*)0xee9b2232);
    if (pSub != nullptr) {
        int bFlag = 0;
        if (GetCurrentGameMode() == &gGameModeSpace) {
            SpaceGameGet();
            bFlag = IsSpaceLevelReady() ? 1 : 0;
        }
        ((cCommunityEditor*)pSub)->DetachCity((cCity*)this, bFlag);
        return;
    }
    void* pOther = Query((void*)0x137e8e0);
    if (pOther != nullptr)
        RefreshCityStatistics((cCommunityEditor*)pOther);
}

// ---------------------------------------------------------------------------
// 0x00bf4a60  SetModelTypeKey
// ---------------------------------------------------------------------------
// @ 0x00bf4a60
void SetModelTypeKey(int* pKey, const Vec3* pValue)
{
    Vec3* pSlot = ((cVector3Map*)pKey)->FindOrInsert((uint32_t)pKey);
    *pSlot = *pValue;
}

// ---------------------------------------------------------------------------
// 0x00bf4a90  ResetVector3Map
// ---------------------------------------------------------------------------
// @ 0x00bf4a90
void ResetVector3Map(cCommunityEditor* pEditor)
{
    cVector3Map* pMap = (cVector3Map*)pEditor;
    pMap->mpRoot = nullptr;
    pMap->mpHead = (int*)&pMap->mpRoot;
    pMap->mpNil = (int*)&pMap->mpRoot;
    pMap->mPad10[0] = 0;
    pMap->mCount = 0;

    for (uint32_t nKey = 0; nKey < 5; ++nKey) {
        Vec3 zero;
        zero.mX = 0.0f;
        zero.mY = 0.0f;
        zero.mZ = 0.0f;
        SetModelTypeKey((int*)nKey, &zero);
    }
    for (uint32_t nKey = 5; nKey < 18; ++nKey) {
        Vec3 zero;
        zero.mX = 0.0f;
        zero.mY = 0.0f;
        zero.mZ = 0.0f;
        SetModelTypeKey((int*)nKey, &zero);
    }
}

// ---------------------------------------------------------------------------
// 0x00bf4b10  cCommunityEditor::CreateVehicleFromModelType
// ---------------------------------------------------------------------------
// @ 0x00bf4b10
void cCommunityEditor::CreateVehicleFromModelType(cCity* pCity, const Vec3* pPosition)
{
    SetModelTypeKey((int*)pCity, pPosition);

    uint32_t nModel = (uint32_t)(intptr_t)pCity;
    int nKind = 0;
    int nLevel = 0;

    switch (nModel) {
    case 0x1f2a25b6:
        nKind = 1;
        nLevel = 1;
        break;
    case 0x2090a11b:
    case 0x1a4e0708:
        nKind = 2;
        nLevel = 2;
        break;
    case 0x2a5147a9:
        nKind = 2;
        nLevel = 1;
        break;
    case 0x441cd3e6:
        nKind = 0;
        nLevel = 1;
        break;
    case 0x449c040f:
        nKind = 1;
        nLevel = 2;
        break;
    case 0x47c10953:
    case 0x4e3f7777:
    case 0x72c49181:
        RefreshCityStatistics(this);
        nKind = 0;
        nLevel = 0;
        break;
    case 0x7d433fad:
        nKind = 0;
        nLevel = 0;
        break;
    case 0x9ad7d4aa:
        nKind = 1;
        nLevel = 0;
        break;
    case 0xf670aa43:
    case 0xbe105f3e:
    case 0xc0b74287:
        nKind = 2;
        nLevel = 0;
        break;
    default:
        return;
    }

    int nCount = (int)(mpCitiesEnd - mpCitiesBegin);
    for (int i = 0; i < nCount; ++i) {
        cCity* pEntry = mpCitiesBegin[i];
        if (pEntry->mCityKind == nLevel &&
            (GetCurrentGameMode() == &gGameModeSpace || pEntry->mCityLevel == nKind)) {
            ((IRefCounted*)pEntry->GetIcon())->Query(pPosition);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00bf4e50  cCommunityEditor::RemoveAllCities
// ---------------------------------------------------------------------------
// @ 0x00bf4e50
void cCommunityEditor::RemoveAllCities(cCity* pCity)
{
    CityAddRef(pCity);
    int nCount = (int)(mpCitiesEnd - mpCitiesBegin);
    for (int i = 0; i < nCount; ++i)
        CityVehicleCreateHook(this);
}

// ---------------------------------------------------------------------------
// 0x00bf4eb0  cCommunityEditor::RebuildCityFromTerrainSphere
// ---------------------------------------------------------------------------
// @ 0x00bf4eb0
void cCommunityEditor::RebuildCityFromTerrainSphere()
{
    cTerrainEditor* pTerrain = (cTerrainEditor*)NounManager();
    cTerrainSphere* pSphere = pTerrain->GetCurrentTerrainSphere();
    if (pSphere->mModelB == 0)
        return;

    Vec3 position;
    position.mX = (float)pSphere->mModelKind;
    position.mY = (float)pSphere->mModelA;
    position.mZ = (float)pSphere->mModelB;
    SetModelTypeKey((int*)0x99e92f05, &position);

    RemoveAllCities((cCity*)0x9c);

    Vec3 stored;
    stored.mX = (float)pSphere->mModelKind;
    stored.mY = (float)pSphere->mModelA;
    stored.mZ = (float)pSphere->mModelB;
    SetModelTypeKey((int*)0x99e92f05, &stored);
}

// ---------------------------------------------------------------------------
// 0x00bf4fc0  cCommunityEditor::CreateVehicleFromTerrainSphere
// ---------------------------------------------------------------------------
// @ 0x00bf4fc0
void cCommunityEditor::CreateVehicleFromTerrainSphere()
{
    cTerrainEditor* pTerrain = (cTerrainEditor*)NounManager();
    cTerrainSphere* pSphere = pTerrain->GetCurrentTerrainSphere();
    if (pSphere->mModelPosition.mZ == 0.0f)
        return;

    NounManager();
    cCity* pCity = (cCity*)GetTerrainEditorObject();
    int nSpecialty = pCity->GetVehicleSpecialty();

    uint32_t nModel;
    if (nSpecialty == 0)
        nModel = 0x7d433fad;
    else if (nSpecialty == 1)
        nModel = 0x9ad7d4aa;
    else
        nModel = 0xf670aa43;

    CreateVehicleFromModelType((cCity*)(intptr_t)nModel, &pSphere->mModelPosition);

    Vec3 stored = pSphere->mModelPosition;
    SetModelTypeKey((int*)nModel, &stored);
}

// ---------------------------------------------------------------------------
// 0x00bf5050  cVector3Map::FindOrInsert
// ---------------------------------------------------------------------------
// @ 0x00bf5050
Vec3* cVector3Map::FindOrInsert(uint32_t key)
{
    int* pHeader = (int*)&mpRoot;
    int* pLower = pHeader;

    if (mpHead != nullptr) {
        int* pNode = mpHead;
        do {
            int* pNext;
            if ((uint32_t)pNode[4] < key) {
                pNext = (int*)*pNode;
            } else {
                pNext = (int*)pNode[1];
                pLower = pNode;
            }
            pNode = pNext;
        } while (pNode != nullptr);
    }

    if (pLower == pHeader || key < (uint32_t)pLower[4]) {
        Vec3 value;
        value.mX = 0.0f;
        value.mY = 0.0f;
        value.mZ = 0.0f;
        MapInsertNode(pLower, key, &value);
    }
    return (Vec3*)(pLower + 5);
}
