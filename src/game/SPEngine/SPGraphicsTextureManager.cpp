// src/game/SPEngine/SPGraphicsTextureManager.cpp -- migrated from slice(s) s007abc90, s007aabb0, s007a9ae0, s007a8a50 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsTextureManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTextureManager.h"
#include "rw/graphics/ActiveState.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* g_D3D9Device;                 // 0x016f89d0
extern "C" void* FUN_0067de60_IDGenerator();
extern "C" void* FUN_0067dcd0_GetManager();
extern "C" void  FUN_00690_120_GetStatus(void*);
extern "C" void* SP_CreateRaster(int, int, int, unsigned int, int);
extern "C" char  FUN_006b4b60();
#pragma intrinsic(_InterlockedExchangeAdd)
#include <new>
#include <xmmintrin.h>
#include <intrin.h>
#include "SP/cTextureAsyncInfo.h"
#include "SP/cJob.h"
#include "EA/Thread/Mutex.h"

// ---- items of slice s007a8a50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* g_D3D9Device;                 // 0x016f89d0
extern "C" void* FUN_0067de60_IDGenerator();
extern "C" void* FUN_0067dcd0_GetManager();
extern "C" void  FUN_00690_120_GetStatus(void*);
extern "C" void* SP_CreateRaster(int, int, int, unsigned int, int);
extern "C" char  FUN_006b4b60();
struct TextureKey { int mKey; unsigned int mType; int mExtra; };
struct cTextureManager {
    void* vtbl;               // +0x00
    char  pad004[0x24 - 4];
    void* mJob;               // +0x24
    char  pad028[0x2c - 0x28];
    void* mJob2;              // +0x2c
    char  pad030[0x148 - 0x30];

    void GetTexture(int a, int b, int c);        // 007a93c0
    void HasTexture(int a, int b);               // 007a93f0
    void GetKeyFromTexture(int* out, int tex);   // 007a9420
    void* GetResourceForTexture(void* tex);      // 007a9450
    void CreateTexture();                        // 007a9470
    void CreateTextureEx(int a,int b,int c,int d,int e,unsigned int flags,int f,int g); // 007a94f0
    void RegisterGameTexture(int a, int b);      // 007a9540
    void ReloadTexture(int a, int b);            // 007a95e0
    void CleanupJob();                           // 007a9620
    char WriteTexture(int tex, char async);      // 007a9730
};
struct RefPtrSlot {
    int* mPtr;
    void Assign(int* value);   // 007a97e0
    void Clear();              // 007a9880
};
struct DequeOwner {
    char pad[0x4c];
    void RemoveMatching(int* value);   // 007a9840
};
struct DequeIter2 {
    int* cur; int* first; int* last; int** map;
    DequeIter2& operator+=(int n);   // 007a9a80
};
// ---- items of slice s007a8a50 end

// ---- items of slice s007a9ae0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line); // 0x00f473a0
extern "C" char VT_ArenaResource[];
struct DequeMap {
    int*  mpBegin;      // +0x00
    int   mCapacity;    // +0x04
    int*  mFirst;       // +0x0c
    int*  mLast;        // +0x10
    int*  mCur;         // +0x14
    int*  mNextBegin;   // +0x18
    int*  mNextLast;    // +0x1c / +0x18?
    int*  mTailFirst;   // +0x20
    int*  mTailLast;    // +0x24
    void InsertAt(int count, int zero);
    void PushBack(int* value);
    void ReverseCopyTo(int* out, int* end);
};
struct Chunk {
    Chunk* mpNext;      // +0x00
    int    pad04;
    int    pad08;
    char   m0c;
    long   mRef;        // +0x10
    int    pad14[2];
    int    pad1c;
    int    pad20;
    int    pad24;
    int    pad28;
    int    pad2c;
};
struct cNodeAllocator {
    int   pad00[4];
    Chunk* mpHeadChunk; // +0x10
    Chunk* Create();
};
struct JobSlots {
    void Clear();      // 007aa320
    int  Transfer(int param_2);   // 007aa3a0
};
struct FixedAllocatorBase { bool AddCore(int, int); };
// ---- items of slice s007a9ae0 end

// ---- items of slice s007aabb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char gTextureAllocFile[];
extern char g_mutexAttribute;   // 0x0140fa10
namespace EA {
namespace Thread {
class Mutex_s007a_abb0 {
public:
    bool Lock(void* pAttribute);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    void Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
private:
    char mData[0x30];
};
}
}
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
void* __cdecl TextureAlloc(unsigned int n, const char* pName, int flags, int align, const char* pFile, int line);
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
class cTextureManager_s007a_abb0 {
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
    EA::Thread::Mutex_s007a_abb0 mMutex;       // +0x20  (0x30)
    IntrusiveList   mTextureInstances; // +0x50
    TextureInstanceMap mTextureInstanceMap; // +0x58 (0x20)
    ArenaSet        mTextureArenas; // +0x78 (0x20)
    EA::Thread::Mutex_s007a_abb0 mArenaMutex;  // +0x98 (0x30)
    int             mNumCacheFrames;      // +0xc8
    int             mCurrentMipLodSetting; // +0xcc
    void*           mUnknownD0;     // +0xd0
    cLoadQueue      mLoadQueue;     // +0xd4 (0x68)
    bool            mShowStats;     // +0x13c
    int             mArenaTextureBytes;   // +0x140
    int             mArenaTextureCount;   // +0x144
};
// ---- items of slice s007aabb0 end

// ---- items of slice s007abc90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct TextureNode_s007a_bc90;
struct TextureValue {
    ResourceKey first;   // +0x00
    void*       second;  // +0x0c
    TextureValue(const ResourceKey& k, void* v) : first(k), second(v) {}
};
struct TextureNode_s007a_bc90 {
    ResourceKey  first;   // +0x00
    void*        second;  // +0x0c
    TextureNode_s007a_bc90* next;    // +0x10
};
struct InsertResult {
    HashIterator it;
    bool         second;
};
struct true_type {};
class TextureInstanceMap_s007a_bc90 {
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
    TextureNode_s007a_bc90**   mpBucketArray; // +0x04
    uint32_t        mnBucketCount; // +0x08
    uint32_t        mnElementCount;// +0x0c
    RehashPolicy    mRehashPolicy; // +0x10
    char            mRest[4];      // +0x1c
};
// ---- items of slice s007abc90 end

// @ 0x007a93b0
void FUN_007a93b0()
{
    void* d = g_D3D9Device;
    ((void(__thiscall*)(void*))((void**)d)[0x14 / 4])(d);
}




// @ 0x007a93c0
void cTextureManager::GetTexture(int a, int b, int c)
{
    TextureKey key;
    key.mKey = a;
    key.mType = 0x2f4e681c;
    key.mExtra = b;
    ((void(__thiscall*)(void*, TextureKey, int))((void**)this->vtbl)[0x1c / 4])(this, key, c);
}




// @ 0x007a93f0
void cTextureManager::HasTexture(int a, int b)
{
    TextureKey key;
    key.mKey = a;
    key.mType = 0x2f4e681c;
    key.mExtra = b;
    ((void(__thiscall*)(void*, TextureKey))((void**)this->vtbl)[0x24 / 4])(this, key);
}




// @ 0x007a9420
void cTextureManager::GetKeyFromTexture(int* out, int tex)
{
    int base = tex ? tex - 8 : 0;
    out[0] = *(int*)(base + 0x18);
    out[1] = *(int*)(base + 0x1c);
    out[2] = *(int*)(base + 0x20);
}




// @ 0x007a9450
bool SP::cTextureManager::StallUntilLoaded(SP::cTextureInstance const * tex)
{
    return tex ? *(void**)((char*)tex + 0x1c) : *(void**)((char*)tex + 0x24);
}




// @ 0x007a9470
void cTextureManager::CreateTexture()
{
    int buf[3] = { 0, 0, 0 };
    void* gen = FUN_0067de60_IDGenerator();
    // virtual slot 1 through the generator's vtable (the original does mov edx,[eax]; mov edx,[edx+4]);
    // ((void**)gen)[1] read the object's second field, an incrementing ID, and the hybrid called it
    ((void(__thiscall*)(void*, int*, unsigned int, int, int, int, int))(*(void***)gen)[1])
        (gen, buf, 0x2f4e681c, 0, 0, 0x22, 0);
    ((void(__thiscall*)(void*, int, int, int, int, int, int, int, int))((void**)this->vtbl)[0x3c / 4])
        (this, 0x2f4e681c, 0, 0, 0, buf[0], buf[1], buf[2], 0);
}




// @ 0x007a94f0
void cTextureManager::CreateTextureEx(int a, int b, int c, int d, int e, unsigned int flags, int f, int g)
{
    if (flags & 0x11)
        ((void(__thiscall*)(void*))((void**)this->vtbl)[0x18 / 4])(this);
    void* raster = SP_CreateRaster(c, d, e, flags, f);
    ((void(__thiscall*)(void*, int, int, void*, int))((void**)this->vtbl)[0x4c / 4])
        (this, a, b, raster, g);
}




// @ 0x007a9540
void cTextureManager::RegisterGameTexture(int a, int b)
{
    int buf[3] = { 0, 0, 0 };
    void* gen = FUN_0067de60_IDGenerator();
    // virtual slot 1 through the generator's vtable (the original does mov edx,[eax]; mov edx,[edx+4]);
    // ((void**)gen)[1] read the object's second field, an incrementing ID, and the hybrid called it
    ((void(__thiscall*)(void*, int*, unsigned int, int, int, int, int))(*(void***)gen)[1])
        (gen, buf, 0x2f4e681c, 0, 0, 0x22, 0);
    // forwards the generated key (buf[0], buf[2]) then a, b: the original pushes b, a, buf[2],
    // buf[0]. Passing (a, b, 0, 0) registered textures under the wrong key and the hybrid later
    // called through the ID as if it were a pointer (2026-10-12).
    ((void(__thiscall*)(void*, int, int, int, int))((void**)this->vtbl)[0x4c / 4])
        (this, buf[0], buf[2], a, b);
}




// @ 0x007a95b0
void FUN_007a95b0(int tex, char flag)
{
    int base = tex ? tex - 8 : 0;
    if (flag)
        *(unsigned char*)(base + 0xc) |= 8;
    else
        *(unsigned char*)(base + 0xc) &= 0xf7;
}




// @ 0x007a95e0
void cTextureManager::ReloadTexture(int a, int b)
{
    TextureKey key;
    key.mKey = a;
    key.mType = 0x2f4e681c;
    key.mExtra = b;
    ((void(__thiscall*)(void*, TextureKey))((void**)this->vtbl)[0x60 / 4])(this, key);
}




// @ 0x007a9620
void cTextureManager::CleanupJob()
{
    if (this->mJob2)
        FUN_00690_120_GetStatus(this->mJob2);
    if (this->mJob)
        ((void(__thiscall*)(void*))((void**)this->mJob)[1])(this->mJob);
}




// @ 0x007a9680
void FUN_007a9680(int** out, int* begin, int* end, int** map, int** mapFirst, int** mapLast)
{
    int* cur = begin;
    int** m = mapFirst;
    while (cur != (int*)mapLast) {
        **out = *cur;
        ++cur;
        (*out)++;
        if (*out == *m) {
            ++m;
            *out = *m;
        }
        if (cur == end) {
            ++m;
            end = *m;
            cur = end;
        }
    }
    out[0] = cur;
    out[1] = *m;
    out[2] = end;
    out[3] = (int*)m;
}




// @ 0x007a9730
char cTextureManager::WriteTexture(int tex, char async)
{
    int base = tex ? tex - 8 : 0;
    if ((*(unsigned char*)(base + 0xc) & 8) == 0)
        return 1;
    ((void(__thiscall*)(void*, int))((void**)this->vtbl)[0x34 / 4])(this, base + 8);
    char ok;
    if (async == 0) {
        void* rm = FUN_0067dcd0_GetManager();
        ok = ((char(__thiscall*)(void*, int, int, int, int, void*))((void**)rm)[0x20 / 4])
            (rm, *(int*)(base + 0x24), 0, tex, 0, 0);
    }
    else {
        ok = FUN_006b4b60();
    }
    if (ok && ((*(unsigned char*)(*(int*)(base + 8) + 4) & 0xf) == 8))
        *(unsigned char*)(base + 0xc) &= 0xf7;
    return ok;
}




// @ 0x007a9840
void DequeOwner::RemoveMatching(int* value)
{
    int param_1 = (int)this;
    int* cur = *(int**)(param_1 + 0x4c);
    int* chunk = *(int**)(param_1 + 0x58);
    int* last = *(int**)(param_1 + 0x54);
    if (cur != *(int**)(param_1 + 0x5c)) {
        while (true) {
            if (*cur == *value)
                *cur = 0;
            ++cur;
            if (cur == last) {
                cur = *(int**)(chunk + 4);
                chunk += 4;
                last = cur + 0x40;
            }
            if (cur == *(int**)(param_1 + 0x5c))
                break;
        }
    }
}




// @ 0x007a9880
#include <intrin.h>
void RefPtrSlot::Clear()
{
    if (mPtr) {
        volatile long* rc = (volatile long*)((char*)mPtr + 0x10);
        _InterlockedExchangeAdd(rc, -1);
        long cur = _InterlockedExchangeAdd(rc, 0);
        if (cur < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
}




// @ 0x007a98b0
void StallUntilLoaded(int** out, int* begin, int* first, int* end, int** map, int* mapEnd)
{
    int* cur = begin;
    int* chunk = first;
    int** m = map;
    while (cur != mapEnd && *cur != (int)end) {
        ++cur;
        if (cur == end) {
            ++m;
            cur = *m;
            end = cur + 0x40;
            chunk = cur;
        }
    }
    out[2] = end;
    out[3] = (int*)m;
    out[0] = cur;
    out[1] = chunk;
}




// @ 0x007a9a80
DequeIter2& DequeIter2::operator+=(int n)
{
    DequeIter2* it = this;
    unsigned int off = (unsigned int)(it->cur - it->first) + n;
    if (off < 0x40) {
        it->cur = it->cur + n;
        return *it;
    }
    int chunkIndex = (int)((off + 0x1000000 + ((int)(off + 0x1000000) >> 0x1f & 0x3f)) >> 6) - 0x40000;
    int** slot = (int**)((char*)it->map + chunkIndex * 4);
    it->map = slot;
    int* base = *slot;
    it->first = base;
    it->last = base + 0x40;
    it->cur = it->first + (off + chunkIndex * -0x40);
    return *it;
}



// @ 0x007a9d70
void FUN_007a9d70(int** out, int* end, int* first, int** map, int* mfirst, int* mlast, int** map2)
{
    int* a = first; int* b = map[0]; int** c = map; int* d = mfirst;
    while (a != end) {
        if (a == b) { --c; b = *c; a = b + 0x40; }
        --a;
        if (d == mlast) { --map2; mlast = *map2; d = mlast + 0x40; }
        --d; *d = *a;
    }
    out[0] = d; out[1] = mlast; out[2] = *map2; out[3] = (int*)map2;
}



// @ 0x007a9eb0
void FUN_007a9eb0(int* self)
{
    if (self[4])
        ((void(__thiscall*)(void*))((void**)self[4])[2])((void*)self[4]);
    if (self[2])
        _InterlockedExchangeAdd((volatile long*)((char*)self[2] + 8), -1);
    *(void**)self = (void*)VT_ArenaResource;
}



// @ 0x007aa3a0
int JobSlots::Transfer(int param_2)
{
    int self = (int)this;
    int* a = *(int**)(self + 0xc);
    if (a && *(int*)(self + 8) == 0) {
        int* b = *(int**)(self + 8);
        if (b) { *(int*)(self + 8) = 0; ((void(__thiscall*)(void*))((void**)b)[1])(b); }
        ((void(__thiscall*)(void*, int*))((void**)a)[0x14 / 4])(a, (int*)(self + 8));
    }
    int* c = *(int**)(self + 0xc);
    if (c) { *(int*)(self + 0xc) = 0; ((void(__thiscall*)(void*))((void**)c)[1])(c); }
    int* d = *(int**)(self + 8);
    if (d && d[6]) {
        void (*cb)(int) = *(void(**)(int))(param_2 + 0x24);
        int old = *(int*)(param_2 + 0x20);
        *(int*)(param_2 + 0x20) = d[6];
        *(int*)(param_2 + 0x24) = 0;
        if (cb) cb(old);
        return 1;
    }
    return 0;
}



// @ 0x007aa800
Chunk* cNodeAllocator::Create()
{
    while (this->mpHeadChunk == 0) {
        if (!((FixedAllocatorBase*)this)->AddCore(0, 0))
            return 0;
    }
    Chunk* p = this->mpHeadChunk;
    this->mpHeadChunk = p->mpNext;
    *(int*)((char*)p + 4) = 0;
    *(int*)((char*)p + 0) = 0;
    *(int*)((char*)p + 8) = 0;
    *(unsigned char*)((char*)p + 0xc) = 0;
    _InterlockedExchangeAdd((volatile long*)((char*)p + 0x10), 1);
    *(int*)((char*)p + 0x18) = 0;
    *(int*)((char*)p + 0x1c) = 0;
    *(int*)((char*)p + 0x20) = 0;
    *(int*)((char*)p + 0x24) = 0;
    *(int*)((char*)p + 0x2c) = 0;
    return p;
}



// @ 0x007aa850
void DequeMap::PushBack(int* value)
{
    int* self = (int*)this;
    int v = *value;
    if (self[1] <= ((self[9] - *self) >> 2) + 1)
        ((DequeMap*)self)->InsertAt(1, 1);
    int* buf = (int*)EASTL_allocator_allocate(0x100, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    *(int*)(self[9] + 4) = (int)buf;
    if (self[6]) *(int*)self[6] = v;
    int t = self[9];
    self[9] = t + 4;
    int base = *(int*)(t + 4);
    self[7] = base;
    self[8] = base + 0x100;
    self[6] = self[7];
}


// @ 0x007aaf90
void cTextureManager_s007a_abb0::UnregisterArena(void* pArena)
{
    EA::Thread::Mutex_s007a_abb0& mtx = mArenaMutex;
    mtx.Lock(&g_mutexAttribute);
    mTextureArenas.erase(pArena);
    mtx.Unlock();
}


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


// @ 0x007ab5f0
bool cTextureManager_s007a_abb0::HasTexture(ResourceKey key)
{
    TextureInstanceMap& map = mTextureInstanceMap;
    EA::Thread::Mutex_s007a_abb0& mtx = mMutex;
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


// @ 0x007ab6c0
uint32_t cTextureManager_s007a_abb0::ReloadTexture(ResourceKey key)
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

// @ 0x007ac080
void*& TextureInstanceMap_s007a_bc90::operator[](const ResourceKey& key)
{
    HashIterator it = find(key);
    if (it.mpNode == mpBucketArray[mnBucketCount])
        it = DoInsertValue(TextureValue(key, 0), true_type()).it;
    return ((TextureNode_s007a_bc90*)it.mpNode)->second;
}
