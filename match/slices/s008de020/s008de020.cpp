// Slice s008de020: EA::ResourceMan::Manager (read key, database/compressor lookups,
// check-cache, database-changed) plus the EASTL rbtree/hashtable helpers it pulls in
// and the InternalDatabaseList / AutoRefCount machinery.
// Flags: /O2 /MD /Gy /EHsc /TP
#include <new>
#include <string.h>
#include "types.h"

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned long long uint64;

// ---------------------------------------------------------------------------
// externals (real addresses in comments)
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int); // 0x13cc4a8 IAT
extern "C" uint64 __cdecl StrtoU6416(const wchar_t*, wchar_t**, int);                            // 0x0092d710
extern "C" char (*g_154c464)(void*, void*, void*, void*, void*, int);                            // 0x0154c464

extern "C" void* RBTreeIncrement_impl(void*);        // 0x00921580
extern "C" void RBTreeInsert_impl(void*, void*, void*, int); // 0x009216a0
extern "C" void* Fn921440(void*, void*, void*, int);          // 0x00921440
extern "C" int lib_eathread_Mutex_Unlock(void*);             // 0x00922270
extern "C" int lib_eathread_Mutex_Lock(void*, const char*);  // 0x009221b0
extern "C" void* EA_Allocator_GetDefaultAllocator();         // 0x00925cb0
extern "C" void* Fn8d5d00();                                 // 0x008d5d00

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange, _InterlockedExchangeAdd)

// ---------------------------------------------------------------------------
// core types
// ---------------------------------------------------------------------------
namespace EA {

// A COM-ish object: vtable at +0, virtual Release(int) at slot 0.
struct IRefCounted {
    virtual void Delete(int flag);      // vtable +0x00
    virtual void AddRefVirtual();       // vtable +0x04
    volatile long mnRefCount;           // +0x04 is taken by AddRefVirtual's slot? no: data
};

// Callable-object / allocator stub with a vtable (slots used by the hashtables).
struct ICoreAllocator {
    virtual void a0();
    virtual void a1();
    virtual void* Allocate(size_t size, int flags, const char* pName); // +0x08
    virtual void Deallocate(void* p, size_t size);                     // +0x0c
};

namespace Thread {
class Mutex { public:
    char pad[0x30];
    void Lock(const char* pName);   // 0x009221b0
    int Unlock();                   // 0x00922270
    Mutex(int a = 0, int b = 0);    // 0x009222a0
};
}

namespace IO {
class FileChangeNotification { public:
    void** vftable;         // +0x00
    bool mbInitialized;     // +0x04
    bool Init();
};
}

namespace ResourceMan {

class Key { public:
    uint32 mInstance;   // +0x00
    uint32 mType;       // +0x04
    uint32 mGroup;      // +0x08
};
struct KeyFilter;

bool ReadKey(const wchar_t* pString, Key* pKey);

// ---------------------------------------------------------------------------
// Manager::ChangeNotificationInfo and its compare functor
// ---------------------------------------------------------------------------
struct ChangeNotificationInfo {
    void* mpFunction;       // +0x00
    void* mpContext;        // +0x04
    KeyFilter* mpKeyFilter; // +0x08
    int mnPriority;         // +0x0c
};

struct ChangeNotificationInfoCompare {
    bool operator()(const ChangeNotificationInfo& a, const ChangeNotificationInfo& b) const;
};

// ---------------------------------------------------------------------------
// Manager
// ---------------------------------------------------------------------------
struct Compression;
struct CacheRes;

class Manager { public:
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
    Thread::Mutex mNameMutex;       // +0x148

    char Fn8de230(int a, int b, int c, int d);
    bool GetLoadedResource(int a, int b);
    bool IsDatabaseRegistered(int a, void** pOut);
    void* FindDatabase(int a);
    void* Fn8de360(int a);
    bool Fn8de3b0(int a, int b);
    void Fn8de400(void* p, int a);
    char CheckCacheInternal(CacheRes* p1, void* p2, void** ppOut, char flag);
    char Fn8dead0(void* pArg2, int a3, void* pArg4, void* pArg5, void* pArg6);
    void DoDatabaseChanged(int a, void* pList);
};

// linked-tree node used by the database list/database lookups
struct DbNode {
    DbNode* mpNext;     // +0x00
    void* mpObject;     // +0x04
    void* mpValue;      // +0x08
};

// [Manager+0x2c] points at this anchor; its first field is the list head.
struct DbList {
    DbNode* mpHead;     // +0x00
};

// ---------------------------------------------------------------------------
// InternalDatabaseList
// ---------------------------------------------------------------------------
struct IAllocatorV {
    virtual void a0();
    virtual void a1();
    virtual void* Allocate(size_t, int, const char*);   // +0x08
    virtual void Deallocate(void*, size_t);             // +0x0c
};

struct InternalDatabaseList {
    struct Node {
        Node* mpNext;       // +0x00
        void* mpValue;      // +0x04
        int mnPriority;     // +0x08
    };

    Node mAnchor;                              // +0x00
    Thread::Mutex mWriteMutex;                 // +0x10
    void** mpBegin;                            // +0x40
    void** mpEnd;                              // +0x44
    void** mpCapacity;                         // +0x48
    IAllocatorV* mpCoreAllocator;              // +0x4c
    const char* mpName;                        // +0x50

    InternalDatabaseList(int a);
    void Add(void* pDatabase, int a);
};

}  // namespace ResourceMan
}  // namespace EA

// ---------------------------------------------------------------------------
// @ 0x008de020
// ---------------------------------------------------------------------------
uint64 SwizzleUint64(uint32 a, uint32 b)
{
    uint32 hi = (((a << 16) | ((((a & 0xff00u) << 16) | (a & 0xff0000u)) >> 16)) << 8) | (a >> 24);
    uint32 lo = (((b >> 16) | ((((b & 0xff0000u) >> 16) | (b & 0xff00u)) << 16)) >> 8) | (b << 24);
    return ((uint64)hi << 32) | lo;
}

// ---------------------------------------------------------------------------
// @ 0x008de0c0
// ---------------------------------------------------------------------------
namespace EA { namespace ResourceMan {
bool ReadKey(const wchar_t* pString, Key* pKey)
{
    wchar_t* pEnd;
    pKey->mType = (uint32)wcstoul(pString, &pEnd, 16);
    if (*pEnd != L':') return false;
    pKey->mGroup = (uint32)wcstoul(pEnd + 1, &pEnd, 16);
    if (*pEnd != L':') return false;
    uint64 v = StrtoU6416(pEnd + 1, &pEnd, 16);
    wchar_t* pStart = pEnd;
    uint32 lo = (uint32)v;
    uint32 hi = (uint32)(v >> 32);
    if (*pEnd == 0) { pKey->mInstance = lo; return true; }
    if (*pEnd == L'\'' && hi == 0) {
        lo = (uint32)wcstoul(pEnd + 1, &pEnd, 16);
        if ((((int)pEnd - (int)pStart) & 0xfffffffe) != 0x12) return false;
    }
    if (*pEnd == 0 || *pEnd == L' ') { pKey->mInstance = lo; return true; }
    return false;
}
}}

// ---------------------------------------------------------------------------
// @ 0x008de1b0
// ---------------------------------------------------------------------------
static int g_01667aa0;
int Fn8de1b0(int v)
{
    int old = g_01667aa0;
    g_01667aa0 = v;
    return old;
}

// ---------------------------------------------------------------------------
// @ 0x008de1e0
// ---------------------------------------------------------------------------
bool EA::ResourceMan::ChangeNotificationInfoCompare::operator()(
        const EA::ResourceMan::ChangeNotificationInfo& a,
        const EA::ResourceMan::ChangeNotificationInfo& b) const
{
    if (a.mnPriority != b.mnPriority) return b.mnPriority < a.mnPriority;
    if (a.mpFunction != b.mpFunction) return a.mpFunction < b.mpFunction;
    if (a.mpContext != b.mpContext) return a.mpContext < b.mpContext;
    return a.mpKeyFilter < b.mpKeyFilter;
}

// ---------------------------------------------------------------------------
// @ 0x008de220
// ---------------------------------------------------------------------------
bool EA::IO::FileChangeNotification::Init()
{
    if (!mbInitialized) mbInitialized = true;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x008de230
// ---------------------------------------------------------------------------
char EA::ResourceMan::Manager::Fn8de230(int a, int b, int c, int d)
{
    char r = g_154c464((void*)a, (void*)b, (void*)c, (void*)d, this, 0);
    if (r) {
        void** vt = *(void***)this;
        typedef void (__thiscall *Fn)(void*, void*, void*);
        ((Fn)vt[0x80 / 4])(this, (void*)a, (void*)b);
    }
    return r;
}

// ---------------------------------------------------------------------------
// @ 0x008de280
// ---------------------------------------------------------------------------
bool EA::ResourceMan::Manager::GetLoadedResource(int a, int b)
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

// ---------------------------------------------------------------------------
// @ 0x008de2d0
// ---------------------------------------------------------------------------
bool EA::ResourceMan::Manager::IsDatabaseRegistered(int a, void** pOut)
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

// ---------------------------------------------------------------------------
// @ 0x008de310
// ---------------------------------------------------------------------------
void* EA::ResourceMan::Manager::FindDatabase(int a)
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

// ---------------------------------------------------------------------------
// @ 0x008de360
// ---------------------------------------------------------------------------
void* EA::ResourceMan::Manager::Fn8de360(int a)
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

// ---------------------------------------------------------------------------
// @ 0x008de3b0
// ---------------------------------------------------------------------------
bool EA::ResourceMan::Manager::Fn8de3b0(int a, int b)
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

// ---------------------------------------------------------------------------
// @ 0x008de400
// ---------------------------------------------------------------------------
void EA::ResourceMan::Manager::Fn8de400(void* p, int a)
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

// ---------------------------------------------------------------------------
// rbtree/hashtable helper stubs
// ---------------------------------------------------------------------------
namespace eastl_shim {

// rbtree node base: right first (EASTL declares mpNodeRight first).
struct RbNode {
    RbNode* mpNodeRight;    // +0x00
    RbNode* mpNodeLeft;     // +0x04
    RbNode* mpNodeParent;   // +0x08
    uint32 mnColor;         // +0x0c
};
// change-info tree node: links then ChangeNotificationInfo at +0x10
struct ChangeNode {
    RbNode base;                                       // +0x00
    EA::ResourceMan::ChangeNotificationInfo mValue;    // +0x10
};

struct IAllocatorV {
    virtual void a0();
    virtual void a1();
    virtual void* Allocate(size_t, int, const char*);   // +0x08
    virtual void Deallocate(void*, size_t);             // +0x0c
};

struct ChangeSet {
    uint32 mUnk0;              // +0x00
    RbNode mAnchor;            // +0x04 (right@+4, left@+8, parent@+0x0c, color@+0x10)
    uint32 mnSize;             // +0x14
    IAllocatorV* mpAllocator;  // +0x18
    const char* mpName;        // +0x1c

    void DoFreeNodes(RbNode* node);   // @ 0x008de4f0
    void LowerBound(void** ppOut, const uint32* pKey); // @ 0x008de450
};

// @ 0x008de450
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

// @ 0x008de4f0
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


// ---------------------------------------------------------------------------
// @ 0x008de530 / @ 0x008de5e0 / @ 0x008de690  (hashtable DoRehash variants)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// AutoRefCount pair (8 bytes: object pointer + int)
// ---------------------------------------------------------------------------
struct AutoRefObj {
    void* mpObject;     // +0x00
    int mField;         // +0x04

    AutoRefObj& operator=(const AutoRefObj& src);   // 0x008dee30
};
struct RefCountedBase {
    void** vftable;     // +0x00
    volatile long mnRefCount; // +0x04
};

static void AddRefObj(void* p)
{
    if (p) _InterlockedIncrement((volatile long*)((char*)p + 4));
}
static void ReleaseObj(void* p)
{
    if (!p) return;
    if (_InterlockedDecrement((volatile long*)((char*)p + 4)) == 0) {
        _InterlockedExchange((volatile long*)((char*)p + 4), 1);
        void** vt = *(void***)p;
        typedef void (__thiscall *Fn)(void*, int);
        ((Fn)vt[0])(p, 1);
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

// ---------------------------------------------------------------------------
// FixedAllocator ctor stub used by InternalDatabaseList
// ---------------------------------------------------------------------------
extern "C" void FixedAllocatorCtor(void* pThis, int a, int b, int c, int d, int e,
                                   void* f, void* g, int h); // 0x00926720
extern "C" int FixedAllocatorAddCore(void* pThis, int a, int b); // 0x00926650

// @ 0x008de8e0
EA::ResourceMan::InternalDatabaseList::InternalDatabaseList(int a)
{
    mAnchor.mpNext = 0;
    mAnchor.mpValue = 0;
    mAnchor.mnPriority = 0;
    mAnchor.mpNext = 0;
    mAnchor.mpValue = 0;
    mAnchor.mnPriority = 0;
    new (&mWriteMutex) Thread::Mutex(0, 1);
    IAllocatorV* alloc = (IAllocatorV*)EA_Allocator_GetDefaultAllocator();
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    mpCoreAllocator = alloc;
    mpName = 0;
    FixedAllocatorCtor((char*)this + 0x54, 0xc, 0, 0xc8, 0, 0,
                       (void*)0x8de1c0, (void*)0x89ed40, a);
}

// @ 0x008de940
void EA::ResourceMan::InternalDatabaseList::Add(void* pDatabase, int a)
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

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
namespace EA { namespace ResourceMan {
// Cache objects: vtable slot 1 (+4) is the virtual Release, slot 5 (+0x14) the lookup/convert call.
struct CacheRes {
    virtual void v0();
    virtual void Release();                 // +0x04
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual char Convert(CacheRes** ppOut); // +0x14
};
struct CacheSrc {
    virtual void v0();
    virtual void Release();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual char Lookup(void* pKey, CacheRes** ppOut); // +0x14
};
struct CacheRef {   // AutoRefCount<T> wrapper
    CacheRes* mp;
    CacheRes** AsPPTypeParam();             // 0x00a16f40
};
extern CacheSrc* Fn8d5d00_src();            // 0x008d5d00 (cdecl, returns CacheSrc*)
}}
using namespace EA::ResourceMan;

// @ 0x008de9d0
char EA::ResourceMan::Manager::CheckCacheInternal(CacheRes* p1, void* p2, void** ppOut, char flag)
{
    typedef char (__thiscall *Slot5)(void*, void*, void*);
    CacheRes* key = p1;
    char bl = ((Slot5)(*(void***)this)[0x14 / 4])(this, key, p2);
    if (!bl) {
        CacheSrc* src = Fn8d5d00_src();
        CacheRes* found = 0;
        if (src) {
            if (src->Lookup(key, &found)) {
                bl = 1;
                if (ppOut) {
                    *ppOut = found;
                    return bl;
                }
                if (p2) {
                    if (flag) mNameMutex.Unlock();
                    CacheRef& ref = *(CacheRef*)&p1;
                    ref.mp = 0;
                    bl = found->Convert(ref.AsPPTypeParam());
                    if (bl) {
                        *(CacheRes**)p2 = ref.mp;
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

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
namespace EA { namespace ResourceMan {
struct Key3 { uint32 v0, v1, v2; };
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
}}

// @ 0x008dead0
char EA::ResourceMan::Manager::Fn8dead0(void* pArg2, int a3, void* pArg4, void* pArg5, void* pArg6)
{
    char result = 0;
    if (pArg2) {
        Key3 k;
        if (pArg6) {
            k = *(Key3*)pArg6;
        } else {
            k.v0 = *(uint32*)((char*)pArg2 + 8);
            k.v1 = *(uint32*)((char*)pArg2 + 0xc);
            k.v2 = *(uint32*)((char*)pArg2 + 0x10);
        }
        DbObj* db = (DbObj*)pArg4;
        ResObj* res = (ResObj*)pArg5;
        if (!db) {
            typedef DbObj* (__thiscall *Fn)(void*, Key3*);
            db = ((Fn)(*(void***)this)[0x58 / 4])(this, &k);
        }
        if (db) {
            if (!res) {
                typedef ResObj* (__thiscall *Fn)(void*, uint32, int);
                res = ((Fn)(*(void***)this)[0x48 / 4])(this, k.v1, -1);
            }
            if (res) {
                ResObj* tmp = 0;
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
// ---------------------------------------------------------------------------
void EA::ResourceMan::Manager::DoDatabaseChanged(int a, void* pList)
{
    if (!pList) return;
    eastl_shim::ChangeSet* pSet = (eastl_shim::ChangeSet*)((char*)this + 0xc);
    if (pSet->mnSize == 0) return;
    DbNode* n = *(DbNode**)mDatabaseList;
    if (!n) return;
    while ((int)n->mpObject != a) {
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
            if (r == 0 || r == a) {
                void* kf = *(void**)((char*)node + 0x18);
                if (kf) {
                    void** kvt = *(void***)kf;
                    typedef char (__thiscall *KfFn)(void*, void*);
                    if (!((KfFn)kvt[1])(kf, item)) continue;
                }
                void* ctx = *(void**)((char*)node + 0x14);
                void* fn = *(void**)((char*)node + 0x10);
                typedef void (__cdecl *Cb)(int, void*, void*);
                ((Cb)fn)(a, item, ctx);
            }
        }
        node = (eastl_shim::RbNode*)RBTreeIncrement_impl(node);
    } while (node != pAnchor);
}

// ---------------------------------------------------------------------------
// @ 0x008decb0
// ---------------------------------------------------------------------------
struct Vec8 {
    AutoRefObj* mpBegin;    // +0x00
    AutoRefObj* mpEnd;      // +0x04
    AutoRefObj* mpCapacity; // +0x08
    EA::ResourceMan::IAllocatorV* mpAllocator; // +0x0c

    void Fn8decb0();        // @ 0x008decb0
};

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

// ---------------------------------------------------------------------------
// @ 0x008ded00  (hashtable insert with rehash-on-demand)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x008dede0
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x008dee90  (rbtree DoInsertValueImpl)
// ---------------------------------------------------------------------------
struct RbTree {
    char pad00[0x14];
    uint32 mnSize;          // +0x14
    EA::ResourceMan::IAllocatorV* mpAllocator;  // +0x18
    const char* mpName;     // +0x1c
    char pad20[4];
    RbTree* mpAnchor;       // +0x24-ish (not modeled precisely)

    void DoInsertValueImpl(void* p2, char* pPos, void* pValue, char flag); // @ 0x008dee90
};

void RbTree::DoInsertValueImpl(void* p2, char* pPos, void* pValue, char flag)
{
    char doInsert;
    if (!flag && pPos != (char*)this + 4) {
        EA::ResourceMan::ChangeNotificationInfoCompare cmp;
        if (!cmp(*(EA::ResourceMan::ChangeNotificationInfo*)pValue,
                 *(EA::ResourceMan::ChangeNotificationInfo*)(pPos + 0x10))) {
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

// ---------------------------------------------------------------------------
// @ 0x008def20  (vector ctor with allocator)
// ---------------------------------------------------------------------------
struct AutoRefVec {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    void* mpAllocator;  // +0x0c
    void* mpName;       // +0x10

    void* Fn8def20(int n, void* pAllocPair); // @ 0x008def20
};

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

// ---------------------------------------------------------------------------
// @ 0x008def80
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x008defe0
// ---------------------------------------------------------------------------
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
