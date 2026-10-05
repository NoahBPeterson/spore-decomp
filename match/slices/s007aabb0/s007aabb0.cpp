// Slice s007aabb0 — SP::cTextureManager teardown, arena registration and the
// texture-instance hash_map accessors (0x7aabb0..0x7abae0).
// Optimized region: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

// ---------------------------------------------------------------------------
// Minimal recovered types.
// ---------------------------------------------------------------------------
namespace EA { namespace Thread {
class Mutex {
public:
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

class cJob {
public:
    void  Cancel(int bWait);   // 0x00692400
    void  Wait();              // 0x006926b0
    int   GetStatus();         // 0x00690120
private:
    char mData[0x28];
};

class cArenaResource;

// EASTL-ish container stubs (only the members reached from this slice).
struct HashIterator {
    void*  mpNode;
    void** mpBucket;
};

struct TextureNode;

class TextureInstanceMap {
public:
    HashIterator find(const ResourceKey& key);     // 0x00833840
    void         DoFreeNodes(void*, uint32_t);     // 0x007611f0

    struct RehashResult { bool first; uint32_t second; };
    struct RehashPolicy {
        float    mfMaxLoadFactor;   // +0x00
        float    mfGrowthFactor;    // +0x04
        uint32_t mnNextResize;      // +0x08
        RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);
    };
    struct InsertResult { HashIterator it; bool second; };
    struct TextureValue { ResourceKey key; void* pInstance; };
    struct true_type {};

    InsertResult DoInsertValue(const TextureValue& value, true_type);   // 0x007ab0d0
    void DoRehash(uint32_t nNewBucketCount);                            // 0x007a9920

    char            mEmpty[4];    // +0x00
    TextureNode**   mpBucketArray; // +0x04
    uint32_t        mnBucketCount; // +0x08
    uint32_t        mnElementCount;// +0x0c
    RehashPolicy    mRehashPolicy; // +0x10
    char            mRest[4];      // +0x1c
};

struct TextureNode {
    ResourceKey key;        // +0x00
    void*       pInstance;  // +0x0c
    TextureNode* pNext;     // +0x10
};

void* gTextureAllocPtr;     // placeholder for the operator new declaration below
void* __cdecl TextureAlloc(unsigned int n, const char* pName, int flags, int align, const char* pFile, int line);
extern const char gTextureAllocFile[];

class ResourceManager {
public:
    char mPad00[0x0c];
    void* vfn0c(void* a, int, int, int, int, int);   // vtable slot 3
};
ResourceManager* GetResourceManager();               // 0x0067dcd0

typedef uint32_t (__thiscall* TextureManagerVfn68)(void* self, void* arg);

class ArenaSet {
public:
    uint32_t erase(void* const& key);              // 0x006b6740
    void     DoFreeNodes(void*, uint32_t);         // 0x006b6570
private:
    char mData[0x20];
};

class IntrusiveList {
private:
    char mData[0x8];
};

class TextureDeque {
public:
    void clear();                                  // 0x00996460
private:
    char mData[0x24];
};

// cTextureAsyncInfo (size 0x10).
class cTextureAsyncInfo {
public:
    void Clear();                                  // 0x007aa320
    void SetTexture(void* p);                      // 0x007a97e0
    static cTextureAsyncInfo* GetCurrent();        // 0x0068f4d0
    uint32_t Setup(ResourceKey* pKey);             // 0x007ab860
    void* mpTexture;    // +0x00  AutoRefCount<cTextureInstanceInternal>
    void* mpLoad;       // +0x04  cFuture<Raster> (job pointer at +0)
    void* mpResource;   // +0x08
    void* mpRequest;    // +0x0c
};

extern char g_mutexAttribute;   // 0x0140fa10
extern void* g_freeListHead;    // 0x01634f6c

// ---------------------------------------------------------------------------
// The two layout-critical classes.
// ---------------------------------------------------------------------------
class cLoadQueue {
public:
    void ClearEntries();                            // 0x007ab090
    void Update();                                  // 0x007aba40
    void Schedule(ResourceKey* pKey);               // 0x007abae0
    cTextureAsyncInfo* StallUntilLoaded(int a, int b, int c, int d, int e, int f, int g, int h, int i);

    void*           mpManager;    // +0x00
    cTextureAsyncInfo mEntry[4];  // +0x04
    TextureDeque    mQueue;       // +0x44
    char            mPad[0x0c];   // +0x68
};

class cTextureManager {
public:
    void UnregisterArena(void* pArena);             // 0x007aaf90
    bool StallFinishBackgroundLoad(ResourceKey* pKey); // 0x007aafc0
    bool HasTexture(ResourceKey key);               // 0x007ab5f0
    uint32_t ReloadTexture(ResourceKey key);        // 0x007ab6c0
    void RegisterArenaContents(void* pArena);       // 0x007ab730
    bool Shutdown();                                // 0x007ab460
    int  CreateTextureRaster(void* a, int b, bool c, int d); // 0x007aabb0

    // +0x00..+0x0b : vtables / base (cITextureManager, RefCountTemplate<int>)
    char            mPad00[0x0c];   // +0x00
    bool            mIsInitialized; // +0x0c
    char            mPad0d[3];
    void*           mInvalidRaster; // +0x10
    void*           mLoadingRaster; // +0x14
    void*           mRef18;         // +0x18
    void*           mRef1c;         // +0x1c
    EA::Thread::Mutex mMutex;       // +0x20  (0x30)
    IntrusiveList   mTextureInstances; // +0x50
    TextureInstanceMap mTextureInstanceMap; // +0x58 (0x20)
    ArenaSet        mTextureArenas; // +0x78 (0x20)
    EA::Thread::Mutex mArenaMutex;  // +0x98 (0x30)
    int             mNumCacheFrames;      // +0xc8
    int             mCurrentMipLodSetting; // +0xcc
    void*           mUnknownD0;     // +0xd0
    cLoadQueue      mLoadQueue;     // +0xd4 (0x68)
    bool            mShowStats;     // +0x13c
    int             mArenaTextureBytes;   // +0x140
    int             mArenaTextureCount;   // +0x144
};

// ---------------------------------------------------------------------------
// @ 0x007aaf90
void cTextureManager::UnregisterArena(void* pArena)
{
    EA::Thread::Mutex& mtx = mArenaMutex;
    mtx.Lock(&g_mutexAttribute);
    mTextureArenas.erase(pArena);
    mtx.Unlock();
}

// ---------------------------------------------------------------------------
// @ 0x007ab090
void cLoadQueue::ClearEntries()
{
    cTextureAsyncInfo* p = mEntry;
    int n = 4;
    do {
        if (p->mpTexture != 0) {
            cJob* pJob = (cJob*)p->mpLoad;
            if (pJob != 0)
                pJob->Cancel(1);
            p->Clear();
        }
        p = (cTextureAsyncInfo*)((char*)p + 0x10);
    } while (--n != 0);
    mQueue.clear();
}

// ---------------------------------------------------------------------------
// @ 0x007aabb0
int cTextureManager::CreateTextureRaster(void* a, int b, bool c, int d)
{
    // PARTIAL: 978-byte EH raster factory with a format switch and a job
    // dispatch; only the control skeleton is recovered here.
    (void)a; (void)b; (void)c; (void)d;
    return 0;
}

// @ 0x007aafc0
bool cTextureManager::StallFinishBackgroundLoad(ResourceKey* pKey)
{
    // PARTIAL: EH job-completion path.
    (void)pKey;
    return false;
}

// @ 0x007ab2f0
extern "C" void FUN_007ab2f0(void)
{
    // PARTIAL: ~cTextureManager with EH frame and refcount releases.
}

// @ 0x007ab460
bool cTextureManager::Shutdown()
{
    // PARTIAL: full teardown path.
    return false;
}

// @ 0x007ab0d0
TextureInstanceMap::InsertResult TextureInstanceMap::DoInsertValue(const TextureValue& value, true_type)
{
    const uint32_t c = value.key.mInstance ^ value.key.mGroup;
    uint32_t n = c % mnBucketCount;
    TextureNode** pBucket = mpBucketArray + n;
    TextureNode* pNode = *pBucket;
    while (pNode != 0) {
        if (value.key.mInstance == pNode->key.mInstance &&
            value.key.mType == pNode->key.mType &&
            value.key.mGroup == pNode->key.mGroup) {
            InsertResult found;
            found.it.mpNode = pNode;
            found.second = false;
            found.it.mpBucket = (void**)pBucket;
            return found;
        }
        pNode = pNode->pNext;
    }
    const RehashResult bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
    TextureNode* pNew = (TextureNode*)TextureAlloc(0x14, "Graphics", 0, 0, gTextureAllocFile, 0xd1);
    if (pNew != 0) {
        pNew->key = value.key;
        pNew->pInstance = value.pInstance;
    }
    pNew->pNext = 0;
    if (bRehash.first) {
        n = c % bRehash.second;
        DoRehash(bRehash.second);
    }
    pNew->pNext = mpBucketArray[n];
    mpBucketArray[n] = pNew;
    ++mnElementCount;
    InsertResult added;
    added.it.mpNode = pNew;
    added.it.mpBucket = (void**)(mpBucketArray + n);
    added.second = true;
    return added;
}

// @ 0x007ab6c0
uint32_t cTextureManager::ReloadTexture(ResourceKey key)
{
    TextureInstanceMap& map = mTextureInstanceMap;
    key.mType = 0;
    HashIterator it = map.find(key);
    if (it.mpNode == map.mpBucketArray[map.mnBucketCount])
        return 0;
    void* pInstance = *(void**)((char*)it.mpNode + 0x0c);
    if (pInstance != 0)
        return ((TextureManagerVfn68)(*(void***)this)[0x68 / 4])(this, (char*)pInstance + 8);
    return ((TextureManagerVfn68)(*(void***)this)[0x68 / 4])(this, 0);
}

// @ 0x007ab5f0
bool cTextureManager::HasTexture(ResourceKey key)
{
    TextureInstanceMap& map = mTextureInstanceMap;
    EA::Thread::Mutex& mtx = mMutex;
    mtx.Lock(&g_mutexAttribute);
    key.mType = 0;
    HashIterator it = map.find(key);
    if (it.mpNode != map.mpBucketArray[map.mnBucketCount]) {
        mtx.Unlock();
        return true;
    }
    ResourceManager* mgr = GetResourceManager();
    key.mType = 0x2f4e681c;
    typedef char (__thiscall* GetResourceFn)(void*, void*, int, int, int, int, int);
    GetResourceFn fn = (GetResourceFn)(*(void***)mgr)[3];
    char b = fn(mgr, &key, 0, 0, 0, 0, 0);
    mtx.Unlock();
    return b != 0;
}

// @ 0x007ab730
void cTextureManager::RegisterArenaContents(void* pArena)
{
    (void)pArena;
    // PARTIAL: arena export iteration.
}

// @ 0x007ab860
uint32_t cTextureAsyncInfo::Setup(ResourceKey* pKey)
{
    (void)pKey;
    // PARTIAL: async job setup.
    return 0;
}

// @ 0x007aba40
void cLoadQueue::Update()
{
    // PARTIAL: drain load queue.
}

// @ 0x007abae0
void cLoadQueue::Schedule(ResourceKey* pKey)
{
    (void)pKey;
    // PARTIAL: enqueue load request.
}
