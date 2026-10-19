// src/game/UTFSpore_Win32/eatrace_imp.cpp -- migrated from slice(s) s00925770, s009245b0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/eatrace_imp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EAMutexData.h"
#include "EA/Trace/ILogFilter.h"
#include "EA/Trace/ILogFormatter.h"
#include "EA/Trace/ILogReporter.h"
#include "EA/Trace/IServer.h"
#include "EA/Trace/LogFilterGroupLevels.h"
#include "EA/Trace/LogFormatterFancy.h"
#include "EA/Trace/LogFormatterSimple.h"
#include "EA/Trace/LogReporter.h"
#include "EA/Thread/Mutex.h"
#include "EA/Trace/Server.h"
#include "EA/Stopwatch.h"
#include "EA/Trace/TraceHelper.h"

// unnamed retail callees and globals (address in the comment)
extern unsigned g_timeout_143dffc;
#include <windows.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <new>
#include <intrin.h>

// ---- items of slice s009245b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Thread {
struct EAMutexData { unsigned __int64 mData[4]; int mnLockCount; bool mbIntraProcess; void* mThreadId; };
}
}
namespace EA {
namespace Thread {
class Mutex_s0092_45b0 {
public:
    EAMutexData mMutexData;
    void Lock(unsigned* pTimeout);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    int  Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
    ~Mutex_s0092_45b0();
};
}
}
extern unsigned g_timeout_143dffc;
namespace EA {
namespace Trace {
extern "C" void* __cdecl eanew(int a1, int a2, int a3, const char* name, int a5, int a6, int a7, int a8);
}
}
namespace EA {
namespace Trace {
extern "C" void* __cdecl eanew6(int size, const char* name, int a, int b, int c, int d);
}
}
namespace EA {
namespace Trace {
extern "C" void __cdecl eadelete(void* p);            // operator delete[] (0x00f47380)
}
}
namespace EA {
namespace Trace {
struct EnabledValue { char pad[0x10]; unsigned field; };
}
}
namespace EA {
namespace Trace {
extern EnabledValue* g_01668ea0;
}
}
namespace EA {
namespace Trace {
struct IObj {                       // IRefCount-style: AddRef, Release, ?, Cast
    virtual void AddRef();          // +0x00
    virtual void Release();         // +0x04
    virtual void v2();              // +0x08
    virtual void* Cast(unsigned id); // +0x0c
};
}
}
namespace EA {
namespace Trace {
struct ITracer_s0092_45b0;
}
}
namespace EA {
namespace Trace {
struct TraceHelper_s0092_45b0 {
    bool mbActive, mbEnabled, mbDisabled;       // +0, +1, +2
    unsigned mType;                             // +4
    int mField8;                                // +8
    int mField0c;                               // +0xc
    const char* mName;                          // +0x10
    int mLoc[3];                                // +0x14
    ITracer_s0092_45b0* mTracer;                           // +0x20
    TraceHelper_s0092_45b0(unsigned type, const char* name, int level, const int* loc);
};
}
}
namespace EA {
namespace Trace {
struct TraceHelperTableBase {
    virtual void v0();
    virtual void v1();
    virtual ~TraceHelperTableBase() {}                          // +0x08
    virtual void v3();
    virtual void UpdateTracerRaw(void* p);                      // +0x10
    virtual void v5();
    virtual void RegisterHelper(TraceHelper_s0092_45b0* h);                // +0x18
    virtual void ReleaseHelper(TraceHelper_s0092_45b0* h);                 // +0x1c
};
}
}
namespace EA {
namespace Trace {
struct HelperVec {
    char** mpBegin; char** mpEnd; char** mpCapacity;
    int pad[3];
    ~HelperVec() { if (mpBegin && ((int*)mpBegin)[-1]) eadelete(mpBegin); }
};
}
}
namespace EA {
namespace Trace {
struct TraceHelperTable : TraceHelperTableBase {
    void* mTracer;                                // +0x04
    HelperVec mHelpers;                           // +0x08
    EA::Thread::Mutex_s0092_45b0 mMutex;                     // +0x20
    volatile int mnRefCount;                      // +0x50
    TraceHelperTable();
    ~TraceHelperTable() {}
    void UpdateTracerV();                         // 0x009250B0
    void UpdateTracer(ITracer_s0092_45b0* pTracer);
    int  Release();
    TraceHelper_s0092_45b0* ReserveHelper(unsigned type, const char* name, int level, const int* loc);
};
}
}
namespace EA {
namespace Trace {
struct HelperTableHolder { char pad[0x10]; TraceHelperTable* field; };
}
}
namespace EA {
namespace Trace {
extern HelperTableHolder* g_01668e9c;
}
}
namespace EA {
namespace Trace {
extern const char g_dialogTail_143e008[0x45];
}
}
namespace EA {
namespace Trace {
struct ILogManager : IObj {};
}
}
namespace EA {
namespace Trace {
ILogManager* GetLogManager();                 // 0x00697fa0
}
}
namespace EA {
namespace Trace {
struct TraceLogManagerRef {
    int f0, f4, f8, fc;
    ILogManager* mpLogManager;                // +0x10
    TraceLogManagerRef();
};
}
}
namespace EA {
namespace Trace {
struct HNode { int key; int* pObj; HNode* mpNext; };
}
}
namespace EA {
namespace Trace {
struct TraceHashtable {
    int pad0;
    HNode** mpBucketArray;           // +4
    unsigned mnBucketCount;          // +8
    int pad0c, pad10, pad14, pad18;
    HNode* mpFreeList;               // +0x1c
    int pad20;
    char* mpPoolBegin;               // +0x24
    char* mpPoolEnd;                 // +0x28
    int pad2c;
    HNode** mpInlineBuckets;         // +0x30
    HNode** DoAllocateBuckets(unsigned n);   // 0x00925300
    void DoRehash(unsigned nNewBucketCount);
};
}
}
namespace EA {
namespace Trace {
struct TempNode { int a, b, c; char* mpHelper; TempNode* mpNext; };
}
}
namespace EA {
namespace Trace {
struct TempTraceHelperMap {
    EA::Thread::Mutex_s0092_45b0 mMutex;                // +0
    struct {
        int pad0;
        TempNode** mpBucketArray;            // +0x34 (this+0x30 + 4)
        unsigned mnBucketCount;              // +0x38
        unsigned mnElementCount;             // +0x3c
        void DoFreeNodes(TempNode** begin, unsigned count);  // 0x007611f0
    } mTable;                                // +0x30
    char pad40[0x50 - 0x40];
    bool mbHelpersReserved;                  // +0x50
    void ReleaseHelpers();
};
}
}
// ---- items of slice s009245b0 end

// ---- items of slice s00925770 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Trace {
extern void* __fastcall ctor_00925540(void*);
}
}
namespace EA {
namespace Trace {
struct Mutex {
    char d[0x30];
    Mutex* Init(const char* name, bool b);    // 0x009222a0 (Mutex::Mutex)
    void Destroy();                           // 0x00922130 (~Mutex)
    void Lock(const void* ctx);               // 0x009221b0
    int  Unlock();                            // 0x00922270
};
}
}
namespace EA {
namespace Trace {
struct TraceHelper_s0092_5770 {
    char pad0;
    bool mIsFiltered;
    bool mIsFilterEvaluated;
    char pad3[0x1d];
    void* mTracer;
};
}
}
namespace EA {
namespace Trace {
TraceHelper_s0092_5770** __cdecl vec_move(void* dst, void* src, int bytes);                                    // 0x011e0744
}
}
namespace EA {
namespace Trace {
void* __cdecl eastl_new(unsigned size, const char* name, int, int, const char* file, int line);    // 0x00f473a0
}
}
namespace EA {
namespace Trace {
void __cdecl eastl_delete(void* p);                                                                // 0x00f47380
}
}
namespace EA {
namespace Trace {
struct HelperVec_s0092_5770 {
    TraceHelper_s0092_5770** mpBegin;
    TraceHelper_s0092_5770** mpEnd;
    TraceHelper_s0092_5770** mpCapacity;
    void DoInsertValue(TraceHelper_s0092_5770** pos, TraceHelper_s0092_5770* const* val);   // 0x009257e0
    __forceinline TraceHelper_s0092_5770** find(TraceHelper_s0092_5770* v) {
        TraceHelper_s0092_5770** last = mpEnd; TraceHelper_s0092_5770** first = mpBegin;
        while (first != last && *first != v) ++first;
        return first;
    }
    __forceinline void erase(TraceHelper_s0092_5770** it) {
        TraceHelper_s0092_5770** next = it + 1;
        if (next < mpEnd) vec_move(it, next, (int)((char*)mpEnd - (char*)next));
        --mpEnd;
    }
    __forceinline void Zero() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void Reserve(int n);                                              // 0x009256a0
    inline void push_back(TraceHelper_s0092_5770* v) {
        if (mpEnd < mpCapacity) {
            TraceHelper_s0092_5770** e = mpEnd++;
            if (e) *e = v;
        } else {
            DoInsertValue(mpEnd, &v);
        }
    }
};
}
}
namespace EA {
namespace Trace {
struct TraceHelperTable_s0092_5770 {
    virtual void AddRef();  // 0x00925050 (EA::Trace::TraceHelperTable::AddRef)
    virtual void Release();  // 0x00925060 (EA::Trace::TraceHelperTable::Release)
    void* mTracer;
    HelperVec_s0092_5770 mVec;
    char pad14[0xc];
    Mutex mMutex;
    long mFlag;
    char pad54[4];
    void RegisterHelper(TraceHelper_s0092_5770* h);      // 0x00925b50
    void UnregisterHelper(TraceHelper_s0092_5770* h);    // 0x00925960
};
}
}
namespace EA {
namespace Trace {
struct HelperTablePtr {
    int w0, w4, w8, wc;
    TraceHelperTable_s0092_5770* mpTable;
    HelperTablePtr* Init();                   // 0x00925b00
    __forceinline void setTable(TraceHelperTable_s0092_5770* n) {
        TraceHelperTable_s0092_5770* old = mpTable;
        if (n != old) {
            if (n) n->AddRef();
            mpTable = n;
            if (old) old->Release();
        }
    }
};
}
}
namespace EA {
namespace Trace {
extern const float g_01485720;
}
}
namespace EA {
namespace Trace {
extern const float g_01470f1c;
}
}
namespace EA {
namespace Trace {
struct TempMapHT {
    void* vt;
    void* mpBuckets;
    unsigned mBucketCount;
    unsigned mElementCount;
    float mMaxLoad;
    float mGrowth;
    volatile int mNextResize;
    int   w1c;
    char  mbEnable;
    void DoFreeNodes(void* buckets, unsigned n);   // 0x007611f0
    __forceinline void Clear() {
        DoFreeNodes(mpBuckets, mBucketCount);
        mElementCount = 0;
        if (mBucketCount > 1) eastl_delete(mpBuckets);
    }
};
}
}
namespace EA {
namespace Trace {
struct TempTraceHelperMap_s0092_5770 {
    Mutex mMutex;
    TempMapHT ht;
    TempTraceHelperMap_s0092_5770* Init();                    // 0x009259d0
    void Destroy();                                // 0x009257a0 (~TempTraceHelperMap)
    void ReleaseHelpers();                         // 0x009255f0
};
}
}
namespace EA {
namespace Trace {
extern const float g_013f0620;
}
}
namespace EA {
namespace Trace {
struct FixedPool {
    void* mpHead;
    int   w4;
    void* mBuf;
    void* mBufEnd;
    int   mNodeSize;
    void* mAlloc;
    void init(void* buf, unsigned size, unsigned nodeSize, unsigned align, unsigned off);   // 0x00921260
};
}
}
namespace EA {
namespace Trace {
struct RehashPolicy {
    float mMaxLoad, mGrowth;
    int   mNextResize;
    unsigned GetBucketCount(unsigned n);       // 0x009213c0
};
}
}
namespace EA {
namespace Trace {
unsigned __cdecl policy_prime(unsigned n);     // 0x00921340
}
}
namespace EA {
namespace Trace {
struct TraceHashtable_s0092_5770 {
    int w0, w4;
    unsigned mBucketCount;
    unsigned mElementCount;
    RehashPolicy mPolicy;
    char pad1c[0x18];
    char mNodes[1];
    TraceHashtable_s0092_5770* Init(unsigned a1, unsigned a2);
    void Init7(unsigned b, unsigned a1, const unsigned& r1, const unsigned& r2, unsigned v, const unsigned& r3, FixedPool* pool);  // 0x00925490
    void DoRehash(unsigned n);                 // 0x00925370
};
}
}
// ---- items of slice s00925770 end

// @ 0x00925000
namespace EA { namespace Trace {
int __stdcall MessageBoxThreadStart(unsigned* p)
{
    int r = MessageBoxA(0, (LPCSTR)p[0], (LPCSTR)p[1], 0x12132);
    switch (r) {
    case 3: p[2] = 1; return 0;
    case 5: p[2] = 2; return 0;
    default: p[2] = 0; return 0;
    }
}
}}  // namespace EA::Trace

// @ 0x00925060
namespace EA { namespace Trace {
int TraceHelperTable::Release()
{
    int n = _InterlockedExchangeAdd((volatile long*)&mnRefCount, -1);
    if (--n == 0) {
        _InterlockedExchange((volatile long*)&mnRefCount, 1);
        if (this) delete this;
        return 0;
    }
    return n;
}
}}  // namespace EA::Trace

// @ 0x009250b0
namespace EA { namespace Trace {
void TraceHelperTable::UpdateTracerV()
{ UpdateTracerRaw(mTracer); }
}}  // namespace EA::Trace

// @ 0x009250c0
namespace EA {
namespace Trace {
void SetTraceDialogEnabled(bool b)
{ g_01668ea0->field = (unsigned)(b != 0); }
}
}  // namespace EA::Trace

// @ 0x00925100
namespace EA {
namespace Trace {
int DisplayTraceDialog(char const * msg, char const * a2)
{
    if (g_01668ea0->field == 1) {
        char buf[0x200];
        strncpy(buf, msg, 0x200);
        buf[0x1ff] = 0;
        size_t len = strlen(buf);
        if (0x200 - len >= 0x45) memcpy(buf + len, g_dialogTail_143e008, 0x45);
        unsigned args[3];
        args[0] = (unsigned)buf;
        args[1] = (unsigned)msg;
        args[2] = 0;
        HANDLE h = CreateThread(0, 0x10000, (LPTHREAD_START_ROUTINE)MessageBoxThreadStart, args, 0, 0);
        if (h) {
            WaitForSingleObject(h, (DWORD)-1);
            CloseHandle(h);
        }
        return args[2];
    }
    return 0;
}
}
}  // namespace EA::Trace

// @ 0x009251d0
namespace EA { namespace Trace {
void TraceHelperTable::UpdateTracer(ITracer_s0092_45b0* pTracer)
{
    mMutex.Lock(&g_timeout_143dffc);
    mTracer = pTracer;
    char** it = mHelpers.mpBegin;
    char** end = mHelpers.mpEnd;
    for (; it != end; ++it) {
        TraceHelper_s0092_45b0* h = (TraceHelper_s0092_45b0*)*it;
        h->mTracer = (ITracer_s0092_45b0*)mTracer;
        h->mbEnabled = true;
        h->mbDisabled = false;
    }
    mMutex.Unlock();
}
}}  // namespace EA::Trace

// @ 0x00925220
namespace EA { namespace Trace {
TraceHelper_s0092_45b0::TraceHelper_s0092_45b0(unsigned type, const char* name, int level, const int* loc)
{
    mbActive = true; mbEnabled = true; mbDisabled = false;
    mType = type;
    mField8 = 0;
    mField0c = level;
    mName = name;
    mLoc[0] = loc[0]; mLoc[1] = loc[1]; mLoc[2] = loc[2];
    mTracer = 0;
    switch (type) {
    case 0: case 1:
        mField8 = 3;
        if (level == 0) mField0c = 0x96;
        break;
    case 2:
        mField8 = 1;
        if (level == 0) mField0c = 0x19;
        break;
    case 3:
        mField8 = 3;
        mField0c = 0x96;
        break;
    default:
        mField8 = 1;
        break;
    }
    if (name == 0) mName = "Assert";
    TraceHelperTable* t = g_01668e9c->field;
    if (t) {
        t->RegisterHelper(this);
    } else {
        mbActive = false;
        mbDisabled = true;
    }
}
}}  // namespace EA::Trace

// @ 0x00925370
namespace EA { namespace Trace {
void TraceHashtable::DoRehash(unsigned nNewBucketCount)
{
    HNode** pNewBucketArray = DoAllocateBuckets(nNewBucketCount);
    for (unsigned i = 0; i < mnBucketCount; ++i) {
        HNode* pNode;
        while ((pNode = mpBucketArray[i]) != 0) {
            int k2 = pNode->pObj ? *pNode->pObj : 0;
            unsigned nNewBucketIndex = (unsigned)(pNode->key + k2) % nNewBucketCount;
            mpBucketArray[i] = pNode->mpNext;
            pNode->mpNext = pNewBucketArray[nNewBucketIndex];
            pNewBucketArray[nNewBucketIndex] = pNode;
        }
    }
    if (mnBucketCount > 1 && (HNode**)mpBucketArray != mpInlineBuckets) {
        if ((char*)mpBucketArray >= mpPoolBegin && (char*)mpBucketArray < mpPoolEnd) {
            *(HNode**)mpBucketArray = mpFreeList;
            mpFreeList = (HNode*)mpBucketArray;
            mpBucketArray = pNewBucketArray;
            mnBucketCount = nNewBucketCount;
            return;
        }
        eadelete(mpBucketArray);
    }
    mpBucketArray = pNewBucketArray;
    mnBucketCount = nNewBucketCount;
}
}}  // namespace EA::Trace

// @ 0x00925420
namespace EA { namespace Trace {
TraceHelper_s0092_45b0* TraceHelperTable::ReserveHelper(unsigned type, const char* name, int level, const int* loc)
{
    mMutex.Lock(&g_timeout_143dffc);
    void* m = eanew6(0x24, "EATrace/TraceHelper", 0, 0, 0, 0);
    TraceHelper_s0092_45b0* h = m ? new (m) TraceHelper_s0092_45b0(type, name, level, loc) : 0;
    mMutex.Unlock();
    return h;
}
}}  // namespace EA::Trace

// @ 0x00925540
namespace EA { namespace Trace {
TraceLogManagerRef::TraceLogManagerRef()
{
    f4 = 0; f0 = 0; mpLogManager = 0;
    ILogManager* m = GetLogManager();
    ILogManager* old = mpLogManager;
    if (m != old) {
        if (m) m->AddRef();
        mpLogManager = m;
        if (old) old->Release();
    }
    g_01668e9c->field->UpdateTracerRaw(mpLogManager);
}
}}  // namespace EA::Trace

// @ 0x009255a0
namespace EA { namespace Trace {
TraceHelperTable::TraceHelperTable()
{}
}}  // namespace EA::Trace

// @ 0x009255f0
namespace EA { namespace Trace {
void TempTraceHelperMap::ReleaseHelpers()
{
    mMutex.Lock(&g_timeout_143dffc);
    TempNode** pBucket = mTable.mpBucketArray;
    TempNode* pNode = *pBucket;
    if (!pNode) {
        do { ++pBucket; } while (*pBucket == 0);
        pNode = *pBucket;
    }
    TempNode* pEnd = mTable.mpBucketArray[mTable.mnBucketCount];
    while (pNode != pEnd) {
        char* h = pNode->mpHelper;
        if (h) {
            TraceHelperTable* t = g_01668e9c->field;
            if (t) t->ReleaseHelper((TraceHelper_s0092_45b0*)h);
            eadelete(h);
        }
        pNode = pNode->mpNext;
        if (!pNode) {
            do { pNode = pBucket[1]; ++pBucket; } while (!pNode);
        }
    }
    mTable.DoFreeNodes(mTable.mpBucketArray, mTable.mnBucketCount);
    mTable.mnElementCount = 0;
    mbHelpersReserved = false;
    mMutex.Unlock();
}
}}  // namespace EA::Trace

// @ 0x00925730
namespace EA { namespace Trace {
void* CreateEnabledValue()
{
    int* p = (int*)eanew(0x14, 4, 0, "OSGlobal", 0, 0, 0, 0);
    if (p) { p[1] = 0; p[0] = 0; p[4] = 1; return p; }
    return 0;
}
}}  // namespace EA::Trace

// @ 0x00925770
namespace EA { namespace Trace {
void* CreateTracerPtr()
{
    int* p = (int*)eanew(0x14, 4, 0, "OSGlobal", 0, 0, 0, 0);
    if (p) return ctor_00925540(p);
    return 0;
}
}}  // namespace EA::Trace

// @ 0x009257a0
namespace EA { namespace Trace {
void TempTraceHelperMap_s0092_5770::Destroy()
{
    ReleaseHelpers();
    ht.Clear();
    mMutex.Destroy();
}
}}  // namespace EA::Trace

// @ 0x009257e0
namespace EA { namespace Trace {
void HelperVec_s0092_5770::DoInsertValue(TraceHelper_s0092_5770** pos, TraceHelper_s0092_5770* const* val)
{
    if (mpEnd != mpCapacity) {
        TraceHelper_s0092_5770** e0 = mpEnd;
        TraceHelper_s0092_5770* const* v = val;
        if (v >= pos && v < e0) ++v;
        if (e0) *e0 = e0[-1];
        TraceHelper_s0092_5770** last = mpEnd - 1;
        size_t bytes = (size_t)((char*)last - (char*)pos);
        memmove(mpEnd - (last - pos), pos, bytes);
        *pos = *v;
        ++mpEnd;
        return;
    }
    unsigned cap = (unsigned)(mpEnd - mpBegin);
    cap = (cap > 0u) ? cap * 2 : 1;
    TraceHelper_s0092_5770** buf = cap ? (TraceHelper_s0092_5770**)eastl_new(cap * 4, "EATrace", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    int off = (int)((char*)pos - (char*)mpBegin);
    TraceHelper_s0092_5770** p = vec_move(buf, mpBegin, off);
    p = p + (off >> 2);
    if (p) *p = *val;
    int tail = (int)((char*)mpEnd - (char*)pos);
    TraceHelper_s0092_5770** e = vec_move(p + 1, pos, tail);
    e = e + (tail >> 2);
    if (mpBegin && ((int*)mpBegin)[-1]) eastl_delete(mpBegin);
    mpBegin = buf;
    mpEnd = e;
    mpCapacity = buf + cap;
}
}}  // namespace EA::Trace

// @ 0x009258f0
namespace EA { namespace Trace {
TraceHelperTable_s0092_5770* CreateHelperTable()
{
    TraceHelperTable_s0092_5770* t = (TraceHelperTable_s0092_5770*)eastl_new(0x58, "EATrace/TraceHelperTable", 0, 0, 0, 0);
    if (t) {
        *(void**)t = (void*)0x143e050;
        t->mTracer = 0;
        t->mVec.Zero();
        t->mMutex.Init(0, true);
        _InterlockedExchange(&t->mFlag, 0);
        t->mVec.Reserve(0x1000);
        return t;
    }
    return 0;
}
}}  // namespace EA::Trace

// @ 0x00925960
namespace EA { namespace Trace {
void TraceHelperTable_s0092_5770::UnregisterHelper(TraceHelper_s0092_5770* h)
{
    mMutex.Lock((const void*)0x143dffc);
    h->mTracer = 0;
    h->mIsFiltered = true;
    h->mIsFilterEvaluated = false;
    TraceHelper_s0092_5770** it = mVec.find(h);
    if (it != mVec.mpEnd) mVec.erase(it);
    mMutex.Unlock();
}
}}  // namespace EA::Trace

// @ 0x009259d0
namespace EA { namespace Trace {
TempTraceHelperMap_s0092_5770* TempTraceHelperMap_s0092_5770::Init()
{
    mMutex.Init(0, true);
    ht.mMaxLoad = g_01485720;
    ht.mGrowth = g_01470f1c;
    ht.mNextResize = 0;
    ht.mBucketCount = 1;
    ht.mpBuckets = (void*)0x154df28;
    ht.mElementCount = 0;
    ht.mNextResize = 0;
    ht.mbEnable = 1;
    return this;
}
}}  // namespace EA::Trace

// @ 0x00925a30
namespace EA { namespace Trace {
TraceHashtable_s0092_5770* TraceHashtable_s0092_5770::Init(unsigned a1, unsigned a2)
{
    char* self = (char*)this;
    union { FixedPool pool; RehashPolicy tmp; } u;
    FixedPool& pool = u.pool;
    {
        pool.mpHead = 0;
        char* buf = self + 0x138;
        pool.init(buf, 0x2f4, 0xc, 4, 0);
        pool.mBuf = buf;
        char* alloc = self + 0x34;
        buf += 0x2f4;
        pool.mBufEnd = buf;
        pool.mNodeSize = 0xc;
        pool.mAlloc = alloc;
        unsigned nb = policy_prime(0x40);
        Init7(nb, a1, a2, a2, a2, a2, &pool);
    }
    RehashPolicy& tmp = u.tmp;
    tmp.mMaxLoad = g_013f0620;
    tmp.mGrowth = g_01470f1c;
    tmp.mNextResize = 0;
    *(int*)&mPolicy.mMaxLoad = *(int*)&tmp.mMaxLoad;
    *(int*)&mPolicy.mGrowth = *(int*)&tmp.mGrowth;
    mPolicy.mNextResize = tmp.mNextResize;
    unsigned n = tmp.GetBucketCount(mElementCount);
    if (n > mBucketCount) DoRehash(n);
    return this;
}
}}  // namespace EA::Trace

// @ 0x00925b00
namespace EA { namespace Trace {
HelperTablePtr* HelperTablePtr::Init()
{
    w4 = w0 = 0;
    mpTable = 0;
    setTable(CreateHelperTable());
    return this;
}
}}  // namespace EA::Trace

// @ 0x00925b50
namespace EA { namespace Trace {
void TraceHelperTable_s0092_5770::RegisterHelper(TraceHelper_s0092_5770* h)
{
    mMutex.Lock((const void*)0x143dffc);
    h->mTracer = mTracer;
    h->mIsFiltered = true;
    h->mIsFilterEvaluated = false;
    mVec.push_back(h);
    mMutex.Unlock();
}
}}  // namespace EA::Trace
