// src/game/SPEngine/SPGraphicsTextureManager.cpp -- migrated from slice(s) s00832790, s008337d0, s007acbb0, s007abc90, s007aabb0, s007a9ae0, s007a8a50 by tools/migrate/rewrite.py
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
#pragma intrinsic(_InterlockedExchange)
#include <new>
#include <xmmintrin.h>
#include <intrin.h>
#include "SP/cTextureAsyncInfo.h"
#include "SP/cJob.h"
#include "EA/Thread/Mutex.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cTextureAsyncQueueEntry.h"
#include "SP/cTextureInstanceInternal.h"
#include <math.h>

// ---- items of slice s007a8a50 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
    int* GetKeyFromTexture(int* out, int tex);   // 007a9420
    void* GetResourceForTexture(void* tex);      // 007a9450
    void CreateTexture();                        // 007a9470
    void CreateTextureEx(int a,int b,int c,int d,int e,unsigned int flags,int f,int g); // 007a94f0
    void RegisterGameTexture(int a, int b);      // 007a9540
    void ReloadTexture(int a, int b);            // 007a95e0
    void CleanupJob();                           // 007a9620
    char WriteTexture(int tex, int extra, char async);  // 007a9730
};
struct RefPtrSlot {
    int* mPtr;
    RefPtrSlot* Assign(int* value);   // 007a97e0
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
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void  memmove(void*, const void*, unsigned int);
extern "C" void* VectorDoInsertValue(void*, void*, unsigned int);
extern "C" void  FUN_006913c0_AddWeakDep(void*);            // 0x006913c0  cJob::AddWeakDependency
extern "C" void  FUN_006926b0_Cancel(void*);                // 0x006926b0  cJob::Cancel
extern "C" void  FUN_006909b0_Refresh(void*);               // 0x006909b0  Editor::Refresh
extern "C" void  FUN_00576650_Assign(void*);                // 0x00576650  cAtomicRefPtr::operator=
extern "C" void  FUN_00630540_Assign(void*);                // 0x00630540  JobRef::operator=
extern "C" void  FUN_009221b0_Lock(void*);                  // 0x009221b0  Mutex::Lock
extern "C" void  FUN_00922270_Unlock(void*);                // 0x00922270  Mutex::Unlock
extern "C" void  FUN_00921440_Needed(void*);                // 0x00921440  RehashPolicy::Needed
extern "C" void  FUN_011ef750_Open(void*);                  // 0x011ef750  texture Open
extern "C" void  FUN_011ef880_Close(void*);                 // 0x011ef880  texture Close
extern "C" void  FUN_007a99d0_Rehash(void*);                // 0x007a99d0  hashtable rehash
extern "C" void* FUN_0067dd60();                            // 0x0067dd60  GetItemManager
extern "C" void* FUN_0067dcd0();                            // 0x0067dcd0  GetFactory
extern "C" void* FUN_0067dcc0();                            // 0x0067dcc0  MessageManager
extern "C" void* FUN_0068f4d0();                            // 0x0068f4d0  GetJobManager
extern "C" void  FUN_006ac040_SetCachingType(int, void*);   // 0x006ac040
extern "C" unsigned int FUN_00932e80_hash(const char*, unsigned int, int);  // 0x00932e80
extern "C" void* FUN_00761b40();                            // 0x00761b40
extern "C" void* FUN_00761c00();                            // 0x00761c00
extern "C" int*  FUN_0041e990_GetInt();                     // 0x0041e990
extern "C" void* g_15fd918;                                 // 0x015fd918
extern "C" char VT_PropertyListA[];   // 0x013ebcdc
extern "C" char VT_PropertyListB[];   // 0x01453eac
extern "C" char VT_PropertyListB2[];  // 0x013ebcb8
extern "C" char VT_PropertyListC[];   // 0x0140fef4
extern "C" char VT_ArenaResource[];   // 0x013eb938
typedef int (__thiscall* cJobReleaseFn)(void*);
typedef void (__thiscall* FnV0)(void*);
typedef void (__thiscall* FnV1)(void*, int);
typedef void (__thiscall* FnV2)(void*, int, int);
typedef void (__thiscall* FnVP)(void*, void*);
typedef bool (__thiscall* FnB1)(void*, void*);
typedef int  (__thiscall* FnI1)(void*, int);
typedef void*(__thiscall* FnP8)(void*, unsigned, int, int, int, int, int, int, int);
struct DequeIterator {
    int*  mpCurrent;         // +0x00
    int*  mpBegin;           // +0x04
    int*  mpEnd;             // +0x08
    int** mpCurrentArrayPtr; // +0x0c
};
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
struct Mutex {                      // EA::Thread::Mutex (0x009221b0 Lock, 0x00922270 Unlock)
    int mData[6];
};
struct TexManager {
    void**        mpVT;             // +0x00
    int           mField04;         // +0x04
    int           mField08;         // +0x08
    unsigned char mInitFlag;        // +0x0c
    void*         mField10;         // +0x10
    void*         mField14;         // +0x14
    void*         mNormalMap;       // +0x18  placeholder normal-map ref (cAtomicRefPtr)
    void*         mSpecGlossMap;    // +0x1c  placeholder spec/gloss ref (cAtomicRefPtr)
    Mutex         mMutex;           // +0x20
    unsigned char mPad[0xcc - 0x20 - sizeof(Mutex)];
    int           mFieldCC;         // +0xcc
    void*         mFieldD0;         // +0xd0
    TexManager*   mSelfD4;          // +0xd4
};
struct JobSlots {
    void Clear();      // 007aa320
    char Transfer(int param_2);   // 007aa3a0 (returns in al)
};
struct JobSlotGroup {
    void* mSlot0;                   // +0x00
    void* mSlot1;                   // +0x04
    void* mSlot2;                   // +0x08
    void* mSlot3;                   // +0x0c
};
struct JobObject {
    void*         mpVT;             // +0x00
    int           mField04;         // +0x04
    void*         mField08;         // +0x08
    unsigned char mState0C;         // +0x0c
    unsigned char mPad0D[3];
    void*         mField10;         // +0x10
    void*         mField14;         // +0x14
    void*         mField18;         // +0x18
    int           mField1C;         // +0x1c
    void*         mField20;         // +0x20
    void*         mField24;         // +0x24
    unsigned char mFlags28;         // +0x28
    unsigned char mPad29[3];
    void*         mField2C;         // +0x2c
};
struct TextureJob {
    void** mpVT;                    // +0x00
    int    mField04;                // +0x04
    void*  mField08;                // +0x08
    void*  mField0C;                // +0x0c
    void*  mField10;                // +0x10
};
struct RehashResult { bool doRehash; unsigned newBucketCount; };
struct HashTable {
    int      mField00;              // +0x00
    void**   mTable;                // +0x04
    unsigned mBucketCount;          // +0x08
    unsigned mCount;                // +0x0c
    int      mPolicy[4];            // +0x10
};
struct JobDesc {
    int           mField00;         // +0x00
    int           mField04;         // +0x04
    unsigned char mFlag08;          // +0x08  (only this byte is written)
    unsigned char mPad09;           // +0x09  (left uninitialised, as in the original)
    unsigned char mPad0A;           // +0x0a
    unsigned char mPad0B;           // +0x0b
    int           mField0C;         // +0x0c
    int           mField10;         // +0x10
    int           mField14;         // +0x14
    int           mField18;         // +0x18
    int           mField1C;         // +0x1c
    int           mField20;         // +0x20
    int           mField24;         // +0x24
    int           mField28;         // +0x28
};
static inline void AddRef(void* p)  { if (p) ((FnV0)(*(void***)p)[0])(p); }
static inline void Release(void* p) { if (p) ((FnV0)(*(void***)p)[1])(p); }
static inline void ReleaseAt10(void* p)
{
    if (!p) return;
    volatile long* rc = (volatile long*)((char*)p + 0x10);
    _InterlockedExchangeAdd(rc, -1);
    long cur = _InterlockedExchangeAdd(rc, 0);
if (cur < 1) _InterlockedExchangeAdd(rc, 1);
else _InterlockedExchangeAdd(rc, 0);
}
struct Empty16 { int a, b, c, d; Empty16(); };
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
void* __cdecl TextureAlloc(unsigned int n, const char* pName, int flags, int align, const char* pFile, int line); // 0x00f473a0
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
extern void* g_emptyBucketArray; // 0x0154df28
extern "C" char SP_SetCachingType(int type, void* p);        // 0x006ac040
extern "C" void AdjustKey(void* pKey, void* pObj);           // 0x006acfe0
extern "C" void StallUntilLoadedFn(void** pOut, int* a, int* b, void* c); // 0x007a98b0
extern "C" void* __fastcall NodeCreate(void* pClassId);   // 0x007aa800
extern "C" void __cdecl gfxFree(void* p);                                   // 0x00f47380
extern "C" int rwArenaNumExported(void* arena);                          // 0x011e23a0
extern "C" void rwArenaExportedByIndex(void* arena, int index, void* pOut); // 0x011e28e0
extern int gMipLodSetting;              // 0x0153bce0
extern int gAppProperties;              // 0x015fd918
extern "C" void cLoadQueueUpdate(void* pQueue);  // 0x007aba40 (cLoadQueue::Update)
extern "C" void RemoveMatching(void* pDeque, void* pKey); // 0x007a9840
extern "C" void TextureEraseNode(void* pMap, void* pNode);            // 0x00b4f930
namespace EA {
namespace Thread {
class Mutex_s007a_bc90 {
public:
    Mutex_s007a_bc90(const void* pParams, bool bDefault);   // 0x009222a0
    ~Mutex_s007a_bc90();
    bool Lock(void* pAttribute);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    void Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
private:
    char mData[0x30];
};
}
}
struct ResManMgr {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual bool GetResource(void* key, int a, int b, int c, int d, int e); // slot 3 (+0xc)
};
extern "C" ResManMgr* ResManager();                    // 0x0067dcd0
class cTextureInstanceInternal;
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
struct cTextureAsyncInfo_s007a_bc90;
struct AsyncDeque;
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
    TextureInstanceMap_s007a_bc90() {
        mRehashPolicy.mfMaxLoadFactor = 1.0f;
        mRehashPolicy.mfGrowthFactor = 2.0f;
        mnBucketCount = 1;
        mpBucketArray = (TextureNode_s007a_bc90**)&g_emptyBucketArray;
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
    ~TextureInstanceMap_s007a_bc90();

    char            mEmpty[4];     // +0x00
    TextureNode_s007a_bc90**   mpBucketArray; // +0x04
    uint32_t        mnBucketCount; // +0x08
    uint32_t        mnElementCount;// +0x0c
    RehashPolicy    mRehashPolicy; // +0x10
    char            mRest[4];      // +0x1c
};
struct CQEntry {           // 0x10-byte queue entry (element ctor 0x007aa620 / dtor 0x007aa660)
    int a, b, c, d;
    CQEntry();
    ~CQEntry();
};
struct CQState {           // POD queue state at +0x44
    int  mData[10];        // +0x00..+0x27
    void Init(int);        // 0x007a9c10
};
class cLoadQueue_s007a_bc90 {
public:
    __declspec(noinline) cLoadQueue_s007a_bc90();              // 0x007ac0f0
    void Schedule(void* pEntry);                    // 0x007abae0
    void*           mpManager;    // +0x00
    CQEntry         mEntries[4];  // +0x04 .. +0x43
    CQState         mQueue;       // +0x44 .. +0x6b
    char            mPad6c[4];    // +0x6c
    int             mField70;     // +0x70
};
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
typedef void (__cdecl *RasterNotifyFn)(void* pRaster, int setting);
class cScopedLock {
public:
    EA::Thread::Mutex_s007a_bc90* mMutex;
    cScopedLock(EA::Thread::Mutex_s007a_bc90* pMutex)
    { mMutex = pMutex; pMutex->Lock(&g_mutexAttribute); }
    ~cScopedLock();     // out-of-line: SP::MutexLock::~MutexLock (0x00697b70)
};
class cTextureManager_s007a_bc90 : public cTmBaseA, public cTmBaseB {
public:
    cTextureManager_s007a_bc90();                              // 0x007ac1e0
    virtual ~cTextureManager_s007a_bc90();
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
    EA::Thread::Mutex_s007a_bc90 mMutex;       // +0x20
    cTmListHead     mList;          // +0x50
    TextureInstanceMap_s007a_bc90 mTextureInstanceMap; // +0x58
    TextureInstanceMap_s007a_bc90 mTextureArenas;      // +0x78
    EA::Thread::Mutex_s007a_bc90 mArenaMutex;  // +0x98
    int             mNumCacheFrames;      // +0xc8
    int             mCurrentMipLodSetting; // +0xcc
    void*           mUnknownD0;     // +0xd0
    cLoadQueue_s007a_bc90      mLoadQueue;     // +0xd4
    char            mTail[0x14];
};
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
struct MtxNode {                        // intrusive list node look-alike at +0x04 of the inst
    int* mpNext;                        // +0x00
    int* mpPrev;                        // +0x04
};
struct cTextureAsyncInfo_s007a_bc90 {
    MtxNode  mList;                     // +0x00 .. +0x07
    void*    mpObject;                  // +0x08
    char     mField0c;
    int      mRefCount;                 // +0x10
    int      mCacheFrames;              // +0x14
    ResourceKey mKey;                   // +0x18
    int*     mpResource;                // +0x24
    uint32_t Setup(ResourceKey* pKey);  // 0x007ab860
};
struct Vec128Ctor { Vec128Ctor(); ~Vec128Ctor(); int mData[2]; };
class TiListHead {                      // intrusive list anchor at +0x50
public:
    TiListHead* mpNext;
    TiListHead* mpPrev;
};
struct AppPropsView {
    int __thiscall GetIntProperty(int id);
    char __thiscall Query(void** pOut, int id);
};
extern AppPropsView* gAppProps;                  // 0x015fd918
struct PropObject {
    int* __thiscall GetInt();                    // 0x0041e990
};
extern "C" void* TextureFindRaw(void* pMap, const ResourceKey* pKey);  // 0x00833840
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
template <class T> void* operator new(unsigned int, T* p) { return p; }
// ---- items of slice s007abc90 end

// ---- items of slice s008337d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_vtblX0;          // 0x141aabc
extern char g_vtblX4;          // 0x141aab8
extern char g_vtblEditorRes;   // 0x13eb938
extern char g_vtblImgTmp;      // 0x13ef094
extern uint32_t g_counter164efec; // 0x164efec
extern char g_htA;             // 0x1547f54
extern void* g_htA_buckets;    // 0x1547f58
extern uint32_t g_htA_count;   // 0x1547f5c
extern uint32_t g_flagF60;     // 0x1547f60
extern char g_htB;             // 0x1547f78
extern void* g_htB_buckets;    // 0x1547f7c
extern uint32_t g_htB_count;   // 0x1547f80
extern uint32_t g_flagF84;     // 0x1547f84
extern "C" void  FUN_00833840(void);
extern "C" void  FUN_008338c0(void);
typedef void   (__thiscall *VFv)(void*);
static inline void** VT(void* o) { return *(void***)o; }
struct TexNode {
    uint32_t k0, k4, k8;  // +0x00 ResourceKey
    void*    value;       // +0x0c
    TexNode* next;        // +0x10
};
struct TexTable {
    uint32_t f0;          // +0x00
    void*    f4;          // +0x04
    uint32_t f8;          // +0x08
    char     pad0c[0x10];
    void*    alloc;       // +0x1c
    uint32_t f20;         // +0x20
    TexNode* CreateNode(const void* src);
    void     Clear(TexNode** buckets, uint32_t count);
};
struct TexMgr {
    void*    vptr0;   // +0x00
    void*    vptr4;   // +0x04
    uint32_t f8;      // +0x08
    TexMgr*  Init();
    void     Dtor();
};
// ---- items of slice s008337d0 end

// ---- items of slice s00832790 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_0011e073e(void);         // operator new[]
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedExchange)
struct RefHolder {
    char  pad[0x10];
    void* p;          // +0x10
    uint32_t GetC();
    uint32_t GetE();
};
struct HashNode { uint32_t key; uint32_t hash; uint32_t field8; uint32_t f0c; HashNode* next; };
struct Hashtable {
    uint32_t   f0;
    HashNode** mpBuckets;   // +0x04
    uint32_t   mnElementCount; // +0x08
    char       pad0c[0x10];
    void*      mpAllocator; // +0x1c
    uint32_t   f20;         // +0x20
    void Rehash(uint32_t nNewBucketCount);
};
// ---- items of slice s00832790 end

// @ 0x007a93b0
void FUN_007a93b0()
{
    void* d = g_D3D9Device;
    ((void(__stdcall*)(void*))(*(void***)d)[0x14 / 4])(d);
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
int* cTextureManager::GetKeyFromTexture(int* out, int tex)
{
    int base = tex ? tex - 8 : 0;
    out[0] = *(int*)(base + 0x18);
    out[1] = *(int*)(base + 0x1c);
    out[2] = *(int*)(base + 0x20);
    return out;
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
void __stdcall FUN_007a95b0(int tex, char flag)
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
        ((int(__thiscall*)(void*))FUN_00690_120_GetStatus)(this->mJob2);
    if (this->mJob) {
        void* job = this->mJob;
        ((void(__thiscall*)(void*))(*(void***)job)[1])(job);
        _ReadWriteBarrier();
    }
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
char cTextureManager::WriteTexture(int tex, int extra, char async)
{
    int base = tex ? tex - 8 : 0;
    if ((*(unsigned char*)(base + 0xc) & 8) == 0)
        return 1;
    ((void(__thiscall*)(void*, int))(*(void***)this)[0x34 / 4])(this, base + 8);
    TextureKey key;
    key.mKey = *(int*)(base + 0x18);
    key.mType = 0x2f4e681c;
    key.mExtra = *(int*)(base + 0x20);
    char ok;
    if (async != 0) {
        ok = ((char(__cdecl*)(int, int, int, TextureKey*))FUN_006b4b60)
            (*(int*)(base + 0x24), extra, 0, &key);
    }
    else {
        void* rm = FUN_0067dcd0_GetManager();
        ok = ((char(__thiscall*)(void*, int, int, int, int, TextureKey*))(*(void***)rm)[0x20 / 4])
            (rm, *(int*)(base + 0x24), 0, (int)async, 0, &key);
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
int** StallUntilLoaded(int** out, int* begin, int* first, int* end, int** map, int* stop, int reserved7, int reserved8, int reserved9, int value)
{
    int* cur = begin;
    int* chunk = first;
    int** m = map;
    int* last = end;
    while (cur != stop && *cur != value) {
        ++cur;
        if (cur == last) {
            ++m;
            cur = *m;
            last = cur + 0x40;
            chunk = cur;
        }
    }
    out[2] = last;
    out[3] = (int*)m;
    out[0] = cur;
    out[1] = chunk;
    return out;
}

// @ 0x007a9a80
DequeIter2& DequeIter2::operator+=(int n)
{
    unsigned int off = (unsigned int)(this->cur - this->first) + n;
    if (off < 0x40) {
        this->cur = this->cur + n;
    } else {
        int chunkIndex = (int)((off + 0x1000000 + ((int)(off + 0x1000000) >> 0x1f & 0x3f)) >> 6) - 0x40000;
        int** slot = this->map + chunkIndex;
        this->map = slot;
        int* base = *slot;
        this->first = base;
        this->last = base + 0x40;
        this->cur = this->first + (off + chunkIndex * -0x40);
    }
    return *this;
}

// @ 0x007a9ae0
void DequeMap::InsertAt(int count, int zero)
{
    int* first = this->mCur;
    int used = ((char*)this->mTailLast - (char*)first) >> 2;
    int n = used + 1;
    int need = n + count;
    unsigned int cap = (unsigned int)this->mCapacity;
    if ((unsigned int)(need * 2) < cap) {
        int* dst = (int*)((char*)this->mpBegin +
            ((int)((cap - need) >> 1) + (~-(unsigned)(zero != 0) & count)) * 4);
        if (dst < first)
            VectorDoInsertValue(dst, first, (used + 1) * 4);
        else
            memmove(dst + (n - (((used + 1) * 4) >> 2)), first, (used + 1) * 4);
    }
    else {
        int cap2 = (this->mCapacity < count) ? count : this->mCapacity;
        int total = cap2 + 2 + (int)cap;
        int* nb = (int*)EASTL_allocator_allocate(total * 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        int* src = (int*)this->mCur;
        int* dst = (int*)((char*)nb + ((((char*)src - (char*)this->mpBegin) >> 2) +
                          (~-(unsigned)(zero != 0) & count)) * 4);
        if (this->mpBegin)
            VectorDoInsertValue(dst, src, this->mTailLast - src + 1);
        if (this->mpBegin)
            EASTL_allocator_deallocate(this->mpBegin);
        this->mpBegin = nb;
        this->mCapacity = total;
    }
    this->mCur = 0;
}

// @ 0x007a9d70
DequeIterator* FUN_007a9d70(DequeIterator* result, DequeIterator first, DequeIterator last, DequeIterator last2)
{
    while (last.mpCurrent != first.mpCurrent) {
        if (last.mpCurrent == last.mpBegin) {
            --last.mpCurrentArrayPtr;
            last.mpBegin = *last.mpCurrentArrayPtr;
            last.mpEnd = last.mpBegin + 0x40;      // EASTL subarray = 64 ints
        }
        --last.mpCurrent;
        if (last2.mpCurrent == last2.mpBegin) {
            --last2.mpCurrentArrayPtr;
            last2.mpBegin = *last2.mpCurrentArrayPtr;
            last2.mpEnd = last2.mpBegin + 0x40;
        }
        --last2.mpCurrent;
        *last2.mpCurrent = *last.mpCurrent;
    }
    result->mpCurrent = last2.mpCurrent;
    result->mpBegin = last2.mpBegin;
    result->mpEnd = last2.mpEnd;
    result->mpCurrentArrayPtr = last2.mpCurrentArrayPtr;
    return result;
}

// @ 0x007a9e10
void* FUN_007a9e10(void* self, int w, int h)
{
    *(void**)self = (void*)VT_PropertyListA;
    *(void**)((char*)self + 4) = 0;
    *(void**)((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = 0;
    *(void**)((char*)self + 0x10) = 0;
    *(void**)((char*)self + 0x14) = 0;
    *(void**)((char*)self + 0x18) = (void*)VT_PropertyListB;
    *(int*)((char*)self + 0x1c) = w;
    *(int*)((char*)self + 0x20) = h;
    *(int*)((char*)self + 0x24) = -1;
    *(void**)((char*)self + 0x28) = 0;
    *(void**)self = (void*)VT_PropertyListC;
    *(void**)((char*)self + 0x18) = (void*)VT_PropertyListB2;
    void* buf = EASTL_allocator_allocate((unsigned)(w * h), "Graphics", 0, 0, 0, 0);
    *(void**)((char*)self + 0x28) = buf;
    *(int*)((char*)self + 0x24) = 1;
    return self;
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

// @ 0x007a9f30
extern "C" bool __fastcall FUN_007a9f30(TexManager* self, int dummy)
{
    (void)dummy;
    if (self->mInitFlag) return false;
    self->mInitFlag = 1;
    self->mField10 = FUN_00761b40();
    self->mField14 = FUN_00761c00();
    if (g_15fd918) {
        int out = 0;
        if (((bool(__thiscall*)(void*, int, void*))(*(void***)g_15fd918)[9])(g_15fd918, 0x2840048, &out)
            && *(short*)((char*)out + 0x12) == 9)
            self->mFieldCC = *FUN_0041e990_GetInt();
    }
    self->mSelfD4 = self;

    unsigned h1 = FUN_00932e80_hash("PlaceholderNormalMap", 0x811c9dc5, 1);
    void* o1 = ((FnP8)(*(void***)self)[15])(self, h1, 0x40002700, 1, 1, 1, 8, 0x15, 0);
    ((void(__thiscall*)(void*, void*))FUN_00576650_Assign)(&self->mNormalMap, o1);
    {
        void* o = self->mNormalMap;
        if (!(*(unsigned char*)((char*)o + 4) & 1)) {
            void* im = FUN_0067dd60();
            ((FnVP)(*(void***)im)[13])(im, o);
        }
    }
    {
        void* o = self->mNormalMap;
        int out = 0;
        if (((int(__thiscall*)(void*, int, int, void*))FUN_011ef750_Open)(*(void**)o, 2, 0, &out)) {
            *(int*)out = 0x7f7fff;
            void* o2 = self->mNormalMap;
            if (!(*(unsigned char*)((char*)o2 + 4) & 1)) {
                void* im = FUN_0067dd60();
                ((FnVP)(*(void***)im)[13])(im, o2);
            }
            ((void(__thiscall*)(void*, void*))FUN_011ef880_Close)(*(void**)o2, &out);
        }
    }
    unsigned h2 = FUN_00932e80_hash("PlaceholderSpecGlossMap", 0x811c9dc5, 1);
    void* o3 = ((FnP8)(*(void***)self)[15])(self, h2, 0x40002700, 1, 1, 1, 8, 0x15, 0);
    ((void(__thiscall*)(void*, void*))FUN_00576650_Assign)(&self->mSpecGlossMap, o3);
    {
        void* o = self->mSpecGlossMap;
        if (!(*(unsigned char*)((char*)o + 4) & 1)) {
            void* im = FUN_0067dd60();
            ((FnVP)(*(void***)im)[13])(im, o);
        }
    }
    {
        void* o = self->mSpecGlossMap;
        int out = 0;
        if (((int(__thiscall*)(void*, int, int, void*))FUN_011ef750_Open)(*(void**)o, 2, 0, &out)) {
            *(int*)out = 0x806464;
            void* o2 = self->mSpecGlossMap;
            if (!(*(unsigned char*)((char*)o2 + 4) & 1)) {
                void* im = FUN_0067dd60();
                ((FnVP)(*(void***)im)[13])(im, o2);
            }
            ((void(__thiscall*)(void*, void*))FUN_011ef880_Close)(*(void**)o2, &out);
        }
    }
    return true;
}

// @ 0x007aa0d0
extern "C" bool __fastcall FUN_007aa0d0(TexManager* self, int dummy, JobSlotGroup* slots, void* mgr)
{
    (void)dummy;
    JobObject* obj = slots ? (JobObject*)((char*)slots - 8) : 0;
    if (obj->mState0C & 1) return true;
    void* dep = obj->mField2C;
    if (dep) {
        ((FnVP)FUN_006913c0_AddWeakDep)(mgr, dep);
        return true;
    }
    void* job = 0;
    void* jm = FUN_0068f4d0();
    if (job) Release(job);
    if (!((FnB1)(*(void***)jm)[4])(jm, &job)) {
        Release(job);
        return false;
    }
    ((FnV1)FUN_009221b0_Lock)(&self->mMutex, 0x140fa10);
    if (!obj->mField2C && !(obj->mState0C & 1))
        ((void(__thiscall*)(void*, void*))FUN_00630540_Assign)(&obj->mField2C, job);
    ((FnV0)FUN_00922270_Unlock)(&self->mMutex);
    if (!(obj->mState0C & 1)) {
        void* d = obj->mField2C;
        if (!d) { Release(job); return false; }
        ((FnVP)FUN_006913c0_AddWeakDep)(mgr, d);
    }
    Release(job);
    return true;
}

// @ 0x007aa200
extern "C" bool __fastcall FUN_007aa200(TexManager* self, int dummy, JobSlotGroup* slots)
{
    (void)dummy;
    JobObject* obj = slots ? (JobObject*)((char*)slots - 8) : 0;
    void* old = obj->mField24;
    if (!old) return false;
    int s08 = *(int*)((char*)old + 8);
    int s0C = *(int*)((char*)old + 0xc);
    int s10 = *(int*)((char*)old + 0x10);
    (void)s08; (void)s0C; (void)s10;
    void* saved = obj->mField24;
    obj->mField24 = 0;
    void* factory = FUN_0067dcd0();
    Release(obj->mField24);
    if (((bool(__thiscall*)(void*, void*, void*, int, int, int, int))(*(void***)factory)[3])(
            factory, &obj->mField24, 0, 0, 0, 0, 0)) {
        ((FnV1)FUN_009221b0_Lock)(&self->mMutex, 0x140fa10);
        void* nv = obj->mField24;
        obj->mField08 = *(void**)((char*)nv + 0x18);
        ((FnV0)FUN_00922270_Unlock)(&self->mMutex);
        Release(saved);
        return true;
    }
    obj->mField24 = saved;
    return false;
}

// @ 0x007aa320
void JobSlots::Clear()
{
    int* self = (int*)this;
    if (self[1]) {
        void* old = (void*)self[1];
        self[1] = 0;
        ((cJobReleaseFn)FUN_00690_120_GetStatus)(old);      // thiscall: this in ecx
    }
    if (self[0]) {
        volatile long* rc = (volatile long*)((char*)self[0] + 0x10);
        self[0] = 0;
        _InterlockedExchangeAdd(rc, -1);
        long cur = _InterlockedExchangeAdd(rc, 0);
        if (cur < 1) _InterlockedExchangeAdd(rc, 1); else _InterlockedExchangeAdd(rc, 0);
    }
    if (self[2]) {
        int* p = (int*)self[2];
        self[2] = 0;
        void** vt = *(void***)p;                            // vtable at *p, slot 1
        ((void(__thiscall*)(void*))vt[1])(p);
    }
    if (self[3]) {
        int* p = (int*)self[3];
        self[3] = 0;
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*))vt[1])(p);
    }
}

// @ 0x007aa3a0
char JobSlots::Transfer(int param_2)
{
    int self = (int)this;
    int* a = *(int**)(self + 0xc);
    if (a && *(int*)(self + 8) == 0) {
        int* b = *(int**)(self + 8);
        if (b) {
            *(int*)(self + 8) = 0;
            void** vt = *(void***)b;
            ((void(__thiscall*)(void*))vt[1])(b);
        }
        void** vt = *(void***)a;                            // slot 5 with &self[2]
        ((void(__thiscall*)(void*, int*))vt[0x14 / 4])(a, (int*)(self + 8));
    }
    int* c = *(int**)(self + 0xc);
    if (c) {
        *(int*)(self + 0xc) = 0;
        void** vt = *(void***)c;
        ((void(__thiscall*)(void*))vt[1])(c);
    }
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

// @ 0x007aa430
extern "C" void __fastcall FUN_007aa430(TexManager* self, int dummy, JobSlotGroup* slots)
{
    (void)dummy;
    JobObject* job = (JobObject*)slots->mSlot0;
    if (!(job->mState0C & 1)) {
        void* ed = slots->mSlot1;
        void* p = 0;
        if (ed) {
            ((FnV0)FUN_006926b0_Cancel)(ed);
            p = *(void**)((char*)slots->mSlot1 + 0x20);
        }
        if (p) {
            if (!(job->mFlags28 & 4)) {
                void* q = *(void**)((char*)p + 4);
                if (((unsigned char)(unsigned)q & 0x1f) == 8) {
                    void* r = *(void**)((char*)p + 8);
                    ((FnV2)(*(void***)r)[11])(r, self->mFieldCC, (int)q);
                }
            }
            job->mField08 = p;
            void* nv = slots->mSlot2;
            void* ov = job->mField24;
            if (nv != ov) {
                AddRef(nv);
                job->mField24 = nv;
                Release(ov);
            }
            if (!(job->mFlags28 & 8)) {
                void* t = slots->mSlot2;
                int arg = t ? ((FnI1)(*(void***)t)[3])(t, 0x355d6f5) : 0;
                FUN_006ac040_SetCachingType(5, (void*)arg);
            }
        } else {
            job->mField08 = self->mField10;
            job->mState0C |= 4;
        }
        job->mState0C |= 1;
    }
    {
        void* r = job->mField2C;
        if (r) {
            ((FnV0)FUN_006909b0_Refresh)(r);
            r = job->mField2C;
            if (r) { job->mField2C = 0; ((FnV0)FUN_00690_120_GetStatus)(r); }
        }
    }
    ((JobSlots*)slots)->Clear();
}

// @ 0x007aa530
extern "C" void __fastcall FUN_007aa530(TextureJob* self, int dummy, int a1, int a2, int a3, int a4)
{
    (void)dummy; (void)a1; (void)a2; (void)a3; (void)a4;
    void* f8 = self->mField08;
    void* x;
    if (f8) {
        if (!(*(unsigned char*)((char*)f8 + 4) & 1)) {
            void* im0 = FUN_0067dd60();
            ((FnVP)(*(void***)im0)[13])(im0, f8);
        }
        x = *(void**)f8;
    } else {
        x = self->mField0C;
    }
    void* tmp = 0;
    void* im = FUN_0067dd60();
    Release(tmp);
    ((void(__thiscall*)(void*, void*, void*, int, int))(*(void***)im)[22])(im, x, &tmp, 0, 0);
    void* f10 = self->mField10;
    void* t = tmp;
    if ((*(int*)((char*)f10 + 0x38) & 1) && *(void**)((char*)f10 + 8))
        Release(*(void**)((char*)f10 + 8));
    *(void**)((char*)f10 + 8) = t;
    AddRef(t);
    *(int*)((char*)f10 + 0x38) |= 1;
    *(void**)((char*)f10 + 0x20) = x;
    void* mm = FUN_0067dcc0();
    void* f10b = self->mField10;
    ((void(__thiscall*)(void*, void*, void*, int, int))(*(void***)mm)[6])(
        mm, *(void**)((char*)f10b + 0x30), f10b, 0, 0);
    Release(tmp);
}

// @ 0x007aa620
Empty16::Empty16()
{
    Empty16* self = this;
    self->a = 0; self->b = 0; self->c = 0; self->d = 0;
}

// @ 0x007aa660
extern "C" void __fastcall FUN_007aa660(JobSlotGroup* self, int dummy)
{
    (void)dummy;
    Release(self->mSlot3);
    Release(self->mSlot2);
    if (self->mSlot1) ((FnV0)FUN_00690_120_GetStatus)(self->mSlot1);
    ReleaseAt10(self->mSlot0);
}

// @ 0x007aa710
extern "C" void* __fastcall FUN_007aa710(HashTable* self, int dummy, int* out, int* key, int unused)
{
    (void)dummy; (void)unused;
    unsigned k = (unsigned)*key;
    unsigned idx = k % self->mBucketCount;
    void* node = self->mTable[idx];
    while (node) {
        if (*(unsigned*)node == k) {
            out[0] = (int)node;
            out[1] = (int)&self->mTable[idx];
            ((unsigned char*)out)[8] = 0;
            return out;
        }
        node = *(void**)((char*)node + 4);
    }
    RehashResult rr;
    rr.doRehash = false; rr.newBucketCount = 0;
    ((void(__thiscall*)(void*, void*, int, int, int))FUN_00921440_Needed)(
        &self->mPolicy, &rr, (int)self->mBucketCount, (int)self->mCount, 1);
    void* n = EASTL_allocator_allocate(8, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (n) *(unsigned*)n = k;
    *(void**)((char*)n + 4) = 0;
    if (rr.doRehash) {
        idx = k % rr.newBucketCount;
        ((void(__thiscall*)(void*, int))FUN_007a99d0_Rehash)(self, (int)rr.newBucketCount);
    }
    *(void**)((char*)n + 4) = self->mTable[idx];
    self->mTable[idx] = n;
    self->mCount++;
    out[0] = (int)n;
    out[1] = (int)&self->mTable[idx];
    ((unsigned char*)out)[8] = 1;
    return out;
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
    _InterlockedExchange(&p->mRef, 1);          // retail: xchg [p+0x10], 1 (not add)
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

// @ 0x007aaa00
extern "C" void __fastcall FUN_007aaa00(TextureJob* self, int dummy, JobSlotGroup* slots, void* refArg, int flag, int kind)
{
    (void)dummy;
    JobObject* obj = slots ? (JobObject*)((char*)slots - 8) : 0;
    if (!(unsigned char)flag) {
        if (!(obj->mState0C & 1))
            ((FnVP)(*(void***)self)[13])(self, (char*)obj + 8);
        ((void(__thiscall*)(void*, void*, void*, int, int))(*(void***)self)[22])(
            self, *(void**)((char*)obj + 8), refArg, 0, 0);
        return;
    }
    if (!kind) kind = 0x522264d;
    void* j = EASTL_allocator_allocate(0x40, "Graphics", 0, 0, 0, 0);
    if (j) {
        *(int*)((char*)j + 0x30) = kind;
        *(void**)j = (void*)0x13eb90c;
        _InterlockedExchange((volatile long*)((char*)j + 4), 0);
        *(void**)j = (void*)0x13eb844;
        *(int*)((char*)j + 0x38) = 0;
    }
    *(void**)((char*)j + 0x10) = *(void**)((char*)obj + 0x20);
    *(void**)((char*)j + 0x18) = *(void**)((char*)obj + 0x18);
    void* k = EASTL_allocator_allocate(0x14, "Graphics", 0, 0, 0, 0);
    if (k) {
        *(void**)k = (void*)0x140faa8;
        _InterlockedExchange((volatile long*)((char*)k + 4), 0);
        *(void**)k = (void*)0x140fab8;
        *(int*)((char*)k + 8) = 0;
        *(int*)((char*)k + 0xc) = 0;
        *(int*)((char*)k + 0x10) = 0;
    }
    AddRef(k);
    {
        void* ov = *(void**)((char*)k + 0x10);
        if (j != ov) {
            Release(j);
            *(void**)((char*)k + 0x10) = j;
            if (ov) ((FnV0)(*(void***)ov)[2])(ov);
        }
    }
    ((void(__thiscall*)(void*, void*))FUN_00576650_Assign)((char*)k + 8, slots);
    *(int*)((char*)k + 0xc) = 0;
    {
        JobDesc desc;
        desc.mField00 = 4;
        desc.mField04 = 0;
        desc.mFlag08  = 1;
        desc.mField0C = 0;
        desc.mField10 = 0;
        desc.mField14 = 0;
        desc.mField18 = 0;
        desc.mField1C = 0;
        desc.mField20 = 0;
        desc.mField24 = 0;
        desc.mField28 = 0;
        void* jm = FUN_0067dd50();
        ((void(__thiscall*)(void*, void*, int, void*))(*(void***)jm)[0x78 / 4])(jm, k, 0, &desc);
    }
    Release(k);
}

// @ 0x007aabb0
bool cTextureManager_s007a_abb0::CreateTextureRaster(Raster* a, void** b, bool c, int d)
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

// @ 0x007aaf90
void cTextureManager_s007a_abb0::UnregisterArena(void* pArena)
{
    EA::Thread::Mutex_s007a_abb0& mtx = mArenaMutex;
    mtx.Lock(&g_mutexAttribute);
    mTextureArenas.erase(pArena);
    mtx.Unlock();
}

// @ 0x007aafc0
bool cTextureManager_s007a_abb0::StallFinishBackgroundLoad(ResourceKey* pKey)
{
    // PARTIAL: EH job-completion path.
    (void)pKey;
    return false;
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

// @ 0x007ab2f0
extern "C" void FUN_007ab2f0(void)
{
    // PARTIAL: ~cTextureManager with EH frame and refcount releases.
}

// @ 0x007ab460
bool SP::cTextureManager::Shutdown()
{
    // PARTIAL: full teardown path.
    return false;
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
bool cTextureManager_s007a_abb0::ReloadTexture(ResourceKey key)
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

// @ 0x007ab730
void SP::cTextureManager::RegisterArenaContents(SP::cArenaResource * pArena)
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

// @ 0x007abc90
void cTextureManager_s007a_bc90::Update()
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

    cTextureAsyncInfo_s007a_bc90* pCur = bChanged ? *(cTextureAsyncInfo_s007a_bc90**)pEnd
                                       : (cTextureAsyncInfo_s007a_bc90*)*ppAnchor;

    nLeft = bChanged ? 0x7fffffff : (int)gMipLodSetting;

    while (pCur != (cTextureAsyncInfo_s007a_bc90*)pEnd && nLeft != 0)
    {
        cTextureAsyncInfo_s007a_bc90* pNext = (cTextureAsyncInfo_s007a_bc90*)pCur->mList.mpNext;
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

// @ 0x007ac080
void*& TextureInstanceMap_s007a_bc90::operator[](const ResourceKey& key)
{
    HashIterator it = find(key);
    if (it.mpNode == mpBucketArray[mnBucketCount])
        it = DoInsertValue(TextureValue(key, 0), true_type()).it;
    return ((TextureNode_s007a_bc90*)it.mpNode)->second;
}

// @ 0x007ac0f0
cLoadQueue_s007a_bc90::cLoadQueue_s007a_bc90()
: mpManager(0), mEntries(), mQueue()
{
    mQueue.Init(0);
    mField70 = 0;
}

// @ 0x007ac2f0
void* cTextureManager_s007a_bc90::CreateInstance(ResourceKey* key, void* pResource, void* pRaster, uint32_t flags, char b)
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
void* cTextureManager_s007a_bc90::RegisterBuiltInGameTexture(void* p1, uint32_t flags)
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
void* cTextureManager_s007a_bc90::GetTextureSync(ResourceKey key, int flags)
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
void* cTextureManager_s007a_bc90::GetTextureAsync(ResourceKey key, int flags)
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
void* cTextureManager_s007a_bc90::StallUntilLoadedUnderLock(ResourceKey* key)
{
    cLoadQueue_s007a_bc90* q = &mLoadQueue;                // this in ecx; the queue's own fields are used

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
                    ((cTextureAsyncInfo_s007a_bc90*)pSlot)->Setup((ResourceKey*)q->mQueue.mData);
                    ((AsyncDeque*)((char*)q + 0x44))->erase(*(DqIterB*)pSlot);
                    ((cTextureManager_s007a_bc90*)q->mpManager)->StallFinishBackgroundLoad(pSlot);
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
        ((cTextureManager_s007a_bc90*)q->mpManager)->StallFinishBackgroundLoad(pSlot);
        if (pSlot->a == 0)
            continue;
        // restart from the top of the outer loop (the slot is now busy)
        continue;
    }
}

// @ 0x007aca00
void* cTextureManager_s007a_bc90::CreateGameTextureFromSerializer(void* arg0, void* arg1, void* arg2, uint32_t flags)
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
void* cTextureManager_s007a_bc90::CreateGameTextureRaw(void* arg0, void* arg1, uint32_t key, uint32_t flags)
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

// @ 0x007acbb0
extern "C" void FUN_007acbb0(void)
{
    // PARTIAL: cTextureManager::GetTexture (EH, map find + sync/async load).
}

// @ 0x007acd90
extern "C" void FUN_007acd90(void)
{
    // PARTIAL: cTextureManager::StallUntilLoaded (EH).
}

// @ 0x008332a0
uint32_t RefHolder::GetC()
{
    void* p = *(void**)((char*)this + 0x10);
    if ((*(uint8_t*)((char*)p + 4) & 1) == 0) {
        void* m = FUN_0067dd60();
        ((void (__thiscall*)(void*, void*))VT(m)[0x34 / 4])(m, p);
    }
    return *(uint16_t*)((char*)(*(void**)p) + 0xc);
}

// @ 0x008332d0
uint32_t RefHolder::GetE()
{
    void* p = *(void**)((char*)this + 0x10);
    if ((*(uint8_t*)((char*)p + 4) & 1) == 0) {
        void* m = FUN_0067dd60();
        ((void (__thiscall*)(void*, void*))VT(m)[0x34 / 4])(m, p);
    }
    return *(uint16_t*)((char*)(*(void**)p) + 0xe);
}

// @ 0x00833300
void Hashtable::Rehash(uint32_t nNewBucketCount)
{
    uint32_t size = nNewBucketCount * 4;
    HashNode** pNew = (HashNode**)((void* (__thiscall*)(void*, uint32_t, int, uint32_t))
        VT(mpAllocator)[8 / 4])(mpAllocator, f20, 0, size + 4);
    ((void (__cdecl*)(void*, int, uint32_t))FUN_0011e073e)(pNew, 0, size);
    *(uint32_t*)((char*)pNew + size) = 0xffffffff;
    for (uint32_t i = 0; i < mnElementCount; ++i) {
        HashNode* node = mpBuckets[i];
        while (node != 0) {
            uint32_t b = (node->hash ^ node->key) % nNewBucketCount;
            mpBuckets[i] = node->next;
            node->next = pNew[b];
            pNew[b] = node;
            node = mpBuckets[i];
        }
    }
    if (mnElementCount > 1)
        ((void (__thiscall*)(void*, HashNode**, uint32_t))VT(mpAllocator)[0xc / 4])
            (mpAllocator, mpBuckets, mnElementCount * 4 + 4);
    mpBuckets = pNew;
    mnElementCount = nNewBucketCount;
}

// @ 0x008337d0
TexNode* TexTable::CreateNode(const void* src)
{
    void* alloc = *(void**)((char*)this + 0x1c);
    TexNode* node = (TexNode*)((void* (__thiscall*)(void*, int, int, int))VT(alloc)[8 / 4])
        (alloc, 0x14, 0, *(int*)((char*)this + 0x20));
    if (node) {
        node->k0 = *(uint32_t*)((char*)src + 0);
        node->k4 = *(uint32_t*)((char*)src + 4);
        node->k8 = *(uint32_t*)((char*)src + 8);
        void* v = *(void**)((char*)src + 0xc);
        node->value = v;
        if (v)
            ((VFv)VT(v)[0 / 4])(v);
    }
    *(uint32_t*)((char*)node + 0x10) = 0;
    return node;
}

// @ 0x00833a20
void TexTable::Clear(TexNode** buckets, uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i) {
        TexNode* node = buckets[i];
        while (node != 0) {
            TexNode* cur = node;
            void* v = *(void**)((char*)cur + 0xc);
            node = node->next;
            if (v)
                ((VFv)VT(v)[4 / 4])(v);
            void* alloc = *(void**)((char*)this + 0x1c);
            ((void (__thiscall*)(void*, TexNode*, int))VT(alloc)[0xc / 4])(alloc, cur, 0x14);
        }
        buckets[i] = 0;
    }
}

// @ 0x00833a80
void TexMgr::Dtor()
{
    *(void* volatile*)((char*)this + 0) = &g_vtblX0;
    *(void* volatile*)((char*)this + 4) = &g_vtblX4;
    if (--g_counter164efec == 0) {
        ((TexTable*)&g_htA)->Clear((TexNode**)g_htA_buckets, g_htA_count);
        g_flagF60 = 0;
        ((TexTable*)&g_htB)->Clear((TexNode**)g_htB_buckets, g_htB_count);
        g_flagF84 = 0;
    }
    *(void* volatile*)((char*)this + 0) = &g_vtblEditorRes;
    *(void* volatile*)((char*)this + 4) = &g_vtblImgTmp;
}

// @ 0x00833af0
void* FUN_00833af0(void* self, void* key)
{
    int local_1c[3];
    ((void (__cdecl*)(int*, void*))FUN_00833840)(local_1c, key);
    if (local_1c[0] != *(int*)(*(int*)((char*)self + 4) + *(int*)((char*)self + 8) * 4))
        return (char*)local_1c[0] + 0xc;
    int local_10 = *(int*)key;
    int local_c  = *(int*)((char*)key + 4);
    int local_8  = *(int*)((char*)key + 8);
    int* local_4 = 0;
    ((void (__cdecl*)(int*, int*, int*))FUN_008338c0)(local_1c, &local_10, (int*)((uint32_t)key & 0xffffff00));
    if (local_4)
        ((VFv)VT(local_4)[4 / 4])(local_4);
    return (char*)local_1c[0] + 0xc;
}

// @ 0x00833ba0
__declspec(noinline) bool FUN_00833ba0(void* param_1, int param_2, void* param_3, float param_4, float param_5)
{
    (void)param_1; (void)param_3; (void)param_4; (void)param_5;
    g_counter164efec = g_counter164efec + (uint32_t)param_2;
    return false;
}

// @ 0x00834000
void __stdcall FUN_00834000(int a1, int a2, int a3)
{
    ((void (__stdcall*)(int, int, int, int, int))FUN_00833ba0)(a1, a2, a3, -1, -1);
}
