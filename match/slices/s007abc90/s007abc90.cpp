// Slice s007abc90 — SP::cTextureManager construction, texture-instance creation and
// the hash_map::operator[] accessor (0x7abc90..0x7acae0).
// Optimized region: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

namespace EA { namespace Thread {
class Mutex {
public:
    Mutex(const void* pParams, bool bDefault);   // 0x009222a0
    ~Mutex();
    bool Lock(void* pAttribute);
    void Unlock();
private:
    char mData[0x30];
};
}}

struct ResourceKey {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};

struct ResManMgr {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(void* key, int a, int b, int c, int d, int e); // slot 3 (+0xc)
};
extern "C" ResManMgr* ResManager();                    // 0x0067dcd0

class cJob;
class cTextureInstanceInternal;

struct HashIterator {
    void*  mpNode;
    void** mpBucket;
};

struct TextureNode;
struct TextureValue {
    ResourceKey first;   // +0x00
    void*       second;  // +0x0c
    TextureValue(const ResourceKey& k, void* v) : first(k), second(v) {}
};
struct TextureNode {
    ResourceKey  first;   // +0x00
    void*        second;  // +0x0c
    TextureNode* next;    // +0x10
};
struct InsertResult {
    HashIterator it;
    bool         second;
};
struct true_type {};

extern char g_mutexAttribute;   // 0x0140fa10
extern void* g_emptyBucketArray; // 0x0154df28

void* __cdecl TextureAlloc(unsigned int n, const char* pName, int flags, int align, const char* pFile, int line);

extern "C" char SP_SetCachingType(int type, void* p);        // 0x006ac040
extern "C" void AdjustKey(void* pKey, void* pObj);           // 0x006acfe0
extern "C" void StallUntilLoadedFn(void** pOut, int* a, int* b, void* c); // 0x007a98b0
struct cTextureAsyncInfo;
struct AsyncDeque;

class TextureInstanceMap {
public:
    struct RehashPolicy {
        float    mfMaxLoadFactor;
        float    mfGrowthFactor;
        uint32_t mnNextResize;
    };
    HashIterator  find(const ResourceKey& key);                        // 0x00833840
    InsertResult  DoInsertValue(const TextureValue& value, true_type); // 0x007ab0d0
    void*&        operator[](const ResourceKey& key);                  // 0x007ac080
    void          DoFreeNodes(void*, uint32_t);
    TextureInstanceMap() {
        mRehashPolicy.mfMaxLoadFactor = 1.0f;
        mRehashPolicy.mfGrowthFactor = 2.0f;
        mnBucketCount = 1;
        mpBucketArray = (TextureNode**)&g_emptyBucketArray;
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
    ~TextureInstanceMap();

    char            mEmpty[4];     // +0x00
    TextureNode**   mpBucketArray; // +0x04
    uint32_t        mnBucketCount; // +0x08
    uint32_t        mnElementCount;// +0x0c
    RehashPolicy    mRehashPolicy; // +0x10
    char            mRest[4];      // +0x1c
};

void cLoadQueueInit();   // placeholder callee so the stub is not provably nothrow

struct CQEntry {           // 0x10-byte queue entry (element ctor 0x007aa620 / dtor 0x007aa660)
    int a, b, c, d;
    CQEntry();
    ~CQEntry();
};

struct CQState {           // POD queue state at +0x44
    int  mData[10];        // +0x00..+0x27
    void Init(int);        // 0x007a9c10
};

class cLoadQueue {
public:
    __declspec(noinline) cLoadQueue();              // 0x007ac0f0
    void Schedule(void* pEntry);                    // 0x007abae0
    void*           mpManager;    // +0x00
    CQEntry         mEntries[4];  // +0x04 .. +0x43
    CQState         mQueue;       // +0x44 .. +0x6b
    char            mPad6c[4];    // +0x6c
    int             mField70;     // +0x70
};

// Base at +0x00 (vptr only) and base at +0x04 (vptr + refcount); both have destructors.
class cTmBaseA {
public:
    virtual ~cTmBaseA();
};
class cTmBaseB {
public:
    cTmBaseB() : mRefCount(0) {}
    virtual ~cTmBaseB();
    int mRefCount;
};
struct cTmDtorMember {   // 4-byte members with destructors at +0x18 and +0x1c
    int v;
    cTmDtorMember() : v(0) {}
    ~cTmDtorMember();
};
struct cTmListHead {     // intrusive list head at +0x50
    cTmListHead* mpNext;
    cTmListHead* mpPrev;
    cTmListHead() { mpPrev = this; mpNext = this; }
    ~cTmListHead();
};

// ---- texture instance internal node (PUBLIC handle is the node at +0x08) ----
class cTIRefCounted {           // object held by the intrusive pointer at +0x24
public:
    virtual void AddRef();      // vtable slot 0
    virtual void Release();     // vtable slot 1
};

class cTextureInstanceInternal {
public:
    cTextureInstanceInternal* mpNext;   // +0x00
    cTextureInstanceInternal* mpPrev;   // +0x04
    void*   mpRaster;                   // +0x08  (public handle)
    char    mField0c;                   // +0x0c
    int     mRefCount;                  // +0x10
    int     mCacheFrames;               // +0x14
    ResourceKey mKey;                   // +0x18
    cTIRefCounted* mpResource;          // +0x24
    uint32_t mUseFlags;                 // +0x28
};

extern "C" void* __fastcall NodeCreate(void* pClassId);   // 0x007aa800

typedef void (__cdecl *RasterNotifyFn)(void* pRaster, int setting);

class cScopedLock {
public:
    EA::Thread::Mutex* mMutex;
    cScopedLock(EA::Thread::Mutex* pMutex)
    { mMutex = pMutex; pMutex->Lock(&g_mutexAttribute); }
    ~cScopedLock();     // out-of-line: SP::MutexLock::~MutexLock (0x00697b70)
};

class cTextureManager : public cTmBaseA, public cTmBaseB {
public:
    cTextureManager();                              // 0x007ac1e0
    virtual ~cTextureManager();
    void Update();                                  // 0x007abc90
    void CleanupJob();                              // 0x007a9620
    bool StallFinishBackgroundLoad(void* pEntry);   // 0x007aafc0
    void* CreateInstance(ResourceKey* key, void* pResource, void* pRaster, uint32_t flags, char b); // 0x007ac2f0
    void* GetTextureSync(ResourceKey key, int flags);   // 0x007ac750
    void* GetTextureAsync(ResourceKey key, int flags);  // 0x007ac850
    void* StallUntilLoadedUnderLock(ResourceKey* key);  // 0x007ac8d0
    void* RegisterBuiltInGameTexture(void* p1, uint32_t flags); // 0x007ac600
    void* CreateGameTextureFromSerializer(void* arg0, void* arg1, void* arg2, uint32_t flags); // 0x007aca00
    void* CreateGameTextureRaw(void* arg0, void* arg1, uint32_t key, uint32_t flags);           // 0x007acae0

    bool            mIsInitialized; // +0x0c
    char            mPad0d[3];
    void*           mInvalidRaster; // +0x10
    void*           mLoadingRaster; // +0x14
    cTmDtorMember   mMember18;      // +0x18
    cTmDtorMember   mMember1c;      // +0x1c
    EA::Thread::Mutex mMutex;       // +0x20
    cTmListHead     mList;          // +0x50
    TextureInstanceMap mTextureInstanceMap; // +0x58
    TextureInstanceMap mTextureArenas;      // +0x78
    EA::Thread::Mutex mArenaMutex;  // +0x98
    int             mNumCacheFrames;      // +0xc8
    int             mCurrentMipLodSetting; // +0xcc
    void*           mUnknownD0;     // +0xd0
    cLoadQueue      mLoadQueue;     // +0xd4
    char            mTail[0x14];
};

// ---------------------------------------------------------------------------
// @ 0x007ac080
void*& TextureInstanceMap::operator[](const ResourceKey& key)
{
    HashIterator it = find(key);
    if (it.mpNode == mpBucketArray[mnBucketCount])
        it = DoInsertValue(TextureValue(key, 0), true_type()).it;
    return ((TextureNode*)it.mpNode)->second;
}

// ---- eastl::deque over 4-byte elements, 0x40 per block (0x100-byte blocks) ----
struct DqIterB {                        // 16-byte deque iterator
    int*  cur;
    int*  first;
    int*  last;
    int** node;
    DqIterB* __thiscall plus_assign(int n);                                 // 0x007a9a80
    DqIterB* __thiscall move_backward(DqIterB* first, DqIterB* last, DqIterB* out);        // 0x007ac170
    DqIterB* __thiscall move_forward(DqIterB* tmp, DqIterB* next, DqIterB* e, DqIterB* out); // 0x007abb80
};
struct AsyncDeque {
    char     mPad0[8];
    DqIterB  begin;                     // +0x08
    DqIterB  end;                       // +0x18
    DqIterB  erase(DqIterB pos);        // 0x007ac480
};
extern "C" void __cdecl gfxFree(void* p);                                   // 0x00f47380

struct MtxNode {                        // intrusive list node look-alike at +0x04 of the inst
    int* mpNext;                        // +0x00
    int* mpPrev;                        // +0x04
};

struct cTextureAsyncQueueEntry {
    int  mKey0, mKey1, mKey2;
    int* mpInst;
};
struct cTextureAsyncInfo {
    MtxNode  mList;                     // +0x00 .. +0x07
    void*    mpObject;                  // +0x08
    char     mField0c;
    int      mRefCount;                 // +0x10
    int      mCacheFrames;              // +0x14
    ResourceKey mKey;                   // +0x18
    int*     mpResource;                // +0x24
    uint32_t Setup(ResourceKey* pKey);  // 0x007ab860
};
struct cTextureLoadQueue {
    int* mpManager;                     // +0x00
    cTextureAsyncInfo mSlots[4];        // +0x04
    AsyncDeque mDeque;                  // +0x44
    int mNextSlot;                      // +0x70
    void Update();
    bool StallFinishBackgroundLoad(cTextureAsyncInfo* p);
};

struct DirectoryItem {                  // rw exported object record
    int   mField00;
    int   mPad04;
    int   mpObject;                     // +0x08
};
extern "C" int rwArenaNumExported(void* arena);                          // 0x011e23a0
extern "C" void rwArenaExportedByIndex(void* arena, int index, void* pOut); // 0x011e28e0
extern "C" void __cdecl ehVectorCtor2(void* p, int elemSize, int count, void* ctor, void* dtor); // 0x011e0b85
struct Vec128Ctor { Vec128Ctor(); ~Vec128Ctor(); int mData[2]; };
extern "C" void __cdecl ehVectorDtor2(void* p, int elemSize, int count, void* dtor); // 0x011e0b22
extern "C" void __cdecl Vec128CtorCall();                                // 0x006c0fa0
extern "C" void __cdecl Vec128DtorCall();                                // 0x00c2e4e0

extern int gMipLodSetting;              // 0x0153bce0
extern int gAppProperties;              // 0x015fd918

// ---------------------------------------------------------------------------
// 0x007abc90 -- types & helpers used by cTextureManager::Update
class TiListHead {                      // intrusive list anchor at +0x50
public:
    TiListHead* mpNext;
    TiListHead* mpPrev;
};

// ---- helpers used by Update (all outside the slice) -----------------------
struct AppPropsView {
    int __thiscall GetIntProperty(int id);
    char __thiscall Query(void** pOut, int id);
};
extern AppPropsView* gAppProps;                  // 0x015fd918
struct PropObject {
    int* __thiscall GetInt();                    // 0x0041e990
};
extern "C" void cLoadQueueUpdate(void* pQueue);  // 0x007aba40 (cLoadQueue::Update)
extern "C" void RemoveMatching(void* pDeque, void* pKey); // 0x007a9840
extern "C" void* TextureFindRaw(void* pMap, const ResourceKey* pKey);  // 0x00833840
extern "C" void TextureEraseNode(void* pMap, void* pNode);            // 0x00b4f930
extern "C" void* gFreeListHead;                  // 0x01634f6c

// ---------------------------------------------------------------------------
// @ 0x007abc90
void cTextureManager::Update()
{
    int  nLodBefore;
    char bChanged;
    int  nLeft;

    cScopedLock lock(&mMutex);

    {
        AppPropsView* pProps = gAppProps;
        if (pProps != 0)
        {
            int reqFrames = pProps->GetIntProperty(0x0101de7d);
            if (reqFrames > 0)
                mNumCacheFrames = reqFrames;
        }
    }

    nLodBefore = mCurrentMipLodSetting;
    if (gAppProps != 0)
    {
        void* pProp = 0;
        if (gAppProps->Query(&pProp, 0x02840048) && *(short*)((char*)pProp + 0x12) == 9)
            mCurrentMipLodSetting = *((PropObject*)pProp)->GetInt();
    }
    bChanged = (nLodBefore != mCurrentMipLodSetting);

    cLoadQueueUpdate((char*)this + 0xd4);

    TiListHead** ppAnchor = (TiListHead**)((char*)this + 0xd0);
    TiListHead*  pEnd = (TiListHead*)((char*)this + 0x50);
    if (*ppAnchor == 0 || *ppAnchor == pEnd)
        *ppAnchor = *(TiListHead**)pEnd;

    cTextureAsyncInfo* pCur = bChanged ? *(cTextureAsyncInfo**)pEnd
                                       : (cTextureAsyncInfo*)*ppAnchor;

    nLeft = bChanged ? 0x7fffffff : (int)gMipLodSetting;

    while (pCur != (cTextureAsyncInfo*)pEnd && nLeft != 0)
    {
        cTextureAsyncInfo* pNext = (cTextureAsyncInfo*)pCur->mList.mpNext;
        volatile long* pCounter = (volatile long*)((char*)pCur + 0x10);

        if (_InterlockedExchange(pCounter, 0) == 1)
        {
            if (pCur->mCacheFrames < 1)
            {
                if ((pCur->mField0c & 1) == 0)
                {
                    int* pLocal = (int*)pCur;
                    RemoveMatching((char*)this + 0xd4, &pLocal);
                }
                {
                    ResourceKey k = pCur->mKey;
                    void* pNode = TextureFindRaw(&mTextureInstanceMap, &k);
                    if (pNode != mTextureInstanceMap.mpBucketArray[mTextureInstanceMap.mnBucketCount])
                        TextureEraseNode(&mTextureInstanceMap, pNode);
                }
                *pCur->mList.mpPrev = *pCur->mList.mpNext;
                *(int*)pCur->mList.mpNext = (int)pCur->mList.mpPrev;
                pCur->mList.mpNext = 0;
                pCur->mList.mpPrev = 0;
                CleanupJob();
            }
            else
            {
                pCur->mCacheFrames = pCur->mCacheFrames - 1;
            }
        }
        else if (_InterlockedExchange(pCounter, 0) > 0 && bChanged != 0 &&
                 pCur->mpObject != 0 &&
                 (*(uint32_t*)((char*)pCur->mpObject + 0x28) & 4) == 0)
        {
            void* pRaster = *(void**)((char*)pCur->mpObject + 8);
            if (pRaster != 0 && (*(uint8_t*)((char*)pRaster + 4) & 0x1f) == 8)
                ((void (__thiscall*)(void*, int))(*(void***)pRaster)[0xb])(pRaster, mCurrentMipLodSetting);
        }

        nLeft--;
        pCur = pNext;
    }
    *ppAnchor = (TiListHead*)pCur;

    if (bChanged)
    {
        cScopedLock arenaLock(&mArenaMutex);

        void** pBegin = *(void***)((char*)this + 0x7c);
        int*   pNode  = *(int**)pBegin;
        if (pNode == 0)
        {
            void** pSlot = pBegin + 1;
            while (*pSlot == 0)
                pSlot++;
            pNode = (int*)*pSlot;
        }
        int* pLast = *(int**)(*(int**)((char*)this + 0x7c) + *(int*)((char*)this + 0x80) * 4);
        while (pNode != pLast)
        {
            int* pArenaObj = *(int**)pNode;
            int  nObjects = rwArenaNumExported(*(void**)((char*)pArenaObj + 0x18));
            for (int i = 0; i < nObjects; i++)
            {
                Vec128Ctor v128;
                void* pOut = 0;
                rwArenaExportedByIndex(*(void**)((char*)pArenaObj + 0x18), i, &pOut);
                if (pOut != 0 && ((int*)&v128.mData[0])[0] == 0x20003)
                {
                    void* pObj = *(void**)((char*)pOut + 8);
                    if (pObj != 0)
                        ((void (__thiscall*)(void*, int))(*(void***)pObj)[0xb])(pObj, mCurrentMipLodSetting);
                }
            }
            pNode = (int*)pNode[1];
            while (pNode == 0)
            {
                pBegin++;
                pNode = (int*)*(pBegin - 1);
            }
        }
    }
}

// @ 0x007ac0f0
cLoadQueue::cLoadQueue()
    : mpManager(0), mEntries(), mQueue()
{
    mQueue.Init(0);
    mField70 = 0;
}

// @ 0x007ac1e0
cTextureManager::cTextureManager()
    : mIsInitialized(false), mInvalidRaster(0), mLoadingRaster(0),
      mMutex(0, true), mArenaMutex(0, true),
      mNumCacheFrames(10), mCurrentMipLodSetting(0), mUnknownD0(0)
{
}

// @ 0x007ac2f0
void* cTextureManager::CreateInstance(ResourceKey* key, void* pResource, void* pRaster, uint32_t flags, char b)
{
    cScopedLock lock(&mMutex);

    cTextureInstanceInternal* inst = (cTextureInstanceInternal*)NodeCreate((void*)0x1634f5c);

    inst->mpPrev = (cTextureInstanceInternal*)mList.mpPrev;
    inst->mpNext = (cTextureInstanceInternal*)&mList;
    mList.mpPrev = (cTmListHead*)inst;
    inst->mpPrev->mpNext = inst;

    inst->mKey = *key;
    inst->mKey.mType = 0;

    cTIRefCounted* pOld = inst->mpResource;
    if ((cTIRefCounted*)pResource != pOld)
    {
        if (pResource != 0)
            ((cTIRefCounted*)pResource)->AddRef();
        inst->mpResource = (cTIRefCounted*)pResource;
        if (pOld != 0)
            pOld->Release();
    }

    inst->mUseFlags = flags;
    inst->mpRaster = pRaster;
    inst->mField0c = b;

    if ((flags & 4) == 0)
    {
        if ((*(uint32_t*)((char*)pRaster + 4) & 0x1f) == 8)
        {
            if (*(void**)((char*)this + 0xcc) != 0)
            {
                void* r = *(void**)((char*)pRaster + 8);
                void** vt = *(void***)r;
                ((RasterNotifyFn)vt[0xb])(r, mCurrentMipLodSetting);
            }
        }
    }
    _InterlockedExchange((volatile long*)&inst->mRefCount, 1);
    inst->mCacheFrames = mNumCacheFrames;

    mTextureInstanceMap[inst->mKey] = inst;

    return (char*)inst + 8;
}

// @ 0x007ac480
DqIterB AsyncDeque::erase(DqIterB pos)
{
    DqIterB result;                     // NRVO candidate: the caller's return slot
    DqIterB next = pos;
    next.cur = pos.cur + 1;
    if (next.cur == pos.last)
    {
        next.node  = pos.node + 1;
        next.first = *next.node;
        next.last  = next.first + 0x40;
        next.cur   = next.first;
    }

    int n = (int)(pos.node - begin.node) * 0x40
          + (int)(begin.last - begin.cur)
          + (int)(pos.cur - pos.first)
          - 0x40;

    int size = ((int)(end.node - begin.node) - 1) * 0x40
             + (int)(end.cur - end.first)
             + (int)(begin.last - begin.cur);

    if (n < (size >> 1))
    {
        next.move_backward(&begin, &pos, &result);
        if (begin.cur + 1 == begin.last)
        {
            if (begin.first != 0)
                gfxFree(begin.first);
            begin.node  = begin.node + 1;
            begin.first = *begin.node;
            begin.last  = begin.first + 0x40;
            begin.cur   = begin.first;
        }
        else
        {
            begin.cur = begin.cur + 1;
        }
    }
    else
    {
        pos.move_forward(&next, &next, &end, &result);
        if (end.cur == end.first)
        {
            if (end.first != 0)
                gfxFree(end.first);
            end.node  = end.node - 1;
            end.first = *end.node;
            end.last  = end.first + 0x40;
            end.cur   = end.last - 1;
        }
        else
        {
            end.cur = end.cur - 1;
        }
    }

    DqIterB t = begin;
    DqIterB* r = t.plus_assign(n);
    result = *r;
    return result;
}

// @ 0x007ac600
void* cTextureManager::RegisterBuiltInGameTexture(void* p1, uint32_t flags)
{
    int* obj = (int*)p1;

    if ((flags & 8) == 0)
        SP_SetCachingType(2, obj);

    ResourceKey key;
    key.mInstance = obj[2];
    key.mType     = obj[3];
    key.mGroup    = obj[4];
    AdjustKey(&key, obj);                       // 0x006acfe0

    cScopedLock lock(&mMutex);

    HashIterator it = mTextureInstanceMap.find(key);
    if (it.mpNode != mTextureInstanceMap.mpBucketArray[mTextureInstanceMap.mnBucketCount])
    {
        int* inst = (int*)((char*)it.mpNode + 0xc);
        void* handle = inst;
        if ((*(uint8_t*)((char*)inst + 0xc) & 1) == 0)
            RemoveMatching(&mLoadQueue, &handle);

        int* pOld = *(int**)((char*)inst + 0x24);
        if (obj != pOld)
        {
            (*(void (__thiscall**)(int*))*(int*)obj)(obj);
            *(int**)((char*)inst + 0x24) = obj;
            if (pOld != 0)
                (*(void (__thiscall**)(int*))(*(int*)pOld + 4))(pOld);
        }
        *(int*)((char*)inst + 8) = obj[6];
        *(uint8_t*)((char*)inst + 0xc) = 9;
        return (char*)inst + 8;
    }

    return CreateInstance(&key, obj, (void*)obj[6], flags, (char)9);
}

// @ 0x007ac750
void* cTextureManager::GetTextureSync(ResourceKey key, int flags)
{
    void* inst = 0;
    ResManMgr* mgr = (ResManMgr*)ResManager();
    key.mType = 0x2f4e681c;

    void* pRaster = 0;
    if (mgr->GetResource(&key, (int)&inst, 0, 0, 0, 0))
    {
        pRaster = *(void**)((char*)inst + 0x18);
        if ((flags & 8) == 0)
            SP_SetCachingType(5, inst);
    }
    else
    {
        int* pProps = (int*)gAppProperties;
        if (pProps != 0 && *(int*)(*(int*)((char*)pProps + 0x3c) + 0x94) != 0)
            pRaster = mInvalidRaster;
    }

    void* res = 0;
    if (pRaster != 0)
        res = CreateInstance(&key, inst, pRaster, (uint32_t)flags, (char)1);

    if (inst != 0)
        (*(void (__thiscall**)(void*))(*(int*)inst + 4))(inst);
    return res;
}

// @ 0x007ac850
void* cTextureManager::GetTextureAsync(ResourceKey key, int flags)
{
    ResManMgr* mgr = (ResManMgr*)ResManager();
    key.mType = 0x2f4e681c;
    if (!mgr->GetResource(&key, 0, 0, 0, 0, 0))
        return 0;
    void* inst = CreateInstance(&key, 0, mLoadingRaster, flags, 0);
    void* local = inst ? (void*)((char*)inst - 8) : 0;
    mLoadQueue.Schedule(&local);
    return inst;
}

// @ 0x007ac8d0
void* cTextureManager::StallUntilLoadedUnderLock(ResourceKey* key)
{
    cLoadQueue* q = &mLoadQueue;                // this in ecx; the queue's own fields are used

    for (;;)
    {
        cTextureInstanceInternal* inst = *(cTextureInstanceInternal**)key;
        CQEntry* pSlot = 0;

        char* pBase = inst ? (char*)inst + 8 : 0;
        if ((*(uint8_t*)(pBase + 4) & 1) != 0 || pSlot != 0)
        {
            if ((*(uint8_t*)(pBase + 4) & 1) == 0)
            {
                void* pOut = 0;
                StallUntilLoadedFn(&pOut, q->mQueue.mData, q->mQueue.mData + 4, inst);
                if (pOut != (void*)q->mQueue.mData[6])
                {
                    ((cTextureAsyncInfo*)pSlot)->Setup((ResourceKey*)q->mQueue.mData);
                    ((AsyncDeque*)((char*)q + 0x44))->erase(*(DqIterB*)pSlot);
                    ((cTextureManager*)q->mpManager)->StallFinishBackgroundLoad(pSlot);
                }
            }
            return 0;
        }

        // scan the four slot entries for a free/owning one
        for (int i = 0; i < 4; i++)
        {
            if (q->mEntries[i].a == 0 || q->mEntries[i].a == (int)inst)
            {
                pSlot = &q->mEntries[i];
                break;
            }
        }
        if (pSlot == 0)
        {
            int n = q->mField70;
            pSlot = &q->mEntries[n];
            if (++q->mField70 >= 4)
                q->mField70 = 0;
        }
        if (pSlot->a == 0)
            continue;                           // restart the scan
        ((cTextureManager*)q->mpManager)->StallFinishBackgroundLoad(pSlot);
        if (pSlot->a == 0)
            continue;
        // restart from the top of the outer loop (the slot is now busy)
        continue;
    }
}

// ---- texture instance created by the built-in creators ------------------
struct TiRefCount {
    volatile long mRefCount;                    // +0x04
    TiRefCount() { _InterlockedExchange(&mRefCount, 0); }
};

struct TiBaseA {                                // vtable 0x013ebcdc
    virtual void v0();
    TiRefCount  mRef;                           // +0x04
    uint32_t    f08;                            // +0x08
    uint32_t    f0c;                            // +0x0c
    uint32_t    f10;                            // +0x10
    uint32_t    f14;                            // +0x14
    virtual void v1();
    TiBaseA() : f08(0), f0c(0), f10(0), f14(0) {}
};

struct TiDerivedA : TiBaseA {                   // vtable 0x0140e12c, 0x1c bytes
    uint32_t f18;                               // +0x18
    TiDerivedA() : f18(0) {}
};

struct GameTexture {                            // 0x20 bytes, ctor 0x00765f10
    GameTexture(void* pArg);
    virtual void v0();
    virtual void v1();
    uint32_t f04, f08, f0c, f10, f14, f18, f1c;
};

template <class T> class TiInstancePtr {        // scoped release guard (dtor 0x007a9610)
public:
    T* mpPtr;
    TiInstancePtr(T* p) : mpPtr(p) {}
    ~TiInstancePtr() { if (mpPtr != 0) mpPtr->v1(); }
};

void* __cdecl operator new(unsigned int sz, const char* name, int, int, int, int);  // 0x00f473a0
inline void* operator new(unsigned int, void* p) { return p; }
template <class T> void* operator new(unsigned int, T* p) { return p; }

// @ 0x007aca00
void* cTextureManager::CreateGameTextureFromSerializer(void* arg0, void* arg1, void* arg2, uint32_t flags)
{
    if ((*(uint8_t*)((char*)arg2 + 4) & 1) == 0)
        (*(void(__thiscall**)(void*, void*))(*(uint32_t*)this + 0x34))(this, arg2);

    GameTexture* p = 0;
    GameTexture* raw = (GameTexture*)operator new(0x20, "Graphics", 0, 0, 0, 0);
    if (raw != 0)
        p = new (raw) GameTexture(*(void**)((char*)arg2 + 0x1c));
    if (p != 0)
        p->v0();

    p->f18 = *(uint32_t*)arg2;
    p->f08 = (uint32_t)arg0;
    p->f0c = 0x2f4e681c;
    p->f10 = (uint32_t)arg1;

    void* res = RegisterBuiltInGameTexture(p, flags);
    p->v1();
    return res;
}

// @ 0x007acae0
void* cTextureManager::CreateGameTextureRaw(void* arg0, void* arg1, uint32_t key, uint32_t flags)
{
    TiDerivedA* raw = (TiDerivedA*)operator new(0x1c, "Graphics", 0, 0, 0, 0);
    TiInstancePtr<TiDerivedA> guard(raw != 0 ? new (raw) TiDerivedA() : 0);
    TiDerivedA* p = guard.mpPtr;
    if (p != 0)
        p->v0();

    p->f18 = key;
    p->f08 = (uint32_t)arg0;
    p->f0c = 0x2f4e681c;
    p->f10 = (uint32_t)arg1;

    return RegisterBuiltInGameTexture(p, flags);
}
