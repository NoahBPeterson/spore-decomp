// Slice s00feff80 -- the city / civilisation / tribe saved-data views: the serialiser entry points of
// cCityData and cCivData, the town turret and building bookkeeping, the model-key lookups used by the
// terrain-sphere rules and the tribe payload constructors.
//
//   0x00feff80  unnamed                              -- pick and spawn tribesmen for a city.
//   0x00ff0330  cCityData::TestNameBit               -- one bit of a name word.
//   0x00ff0350  cCityData::AddValue                  -- accumulate a float, clamped at zero.
//   0x00ff03d0  sGetIndexFromModelType               -- index of a model key in sStoredModelKeys.
//   0x00ff0400  cCityData::GetPercent                -- share of mField20 in mField20 + mNumBuildings.
//   0x00ff0430  cCityData::SetPosition               -- copy a position into the city.
//   0x00ff0450  cCityData::Write                     -- serialise the city (value-copy word form).
//   0x00ff04d0  cCityData::WriteRaw                  -- serialise the city (pointer word form).
//   0x00ff05d0  sWriteUint16                         -- write one word through a stream.
//   0x00ff0610  cTribeData::cTribeData               -- tribe payload built from a live tribe.
//   0x00ff06a0  cTribeData::cTribeData               -- tribe payload from a population/food pair.
//   0x00ff0700  cTribeData::cTribeData               -- empty tribe payload.
//   0x00ff0760  cCityData::GetNumTurrets             -- number of set turret bits.
//   0x00ff07a0  cCityData::GetBuilding               -- indexed building record.
//   0x00ff07e0  cCityData::RemoveTurret              -- clear one turret bit and its building.
//   0x00ff0870  cCityData::GetNumBuildings           -- building count without the turrets.
//   0x00ff08b0  cCityData::SetThreatLevel            -- threat level of a city and its district flag.
//   0x00ff0940  cCivData::CopyTerrainKeys            -- terrain-sphere specific model key copies.
//   0x00ff0cd0  cCivData::GetResourceKey             -- model key of a noun's resource type.
//   0x00ff0db0  cSpatialSnapshot::Init               -- position and ids of a noun.
//   0x00ff0df0  cSpatialSnapshot::Set                -- position and ids from a vector and two ints.
//   0x00ff0e20  cCivData::Write                      -- serialise the city and vehicle lists.
//   0x00ff0f30  WriteSTLSequenceT<cBuildingData>     -- serialise a building sequence.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

namespace EA { namespace IO {
class IStream;
bool WriteUint16(IStream* pStream, const uint32_t* pValue, uint32_t nCount, int nFlags);     // 0x0093a9d0
bool WriteUint16Raw(IStream* pStream, const uint16_t* pValue, uint32_t nCount, int nFlags);  // 0x0093a700
bool WriteUint32(IStream* pStream, const uint32_t* pValue, uint32_t nCount, int nFlags);     // 0x0093aa70
} }

namespace SP {

struct Vec3 { float x, y, z; };

// three raw words: the header of a city record
struct cInt3 {
    int32_t x;    // +0x00
    int32_t y;    // +0x04
    int32_t z;    // +0x08
};

// a spatial position: three floats that the original also moves as three raw words
struct cVector3 {
    union {
        struct { float x; float y; float z; };                    // +0x00
        struct { int32_t mWord0; int32_t mWord1; int32_t mWord2; };
    };
};

// copy a position float by float
static inline void CopyPositionFloats(cVector3* pDest, const cVector3* pSource)
{
    pDest->x = pSource->x;
    pDest->y = pSource->y;
    pDest->z = pSource->z;
}

// copy a position word by word
static inline void CopyPositionWords(cVector3* pDest, const cVector3* pSource)
{
    pDest->mWord0 = pSource->mWord0;
    pDest->mWord1 = pSource->mWord1;
    pDest->mWord2 = pSource->mWord2;
}

// ---------------------------------------------------------------------------
// model keys (12 bytes each) shared by every civ / city record
// ---------------------------------------------------------------------------
struct cResourceKey {
    uint32_t mModelType;    // +0x00
    uint32_t mField04;      // +0x04
    uint32_t mField08;      // +0x08
};

extern int32_t sStoredModelKeys[16];                                          // 0x015b4df8
bool sGetIndexFromModelType(uint32_t modelType, uint32_t* pIndex);           // 0x00ff03d0

// index of a model key in sStoredModelKeys, zero when the key is absent
static inline uint32_t FindModelKeyIndex(uint32_t modelType)
{
    for (int i = 0; i < 16; ++i) {
        if (sStoredModelKeys[i] == (int32_t)modelType)
            return (uint32_t)i;
    }
    return 0;
}

// population count of the low eight bits (turret mask)
static inline int CountBits(uint32_t bits)
{
    uint32_t v = bits;
    v = v - ((v >> 1) & 0x55555555u);
    v = (v & 0x33333333u) + ((v >> 2) & 0x33333333u);
    v = (v + (v >> 4)) & 0x0f0f0f0fu;
    return (int)((v * 0x01010101u) >> 24);
}

// ---------------------------------------------------------------------------
// EA stream objects (only the used vtable slots are named)
// ---------------------------------------------------------------------------
class cStreamPos {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual int Tell(int n); virtual void Seek(int n, int nOrigin);
};

class cStreamPos;

class cStreamWriter {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5();
    virtual EA::IO::IStream* GetStream();                     // +0x18
};

class cOutStream {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual bool End();                                       // +0x1c
    virtual cStreamWriter* GetWriter();                       // +0x20
};

// element count of a saved list, written before the elements
static inline void WriteStreamCount(cOutStream* pStream, uint32_t nCount)
{
    cStreamWriter* pWriter = pStream->GetWriter();
    EA::IO::IStream* pPos = pWriter->GetStream();
    EA::IO::WriteUint32(pPos, &nCount, 1, 0);
}

// descriptor tables of the property serialisers
extern void* gCityVarList[2];        // 0x015b5510
extern void* gCivVarList[2];         // 0x015b59c0
extern void* gVehicleVarList[2];     // 0x015b4f28
extern void* gBuildingVarList[2];    // 0x015b5018

class cVarListSerializer {
public:
    cVarListSerializer(void* pObject, void* pVarList, uint32_t nSignature);  // 0x00692f90
    bool Serialize(cOutStream* pStream);                                     // 0x00692900
    bool SerializeAlt(cOutStream* pStream);                                  // 0x00693e10

    int32_t mStorage[0xa14 / 4];      // property table + object/var-list pointers
};

// ---------------------------------------------------------------------------
// nouns / tribes
// ---------------------------------------------------------------------------
class cSpatialObject {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void va();
    virtual const cVector3* GetPosition();                    // +0x2c
    virtual void vb2(); virtual void vb3(); virtual void vb4(); virtual void vb5();
};

class cTribe {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void va(); virtual void vb(); virtual void vc(); virtual void vd(); virtual void ve();
    virtual void vf(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual uint32_t GetPoliticalID();                        // +0x4c
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v1a(); virtual void v1b(); virtual void v1c(); virtual void v1d();
    virtual void v1e(); virtual void v1f(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28();
    virtual uint32_t GetFood();                               // +0xa4

    char mPad04[0x120 - 0x04];                                // +0x004 .. +0x120
    cSpatialObject mSpatial;                                  // +0x120
    int32_t GetAdultPopulation();                             // 0x00c8f370
};

class cStarManager {
public:
    uint32_t GetCurrentPoliticalID();                         // 0x00ba6630
};

class cGameNounManager;

extern cVector3 gDefaultTribePosition;                        // 0x016dad08
cGameNounManager* NounManager();                              // 0x00b3d300
cStarManager* __stdcall StarManager(int nUniverse);           // 0x00b3d2a0

// saved payload of one tribe
struct cTribeData {
    uint32_t mPoliticalID;    // +0x00
    cVector3 mPosition;       // +0x04
    int32_t  mPopulation;     // +0x10
    int32_t  mFood;           // +0x14

    cTribeData();
    cTribeData(int32_t nPopulation, int32_t nFood);
    cTribeData(cTribe* pTribe);
};

// ---------------------------------------------------------------------------
// cities
// ---------------------------------------------------------------------------
class cBuildingThing {
public:
    char mPad00[0x30];
    float mField30;           // +0x30
};

class cCityBlock {
public:
    char mPad00[0x3c];
    cBuildingThing** mpThingsBegin;   // +0x3c
    cBuildingThing** mpThingsEnd;     // +0x40
};

// one building record of a city (0x38 bytes)
class cBuildingData {
public:
    Vec3 mPosition;           // +0x00
    char mPad0c[0x38 - 0x0c];
};

class cCityData {
public:
    cInt3    mKey;                     // +0x00
    char     mPad0c[0x10];             // +0x0c
    float    mValue;                   // +0x1c
    int32_t  mField20;                 // +0x20
    int32_t  mNumBuildings;            // +0x24
    uint8_t  mTurretMask;              // +0x28
    char     mPad29[0x07];             // +0x29
    float    mThreatLevel;             // +0x30
    char     mPad34[0x2c];             // +0x34
    uint16_t mName[14];                // +0x60
    cBuildingData* mpBuildingsBegin;   // +0x7c
    cBuildingData* mpBuildingsEnd;     // +0x80
    char     mPad84[0x15c - 0x84];     // +0x84
    cCityBlock** mpBlocksBegin;        // +0x15c
    cCityBlock** mpBlocksEnd;          // +0x160

    bool TestNameBit(int nIndex, uint32_t nBit) const;     // 0x00ff0330
    void AddValue(float fDelta);                           // 0x00ff0350
    int  GetPercent() const;                               // 0x00ff0400
    void SetKey(const cInt3* pKey);                        // 0x00ff0430
    void Write(cOutStream* pStream);                       // 0x00ff0450
    void WriteRaw(cOutStream* pStream);                    // 0x00ff04d0
    int  GetNumTurrets() const;                            // 0x00ff0760
    cBuildingData* GetBuilding(int nIndex);                // 0x00ff07a0
    void RemoveTurret();                                   // 0x00ff07e0
    int  GetNumBuildings() const;                          // 0x00ff0870
    void SetThreatLevel(float fLevel, cCityData* pCity);   // 0x00ff08b0
    void SetAlert(bool bAlert);                            // 0x00b8d980
    bool IsAlerted();                                      // 0x00b8d9a0
};

// ---------------------------------------------------------------------------
// civilisations
// ---------------------------------------------------------------------------
class cTerrainSphere {
public:
    char mPad00[0x1108];
    int32_t mSphereType;      // +0x1108
};

class cGameNounManager {
public:
    cTerrainSphere* GetCurrentTerrainSphere();    // 0x00f67d90
};

class cNoun {
public:
    char mPad00[0x34];
    cSpatialObject mSpatial;     // +0x34 (its GetPosition is at +0x2c)
    char mPad38[0xb1c - 0x38];   // +0x38
    int32_t mFieldB1c;           // +0x0b1c
    int32_t mFieldB20;           // +0x0b20
};

// noun whose +0x34 word names the resource type of a model key
class cResourceNoun {
public:
    char mPad00[0x34];
    int32_t mResourceType;       // +0x34
};

// position of a noun plus the two trailing ids
class cSpatialSnapshot {
public:
    cVector3 mPosition;          // +0x00
    int32_t  mField0c;           // +0x0c
    int32_t  mField10;           // +0x10

    cSpatialSnapshot* Init(cNoun* pNoun);                     // 0x00ff0db0
    cSpatialSnapshot& Set(const cVector3* pPosition, int32_t nField0c,
                          int32_t nField10);                  // 0x00ff0df0
};

class cVehicleData {
public:
    char mPad00[4];
};

class cCivData {
public:
    cResourceKey* mpModelKeys;      // +0x00
    char mPad04[0x28 - 0x04];       // +0x04
    cVehicleData** mpVehiclesBegin; // +0x28
    cVehicleData** mpVehiclesEnd;   // +0x2c
    char mPad30[0x3c - 0x30];       // +0x30
    cCityData** mpCitiesBegin;      // +0x3c
    cCityData** mpCitiesEnd;        // +0x40

    void CopyTerrainKeys();                     // 0x00ff0940
    cResourceKey* GetResourceKey(cResourceNoun* pNoun);  // 0x00ff0cd0
    void Write(cOutStream* pStream);            // 0x00ff0e20

    // copy the three terrain keys named by a terrain-sphere rule into the shared slots
    void CopyThreeKeys(uint32_t nKeyA, uint32_t nKeyB, uint32_t nKeyC)
    {
        uint32_t nSlotA = FindModelKeyIndex(nKeyA);
        uint32_t nSlotB = FindModelKeyIndex(nKeyB);
        uint32_t nSlotC = FindModelKeyIndex(nKeyC);
        uint32_t nSlotD = FindModelKeyIndex(0xbc1041e6);
        mpModelKeys[nSlotD] = mpModelKeys[nSlotA];
        uint32_t nSlotE = FindModelKeyIndex(0xc15695da);
        mpModelKeys[nSlotE] = mpModelKeys[nSlotB];
        uint32_t nSlotF = FindModelKeyIndex(0x2090a11b);
        mpModelKeys[nSlotF] = mpModelKeys[nSlotC];
    }
};

// the building sequence the writer walks (eastl::vector of building records)
class cBuildingList {
public:
    const cBuildingData* mpBegin;    // +0x00
    const cBuildingData* mpEnd;      // +0x04
};

// serialise a sequence of building records
bool WriteSTLSequenceT(cOutStream* pStream, const cBuildingList* pBuildings);  // 0x00ff0f30

// ---------------------------------------------------------------------------
// citizen spawning of the city growth routine
// ---------------------------------------------------------------------------
class cRefTarget {
public:
    virtual void AddRef();                 // +0x00
    virtual void Release();                // +0x04
};

// eastl vector of ref-counted handles (the allocator front of the real vector is not touched)
class cRefVector {
public:
    void PushBack(cRefTarget* pTarget);    // 0x00aea5d0

    cRefTarget** mpBegin;                  // +0x00
    cRefTarget** mpEnd;                    // +0x04
    cRefTarget** mpCapacity;               // +0x08
};

class cBehavior;
class cCitizenMind;

class cNearNoun {
public:
    const Vec3* GetPosition();             // 0x00c6acc0
};

class cBehaviorManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void va(); virtual void vb(); virtual void vc(); virtual void vd();
    virtual void RegisterBehavior(cBehavior* pBehavior);    // +0x38
};

class cCitizen {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual cBehavior* GetBehavior(uint32_t nBehaviorId);   // +0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void va(); virtual void vb(); virtual void vc(); virtual void vd();
    virtual void ve(); virtual void vf(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14();
    virtual void Activate();                                // +0x54

    char mPad58[0xb62 - 0x58];             // +0x058
    uint8_t mFieldB62;                     // +0x0b62
};

class cCitizenMind {
public:
    char mPad00[0x71];
    uint8_t mField71;                      // +0x71
    char mPad72[3];
    uint8_t mField75;                      // +0x75
};

extern Vec3 gCityCentrePosition;                              // 0x016daccc
void* PlanetModel();                                          // 0x00b3d350
void* GetSpawnTuning();                                       // 0x00b3d480
uint32_t RandomUint32Uniform(uint32_t nRange);                // 0x00a68fb0
void GatherSpawnCandidates(cRefVector* pOut, cGameNounManager* pNouns, void* pTuning);
void ShuffleSpawnCandidates(cRefVector* pCandidates);         // 0x00fefec0
cCitizen* CreateCitizen(const Vec3* pPosition, uint32_t nOwner, bool bAdult, void* pParent,
                        int32_t nA, int32_t nB);              // 0x00c099e0
void InitCitizenTool(cCitizen* pCitizen, uint32_t nToolId);    // 0x00c03170
void RegisterCitizen(cCitizen* pCitizen);                      // 0x00acd2d0
void BindCitizenHome(cCitizen* pCitizen, uint32_t nBehaviorId);  // 0x00c1d430
cBehaviorManager* BehaviorManager();                           // 0x00b3d260
void operator delete[](void* pBlock);                          // 0x00f47380

// a noun standing exactly on the city centre is never picked to become a citizen
static inline bool IsParkedAtCityCentre(cNearNoun* pNoun)
{
    const Vec3* pPosition = pNoun->GetPosition();
    return pPosition->x == gCityCentrePosition.x && pPosition->y == gCityCentrePosition.y
        && pPosition->z == gCityCentrePosition.z;
}

// @ 0x00feff80  SP::sSpawnTribesmen
// Picks up to nCount tribesmen out of the planet's noun list -- drawing between nMinSlot and nMaxSlot
// of them per pass -- and turns every pick into a citizen of the city (nOwner, nToolId, nBehaviorId).
void sSpawnTribesmen(uint32_t nOwner, int nCount, int nMinSlot, int nMaxSlot,
                     uint32_t nToolId, uint32_t nBehaviorId, cRefVector* pTargets)
{
    PlanetModel();
    cGameNounManager* pNouns = NounManager();
    void* pTuning = GetSpawnTuning();
    int32_t nSpawned = 0;

    cRefVector candidates;
    GatherSpawnCandidates(&candidates, pNouns, pTuning);
    ShuffleSpawnCandidates(&candidates);

    while (candidates.mpBegin != candidates.mpEnd && nSpawned < nCount) {
        int32_t nWant = (int32_t)RandomUint32Uniform((uint32_t)((nMaxSlot - nMinSlot) + 1)) + nMinSlot;
        int32_t nLeft = nCount - nSpawned;
        int32_t nPicks = nWant < nLeft ? nWant : nLeft;
        cRefTarget* pPick = 0;

        // drop candidates off the back of the list until the drawn one may stay
        while (candidates.mpBegin != candidates.mpEnd) {
            if (pPick != 0 && !IsParkedAtCityCentre((cNearNoun*)pPick))
                break;
            cRefTarget* pTail = *--candidates.mpEnd;
            int32_t nSlots = (int32_t)(candidates.mpEnd - candidates.mpBegin);
            int32_t nSlot = (int32_t)RandomUint32Uniform((uint32_t)nSlots);
            cRefTarget* pOld = candidates.mpBegin[nSlot];
            pPick = pTail;
            if (pTail != pOld) {
                if (pTail != 0)
                    pTail->AddRef();
                candidates.mpBegin[nSlot] = pTail;
                if (pOld != 0)
                    pOld->Release();
            }
            cRefTarget* pDropped = *candidates.mpEnd;
            if (pDropped != 0)
                pDropped->Release();
        }
        if (pPick == 0) {
            GatherSpawnCandidates(&candidates, pNouns, pTuning);
            ShuffleSpawnCandidates(&candidates);
            continue;
        }

        // hand the pick over to the target list
        pPick->AddRef();
        pTargets->PushBack(pPick);
        pPick->Release();

        for (int32_t i = 0; i < nPicks; ++i) {
            Vec3 position = *((cNearNoun*)pPick)->GetPosition();
            bool bAdult = RandomUint32Uniform(10) >= 2;
            cCitizen* pCitizen = CreateCitizen(&position, nOwner, bAdult, pPick, 0, 1);
            if (pCitizen != 0) {
                InitCitizenTool(pCitizen, nToolId);
                RegisterCitizen(pCitizen);
                pCitizen->mFieldB62 = 1;
                BindCitizenHome(pCitizen, nBehaviorId);
                ++nSpawned;
                BehaviorManager()->RegisterBehavior(pCitizen->GetBehavior(0x11c0ba3));
                cCitizenMind* pMind = (cCitizenMind*)pCitizen->GetBehavior(0x116dd1b);
                if (pMind != 0) {
                    pMind->mField71 = 0;
                    pMind->mField75 = 1;
                }
                pCitizen->Activate();
            }
        }
    }

    for (cRefTarget** ppRef = candidates.mpBegin; ppRef != candidates.mpEnd; ++ppRef) {
        if (*ppRef != 0)
            (*ppRef)->Release();
    }
    if (candidates.mpBegin != 0)
        operator delete[](candidates.mpBegin);
}

// ---------------------------------------------------------------------------
// model key tables
// ---------------------------------------------------------------------------

// @ 0x00ff03d0  SP::sGetIndexFromModelType
bool sGetIndexFromModelType(uint32_t modelType, uint32_t* pIndex)
{
    for (int i = 0; i < 16; ++i) {
        if (modelType == (uint32_t)sStoredModelKeys[i]) {
            *pIndex = (uint32_t)i;
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// cCityData
// ---------------------------------------------------------------------------

// @ 0x00ff0330  SP::cCityData::TestNameBit
bool cCityData::TestNameBit(int nIndex, uint32_t nBit) const
{
    return (mName[nIndex] & (1u << nBit)) != 0;
}

// @ 0x00ff0350  SP::cCityData::AddValue
void cCityData::AddValue(float fDelta)
{
    float fValue = fDelta + mValue;
    mValue = fValue;
    if (fValue < 0.0f)
        mValue = 0.0f;
}

// @ 0x00ff0400  SP::cCityData::GetPercent
int cCityData::GetPercent() const
{
    int nTotal = mField20 + mNumBuildings;
    if (nTotal != 0)
        return (mField20 * 1000) / nTotal;
    return 1000;
}

// @ 0x00ff0430  SP::cCityData::SetKey
void cCityData::SetKey(const cInt3* pKey)
{
    mKey.x = pKey->x;
    mKey.y = pKey->y;
    mKey.z = pKey->z;
}

// @ 0x00ff0450  SP::cCityData::Write
void cCityData::Write(cOutStream* pStream)
{
    for (int i = 0; i < 14; ++i) {
        cStreamWriter* pWriter = pStream->GetWriter();
        uint32_t nWord = mName[i];
        EA::IO::IStream* pPos = pWriter->GetStream();
        EA::IO::WriteUint16(pPos, &nWord, 1, 0);
    }
    cVarListSerializer serializer(this, gCityVarList, 0x1a80d26);
    serializer.Serialize(pStream);
}

// @ 0x00ff04d0  SP::cCityData::WriteRaw
void cCityData::WriteRaw(cOutStream* pStream)
{
    for (int i = 0; i < 14; ++i) {
        cStreamWriter* pWriter = pStream->GetWriter();
        EA::IO::IStream* pPos = pWriter->GetStream();
        EA::IO::WriteUint16Raw(pPos, &mName[i], 1, 0);
    }
    cVarListSerializer serializer(this, gCityVarList, 0x1a80d26);
    serializer.SerializeAlt(pStream);
}

// @ 0x00ff05d0  SP::sWriteUint16
bool sWriteUint16(cOutStream* pStream, const uint16_t* pValue)
{
    cStreamWriter* pWriter = pStream->GetWriter();
    uint32_t nWord = *pValue;
    EA::IO::IStream* pPos = pWriter->GetStream();
    EA::IO::WriteUint16(pPos, &nWord, 1, 0);
    return true;
}

// @ 0x00ff0760  SP::cCityData::GetNumTurrets
int cCityData::GetNumTurrets() const
{
    return CountBits(mTurretMask);
}

// @ 0x00ff07a0  SP::cCityData::GetBuilding
cBuildingData* cCityData::GetBuilding(int nIndex)
{
    if (nIndex < (int32_t)(mpBuildingsEnd - mpBuildingsBegin))
        return &mpBuildingsBegin[nIndex];
    return 0;
}

// @ 0x00ff07e0  SP::cCityData::RemoveTurret
void cCityData::RemoveTurret()
{
    int nBefore = CountBits(mTurretMask);
    mTurretMask &= mTurretMask - 1;
    int nAfter = CountBits(mTurretMask);
    if (nBefore - nAfter > 0)
        --mNumBuildings;
}

// @ 0x00ff0870  SP::cCityData::GetNumBuildings
int cCityData::GetNumBuildings() const
{
    return mNumBuildings - CountBits(mTurretMask);
}

// @ 0x00ff08b0  SP::cCityData::SetThreatLevel
void cCityData::SetThreatLevel(float fLevel, cCityData* pCity)
{
    mThreatLevel = fLevel;
    if (pCity == 0)
        return;
    if (fLevel <= 20.0f) {
        pCity->SetAlert(true);
        return;
    }
    if (!pCity->IsAlerted())
        return;
    uint32_t nBlocks = (uint32_t)(pCity->mpBlocksEnd - pCity->mpBlocksBegin);
    if (nBlocks > 0) {
        cCityBlock* pBlock = *pCity->mpBlocksBegin;
        cBuildingThing** ppBegin = pBlock->mpThingsBegin;
        int32_t nThings = (int32_t)(pBlock->mpThingsEnd - ppBegin);
        cBuildingThing** ppThing = ppBegin;
        for (int32_t i = 0; i < nThings; ++i) {
            if ((*ppThing)->mField30 <= 20.0f)
                return;
            ++ppThing;
        }
    }
    pCity->SetAlert(false);
}

// ---------------------------------------------------------------------------
// cTribeData
// ---------------------------------------------------------------------------

// @ 0x00ff0610  SP::cTribeData::cTribeData
cTribeData::cTribeData(cTribe* pTribe)
{
    mPoliticalID = 0xffffffff;
    CopyPositionFloats(&mPosition, &gDefaultTribePosition);
    mPopulation = 0;
    mFood = 0;
    if (pTribe != 0) {
        mPoliticalID = pTribe->GetPoliticalID();
        CopyPositionWords(&mPosition, pTribe->mSpatial.GetPosition());
        mPopulation = pTribe->GetAdultPopulation();
        mFood = pTribe->GetFood();
    }
}

// @ 0x00ff06a0  SP::cTribeData::cTribeData
cTribeData::cTribeData(int32_t nPopulation, int32_t nFood)
{
    CopyPositionFloats(&mPosition, &gDefaultTribePosition);
    mPopulation = nPopulation;
    mFood = nFood;
    if (NounManager() != 0)
        mPoliticalID = StarManager(0)->GetCurrentPoliticalID();
}

// @ 0x00ff0700  SP::cTribeData::cTribeData
cTribeData::cTribeData()
{
    CopyPositionFloats(&mPosition, &gDefaultTribePosition);
    mPopulation = 0;
    mFood = 0;
    if (NounManager() != 0)
        mPoliticalID = StarManager(0)->GetCurrentPoliticalID();
}

// ---------------------------------------------------------------------------
// cCivData
// ---------------------------------------------------------------------------

// @ 0x00ff0940  SP::cCivData::CopyTerrainKeys
void cCivData::CopyTerrainKeys()
{
    int32_t nSphereType = NounManager()->GetCurrentTerrainSphere()->mSphereType;
    if (nSphereType == 0x0a35d0f5)
        CopyThreeKeys(0x7d433fad, 0x8f963dcb, 0x441cd3e6);
    else if (nSphereType == 0x3360727f)
        CopyThreeKeys(0xf670aa43, 0x2a5147a9, 0x1a4e0708);
    else if (nSphereType == 0x6aeb96a1)
        CopyThreeKeys(0x9ad7d4aa, 0x1f2a25b6, 0x449c040f);
}

// @ 0x00ff0cd0  SP::cCivData::GetResourceKey
cResourceKey* cCivData::GetResourceKey(cResourceNoun* pNoun)
{
    uint32_t nIndex = 0;
    switch (pNoun->mResourceType) {
    case 0x018ea1eb:
        sGetIndexFromModelType(0x99e92f05, &nIndex);
        break;
    case 0x018ea2cc:
        sGetIndexFromModelType(0x47c10953, &nIndex);
        break;
    case 0x018eb106:
        nIndex = FindModelKeyIndex(0x4e3f7777);
        break;
    case 0x01a56aba:
        nIndex = FindModelKeyIndex(0x72c49181);
        break;
    }
    return mpModelKeys + nIndex;
}

// @ 0x00ff0e20  SP::cCivData::Write
void cCivData::Write(cOutStream* pStream)
{
    cVarListSerializer serializer(this, gCivVarList, 0x1a80d26);

    int32_t nCities = (int32_t)(mpCitiesEnd - mpCitiesBegin);
    WriteStreamCount(pStream, (uint32_t)nCities);
    for (int32_t i = 0; i < nCities; ++i)
        mpCitiesBegin[i]->Write(pStream);

    int32_t nVehicles = (int32_t)(mpVehiclesEnd - mpVehiclesBegin);
    WriteStreamCount(pStream, (uint32_t)nVehicles);
    for (int32_t i = 0; i < nVehicles; ++i) {
        cVarListSerializer vehicleSerializer(mpVehiclesBegin[i], gVehicleVarList, 0x1a80d26);
        vehicleSerializer.Serialize(pStream);
    }
    serializer.Serialize(pStream);
}

// ---------------------------------------------------------------------------
// cSpatialSnapshot
// ---------------------------------------------------------------------------

// @ 0x00ff0db0  SP::cSpatialSnapshot::Init
cSpatialSnapshot* cSpatialSnapshot::Init(cNoun* pNoun)
{
    if (pNoun != 0) {
        CopyPositionWords(&mPosition, pNoun->mSpatial.GetPosition());
        mField0c = pNoun->mFieldB1c;
        mField10 = pNoun->mFieldB20;
    }
    return this;
}

// @ 0x00ff0df0  SP::cSpatialSnapshot::Set
cSpatialSnapshot& cSpatialSnapshot::Set(const cVector3* pPosition, int32_t nField0c,
                                        int32_t nField10)
{
    CopyPositionFloats(&mPosition, pPosition);
    mField0c = nField0c;
    mField10 = nField10;
    return *this;
}

// ---------------------------------------------------------------------------
// building sequence
// ---------------------------------------------------------------------------

// @ 0x00ff0f30  SP::WriteSTLSequenceT
bool WriteSTLSequenceT(cOutStream* pStream, const cBuildingList* pBuildings)
{
    WriteStreamCount(pStream, (uint32_t)(pBuildings->mpEnd - pBuildings->mpBegin));
    const cBuildingData* pEnd = pBuildings->mpEnd;
    for (const cBuildingData* pData = pBuildings->mpBegin; pData != pEnd; ++pData) {
        cVarListSerializer serializer((void*)pData, gBuildingVarList, 0x1a80d26);
        serializer.Serialize(pStream);
    }
    return pStream->End();
}

}  // namespace SP
