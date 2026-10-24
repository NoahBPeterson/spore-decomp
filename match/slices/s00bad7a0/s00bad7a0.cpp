// s00bad7a0 -- the star-manager side of the space simulator: the feedback map
// erase, the two teardown passes, the load-from-save-object path, the per-star
// visibility update, the inventory-item update, the civilization counter map
// operator[], the string-vector growth/copy helpers, the cheat handler and the
// manager constructor.
//
//   0x00bad7a0 cStarManager::EraseFeedback      (map erase by object handle)
//   0x00bad810 cStarManager::Reset              (banner + agent teardown)
//   0x00bad8d0 cStarManager::Shutdown           (idle-state teardown)
//   0x00bad940 cStarManager::LoadFromObject
//   0x00badae0 cStarManager::UpdateVisibility
//   0x00badd10 cStarManager::UpdateItem
//   0x00badea0 CivCounterMap::operator[]
//   0x00bae000 WStringVector::Reserve
//   0x00bae0a0 WStringVector::CopyFrom
//   0x00bae130 cStarManager::Cheat
//   0x00bae490 cStarManager::cStarManager
//
// Layout note: the manager keeps the banner list at +0x3c/+0x40, the star list
// at +0x50/+0x54, the feedback rbtree at +0x150 (anchor +0x04, size +0x14), the
// pending handle at +0x14c, the current item at +0x1dc, the world string at
// +0x6c..+0x74 and the state/flags at +0x28/+0x2c.  The rbtree layout is shared
// by both maps: allocator word, the self-referencing end node, the root pointer
// and the element count.
#include "types.h"
#include <string.h>

#define nullptr 0

// ---------------------------------------------------------------------------
// engine objects
// ---------------------------------------------------------------------------

// Game-side polymorphic object; every slot is named by its byte offset since
// this file only ever calls through the vtable.
class IGameObject {
public:
    virtual void* Slot00();                         // +0x000
    virtual void Release();                         // +0x004
    virtual void Release2();                        // +0x008
    virtual void* Slot0c();
    virtual void* Slot10();                         // +0x010
    virtual void* Slot14();
    virtual void* Slot18();
    virtual void* Slot1c();
    virtual void* Slot20();
};

// EA::AutoRefCount<...>-style handle: releasing through slot +4.
class IRefCounted {
public:
    virtual void* Slot00();                         // +0x000
    virtual void Release();                         // +0x004
    virtual void Release2();                        // +0x008
};

class cGonzagoSubsystem {
public:
    cGonzagoSubsystem();                            // 0x00b5b960
    virtual void Slot00();
    virtual void Slot04();
    uint8_t mPad00[0x18];       // +0x004
};

class cCivilization;
class cStarAgent;

class cGameNounManager {
public:
    void RemoveNounsOfType(int32_t nType);          // 0x00b22650
};

// the background simulator singleton: only its +8 slot is used here
class cSPBackgroundSimManager {
public:
    uint8_t mPad00[0x08];       // +0x00
    IRefCounted* mpIdleState;   // +0x08
};

extern cSPBackgroundSimManager* gspBackgroundSimManager;    // 0x016dda8c

struct Vector3 {
    float x;
    float y;
    float z;
};

// eastl::basic_string<wchar_t> -- three pointers, the capacity word last.
class WString {
public:
    void Assign(const wchar_t* pFirst, const wchar_t* pLast);   // 0x00423650
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
};

// a node of the feedback rbtree: 0x10 bytes of links, the key, then the value
class FeedbackNode {
public:
    FeedbackNode* mpLeft;       // +0x00
    FeedbackNode* mpRight;      // +0x04
    FeedbackNode* mpParent;     // +0x08
    bool mbRed;                 // +0x0c
    uint8_t mPad0d[0x03];       // +0x0d
    uint32_t mnKey;             // +0x10
    IRefCounted* mpValue;       // +0x14
};

struct MapIterator {
    FeedbackNode* mpNode;       // +0x00
};

// eastl::map<key, T>: the anchor node is the second word and the root pointer
// the fourth; the element count follows the 0x10-byte anchor.
class RbTree {
public:
    uint8_t mPad00[0x04];       // +0x00  (allocator word)
    FeedbackNode* mpAnchor;     // +0x04  (self-referencing end node)
    uint8_t mPad08[0x04];       // +0x08
    FeedbackNode* mpRoot;       // +0x0c
    uint32_t mnSize;            // +0x10
};

// eastl::map<SP::cCivilization*, uint32_t>
class CivCounterMap {
public:
    uint32_t& GetCounter(cCivilization* pKey);      // 0x00badea0
    void DoInsertValue(FeedbackNode* pParent, const uint32_t* pKey,
                       uint32_t nValue);            // 0x00baa660

    RbTree mTree;               // +0x00
};

// eastl::map<uint32_t, AutoRefCount<cFeedbackEvent>>
class FeedbackMap {
public:
    MapIterator Find(const uint32_t& rKey);         // 0x00e5c780

    RbTree mTree;               // +0x00
};

// the agent/starbase record hung off the two pointer lists
class cStarAgentRecord {
public:
    uint8_t mPad00[0x3c];       // +0x000
    bool mbActive;              // +0x03c
    IRefCounted* mpEffect;      // +0x040
    uint8_t mPad44[0x1c];       // +0x044
    WString mName;              // +0x060
};

// the banner list element
class cBanner {
public:
    uint8_t mPad00[0x40];       // +0x000
    IGameObject* mpOwner;       // +0x040
};

// eastl::vector<eastl::basic_string<wchar_t>> -- 0x10-byte elements
class WStringVector {
public:
    void Reserve(uint32_t nCount);                          // 0x00bae000
    WStringVector* CopyFrom(const WStringVector* pOther);   // 0x00bae0a0

    WString* mpBegin;           // +0x00
    WString* mpEnd;             // +0x04
    WString* mpCapacity;        // +0x08
    uint8_t mAllocator[0x04];   // +0x0c
};

// ---------------------------------------------------------------------------
// imports and helpers
// ---------------------------------------------------------------------------

void __cdecl operator_delete(void* pBlock);                             // 0x00f47380
void* __cdecl operator_new(size_t nSize, const char* pName, int32_t nA,
                           int32_t nB, const char* pFile, int32_t nLine);   // 0x00f473a0

cGameNounManager* __cdecl NounManager();                                // 0x00b3d300
void* __cdecl CheatManager();                                           // 0x00b3d2a0
IGameObject* __cdecl SaveLoadManager();                                 // 0x00fd9c60
void* __cdecl cStar_GetSolarSystem(void* pStar);                        // 0x00c8b770
float __cdecl cStar_GetOrbitRadius(void* pSolarSystem, int32_t nIndex,
                                   int32_t nOne);                       // 0x00c84d40
float __cdecl cPlanet_GetOrbitRadius(void* pPlanet, int32_t nIndex,
                                     int32_t nOne);                     // 0x00c84c60
void __cdecl SetVisible(void* pObject, int32_t nOne);                   // 0x00c70f90
float __cdecl VectorLength(const Vector3* pVector);                     // 0x0040ae50
uint32_t __cdecl RandomUint32Uniform(uint32_t nRange);                  // 0x00a68fb0
void* __cdecl ChildGetSomething(uint32_t nPrompt);                      // 0x00401090
void* __cdecl AddRefObject(void* pObject);                              // 0x00801920
void __cdecl FUN_00b3d420();                                            // 0x00b3d420
void* __cdecl FUN_006b42e0(void* pObject);                              // 0x006b42e0
uint32_t __cdecl FUN_00b8d8f0(void);                                    // 0x00b8d8f0
void* __cdecl FUN_00ba6d80(uint32_t nA);                                // 0x00ba6d80
uint32_t __cdecl GetItemInstanceID(void* pItem);                        // 0x00c87040
int32_t __cdecl FUN_00b8dab0(void);                                     // 0x00b8dab0
void __cdecl FUN_00ba7bd0(void* pCfg);                                  // 0x00ba7bd0
void __cdecl FUN_00bab010(void* pCfg, void* pArg);                      // 0x00bab010
bool __cdecl FUN_00bb9af0(void* pItem, int32_t nFlags);                 // 0x00bb9af0
void __cdecl FUN_00bad440(void* pSelf, void* pObject, void* pCfg);      // 0x00bad440
void __cdecl FUN_00ba8220(void* pCfg);                                  // 0x00ba8220
void __cdecl FUN_00bb9b90(void* pA);                                    // 0x00bb9b90
void __cdecl FUN_00bb9ad0(int32_t nA);                                  // 0x00bb9ad0
void __cdecl FUN_00bb9b00(int32_t nA, int32_t nB);                      // 0x00bb9b00
void* __cdecl FUN_00bbaa60(int32_t nA);                                 // 0x00bbaa60
void __cdecl FUN_00c86e50();                                            // 0x00c86e50
void __cdecl FUN_004df3e0(void* pObject);                               // 0x004df3e0
void __cdecl FUN_00bac3a0();                                            // 0x00bac3a0
void __cdecl FUN_00c30c60();                                            // 0x00c30c60
void __cdecl FUN_01021230();                                            // 0x01021230
void __cdecl FUN_01039070(void* pObject);                               // 0x01039070
void __cdecl CopyImpl_0(void* pFirst, void* pLast, void* pOut);         // 0x006782c0
void __cdecl RBTreeIncrement(FeedbackNode* pNode);                      // 0x00921580
void __cdecl RBTreeErase(FeedbackNode* pNode, void* pAnchor);           // 0x00921880
WString* __cdecl UninitializedCopyStrings(WString* pFirst, WString* pLast,
                                          WString* pOut);               // 0x0054b400
WString* __cdecl UninitializedRelocateCommit(WString* pFirst, WString* pLast,
                                             WString* pOut);            // 0x005e9550
void __cdecl VectorBoolGrow(int32_t nCount, void* pAllocator);          // 0x00b93c60
void* __cdecl FUN_00829110(void* pDest, void* pFirst, void* pLast,
                           void* pOut, void* pExtra);                   // 0x00829110
int32_t* __cdecl OptionArguments(void* pArgs, const char* pName, int32_t* pCount,
                                 int32_t nMin, int32_t nMax);           // 0x00838130
bool __cdecl DoFindNode(const char* pKey, const char* pData);           // 0x01436318
void* __cdecl cConcat(void* pOut, void* pA, void* pB);                  // 0x00618890
int32_t __cdecl cSPLivingUniverse_GetPlayerEmpire();                    // 0x00c71e30

extern int32_t gCheatStarCount;                 // 0x0168964c
extern float gRandomScale;                      // 0x01471064
extern float gRandomScale2;                     // 0x01470f1c
extern float gRealOne;                          // 0x01485720
extern const char gCheatFlush[];                // 0x01455358
extern const char gCheatHistory[];              // 0x013f0d64
extern const char gCheatStar[];                 // 0x01455f24
extern const char gCheatEmpires[];              // 0x01436318
extern const char gCheatCurrent[];              // 0x01436318
extern const char gCheatStarsName[];            // 0x01436318
extern wchar_t gEmptyString16[];                // 0x01667bac

// eastl::vector<T*>::erase(begin, last, end) with last == end: the move is a
// zero-length memcpy and the new end is the begin pointer.
template <class T>
static int32_t EraseAllPointers(T** pBegin, T** pLast, T** pEnd)
{
    memcpy(pBegin, pLast, (size_t)((char*)pEnd - (char*)pLast));
    return (int32_t)(pBegin - pEnd);
}

// ---------------------------------------------------------------------------
// the maps
// ---------------------------------------------------------------------------

// @ 0x00badea0
uint32_t& CivCounterMap::GetCounter(cCivilization* pKey)
{
    FeedbackNode* pAnchor = mTree.mpAnchor;
    FeedbackNode* pParent = pAnchor;
    FeedbackNode* pNode = mTree.mpRoot;
    while (pNode != nullptr) {
        if (pNode->mnKey < (uint32_t)(size_t)pKey) {
            pNode = pNode->mpLeft;
        } else {
            pParent = pNode;
            pNode = pNode->mpRight;
        }
    }
    if (pParent != pAnchor && (uint32_t)(size_t)pParent->mnKey >= (uint32_t)(size_t)pKey)
        return *(uint32_t*)&pParent->mpValue;

    DoInsertValue(pParent, (const uint32_t*)&pKey, 0);
    return *(uint32_t*)&pParent->mpValue;
}

// ---------------------------------------------------------------------------
// the manager
// ---------------------------------------------------------------------------
class cStarManager : public cGonzagoSubsystem {
public:
    cStarManager();                                         // 0x00bae490
    void EraseFeedback(void* pEvent);                       // 0x00bad7a0
    void Reset();                                           // 0x00bad810
    void Shutdown();                                        // 0x00bad8d0
    void LoadFromObject(void* pObject);                     // 0x00bad940
    void UpdateVisibility(void* pStar, void* pPlanet, float fNear, float fFar,
                          const Vector3* pOffset);          // 0x00badae0
    void UpdateItem(void* pItem, void* pConfig);            // 0x00badd10
    void Cheat(void* pArguments);                           // 0x00bae130

    uint8_t mPad1c[0x08];           // +0x01c
    cStarManager* mpListSelf;       // +0x024
    int32_t mnState;                // +0x028
    uint32_t mnFlags;               // +0x02c
    bool mbLoaded;                  // +0x030
    uint8_t mPad31[0x03];           // +0x031
    IRefCounted* mpPending;         // +0x034
    uint8_t mPad38[0x04];           // +0x038
    cBanner** mppBanners;           // +0x03c
    cBanner** mppBannersEnd;        // +0x040
    Vector3 mOffset;                // +0x044
    cStarAgentRecord** mppAgents;   // +0x050
    cStarAgentRecord** mppAgentsEnd;// +0x054
    uint8_t mPad58[0x0c];           // +0x058
    bool mbVisible;                 // +0x064
    uint8_t mPad65[0x07];           // +0x065
    WString mWorldName;             // +0x06c
    uint8_t mPad78[0x64];           // +0x078
    IRefCounted** mppThreats;       // +0x0dc
    IRefCounted** mppThreatsEnd;    // +0x0e0
    uint8_t mPadE4[0x68];           // +0x0e4
    uint8_t* mpHandleTable;         // +0x14c
    FeedbackMap mFeedback;          // +0x150
    uint8_t mPad168[0x74];          // +0x168
    IRefCounted* mpCurrentItem;     // +0x1dc
    uint8_t mPad1e0[0x08];          // +0x1e0
    int32_t mnItemCount;            // +0x1e8
    uint8_t mPad1ec[0x30];          // +0x1ec
};

// @ 0x00bad7a0
void cStarManager::EraseFeedback(void* pEvent)
{
    uint32_t nKey = *(uint32_t*)((uint8_t*)pEvent + 0x84);
    MapIterator it = mFeedback.Find(nKey);
    if (it.mpNode != mFeedback.mTree.mpAnchor) {
        --mFeedback.mTree.mnSize;
        RBTreeIncrement(it.mpNode);
        RBTreeErase(it.mpNode, mFeedback.mTree.mpAnchor);
        if (it.mpNode->mpValue != nullptr)
            it.mpNode->mpValue->Release();
        operator_delete(it.mpNode);
    }
}

// @ 0x00bad810
void cStarManager::Reset()
{
    for (int32_t i = 0; i < (int32_t)(mppBannersEnd - mppBanners); ++i)
        mppBanners[i]->mpOwner->Slot10();

    for (int32_t i = 0; i < (int32_t)(mppAgentsEnd - mppAgents); ++i) {
        cStarAgentRecord* pAgent = mppAgents[i];
        pAgent->mbActive = false;
        if (pAgent->mpEffect != nullptr) {
            FUN_00c86e50();
            if (pAgent->mpEffect != nullptr) {
                IRefCounted* pOld = pAgent->mpEffect;
                pAgent->mpEffect = nullptr;
                pOld->Release2();
            }
        }
    }

    if (mpCurrentItem != nullptr) {
        IRefCounted* pOld = mpCurrentItem;
        mpCurrentItem = nullptr;
        pOld->Release();
    }

    mppAgentsEnd += EraseAllPointers(mppAgents, mppAgentsEnd, mppAgentsEnd);
}

// @ 0x00bad8d0
void cStarManager::Shutdown()
{
    IRefCounted* pOld = gspBackgroundSimManager->mpIdleState;
    if (pOld != nullptr) {
        gspBackgroundSimManager->mpIdleState = nullptr;
        pOld->Release();
    }

    mppAgentsEnd += EraseAllPointers(mppAgents, mppAgentsEnd, mppAgentsEnd);

    NounManager()->RemoveNounsOfType(0x18eb9d2);
    gCheatStarCount = 0;
}

// @ 0x00bad940
void cStarManager::LoadFromObject(void* pObject)
{
    uint32_t nHandle = *(uint32_t*)((uint8_t*)pObject + 0x7c);
    cStarAgentRecord* pAgent;
    if (nHandle == 0) {
        pAgent = (cStarAgentRecord*)mpPending;
    } else if (nHandle == 0xffffffff) {
        pAgent = nullptr;
    } else {
        uint8_t* pBlock = *(uint8_t**)(mpHandleTable + (nHandle >> 12) * 0x14);
        pAgent = *(cStarAgentRecord**)(pBlock + (nHandle & 0xfff) * 4);
    }

    WString* pName = (WString*)((uint8_t*)pObject + 0x10);
    if (pName != &pAgent->mName)
        pAgent->mName.Assign(pName->mpBegin, pName->mpEnd);

    void* pConfig = *(void**)((uint8_t*)pObject + 0x48);
    if (pConfig != nullptr) {
        FUN_00bb9b90((uint8_t*)pConfig + 0x504);
        FUN_004df3e0(ChildGetSomething((uint32_t)(size_t)pConfig));
    }

    FUN_00bb9ad0(*(int32_t*)((uint8_t*)pObject + 0xa4));
    FUN_00bb9b00(2, 0);
    uint8_t* pSlot = (uint8_t*)FUN_00bbaa60(0);
    *(int32_t*)(pSlot + 0x194) = *(int32_t*)((uint8_t*)pObject + 0xa4);

    IRefCounted** ppThreats = mppThreats;
    IRefCounted** ppThreatsEnd = mppThreatsEnd;
    IRefCounted* pExisting = (IRefCounted*)pAgent;
    if (ppThreats != ppThreatsEnd) {
        while (*ppThreats != pExisting) {
            ++ppThreats;
            if (ppThreats == ppThreatsEnd)
                break;
        }
        if (ppThreats != ppThreatsEnd) {
            if (ppThreats + 1 < ppThreatsEnd)
                CopyImpl_0(ppThreats + 1, ppThreatsEnd, ppThreats);
            IRefCounted** ppNewEnd = ppThreatsEnd - 1;
            mppThreatsEnd = ppNewEnd;
            if (*ppNewEnd != nullptr)
                (*ppNewEnd)->Release();
        }
    }

    IRefCounted* pOld = mpCurrentItem;
    if (pExisting != pOld) {
        if (pExisting != nullptr)
            pExisting->Slot00();
        mpCurrentItem = pExisting;
        if (pOld != nullptr)
            pOld->Release();
    }

    WString* pWorld = (WString*)pObject;
    if (pWorld != &mWorldName)
        mWorldName.Assign(pWorld->mpBegin, pWorld->mpEnd);

    IGameObject* pSave = SaveLoadManager();
    IGameObject* pStar = *(IGameObject**)((uint8_t*)pSave + 0x188);
    *(float*)((uint8_t*)pStar + 0x58) = *(float*)((uint8_t*)pStar + 0x54);

    pSave = SaveLoadManager();
    pStar = *(IGameObject**)((uint8_t*)pSave + 0x188);
    *(bool*)((uint8_t*)pStar + 0x48) = true;

    pSave = SaveLoadManager();
    pStar = *(IGameObject**)((uint8_t*)pSave + 0x188);
    *(bool*)((uint8_t*)pStar + 0x49) = true;
}

// @ 0x00badae0
void cStarManager::UpdateVisibility(void* pStar, void* pPlanet, float fNear,
                                    float fFar, const Vector3* pOffset)
{
    if ((mnFlags >> 2 & 1) == 0 && mnState != 2)
        return;

    float fOuter;
    float fInner;
    if (pStar != nullptr && pPlanet != nullptr) {
        void* pSystem = cStar_GetSolarSystem(pStar);
        fOuter = cStar_GetOrbitRadius(pSystem, 1, 1);
        fInner = cStar_GetOrbitRadius(pSystem, 2, 1);
        SetVisible(pPlanet, 1);
    } else if (pStar != nullptr && !mbLoaded) {
        IGameObject* pObject = (IGameObject*)AddRefObject(pStar);
        fOuter = cPlanet_GetOrbitRadius(pObject, 1, 1);
        fInner = cPlanet_GetOrbitRadius(pObject, 2, 1);
        float fLength = VectorLength(pOffset != nullptr ? pOffset : &mOffset);
        if (fLength < fOuter) {
            mbVisible = true;
            if (mOffset.x > 0.0f)
                mOffset.x = (float)RandomUint32Uniform(3) * gRandomScale;
            else
                mOffset.x = (float)(int32_t)(mOffset.x * gRandomScale2) * gRandomScale;
        } else if (fLength > fInner) {
            mbVisible = false;
            if (mOffset.x > 0.0f)
                mOffset.x = (float)(int32_t)(mOffset.x * gRandomScale2) * gRandomScale;
            else
                mOffset.x = (float)RandomUint32Uniform(3) * gRandomScale;
        } else if (mnState != 2) {
            return;
        } else {
            mbVisible = gRealOne;
            if (mOffset.x > 0.0f)
                mOffset.x = (float)RandomUint32Uniform(3) * gRandomScale;
            else if (mOffset.x < 0.0f)
                mOffset.x = 0.0f;
            else
                mOffset.x = gRealOne;
        }
        return;
    } else {
        return;
    }

    if (fNear > fOuter) {
        (void)fInner;
    }
}

// @ 0x00badd10
void cStarManager::UpdateItem(void* pItem, void* pConfig)
{
    FUN_00b3d420();
    if (FUN_00b3d420(), *(int32_t*)((uint8_t*)FUN_006b42e0(nullptr) + 0x14) == 0)
        return;

    uint32_t nFlags = mnFlags;
    if ((nFlags & 8) != 0)
        return;
    mnFlags = nFlags | 8;

    uint8_t* pObject = (uint8_t*)pItem;
    void* pSlot = FUN_00ba6d80(FUN_00b8d8f0());
    uint32_t nId = GetItemInstanceID(pSlot);

    if ((nId & 1) != 0) {
        FUN_00ba7bd0(pObject);
        if (pConfig != nullptr)
            FUN_00bab010(pObject, pConfig);
        switch (mnState) {
        case 3:
            pObject[0x0c] = 0;
            pObject[0x10] = 1;
            pObject[0x14] = 4;
            pObject[0x18] = 1;
            break;
        case 4:
            pObject[0x0c] = 0;
            pObject[0x10] = 2;
            pObject[0x14] = 8;
            pObject[0x18] = 4;
            break;
        case 5:
            pObject[0x0c] = 1;
            pObject[0x10] = 8;
            pObject[0x14] = 8;
            pObject[0x18] = 4;
            pObject[0x1c] = 2;
            break;
        }
    } else {
        if (FUN_00b8dab0() < 2) {
            FUN_00bad440(this, pItem, pConfig);
            return;
        }
        FUN_00ba7bd0(pObject);
        if (pConfig != nullptr)
            FUN_00bab010(pObject, pConfig);
        if (FUN_00b8dab0() < 5) {
            pObject[0x0c] = 1;
        } else {
            uint32_t nValue = *(uint32_t*)(pObject + 0x10) & 0xfffffffe;
            if (nValue == 0)
                nValue |= 2;
            *(uint32_t*)(pObject + 0x10) = nValue;
            if (!FUN_00bb9af0(pSlot, 0x100))
                pObject[0x0c] = 1;
        }
    }

    FUN_00bad440(this, pItem, pObject);
    FUN_00ba8220(pObject);
}

// @ 0x00bae000
void WStringVector::Reserve(uint32_t nCount)
{
    if ((uint32_t)(mpEnd - mpBegin) >= nCount)
        return;

    WString* pNew = nullptr;
    if (nCount != 0) {
        pNew = (WString*)operator_new(nCount << 4, "Simulator", 0, 0,
                                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL"
                                      "\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }

    WString* pOldBegin = mpBegin;
    WString* pOldEnd = mpEnd;
    UninitializedCopyStrings(pOldBegin, pOldEnd, pNew);
    UninitializedRelocateCommit(pOldBegin, pOldEnd, pNew);
    if (pOldBegin != nullptr)
        operator_delete(pOldBegin);

    mpEnd = pNew + (pOldEnd - pOldBegin);
    mpCapacity = pNew + nCount;
    mpBegin = pNew;
}

// @ 0x00bae0a0
WStringVector* WStringVector::CopyFrom(const WStringVector* pOther)
{
    VectorBoolGrow((int32_t)(pOther->mpEnd - pOther->mpBegin), (void*)pOther->mAllocator);
    FUN_00829110(mpBegin, pOther->mpBegin, pOther->mpEnd, mpBegin, mAllocator);
    mpEnd = (WString*)pOther->mpEnd;

    *(float*)((uint8_t*)this + 0x14) = *(float*)((uint8_t*)pOther + 0x14);
    *(uint32_t*)((uint8_t*)this + 0x18) = *(uint32_t*)((uint8_t*)pOther + 0x18);

    void* pOtherInner = (void*)((uint8_t*)pOther + 0x1c);
    VectorBoolGrow((int32_t)((*(uint32_t**)((uint8_t*)pOther + 0x20))
                             - (*(uint32_t**)((uint8_t*)pOther + 0x1c))) >> 2,
                   (void*)((uint8_t*)pOther + 0x28));
    uint8_t* pDst = *(uint8_t**)((uint8_t*)this + 0x1c);
    uint8_t* pSrc = *(uint8_t**)((uint8_t*)pOther + 0x1c);
    size_t nBytes = (size_t)(*(uint8_t**)((uint8_t*)pOther + 0x20) - pSrc);
    memcpy(pDst, pSrc, nBytes);
    *(uint8_t**)((uint8_t*)this + 0x20) = pDst + nBytes;
    (void)pOtherInner;
    return this;
}

// @ 0x00bae130
void cStarManager::Cheat(void* pArguments)
{
    int32_t nCount = 0;
    if (OptionArguments(pArguments, gCheatFlush, &nCount, 0, 0) != nullptr) {
        FUN_00b3d420();
        FUN_00bac3a0();
    }
    if (OptionArguments(pArguments, gCheatHistory, &nCount, 0, 0) != nullptr)
        FUN_00b3d420();

    int32_t* pArgs = OptionArguments(pArguments, gCheatStar, &nCount, 1, 1);
    if (pArgs != nullptr) {
        const char* pName = (const char*)*pArgs;
        if (DoFindNode(gCheatCurrent, pName)) {
            cSPLivingUniverse_GetPlayerEmpire();
            FUN_00c30c60();
        }
        if (DoFindNode(gCheatEmpires, pName))
            FUN_01021230();
        if (DoFindNode(gCheatStarsName, pName))
            FUN_00b3d420();
        if (DoFindNode(gCheatEmpires, pName))
            ((IGameObject*)CheatManager())->Slot20();
    }

    if (OptionArguments(pArguments, gCheatStar, &nCount, 0, 0x7fffffff) != nullptr) {
        char* pScript = (char*)operator_new(0x18, "Simulator", 0, 0,
                                            "c:\\BuildAgent\\max-spore001-spore\\CMBuild"
                                            "\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include"
                                            "\\EASTL/allocator.h", 0xd1);
        strcpy(pScript, "tester -run TestScript ");
        void* pCommand = cConcat(nullptr, pScript, " -ea_asserts");
        ((IGameObject*)CheatManager())->Slot20();
        operator_delete(pCommand);
        operator_delete(pScript);
    }
}

// @ 0x00bae490
cStarManager::cStarManager()
{
    mpListSelf = this + 1;
    mnState = 0;
    mnFlags = 0;
    mbLoaded = 0;
    mpPending = 0;
    mppBanners = 0;
    mppBannersEnd = 0;
    mOffset.x = 0.0f;
    mOffset.y = 0.0f;
    mOffset.z = 0.0f;
    mppAgents = 0;
    mppAgentsEnd = 0;
    mbVisible = 0;
    mWorldName.mpBegin = gEmptyString16;
    mWorldName.mpEnd = gEmptyString16;
    mWorldName.mpCapacity = gEmptyString16 + 1;
    mppThreats = 0;
    mppThreatsEnd = 0;
    mpHandleTable = 0;
    mFeedback.mTree.mPad00[0] = 0;
    mFeedback.mTree.mpAnchor = (FeedbackNode*)&mFeedback.mTree.mpAnchor;
    mFeedback.mTree.mpRoot = 0;
    mFeedback.mTree.mnSize = 0;
    mpCurrentItem = 0;
    mnItemCount = 0;
}
