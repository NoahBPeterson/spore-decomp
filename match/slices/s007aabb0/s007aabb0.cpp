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

// Raster view used by the synchronous path of CreateTextureRaster.
struct Raster {
    uint32_t mFormat;       // +0x00
    char     mPad04[8];
    uint16_t mWidth;        // +0x0c
    uint16_t mHeight;       // +0x0e
    uint32_t D3D9GetMipLevelSize(unsigned char level);                          // 0x011f0000
    void     FillSpriteTexture(void* pBuffer, unsigned int size, int zero);     // 0x011f0440
};

// Common texture-instance layout built by the three texture constructors.
struct TextureObject {
    void*    mpVtable;      // +0x00
    uint32_t mRefCount;     // +0x04
    uint32_t mField08;      // +0x08
    uint32_t mField0c;      // +0x0c
    uint32_t mField10;      // +0x10
    uint32_t mField14;      // +0x14
    void*    mpVtable18;    // +0x18
    uint32_t mWidth;        // +0x1c
    uint32_t mHeight;       // +0x20
    uint32_t mFormat;       // +0x24
    void*    mpBuffer;      // +0x28
    void* InitBase(int width, int height);      // 0x00432960
    void* InitRGBA8(int width, int height);     // 0x004328d0
    void* InitA8(int width, int height);        // 0x007a9e10
};

// Single-pointer smart slot used by the synchronous path.
struct PointerSlot {
    void* mpObject;         // +0x00
    PointerSlot* Assign(void* pObject);         // 0x004535d0
};

// Instance object and its temporary smart-pointer wrapper built by the async path.
struct AsyncTextureInstance {
    void*    mpVtable;      // +0x00
    uint32_t mRefCount;     // +0x04
    char     mPad08[8];     // +0x08
    uint32_t mField10;      // +0x10
    uint32_t mField14;      // +0x14
    uint32_t mField18;      // +0x18
    char     mPad1c[0x14];  // +0x1c
    uint32_t mId;           // +0x30
    uint32_t mField34;      // +0x34
    uint32_t mField38;      // +0x38
    uint32_t mField3c;      // +0x3c
};

struct RefWrapper {
    void*    mpVtable;      // +0x00
    uint32_t mRefCount;     // +0x04
    void*    mpRef8;        // +0x08
    void*    mpRaster;      // +0x0c
    void*    mpInstance;    // +0x10
};

void* gTextureAllocPtr;     // placeholder for the operator new declaration below
void* __cdecl TextureAlloc(unsigned int n, const char* pName, int flags, int align, const char* pFile, int line); // 0x00f473a0
extern const char gTextureAllocFile[];

class ResourceManager {
public:
    char mPad00[0x0c];
    void* vfn0c(void* a, int, int, int, int, int);   // vtable slot 3
};
ResourceManager* GetResourceManager();               // 0x0067dcd0
void* FUN_0067dd50();                                // 0x0067dd50

typedef bool (__thiscall* TextureManagerVfn68)(void* self, void* arg);

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
    bool ReloadTexture(ResourceKey key);            // 0x007ab6c0
    void RegisterArenaContents(void* pArena);       // 0x007ab730
    bool Shutdown();                                // 0x007ab460
    bool CreateTextureRaster(Raster* a, void** b, bool c, int d); // 0x007aabb0

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
bool cTextureManager::CreateTextureRaster(Raster* a, void** b, bool c, int d)
{
    if (c) {
        uint32_t id = (d != 0) ? (uint32_t)d : 0x522264du;
        AsyncTextureInstance* inst = (AsyncTextureInstance*)TextureAlloc(0x40, "Graphics", 0, 0, 0, 0);
        if (inst != 0) {
            inst->mId = id;
            inst->mpVtable = (void*)0x13eb90c;
            inst->mRefCount = 0;
            inst->mpVtable = (void*)0x13eb844;
            inst->mField38 = 0;
            inst->mField10 = 0xffffffffu;
            inst->mField18 = 0xffffffffu;
        }
        RefWrapper* ref = (RefWrapper*)TextureAlloc(0x14, "Graphics", 0, 0, 0, 0);
        if (ref != 0) {
            ref->mpVtable = (void*)0x140faa8;
            ref->mRefCount = 0;
            ref->mpVtable = (void*)0x140fab8;
            ref->mpRef8 = 0;
            ref->mpRaster = 0;
            ref->mpInstance = 0;
            ((void (__thiscall*)(void*))((void**)(*(void**)ref))[0])(ref);
        }
        void* old = ref->mpInstance;
        if (inst != old) {
            ((void (__thiscall*)(void*))((void**)(*(void**)inst))[1])(inst);
            ref->mpInstance = inst;
            if (old != 0)
                ((void (__thiscall*)(void*))((void**)(*(void**)old))[2])(old);
        }
        ref->mpRaster = a;
        struct RequestDesc {
            uint32_t f00, f04;
            uint8_t  f08;
            uint8_t  pad09[3];
            uint32_t f0c, f10, f14, f18, f1c, f20, f24, f28;
        } desc;
        desc.f00 = 4; desc.f04 = 0; desc.f08 = 1;
        desc.f0c = desc.f10 = desc.f14 = desc.f18 = 0;
        desc.f1c = desc.f20 = desc.f24 = desc.f28 = 0;
        void* mgr = FUN_0067dd50();
        typedef void (__thiscall* MgrVfn)(void*, void*, int, void*);
        ((MgrVfn)((void**)(*(void**)mgr))[0x78 / 4])(mgr, ref, 0, &desc);
        ((void (__thiscall*)(void*))((void**)(*(void**)ref))[1])(ref);
        return true;
    }

    Raster* raster = a;
    const int width = raster->mWidth;
    const int height = raster->mHeight;
    const uint32_t mipSize = raster->D3D9GetMipLevelSize(0);

    PointerSlot slot;
    slot.mpObject = 0;
    TextureObject* texture = 0;

    switch (raster->mFormat) {
    case 0x31545844:    // DXT1
        texture = (TextureObject*)TextureAlloc(0x2c, "Graphics", 0, 0, 0, 0);
        if (texture != 0)
            texture = (TextureObject*)texture->InitBase(width, height);
        slot.Assign(texture);
        texture = (TextureObject*)slot.mpObject;
        texture->mpBuffer = TextureAlloc(mipSize, "Graphics", 0, 0, 0, 0);
        texture->mFormat = 4;
        break;
    case 0x33545844:    // DXT3
        texture = (TextureObject*)TextureAlloc(0x2c, "Graphics", 0, 0, 0, 0);
        if (texture != 0)
            texture = (TextureObject*)texture->InitBase(width, height);
        slot.Assign(texture);
        texture = (TextureObject*)slot.mpObject;
        texture->mpBuffer = TextureAlloc(mipSize, "Graphics", 0, 0, 0, 0);
        texture->mFormat = 5;
        break;
    case 0x35545844:    // DXT5
        texture = (TextureObject*)TextureAlloc(0x2c, "Graphics", 0, 0, 0, 0);
        if (texture != 0)
            texture = (TextureObject*)texture->InitBase(width, height);
        slot.Assign(texture);
        texture = (TextureObject*)slot.mpObject;
        texture->mpBuffer = TextureAlloc(mipSize, "Graphics", 0, 0, 0, 0);
        texture->mFormat = 6;
        break;
    case 0x15:
    case 0x16:
        texture = (TextureObject*)TextureAlloc(0x2c, "Graphics", 0, 0, 0, 0);
        if (texture != 0)
            texture = (TextureObject*)texture->InitRGBA8(width, height);
        slot.Assign(texture);
        texture = (TextureObject*)slot.mpObject;
        break;
    case 0x1c:
        texture = (TextureObject*)TextureAlloc(0x2c, "Graphics", 0, 0, 0, 0);
        if (texture != 0)
            texture = (TextureObject*)texture->InitA8(width, height);
        slot.Assign(texture);
        texture = (TextureObject*)slot.mpObject;
        break;
    default:
        return false;
    }

    if (texture == 0)
        return false;
    raster->FillSpriteTexture(texture->mpBuffer, mipSize, 0);
    *b = texture;
    return true;
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
bool cTextureManager::ReloadTexture(ResourceKey key)
{
    TextureInstanceMap& map = mTextureInstanceMap;
    key.mType = 0;
    HashIterator it = map.find(key);
    if (it.mpNode != map.mpBucketArray[map.mnBucketCount]) {
        void* pInstance = ((TextureNode*)it.mpNode)->pInstance;
        void* pArg = pInstance != 0 ? (char*)pInstance + 8 : 0;
        return ((TextureManagerVfn68)(*(void***)this)[0x68 / 4])(this, pArg);
    }
    return false;
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
