// Slice s00e3eca0 -- SPUI layout-manager model cache (world sizes + screen bounds
// keyed by ResourceMan key).  Game code, VS2008 flags.
typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;

// ---------------------------------------------------------------------------
// eastl red-black tree shared by the caches below.
//   tree object:  +0x00 unknown, +0x04 anchor, +0x18 pad
//   node:         +0x00 "greater" child, +0x04 "less" child, +0x08 parent,
//                 +0x0c colour, +0x10 key, +0x14 value
// ---------------------------------------------------------------------------
struct RBNodeBase {
    RBNodeBase* mpGreater;    // +0x00
    RBNodeBase* mpLess;       // +0x04
    RBNodeBase* mpParent;     // +0x08
    uint8_t     mColor;       // +0x0c
    uint8_t     mPad0d[3];    // +0x0d
};

struct RBAnchor {
    RBNodeBase* mpLeft;       // +0x00  anchor address == end()
    RBNodeBase* mpRight;      // +0x04
    RBNodeBase* mpParent;     // +0x08  root
    uint8_t     mColor;       // +0x0c
    uint8_t     mPad0d[3];    // +0x0d
    uint32_t    mLength;      // +0x10
};

struct ModelTree {
    void*       mpAllocator;  // +0x00
    RBAnchor    mAnchor;      // +0x04
    uint32_t    mPad18;       // +0x18

    float* WorldAt(const uint32_t* pKey);      // 0x00e3eca0
    float* BoundsAt(const uint32_t* pKey);     // 0x00e3ed30
};

// map<unsigned, cSPUILayoutManager::cWorld>
struct WorldNode : RBNodeBase {
    uint32_t mKey;            // +0x10
    float    mWidth;          // +0x14
    float    mHeight;         // +0x18
    uint32_t mPad1c;          // +0x1c
};

// map<unsigned, cScreenBounds>
struct BoundsNode : RBNodeBase {
    uint32_t mKey;            // +0x10
    float    mLeft;           // +0x14
    float    mTop;            // +0x18
    float    mRight;          // +0x1c
    float    mBottom;         // +0x20
};

// value_type temporaries handed to the out-of-line tree insert helpers
struct WorldPair {
    union { uint32_t mKey; float mKeyValue; };       // +0x00
    union { float mWidth; uint32_t mWidthBits; };    // +0x04
    union { float mHeight; uint32_t mHeightBits; };  // +0x08
};

struct BoundsPair {
    union { uint32_t mKey; float mKeyValue; };       // +0x00
    union { float mLeft;   uint32_t mLeftBits;   };  // +0x04
    union { float mTop;    uint32_t mTopBits;    };  // +0x08
    union { float mRight;  uint32_t mRightBits;  };  // +0x0c
    union { float mBottom; uint32_t mBottomBits; };  // +0x10
};

union RawFloat {
    uint32_t mBits;
    float    mFloat;
};

// the insert helpers take the insertion hint as a one-word iterator value
struct InsertPos {
    RBNodeBase* mpNode;       // +0x00
};

void __stdcall InsertWorldPair(WorldNode** ppResult, InsertPos pos,
                               const WorldPair* pValue, bool bMulti);      // 0x00e3db00
void __stdcall InsertBoundsPair(BoundsNode** ppResult, InsertPos pos,
                                const BoundsPair* pValue, bool bMulti);    // 0x00e3dbd0
void __stdcall DoNukeSubtree(void* pTree, RBNodeBase* pRoot);              // 0x009a9600
RBNodeBase* FindInWorldTree(ModelTree* pTree, const uint32_t* pKey);       // 0x00e5c780

// ---------------------------------------------------------------------------
// 0x00e3eca0 -- cWorld& map<unsigned, cWorld>::operator[](const unsigned&)
// ---------------------------------------------------------------------------
// @ 0x00e3eca0
float* ModelTree::WorldAt(const uint32_t* pKey)
{
    RBNodeBase* pAnchor = (RBNodeBase*)&mAnchor;
    RBNodeBase* pPos = pAnchor;
    RBNodeBase* pNode = mAnchor.mpParent;

    while (pNode != 0) {
        if (!(((WorldNode*)pNode)->mKey < *pKey)) {
            pPos = pNode;
            pNode = pNode->mpLess;
        } else {
            pNode = pNode->mpGreater;
        }
    }
    if (pPos != pAnchor && !(*pKey < ((WorldNode*)pPos)->mKey)) {
        return &((WorldNode*)pPos)->mWidth;
    }

    WorldPair value;
    value.mKey    = *pKey;
    value.mWidth  = value.mKeyValue;
    value.mHeight = value.mWidth;

    InsertPos pos = { pPos };
    WorldNode* pNew;
    InsertWorldPair(&pNew, pos, &value, false);
    return &pNew->mWidth;
}

// ---------------------------------------------------------------------------
// 0x00e3ed30 -- cScreenBounds& map<unsigned, cScreenBounds>::operator[](const unsigned&)
// ---------------------------------------------------------------------------
// @ 0x00e3ed30
float* ModelTree::BoundsAt(const uint32_t* pKey)
{
    RBNodeBase* pAnchor = (RBNodeBase*)&mAnchor;
    RBNodeBase* pPos = pAnchor;
    RBNodeBase* pNode = mAnchor.mpParent;

    while (pNode != 0) {
        if (!(((BoundsNode*)pNode)->mKey < *pKey)) {
            pPos = pNode;
            pNode = pNode->mpLess;
        } else {
            pNode = pNode->mpGreater;
        }
    }
    if (pPos != pAnchor && !(*pKey < ((BoundsNode*)pPos)->mKey)) {
        return &((BoundsNode*)pPos)->mLeft;
    }

    BoundsPair value;
    value.mKey     = *pKey;
    value.mLeft    = value.mKeyValue;
    value.mTop     = value.mLeft;
    value.mRight   = value.mTop;
    value.mBottom  = value.mRight;

    InsertPos pos = { pPos };
    BoundsNode* pNew;
    InsertBoundsPair(&pNew, pos, &value, false);
    return &pNew->mLeft;
}

// ---------------------------------------------------------------------------
// 0x00e3ede0 -- cSPUILayoutManager::CollectModelKeys(KeyVector&)
// ---------------------------------------------------------------------------
struct KeyVector {
    uint32_t* mpBegin;        // +0x00
    uint32_t* mpEnd;          // +0x04
    uint32_t* mpCapacity;     // +0x08
    uint32_t* begin() { return mpBegin; }
    uint32_t* end()   { return mpEnd; }
    uint32_t* erase(uint32_t* pFirst, uint32_t* pLast);            // 0x0050f740
};

extern "C" void* FUN_01021260();                                   // GetActivePlanet
struct ModelSelector { void __thiscall Select(KeyVector* pKeys); };// 0x00acc800 (thiscall)
void* FUN_00b3d480();                                              // model selector owner
void  FUN_004f6b70(uint32_t* pFirst, uint32_t* pLast);             // eastl::sort
uint32_t* FUN_004f6830(uint32_t* pFirst, uint32_t* pLast);         // eastl::unique

// @ 0x00e3ede0
void FUN_00e3ede0(KeyVector* pKeys)
{
    if (FUN_01021260() != 0) {
        ((ModelSelector*)FUN_00b3d480())->Select(pKeys);
        FUN_004f6b70(pKeys->begin(), pKeys->end());
        uint32_t* pLast = FUN_004f6830(pKeys->begin(), pKeys->end());
        pKeys->erase(pLast, pKeys->end());
    }
}

// ---------------------------------------------------------------------------
// shared player / layout declarations
// ---------------------------------------------------------------------------
struct ResourceKey {
    uint32_t mType;           // +0x00
    uint32_t mInstance;       // +0x04
    uint32_t mGroup;          // +0x08
};

struct KeyInstance {
    uint32_t mId;             // +0x00
    float    mValue;          // +0x04
    uint32_t mExtra;          // +0x08
};

struct Property {
    virtual void v00();            // +0x00
    virtual void Release();        // +0x04
    uint8_t  mPad08[0x0a];         // +0x08
    uint16_t mValueType;           // +0x12
    bool*    GetBool();            // 0x0041e920
    int*     GetInt();             // 0x0041e990
};

struct PropertyManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual bool GetPropertyByKey(uint32_t key, uint32_t prop, Property** ppOut);   // +0x24
    virtual void v0a();                                                              // +0x28
    virtual bool GetProperty(uint32_t key, uint32_t prop, Property** ppOut);          // +0x2c
};

struct KeyVector12 {
    ResourceKey* mpBegin;             // +0x00
    ResourceKey* mpEnd;               // +0x04
    ResourceKey* mpCapacity;          // +0x08
};

struct ModelManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual void GetModels(KeyVector12* pOut, const ResourceKey* pKey, int bFlag);  // +0x38
};

struct IWin {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual float* GetRect();                                                      // +0x38
};

struct cSPUILayout {
    cSPUILayout();                                                // 0x00810000
    bool Init(const ResourceKey& key, bool bFlag, uint32_t id);   // 0x008120d0
    IWin* FindWindowByID(uint32_t id, int bFlag);                 // 0x008105b0
    void Shutdown(uint32_t flags);                                // 0x00811ad0
    ~cSPUILayout();                                               // 0x00811fe0
};

struct ModelKeySet {
    uint32_t   mPad00[2];           // +0x00
    void**     mppBuckets;          // +0x08
    uint32_t   mBucketCount;        // +0x0c
};

struct BoundsStringTree {
    void*    mpAllocator;         // +0x00
    RBAnchor mAnchor;             // +0x04
    uint32_t mPad18;              // +0x18
};

struct cSPUILayoutManager {
    uint32_t         mPad000[0x10];       // +0x000
    IWin*            mpSelectionTarget;   // +0x040
    uint32_t         mPad044[0x3D];       // +0x044
    ModelTree        m_worlds;            // +0x138
    ModelTree        m_bounds;            // +0x154
    uint32_t         mPad170[0x38];       // +0x170
    BoundsStringTree m_boundsTree;        // +0x250
    uint32_t         mPad26c[0xBD];       // +0x26c
    ModelKeySet      m_keySet;            // +0x560
    uint32_t         mPad570[0x04];       // +0x570

    void ResetTree(ModelTree& tree);
    void PreloadModelBounds();
};

struct ModelHash;

void*    EA_ResourceMan_GetManager();                             // 0x0067dcd0
PropertyManager* SP_PropertyManager();                            // 0x0067de30
bool     SP_GetPropertyAsKeyInstance(Property* pProp, uint32_t prop,
                                     uint32_t* pOut);             // 0x006a12a0
float*   SPUIHelpers_GetBoundingScreenRect(float* pRect, IWin* pWin,
                                           char bFlag);           // 0x00808d20
void     operator_delete(void* p);                                // 0x00f47380
uint32_t g_layoutKeyGroup;                                        // 0x015a5930

void cSPUILayoutManager::ResetTree(ModelTree& tree)
{
    DoNukeSubtree(&tree, tree.mAnchor.mpParent);
    RBNodeBase* pAnchor = (RBNodeBase*)&tree.mAnchor;
    tree.mAnchor.mpLeft   = pAnchor;
    tree.mAnchor.mpRight  = pAnchor;
    tree.mAnchor.mpParent = 0;
    tree.mAnchor.mColor   = 0;
    tree.mAnchor.mLength  = 0;
}

// @ 0x00e3f010
void cSPUILayoutManager::PreloadModelBounds()
{
    KeyVector12  models  = { 0, 0, 0 };
    ResourceKey  listKey = { 0x013f662c, 0x00b1b104, 0xe1d7164f };

    ((ModelManager*)EA_ResourceMan_GetManager())->GetModels(&models, &listKey, 0);

    ResetTree(m_worlds);
    ResetTree(m_bounds);

    cSPUILayout layout;

    int count = models.mpEnd - models.mpBegin;
    for (int i = 0; i < count; ++i) {
        ResourceKey* pEntry = &models.mpBegin[i];
        Property*    pProp  = 0;
        if (!SP_PropertyManager()->GetProperty(pEntry->mType, pEntry->mGroup, &pProp))
            continue;

        uint32_t iKeyInstance = 0;
        if (!SP_GetPropertyAsKeyInstance(pProp, 0x34e3b684, &iKeyInstance))
            continue;

        if (FindInWorldTree(&m_worlds, &iKeyInstance) == (RBNodeBase*)&m_worlds.mAnchor)
            continue;

        ResourceKey layoutKey = { iKeyInstance, 0x0510a95b, g_layoutKeyGroup };
        layout.Init(layoutKey, true, 0x05b598fa);

        IWin* pWindow = layout.FindWindowByID(0x94e2c6d2, 1);
        if (pWindow != 0) {
            float* pRect   = pWindow->GetRect();
            float  fWidth  = pRect[2] - pRect[0];
            float  fHeight = pRect[3] - pRect[1];

            float* pWorld = m_worlds.WorldAt(&iKeyInstance);
            pWorld[0] = fWidth;
            pWorld[1] = fHeight;

            float screenRect[4];
            SPUIHelpers_GetBoundingScreenRect(screenRect, pWindow, 1);

            float* pBounds = m_bounds.BoundsAt(&iKeyInstance);
            pBounds[0] = screenRect[0];
            pBounds[1] = screenRect[1];
            pBounds[2] = screenRect[2];
            pBounds[3] = screenRect[3];
        }
        layout.Shutdown(1);
    }
    layout.~cSPUILayout();

    if (models.mpBegin != 0 && ((uint32_t*)models.mpBegin)[-1] != 0)
        operator_delete(models.mpBegin);
}

// ---------------------------------------------------------------------------
// model records used by the selection helpers
// ---------------------------------------------------------------------------
struct cMWModel {
    uint32_t     mPad00;            // +0x00
    cMWModel*    mpNext;            // +0x04
    uint32_t     mPad08[3];         // +0x08
    KeyInstance* mpKeyInstance;     // +0x14
    uint32_t     mPad18[0x16];      // +0x18
    uint32_t     mSizeBudget;       // +0x70
};

struct ModelHash {
    cMWModel* mpFirst;              // +0x00
    uint32_t  mPad04;               // +0x04
    uint32_t  mPad08;               // +0x08
};

struct SizeKeyVector {
    uint32_t* mpBegin;              // +0x00
    uint32_t* mpEnd;                // +0x04
    uint32_t* mpCapacity;           // +0x08
    void DoInsertKey4(uint32_t* pWhere, const uint32_t& value);   // 0x00b96600
};

struct ModelSelectionSource {
    uint32_t  mKey;                 // +0x00
    uint32_t* mpOwner;              // +0x04
    uint32_t  mPad08;               // +0x08
    uint32_t  mPad0c[0x17];         // +0x0c
    uint32_t  mSizeBudget;          // +0x68
};

void FUN_00b41b90(void* pSet, void* pOut, const cMWModel* pModel, int bFlag);   // 0x00b41b90
void FUN_00e48f30(void* pThis, const uint32_t* pBudget,
                  uint32_t iChosen, uint32_t iTotal);                            // 0x00e48f30
void FUN_00e47700(void* pThis, const void* pVec);                                // 0x00e47700
void* FUN_0067de90();                                                            // pool alloc
void  FUN_007eb100(ModelHash* pThis);                                            // 0x007eb100
void  SP_GetPropertyVector(Property* pProp, uint32_t id,
                           void* pOutA, void* pOutB);                            // 0x006a0ae0

// @ 0x00e3f2a0
bool __fastcall FUN_00e3f2a0(cSPUILayoutManager* pThis, int, ModelSelectionSource* pSource,
                             cMWModel* pStart)
{
    uint32_t* pBudget = pSource->mpOwner + 2;
    if (pBudget == 0)
        return false;

    bool      bEnabled  = false;
    int       iLimit    = 0;
    int       iChosen   = 1;
    int       iIndex    = 2;
    int       iCountA   = 0;
    int       iCountB   = 0;
    uint32_t  iKey      = pSource->mKey;
    uint32_t  iTotal    = 0;
    Property* pProp     = 0;
    uint32_t  iEntryA   = 0;
    uint32_t  iEntryB   = 0;
    uint32_t  iKeyInst  = 0;
    float     fOther    = 0.0f;
    float     fHeight   = 0.0f;
    SizeKeyVector modelsA = { 0, 0, 0 };
    SizeKeyVector modelsB = { 0, 0, 0 };
    SizeKeyVector modelsC = { 0, 0, 0 };

    PropertyManager* pProps = SP_PropertyManager();
    pProps->GetProperty(iKey, 0xe1d7164f, &pProp);

    if (pProp != 0) {
        Property* pB = 0;
        pProps->GetPropertyByKey(iKey, 0x94f79745, (Property**)&iEntryA);
        if (pProp != 0 && pProps->GetPropertyByKey(iKey, 0xd53426dd, &pB)) {
            if (pB != 0 && pB->mValueType == 1)
                bEnabled = *pB->GetBool();
        }
        if (pProp != 0 && pProps->GetPropertyByKey(iKey, 0xd52d9182, &pB)) {
            if (pB != 0 && pB->mValueType == 9)
                iLimit = *pB->GetInt();
        }
    }

    SP_GetPropertyVector(pProp, 0xd52d9183, &iCountA, &modelsA);
    SP_GetPropertyVector(pProp, 0x066f843b, &iCountB, &modelsB);
    SP_GetPropertyAsKeyInstance(pProp, 0x34e3b684, &iKeyInst);

    fOther  = 0.0f;
    fHeight = 0.0f;
    if (bEnabled) {
        if (FindInWorldTree(&pThis->m_worlds, &iKeyInst) != (RBNodeBase*)&pThis->m_worlds.mAnchor)
            fHeight = pThis->m_worlds.WorldAt(&iKeyInst)[1];
        if (pThis->mpSelectionTarget != 0) {
            float* pRect = pThis->mpSelectionTarget->GetRect();
            fOther = pRect[3] - pRect[1];
        }
    }

    bool bAny = (iCountA > 0 || iLimit > 0 || iCountB > 0);

    ModelHash* pHash = (ModelHash*)FUN_0067de90();
    FUN_007eb100(pHash);
    cMWModel* pEnd = pHash->mpFirst;

    if (pStart != pEnd) {
        for (cMWModel* pNode = pStart; pNode != pEnd; pNode = pNode->mpNext) {
            KeyInstance* pInst     = pNode->mpKeyInstance;
            uint32_t     iModelKey = pInst->mId;
            uint32_t     iModelSize = pInst->mExtra;
            bool         bFlag     = false;
            bool         bFound    = false;

            if (bAny) {
                if (iLimit > 0 && *pBudget - iModelSize > (uint32_t)iLimit)
                    bFlag = true;
                for (int i = 0; i < iCountA; ++i) {
                    if (modelsA.mpBegin[i] == iModelKey) { bFlag = true; break; }
                }
                for (int i = 0; i < iCountB; ++i) {
                    if (modelsB.mpBegin[i] == iModelKey) { bFound = true; break; }
                }
                if (iCountB > 0 && !bFound)
                    bFlag = true;
            }
            if (bEnabled && iCountB == 0 && (float)iIndex * fHeight < fOther)
                goto Select;
            if (bFlag)
                goto Select;
            if (iModelKey != iKey && !bFound)
                continue;

        Select:
            ++iChosen;
            ++iIndex;
            iTotal += pNode->mSizeBudget;
            {
                uint32_t   iBucket = (uint32_t)pNode % pThis->m_keySet.mBucketCount;
                cMWModel** ppSlot  = (cMWModel**)&((cMWModel**)pThis->m_keySet.mppBuckets)[iBucket];
                cMWModel*  pCur    = *ppSlot;
                bool       bInSet  = false;
                for (; pCur != 0; pCur = pCur->mpNext) {
                    if (pCur == pNode) { bInSet = true; break; }
                }
                if (!bInSet)
                    FUN_00b41b90(&pThis->m_keySet, ppSlot, pNode, 0);
            }
            {
                uint32_t iModel = (uint32_t)pNode;
                modelsC.DoInsertKey4(modelsC.mpEnd, iModel);
            }
        }
    }

    FUN_00e48f30(pStart, pBudget, (uint32_t)iChosen, iTotal);
    FUN_00e47700(pThis, &modelsC);
    if (pProp != 0)
        pProp->Release();
    if (modelsC.mpBegin != 0 && ((uint32_t*)modelsC.mpBegin)[-1] != 0)
        operator_delete(modelsC.mpBegin);
    return true;
}

// ---------------------------------------------------------------------------
// 0x00e3f7a0 -- cached model height lookup
// ---------------------------------------------------------------------------
float  FUN_00e37d70(void* pThis, float fValue);                    // 0x00e37d70
float* FUN_00be0790(const uint32_t* pKey);                        // 0x00be0790
void*  FUN_0067de90(int nSize);                                   // pool alloc (sized)
uint32_t* FindInBoundsTree(BoundsStringTree* pTree, const uint32_t* pKey);  // 0x00e39fb0
float  g_flHeightLimit;                                           // 0x016ace30

// @ 0x00e3f7a0
float __fastcall FUN_00e3f7a0(cSPUILayoutManager* pThis, int, uint32_t iKey)
{
    if (iKey != 0xa426730b && iKey != 0xad56080c)
        return 0.0f;

    if (FindInBoundsTree(&pThis->m_boundsTree, &iKey) != (uint32_t*)&pThis->m_boundsTree.mAnchor)
        return *FUN_00be0790(&iKey);

    if (FUN_0067de90() == 0)
        return 0.0f;

    ModelHash* pHash = (ModelHash*)FUN_0067de90(0x0c);
    if (pHash == 0) {
        *FUN_00be0790(&iKey) = 0.0f;
        return 0.0f;
    }
    FUN_007eb100(pHash);

    cMWModel* pEnd = pHash->mpFirst;
    if (pEnd != 0) {
        for (cMWModel* pNode = pHash->mpFirst; pNode != pEnd; pNode = pNode->mpNext) {
            KeyInstance* pInst     = pNode->mpKeyInstance;
            uint32_t     iModelKey = pInst->mId;
            Property*    pProp     = 0;

            SP_PropertyManager()->GetProperty(iModelKey, 0xe1d7164f, &pProp);

            if (pProp != 0) {
                uint32_t iOtherKey = 0;
                SP_GetPropertyAsKeyInstance(pProp, 0x91ad064, &iOtherKey);
                if (iOtherKey == iKey) {
                    float fValue = FUN_00e37d70(pThis, pInst->mValue);
                    if (fValue < -g_flHeightLimit) fValue = -g_flHeightLimit;
                    if (fValue >  g_flHeightLimit) fValue =  g_flHeightLimit;
                    *FUN_00be0790(&iKey) = fValue;
                    pProp->Release();
                    return fValue;
                }
                pProp->Release();
            }
        }
    }
    *FUN_00be0790(&iKey) = 0.0f;
    return 0.0f;
}
