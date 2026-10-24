// SporeApp.exe slice s00b2a8d0 -- ability / distribution record containers (gold6, worker 36)

#include "types.h"
#include <new>

// ---------------------------------------------------------------------------
// shared elements
// ---------------------------------------------------------------------------

// Object held by an AutoRef slot.
struct IRefCounted {
    virtual void     AddRef();                              // +0x00
    virtual uint32_t Release();                             // +0x04
};

// One owning slot (4 bytes).
struct AutoRef {
    IRefCounted* mpObject;                                  // +0x00

    AutoRef() : mpObject(0) {}

    AutoRef(const AutoRef& src) : mpObject(src.mpObject)
    {
        if (mpObject)
            mpObject->AddRef();
    }

    ~AutoRef()
    {
        if (mpObject)
            mpObject->Release();
    }

    void Clear()
    {
        if (mpObject) {
            IRefCounted* pOld = mpObject;
            mpObject = 0;
            pOld->Release();
        }
    }

    void AssignObject(IRefCounted* pNew)
    {
        IRefCounted* pOld = mpObject;
        if (pNew != pOld) {
            if (pNew)
                pNew->AddRef();
            mpObject = pNew;
            if (pOld)
                pOld->Release();
        }
    }

    void Assign(const AutoRef& src)
    {
        AssignObject(src.mpObject);
    }
};

// 0x18-byte record: id, value pair and an owning pointer.
struct cAbilityRecord {
    int32_t mId;                                            // +0x00
    int32_t mPad04;                                         // +0x04
    int32_t m08;                                            // +0x08
    int32_t m0c;                                            // +0x0c
    AutoRef mRef;                                           // +0x10
    int32_t mPad14;                                         // +0x14

    cAbilityRecord() {}

    cAbilityRecord(const cAbilityRecord& src);

    cAbilityRecord& operator=(const cAbilityRecord& src)
    {
        mId = src.mId;
        mRef.Assign(src.mRef);
        m08 = src.m08;
        m0c = src.m0c;
        return *this;
    }

    void Reset()
    {
        mId = -1;
        m08 = 0;
        m0c = 0;
        mRef.Clear();
        if (mRef.mpObject)
            mRef.mpObject->Release();
    }
};

// 0x24-byte polymorphic distribution tile.
struct cDistributeTile {
    virtual void v00();                                     // +0x00
    int32_t m04;                                            // +0x04
    int32_t m08;                                            // +0x08
    int32_t m0c;                                            // +0x0c
    float   m10;                                            // +0x10
    float   m14;                                            // +0x14
    float   m18;                                            // +0x18
    int32_t m1c;                                            // +0x1c
    int32_t m20;                                            // +0x20

    cDistributeTile(const cDistributeTile& src)
        : m20(0)
    {
        m04 = src.m04;
        m08 = src.m08;
        m0c = src.m0c;
        m10 = src.m10;
        m14 = src.m14;
        m18 = src.m18;
        m1c = src.m1c;
        m20 = src.m20;
    }
};

// Position source embedded at +0x34 of an ability; GetPosition sits in vtable
// slot 0x2c.
struct cPosition {
    virtual void   v00();
    virtual void   v04();
    virtual void   v08();
    virtual void   v0c();
    virtual void   v10();
    virtual void   v14();
    virtual void   v18();
    virtual void   v1c();
    virtual void   v20();
    virtual void   v24();
    virtual void   v28();
    virtual float* GetPosition();                           // +0x2c
};

struct cAbility {
    char        mPad00[0x34];                               // +0x00 .. +0x33
    cPosition   mPosition;                                  // +0x34
};

// Object owning a set of noun slots. The noun array is guarded by a two-word
// mark bitmap.
struct cAbilityObject {
    virtual void v00();                                     // +0x00
    virtual void v04();
    virtual void v08();
    virtual void* v0c();
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
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7c();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void* v94(void* pArg);                          // +0x94

    char     mPad04[0x130];                                 // +0x04 .. +0x133
    uint32_t m134;                                          // +0x134
    uint32_t m138;                                          // +0x138
    uint32_t m13c;                                          // +0x13c
    uint32_t m140;                                          // +0x140
};

// Noun slot list: mark bitmap, count, item array.
struct cNounList {
    uint32_t mMarks[2];                                     // +0x00
    uint32_t mnCount;                                       // +0x08
    void**   mpNouns;                                       // +0x0c

    void RemoveNouns(bool bOnlyUnmarked);                   // 0x00b2b090
};

// ---------------------------------------------------------------------------
// external engine entry points
// ---------------------------------------------------------------------------
// 8-byte iterator handle passed by value.
struct cIterator {
    int32_t mIndex;                                         // +0x00
    void*   mpNode;                                         // +0x04
};

void* __cdecl InsertRangeImpl(void* pDest, cIterator pos, void* pFirst, void* pLast);  // 0x00b2a880
void __cdecl ForwardEvent(void* a, void* b, void* c, void* d, void* pChannel);   // 0x005939d0
void* __fastcall NounManager();                             // 0x00b3d300
void* __fastcall CreateNoun(void* pMgr);                    // 0x00b3d3b0
void __fastcall RemoveNoun(void* pMgr, void* pNoun);        // 0x00b225d0
void* __fastcall BeginObstacleQuery();                      // 0x00b3d3b0
void* __cdecl ObstacleIdKey(int32_t id, int32_t unused, int32_t extra);   // 0x00b3d3c0
void* __fastcall ObstacleManager_FindById(void* pMgr);      // 0x00b74e90
void __fastcall Obstacle_SetState(void* pObstacle, int32_t state);  // 0x00b73de0
void __fastcall Obstacle_SetFlag(void* pObstacle, int32_t flag);    // 0x00b725e0

struct cEventChannel {
    void Send(void* a, void* b, void* c, void* d);          // 0x00b2b6a0
};

// ---------------------------------------------------------------------------
// container algorithms
// ---------------------------------------------------------------------------

// @ 0x00b2a8d0
void __stdcall ConstructFill(cAbilityRecord* pBegin, cAbilityRecord* pEnd)
{
    for (; pBegin < pEnd; ++pBegin) {
        pBegin->Reset();
    }
}

// @ 0x00b2a920
void HeapInsertRange(AutoRef* pBegin, AutoRef* pEnd, float x, float y, float z)
{
    for (AutoRef* pItem = pBegin + 1; pItem != pEnd; ++pItem) {
        IRefCounted* pObj = pItem->mpObject;
        if (pObj)
            pObj->AddRef();
        AutoRef* pHole = pItem;
        for (; pHole != pBegin; --pHole) {
            float* pParentPos = ((cAbility*)pHole[-1].mpObject)->mPosition.GetPosition();
            float* pObjPos = ((cAbility*)pObj)->mPosition.GetPosition();
            float dParent = (y - pParentPos[1]) * (y - pParentPos[1])
                          + (x - pParentPos[0]) * (x - pParentPos[0])
                          + (z - pParentPos[2]) * (z - pParentPos[2]);
            float dObj = (y - pObjPos[1]) * (y - pObjPos[1])
                       + (x - pObjPos[0]) * (x - pObjPos[0])
                       + (z - pObjPos[2]) * (z - pObjPos[2]);
            if (dParent <= dObj)
                break;
            pHole->Assign(pHole[-1]);
        }
        pHole->AssignObject(pObj);
        if (pObj)
            pObj->Release();
    }
}

// @ 0x00b2aab0
void HeapPushRange(AutoRef* pBegin, AutoRef* pEnd, float x, float y, float z)
{
    for (AutoRef* pItem = pBegin; pItem != pEnd; ++pItem) {
        IRefCounted* pObj = pItem->mpObject;
        if (pObj)
            pObj->AddRef();
        AutoRef* pHole = pItem;
        for (; pHole != pBegin; --pHole) {
            float* pParentPos = ((cAbility*)pHole[-1].mpObject)->mPosition.GetPosition();
            float* pObjPos = ((cAbility*)pObj)->mPosition.GetPosition();
            float dParent = (y - pParentPos[1]) * (y - pParentPos[1])
                          + (x - pParentPos[0]) * (x - pParentPos[0])
                          + (z - pParentPos[2]) * (z - pParentPos[2]);
            float dObj = (y - pObjPos[1]) * (y - pObjPos[1])
                       + (x - pObjPos[0]) * (x - pObjPos[0])
                       + (z - pObjPos[2]) * (z - pObjPos[2]);
            if (dParent <= dObj)
                break;
            pHole->Assign(pHole[-1]);
        }
        pHole->AssignObject(pObj);
        if (pObj)
            pObj->Release();
    }
}

// @ 0x00b2ac90
void CopyAddRef(void** pDest, uint32_t count, void** pSrc)
{
    while (count > 0) {
        if (pDest) {
            IRefCounted* pObj = (IRefCounted*)*pSrc;
            *pDest = pObj;
            if (pObj)
                pObj->AddRef();
        }
        --count;
        ++pDest;
    }
}

// @ 0x00b2acd0
cAbilityRecord* AssignFill(cAbilityRecord* pBegin, cAbilityRecord* pEnd, cAbilityRecord* pOut)
{
    if (pBegin == pEnd)
        return pOut;
    do {
        pBegin->Reset();
        ++pBegin;
        ++pOut;
    } while (pBegin != pEnd);
    return pOut;
}

// @ 0x00b2ad40
cDistributeTile* ConstructTiles(const cDistributeTile* pSrcBegin, const cDistributeTile* pSrcEnd,
                                cDistributeTile* pDest)
{
    for (; pSrcBegin != pSrcEnd; ++pSrcBegin) {
        if (pDest)
            new (pDest) cDistributeTile(*pSrcBegin);
        ++pDest;
    }
    return pDest;
}

// @ 0x00b2ada0
void HeapInsertAt(AutoRef* ppItems, int32_t index, int32_t count, IRefCounted* pObj,
                  float x, float y, float z)
{
    while (index < count) {
        IRefCounted* pParent = ppItems[(index - 1) >> 1].mpObject;
        float* pParentPos = ((cAbility*)pParent)->mPosition.GetPosition();
        float* pObjPos = ((cAbility*)pObj)->mPosition.GetPosition();
        float dParent = (y - pParentPos[1]) * (y - pParentPos[1])
                      + (x - pParentPos[0]) * (x - pParentPos[0])
                      + (z - pParentPos[2]) * (z - pParentPos[2]);
        float dObj = (y - pObjPos[1]) * (y - pObjPos[1])
                   + (x - pObjPos[0]) * (x - pObjPos[0])
                   + (z - pObjPos[2]) * (z - pObjPos[2]);
        if (dParent <= dObj)
            break;
        ppItems[count].Assign(ppItems[index]);
        count = index;
    }
    ppItems[count].AssignObject(pObj);
    if (pObj)
        pObj->Release();
}

// @ 0x00b2af00
void SwapRefs(AutoRef* pA, AutoRef* pB)
{
    AutoRef tmp(*pA);
    pA->Assign(*pB);
    pB->Assign(tmp);
}

// @ 0x00b2af80
void* InsertRange(void* pDest, void* pIter, void* pFirst, void* pLast)
{
    InsertRangeImpl(pDest, *(cIterator*)((char*)pIter + 4), pFirst, pLast);
    return pDest;
}

// @ 0x00b2afb0
void DestroyAbilityObject(char* pThis)
{
    char* pSlot = pThis + 0x250;
    for (int32_t i = 8; i >= 0; --i) {
        pSlot -= 0x40;
        IRefCounted* pObj = *(IRefCounted**)pSlot;
        if (pObj)
            pObj->Release();
    }
}

// @ 0x00b2aff0
cAbilityRecord::cAbilityRecord(const cAbilityRecord& src)
{
    mId = src.mId;
    m08 = src.m08;
    m0c = src.m0c;
    mRef.Assign(src.mRef);
}

// @ 0x00b2b040
cAbilityRecord* AssignRecord(cAbilityRecord* pDest, const cAbilityRecord* pSrc)
{
    *pDest = *pSrc;
    return pDest;
}

// @ 0x00b2b090
void cNounList::RemoveNouns(bool bOnlyUnmarked)
{
    for (uint32_t i = 0; i < mnCount; ++i) {
        void* pNoun = mpNouns[i];
        if (!pNoun)
            continue;
        if (!bOnlyUnmarked && (mMarks[i >> 5] & (1u << (i & 0x1f))) != 0)
            continue;
        BeginObstacleQuery();
        cAbilityObject* pBody = (cAbilityObject*)pNoun;
        void* pObstacle = ObstacleManager_FindById(ObstacleIdKey((int32_t)pBody->m13c, 0,
                                                                (int32_t)pBody->m140));
        (void)pObstacle;
        RemoveNoun(NounManager(), pNoun);
        IRefCounted* pObj = (IRefCounted*)mpNouns[i];
        if (pObj) {
            mpNouns[i] = 0;
            pObj->Release();
        }
    }
}

// ---------------------------------------------------------------------------
// terrain distribution info
// ---------------------------------------------------------------------------

struct cTypeInfo {
    AutoRef  mProps;                                        // +0x00
    float    mMinEmitMap;                                   // +0x04
    float    mMaxEmitMap;                                   // +0x08
    float    mSpriteScale;                                  // +0x0c
    int32_t  mResourceIDs[11];                              // +0x10 .. +0x38

    cTypeInfo& operator=(const cTypeInfo& src);             // 0x00b2b150
};

// @ 0x00b2b150
cTypeInfo& cTypeInfo::operator=(const cTypeInfo& src)
{
    mProps.Assign(src.mProps);
    mMinEmitMap = src.mMinEmitMap;
    mMaxEmitMap = src.mMaxEmitMap;
    mSpriteScale = src.mSpriteScale;
    mResourceIDs[0] = src.mResourceIDs[0];
    mResourceIDs[1] = src.mResourceIDs[1];
    mResourceIDs[2] = src.mResourceIDs[2];
    mResourceIDs[3] = src.mResourceIDs[3];
    mResourceIDs[4] = src.mResourceIDs[4];
    mResourceIDs[5] = src.mResourceIDs[5];
    mResourceIDs[6] = src.mResourceIDs[6];
    mResourceIDs[7] = src.mResourceIDs[7];
    mResourceIDs[8] = src.mResourceIDs[8];
    mResourceIDs[9] = src.mResourceIDs[9];
    mResourceIDs[10] = src.mResourceIDs[10];
    return *this;
}

// ---------------------------------------------------------------------------
// distribute tables
// ---------------------------------------------------------------------------
struct cDistributeTable {
    uint32_t mPad00[17];                                    // +0x00 .. +0x43
    uint32_t mEntries[27][7];                               // +0x44 (27 x 0x1c)

    uint32_t* FindEntry(uint32_t id);                       // 0x00b2b1e0
    void* CreateNounFor(uint32_t index, void* pInfo);       // 0x00b2b2d0
};

// @ 0x00b2b1e0
uint32_t* cDistributeTable::FindEntry(uint32_t id)
{
    for (int32_t outer = 0; outer < 3; ++outer) {
        for (int32_t inner = 0; inner < 9; ++inner) {
            uint32_t* pRow = mEntries[outer * 9 + inner];
            if (pRow[3] == id || pRow[4] == id || pRow[5] == id || pRow[6] == id)
                return pRow;
        }
    }
    return 0;
}

// @ 0x00b2b2d0
void* cDistributeTable::CreateNounFor(uint32_t index, void* pInfo)
{
    cAbilityObject* pNoun = (cAbilityObject*)CreateNoun(NounManager());
    if (!pNoun)
        return 0;
    cAbilityObject* pBody = (cAbilityObject*)pNoun->v0c();
    if (pBody && index) {
        pBody->v94(pInfo);
    }
    return pBody;
}

// @ 0x00b2b430
void* CreateDistributeNoun(void* unused1, void* unused2, void* pTable, void* pInfo, void* pExtra)
{
    cAbilityObject* pNoun = (cAbilityObject*)CreateNoun(NounManager());
    if (!pNoun)
        return 0;
    cAbilityObject* pBody = (cAbilityObject*)pNoun->v0c();
    if (!pBody)
        return 0;
    pBody->v94(pExtra);
    pBody->v94(pTable);
    return pBody;
}

// ---------------------------------------------------------------------------
// feedback-event set (eastl rbtree of uint32 -> owning event pointer)
// ---------------------------------------------------------------------------
struct cRbNode {
    cRbNode* mpParent;                                      // +0x00
    cRbNode* mpRight;                                       // +0x04
    cRbNode* mpLeft;                                        // +0x08
    uint32_t mColor;                                        // +0x0c
};

struct cEventNode : cRbNode {
    uint32_t mKey;                                          // +0x10
    uint32_t mValue;                                        // +0x14
    void*    mpEvent;                                       // +0x18
    char     mPad1c[4];                                     // +0x1c
};

struct cEventTree {
    uint32_t  mPad00;                                       // +0x00
    cRbNode   mHeader;                                      // +0x04 .. +0x13
    uint32_t  mnCount;                                      // +0x14

    bool EraseKey(const uint32_t* pKey);                    // 0x00b2b5b0
    void* Insert(const uint32_t* pKey);                     // 0x00b2b6d0
    void  InsertAt(cEventNode** ppOut, cRbNode* pParent, const uint32_t* pKey, bool bHint);  // 0x00b2b720
};

void __fastcall TreeFind(cEventTree* pTree, void** ppOut, const uint32_t* pKey);   // 0x00e5c780
void* __fastcall RBTreeIncrement(cRbNode* pNode);           // 0x00921580
void __cdecl RBTreeErase(cRbNode* pNode, cRbNode* pHeader);  // 0x00921880
void __cdecl operator_delete_array(void* p);                // 0x00f47380

// @ 0x00b2b5b0
bool cEventTree::EraseKey(const uint32_t* pKey)
{
    void* pFound;
    TreeFind(this, &pFound, pKey);
    if (pFound == (void*)&mHeader)
        return false;
    --mnCount;
    RBTreeIncrement((cRbNode*)pFound);
    RBTreeErase((cRbNode*)pFound, &mHeader);
    operator_delete_array(pFound);
    return true;
}

// ---------------------------------------------------------------------------
// small hash table used by the distribute manager
// ---------------------------------------------------------------------------
struct cPair {
    uint32_t mKey;                                          // +0x00
    uint32_t mValue;                                        // +0x04
    cPair*   mpNext;                                        // +0x08
    char     mPad0c[8];                                     // +0x0c
};

struct cPairTable {
    uint32_t  mPad00;                                       // +0x00
    uint32_t* mpBuckets;                                    // +0x04
    uint32_t  mnBuckets;                                    // +0x08

    void Find(cPair** ppResult, const uint32_t* pKey);      // 0x00b2b600
};

// @ 0x00b2b600
void cPairTable::Find(cPair** ppResult, const uint32_t* pKey)
{
    cPair* pNode = (cPair*)mpBuckets[pKey[0] % mnBuckets];
    while (pNode) {
        if (pNode->mKey == pKey[0]) {
            ppResult[0] = pNode;
            return;
        }
        pNode = pNode->mpNext;
    }
    ppResult[0] = 0;
}

// @ 0x00b2b6a0
void __fastcall SendEvent(void* pChannel, void* a, void* b, void* c, void* d)
{
    ForwardEvent(a, b, c, d, pChannel);
}

// @ 0x00b2b6d0
void* cEventTree::Insert(const uint32_t* pKey)
{
    cEventNode* pNode = (cEventNode*)mHeader.mpParent;
    while (pNode) {
        if (pNode->mValue < pKey[1] || (pNode->mValue <= pKey[1] && pNode->mKey <= pKey[0]))
            pNode = (cEventNode*)pNode->mpParent;
        else
            pNode = (cEventNode*)pNode->mpLeft;
    }
    return (void*)pNode;
}

// @ 0x00b2b720
void cEventTree::InsertAt(cEventNode** ppOut, cRbNode* pParent, const uint32_t* pKey, bool bHint)
{
    (void)bHint;
    (void)pParent;
    (void)pKey;
    *ppOut = 0;
}

// @ 0x00b2b7c0
cAbilityRecord* CopyConstructRange(const cAbilityRecord* pSrcBegin, const cAbilityRecord* pSrcEnd,
                                   cAbilityRecord* pDest)
{
    for (; pSrcBegin != pSrcEnd; ++pSrcBegin) {
        if (pDest)
            new (pDest) cAbilityRecord(*pSrcBegin);
        ++pDest;
    }
    return pDest;
}

// @ 0x00b2b830
cAbilityRecord* AssignRange(cAbilityRecord* pSrcBegin, cAbilityRecord* pSrcEnd,
                            cAbilityRecord* pDest)
{
    for (; pSrcBegin != pSrcEnd; ++pSrcBegin) {
        *pDest = *pSrcBegin;
        ++pDest;
    }
    return pDest;
}
