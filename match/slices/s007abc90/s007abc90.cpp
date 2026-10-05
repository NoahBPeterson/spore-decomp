// Slice s007abc90 — SP::cTextureManager construction, texture-instance creation and
// the hash_map::operator[] accessor (0x7abc90..0x7acae0).
// Optimized region: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

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

    char            mEmpty[4];     // +0x00
    TextureNode**   mpBucketArray; // +0x04
    uint32_t        mnBucketCount; // +0x08
    uint32_t        mnElementCount;// +0x0c
    RehashPolicy    mRehashPolicy; // +0x10
    char            mRest[4];      // +0x1c
};

class cLoadQueue {
public:
    cLoadQueue();                                   // 0x007ac0f0
    void Schedule(void* pEntry);                    // 0x007abae0
    void*           mpManager;    // +0x00
    char            mEntry[0x40]; // +0x04
    char            mQueue[0x30]; // +0x44
};

class cTextureManager {
public:
    cTextureManager();                              // 0x007ac1e0
    void* CreateInstance(ResourceKey* key, void* pResource, int a, uint32_t flags, char b, ...); // 0x007ac2f0
    void* GetTextureSync(ResourceKey key, int flags);   // 0x007ac750
    void* GetTextureAsync(ResourceKey key, int flags);  // 0x007ac850
    void* StallUntilLoadedUnderLock(ResourceKey* key);  // 0x007ac8d0
    void* RegisterBuiltInGameTexture(void* p1, uint32_t flags); // 0x007ac600

    char            mPad00[0x0c]; // +0x00
    bool            mIsInitialized;
    char            mPad0d[3];
    void*           mInvalidRaster; // +0x10
    void*           mLoadingRaster; // +0x14
    char            mPad18[8];
    EA::Thread::Mutex mMutex;       // +0x20
    char            mPad50[8];
    TextureInstanceMap mTextureInstanceMap; // +0x58
    char            mPad78[0x20];
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

// ---------------------------------------------------------------------------
// @ 0x007abc90
extern "C" void FUN_007abc90(void)
{
    // PARTIAL: large texture-creation EH routine.
}

// @ 0x007ac0f0
cLoadQueue::cLoadQueue()
{
    // PARTIAL: EH member construction (entry vector + deque).
    mpManager = 0;
}

// @ 0x007ac1e0
cTextureManager::cTextureManager()
{
    // PARTIAL: EH base/vtable + member construction.
}

// @ 0x007ac2f0
void* cTextureManager::CreateInstance(ResourceKey* key, void* pResource, int a, uint32_t flags, char b, ...)
{
    (void)key; (void)pResource; (void)a; (void)flags; (void)b;
    // PARTIAL: texture-instance allocation + map insert.
    return 0;
}

// @ 0x007ac480
extern "C" void FUN_007ac480(void)
{
    // PARTIAL: eastl::deque<cTextureAsyncQueueEntry>::erase.
}

// @ 0x007ac600
void* cTextureManager::RegisterBuiltInGameTexture(void* p1, uint32_t flags)
{
    (void)p1; (void)flags;
    // PARTIAL: lookup-or-create built-in texture.
    return 0;
}

// @ 0x007ac750
void* cTextureManager::GetTextureSync(ResourceKey key, int flags)
{
    (void)key; (void)flags;
    // PARTIAL: synchronous resource load.
    return 0;
}

// @ 0x007ac850
void* cTextureManager::GetTextureAsync(ResourceKey key, int flags)
{
    (void)key; (void)flags;
    // PARTIAL: asynchronous resource load + queue schedule.
    return 0;
}

// @ 0x007ac8d0
void* cTextureManager::StallUntilLoadedUnderLock(ResourceKey* key)
{
    (void)key;
    // PARTIAL: wait for the queued load of the requested key.
    return 0;
}

// @ 0x007aca00
extern "C" void FUN_007aca00(void)
{
    // PARTIAL: create texture-instance from a serializer object.
}

// @ 0x007acae0
extern "C" void FUN_007acae0(void)
{
    // PARTIAL: create texture-instance from raw parameters.
}
