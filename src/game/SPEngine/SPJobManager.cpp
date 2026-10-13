// src/game/SPEngine/SPJobManager.cpp -- migrated from slice(s) s006925c0, s006907e0, s0068e670 by tools/migrate/rewrite.py
// Object file: SPEngine/SPJobManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include <intrin.h>

// ---- items of slice s0068e670 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Mutex { uint32_t _[12]; void Lock(void*); void Unlock(); };
struct HObj { void Close(); };
struct ClsF4A0 { uint32_t f0; uint32_t f4; HObj h; void Reset(); };
struct ClsF540 { uint32_t f0, f4; Mutex m; int count; void Acquire(); void Release(); };
struct Inner570 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(void*, int, int);       // slot 7 (0x1c)
};
struct Outer570 { uint32_t pad[10]; Inner570* mInner; };  // inner ptr at +0x28
struct VObj { virtual void v0(); virtual void v1(); };
struct ClsF5B0 { VObj* m; void Set(VObj* p); };
// ---- items of slice s0068e670 end

// ---- items of slice s006907e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IntrusiveList {
    IntrusiveList* mpNext;   // +0
    IntrusiveList* mpPrev;   // +4
    IntrusiveList();
};
IntrusiveList::IntrusiveList() { mpPrev = this; mpNext = this; }
namespace EA {
namespace Thread {
class Mutex_s0069_07e0 {
public:
    char mData[0x30];
    void Lock(unsigned int flags);
    void Unlock();
};
}
}
struct AutoRefCount { void* mpPtr; };
struct cJobData;
class cJobManager;
struct cJobThread;
struct cJobLink;
struct JobDependencyNode { JobDependencyNode* mpNext; JobDependencyNode* mpPrev; };
struct cJob {
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
    int AddRef();
    void Queue();
    void AddDependency(cJob* other);
    void AddWeakDependency(cJob* other);
};
struct cJobDataNode { void* mpNext; void* mpPrev; };
struct cJobData : cJobDataNode, cJob {
    cJobManager* mpManager;         // +0x30
    bool mbSynchronousWait;         // +0x34
    char mPad35[3];
    IntrusiveList mDependencies;    // +0x38
    IntrusiveList mDependents;      // +0x40
    int mRealPriority;              // +0x48
    int mRefCount;                  // +0x4c
};
struct cJobThread {
    void* mpNext;                   // +0x00
    void* mpPrev;                   // +0x04
    char mPad08[0x18];              // +0x08 (JobWaitNode incl. semaphore)
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
};
struct EAVector { void* mpBegin; void* mpEnd; void* mpCapacity; };
class cJobManager {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual cJobThread* CreateThread(unsigned int affinity, int a, int b); // +0x14
    virtual void RemoveThread(cJobThread* pThread);                        // +0x18
    virtual bool EndThread(cJobThread* pThread, int a, int b);             // +0x1c

    unsigned int mPad04;            // +0x04
    EA::Thread::Mutex_s0069_07e0 mMutex;       // +0x08
    int mUnknown38;                 // +0x38
    IntrusiveList mJobReadyCondition;       // +0x3c
    IntrusiveList mJobReadyOrSyncCondition; // +0x44
    IntrusiveList mJobs[9];         // +0x4c
    IntrusiveList mReadyList[32];   // +0x94
    unsigned int mValidAffinities;  // +0x194
    IntrusiveList mThreads;         // +0x198
    int mActiveJobCount;            // +0x1a0
    EAVector mWaitingThreads;       // +0x1a4
    char mPad1b0[8];                // +0x1b0
    EAVector mWaitingPriorities;    // +0x1b8
    char mPad1c4[8];                // +0x1c4
    cJobThread* mpSyncThread;       // +0x1cc
    IntrusiveList mFreeLinks;       // +0x1d0
    IntrusiveList mFreeWaitNodes;   // +0x1d8
    void* mInitThreadFunc;          // +0x1e0

    void QueueJobUnderLock(cJobData* job);
    void PromoteJobPriorityUnderLock(cJobData* job, int priority);
    void SetJobPriorityUnderLock(cJobData* job, int priority);
    void CheckDependentPriority(cJobData* job, int priority);
    void InsertWaitingThread(cJobThread* t, int priority);
    void ScheduleJob(cJobData* job);
    void FailJob(cJobData* job);
    void FailNonRunnableJobs();
    void FailJobDependents(cJobData* job, bool weakOnly);
    __declspec(noinline) void AddJobDependency(cJobData* dependent, cJobData* dependency, bool weak);
    cJobLink* GetFreeLink();
    void FlushWaitingLists();
    void RebuildWaitingLists();
};
void cJobManager::slot0() {}
void cJobManager::slot1() {}
void cJobManager::slot2() {}
void cJobManager::slot3() {}
void cJobManager::slot4() {}
void cJobManager::RemoveThread(cJobThread*) {}
bool cJobManager::EndThread(cJobThread*, int, int) { return false; }
void cJobManager::ScheduleJob(cJobData*) {}
// ---- items of slice s006907e0 end


// ---- items of slice s006925c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
    extern unsigned int g_MutexFlags; // 0x01403750
namespace EA {
namespace Thread {
class Mutex_s0069_25c0 {
public:
    char mData[0x30];
    void Lock(unsigned int flags);
    void Unlock();
};  // namespace EA::Thread
}
}
struct MutexScopedLock {
    EA::Thread::Mutex_s0069_25c0* mpMutex;
    MutexScopedLock(EA::Thread::Mutex_s0069_25c0* m) : mpMutex(m) { m->Lock((unsigned int)&g_MutexFlags); }
    ~MutexScopedLock() { mpMutex->Unlock(); }
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

// @ 0x0068f450
namespace EA
{
int GetHighestBitPowerOf2(unsigned int v) {
    int n = 0;
    if (v & 0xffff0000) { n = 0x10; v >>= 0x10; }
    if (v & 0xff00) { n += 8; v >>= 8; }
    if (v & 0xf0) { n += 4; v >>= 4; }
    if (v & 0xc) { n += 2; v >>= 2; }
    if (v & 2) { n += 1; }
    return n;
}
}






// @ 0x0068f4a0
void ClsF4A0::Reset()
{
    f0 = 0;
    f4 = 0;
    h.Close();
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
extern "C" void FUN_68F5A0(void* a, void** b)
{
    ((void (__cdecl*)(void*))((void**)*b)[0])(a);
}






// @ 0x0068f5b0
void ClsF5B0::Set(VObj* p)
{
    VObj* old = m;
    m = p;
    if (old)
        old->v1();
}




// @ 0x0068f950
int cJob::AddRef()
{
    cJobData* p = static_cast<cJobData*>(this);
    long* pRC = (long*)&p->mRefCount;
    return _InterlockedExchangeAdd(pRC, 1) + 1;
}

// @ 0x006925c0
bool cJobManager_s0069_25c0::Run(void* a, void* b, void* c)
{
    MutexScopedLock lock(&mMutex);
    return FUN_00691f60(&lock, a, b, c) != 0;
}
