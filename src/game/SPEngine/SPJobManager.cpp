// src/game/SPEngine/SPJobManager.cpp -- migrated from slice(s) s006925c0, s00691680, s006907e0, s0068f670, s0068e670 by tools/migrate/rewrite.py
// Object file: SPEngine/SPJobManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "SP/cJob.h"
#include "SP/JobCondition.h"
#include "SP/JobDependencyNode.h"
#include "SP/JobThreadNode.h"
#include "SP/JobWaitNode.h"
#include "EA/Thread/Mutex.h"
#include "EA/Thread/Semaphore.h"
#include "SP/cJobData.h"
#include "SP/cJobLink.h"
#include "SP/cJobManager.h"
#include "SP/cJobThread.h"
#include <new>
#include "EA/Thread/Thread.h"
#include <string.h>
#include "SP/cIJobManager.h"

// ---- items of slice s0068e670 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl SemaphorePost(void* self, int n);        // 0x0922740
extern "C" int*  __cdecl FUN_0068f4d0();                          // 0x068f4d0
static inline void** VT(void* p) { return *(void***)p; }
struct Mutex { uint32_t _[12]; void Lock(void*); void Unlock(); };
struct JobLock {
    void* vtbl0;            // +0x00
    void* vtbl1;            // +0x04
    void* f08;              // +0x08
    void* mRefObj;          // +0x0c
    void* mJob;             // +0x10
    JobLock(void* a, int b, void* c);
};
struct HObj { void Close(); };
struct ClsF4A0 { uint32_t f0; uint32_t f4; HObj h; void Reset(); };
struct ClsF540 { uint32_t f0, f4; Mutex m; int count; void Acquire(); void Release(); };
struct Inner570 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void v7(void*, int, int);       // slot 7 (0x1c)
};
struct Outer570 { uint32_t pad[10]; Inner570* mInner; };  // inner ptr at +0x28
struct VObj { virtual void v0(); virtual void v1(); };
struct ClsF5B0 { VObj* m; void Set(VObj* p); };
struct ListNode { ListNode* next; ListNode* prev; uint32_t pad[2]; };
// ---- items of slice s0068e670 end

// ---- items of slice s0068f670 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AutoRefCount {
    void* mpPtr;                    // +0
};
struct cJobDataNode { void* mpNext; void* mpPrev; };
extern unsigned int g_MutexFlags;   // 0x01403750
extern char sz_13ec47c[];           // 0x013ec47c
__declspec(noinline) void* EAAllocate(size_t size, const char* name, int, int, int, int);  // 0x00f473a0
__declspec(noinline) void  EADeallocate(void* p);   // 0x00f47380
struct IntrusiveList {
    IntrusiveList* mpNext;   // +0
    IntrusiveList* mpPrev;   // +4
    IntrusiveList();
    ~IntrusiveList();        // out of line in the image (0x00620230)
};
// @ 0x0068fa50
IntrusiveList::IntrusiveList() {
    mpPrev = this;
    mpNext = this;
}
inline void AppendTail(IntrusiveList* pList, IntrusiveList* pNode) {
    pNode->mpPrev = pList->mpPrev;
    pNode->mpNext = pList;
    pList->mpPrev = pNode;
    pNode->mpPrev->mpNext = pNode;
}
inline void ClearList(IntrusiveList* pAnchor) {
    IntrusiveList* p = pAnchor->mpNext;
    if (p != pAnchor) {
        for (;;) {
            IntrusiveList* pNext = p->mpNext;
            p->mpPrev = 0;
            p->mpNext = 0;
            p = pNext;
            if (pNext == pAnchor) break;
        }
    }
    pAnchor->mpPrev = 0;
    pAnchor->mpNext = 0;
}
template <class T>
struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject != 0) mpObject->Release(); }
    void Release() {
        if (mpObject != 0) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
    }
};
namespace EA {
namespace Thread {
class Mutex_s0068_f670 {
public:
    char mData[0x30];
    Mutex_s0068_f670(const void* pParams, bool bInit); // 0x009222a0
    ~Mutex_s0068_f670();                               // 0x00922130
    void Lock(unsigned int flags);          // 0x009221b0
    void Unlock();                          // 0x00922270
};
}
}
namespace EA {
namespace Thread {
class Semaphore_s0068_f670 {
public:
    char mData[0x10];
    Semaphore_s0068_f670(int initial); // 0x00922880
    ~Semaphore_s0068_f670();           // 0x00922610
    void Post(int count = 1);                       // 0x00922740
};
}
}
struct IUnknown32 {
    virtual int AddRef();           // +0
    virtual int Release();          // +4
};
template <class T>
struct EAVector_s0068_f670 {
    T* mpBegin;                     // +0
    T* mpEnd;                       // +4
    T* mpCap;                       // +8

    EAVector_s0068_f670() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~EAVector_s0068_f670() {
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            EADeallocate(mpBegin);
    }
};
struct AutoRefCount_s0068_f670 {
    void* mpPtr;                    // +0
    AutoRefCount_s0068_f670() : mpPtr(0) {}
};
struct cJobData;
class cJobManager;
struct cJobThread;
struct cJobLink;
struct JobDependencyNode {
    JobDependencyNode* mpNext;      // +0
    JobDependencyNode* mpPrev;      // +4
};
struct JobWaitNode {
    JobWaitNode* mpNext;            // +0
    JobWaitNode* mpPrev;            // +4
    EA::Thread::Semaphore_s0068_f670 mSemaphore; // +8
};
struct JobThreadNode {
    JobThreadNode* mpNext;          // +0
    JobThreadNode* mpPrev;          // +4
};
struct cJob {
    void* mpCallback;               // +0x00
    void* mpCallbackData;           // +0x04
    AutoRefCount_s0068_f670 mpExtraObject;     // +0x08
    char* mpDebugName;              // +0x0c
    int mPriority;                  // +0x10
    int mStatus;                    // +0x14
    unsigned int mThreadAffinity;   // +0x18
    int mSlot;                      // +0x1c
    void* mpReturnValue;            // +0x20
    void* mpCleanupReturnValue;     // +0x24

    int AddRef();
    int Release();
    int ContinueJob();
    bool Continuation(void* a, void* b);
};
struct cJobDataNode_s0068_f670 {
    void* mpNext; void* mpPrev;
    cJobDataNode_s0068_f670() { mpPrev = 0; mpNext = 0; }
};
struct cJobData : cJobDataNode_s0068_f670, cJob {
    cJobData();

    cJobManager* mpManager;         // +0x30
    bool mbSynchronousWait;         // +0x34
    char mPad35[3];
    IntrusiveList mDependencies;    // +0x38
    IntrusiveList mDependents;      // +0x40
    int mRealPriority;              // +0x48
    int mRefCount;                  // +0x4c
};
struct cJobThread : JobThreadNode, JobWaitNode {
    void* mThreadHandle;            // +0x20
    void* mThreadId;                // +0x24
    cJobManager* mpJobManager;      // +0x28
    unsigned int mAffinity;         // +0x2c
    int mCurrentPriority;           // +0x30
    cJobData* mCurrentJob;          // +0x34
    bool mbExit;                    // +0x38
};
struct cJobLink : JobDependencyNode {
    JobDependencyNode mDependentLink;  // +0x8
    cJobData* mpDependency;         // +0x10
    cJobData* mpDependent;          // +0x14
    bool isWeak;                    // +0x18
    char mPad19[3];
};
struct cIJobManager {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual cJobThread* CreateThread(unsigned int affinity, int a, int b);
    virtual void RemoveThread(cJobThread* pThread);
    virtual bool EndThread(cJobThread* pThread, int a, int b);
    virtual ~cIJobManager() {}
};
class cJobManager : public cIJobManager {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual cJobThread* CreateThread(unsigned int affinity, int a, int b); // slot5 (+0x14)
    virtual void RemoveThread(cJobThread* pThread);                        // slot6 (+0x18)
    virtual bool EndThread(cJobThread* pThread, int a, int b);             // slot7 (+0x1c)

    cJobManager();
    ~cJobManager();

    unsigned int mPad04;            // +0x04
    EA::Thread::Mutex_s0068_f670 mMutex;       // +0x08
    int mnLockCount;                // +0x38
    IntrusiveList mJobReadyCondition;       // +0x3c
    IntrusiveList mJobReadyOrSyncCondition; // +0x44
    IntrusiveList mJobs[9];         // +0x4c
    IntrusiveList mReadyList[32];   // +0x94
    unsigned int mValidAffinities;  // +0x194
    IntrusiveList mThreads;         // +0x198
    int mUnknown1a0;                // +0x1a0
    EAVector_s0068_f670<void*> mWaitingThreads;    // +0x1a4
    char mPad1b0[8];                // +0x1b0
    EAVector_s0068_f670<void*> mWaitingPriorities; // +0x1b8
    char mPad1c4[8];                // +0x1c4
    cJobThread* mpSyncThread;       // +0x1cc
    IntrusiveList mFreeLinks;       // +0x1d0
    IntrusiveList mFreeWaitNodes;   // +0x1d8
    void* mInitThreadFunc;          // +0x1e0

    cJobData* GetRunnableJob(cJobThread* pThread, int minPriority);
    JobWaitNode* GetFreeWaitNode();
    __declspec(noinline) void FreeJobUnderLock(EA::Thread::Mutex_s0068_f670** ppMutex, cJobData* pJob);
    bool GetFreeJob(cJob** ppOut);
    bool IsAffinityInUse(unsigned int affinity);
    __declspec(noinline) void InsertJobByPriority(IntrusiveList* pList, cJobData* job);
    cJobLink* GetFreeLink();
    __declspec(noinline) void GetJobStatus(cJobData* pJob);
    bool Init(unsigned int affinities, int threadCount);
    void Shutdown();
    void ScheduleJob(cJobData* job);
    void FailJobDependents(cJobData* job, bool weakOnly);
    void PreShutdown();
    void FailJob(cJobData* job);                                    // 0x00690f60
};
struct ProfHashNode {
    const void* mKey;               // +0
    ProfHashNode* mpNext;           // +4
};
class ProfHashTable {
public:
    ProfHashNode** DoAllocateBuckets(unsigned int nCount);  // 0x0068fa60
    void DoRehash(unsigned int nNewBucketCount);            // 0x0068fad0

    ProfHashNode** mpBuckets;       // +0x00
    unsigned int mnBuckets;         // +0x04
    unsigned int mnEntries;         // +0x08
    ProfHashNode** mpFreeList;      // +0x0c
    ProfHashNode** mpFixedBuckets;  // +0x10
    ProfHashNode** mpPoolBegin;     // +0x14
    ProfHashNode** mpPoolEnd;       // +0x18
    float mfLoadFactor;             // +0x1c
};
void cIJobManager::slot0() {}
void cIJobManager::slot1() {}
void cIJobManager::slot2() {}
void cIJobManager::slot3() {}
void cIJobManager::slot4() {}
cJobThread* cIJobManager::CreateThread(unsigned int, int, int) { return 0; }
void cIJobManager::RemoveThread(cJobThread*) {}
bool cIJobManager::EndThread(cJobThread*, int, int) { return false; }
void cJobManager::slot0() {}
void cJobManager::slot1() {}
void cJobManager::slot2() {}
void cJobManager::slot3() {}
void cJobManager::slot4() {}
cJobThread* cJobManager::CreateThread(unsigned int, int, int) { return 0; }
void cJobManager::RemoveThread(cJobThread*) {}
bool cJobManager::EndThread(cJobThread*, int, int) { return false; }
// ---- items of slice s0068f670 end

// ---- items of slice s006907e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IntrusiveList_s0069_07e0 {
    IntrusiveList_s0069_07e0* mpNext;   // +0
    IntrusiveList_s0069_07e0* mpPrev;   // +4
    IntrusiveList_s0069_07e0();
};
IntrusiveList_s0069_07e0::IntrusiveList_s0069_07e0() { mpPrev = this; mpNext = this; }
namespace EA {
namespace Thread {
class Mutex_s0069_07e0 {
public:
    char mData[0x30];
    void Lock(unsigned int flags);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    void Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
};
}
}
struct AutoRefCount_s0069_07e0 { void* mpPtr; };
struct cJobData_s0069_07e0;
class cJobManager_s0069_07e0;
struct cJobThread_s0069_07e0;
struct cJobLink_s0069_07e0;
struct cJob_s0069_07e0 {
    void* mpCallback;               // +0x00
    void* mpCallbackData;           // +0x04
    AutoRefCount_s0069_07e0 mpExtraObject;     // +0x08
    char* mpDebugName;              // +0x0c
    int mPriority;                  // +0x10
    int mStatus;                    // +0x14
    unsigned int mThreadAffinity;   // +0x18
    int mSlot;                      // +0x1c
    void* mpReturnValue;            // +0x20
    void* mpCleanupReturnValue;     // +0x24
    int AddRef();  // 0x0068f950 (cJob::AddRef)
    void Queue();  // 0x006909b0 (cJob::Queue)
    void AddDependency(cJob_s0069_07e0* other);  // 0x00691380 (cJob::AddDependency)
    void AddWeakDependency(cJob_s0069_07e0* other);  // 0x006913c0 (cJob::AddWeakDependency)
};
struct cJobData_s0069_07e0 : cJobDataNode, cJob_s0069_07e0 {
    cJobManager_s0069_07e0* mpManager;         // +0x30
    bool mbSynchronousWait;         // +0x34
    char mPad35[3];
    IntrusiveList_s0069_07e0 mDependencies;    // +0x38
    IntrusiveList_s0069_07e0 mDependents;      // +0x40
    int mRealPriority;              // +0x48
    int mRefCount;                  // +0x4c
};
struct cJobThread_s0069_07e0 {
    void* mpNext;                   // +0x00
    void* mpPrev;                   // +0x04
    char mPad08[0x18];              // +0x08 (JobWaitNode incl. semaphore)
    void* mThreadHandle;            // +0x20
    void* mThreadId;                // +0x24
    cJobManager_s0069_07e0* mpJobManager;      // +0x28
    unsigned int mAffinity;         // +0x2c
    int mCurrentPriority;           // +0x30
    cJobData_s0069_07e0* mCurrentJob;          // +0x34
    bool mbExit;                    // +0x38
};
struct cJobLink_s0069_07e0 : JobDependencyNode {
    JobDependencyNode mDependentLink;  // +0x8
    cJobData_s0069_07e0* mpDependency;         // +0x10
    cJobData_s0069_07e0* mpDependent;          // +0x14
    bool isWeak;                    // +0x18
};
struct EAVector { void* mpBegin; void* mpEnd; void* mpCapacity; };
class cJobManager_s0069_07e0 {
public:
    virtual void slot0_s0069_07e0();
    virtual void slot1_s0069_07e0();
    virtual void slot2_s0069_07e0();
    virtual void slot3_s0069_07e0();
    virtual void slot4_s0069_07e0();
    virtual cJobThread_s0069_07e0* CreateThread(unsigned int affinity, int a, int b); // +0x14
    virtual void RemoveThread_s0069_07e0(cJobThread_s0069_07e0* pThread);                        // +0x18
    virtual bool EndThread_s0069_07e0(cJobThread_s0069_07e0* pThread, int a, int b);             // +0x1c

    unsigned int mPad04;            // +0x04
    EA::Thread::Mutex_s0069_07e0 mMutex;       // +0x08
    int mUnknown38;                 // +0x38
    IntrusiveList_s0069_07e0 mJobReadyCondition;       // +0x3c
    IntrusiveList_s0069_07e0 mJobReadyOrSyncCondition; // +0x44
    IntrusiveList_s0069_07e0 mJobs[9];         // +0x4c
    IntrusiveList_s0069_07e0 mReadyList[32];   // +0x94
    unsigned int mValidAffinities;  // +0x194
    IntrusiveList_s0069_07e0 mThreads;         // +0x198
    int mActiveJobCount;            // +0x1a0
    EAVector mWaitingThreads;       // +0x1a4
    char mPad1b0[8];                // +0x1b0
    EAVector mWaitingPriorities;    // +0x1b8
    char mPad1c4[8];                // +0x1c4
    cJobThread_s0069_07e0* mpSyncThread;       // +0x1cc
    IntrusiveList_s0069_07e0 mFreeLinks;       // +0x1d0
    IntrusiveList_s0069_07e0 mFreeWaitNodes;   // +0x1d8
    void* mInitThreadFunc;          // +0x1e0

    void QueueJobUnderLock(cJobData_s0069_07e0* job);  // 0x006907e0 (cJobManager::QueueJobUnderLock)
    void PromoteJobPriorityUnderLock(cJobData_s0069_07e0* job, int priority);  // 0x006908a0 (cJobManager::PromoteJobPriorityUnderLock)
    void SetJobPriorityUnderLock(cJobData_s0069_07e0* job, int priority);  // 0x00690930 (cJobManager::SetJobPriorityUnderLock)
    void CheckDependentPriority(cJobData_s0069_07e0* job, int priority);  // 0x00690b50 (cJobManager::CheckDependentPriority)
    void InsertWaitingThread(cJobThread_s0069_07e0* t, int priority);  // 0x00691500 (cJobManager::InsertWaitingThread)
    void ScheduleJob(cJobData_s0069_07e0* job);  // 0x00690540 (cJobManager::ScheduleJob)
    void FailJob(cJobData_s0069_07e0* job);  // 0x00690f60 (cJobManager::FailJob)
    void FailNonRunnableJobs();  // 0x006910a0 (cJobManager::FailNonRunnableJobs)
    void FailJobDependents(cJobData_s0069_07e0* job, bool weakOnly);  // 0x00690630 (cJobManager::FailJobDependents)
    __declspec(noinline) void AddJobDependency(cJobData_s0069_07e0* dependent, cJobData_s0069_07e0* dependency, bool weak);  // 0x00691260 (cJobManager::AddJobDependency)
    cJobLink_s0069_07e0* GetFreeLink();  // 0x00690050 (cJobManager::GetFreeLink)
    void FlushWaitingLists();  // 0x006915c0 (cJobManager::FlushWaitingLists)
    void RebuildWaitingLists();
};
unsigned int GetMaxDependentPriority_s0069_07e0(cJobData_s0069_07e0* job);
void* operator new(size_t, const char* name, int, unsigned, const char* file, int line);   // 0x00f473a0
void  EASTL_allocator_deallocate(void* p);   // 0x00f47380
#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
struct WaitingList2 {
    cJob_s0069_07e0** mpBegin;          // +0
    cJob_s0069_07e0** mpEnd;            // +4
    cJob_s0069_07e0** mpCapacity;       // +8
    int mOverflowAllocator;  // +0xc
    void* mpPoolBegin;       // +0x10
    cJob_s0069_07e0** DoAllocate(const size_t& n) {
        if (n)
            return (cJob_s0069_07e0**)::operator new(n * sizeof(cJob_s0069_07e0*), "App", 0, 0, EASTL_ALLOC_FILE, 0xd1);
        return 0;
    }
    void DoFree(cJob_s0069_07e0** p) {
        if (p && p != mpPoolBegin)
            EASTL_allocator_deallocate(p);
    }
    void DoInsertValue(cJob_s0069_07e0** position, cJob_s0069_07e0* const& value);
};
unsigned int GetMaxDependentPriority_s0069_07e0(cJobData_s0069_07e0* job) {
    unsigned int maxPri = (unsigned int)job->mPriority;
    IntrusiveList_s0069_07e0* pAnchor = &job->mDependents;
    for (IntrusiveList_s0069_07e0* it = pAnchor->mpNext; it != pAnchor; it = it->mpNext) {
        cJobLink_s0069_07e0* link = (cJobLink_s0069_07e0*)((char*)it - 8);
        int pri = link->mpDependent->mRealPriority;
        if ((int)maxPri < pri) maxPri = (unsigned int)pri;
    }
    return maxPri;
}
void cJobManager_s0069_07e0::ScheduleJob(cJobData_s0069_07e0*) {}
// ---- items of slice s006907e0 end

// ---- items of slice s00691680 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* p);
struct IntrusiveList_s0069_1680 {
    IntrusiveList_s0069_1680* mpNext;
    IntrusiveList_s0069_1680* mpPrev;
    IntrusiveList_s0069_1680();
    bool empty() const { return mpPrev == this; }
    // unlink and clear (debug-style zeroing of the node)
    void remove() {
        IntrusiveList_s0069_1680* p = mpPrev;
        IntrusiveList_s0069_1680* n = mpNext;
        p->mpNext = n;
        n->mpPrev = p;
        mpPrev = 0;
        mpNext = 0;
    }
    // link this node before the anchor (push_back)
    void push_back_to(IntrusiveList_s0069_1680* anchor) {
        mpPrev = anchor->mpPrev;
        mpNext = anchor;
        anchor->mpPrev = this;
        mpPrev->mpNext = this;
    }
    // link this node after the anchor (push_front)
    void push_front_to(IntrusiveList_s0069_1680* anchor) {
        mpNext = anchor->mpNext;
        mpPrev = anchor;
        anchor->mpNext = this;
        mpNext->mpPrev = this;
    }
};
IntrusiveList_s0069_1680::IntrusiveList_s0069_1680() { mpPrev = this; mpNext = this; }
namespace EA {
namespace Thread {
class Mutex_s0069_1680 {
public:
    char mData[0x30];
    void Lock(unsigned int flags);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    void Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
};
}
}
namespace EA {
namespace Thread {
class Semaphore_s0069_1680 {
public:
    char mData[0x10];
    Semaphore_s0069_1680(int initial);
    void Post(int count);  // 0x00922740 (EA::Thread::Semaphore::Post)
    void Post();  // 0x00922740 (EA::Thread::Semaphore::Post)
    int Wait(unsigned int timeout);  // 0x00922690 (EA::Thread::Semaphore::Wait)
};
}
}
namespace EA {
namespace Thread {
class Thread_s0069_1680 {
public:
    char mData[4];
    int GetStatus(void* pStatus);                    // 0x00922a10
    int WaitForEnd(unsigned int timeout, int* pRet); // 0x00922940
};
}
}
namespace EA {
namespace Thread {
void* GetThreadId();                                 // 0x00921cc0
}
}
#define K_TIMEOUT ((unsigned int)&g_MutexFlags)
struct MutexScopedLock {
    EA::Thread::Mutex_s0069_1680* mpMutex;
    MutexScopedLock(EA::Thread::Mutex_s0069_1680* m) : mpMutex(m) { m->Lock(K_TIMEOUT); }
    ~MutexScopedLock() { mpMutex->Unlock(); }
};
struct cJobData_s0069_1680;
class cJobManager_s0069_1680;
struct cJobThread_s0069_1680;
struct cJobLink_s0069_1680;
struct JobDependencyNode_s0069_1680 : IntrusiveList_s0069_1680 {};
struct JobDependentNode : IntrusiveList_s0069_1680 {};
struct cJob_s0069_1680 {
    void* mpCallback;               // +0x00
    void* mpCallbackData;           // +0x04
    AutoRefCount mpExtraObject;     // +0x08
    char* mpDebugName;              // +0x0c
    int mPriority;                  // +0x10
    int mStatus;                    // +0x14
    unsigned int mThreadAffinity;   // +0x18
    int mSlot;                      // +0x1c
    void* mpReturnValue;            // +0x20
    void* mpCleanupReturnValue;     // +0x24
    bool Cancel(bool b);
};
struct cJobData_s0069_1680 : IntrusiveList_s0069_1680, cJob_s0069_1680 {
    cJobManager_s0069_1680* mpManager;         // +0x30
    bool mbSynchronousWait;         // +0x34
    char mPad35[3];
    IntrusiveList_s0069_1680 mDependencies;    // +0x38  (JobDependencyNode list)
    IntrusiveList_s0069_1680 mDependents;      // +0x40  (JobDependentNode list)
    int mRealPriority;              // +0x48
    int mRefCount;                  // +0x4c
    cJobManager_s0069_1680* GetManager() { return mpManager; }
};
struct JobWaitNode_s0069_1680 : IntrusiveList_s0069_1680 {
    EA::Thread::Semaphore_s0069_1680 mSemaphore;   // +0x08
};
struct cJobThread_s0069_1680 : IntrusiveList_s0069_1680, JobWaitNode_s0069_1680 {
    EA::Thread::Thread_s0069_1680 mThread;     // +0x20
    void* mThreadId;                // +0x24
    cJobManager_s0069_1680* mpJobManager;      // +0x28
    unsigned int mAffinity;         // +0x2c
    int mCurrentPriority;           // +0x30
    cJobData_s0069_1680* mCurrentJob;          // +0x34
    bool mbExit;                    // +0x38
    void Destruct();                // 0x0068f4e0
};
struct cJobLink_s0069_1680 : JobDependencyNode_s0069_1680, JobDependentNode {
    cJobData_s0069_1680* mpDependency;         // +0x10
    cJobData_s0069_1680* mpDependent;          // +0x14
    bool isWeak;                    // +0x18
};
struct TimeBudget {
    char mPad[0x18];
    long long mDeadline;
};
struct JobCondition {
    IntrusiveList_s0069_1680 mWaitList;
    void NotifyAll();               // 0x0068f5d0
};
struct Tag {};
struct HashNode { cJobData_s0069_1680* mKey; HashNode* mpNext; };
struct HashInsertResult { void* mIter; HashNode* mNode; bool mInserted; };
struct JobSet {
    unsigned int mBase;             // +0x00
    HashNode** mpBuckets;           // +0x04
    unsigned int mnBuckets;         // +0x08
    unsigned int mnElements;        // +0x0c
    char mPad10[0x1c - 0x10];
    HashNode* mpFreeList;           // +0x1c
    char mPad20[4];
    char* mpPoolBegin;              // +0x24
    char* mpPoolEnd;                // +0x28
    char mPad2c[4];
    HashNode** mpFixedBuckets;      // +0x30
    char mPad34[0x24c - 0x34];

    JobSet(const Tag& a, const Tag& b);                           // 0x00691400
    HashInsertResult insert(cJobData_s0069_1680* const& key, Tag t);         // 0x006909e0
    void FreeBuckets(HashNode** p, unsigned int n);               // 0x0068fb70
    unsigned int count(cJobData_s0069_1680* const& k) const {
        unsigned int n = 0;
        for (HashNode* p = mpBuckets[(unsigned int)k % mnBuckets]; p; p = p->mpNext)
            if (k == p->mKey)
                ++n;
        return n;
    }
    ~JobSet() {
        FreeBuckets(mpBuckets, mnBuckets);
        mnElements = 0;
        if (mnBuckets > 1 && mpBuckets != mpFixedBuckets) {
            if ((char*)mpBuckets < mpPoolBegin || mpPoolEnd <= (char*)mpBuckets)
                operator delete[](mpBuckets);
            else {
                *(HashNode**)mpBuckets = mpFreeList;
                mpFreeList = (HashNode*)mpBuckets;
            }
        }
    }
};
struct JobStack {
    cJobData_s0069_1680** mpBegin;
    cJobData_s0069_1680** mpEnd;
    cJobData_s0069_1680** mpCapacity;
    unsigned int mAlloc;
    cJobData_s0069_1680** mpFixed;
    cJobData_s0069_1680* mBuf[32];
    JobStack() {
        mpBegin = mBuf;
        mpEnd = mBuf;
        mpCapacity = mBuf + 32;
        mpFixed = mBuf;
    }
    ~JobStack() {
        if (mpBegin && mpBegin != mpFixed)
            operator delete[](mpBegin);
    }
    void DoInsertValueEnd(cJobData_s0069_1680** pos, cJobData_s0069_1680* const& v);    // 0x00690c90
    void push_back(cJobData_s0069_1680* const& v) {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) cJobData_s0069_1680*(v);
        else
            DoInsertValueEnd(mpEnd, v);
    }
    bool empty() const { return mpBegin == mpEnd; }
};
class cJobManager_s0069_1680 {
public:
    virtual void slot0_s0069_1680();
    virtual void slot1_s0069_1680();
    virtual void slot2_s0069_1680();
    virtual void slot3_s0069_1680();
    virtual void slot4_s0069_1680();
    virtual cJobThread_s0069_1680* CreateThread_s0069_1680(unsigned int affinity, int a, int b);
    virtual void RemoveThread_s0069_1680(cJobThread_s0069_1680* pThread);
    virtual bool EndThread_s0069_1680(cJobThread_s0069_1680* pThread, int a, int b);

    unsigned int mPad04;
    EA::Thread::Mutex_s0069_1680 mMutex;       // +0x08
    int mLockCount;                 // +0x38 (recursive lock depth, saved across waits)
    JobCondition mJobReadyCondition;        // +0x3c
    JobCondition mJobReadyOrSyncCondition;  // +0x44
    IntrusiveList_s0069_1680 mJobs[9];         // +0x4c
    IntrusiveList_s0069_1680 mReadyList[32];   // +0x94
    unsigned int mValidAffinities;  // +0x194
    IntrusiveList_s0069_1680 mThreads;         // +0x198
    int mActiveJobCount;            // +0x1a0
    EAVector mWaitingThreads;       // +0x1a4
    char mPad1b0[8];
    EAVector mWaitingPriorities;    // +0x1b8
    char mPad1c4[8];
    cJobThread_s0069_1680* mpSyncThread;       // +0x1cc
    IntrusiveList_s0069_1680 mFreeLinks;       // +0x1d0
    IntrusiveList_s0069_1680 mFreeWaitNodes;   // +0x1d8
    void* mInitThreadFunc;          // +0x1e0

    __declspec(noinline) void InsertWaitingThread(int priority);
    __declspec(noinline) void FlushWaitingLists();
    void AddWaitingJob(int priority);
    void FlushWaiting();
    bool CircularRef(cJob_s0069_1680* a, cJob_s0069_1680* b);                                   // 0x00691680
    void RunJob(MutexScopedLock* lock, cJobThread_s0069_1680* thread, cJobData_s0069_1680* job); // 0x00691d30
    bool RunUnderLock(MutexScopedLock* lock, cJobThread_s0069_1680* thread, TimeBudget* budget, bool noWait); // 0x00691f60
    void WaitForJobUnderLock(MutexScopedLock* lock, cJobData_s0069_1680* job);       // 0x00692150
    bool CancelJob(cJobData_s0069_1680* job, bool wait);                             // 0x00692330
    void DestroyJobThread(cJobThread_s0069_1680* thread);                            // 0x00692430
    cJobData_s0069_1680* GetRunnableJob(cJobThread_s0069_1680* pThread, int minPriority);       // 0x0068f670
    void ScheduleJob(cJobData_s0069_1680* job);                                      // 0x00690540
    void FailJob(cJobData_s0069_1680* job);                                          // 0x00690f60
    void FailJobDependents(cJobData_s0069_1680* job, bool b);                        // 0x00690630
    void FailNonRunnableJobs();                                           // 0x006910a0
    void FreeJobUnderLock(MutexScopedLock* lock, cJobData_s0069_1680* job);          // 0x0068f7c0
    void PromoteJobPriorityUnderLock(cJobData_s0069_1680* job, int priority);        // 0x006908a0
    void LowerJobPriority(cJobData_s0069_1680* job, int priority);                   // 0x00690930
    int ComputePriority(cJobData_s0069_1680* job);                                   // 0x0068ffb0
    void SyncThreadTime(unsigned int t);                                  // 0x00691500
    JobWaitNode_s0069_1680* AcquireWaitNode();                                       // 0x0068f700
    void WakeUp();                                                        // 0x006915c0
};
unsigned int GetCurrentThreadTime();                                      // 0x00921d70
// ---- items of slice s00691680 end

// ---- items of slice s006925c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Thread {
class Mutex_s0069_25c0 {
public:
    char mData[0x30];
    void Lock(unsigned int flags);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    void Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
};  // namespace EA::Thread
}
}
struct MutexScopedLock_s0069_25c0 {
    EA::Thread::Mutex_s0069_25c0* mpMutex;
    MutexScopedLock_s0069_25c0(EA::Thread::Mutex_s0069_25c0* m) : mpMutex(m) { m->Lock((unsigned int)&g_MutexFlags); }
    ~MutexScopedLock_s0069_25c0() { mpMutex->Unlock(); }
};
class cJobManager_s0069_25c0;
__declspec(noinline) int  FUN_00691f60(void* lock, void* a, void* b, void* c);
class cJobManager_s0069_25c0 {
public:
    char mPad00[8];
    EA::Thread::Mutex_s0069_25c0 mMutex;   // +0x08
    char mRest[0x1e4 - 0x38];
    bool Run(void* a, void* b, void* c);
    void WaitForJob(void* job);
};
// ---- items of slice s006925c0 end

// @ 0x0068f350
extern "C" int TryLockJobs(void* a, void* b, JobLock** out)
{
    (void)a; (void)b; (void)out;
    int* p = FUN_0068f4d0();
    if (!((char (__thiscall*)(void*, void*))VT(p)[0x10 / 4])(p, b)) return 0;
    p = FUN_0068f4d0();
    if (!((char (__thiscall*)(void*, void*))VT(p)[0x10 / 4])(p, b)) return 0;
    return 1;
}

// @ 0x0068f450
namespace EA {
unsigned int GetHighestBitPowerOf2(unsigned int v)
{
    int n = 0;
    if (v & 0xffff0000) { n = 0x10; v >>= 0x10; }
    if (v & 0xff00) { n += 8; v >>= 8; }
    if (v & 0xf0) { n += 4; v >>= 4; }
    if (v & 0xc) { n += 2; v >>= 2; }
    if (v & 2) { n += 1; }
    return n;
}
}  // namespace EA

// @ 0x0068f4a0
void ClsF4A0::Reset()
{
    f0 = 0;
    f4 = 0;
    h.Close();
}

// @ 0x0068f4e0
extern "C" void FUN_68F4E0(void* p)
{
    void* o = *(void**)((char*)p + 0x20);
    (void)o;
    *(uint32_t*)((char*)p + 8) = 0;
    *(uint32_t*)((char*)p + 0xc) = 0;
}

// @ 0x0068f540
void ClsF540::Acquire()
{
    m.Lock((void*)0x01403750);
    ++count;
}

// @ 0x0068f560
void ClsF540::Release()
{
    --count;
    m.Unlock();
}

// @ 0x0068f570
extern "C" int FUN_68F570(Outer570* p)
{
    void (*fn)(void*) = *(void (**)(void*))((char*)p->mInner + 0x1e0);
    if (fn)
        fn(p);
    ((Inner570*)p->mInner)->v7(p, 0, 0);
    return 0;
}

// @ 0x0068f5a0
struct Callable68F5A0 { virtual void f(void* a); };
extern "C" void FUN_68F5A0(void* a, Callable68F5A0* b)
{
    b->f(a);
}

// @ 0x0068f5b0
void ClsF5B0::Set(VObj* p)
{
    VObj* old = m;
    m = p;
    if (old)
        old->v1();
}

// @ 0x0068f5d0
extern "C" void FUN_68F5D0(ListNode* h)
{
    while (h->next != h) {
        ListNode* n = h->next;
        ListNode* p = n->next;
        if (p != n) {
            ListNode* q = n->prev;
            p->prev = q;
            q->next = p;
            n->next = n;
            n->prev = n;
            SemaphorePost((char*)n + 0x10, 1);
        }
    }
}

// @ 0x0068f600
extern "C" void* FUN_68F600(void* p)
{
    *(uint32_t*)((char*)p + 4) = 0;
    *(uint32_t*)((char*)p + 0) = 0;
    char* s = (char*)p + 8;
    *(uint32_t*)(s + 4) = 0;
    *(uint32_t*)(s + 0) = 0;
    *(void**)(s) = s;
    *(void**)(s + 4) = s;
    return p;
}

// @ 0x0068f670
cJobData* cJobManager::GetRunnableJob(cJobThread* pThread, int minPriority)
{
    unsigned int mask = pThread->mAffinity;
    cJobData* pBest = 0;
    while (mask) {
        unsigned int v = mask;
        int idx = 0;
        if (v & 0xffff0000) { idx = 0x10; v >>= 0x10; }
        if (v & 0xff00)     { idx += 8;   v >>= 8; }
        if (v & 0xf0)       { idx += 4;   v >>= 4; }
        if (v & 0xc)        { idx += 2;   v >>= 2; }
        if (v & 2)          { idx += 1; }
        int bit = 1 << idx;
        IntrusiveList* pList = &mReadyList[idx];
        mask &= ~bit;
        if (pList->mpPrev != pList) {
            cJobData* pJob = (cJobData*)pList->mpNext;
            int pri = pJob->mRealPriority;
            if (pri >= minPriority) {
                pBest = pJob;
                minPriority = pri;
            }
        }
    }
    return pBest;
}

// @ 0x0068f700
JobWaitNode* cJobManager::GetFreeWaitNode()
{
    IntrusiveList* pAnchor = &mFreeWaitNodes;
    if (pAnchor->mpPrev != pAnchor) {
        IntrusiveList* pNode = pAnchor->mpNext;
        pNode->mpNext->mpPrev = pAnchor;
        pAnchor->mpNext = pNode->mpNext;
        if (pNode != pAnchor) {
            pNode->mpPrev = 0;
            pNode->mpNext = 0;
        }
        return (JobWaitNode*)pNode;
    }
    JobWaitNode* pNode = (JobWaitNode*)EAAllocate(0x18, "App/cJobManager/WaitNode", 0, 0, 0, 0);
    if (pNode) {
        pNode->mpPrev = 0;
        pNode->mpNext = 0;
        new (&pNode->mSemaphore) EA::Thread::Semaphore_s0068_f670(0);
        pNode->mpNext = (JobWaitNode*)pNode;
        pNode->mpPrev = (JobWaitNode*)pNode;
    }
    return pNode;
}

// @ 0x0068f7c0
void cJobManager::FreeJobUnderLock(EA::Thread::Mutex_s0068_f670** ppMutex, cJobData* pJob)
{
    FailJob(pJob);
    void (*pCleanup)(void*) = (void (*)(void*))pJob->mpCleanupReturnValue;
    pJob->mpCleanupReturnValue = 0;
    void* pReturn = pJob->mpReturnValue;
    pJob->mpReturnValue = 0;
    AutoRef<IUnknown32> oldExtra;
    oldExtra.mpObject = (IUnknown32*)pJob->mpExtraObject.mpPtr;
    pJob->mpExtraObject.mpPtr = 0;
    IntrusiveList* pNode = (IntrusiveList*)pJob;
    pNode->mpPrev->mpNext = pNode->mpNext;
    pNode->mpNext->mpPrev = pNode->mpPrev;
    pNode->mpPrev = 0;
    pNode->mpNext = 0;
    AppendTail(&mJobs[0], pNode);
    pJob->mSlot = 0;
    int nWait = mnLockCount;
    mnLockCount = 0;
    if (ppMutex != 0) {
        for (int i = 0; i < nWait; ++i) (*ppMutex)->Unlock();
        (*ppMutex)->Unlock();
    } else {
        for (int i = 0; i < nWait; ++i) mMutex.Unlock();
        mMutex.Unlock();
    }
    if (pCleanup != 0) pCleanup(pReturn);
    oldExtra.Release();
    if (ppMutex != 0) {
        (*ppMutex)->Lock((unsigned int)&g_MutexFlags);
        for (int i = 0; i < nWait; ++i) (*ppMutex)->Lock((unsigned int)&g_MutexFlags);
    } else {
        mMutex.Lock((unsigned int)&g_MutexFlags);
        for (int i = 0; i < nWait; ++i) mMutex.Lock((unsigned int)&g_MutexFlags);
    }
    mnLockCount = nWait;
}

// @ 0x0068f950
int cJob::AddRef()
{
    cJobData* p = static_cast<cJobData*>(this);
    long* pRC = (long*)&p->mRefCount;
    return _InterlockedExchangeAdd(pRC, 1) + 1;
}

// @ 0x0068f970
int cJob::ContinueJob()
{
    cJobData* p = static_cast<cJobData*>(this);
    EA::Thread::Mutex_s0068_f670* pMutex = &p->mpManager->mMutex;
    pMutex->Lock((unsigned int)&g_MutexFlags);
    int status = p->mStatus;
    pMutex->Unlock();
    return status;
}

// @ 0x0068f9f0
bool cJob::Continuation(void* a, void* b)
{
    cJobData* p = static_cast<cJobData*>(this);
    EA::Thread::Mutex_s0068_f670* pMutex = &p->mpManager->mMutex;
    pMutex->Lock((unsigned int)&g_MutexFlags);
    if (p->mStatus == 4 || p->mStatus == 5) {
        p->mpCallback = a;
        p->mpCallbackData = b;
        p->mStatus = 5;
    }
    pMutex->Unlock();
    return true;
}

// @ 0x0068fad0
void ProfHashTable::DoRehash(unsigned int nNewBucketCount)
{
    ProfHashNode** pNew = DoAllocateBuckets(nNewBucketCount);
    for (unsigned int i = 0; i < mnBuckets; ++i) {
        ProfHashNode* pNode = mpBuckets[i];
        while (pNode != 0) {
            unsigned int idx = (unsigned int)pNode->mKey % nNewBucketCount;
            mpBuckets[i] = pNode->mpNext;
            pNode->mpNext = pNew[idx];
            pNew[idx] = pNode;
            pNode = mpBuckets[i];
        }
    }
    ProfHashNode** pOld = mpBuckets;
    if (mnBuckets > 1 && pOld != mpFixedBuckets) {
        if (pOld >= mpPoolBegin && pOld < mpPoolEnd) {
            *pOld = (ProfHashNode*)mpFreeList;
            mpFreeList = pOld;
        } else {
            EADeallocate(pOld);
        }
    }
    mpBuckets = pNew;
    mnBuckets = nNewBucketCount;
}

// @ 0x0068fbe0
cJobData::cJobData()
{
    _InterlockedExchange((volatile long*)&mRefCount, 0);
    mpDebugName = sz_13ec47c;
    if (mpExtraObject.mpPtr) {
        IUnknown32* pExtra = (IUnknown32*)mpExtraObject.mpPtr;
        mpExtraObject.mpPtr = 0;
        pExtra->Release();
    }
    mpReturnValue = 0;
    mpCleanupReturnValue = 0;
}

// @ 0x0068fc60
cJobManager::~cJobManager()
{
}

// @ 0x0068fd40
void cJobManager::PreShutdown()
{
    IntrusiveList* pAnchor = &mThreads;
    for (;;) {
        IntrusiveList* pNode = pAnchor->mpNext;
        if (pNode == pAnchor) break;
        while (pNode == (IntrusiveList*)mpSyncThread) {
            pNode = pNode->mpNext;
            if (pNode == pAnchor) goto done;
        }
        RemoveThread((cJobThread*)pNode);
        if (pNode == pAnchor) break;
    }
done:
    while (EndThread(mpSyncThread, 0, 1)) {}
}

// @ 0x0068fda0
bool cJobManager::GetFreeJob(cJob** ppOut)
{
    mMutex.Lock((unsigned int)&g_MutexFlags);
    cJobData* pJob;
    IntrusiveList* pFree = &mJobs[0];
    if (pFree->mpPrev == pFree) {
        void* pMem = EAAllocate(0x50, "App/cJobManager/cJob", 0, 0, 0, 0);
        pJob = pMem ? new (pMem) cJobData : 0;
    } else {
        IntrusiveList* pNode = pFree->mpNext;
        pNode->mpNext->mpPrev = pFree;
        pFree->mpNext = pNode->mpNext;
        pJob = (pNode != pFree) ? (cJobData*)pNode : 0;
        if (pJob != 0) {
            pNode->mpPrev = 0;
            pNode->mpNext = 0;
        }
    }
    cJob* pOut = 0;
    if (pJob != 0) {
        pOut = pJob;
        pOut->AddRef();
        pOut->mpCallback = 0;
        pOut->mpCallbackData = 0;
        if (pJob->mpExtraObject.mpPtr) {
            IUnknown32* pExtra = (IUnknown32*)pJob->mpExtraObject.mpPtr;
            pJob->mpExtraObject.mpPtr = 0;
            pExtra->Release();
        }
        pJob->mpDebugName = 0;
        pJob->mPriority = 0;
        pJob->mRealPriority = 0;
        pJob->mStatus = 1;
        pJob->mThreadAffinity = 0xffffffff;
        pJob->mSlot = 0xffffffff;
        pJob->mpManager = this;
        pJob->mbSynchronousWait = false;
        IntrusiveList* pReady = &mJobs[1];
        AppendTail(pReady, (IntrusiveList*)pJob);
    }
    *ppOut = pOut;
    bool ok = (pJob != 0);
    mMutex.Unlock();
    return ok;
}

// @ 0x0068fed0
bool cJobManager::IsAffinityInUse(unsigned int affinity)
{
    mMutex.Lock((unsigned int)&g_MutexFlags);
    if (affinity == 0xffffffff && mJobs[4].mpPrev != &mJobs[4]) {
        mMutex.Unlock();
        return true;
    }
    for (int i = 0; i < 0x20; ++i) {
        if ((affinity & (1u << i)) && mReadyList[i].mpPrev != &mReadyList[i]) {
            mMutex.Unlock();
            return true;
        }
    }
    for (IntrusiveList* it = mJobs[4].mpNext; it != &mJobs[4]; it = it->mpNext) {
        if (((cJobData*)it)->mThreadAffinity & affinity) {
            mMutex.Unlock();
            return true;
        }
    }
    mMutex.Unlock();
    return false;
}

// @ 0x0068ffb0
unsigned int GetMaxDependentPriority(cJobData* job)
{
    unsigned int maxPri = (unsigned int)job->mPriority;
    IntrusiveList* pAnchor = &job->mDependents;
    for (IntrusiveList* it = pAnchor->mpNext; it != pAnchor; it = it->mpNext) {
        cJobLink* link = (cJobLink*)((char*)it - 8);
        cJobData* dep = link->mpDependent;
        int pri = dep->mRealPriority;
        if ((int)maxPri < pri) maxPri = (unsigned int)pri;
    }
    return maxPri;
}

// @ 0x0068fff0
void cJobManager::InsertJobByPriority(IntrusiveList* pList, cJobData* job)
{
    IntrusiveList* pJob = (IntrusiveList*)job;
    IntrusiveList* pPrev = pJob->mpPrev;
    IntrusiveList* pNext = pJob->mpNext;
    pPrev->mpNext = pNext;
    pNext->mpPrev = pPrev;
    pJob->mpNext = 0;
    pJob->mpPrev = 0;
    IntrusiveList* first = pList->mpNext;
    job->mStatus = 3;
    IntrusiveList* pos = first;
    if (first != pList) {
        int pri = job->mRealPriority;
        IntrusiveList* node = pList->mpPrev;
        for (;;) {
            if (pri <= ((cJobData*)node)->mRealPriority) {
                pos = node->mpNext;
                break;
            }
            if (first == node) {
                pos = node;
                break;
            }
            node = node->mpPrev;
        }
    }
    IntrusiveList* prev = pos->mpPrev;
    pos->mpPrev = pJob;
    prev->mpNext = pJob;
    pJob->mpPrev = prev;
    pJob->mpNext = pos;
}

// @ 0x00690050
cJobLink* cJobManager::GetFreeLink()
{
    IntrusiveList* pAnchor = &mFreeLinks;
    // Nodes are appended at the tail (AppendTail), so the free link comes off the tail: the
    // anchor's mpPrev is the node, and mpNext of that node's predecessor is relinked to the
    // anchor (`mov 0x4(%edx),%ecx; mov 0x4(%ecx),%esi; mov %edx,(%esi)` at 0x0069008c).
    if (pAnchor->mpPrev != pAnchor) {
        IntrusiveList* pNode = pAnchor->mpPrev;
        IntrusiveList* pPrev = pNode->mpPrev;
        pPrev->mpNext = pAnchor;
        pAnchor->mpPrev = pPrev;
        if (pNode != pAnchor) {
            pNode->mpPrev = 0;
            pNode->mpNext = 0;
        }
        return (cJobLink*)pNode;
    }
    cJobLink* pLink = (cJobLink*)EAAllocate(0x1c, "App/cJobManager/cJobLink", 0, 0, 0, 0);
    if (pLink) {
        ((IntrusiveList*)pLink)->mpPrev = 0;
        ((IntrusiveList*)pLink)->mpNext = 0;
        pLink->mDependentLink.mpPrev = 0;
        pLink->mDependentLink.mpNext = 0;
    }
    return pLink;
}

// @ 0x006900b0
void cJobManager::GetJobStatus(cJobData* pJob)
{
    EA::Thread::Mutex_s0068_f670* pMutex = &mMutex;
    pMutex->Lock((unsigned int)&g_MutexFlags);
    FreeJobUnderLock(&pMutex, pJob);
    pMutex->Unlock();
}

// @ 0x00690120
int cJob::Release()
{
    cJobData* p = static_cast<cJobData*>(this);
    long* pRC = (long*)&p->mRefCount;
    int n = _InterlockedExchangeAdd(pRC, -1) - 1;
    if (n == 0) {
        p->mpManager->GetJobStatus(p);
    }
    return n;
}

// @ 0x00690210
cJobManager::cJobManager()
: mMutex(0, true), mnLockCount(0), mValidAffinities(0),
      mUnknown1a0(0), mpSyncThread(0), mInitThreadFunc(0)
{
}

// @ 0x00690330
bool cJobManager::Init(unsigned int affinities, int threadCount)
{
    mInitThreadFunc = (void*)threadCount;
    mnLockCount = 0;
    if (mpSyncThread == 0) {
        mpSyncThread = CreateThread(0x80000000, 0, -1);
        mpSyncThread->mThreadId = 0;
    }
    unsigned int bit = 1;
    for (unsigned int i = 0; i < 0x20; ++i) {
        if (affinities & bit)
            CreateThread(0x80000000, 1, (int)i);
        bit = (bit << 1) | (bit >> 31);
    }
    unsigned int used = 0;
    for (IntrusiveList* it = mThreads.mpNext; it != &mThreads; it = it->mpNext) {
        cJobThread* t = (cJobThread*)it;
        if (t->mThreadId != 0)
            used |= t->mAffinity;
    }
    mValidAffinities = used;
    return true;
}

// @ 0x006903c0
void cJobManager::Shutdown()
{
    slot2();
    if (mpSyncThread != 0) {
        RemoveThread(mpSyncThread);
        mpSyncThread = 0;
    }
    for (int i = 0; i < 9; ++i) {
        IntrusiveList* pList = &mJobs[i];
        while (pList->mpPrev != pList) {
            IntrusiveList* pNode = pList->mpPrev;
            pNode->mpPrev->mpNext = pList;
            pList->mpPrev = pNode->mpPrev;
            if (pNode != pList) {
                pNode->mpPrev = 0;
                pNode->mpNext = 0;
            }
            cJobData* pJob = (cJobData*)pNode;
            if (pJob->mpExtraObject.mpPtr != 0) {
                IUnknown32* pExtra = (IUnknown32*)pJob->mpExtraObject.mpPtr;
                pJob->mpExtraObject.mpPtr = 0;
                pExtra->Release();
            }
            if (pJob != 0) {
                ClearList(&pJob->mDependents);
                ClearList(&pJob->mDependencies);
                EADeallocate(pJob);
            }
        }
    }
    IntrusiveList* pList = &mFreeLinks;
    while (pList->mpPrev != pList) {
        IntrusiveList* pNode = pList->mpPrev;
        pNode->mpPrev->mpNext = pList;
        pList->mpPrev = pNode->mpPrev;
        if (pNode != pList) { pNode->mpPrev = 0; pNode->mpNext = 0; }
        EADeallocate(pNode);
    }
    pList = &mFreeWaitNodes;
    while (pList->mpPrev != pList) {
        IntrusiveList* pNode = pList->mpPrev;
        pNode->mpPrev->mpNext = pList;
        pList->mpPrev = pNode->mpPrev;
        if (pNode != pList) { pNode->mpPrev = 0; pNode->mpNext = 0; }
        if (pNode != 0) {
            ((JobWaitNode*)pNode)->mSemaphore.~Semaphore_s0068_f670();
            EADeallocate(pNode);
        }
    }
}

// @ 0x00690540
void cJobManager::ScheduleJob(cJobData* job)
{
    unsigned int aff = job->mThreadAffinity;
    if ((mValidAffinities & aff) == 0) {
        FailJob(job);
        return;
    }
    if (aff == 0xffffffff) {
        InsertJobByPriority(&mJobs[3], job);
        IntrusiveList* pCond = &mJobReadyCondition;
        if (pCond->mpPrev != pCond) {
            IntrusiveList* n = pCond->mpNext;
            if (n->mpPrev != n) {
                IntrusiveList* nx = n->mpNext;
                IntrusiveList* pv = n->mpPrev;
                nx->mpPrev = pv;
                pv->mpNext = nx;
                n->mpNext = n;
                n->mpPrev = n;
                ((JobWaitNode*)n)->mSemaphore.Post(1);
            }
        }
        pCond = &mJobReadyOrSyncCondition;
        if (pCond->mpPrev != pCond) {
            IntrusiveList* n = pCond->mpNext;
            if (n->mpPrev != n) {
                IntrusiveList* nx = n->mpNext;
                IntrusiveList* pv = n->mpPrev;
                nx->mpPrev = pv;
                pv->mpNext = nx;
                n->mpNext = n;
                n->mpPrev = n;
                ((JobWaitNode*)n)->mSemaphore.Post();
            }
        }
    } else {
        unsigned int a = aff;
        int idx = 0;
        while (!(a & 1)) { a >>= 1; ++idx; }
        InsertJobByPriority(&mReadyList[idx], job);
        for (IntrusiveList* it = mThreads.mpNext; it != &mThreads; it = it->mpNext) {
            cJobThread* t = (cJobThread*)it;
            if (t->mThreadId != 0 && (job->mThreadAffinity & t->mAffinity) != 0) {
                JobWaitNode* wait = (JobWaitNode*)((char*)t + 8);
                if (wait->mpPrev != wait) {
                    JobWaitNode* nx = wait->mpNext;
                    JobWaitNode* pv = wait->mpPrev;
                    nx->mpPrev = pv;
                    pv->mpNext = nx;
                    wait->mpNext = wait;
                    wait->mpPrev = wait;
                    wait->mSemaphore.Post(1);
                }
            }
        }
    }
}

// @ 0x00690630
void cJobManager::FailJobDependents(cJobData* job, bool weakOnly)
{
    IntrusiveList keep;
    IntrusiveList* pList = &job->mDependents;
    while (pList->mpPrev != pList) {
        IntrusiveList* pNode = pList->mpPrev;
        cJobData* pDep = (cJobData*)((char*)pNode - 8);
        cJobLink* pLink = (cJobLink*)pDep;
        cJobData* dep = pLink->mpDependent;
        pNode->mpPrev->mpNext = pNode->mpNext;
        pNode->mpNext->mpPrev = pNode->mpPrev;
        pNode->mpNext = 0;
        pNode->mpPrev = 0;
        if (!pLink->isWeak) {
            pLink->mpPrev->mpNext = pLink->mpNext;
            pLink->mpNext->mpPrev = pLink->mpPrev;
            pLink->mpPrev = 0;
            pLink->mpNext = 0;
            AppendTail(&mFreeLinks, (IntrusiveList*)pLink);
            if (weakOnly) {
                if (dep->mDependencies.mpPrev == &dep->mDependencies && dep->mStatus == 2)
                    ScheduleJob(dep);
            } else {
                FailJob(dep);
            }
        } else if (!weakOnly) {
            pLink->mpPrev->mpNext = pLink->mpNext;
            pLink->mpNext->mpPrev = pLink->mpPrev;
            pLink->mpPrev = 0;
            pLink->mpNext = 0;
            AppendTail(&mFreeLinks, (IntrusiveList*)pLink);
            FailJob(dep);
        } else {
            AppendTail(&keep, pNode);
        }
    }
    while (keep.mpPrev != &keep) {
        IntrusiveList* pNode = keep.mpPrev;
        pNode->mpPrev->mpNext = pNode->mpNext;
        pNode->mpNext->mpPrev = pNode->mpPrev;
        pNode->mpNext = 0;
        pNode->mpPrev = 0;
        AppendTail(pList, pNode);
    }
    for (IntrusiveList* p = keep.mpNext; p != &keep; ) {
        IntrusiveList* pNext = p->mpNext;
        p->mpPrev = 0;
        p->mpNext = 0;
        p = pNext;
    }
}

// @ 0x006907e0
void cJobManager_s0069_07e0::QueueJobUnderLock(cJobData_s0069_07e0* job)
{
    mMutex.Lock((unsigned int)&g_MutexFlags);
    if (job->mStatus == 1) {
        job->AddRef();
        if (job->mDependencies.mpPrev == &job->mDependencies) {
            ScheduleJob(job);
        } else {
            IntrusiveList_s0069_07e0* pNode = (IntrusiveList_s0069_07e0*)job;
            pNode->mpPrev->mpNext = pNode->mpNext;
            pNode->mpNext->mpPrev = pNode->mpPrev;
            pNode->mpPrev = 0;
            pNode->mpNext = 0;
            job->mStatus = 2;
            IntrusiveList_s0069_07e0* pList = &mJobs[2];
            pNode->mpPrev = pList->mpPrev;
            pNode->mpNext = pList;
            pList->mpPrev->mpNext = pNode;
            pList->mpPrev = pNode;
        }
    }
    mMutex.Unlock();
}

// @ 0x006908a0
void cJobManager_s0069_07e0::PromoteJobPriorityUnderLock(cJobData_s0069_07e0* job, int priority)
{
    if (job->mStatus == 3) {
        IntrusiveList_s0069_07e0* pNode = (IntrusiveList_s0069_07e0*)job;
        pNode->mpPrev->mpNext = pNode->mpNext;
        pNode->mpNext->mpPrev = pNode->mpPrev;
        pNode->mpPrev = 0;
        pNode->mpNext = 0;
        job->mStatus = 2;
        IntrusiveList_s0069_07e0* pList = &mJobs[2];
        pNode->mpPrev = pList->mpPrev;
        pNode->mpNext = pList;
        pList->mpPrev->mpNext = pNode;
        pList->mpPrev = pNode;
        ScheduleJob(job);
    }
    job->mRealPriority = priority;
    IntrusiveList_s0069_07e0* pAnchor = &job->mDependents;
    for (IntrusiveList_s0069_07e0* it = pAnchor->mpNext; it != pAnchor; it = it->mpNext) {
        cJobLink_s0069_07e0* link = (cJobLink_s0069_07e0*)((char*)it - 8);
        cJobData_s0069_07e0* dep = link->mpDependent;
        if (dep->mRealPriority < job->mRealPriority)
            PromoteJobPriorityUnderLock(dep, job->mRealPriority);
    }
}

// @ 0x00690930
void cJobManager_s0069_07e0::SetJobPriorityUnderLock(cJobData_s0069_07e0* job, int priority)
{
    int oldPriority = job->mRealPriority;
    job->mRealPriority = priority;
    if (job->mStatus == 3) {
        IntrusiveList_s0069_07e0* pNode = (IntrusiveList_s0069_07e0*)job;
        pNode->mpPrev->mpNext = pNode->mpNext;
        pNode->mpNext->mpPrev = pNode->mpPrev;
        pNode->mpPrev = 0;
        pNode->mpNext = 0;
        job->mStatus = 2;
        IntrusiveList_s0069_07e0* pList = &mJobs[2];
        pNode->mpPrev = pList->mpPrev;
        pNode->mpNext = pList;
        pList->mpPrev->mpNext = pNode;
        pList->mpPrev = pNode;
        ScheduleJob(job);
    }
    IntrusiveList_s0069_07e0* pAnchor = &job->mDependents;
    for (IntrusiveList_s0069_07e0* it = pAnchor->mpNext; it != pAnchor; it = it->mpNext) {
        cJobLink_s0069_07e0* link = (cJobLink_s0069_07e0*)((char*)it - 8);
        CheckDependentPriority(link->mpDependent, oldPriority);
    }
}

// @ 0x006909b0
void cJob_s0069_07e0::Queue()
{
    cJobData_s0069_07e0* p = static_cast<cJobData_s0069_07e0*>(this);
    p->mpManager->QueueJobUnderLock(p);
}

// @ 0x006909e0
void* ProfTable_DoInsertValue(void* self, void* result, void* key)
{
    (void)self; (void)result; (void)key;
    return 0;
}

// @ 0x00690b50
void cJobManager_s0069_07e0::CheckDependentPriority(cJobData_s0069_07e0* job, int priority)
{
    int pri = job->mRealPriority;
    if (pri == priority) {
        int maxp = GetMaxDependentPriority_s0069_07e0(job);
        if (maxp < pri)
            SetJobPriorityUnderLock(job, maxp);
    }
}

// @ 0x00690b80
void WaitingList1_Insert(void* vec, void* pos, void* value)
{
    (void)vec; (void)pos; (void)value;
}

// @ 0x00690c90
void WaitingList2::DoInsertValue(cJob_s0069_07e0** position, cJob_s0069_07e0* const& value)
{
    if (mpEnd != mpCapacity) {
        cJob_s0069_07e0* const* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) cJob_s0069_07e0*(*(mpEnd - 1));
        memmove(mpEnd - ((mpEnd - 1) - position), position, (size_t)((char*)(mpEnd - 1) - (char*)position));
        *position = *pValue;
        ++mpEnd;
    } else {
        const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
        const size_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        cJob_s0069_07e0** const pNewData = DoAllocate(nNewSize);
        cJob_s0069_07e0** pNewEnd = (cJob_s0069_07e0**)memcpy(pNewData, mpBegin, (size_t)((char*)position - (char*)mpBegin)) + (position - mpBegin);
        ::new (pNewEnd) cJob_s0069_07e0*(value);
        ++pNewEnd;
        pNewEnd = (cJob_s0069_07e0**)memcpy(pNewEnd, position, (size_t)((char*)mpEnd - (char*)position)) + (mpEnd - position);
        DoFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00690da0
SP::cJobThread * SP::cJobManager::CreateJobThread(unsigned int affinity, bool a, int b)
{
    (void)affinity; (void)a; (void)b;
    return 0;
}

// @ 0x00690f60
void SP::cJobManager::FailJob(SP::cJobData & job)
{
    (void)job;
}

// @ 0x006910a0
void SP::cJobManager::FailNonRunnableJobs()
{
}

// @ 0x00691260
void cJobManager_s0069_07e0::AddJobDependency(cJobData_s0069_07e0* dependent, cJobData_s0069_07e0* dependency, bool weak)
{
    mMutex.Lock((unsigned int)&g_MutexFlags);
    switch (dependent->mStatus) {
    case 1:
    case 2:
    case 4:
    case 5:
        if (dependency->mStatus == 8) {
            if (!weak)
                FailJob(dependent);
        } else if (dependency->mStatus != 7) {
            cJobLink_s0069_07e0* link = GetFreeLink();
            if (link == 0) {
                FailJob(dependent);
            } else {
                link->isWeak = weak;
                link->mpDependency = dependency;
                link->mpDependent = dependent;
                IntrusiveList_s0069_07e0* n1 = (IntrusiveList_s0069_07e0*)link;
                IntrusiveList_s0069_07e0* deps = &dependent->mDependencies;
                n1->mpNext = deps;
                n1->mpPrev = deps->mpPrev;
                deps->mpPrev->mpNext = n1;
                deps->mpPrev = n1;
                IntrusiveList_s0069_07e0* n2 = (IntrusiveList_s0069_07e0*)((char*)link + 8);
                IntrusiveList_s0069_07e0* depnts = &dependency->mDependents;
                n2->mpNext = depnts;
                n2->mpPrev = depnts->mpPrev;
                depnts->mpPrev->mpNext = n2;
                depnts->mpPrev = n2;
                if (dependency->mRealPriority < dependent->mRealPriority)
                    PromoteJobPriorityUnderLock(dependency, dependent->mRealPriority);
            }
        }
        if (dependent->mStatus == 4)
            dependent->mStatus = 5;
        break;
    default:
        break;
    }
    mMutex.Unlock();
}

// @ 0x00691380
void cJob_s0069_07e0::AddDependency(cJob_s0069_07e0* other)
{
    if (other == 0) return;
    cJobData_s0069_07e0* pOther = static_cast<cJobData_s0069_07e0*>(other);
    cJobData_s0069_07e0* pThis = static_cast<cJobData_s0069_07e0*>(this);
    pThis->mpManager->AddJobDependency(pThis, pOther, false);
}

// @ 0x006913c0
void cJob_s0069_07e0::AddWeakDependency(cJob_s0069_07e0* other)
{
    if (other == 0) return;
    cJobData_s0069_07e0* pOther = static_cast<cJobData_s0069_07e0*>(other);
    cJobData_s0069_07e0* pThis = static_cast<cJobData_s0069_07e0*>(this);
    pThis->mpManager->AddJobDependency(pThis, pOther, true);
}

// @ 0x00691400
void* FixedHashSet_Construct(void* self)
{
    return self;
}

// @ 0x00691500
void cJobManager_s0069_07e0::InsertWaitingThread(cJobThread_s0069_07e0* t, int priority)
{
    (void)t; (void)priority;
}

// @ 0x006915c0
void cJobManager_s0069_07e0::FlushWaitingLists()
{
}

// @ 0x00691680
bool cJobManager_s0069_1680::CircularRef(cJob_s0069_1680* a, cJob_s0069_1680* b)
{
    MutexScopedLock lock(&mMutex);
    cJobData_s0069_1680* jobA = static_cast<cJobData_s0069_1680*>(a);
    cJobData_s0069_1680* jobB = static_cast<cJobData_s0069_1680*>(b);
    Tag tag;
    JobSet visitedA(tag, tag);
    JobSet visitedB(tag, tag);
    JobStack stackA;
    JobStack stackB;
    stackA.push_back(jobA);
    visitedA.insert(jobA, tag);
    stackB.push_back(jobB);
    visitedB.insert(jobB, tag);
    while (!stackA.empty() && !stackB.empty()) {
        cJobData_s0069_1680* x = *--stackB.mpEnd;
        if (visitedA.count(x) != 0)
            return true;
        for (IntrusiveList_s0069_1680* n = x->mDependencies.mpNext; n != &x->mDependencies; n = n->mpNext) {
            cJobLink_s0069_1680* link = static_cast<cJobLink_s0069_1680*>(static_cast<JobDependencyNode_s0069_1680*>(n));
            if (visitedB.count(link->mpDependency) == 0) {
                stackB.push_back(link->mpDependency);
                visitedB.insert(link->mpDependency, tag);
            }
        }
        cJobData_s0069_1680* y = *--stackA.mpEnd;
        if (visitedB.count(y) != 0)
            return true;
        for (IntrusiveList_s0069_1680* n = y->mDependents.mpNext; n != &y->mDependents; n = n->mpNext) {
            cJobLink_s0069_1680* link = static_cast<cJobLink_s0069_1680*>(static_cast<JobDependentNode*>(n));
            if (visitedA.count(link->mpDependent) == 0) {
                stackA.push_back(link->mpDependent);
                visitedA.insert(link->mpDependent, tag);
            }
        }
    }
    return false;
}

// @ 0x00691d30
void cJobManager_s0069_1680::RunJob(MutexScopedLock* lock, cJobThread_s0069_1680* thread, cJobData_s0069_1680* job)
{
    job->remove();
    job->push_back_to(&mJobs[4]);
    cJob_s0069_1680* j = job;
    if (j->mpCallback != 0) {
        job->mStatus = 4;
        cJobData_s0069_1680* prev = thread->mCurrentJob;
        thread->mCurrentJob = job;
        int n = mLockCount;
        mLockCount = 0;
        if (n > 0) {
            int i = n;
            do {
                lock->mpMutex->Unlock();
            } while (--i != 0);
        }
        lock->mpMutex->Unlock();
        bool ok = ((bool (*)(cJob_s0069_1680*, void*))j->mpCallback)(j, job->mpCallbackData);
        lock->mpMutex->Lock(K_TIMEOUT);
        if (n > 0) {
            int i = n;
            do {
                lock->mpMutex->Lock(K_TIMEOUT);
            } while (--i != 0);
        }
        mLockCount = n;
        thread->mCurrentJob = prev;
        if (!ok) {
            FailJob(job);
            return;
        }
    }
    int st = job->mStatus;
    if (st == 8 || st == 6) {
        FailJob(job);
        return;
    }
    if (!job->mDependencies.empty()) {
        job->mStatus = 2;
        job->remove();
        job->push_back_to(&mJobs[2]);
        return;
    }
    if (st == 5) {
        ScheduleJob(job);
        return;
    }
    job->mStatus = 7;
    job->remove();
    job->push_back_to(&mJobs[7]);
    while (!job->mDependents.empty()) {
        IntrusiveList_s0069_1680* n = job->mDependents.mpPrev;
        cJobLink_s0069_1680* link = static_cast<cJobLink_s0069_1680*>(static_cast<JobDependentNode*>(n));
        cJobData_s0069_1680* dep = link->mpDependent;
        static_cast<JobDependentNode*>(link)->remove();
        static_cast<JobDependencyNode_s0069_1680*>(link)->remove();
        static_cast<JobDependencyNode_s0069_1680*>(link)->push_back_to(&mFreeLinks);
        if (dep->mDependencies.empty() && dep->mStatus == 2)
            ScheduleJob(dep);
    }
    if (job->mbSynchronousWait) {
        job->mbSynchronousWait = false;
        mJobReadyOrSyncCondition.NotifyAll();
    }
    if (_InterlockedExchangeAdd((volatile long*)&job->mRefCount, -1) - 1 == 0)
        job->mpManager->FreeJobUnderLock(lock, job);
}

// @ 0x00691f60
bool cJobManager_s0069_1680::RunUnderLock(MutexScopedLock* lock, cJobThread_s0069_1680* thread, TimeBudget* budget, bool noWait)
{
    bool ran = false;
    while (!thread->mbExit) {
        cJobData_s0069_1680* run;
        IntrusiveList_s0069_1680* ready = &mJobs[3];
        if (!ready->empty()) {
            run = static_cast<cJobData_s0069_1680*>(ready->mpNext);
            cJobData_s0069_1680* r = GetRunnableJob(thread, run->mRealPriority);
            if (r)
                run = r;
        } else {
            run = GetRunnableJob(thread, 0x80000000);
        }
        if (run) {
            int savedPriority = thread->mCurrentPriority;
            thread->mCurrentPriority = run->mRealPriority;
            RunJob(lock, thread, run);
            thread->mCurrentPriority = savedPriority;
            ran = true;
            if (budget) {
                long long now;
                QueryPerformanceCounter(&now);
                if (budget->mDeadline - now < 0)
                    return ran;
            }
        } else {
            if (noWait)
                return ran;
            JobWaitNode_s0069_1680* node = thread;
            node->mpNext = 0;
            node->mpPrev = 0;
            node->push_back_to(&mJobReadyCondition.mWaitList);
            lock->mpMutex->Unlock();
            node->mSemaphore.Wait(K_TIMEOUT);
            lock->mpMutex->Lock(K_TIMEOUT);
        }
    }
    return ran;
}

// @ 0x00692080
void cJobManager_s0069_1680::AddWaitingJob(int priority)
{
    MutexScopedLock lock(&mMutex);
    InsertWaitingThread(priority);
}

// @ 0x006920f0
void cJobManager_s0069_1680::FlushWaiting()
{
    MutexScopedLock lock(&mMutex);
    FlushWaitingLists();
}

// @ 0x00692150
void cJobManager_s0069_1680::WaitForJobUnderLock(MutexScopedLock* lock, cJobData_s0069_1680* job)
{
    int st = job->mStatus;
    if (st == 8 || st == 7 || st == 0 || st == 1)
        return;
    void* tid = EA::Thread::GetThreadId();
    cJobThread_s0069_1680* thread = 0;
    SyncThreadTime(GetCurrentThreadTime());
    JobWaitNode_s0069_1680* node;
    for (IntrusiveList_s0069_1680* t = mThreads.mpNext; t != &mThreads; t = t->mpNext) {
        if (((cJobThread_s0069_1680*)t)->mThreadId == tid) {
            thread = (cJobThread_s0069_1680*)t;
            node = thread;
            goto found;
        }
    }
    node = AcquireWaitNode();
found:
    int real = job->mRealPriority;
    int prio = 0;
    if (real > 0)
        prio = real;
    if (thread && thread->mCurrentPriority > prio)
        prio = thread->mCurrentPriority;
    job->mPriority = prio + 0x10000;
    int np = ComputePriority(job);
    if (real < np)
        PromoteJobPriorityUnderLock(job, np);
    else if (real > np)
        LowerJobPriority(job, np);
    while (job->mStatus != 8 && job->mStatus != 7 && job->mStatus != 0 && job->mStatus != 1) {
        job->mbSynchronousWait = true;
        if (!thread || !RunUnderLock(lock, thread, 0, true)) {
            int n = mLockCount;
            mLockCount = 0;
            if (n > 0) {
                int i = n;
                do {
                    lock->mpMutex->Unlock();
                } while (--i != 0);
            }
            node->mpNext = 0;
            node->mpPrev = 0;
            node->push_back_to(&mJobReadyOrSyncCondition.mWaitList);
            lock->mpMutex->Unlock();
            node->mSemaphore.Wait(K_TIMEOUT);
            lock->mpMutex->Lock(K_TIMEOUT);
            if (n > 0) {
                int i = n;
                do {
                    lock->mpMutex->Lock(K_TIMEOUT);
                } while (--i != 0);
            }
            mLockCount = n;
        }
    }
    if (!thread)
        node->push_front_to(&mFreeWaitNodes);
    WakeUp();
}

// @ 0x00692330
bool cJobManager_s0069_1680::CancelJob(cJobData_s0069_1680* job, bool wait)
{
    MutexScopedLock lock(&mMutex);
    bool result = false;
    switch (job->mStatus) {
    case 1:
    case 2:
    case 3:
        FailJob(job);
        // fallthrough
    case 8:
        result = true;
        break;
    case 4:
    case 5:
        FailJobDependents(job, true);
        job->mStatus = 6;
        if (wait)
            WaitForJobUnderLock(&lock, job);
        break;
    case 6:
        if (wait)
            WaitForJobUnderLock(&lock, job);
        break;
    default:
        break;
    }
    return result;
}

// @ 0x00692430
void cJobManager_s0069_1680::DestroyJobThread(cJobThread_s0069_1680* thread)
{
    MutexScopedLock lock(&mMutex);
    if (thread->mThread.GetStatus(0) == 1) {
        for (;;) {
            if (thread->mCurrentJob) {
                WaitForJobUnderLock(&lock, thread->mCurrentJob);
                continue;
            }
            cJobData_s0069_1680* j = GetRunnableJob(thread, 0x80000000);
            if (!j)
                break;
            WaitForJobUnderLock(&lock, j);
        }
        thread->mbExit = true;
        JobWaitNode_s0069_1680* node = thread;
        if (node->mpPrev != node) {
            node->remove();
            node->mpNext = node;
            node->mpPrev = node;
            node->mSemaphore.Post(1);
        }
        int n = mLockCount;
        mLockCount = 0;
        if (n > 0) {
            int i = n;
            do {
                lock.mpMutex->Unlock();
            } while (--i != 0);
        }
        lock.mpMutex->Unlock();
        thread->mThread.WaitForEnd(K_TIMEOUT, 0);
        lock.mpMutex->Lock(K_TIMEOUT);
        if (n > 0) {
            int i = n;
            do {
                lock.mpMutex->Lock(K_TIMEOUT);
            } while (--i != 0);
        }
        mLockCount = n;
    }
    static_cast<IntrusiveList_s0069_1680*>(thread)->remove();
    unsigned int affinities = 0;
    for (IntrusiveList_s0069_1680* t = mThreads.mpNext; t != &mThreads; t = t->mpNext) {
        cJobThread_s0069_1680* ct = (cJobThread_s0069_1680*)t;
        if (ct->mThreadId)
            affinities |= ct->mAffinity;
    }
    mValidAffinities = affinities;
    FailNonRunnableJobs();
    thread->Destruct();
    operator delete[](thread);
}

// @ 0x006925c0
bool cJobManager_s0069_25c0::Run(void* a, void* b, void* c)
{
    MutexScopedLock_s0069_25c0 lock(&mMutex);
    return FUN_00691f60(&lock, a, b, c) != 0;
}
