// Slice s0103dee0 -- SP::cSPSpaceTrading spice/tool selling decisions.
typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef int            int32_t;

// ---------------------------------------------------------------------------
// property plumbing
// ---------------------------------------------------------------------------
struct Property {
    virtual void v00();            // +0x00
    virtual void Release();        // +0x04
    virtual void v02();            // +0x08
    uint8_t  mPad0c[6];            // +0x0c
    uint16_t mValueType;           // +0x12
    bool*    GetBool();            // 0x0041e920
    int*     GetInt();             // 0x0041e990
    float*   GetFloat();           // 0x0041e9d0
};

struct PropertyManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual bool HasProperty(uint32_t prop);                                   // +0x1c
    virtual void v08();                                                        // +0x20
    virtual bool GetPropertyByKey(uint32_t prop, Property** ppOut);            // +0x24
    virtual void v0a();                                                        // +0x28
    virtual bool GetProperty(uint32_t key, uint32_t prop, Property** ppOut);   // +0x2c
};

// an AutoRefCount<SP::cSPSpaceInventoryItem>; the item object owns the counts
struct cSpaceItem {
    virtual void v00();            // +0x00
    virtual void AddRef();         // +0x04
    virtual void Release();        // +0x08
    virtual void v03();            // +0x0c
    virtual void v04();            // +0x10
    virtual void v05();            // +0x14
    virtual int* GetKey();         // +0x18
    uint8_t  mPad04[0x0c];         // +0x04
    uint32_t mPoliticalId;         // +0x10
    uint32_t mItemCount;           // +0x14
};

struct ItemRef {
    cSpaceItem* mpObject;          // +0x00
    ItemRef() : mpObject(0) {}
    ItemRef(cSpaceItem* p) : mpObject(p) {}
    operator cSpaceItem*() const { return mpObject; }
};

// eastl::vector<ItemRef>; push_back keeps the inlined fast path (slow path 0x00f14270)
struct ItemVec {
    ItemRef* mpBegin;              // +0x00
    ItemRef* mpEnd;                // +0x04
    ItemRef* mpCapacity;           // +0x08
    void DoInsert(ItemRef* pWhere, const ItemRef* pValue);        // 0x00f14270
    void push_back(cSpaceItem* pObject) {
        ItemRef* pSlot = mpEnd;
        if (pSlot < mpCapacity) {
            mpEnd = pSlot + 1;
            if (pSlot) {
                pSlot->mpObject = pObject;
                if (pObject)
                    pObject->AddRef();
            }
        } else {
            ItemRef value(pObject);
            DoInsert(pSlot, &value);
        }
    }
};

struct cSPTimer {
    void Restart();                // 0x00bc3130
    unsigned long long GetElapsedTime();   // 0x00bc2e50
};

struct ItemStore {
    uint8_t  mPad00[0x2c];         // +0x00
    cSPTimer mTimer;               // +0x2c
    uint32_t mPad30;               // +0x30
    ItemVec  mInventory;           // +0x34
    uint32_t mPad40[2];            // +0x40
    uint32_t mAgesHandle;          // +0x48
    uint32_t mPad4c;               // +0x4c
};

struct cInventory {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28();
    virtual bool HasItem(const char* pName);       // +0x74
};

struct cGameNounManager {
    void* GetAvatar();                             // 0x00b1fdb0
};

struct cSPSimulatorSpaceGame {
    cInventory* GetPlayerInventory();              // 0x00a1ad60
};

struct ToolInfo {
    uint8_t  mPad00[0x28];         // +0x00
    int32_t  mCount;               // +0x28
    uint8_t  mPad2c[0x2c];         // +0x2c
    int32_t  mSpiceIndex;          // +0x58
};

struct ItemInfo;

struct cSPSpaceTrading {
    uint8_t        mPad00[0x48];       // +0x00
    ItemStore**    mppStores;          // +0x48
    uint32_t       mPad4c[0x0a];       // +0x4c
    ItemVec        mSelling;           // +0x74
    uint32_t       mPad80[0x07];       // +0x80
    int32_t        mStoreIndex;        // +0x9c
    uint32_t       mPadA0[0x40];       // +0xa0
    ToolInfo*      mpSelectedToolInfo; // +0x1a0

    void CreateCommodityFromID(cSpaceItem** ppOut, cSpaceItem** ppSecond,
                               Property* pProp, float fValue);      // 0x0103a480
    bool ConsiderSellingTool(int iObjectID, ToolInfo* pInfo, uint32_t iKey,
                             int iMode, void* pExtra);
    bool ConsiderSellingSpice(int iObject, int iKeyA, int iKeyB, int iKeyC);
};

struct SpaceGame {
    uint8_t mPad00[0xc4];          // +0x00
    uint8_t mFlags;                // +0xc4
};

struct RandomLinearCongruential {
    double RandomDoubleUniform();
};

cSPSimulatorSpaceGame* SP_SpaceGameGet();                                  // 0x01002bd0
SpaceGame* SpaceGameGet();                                                 // 0x01002bd0
int*   FUN_00b8dad0(cSPSpaceTrading* pThis);                               // 0x00b8dad0
Property* FUN_00c705c0(int iObject, int iFlag);                            // 0x00c705c0
cGameNounManager* FUN_00b8de30(cSPSpaceTrading* pThis);                     // 0x00b8de30
int    SP_GetPlayerEmpireID();                                             // 0x01021090
void*  SP_GetPlayerEmpire();                                               // 0x00c32c10
PropertyManager* GetPropertyManager();                                     // 0x0067de30
void   SP_GetPropertyT(Property* pProp, uint32_t prop, void* pOut);        // 0x0040cf10
void   FUN_0103de00(void* pAges);                                          // 0x0103de00
float  FUN_01005c60(int n);                                                // 0x01005c60
bool   FUN_00c322c0(int n);                                                // 0x00c322c0
float  FUN_00c75c30(uint32_t key);                                         // 0x00c75c30
void   FUN_00c308d0(void* pEmpire);                                        // 0x00c308d0
void   FUN_00c31bc0(int iValue);                                           // 0x00c31bc0
void   FUN_00b3d2a0(void* pAvatar);                                        // 0x00b3d2a0
int    FUN_00ba9370(void* pAvatar);                                        // 0x00ba9370
void   GetPropertyAsKey(Property* pProp, uint32_t prop, uint32_t* pOut);   // 0x0040cf50
bool   GetPropertyAsKeyInstance(Property* pProp, uint32_t prop, int* pOut); // 0x006a12a0
float* GetPropertyAsFloat(Property* pProp);                                // 0x0040cfb0
int*   GetPropertyAsInt(Property* pProp);                                  // 0x0040cfa0
cGameNounManager* GetNounManager();                                        // 0x0067de90
void*  NounManager(uint32_t key);                                          // 0x00b5b800
bool   AreBasicToolConditionsMet(Property* pProp, int bFlag);              // 0x0103c000
int    FUN_011e0810();                                                     // 0x011e0810
RandomLinearCongruential sMathRandom;                                      // 0x016aca40

const char kItemInterplanetaryDrive[] = "k_interplanetarydrive";

// ---------------------------------------------------------------------------
// 0x0103e6e0 -- cSPSpaceTrading::ConsiderSellingSpice
// ---------------------------------------------------------------------------
// @ 0x0103e6e0
bool cSPSpaceTrading::ConsiderSellingSpice(int iObject, int iKeyA, int iKeyB, int iKeyC)
{
    if (!SP_SpaceGameGet()->GetPlayerInventory()->HasItem(kItemInterplanetaryDrive))
        return false;

    int* pKey = FUN_00b8dad0((cSPSpaceTrading*)iObject);   // key of the object handed in
    if (iKeyA != pKey[0] || iKeyB != pKey[1] || iKeyC != pKey[2])
        return false;

    Property* pSpice = FUN_00c705c0(iObject, 0);
    if (pSpice == 0)
        return false;

    float fValue;
    if ((int)FUN_00b8de30(this)->GetAvatar() == SP_GetPlayerEmpireID()) {
        fValue = 0.0f;
    } else {
        Property* pProp = 0;
        GetPropertyManager()->GetProperty(iKeyA, 0x34d97fa, &pProp);
        SP_GetPropertyT(pProp, 0x34f1a4a, &fValue);
        if (pProp != 0)
            pProp->Release();
    }

    cSpaceItem* pItem = 0;
    cSpaceItem* pOther = 0;
    CreateCommodityFromID(&pItem, &pOther, pSpice, fValue);
    mppStores[mStoreIndex]->mInventory.push_back(pItem);
    cSpaceItem* pFirst = pItem;
    FUN_0103de00(&mppStores[mStoreIndex]->mAgesHandle);
    mppStores[mStoreIndex]->mTimer.Restart();

    CreateCommodityFromID(&pItem, &pOther, (Property*)0, fValue);
    mSelling.push_back(pItem);

    if (pItem != 0)
        pItem->Release();
    if (pFirst != 0)
        pFirst->Release();
    return true;
}

// ---------------------------------------------------------------------------
// 0x0103dee0 -- cSPSpaceTrading::ConsiderSellingTool
// ---------------------------------------------------------------------------
// spice chance property per trade-commodity index (0x0567ddd0.. , then 0x05f89ff4..)
static const uint32_t s_spiceChanceKeys[] = {
    0x0567ddd0, 0x0567ddd1, 0x0567ddd2, 0x0567ddd3, 0x0567ddd4,
    0x0567ddd5, 0x0567ddd6, 0x0567ddd7, 0x0567ddd8, 0x05f89ff4,
    0x05f89ff5, 0x05f89ff6, 0x05f89ff7, 0x05f89ff8, 0x05f89ff9,
    0x05f89ffa, 0x05f89ffb, 0x05f89ffc, 0x05f89ffd
};

// spice price property per trade-commodity index (0x05b80b32..)
static const uint32_t s_spicePriceKeys[] = {
    0x05b80b32, 0x05b80b33, 0x05b80b34, 0x05b80b35, 0x05b80b36,
    0x05b80b37, 0x05b80b38, 0x05b80b39, 0x05b80b3a, 0x05b80b3c,
    0x05b80b3b, 0x05b80b3c, 0x05b80b3d, 0x05b80b3d, 0x05b80b3c,
    0x05b80b3b, 0x05b80b3d, 0x05b80b3b, 0x05b80b3c
};

// @ 0x0103dee0
bool cSPSpaceTrading::ConsiderSellingTool(int iObjectID, ToolInfo* pInfo, uint32_t iKey,
                                          int iMode, void* pExtra)
{
    Property* pProp = 0;
    bool      bToolTypeOk = false;
    int       iToolType = 0;
    int       iKeyOut = 0;

    cGameNounManager* pNounMgr = GetNounManager();
    void* pAvatar = pNounMgr->GetAvatar();
    FUN_00b3d2a0(pAvatar);
    int iEmpire = FUN_00ba9370(pAvatar);
    FUN_00c308d0(SP_GetPlayerEmpire());
    FUN_00c31bc0(iEmpire);

    PropertyManager* pProps = GetPropertyManager();
    pProps->GetProperty(iKey, 0x34d97fa, &pProp);

    uint32_t keyA[3] = { 0, 0, 0 };
    GetPropertyAsKey(pProp, 0x34f1a4f, keyA);
    if (keyA[0] == 0x4edcc2bf) {
        iToolType = 1;
        bToolTypeOk = true;
    } else if (!pProps->HasProperty(0x057f3499)) {
        iToolType = 3;
    } else {
        Property* pTypeProp = 0;
        if (pProp != 0 && pProps->GetPropertyByKey(0x057f3499, &pTypeProp) &&
            pTypeProp->mValueType == 10)
            iToolType = *GetPropertyAsInt(pTypeProp);
    }

    bool bHasSpice = pProps->HasProperty(0x05caa7c3);
    if ((!bToolTypeOk && !bHasSpice) || (iEmpire == iMode && pInfo->mCount < 3))
        goto Fail;

    if (bHasSpice) {
        ItemStore* pStore = mppStores[mStoreIndex];
        ItemVec*   pVec   = &pStore->mInventory;
        int        nItems = (int)(pVec->mpEnd - pVec->mpBegin);
        for (int i = 0; i < nItems; ++i) {
            cSpaceItem* pItem = pVec->mpBegin[i].mpObject;
            int* pItemKey = pItem->GetKey();
            if (pItemKey[0] != pInfo->mCount || pItemKey[1] != iKey ||
                pItemKey[2] != iObjectID)
                continue;

            int iAgeProp = 0;
            if (pProp != 0) {
                Property* pAge = 0;
                if (pProps->GetPropertyByKey(0x05caa7c3, &pAge) &&
                    pAge->mValueType == 9)
                    iAgeProp = *GetPropertyAsInt(pAge);
            }
            NounManager(0xa5345685);
            FUN_00c75c30(0xa5345685);
            int      iLimit = iAgeProp * 60000;
            int      iNow   = FUN_011e0810();
            unsigned long long iElapsed = pStore->mTimer.GetElapsedTime();
            if (iNow == 0 || iElapsed < (unsigned long long)iLimit || (Property*)pItem == pProp)
                goto Fail;
        }
    }

    bool bTypeFlag = false;
    Property* pType1 = 0;
    if (pProp != 0 && pProps->GetPropertyByKey(0x34f1a50, &pType1) &&
        pType1->mValueType == 1)
        bTypeFlag = *pType1->GetBool();
    bool bProceed = !(!bToolTypeOk && bTypeFlag);

    uint32_t keyB[3] = { 0, 0, 0 };
    GetPropertyAsKey(pProp, 0x35d5cb4, keyB);

    float fBasePrice = 0.0f;
    Property* pPriceProp = 0;
    if (pProp != 0 && pProps->GetPropertyByKey(0x34f1a49, &pPriceProp) &&
        pPriceProp->mValueType == 0x0d)
        fBasePrice = *GetPropertyAsFloat(pPriceProp);

    if (!bProceed || !AreBasicToolConditionsMet(pProp, 1))
        goto Fail;

    uint32_t iChanceKey = s_spiceChanceKeys[pInfo->mSpiceIndex];
    int      iChance = 0;
    if (pProps->HasProperty(iChanceKey))
        SP_GetPropertyT(pProp, iChanceKey, &iChance);

    if ((float)iChance <= (float)sMathRandom.RandomDoubleUniform() * 100.0f)
        goto Fail;

    float fMultiplier = 1.0f;
    Property* pMultProp = 0;
    if (pProp != 0 && pProps->GetPropertyByKey(0x34f1a4a, &pMultProp) &&
        pMultProp->mValueType == 0x0d)
        fMultiplier = *GetPropertyAsFloat(pMultProp);

    int iPrice = 0x3f800000;
    SP_GetPropertyT(pProp, s_spicePriceKeys[pInfo->mSpiceIndex], &iPrice);

    float fPriceFactor = 1.0f;
    if (pInfo == mpSelectedToolInfo) {
        int iType = 0;
        GetPropertyAsKeyInstance(pProp, 0x6009608, &iType);
        if ((iType == (int)0x9ab762c0 && (SpaceGameGet()->mFlags & 4) != 0) ||
            (iType == (int)0x5ec025c8 && (SpaceGameGet()->mFlags & 2) != 0)) {
            fPriceFactor = FUN_01005c60(2);
        } else {
            if (iType == (int)0xa4c2f6bd && FUN_00c322c0(6))
                fPriceFactor = FUN_01005c60(2);
            if (iType == (int)0x90348c2e && FUN_00c322c0(8))
                fPriceFactor = FUN_01005c60(2);
        }
    }

    NounManager(0x35edc257);
    float fTerrain = FUN_00c75c30(0x35edc257);
    float fValue = (float)iPrice * fMultiplier * fTerrain * fPriceFactor;

    cSpaceItem* pItem = 0;
    CreateCommodityFromID(&pItem, (cSpaceItem**)&iKeyOut, pProp, fValue);

    ItemStore* pStore = mppStores[mStoreIndex];
    pStore->mInventory.push_back(pItem);
    FUN_0103de00(&pStore->mAgesHandle);
    pStore->mTimer.Restart();

    cSpaceItem* pItemB = 0;
    CreateCommodityFromID(&pItemB, (cSpaceItem**)&iKeyOut, (Property*)0, fValue);
    mSelling.push_back(pItemB);

    if (pItemB != 0)
        pItemB->Release();
    if (pItem != 0)
        pItem->Release();
    if (pProp != 0)
        pProp->Release();
    return true;

Fail:
    if (pProp != 0)
        pProp->Release();
    return false;
}
