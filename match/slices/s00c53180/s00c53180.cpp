// Slice s00c53180: SP::cSPMissionFetch logic (mission update tick, fetch-reward
// fulfilment, UI short description / fetch item names, and the sampler-plate
// vector helpers used to record which species were collected).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// Shipping layout: cSPMission base is 0x1f0 bytes (mRewardMoney +0x78, mUIText
// +0x14c, mpParentMission +0x17c, mMissionPropList +0x180, mGiveOnAcceptMoney
// +0x184); cSPMissionFetch fields start at +0x1f0 (state +0x1f0, type +0x1f4,
// artifact key +0x1f8, position +0x204, plant key +0x210, animal key +0x21c,
// commodity key +0x228, sampler-plate vector +0x234, drop-off flag +0x248).
#include "types.h"

#define VSLOT(n) virtual void _v##n();

// ---------------------------------------------------------------------------
// small value types
// ---------------------------------------------------------------------------
class Key {
public:
    uint32_t mInstance;   // +0x00
    uint32_t mType;       // +0x04
    uint32_t mGroup;      // +0x08
};

struct cSPVector3 {
    float x, y, z;
};

struct cFetchSample {
    bool mIsAnimal;       // +0x00
    Key mSpeciesKey;      // +0x04
};

struct Quad16;

// eastl::copy_impl<...>::do_copy (0x00705250)
Quad16* copy(const Quad16* first, const Quad16* last, Quad16* dest);

// ---------------------------------------------------------------------------
// eastl::basic_string<wchar_t,eastl::allocator> (12 bytes)
// ---------------------------------------------------------------------------
class WString {
public:
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    WString();                                         // 0x00933910
    WString(const wchar_t* pStr);                      // 0x0041df50
    ~WString();                                        // 0x00933960
    WString& operator=(const WString& rhs);            // 0x0057cb60
    void assign(const wchar_t* first, const wchar_t* last); // 0x00423650
};

// ---------------------------------------------------------------------------
// SP::cString (12 bytes)
// ---------------------------------------------------------------------------
class cString {
public:
    uint32_t mnTableId;    // +0x00
    uint32_t mnKey;        // +0x04
    const wchar_t* mpText; // +0x08
    cString();                                  // 0x006b5060
    ~cString();                                 // 0x006b5240
    const wchar_t* GetText();                   // 0x006b55c0
};

// ---------------------------------------------------------------------------
// sampler-plate vector (eastl::vector<cFetchSample, sp_vector_allocator>)
// ---------------------------------------------------------------------------
class cFetchSampleVector {
public:
    cFetchSample* mpBegin;     // +0x00
    cFetchSample* mpEnd;       // +0x04
    cFetchSample* mpCapacity;  // +0x08
    cFetchSample* DoInsertValue(cFetchSample* pos, const cFetchSample& value); // 0x00c19d10
    void Reserve(uint32_t nCount);                                             // 0x00c53690
    void push_back(const cFetchSample& value);                                 // 0x00c53a50
    void clear();                                                              // 0x00c53a90
};

// ---------------------------------------------------------------------------
// property / inventory objects
// ---------------------------------------------------------------------------
class cItemList {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11)
    Key* GetKeys();                // 0x00446ff0
    uint32_t mnPad04;              // +0x04
    int32_t mnCount;               // +0x08
    uint32_t mnPad0c;              // +0x0c
    uint8_t mnFlags;               // +0x10
    uint8_t mnPad11;               // +0x11
    uint16_t mnCount2;             // +0x12
};

class cPropertyList {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9)
    virtual cItemList* FindItems(uint32_t nId);      // +0x28
    virtual void _v2c();
};

class cPropertyValue {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
    uint32_t mnPad04;              // +0x04
    int32_t mnValue;               // +0x08
};

class cPropertyManager {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10)
    virtual void GetProperty(uint32_t nKey, uint32_t nId, cPropertyValue** ppValue); // +0x2c
};

class cInventoryItem {
public:
    VSLOT(0) VSLOT(1)
    virtual void Release();                          // +0x08
    VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8)
};

class cInventory {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14)
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21)
    VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    VSLOT(29) VSLOT(30)
    virtual void AddItem(cInventoryItem* pItem, int32_t nCount, int32_t nFlags); // +0x80
};

class cCommManager {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9)
    virtual bool IsActive();                                   // +0x28
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17)
    VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24)
    VSLOT(25) VSLOT(26)
    virtual void RemoveMatching(int32_t a, int32_t b, void* pMission); // +0x6c
};

class cSpeciesProfile {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual Key* GetSpeciesKey();                            // +0x18
    VSLOT(7) VSLOT(8)
    virtual cInventoryItem* MakeInventoryItem(void* pName);  // +0x24
    virtual const wchar_t* GetName();                        // +0x28
    uint8_t mnPad04[0x500];       // +0x004
    Key mSpeciesKey;              // +0x504
    uint8_t mnPad510[0x0c];       // +0x510
    const wchar_t* mpDisplayName; // +0x51c
};

class cSpeciesManager {
public:
    cSpeciesProfile* GetSpeciesFromID(const Key* pKey);      // 0x00b90410
};

class cPlanetEco {
public:
    Key* GetCommodityKey();    // 0x00b8dad0
    Key* GetAnimalKey();       // 0x00b8e090
};

class cPlanet {
public:
    uint8_t mnPad00[0xbc];     // +0x000
    Key* mpPlantKeysBegin;     // +0x0bc
    Key* mpPlantKeysEnd;       // +0x0c0
    uint8_t mnPadC4[0x0c];     // +0x0c4
    Key* mpAnimalKeysBegin;    // +0x0d0
    Key* mpAnimalKeysEnd;      // +0x0d4
    uint8_t mnPadD8[0x64];     // +0x0d8
    cPlanetEco* mpEco;         // +0x13c
    cSpeciesProfile* GetRandomAnimalSpecies();   // 0x00c70c10
    cSpeciesProfile* GetRandomPlantSpecies();    // 0x00c70c90
};

class cSpaceGame {
public:
    cInventory* GetPlayerInventory();            // 0x00a1ad60
};

// ---------------------------------------------------------------------------
// SP::cSPMission base (shipping layout is 0x1f0 bytes)
// ---------------------------------------------------------------------------
class cSPMission {
public:
    uint8_t mnPad00[0x78];           // +0x000
    float mRewardMoney;              // +0x078
    uint8_t mnPad7c[0xd0];           // +0x07c
    WString mUIText;                 // +0x14c
    uint8_t mnPad158[0x24];          // +0x158
    cSPMission* mpParentMission;     // +0x17c
    cPropertyList* mMissionPropList; // +0x180
    int32_t mGiveOnAcceptMoney;      // +0x184
    uint8_t mnPad188[0x68];          // +0x188
    int32_t Update(int32_t nDelta);                        // 0x00c478b0
    void TriggerUIUpdate();                                // 0x00c47d80
    void ValidateProgressEvent();                          // 0x00c44f20
    void Fulfill();                                        // 0x00c2e4e0
    cPlanet* GetTargetPlanet();                            // 0x00970b30
    void GetText(uint32_t nTextId, WString* pOut);         // 0x00c487d0
};

class cSPMissionFlight101 : public cSPMission {
public:
    void ValidateHerds();                        // 0x00c55ca0
};

// ---------------------------------------------------------------------------
// SP::cSPMissionFetch
// ---------------------------------------------------------------------------
class cSPMissionFetch : public cSPMission {
public:
    int32_t mFetchMissionState;          // +0x1f0
    uint32_t mTypeOfFetch;               // +0x1f4
    Key mFetchArtifactCargoItemID;       // +0x1f8
    cSPVector3 mFetchArtifactPos;        // +0x204
    Key mFetchPlantSpeciesKey;           // +0x210
    Key mFetchAnimalSpeciesKey;          // +0x21c
    Key mFetchCommodityKey;              // +0x228
    cFetchSampleVector mSamplerPlate;    // +0x234
    uint8_t mnPad240[0x08];              // +0x240
    bool mDropOffRequired;               // +0x248
    uint8_t mnPad249[0x03];              // +0x249
    float mDropOffDistance;              // +0x24c
    int32_t Update(int32_t nDelta);                     // 0x00c53180
    void Fulfill();                                     // 0x00c532d0
    void GetUIShortDescription(WString* pOut);          // 0x00c53720
    void GetFetchItemName(WString* pOut);               // 0x00c53800
    bool PickFetchItem();                               // 0x00c53bc0
    bool IsSatisfied();                                 // 0x00c52a70
    void OnComplete();                                  // 0x00c52ea0
    void SetFetchState(int32_t nState);                 // 0x00c5ed90
    void Expire();                                      // 0x00c471c0
};

// ---------------------------------------------------------------------------
// serializer used by ReadSTLSequenceT
// ---------------------------------------------------------------------------
class cDataSerializationInfo {
public:
    uint8_t mnData[0x14];
};

class cVarListSerializer {
public:
    cDataSerializationInfo mDataSerializationInfos[128]; // +0x0000
    int32_t mSerializableVarCount;                       // +0x0a00
    int32_t mSerializedVarCount;                         // +0x0a04
    uint32_t mSignature;                                 // +0x0a08
    void* mpObject;                                      // +0x0a0c
    void* mpSerializerList;                              // +0x0a10
    cVarListSerializer(void* pObject, const char* pName, uint32_t nSignature); // 0x00692f90
    void Serialize(void* pSerializer);                                         // 0x00693e10
};

class cSerializedObject {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void* GetStream();                 // +0x18
};

class cSerializer {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6)
    virtual void End();                        // +0x1c
    virtual cSerializedObject* GetObject();    // +0x20
};

class cUniverseContext {
public:
    bool IsArchived();     // 0x00bba900
    bool IsPlanet();       // 0x00bb9d40
};

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void EA_IO_ReadInt32(void* pStream, uint32_t* pValue, int32_t nCount, int32_t nFlags); // 0x0093a780
const Key* EmptyKey();                                     // 0x016907d4 (three dwords)
cPropertyManager* PropertyManager();                       // 0x0067de30
void GetPropertyAsText(cPropertyValue* pValue, uint32_t nId, cString* pOut); // 0x006a1360
cSpeciesManager* PlantSpeciesManager(const Key* pKey);     // 0x00b3d420
cSpeciesManager* AnimalSpeciesManager(const Key* pKey);    // 0x00b3d450
cSpeciesProfile* GetSpeciesProfile(const Key* pKey);       // 0x004df550
cInventoryItem* MakeInventoryItemFromKey(const Key* pKey); // 0x00ac0cb0
cInventoryItem* MakeArtifactFromKey(Key* pKey);            // 0x00c878d0
void AddCommodityToInventory(const Key* pKey, int32_t nCount); // 0x00b3d3d0
cSpaceGame* SpaceGameGet();                                // 0x01002bd0
cCommManager* CommManager();                               // 0x00b3d4a0
void* GetPlayerProperty(void* pInventory);                 // 0x00ff3f00
bool CompareDeclareParam(void* a, void* b);                // 0x004eb930
bool PlayerHasDropCargo(void* pObject);                    // 0x0104bd50
void* GetSetting9(const Key* pKey);                        // 0x00401090
void* MakeNameString(void* p);                             // 0x00c463d0
int32_t GetUniverseContext();                              // 0x01021080
cUniverseContext* GetArchivedContext();                    // 0x01021240
cUniverseContext* GetActivePlanetRecord();                 // 0x010212a0
uint32_t RandomUint32Uniform(uint32_t nRange);             // 0x00a68fb0
void* GetPlanetCapability(cPlanet* pPlanet);               // 0x008414c0
cSPMissionFlight101* GetSubMission(cSPMission* pParent, uint32_t nId); // 0x0042227d

// ---------------------------------------------------------------------------
// vector helpers
// ---------------------------------------------------------------------------
// @ 0x00c53a50
void cFetchSampleVector::push_back(const cFetchSample& value)
{
    if (mpEnd < mpCapacity) {
        cFetchSample* pEnd = mpEnd;
        mpEnd = pEnd + 1;
        if (pEnd != 0)
            *pEnd = value;
    } else {
        DoInsertValue(mpEnd, value);
    }
}

// @ 0x00c53a90
void cFetchSampleVector::clear()
{
    cFetchSample* pEnd = mpEnd;
    cFetchSample* pBegin = mpBegin;
    copy((const Quad16*)pEnd, (const Quad16*)pEnd, (Quad16*)pBegin);
    mpEnd -= pEnd - pBegin;
}

// ---------------------------------------------------------------------------
// SP::ReadSTLSequenceT<eastl::vector<SP::cFetchSample,...>>
// @ 0x00c53ac0
void ReadFetchSamples(cSerializer* pSerializer, cFetchSampleVector& samples)
{
    cFetchSample sample;

    samples.clear();

    uint32_t nCount = 0;
    cSerializedObject* pObject = pSerializer->GetObject();
    void* pStream = pObject->GetStream();
    EA_IO_ReadInt32(pStream, &nCount, 1, 0);
    samples.Reserve(nCount);

    for (uint32_t i = 0; i < nCount; ++i) {
        sample.mSpeciesKey.mInstance = 0;
        sample.mSpeciesKey.mType = 0;
        sample.mSpeciesKey.mGroup = 0;
        cVarListSerializer serializer(&sample, "FetchSample", 0x01a80d26);
        serializer.Serialize(pSerializer);
        samples.push_back(sample);
    }

    pSerializer->End();
}

// ---------------------------------------------------------------------------
// SP::cSPMissionFetch::Update
// @ 0x00c53180
int32_t cSPMissionFetch::Update(int32_t nDelta)
{
    int32_t nResult = cSPMission::Update(nDelta);
    if (nResult != 3)
        return nResult;

    switch (mFetchMissionState) {
    case 0:
        if (IsSatisfied() && !mDropOffRequired) {
            if (!CommManager()->IsActive())
                OnComplete();
        }
        break;
    case 1:
        if (!IsSatisfied()) {
            cInventory* pInventory = SpaceGameGet()->GetPlayerInventory();
            void* pObject = GetPlayerProperty(pInventory);
            if (pObject == 0
                || !(CompareDeclareParam(*(void**)(*(uint8_t**)pObject + 0x18), 0)
                     && PlayerHasDropCargo(pObject))) {
                if (mFetchMissionState != 0) {
                    mFetchMissionState = 0;
                    TriggerUIUpdate();
                }
            }
        }
        break;
    case 2:
        if (!mDropOffRequired && !IsSatisfied())
            SetFetchState(0);
        break;
    default:
        break;
    }

    {
        cSPMission* pParent = mpParentMission != 0 ? mpParentMission : this;
        CommManager()->RemoveMatching(-1, -1, pParent);
        ValidateProgressEvent();
        Expire();
    }

    if (*(const uint32_t*)&mRewardMoney == 0xbb448992 && mpParentMission != 0) {
        cSPMissionFlight101* pFlight = GetSubMission(mpParentMission, 0x0422227d);
        if (pFlight != 0)
            pFlight->ValidateHerds();
    }
    return 3;
}

// ---------------------------------------------------------------------------
// SP::cSPMissionFetch::Fulfill
// @ 0x00c532d0
void cSPMissionFetch::Fulfill()
{
    cSPMission::Fulfill();

    switch (mTypeOfFetch) {
    case 0x6d5c48c: {
        cSpeciesManager* pManager = PlantSpeciesManager(&mFetchPlantSpeciesKey);
        cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&mFetchPlantSpeciesKey);
        if (pProfile == 0)
            break;
        cInventoryItem* pItem = pProfile->MakeInventoryItem(MakeNameString(0));
        SpaceGameGet()->GetPlayerInventory()->AddItem(pItem, 0, 1);
        if (pItem != 0)
            pItem->Release();
        break;
    }
    case 0xbfb44ccc:
        AddCommodityToInventory(&mFetchCommodityKey, 1);
        break;
    case 0xfb3b1635:
    case 0x2dc69129:
    case 0x3e994b2b:
    case 0x69412983: {
        cSpeciesManager* pManager = AnimalSpeciesManager(&mFetchAnimalSpeciesKey);
        cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&mFetchAnimalSpeciesKey);
        if (pProfile != 0) {
            cInventoryItem* pItem = pProfile->MakeInventoryItem(MakeNameString(0));
            SpaceGameGet()->GetPlayerInventory()->AddItem(pItem, 0, 1);
            if (pItem != 0)
                pItem->Release();
        }
        if (mFetchPlantSpeciesKey.mInstance != EmptyKey()->mInstance
            || mFetchPlantSpeciesKey.mType != EmptyKey()->mType
            || mFetchPlantSpeciesKey.mGroup != EmptyKey()->mGroup) {
            cSpeciesManager* pPlantManager = PlantSpeciesManager(&mFetchPlantSpeciesKey);
            cSpeciesProfile* pPlant = pPlantManager->GetSpeciesFromID(&mFetchPlantSpeciesKey);
            if (pPlant != 0) {
                cInventoryItem* pItem = pPlant->MakeInventoryItem(MakeNameString(0));
                SpaceGameGet()->GetPlayerInventory()->AddItem(pItem, 0, 1);
                if (pItem != 0)
                    pItem->Release();
            }
        }
        break;
    }
    case 0x19ec2c8b: {
        Key key = mFetchArtifactCargoItemID;
        cInventoryItem* pItem = MakeArtifactFromKey(&key);
        if (pItem != 0) {
            SpaceGameGet()->GetPlayerInventory()->AddItem(pItem, 0, 1);
            pItem->Release();
        }
        break;
    }
    case 0x23da98ff: {
        uint32_t nCount = (uint32_t)(mSamplerPlate.mpEnd - mSamplerPlate.mpBegin);
        for (uint32_t i = 0; i < nCount; ++i) {
            cFetchSample* pSample = &mSamplerPlate.mpBegin[i];
            cInventoryItem* pItem = 0;
            if (pSample->mIsAnimal) {
                pItem = MakeInventoryItemFromKey(&pSample->mSpeciesKey);
            } else {
                cSpeciesManager* pManager = PlantSpeciesManager(&pSample->mSpeciesKey);
                cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&pSample->mSpeciesKey);
                if (pProfile != 0)
                    pItem = pProfile->MakeInventoryItem(MakeNameString(0));
            }
            if (pItem != 0) {
                SpaceGameGet()->GetPlayerInventory()->AddItem(pItem, 0, 1);
                pItem->Release();
            }
        }
        break;
    }
    case 0x7ecbe6f5: {
        Key key;
        key.mInstance = 0x1344c7ff;
        key.mType = 0;
        key.mGroup = 0;
        AddCommodityToInventory(&key, 1);
        break;
    }
    default:
        break;
    }

    OnComplete();
}

// ---------------------------------------------------------------------------
// SP::cSPMissionFetch::GetUIShortDescription
// @ 0x00c53720
void cSPMissionFetch::GetUIShortDescription(WString* pOut)
{
    if (mUIText.mpBegin == mUIText.mpEnd) {
        uint32_t nTextId;
        cUniverseContext* pContext;
        switch (mFetchMissionState) {
        case 0:
            if (*(const uint32_t*)&mRewardMoney == 0x809ab04a) {
                if (GetUniverseContext() == 1
                    && (pContext = GetArchivedContext()) != 0
                    && pContext->IsArchived()) {
                    nTextId = 0x639f0b00;
                } else if (GetUniverseContext() == 0
                           && (pContext = GetActivePlanetRecord()) != 0
                           && pContext->IsPlanet()) {
                    nTextId = 0x791cfa76;
                } else {
                    nTextId = 0xaad9c0b3;
                }
            } else {
                nTextId = 0xaad9c0b3;
            }
            GetText(nTextId, pOut);
            break;
        case 2:
            GetText(0x4e1f8fa8, pOut);
            break;
        case 3:
            GetText(0x0b4dfecf, pOut);
            break;
        default:
            break;
        }

        if (pOut != &mUIText)
            mUIText.assign(pOut->mpBegin, pOut->mpEnd);
    } else {
        if (pOut != &mUIText)
            pOut->assign(mUIText.mpBegin, mUIText.mpEnd);
    }
}

// ---------------------------------------------------------------------------
// SP::cSPMissionFetch::GetFetchItemName
// @ 0x00c53800
void cSPMissionFetch::GetFetchItemName(WString* pOut)
{
    switch (mTypeOfFetch) {
    case 0xbfb44ccc: {
        cString text;
        cPropertyValue* pValue = 0;
        PropertyManager()->GetProperty(mFetchCommodityKey.mInstance, 0x34d97fa, &pValue);
        GetPropertyAsText(pValue, 0x3068d95d, &text);
        WString temp(text.GetText());
        *pOut = temp;
        temp.~WString();
        text.~cString();
        break;
    }
    case 0x19ec2c8b: {
        cString text;
        cPropertyValue* pValue = 0;
        PropertyManager()->GetProperty(mFetchArtifactCargoItemID.mInstance, 0x37d494e, &pValue);
        GetPropertyAsText(pValue, 0x3068d95d, &text);
        WString temp(text.GetText());
        if (pOut != &temp)
            pOut->assign(temp.mpBegin, temp.mpEnd);
        temp.~WString();
        text.~cString();
        break;
    }
    case 0xfb3b1635:
    case 0x2dc69129:
    case 0x6d5c48c:
    case 0x3e994b2b:
    case 0x69412983:
    case 0x736c417f: {
        if (mFetchPlantSpeciesKey.mInstance != EmptyKey()->mInstance
            || mFetchPlantSpeciesKey.mType != EmptyKey()->mType
            || mFetchPlantSpeciesKey.mGroup != EmptyKey()->mGroup) {
            cSpeciesManager* pManager = PlantSpeciesManager(&mFetchPlantSpeciesKey);
            cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&mFetchPlantSpeciesKey);
            if (pProfile != 0) {
                WString temp(pProfile->GetName());
                *pOut = temp;
                temp.~WString();
            }
        } else if (mFetchAnimalSpeciesKey.mInstance != EmptyKey()->mInstance
                   || mFetchAnimalSpeciesKey.mType != EmptyKey()->mType
                   || mFetchAnimalSpeciesKey.mGroup != EmptyKey()->mGroup) {
            cSpeciesManager* pManager = PlantSpeciesManager(&mFetchAnimalSpeciesKey);
            cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&mFetchAnimalSpeciesKey);
            if (pProfile != 0) {
                WString temp(pProfile->GetName());
                *pOut = temp;
                temp.~WString();
            }
        }
        break;
    }
    default:
        break;
    }
}

// ---------------------------------------------------------------------------
// SP::cSPMissionFetch::PickFetchItem
// @ 0x00c53bc0
bool cSPMissionFetch::PickFetchItem()
{
    switch (mTypeOfFetch) {
    case 0xbfb44ccc: {
        cPlanetEco* pEco = GetTargetPlanet()->mpEco;
        mFetchCommodityKey = *pEco->GetCommodityKey();
        return true;
    }
    case 0x23da98ff: {
        mSamplerPlate.clear();
        cPlanet* pPlanet = GetTargetPlanet();
        uint32_t nAnimals = (uint32_t)(pPlanet->mpAnimalKeysEnd - pPlanet->mpAnimalKeysBegin);
        for (uint32_t i = 0; i < nAnimals; ++i) {
            cFetchSample sample;
            sample.mIsAnimal = true;
            sample.mSpeciesKey = pPlanet->mpAnimalKeysBegin[i];
            mSamplerPlate.push_back(sample);
        }
        uint32_t nPlants = (uint32_t)(pPlanet->mpPlantKeysEnd - pPlanet->mpPlantKeysBegin);
        for (uint32_t i = 0; i < nPlants; ++i) {
            cFetchSample sample;
            sample.mIsAnimal = false;
            sample.mSpeciesKey = pPlanet->mpPlantKeysBegin[i];
            mSamplerPlate.push_back(sample);
        }
        return true;
    }
    case 0x19ec2c8b: {
        cItemList* pList = mMissionPropList->FindItems(0x781900a6);
        int32_t nCount;
        if ((pList->mnFlags & 0x30) != 0) {
            nCount = pList->mnCount;
            if (nCount <= 0)
                break;
        } else if (pList->mnCount2 != 0) {
            nCount = 1;
        } else {
            break;
        }
        Key* pKeys = pList->GetKeys();
        uint32_t nIndex = RandomUint32Uniform((uint32_t)nCount);
        mFetchArtifactCargoItemID = pKeys[nIndex];
        return true;
    }
    case 0x2dc69129: {
        mFetchAnimalSpeciesKey = *EmptyKey();
        if (*(const uint32_t*)&mRewardMoney == 0xbb448992 && mpParentMission != 0) {
            cSPMissionFlight101* pFlight = GetSubMission(mpParentMission, 0x0422227d);
            if (pFlight != 0 && pFlight->GetTargetPlanet() != 0) {
                /* parent flight mission already owns a herd target */
            }
        }
        cSpeciesProfile* pProfile = GetTargetPlanet()->GetRandomAnimalSpecies();
        if (pProfile == 0)
            break;
        mFetchAnimalSpeciesKey = pProfile->mSpeciesKey;
        break;
    }
    case 0x3e994b2b:
    case 0x69412983: {
        cPlanet* pPlanet = GetTargetPlanet();
        if (pPlanet == 0 || pPlanet->mpEco == 0)
            return true;
        mFetchAnimalSpeciesKey = *pPlanet->mpEco->GetAnimalKey();
        return true;
    }
    case 0x736c417f: {
        mFetchPlantSpeciesKey = *EmptyKey();
        cPlanet* pPlanet = GetTargetPlanet();
        void* pCapability = GetPlanetCapability(pPlanet);
        (void)pCapability;
        uint32_t nAnimals = (uint32_t)(pPlanet->mpAnimalKeysEnd - pPlanet->mpAnimalKeysBegin);
        for (uint32_t i = 0; i < nAnimals; ++i) {
            Key key = pPlanet->mpAnimalKeysBegin[i];
            GetSetting9(&key);
            GetSpeciesProfile(&key);
        }
        uint32_t nPlants = (uint32_t)(pPlanet->mpPlantKeysEnd - pPlanet->mpPlantKeysBegin);
        for (uint32_t i = 0; i < nPlants; ++i) {
            Key key = pPlanet->mpPlantKeysBegin[i];
            cSpeciesManager* pManager = PlantSpeciesManager(&key);
            cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&key);
            if (pProfile != 0)
                pProfile->GetName();
        }
        bool bAnimals = nAnimals > 0;
        bool bPlants = nPlants > 0;
        if (bAnimals && bPlants) {
            if (RandomUint32Uniform(100) > 50) {
                cSpeciesProfile* pProfile = GetTargetPlanet()->GetRandomAnimalSpecies();
                if (pProfile == 0)
                    break;
                mFetchAnimalSpeciesKey = pProfile->mSpeciesKey;
                break;
            }
        } else if (bAnimals) {
            cSpeciesProfile* pProfile = GetTargetPlanet()->GetRandomAnimalSpecies();
            if (pProfile == 0)
                break;
            mFetchAnimalSpeciesKey = pProfile->mSpeciesKey;
            break;
        } else if (!bPlants) {
            break;
        }
        cSpeciesProfile* pProfile = GetTargetPlanet()->GetRandomPlantSpecies();
        if (pProfile == 0)
            break;
        mFetchPlantSpeciesKey = *pProfile->GetSpeciesKey();
        break;
    }
    case 0x7ecbe6f5:
        return true;
    default:
        break;
    }

    if (mFetchArtifactCargoItemID.mInstance == EmptyKey()->mInstance
        && mFetchArtifactCargoItemID.mType == EmptyKey()->mType
        && mFetchArtifactCargoItemID.mGroup == EmptyKey()->mGroup
        && mFetchAnimalSpeciesKey.mInstance == EmptyKey()->mInstance
        && mFetchAnimalSpeciesKey.mType == EmptyKey()->mType
        && mFetchAnimalSpeciesKey.mGroup == EmptyKey()->mGroup
        && mFetchPlantSpeciesKey.mInstance == EmptyKey()->mInstance
        && mFetchPlantSpeciesKey.mType == EmptyKey()->mType
        && mFetchPlantSpeciesKey.mGroup == EmptyKey()->mGroup) {
        mTypeOfFetch = 0xffffffff;
        return false;
    }
    return true;
}
