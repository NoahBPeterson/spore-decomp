// src/game/UTFSpore_Win32/Manager.cpp -- migrated from slice(s) s008e1d50, s008de020 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Manager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Manager.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Thread/Mutex.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void RBTreeInsert_impl(void*, void*, void*, int); // 0x009216a0
extern "C" void* Fn921440(void*, void*, void*, int);          // 0x00921440
extern "C" void* EA_Allocator_GetDefaultAllocator();         // 0x00925cb0
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" void FixedAllocatorCtor(void* pThis, int a, int b, int c, int d, int e,
                                   void* f, void* g, int h); // 0x00926720
extern "C" int FixedAllocatorAddCore(void* pThis, int a, int b); // 0x00926650
#include <new>
#include <string.h>
#include "EA/Allocator/ZoneObject.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/Allocator/StackAllocator.h"
#include <intrin.h>
#pragma intrinsic(_InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange, _InterlockedExchangeAdd)

// ---- items of slice s008de020 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
extern "C" char (*g_154c464)(void*, void*, void*, void*, void*, int);                            // 0x0154c464
namespace EA {
namespace Thread {
struct Mutex_s008d_e020 {
    char pad[0x30];
    void Lock(const char* pName);   // 0x009221b0
    int Unlock();                   // 0x00922270
    Mutex_s008d_e020(int a = 0, int b = 0);    // 0x009222a0
};
}
}
namespace EA {
namespace ResourceMan {
struct KeyFilter_s008d_e020;
}
}
namespace EA {
namespace ResourceMan {
struct ChangeNotificationInfo_s008d_e020 {
    void* mpFunction;       // +0x00
    void* mpContext;        // +0x04
    KeyFilter_s008d_e020* mpKeyFilter; // +0x08
    int mnPriority;         // +0x0c
};
}
}
namespace EA {
namespace ResourceMan {
struct ChangeNotificationInfoCompare_s008d_e020 {
    bool operator()(const ChangeNotificationInfo_s008d_e020& a, const ChangeNotificationInfo_s008d_e020& b) const;  // 0x008de1e0 (EA::ResourceMan::ChangeNotificationInfoCompare::operator)
};
}
}
namespace EA {
namespace ResourceMan {
struct CacheRes;
}
}
namespace EA {
namespace ResourceMan {
struct Manager_s008d_e020 {
    void** vftable;                 // +0x00
    bool mbInitialized;             // +0x04
    char pad05[3];
    void* mpAllocator;              // +0x08
    char pad0C[0x20];               // +0x0c .. +0x2b
    void* mDatabaseList;            // +0x2c (root of the database linked tree)
    char pad30[0x9c - 0x30];
    void** mCompressorBegin;        // +0x9c
    void** mCompressorEnd;          // +0xa0
    char padA4[0x148 - 0xa4];
    Thread::Mutex_s008d_e020 mNameMutex;       // +0x148

    char Fn8de230(int a, int b, int c, int d);  // 0x008de230 (EA::ResourceMan::Manager::Fn8de230)
    bool GetLoadedResource(int a, int b);  // 0x008de280 (EA::ResourceMan::Manager::GetLoadedResource)
    bool IsDatabaseRegistered(int a, void** pOut);  // 0x008de2d0 (EA::ResourceMan::Manager::IsDatabaseRegistered)
    void* FindDatabase(int a);  // 0x008de310 (EA::ResourceMan::Manager::FindDatabase)
    void* Fn8de360(int a);  // 0x008de360 (EA::ResourceMan::Manager::Fn8de360)
    bool Fn8de3b0(int a, int b);  // 0x008de3b0 (EA::ResourceMan::Manager::Fn8de3b0)
    void Fn8de400(void* p, int a);  // 0x008de400 (EA::ResourceMan::Manager::Fn8de400)
    char CheckCacheInternal(CacheRes* p1, void* p2, void** ppOut, char flag);  // 0x008de9d0 (EA::ResourceMan::Manager::CheckCacheInternal)
    char Fn8dead0(void* pArg2, int a3, void* pArg4, void* pArg5, void* pArg6);
    void DoDatabaseChanged(int a, void* pList);  // 0x008debf0 (EA::ResourceMan::Manager::DoDatabaseChanged)
};
}
}
namespace EA {
namespace ResourceMan {
struct DbNode {
    DbNode* mpNext;     // +0x00
    void* mpObject;     // +0x04
    void* mpValue;      // +0x08
};
}
}
namespace EA {
namespace ResourceMan {
struct DbList {
    DbNode* mpHead;     // +0x00
};
}
}
namespace EA {
namespace ResourceMan {
struct IAllocatorV {
    virtual void a0();
    virtual void a1();
    virtual void* Allocate(size_t, int, const char*);   // +0x08
    virtual void Deallocate(void*, size_t);             // +0x0c
};
}
}
namespace EA {
namespace ResourceMan {
struct InternalDatabaseList_s008d_e020 {
    struct Node {
        Node* mpNext;       // +0x00
        void* mpValue;      // +0x04
        int mnPriority;     // +0x08
    };

    Node mAnchor;                              // +0x00
    Thread::Mutex_s008d_e020 mWriteMutex;                 // +0x10
    void** mpBegin;                            // +0x40
    void** mpEnd;                              // +0x44
    void** mpCapacity;                         // +0x48
    IAllocatorV* mpCoreAllocator;              // +0x4c
    const char* mpName;                        // +0x50

    InternalDatabaseList_s008d_e020(int a);  // 0x008de8e0 (EA::ResourceMan::InternalDatabaseList::InternalDatabaseList_s008d_e020)
    void Add(void* pDatabase, int a);  // 0x008de940 (EA::ResourceMan::InternalDatabaseList::Add)
};
}
}
namespace eastl_shim {
struct RbNode {
    RbNode* mpNodeRight;    // +0x00
    RbNode* mpNodeLeft;     // +0x04
    RbNode* mpNodeParent;   // +0x08
    uint32 mnColor;         // +0x0c
};
}
namespace eastl_shim {
struct IAllocatorV {
    virtual void a0();
    virtual void a1();
    virtual void* Allocate(size_t, int, const char*);   // +0x08
    virtual void Deallocate(void*, size_t);             // +0x0c
};
}
namespace eastl_shim {
struct ChangeSet {
    uint32 mUnk0;              // +0x00
    RbNode mAnchor;            // +0x04 (right@+4, left@+8, parent@+0x0c, color@+0x10)
    uint32 mnSize;             // +0x14
    IAllocatorV* mpAllocator;  // +0x18
    const char* mpName;        // +0x1c

    void DoFreeNodes(RbNode* node);   // @ 0x008de4f0
    void LowerBound(void** ppOut, const uint32* pKey); // @ 0x008de450
};
}
struct HashBase {
    uint32 mUnk0;               // +0x00
    void** mpBucketArray;       // +0x04
    uint32 mnBucketCount;       // +0x08
    uint32 mnElementCount;      // +0x0c
    uint32 mRehash[3];          // +0x10
    EA::ResourceMan::IAllocatorV* mpAllocator;  // +0x1c
    const char* mpName;         // +0x20

    void DoRehash1(uint32 n);   // @ 0x008de530
    void DoRehash2(uint32 n);   // @ 0x008de5e0
    void DoRehash3(uint32 n);   // @ 0x008de690
    void DoFreeNodes(void** pBucketArray, uint32 n); // @ 0x008de7f0
    void HashBase_Insert(void** ppResult, uint32* pKey, uint32 extra); // @ 0x008ded00
};
struct AutoRefObj {
    void* mpObject;     // +0x00
    int mField;         // +0x04

    AutoRefObj& operator=(const AutoRefObj& src);   // 0x008dee30
};
namespace EA {
namespace ResourceMan {
struct CacheRes {
    virtual void v0();
    virtual void Release();                 // +0x04
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual char Convert(CacheRes** ppOut); // +0x14
};
}
}
namespace EA {
namespace ResourceMan {
struct CacheSrc {
    virtual void v0();
    virtual void Release();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual char Lookup(void* pKey, CacheRes** ppOut); // +0x14
};
}
}
namespace EA {
namespace ResourceMan {
struct CacheRef {   // AutoRefCount<T> wrapper
    CacheRes* mp;
    CacheRes** AsPPTypeParam();             // 0x00a16f40
};
}
}
namespace EA {
namespace ResourceMan {
extern CacheSrc* Fn8d5d00_src();            // 0x008d5d00 (cdecl, returns CacheSrc*)
}
}
namespace EA {
namespace ResourceMan {
struct Key3 { uint32 v0, v1, v2; };
}
}
namespace EA {
namespace ResourceMan {
struct ResObj {                       // vtable slots used: 2 (+8), 9 (+0x24), 10 (+0x28)
    virtual void p0();
    virtual void p1();
    virtual void Release();           // +0x08
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void Vf24();              // +0x24
    virtual char Vf28(void* a, ResObj* b, int c, uint32 d); // +0x28
};
}
}
namespace EA {
namespace ResourceMan {
struct DbObj {                        // slots used: 13 (+0x34), 16 (+0x40)
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual char Vf34(Key3* pKey, ResObj** ppOut, int a, int b, int c, int d); // +0x34
    virtual void p14();
    virtual void p15();
    virtual void Vf40(Key3* pKey);    // +0x40
};
}
}
struct Vec8 {
    AutoRefObj* mpBegin;    // +0x00
    AutoRefObj* mpEnd;      // +0x04
    AutoRefObj* mpCapacity; // +0x08
    EA::ResourceMan::IAllocatorV* mpAllocator; // +0x0c

    void Fn8decb0();        // @ 0x008decb0
};
struct RbTree {
    char pad00[0x14];
    uint32 mnSize;          // +0x14
    EA::ResourceMan::IAllocatorV* mpAllocator;  // +0x18
    const char* mpName;     // +0x1c
    char pad20[4];
    RbTree* mpAnchor;       // +0x24-ish (not modeled precisely)

    void DoInsertValueImpl(void* p2, char* pPos, void* pValue, char flag); // @ 0x008dee90
};
struct AutoRefVec {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    void* mpAllocator;  // +0x0c
    void* mpName;       // +0x10

    void* Fn8def20(int n, void* pAllocPair); // @ 0x008def20
};
// ---- items of slice s008de020 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* RBTreeIncrement_impl(void*);        // 0x00921580

// ---- items of slice s008e1d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vtbl_Manager[];     // 0x1436ae8
extern char vtbl_ZBase[];       // 0x13effb8
extern void* gEmptyBuckets[];   // 0x154df28
struct CAlloc {
    virtual void a0();
    virtual void a1();
    virtual void* Alloc(unsigned size, const char* name, unsigned flags);   // +8
    virtual void Free(void* p, unsigned size);                              // +0xc
};
CAlloc* __cdecl GetDefaultAllocator();   // 0x925cb0
struct IFactory {
    virtual void* Del(unsigned flags);
    virtual void OnAdded();
    virtual void OnRemoved();
    volatile long mRef;     // +4
};
inline void AddRefF(IFactory* p)
{
    if (p)
        _InterlockedExchangeAdd(&p->mRef, 1);
}
inline void ReleaseF(IFactory* p)
{
    if (p) {
        if (_InterlockedExchangeAdd(&p->mRef, -1) - 1 == 0) {
            _InterlockedExchange(&p->mRef, 1);
            p->Del(1);
        }
    }
}
struct FEntry {
    IFactory* mp;
    int mPriority;
};
struct FactoryVec {
    FEntry* mpBegin;    // +0
    FEntry* mpEnd;      // +4
    FEntry* mpCap;      // +8
    CAlloc* mpAlloc;    // +0xc
    int mFlags;         // +0x10
    FactoryVec(CAlloc* a) : mpBegin(0), mpEnd(0), mpCap(0), mpAlloc(a), mFlags(0) {}
    void insert(FEntry* where, const FEntry& v);        // 0x8e1690
    void DoInsertValue(FEntry* where, const FEntry& v); // 0x8e12c0
    void DestroyRange(FEntry* first, FEntry* last);     // 0x8dede0
    ~FactoryVec()
    {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin)
            mpAlloc->Free(mpBegin, (unsigned)(((char*)mpCap - (char*)mpBegin) >> 3) * 8);
    }
};
void __cdecl MoveDown(FEntry* first, FEntry* last, FEntry* dest);   // 0x8defe0
struct ZBase {
    void* vt;
    ~ZBase() { vt = vtbl_ZBase; }
};
struct RBAnchor {
    void* right;
    void* left;
    void* parent;
    int color;
    RBAnchor() : left(0), parent(0), color(0) {}
};
struct RBSet {
    uint8_t mCompare;       // +0 (padded to 4)
    RBAnchor mAnchor;       // +4
    int mnSize;             // +0x14
    CAlloc* mpAlloc;        // +0x18
    int mnFlags;            // +0x1c
    void DoNuke(void* root);    // 0x8de4f0
    RBSet(CAlloc* a) : mCompare(0), mpAlloc(a), mnFlags(0)
    {
        mAnchor.right = &mAnchor;
        mAnchor.left = &mAnchor;
        mAnchor.parent = 0;
        *(char*)&mAnchor.color = 0;
        mnSize = 0;
    }
    ~RBSet() { DoNuke(mAnchor.parent); }
};
struct HTBase {
    uint32_t pad0;
    void** mpBuckets;       // +4
    unsigned mnBuckets;     // +8
    unsigned mnElems;       // +0xc
    float mfMaxLoad;        // +0x10
    float mfGrowth;         // +0x14
    unsigned mnNextResize;  // +0x18
    CAlloc* mpAlloc;        // +0x1c
    int mFlags;             // +0x20
    HTBase(CAlloc* a) : mnBuckets(1), mnElems(0), mfMaxLoad(1.0f), mfGrowth(2.0f), mnNextResize(0), mpAlloc(a), mFlags(0)
    {
        mpBuckets = gEmptyBuckets;
    }
};
template <int N>
struct HT : HTBase {
    HT(CAlloc* a) : HTBase(a) {}
    void DoFreeNodes(void** buckets, unsigned n);
    ~HT()
    {
        DoFreeNodes(mpBuckets, mnBuckets);
        mnElems = 0;
        if (mnBuckets > 1)
            mpAlloc->Free(mpBuckets, mnBuckets * 4 + 4);
    }
};
struct IDBList {
    char d[0x78];
    IDBList(CAlloc* a);     // 0x8de8e0
    ~IDBList();             // 0x8e1420
};
struct StackAllocator {
    char d[0x20];
    StackAllocator(CAlloc* a, unsigned size, unsigned align);   // 0x925f30
    ~StackAllocator();                                          // 0x925e60
};
struct Mutex2 {
    char d[0x30];
    Mutex2(void*, bool);    // 0x9222a0
    ~Mutex2();              // 0x922130
};
struct ZBase1 : ZBase {
    ZBase1() { vt = vtbl_Manager; }
};
struct ManagerX : ZBase1 {
    bool mbInitialized;             // +4
    CAlloc* mpAllocator;            // +8
    RBSet mFunctionInfoSet;         // +0xc
    IDBList* mpDatabaseList;        // +0x2c
    HT<1> mTypeToFactoryMap;        // +0x30
    HT<2> mResourceToRecordMap;     // +0x54
    HT<3> mTable78;                 // +0x78
    FactoryVec mFactories;          // +0x9c (pair<AutoRefCount<Factory>,int> vector)
    HT<4> mTableB0;                 // +0xb0
    StackAllocator mStack;          // +0xd4
    HT<5> mNameMap;                 // +0xf4
    Mutex2 mNameMutex;              // +0x118
    Mutex2 mMutex;                  // +0x148

    ManagerX(CAlloc* alloc);
    ~ManagerX();
    bool RegisterFactory(bool bAdd, IFactory* f, int prio);
    void ResetAll();
};
// ---- items of slice s008e1d50 end

// @ 0x008de1e0
bool EA::ResourceMan::ChangeNotificationInfoCompare_s008d_e020::operator()( const EA::ResourceMan::ChangeNotificationInfo_s008d_e020& a, const EA::ResourceMan::ChangeNotificationInfo_s008d_e020& b) const
{
    if (a.mnPriority != b.mnPriority) return b.mnPriority < a.mnPriority;
    if (a.mpFunction != b.mpFunction) return a.mpFunction < b.mpFunction;
    if (a.mpContext != b.mpContext) return a.mpContext < b.mpContext;
    return a.mpKeyFilter < b.mpKeyFilter;
}

// @ 0x008de220
bool EA::ResourceMan::Manager::Init()
{
    if (!mbInitialized) mbInitialized = true;
    return true;
}

// @ 0x008de230
char EA::ResourceMan::Manager_s008d_e020::Fn8de230(int a, int b, int c, int d)
{
    char r = g_154c464((void*)a, (void*)b, (void*)c, (void*)d, this, 0);
    if (r) {
        void** vt = *(void***)this;
        typedef void (__thiscall *Fn)(void*, void*, void*);
        ((Fn)vt[0x80 / 4])(this, (void*)a, (void*)b);
    }
    return r;
}

// @ 0x008de280
bool EA::ResourceMan::Manager_s008d_e020::GetLoadedResource(int a, int b)
{
    void** it = mCompressorBegin;
    void** end = mCompressorEnd;
    while (it != end) {
        void* c = *it;
        void** vt = *(void***)c;
        typedef bool (__thiscall *Fn)(void*, int, int);
        if (((Fn)vt[0x18 / 4])(c, a, b)) return true;
        it += 2;
    }
    return false;
}

// @ 0x008de2d0
bool EA::ResourceMan::Manager_s008d_e020::IsDatabaseRegistered(int a, void** pOut)
{
    EA::ResourceMan::DbNode* n = ((EA::ResourceMan::DbList*)mDatabaseList)->mpHead;
    for (;;) {
        if (!n) return false;
        if ((int)n->mpObject == a) {
            if (pOut) *pOut = n->mpValue;
            return true;
        }
        n = n->mpNext;
    }
}

// @ 0x008de310
void* EA::ResourceMan::Manager_s008d_e020::FindDatabase(int a)
{
    EA::ResourceMan::DbNode* n = ((EA::ResourceMan::DbList*)mDatabaseList)->mpHead;
    if (!n) return 0;
    do {
        void* db = n->mpObject;
        void** vt = *(void***)db;
        typedef bool (__thiscall *Fn)(void*, int, int, int, int, int, int);
        if (((Fn)vt[0x34 / 4])(db, a, 0, 1, 6, 1, 0)) return db;
        n = n->mpNext;
    } while (n);
    return 0;
}

// @ 0x008de360
void* EA::ResourceMan::Manager_s008d_e020::Fn8de360(int a)
{
    void** it = mCompressorBegin;
    void** end = mCompressorEnd;
    while (it != end) {
        void* c = *it;
        void** vt = *(void***)c;
        typedef bool (__thiscall *Fn)(void*, int, int);
        if (((Fn)vt[0x18 / 4])(c, a, 0)) return c;
        it += 2;
    }
    return 0;
}

// @ 0x008de3b0
bool EA::ResourceMan::Manager_s008d_e020::Fn8de3b0(int a, int b)
{
    void** it = mCompressorBegin;
    void** end = mCompressorEnd;
    while (it != end) {
        void* c = *it;
        void** vt = *(void***)c;
        typedef bool (__thiscall *Fn)(void*, int, int);
        if (((Fn)vt[0x1c / 4])(c, a, b)) return true;
        it += 2;
    }
    return false;
}

// @ 0x008de400
void EA::ResourceMan::Manager_s008d_e020::Fn8de400(void* p, int a)
{
    if (p) {
        void** vt = *(void***)p;
        typedef void (__thiscall *Fn)(void*, int);
        ((Fn)vt[0x28 / 4])(p, a);
        return;
    }
    void** it = mCompressorBegin;
    void** end = mCompressorEnd;
    if (it == end) return;
    do {
        void* c = *it;
        void** vt = *(void***)c;
        typedef void (__thiscall *Fn)(void*, int);
        ((Fn)vt[0x28 / 4])(c, a);
        it += 2;
    } while (it != end);
}

// @ 0x008de450
namespace eastl_shim {
void ChangeSet::LowerBound(void** ppOut, const uint32* pKey)
{
    char* pAnchor = (char*)this + 4;
    char* p = *(char**)((char*)this + 0xc);
    char* pParent = pAnchor;
    if (p) {
        do {
            uint32* n = (uint32*)p;
            bool less;
            if (pKey[3] == n[7]) {
                less = n[4] < pKey[0];
                if (n[4] == pKey[0]) {
                    less = n[5] < pKey[1];
                    if (n[5] == pKey[1]) less = n[6] < pKey[2];
                }
            } else {
                less = (int)pKey[3] < (int)n[7];
            }
            char* next;
            if (less) {
                next = *(char**)n;                       // mpNodeRight
            } else {
                next = *(char**)((char*)n + 4);          // mpNodeLeft
                pParent = p;
            }
            p = next;
        } while (p);
    }
    if (pParent != pAnchor) {
        uint32* n = (uint32*)pParent;
        bool less;
        if (n[7] == pKey[3]) {
            less = pKey[0] < n[4];
            if (pKey[0] == n[4]) {
                less = pKey[1] < n[5];
                if (pKey[1] == n[5]) less = pKey[2] < n[6];
            }
        } else {
            less = (int)n[7] < (int)pKey[3];
        }
        if (!less) { *ppOut = pParent; return; }
    }
    *ppOut = pAnchor;
}
}  // namespace eastl_shim

// @ 0x008de4f0
namespace eastl_shim {
void ChangeSet::DoFreeNodes(RbNode* node)
{
    while (node) {
        DoFreeNodes(node->mpNodeRight);
        RbNode* next = node->mpNodeLeft;
        mpAllocator->Deallocate(node, 0x20);
        node = next;
    }
}
}  // namespace eastl_shim

// @ 0x008de530
void HashBase::DoRehash1(uint32 n)
{
    size_t size = n * 4;
    void** pNew = (void**)mpAllocator->Allocate(size + 4, 0, mpName);
    memset(pNew, 0, size);
    *(uint32*)((char*)pNew + size) = 0xffffffff;
    for (uint32 i = 0; i < mnBucketCount; ++i) {
        char* node;
        while ((node = (char*)mpBucketArray[i]) != 0) {
            uint32 hash = *(uint32*)node;
            mpBucketArray[i] = *(void**)(node + 8);
            *(void**)(node + 8) = pNew[hash % n];
            pNew[hash % n] = node;
        }
    }
    if (mnBucketCount > 1) mpAllocator->Deallocate(mpBucketArray, mnBucketCount * 4 + 4);
    mpBucketArray = pNew;
    mnBucketCount = n;
}

// @ 0x008de5e0
void HashBase::DoRehash2(uint32 n)
{
    size_t size = n * 4;
    void** pNew = (void**)mpAllocator->Allocate(size + 4, 0, mpName);
    memset(pNew, 0, size);
    *(uint32*)((char*)pNew + size) = 0xffffffff;
    for (uint32 i = 0; i < mnBucketCount; ++i) {
        char* node;
        while ((node = (char*)mpBucketArray[i]) != 0) {
            uint32 hash = *(uint32*)node;
            mpBucketArray[i] = *(void**)(node + 0x14);
            *(void**)(node + 0x14) = pNew[hash % n];
            pNew[hash % n] = node;
        }
    }
    if (mnBucketCount > 1) mpAllocator->Deallocate(mpBucketArray, mnBucketCount * 4 + 4);
    mpBucketArray = pNew;
    mnBucketCount = n;
}

// @ 0x008de690
void HashBase::DoRehash3(uint32 n)
{
    size_t size = n * 4;
    void** pNew = (void**)mpAllocator->Allocate(size + 4, 0, mpName);
    memset(pNew, 0, size);
    *(uint32*)((char*)pNew + size) = 0xffffffff;
    for (uint32 i = 0; i < mnBucketCount; ++i) {
        char* node;
        while ((node = (char*)mpBucketArray[i]) != 0) {
            uint32 hash = *(uint32*)(node + 8) ^ *(uint32*)node;
            mpBucketArray[i] = *(void**)(node + 0x1c);
            *(void**)(node + 0x1c) = pNew[hash % n];
            pNew[hash % n] = node;
        }
    }
    if (mnBucketCount > 1) mpAllocator->Deallocate(mpBucketArray, mnBucketCount * 4 + 4);
    mpBucketArray = pNew;
    mnBucketCount = n;
}

// @ 0x008de7f0
void HashBase::DoFreeNodes(void** pBucketArray, uint32 n)
{
    for (uint32 i = 0; i < n; ++i) {
        char* node = (char*)pBucketArray[i];
        while (node) {
            char* next = *(char**)(node + 8);
            mpAllocator->Deallocate(node, 0xc);
            node = next;
        }
        pBucketArray[i] = 0;
    }
}

// @ 0x008de840
void* Fn8de840(void** ppOut, AutoRefObj* first, AutoRefObj* last, AutoRefObj* dest)
{
    *ppOut = dest;
    for (; first != last; ++first) {
        AutoRefObj* out = (AutoRefObj*)*ppOut;
        if (out) {
            AutoRefObj* src = first;
            out->mpObject = src->mpObject;
            if (src->mpObject) {
                void** vt = *(void***)src->mpObject;
                typedef void (__thiscall *Fn)(void*);
                ((Fn)vt[1])(src->mpObject);
            }
            out->mField = src->mField;
        }
        *ppOut = (char*)*ppOut + 8;
    }
    return ppOut;
}

// @ 0x008de890
AutoRefObj* Fn8de890(AutoRefObj* first, AutoRefObj* last, AutoRefObj* dest)
{
    if (first == last) return dest;
    do {
        if (dest) {
            dest->mpObject = first->mpObject;
            if (first->mpObject) {
                void** vt = *(void***)first->mpObject;
                typedef void (__thiscall *Fn)(void*);
                ((Fn)vt[1])(first->mpObject);
            }
            dest->mField = first->mField;
        }
        ++first;
        ++dest;
    } while (first != last);
    return dest;
}

// @ 0x008de8e0
EA::ResourceMan::InternalDatabaseList_s008d_e020::InternalDatabaseList_s008d_e020(int a)
{
    mAnchor.mpNext = 0;
    mAnchor.mpValue = 0;
    mAnchor.mnPriority = 0;
    mAnchor.mpNext = 0;
    mAnchor.mpValue = 0;
    mAnchor.mnPriority = 0;
    new (&mWriteMutex) Thread::Mutex_s008d_e020(0, 1);
    EA::ResourceMan::IAllocatorV* alloc = (EA::ResourceMan::IAllocatorV*)EA_Allocator_GetDefaultAllocator();
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    mpCoreAllocator = alloc;
    mpName = 0;
    FixedAllocatorCtor((char*)this + 0x54, 0xc, 0, 0xc8, 0, 0,
                       (void*)0x8de1c0, (void*)0x89ed40, a);
}

// @ 0x008de940
void EA::ResourceMan::InternalDatabaseList_s008d_e020::Add(void* pDatabase, int a)
{
    void** vt = *(void***)((char*)pDatabase + 4);
    {
        typedef void (__thiscall *Fn)(void*);
        ((Fn)vt[0])((char*)pDatabase + 4);
    }
    Node* pNode;
    char* alloc = (char*)this + 0x54;
    for (;;) {
        Node* head = *(Node**)(alloc + 0x10);
        if (head) {
            *(void**)(alloc + 0x10) = head->mpNext;
            _InterlockedExchange((volatile long*)&head->mpNext, 0);
            head->mpValue = 0;
            head->mnPriority = 0;
            pNode = head;
            break;
        }
        if (!FixedAllocatorAddCore(alloc, 0, 0)) { pNode = 0; break; }
    }
    pNode->mpValue = pDatabase;
    pNode->mnPriority = a;
    mWriteMutex.Lock((const char*)0x1436ab8);
    Node* p = mAnchor.mpNext;
    Node* prev = &mAnchor;
    while (p) {
        if (p->mnPriority < a) break;
        prev = p;
        p = p->mpNext;
    }
    _InterlockedExchange((volatile long*)&pNode->mpNext, (long)p);
    _InterlockedExchange((volatile long*)&prev->mpNext, (long)pNode);
    mWriteMutex.Unlock();
}

// @ 0x008de9d0
char EA::ResourceMan::Manager_s008d_e020::CheckCacheInternal(EA::ResourceMan::CacheRes* p1, void* p2, void** ppOut, char flag)
{
    typedef char (__thiscall *Slot5)(void*, void*, void*);
    EA::ResourceMan::CacheRes* key = p1;
    char bl = ((Slot5)(*(void***)this)[0x14 / 4])(this, key, p2);
    if (!bl) {
        EA::ResourceMan::CacheSrc* src = EA::ResourceMan::Fn8d5d00_src();
        EA::ResourceMan::CacheRes* found = 0;
        if (src) {
            if (src->Lookup(key, &found)) {
                bl = 1;
                if (ppOut) {
                    *ppOut = found;
                    return bl;
                }
                if (p2) {
                    if (flag) mNameMutex.Unlock();
                    EA::ResourceMan::CacheRef& ref = *(EA::ResourceMan::CacheRef*)&p1;
                    ref.mp = 0;
                    bl = found->Convert(ref.AsPPTypeParam());
                    if (bl) {
                        *(EA::ResourceMan::CacheRes**)p2 = ref.mp;
                        ref.mp = 0;
                    }
                    if (flag) mNameMutex.Lock((const char*)0x1436ab8);
                    if (ref.mp) ref.mp->Release();
                }
            }
            if (found) found->Release();
        }
    }
    return bl;
}

// @ 0x008dead0
char EA::ResourceMan::Manager_s008d_e020::Fn8dead0(void* pArg2, int a3, void* pArg4, void* pArg5, void* pArg6)
{
    char result = 0;
    if (pArg2) {
        EA::ResourceMan::Key3 k;
        if (pArg6) {
            k = *(EA::ResourceMan::Key3*)pArg6;
        } else {
            k.v0 = *(uint32*)((char*)pArg2 + 8);
            k.v1 = *(uint32*)((char*)pArg2 + 0xc);
            k.v2 = *(uint32*)((char*)pArg2 + 0x10);
        }
        EA::ResourceMan::DbObj* db = (EA::ResourceMan::DbObj*)pArg4;
        EA::ResourceMan::ResObj* res = (EA::ResourceMan::ResObj*)pArg5;
        if (!db) {
            typedef EA::ResourceMan::DbObj* (__thiscall *Fn)(void*, EA::ResourceMan::Key3*);
            db = ((Fn)(*(void***)this)[0x58 / 4])(this, &k);
        }
        if (db) {
            if (!res) {
                typedef EA::ResourceMan::ResObj* (__thiscall *Fn)(void*, uint32, int);
                res = ((Fn)(*(void***)this)[0x48 / 4])(this, k.v1, -1);
            }
            if (res) {
                EA::ResourceMan::ResObj* tmp = 0;
                if (db->Vf34(&k, &tmp, 3, 2, 1, 0)) {
                    result = res->Vf28(pArg2, tmp, a3, k.v1);
                    tmp->Vf24();
                    if (!result) db->Vf40(&k);
                }
                if (tmp) tmp->Release();
            }
        }
    }
    return result;
}

// @ 0x008debf0
void EA::ResourceMan::Manager::DoDatabaseChanged(EA::ResourceMan::Database * a, eastl::vector<EA::ResourceMan::Key, eastl::sp_vector_allocator> * pList)
{
    int a_v = (int)a;
    if (!pList) return;
    eastl_shim::ChangeSet* pSet = (eastl_shim::ChangeSet*)((char*)this + 0xc);
    if (pSet->mnSize == 0) return;
    DbNode* n = *(DbNode**)mDatabaseArray;
    if (!n) return;
    while ((int)n->mpObject != a_v) {
        n = n->mpNext;
        if (!n) return;
    }
    eastl_shim::RbNode* pAnchor = &pSet->mAnchor;
    eastl_shim::RbNode* node = pSet->mAnchor.mpNodeLeft;
    if (node == pAnchor) return;

    int* p = (int*)pList;
    do {
        int* begin = (int*)p[0];
        int* end = (int*)p[1];
        for (; begin != end; begin += 3) {
            void* item = begin;
            void** vt = *(void***)this;
            typedef int (__thiscall *Fn58)(void*, void*);
            int r = ((Fn58)vt[0x58 / 4])(this, item);
            if (r == 0 || r == a_v) {
                void* kf = *(void**)((char*)node + 0x18);
                if (kf) {
                    void** kvt = *(void***)kf;
                    typedef char (__thiscall *KfFn)(void*, void*);
                    if (!((KfFn)kvt[1])(kf, item)) continue;
                }
                void* ctx = *(void**)((char*)node + 0x14);
                void* fn = *(void**)((char*)node + 0x10);
                typedef void (__cdecl *Cb)(int, void*, void*);
                ((Cb)fn)(a_v, item, ctx);
            }
        }
        node = (eastl_shim::RbNode*)RBTreeIncrement_impl(node);
    } while (node != pAnchor);
}

// @ 0x008decb0
void Vec8::Fn8decb0()
{
    for (AutoRefObj* it = mpBegin; it < mpEnd; ++it) {
        void* o = it->mpObject;
        if (o) {
            void** vt = *(void***)o;
            typedef void (__thiscall *Fn)(void*);
            ((Fn)vt[0x08 / 4])(o);
        }
    }
    if (mpBegin) {
        size_t bytes = ((char*)mpEnd - (char*)mpBegin) >> 3;
        mpAllocator->Deallocate(mpBegin, bytes * 8);
    }
}

// @ 0x008ded00
void HashBase::HashBase_Insert(void** ppResult, uint32* pKey, uint32 extra)
{
    (void)extra;
    uint32 hash = *pKey;
    uint32 idx = hash % mnBucketCount;
    void** pSlot = &mpBucketArray[idx];
    char* node = (char*)*pSlot;
    while (node) {
        if (hash == *(uint32*)node) {
            *ppResult = node;
            *((char*)ppResult + 8) = 0;
            *(void**)((char*)ppResult + 4) = pSlot;
            return;
        }
        node = *(char**)(node + 8);
    }
    char dontCare;
    void* allocObj;
    Fn921440(&allocObj, (void*)(size_t)mnBucketCount, (void*)(size_t)mnElementCount, 1);
    node = (char*)mpAllocator->Allocate(0xc, 0, mpName);
    if (node) {
        *(uint32*)node = *(uint32*)pKey;
        *(uint32*)(node + 4) = *(uint32*)((char*)pKey + 4);
    }
    *(void**)(node + 8) = 0;
    (void)dontCare;
    if (*(char*)&dontCare) {
        idx = hash % mnElementCount;
        DoRehash1(mnElementCount);
    }
    uint32 off = idx * 4;
    *(void**)(node + 8) = *(void**)((char*)mpBucketArray + off);
    *(void**)((char*)mpBucketArray + off) = node;
    mnElementCount++;
    *(void**)((char*)ppResult + 0) = node;
    *((char*)ppResult + 8) = 1;
    *(void**)((char*)ppResult + 4) = (char*)mpBucketArray + off;
}

// @ 0x008dede0
void __stdcall Fn8dede0(AutoRefObj* first, AutoRefObj* last)
{
    for (; first < last; ++first) {
        void* o = first->mpObject;
        if (o) {
            if (_InterlockedDecrement((volatile long*)((char*)o + 4)) == 0) {
                _InterlockedExchange((volatile long*)((char*)o + 4), 1);
                void** vt = *(void***)o;
                typedef void (__thiscall *Fn)(void*, int);
                ((Fn)vt[0])(o, 1);
            }
        }
    }
}

// @ 0x008dee30
AutoRefObj& AutoRefObj::operator=(const AutoRefObj& src)
{
    void* v = src.mpObject;
    void* old = mpObject;
    if (v != old) {
        if (v) _InterlockedIncrement((volatile long*)((char*)v + 4));
        mpObject = v;
        if (old) {
            if (_InterlockedDecrement((volatile long*)((char*)old + 4)) == 0) {
                _InterlockedExchange((volatile long*)((char*)old + 4), 1);
                void** vt = *(void***)old;
                typedef void (__thiscall *Fn)(void*, int);
                ((Fn)vt[0])(old, 1);
            }
        }
    }
    mField = src.mField;
    return *this;
}

// @ 0x008dee90
void RbTree::DoInsertValueImpl(void* p2, char* pPos, void* pValue, char flag)
{
    char doInsert;
    if (!flag && pPos != (char*)this + 4) {
        EA::ResourceMan::ChangeNotificationInfoCompare_s008d_e020 cmp;
        if (!cmp(*(EA::ResourceMan::ChangeNotificationInfo_s008d_e020*)pValue,
                 *(EA::ResourceMan::ChangeNotificationInfo_s008d_e020*)(pPos + 0x10))) {
            doInsert = 1;
        } else {
            doInsert = 0;
        }
    } else {
        doInsert = 0;
    }
    char* node = (char*)mpAllocator->Allocate(0x20, 0, mpName);
    void* payload = node + 0x10;
    if (payload) {
        *(uint32*)payload = ((uint32*)pValue)[0];
        *(uint32*)((char*)payload + 4) = ((uint32*)pValue)[1];
        *(uint32*)((char*)payload + 8) = ((uint32*)pValue)[2];
        *(uint32*)((char*)payload + 0xc) = ((uint32*)pValue)[3];
    }
    RBTreeInsert_impl(node, pPos, (char*)this + 4, doInsert);
    ++mnSize;
    *(void**)p2 = node;
}

// @ 0x008def20
void* AutoRefVec::Fn8def20(int n, void* pAllocPair)
{
    void* alloc = *(void**)pAllocPair;
    mpAllocator = alloc;
    void* name = *((void**)pAllocPair + 1);
    mpName = name;
    if (n) {
        void* mem = ((EA::ResourceMan::IAllocatorV*)alloc)->Allocate(n * 8, 0, (const char*)name);
        mpBegin = mem;
        mpEnd = mem;
        mpCapacity = (char*)mem + n * 8;
        return this;
    }
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    return this;
}

// @ 0x008def80
AutoRefObj* Fn8def80(AutoRefObj* first, AutoRefObj* last, AutoRefObj* dest)
{
    if (first == last) return dest;
    do {
        void* o = first->mpObject;
        if (o) {
            if (_InterlockedDecrement((volatile long*)((char*)o + 4)) == 0) {
                _InterlockedExchange((volatile long*)((char*)o + 4), 1);
                void** vt = *(void***)o;
                typedef void (__thiscall *Fn)(void*, int);
                ((Fn)vt[0])(o, 1);
            }
        }
        ++first;
        ++dest;
    } while (first != last);
    return dest;
}

// @ 0x008defe0
AutoRefObj* Fn8defe0(AutoRefObj* first, AutoRefObj* last, AutoRefObj* dest)
{
    if (first == last) return dest;
    do {
        void* src = first->mpObject;
        void* old = dest->mpObject;
        if (src != old) {
            if (src) _InterlockedIncrement((volatile long*)((char*)src + 4));
            dest->mpObject = src;
            if (old) {
                if (_InterlockedDecrement((volatile long*)((char*)old + 4)) == 0) {
                    _InterlockedExchange((volatile long*)((char*)old + 4), 1);
                    void** vt = *(void***)old;
                    typedef void (__thiscall *Fn)(void*, int);
                    ((Fn)vt[0])(old, 1);
                }
            }
        }
        dest->mField = first->mField;
        ++first;
        ++dest;
    } while (first != last);
    return dest;
}

// @ 0x008e1d50
bool ManagerX::RegisterFactory(bool bAdd, IFactory* f, int prio)
{
    if (!bAdd) {
        FEntry* it = mFactories.mpBegin;
        FEntry* end = mFactories.mpEnd;
        if (it == end)
            return false;
        for (; it != end; ++it) {
            if (it->mp == f)
                goto found;
        }
        return false;
    found:
        if (_InterlockedExchangeAdd(&it->mp->mRef, 0) == 1)
            it->mp->OnRemoved();
        if (it + 1 < mFactories.mpEnd)
            MoveDown(it + 1, mFactories.mpEnd, it);
        --mFactories.mpEnd;
        ReleaseF(mFactories.mpEnd->mp);
        return true;
    }
    AddRefF(f);
    FEntry local;
    local.mp = f;
    AddRefF(f);
    local.mPriority = prio;
    ReleaseF(f);
    bool r = true;
    for (FEntry* it = mFactories.mpBegin; it != mFactories.mpEnd; ++it) {
        if (it->mp == f) {
            r = false;
            goto done;
        }
        if (it->mPriority < prio) {
            mFactories.insert(it, local);
            goto added;
        }
    }
    {
        FEntry* e = mFactories.mpEnd;
        if (e < mFactories.mpCap) {
            mFactories.mpEnd = e + 1;
            if (e) {
                e->mp = f;
                AddRefF(f);
                e->mPriority = prio;
            }
        } else {
            mFactories.DoInsertValue(e, local);
        }
    }
added:
    f->OnAdded();
done:
    ReleaseF(local.mp);
    return r;
}

// @ 0x008e1f10
ManagerX::~ManagerX()
{
    vt = vtbl_Manager;
    mpDatabaseList->~IDBList();
    mpAllocator->Free(mpDatabaseList, 0);
}

// @ 0x008e20c0
ManagerX::ManagerX(CAlloc* alloc)
: mbInitialized(false),
      mpAllocator(alloc ? alloc : GetDefaultAllocator()),
      mFunctionInfoSet(mpAllocator),
      mpDatabaseList(new (mpAllocator->Alloc(0x78, "Resource/Mgr/DBList", 0)) IDBList(mpAllocator)),
      mTypeToFactoryMap(mpAllocator),
      mResourceToRecordMap(mpAllocator),
      mTable78(mpAllocator),
      mFactories(mpAllocator),
      mTableB0(mpAllocator),
      mStack(mpAllocator, 0x400, 0x20),
      mNameMap((CAlloc*)&mStack),
      mNameMutex(0, true),
      mMutex(0, true)
{
    vt = vtbl_Manager;
}
