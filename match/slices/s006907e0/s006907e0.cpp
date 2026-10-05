// Batch w1g5 slice s006907e0 — SP::cJobManager scheduling/dependency subsystem.
// Region is /O2 (no frame pointer, register-allocated, EH with __ehhandler$).
#include "types.h"
#include <new>
#include <intrin.h>

__declspec(noinline) void* EAAllocate(size_t size, const char* name, int, int, int, int);
__declspec(noinline) void  EADeallocate(void* p);

struct IntrusiveList {
    IntrusiveList* mpNext;   // +0
    IntrusiveList* mpPrev;   // +4
    IntrusiveList();
};
IntrusiveList::IntrusiveList() { mpPrev = this; mpNext = this; }

namespace EA { namespace Thread {
class Mutex {
public:
    char mData[0x30];
    void Lock(unsigned int flags);
    void Unlock();
};
class Semaphore {
public:
    char mData[0x10];
    Semaphore(int initial);
    void Post(int count);
    void Post();
};
}} // namespace EA::Thread

extern unsigned int g_MutexFlags;   // 0x01403750

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
    EA::Thread::Mutex mMutex;       // +0x08
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

unsigned int GetMaxDependentPriority(cJobData* job);

// ===========================================================================
// @ 0x0068f950 (shared helper, referenced by this slice's AddRef call)
// ===========================================================================
int cJob::AddRef() {
    cJobData* p = static_cast<cJobData*>(this);
    long* pRC = (long*)&p->mRefCount;
    return _InterlockedExchangeAdd(pRC, 1) + 1;
}

// ===========================================================================
// @ 0x006909b0  cJob::Queue
// ===========================================================================
void cJob::Queue() {
    cJobData* p = static_cast<cJobData*>(this);
    p->mpManager->QueueJobUnderLock(p);
}

// ===========================================================================
// @ 0x00691380  cJob::AddDependency
// ===========================================================================
void cJob::AddDependency(cJob* other) {
    if (other == 0) return;
    cJobData* pOther = static_cast<cJobData*>(other);
    cJobData* pThis = static_cast<cJobData*>(this);
    pThis->mpManager->AddJobDependency(pThis, pOther, false);
}

// ===========================================================================
// @ 0x006913c0  cJob::AddWeakDependency
// ===========================================================================
void cJob::AddWeakDependency(cJob* other) {
    if (other == 0) return;
    cJobData* pOther = static_cast<cJobData*>(other);
    cJobData* pThis = static_cast<cJobData*>(this);
    pThis->mpManager->AddJobDependency(pThis, pOther, true);
}

// ===========================================================================
// @ 0x006907e0  cJobManager::QueueJobUnderLock
// ===========================================================================
void cJobManager::QueueJobUnderLock(cJobData* job) {
    mMutex.Lock((unsigned int)&g_MutexFlags);
    if (job->mStatus == 1) {
        job->AddRef();
        if (job->mDependencies.mpPrev == &job->mDependencies) {
            ScheduleJob(job);
        } else {
            IntrusiveList* pNode = (IntrusiveList*)job;
            pNode->mpPrev->mpNext = pNode->mpNext;
            pNode->mpNext->mpPrev = pNode->mpPrev;
            pNode->mpPrev = 0;
            pNode->mpNext = 0;
            job->mStatus = 2;
            IntrusiveList* pList = &mJobs[2];
            pNode->mpPrev = pList->mpPrev;
            pNode->mpNext = pList;
            pList->mpPrev->mpNext = pNode;
            pList->mpPrev = pNode;
        }
    }
    mMutex.Unlock();
}

// ===========================================================================
// @ 0x006908a0  SP::cJobManager::PromoteJobPriorityUnderLock
// ===========================================================================
void cJobManager::PromoteJobPriorityUnderLock(cJobData* job, int priority) {
    if (job->mStatus == 3) {
        IntrusiveList* pNode = (IntrusiveList*)job;
        pNode->mpPrev->mpNext = pNode->mpNext;
        pNode->mpNext->mpPrev = pNode->mpPrev;
        pNode->mpPrev = 0;
        pNode->mpNext = 0;
        job->mStatus = 2;
        IntrusiveList* pList = &mJobs[2];
        pNode->mpPrev = pList->mpPrev;
        pNode->mpNext = pList;
        pList->mpPrev->mpNext = pNode;
        pList->mpPrev = pNode;
        ScheduleJob(job);
    }
    job->mRealPriority = priority;
    IntrusiveList* pAnchor = &job->mDependents;
    for (IntrusiveList* it = pAnchor->mpNext; it != pAnchor; it = it->mpNext) {
        cJobLink* link = (cJobLink*)((char*)it - 8);
        cJobData* dep = link->mpDependent;
        if (dep->mRealPriority < job->mRealPriority)
            PromoteJobPriorityUnderLock(dep, job->mRealPriority);
    }
}

// ===========================================================================
// @ 0x00690930  cJobManager::SetJobPriorityUnderLock
// ===========================================================================
void cJobManager::SetJobPriorityUnderLock(cJobData* job, int priority) {
    int oldPriority = job->mRealPriority;
    job->mRealPriority = priority;
    if (job->mStatus == 3) {
        IntrusiveList* pNode = (IntrusiveList*)job;
        pNode->mpPrev->mpNext = pNode->mpNext;
        pNode->mpNext->mpPrev = pNode->mpPrev;
        pNode->mpPrev = 0;
        pNode->mpNext = 0;
        job->mStatus = 2;
        IntrusiveList* pList = &mJobs[2];
        pNode->mpPrev = pList->mpPrev;
        pNode->mpNext = pList;
        pList->mpPrev->mpNext = pNode;
        pList->mpPrev = pNode;
        ScheduleJob(job);
    }
    IntrusiveList* pAnchor = &job->mDependents;
    for (IntrusiveList* it = pAnchor->mpNext; it != pAnchor; it = it->mpNext) {
        cJobLink* link = (cJobLink*)((char*)it - 8);
        CheckDependentPriority(link->mpDependent, oldPriority);
    }
}

// ===========================================================================
// @ 0x00690b50  cJobManager::CheckDependentPriority
// ===========================================================================
void cJobManager::CheckDependentPriority(cJobData* job, int priority) {
    int pri = job->mRealPriority;
    if (pri == priority) {
        int maxp = GetMaxDependentPriority(job);
        if (maxp < pri)
            SetJobPriorityUnderLock(job, maxp);
    }
}

// ===========================================================================
// @ 0x006909e0  eastl prof hashtable DoInsertValue
// ===========================================================================
void* ProfTable_DoInsertValue(void* self, void* result, void* key) {
    (void)self; (void)result; (void)key;
    return 0;
}

// ===========================================================================
// @ 0x00690b80 / 0x00690c90  eastl vector insert (candidate lists)
// ===========================================================================
void WaitingList1_Insert(void* vec, void* pos, void* value) {
    (void)vec; (void)pos; (void)value;
}

// ===========================================================================
// @ 0x00690da0  SP::cJobManager::CreateJobThread
// ===========================================================================
cJobThread* cJobManager::CreateThread(unsigned int affinity, int a, int b) {
    (void)affinity; (void)a; (void)b;
    return 0;
}

// ===========================================================================
// @ 0x00690f60  SP::cJobManager::FailJob
// ===========================================================================
void cJobManager::FailJob(cJobData* job) {
    (void)job;
}

// ===========================================================================
// @ 0x006910a0  SP::cJobManager::FailNonRunnableJobs
// ===========================================================================
void cJobManager::FailNonRunnableJobs() {
}

// ===========================================================================
// @ 0x00691260  SP::cJobManager::AddJobDependency
// ===========================================================================
void cJobManager::AddJobDependency(cJobData* dependent, cJobData* dependency, bool weak) {
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
            cJobLink* link = GetFreeLink();
            if (link == 0) {
                FailJob(dependent);
            } else {
                link->isWeak = weak;
                link->mpDependency = dependency;
                link->mpDependent = dependent;
                IntrusiveList* n1 = (IntrusiveList*)link;
                IntrusiveList* deps = &dependent->mDependencies;
                n1->mpNext = deps;
                n1->mpPrev = deps->mpPrev;
                deps->mpPrev->mpNext = n1;
                deps->mpPrev = n1;
                IntrusiveList* n2 = (IntrusiveList*)((char*)link + 8);
                IntrusiveList* depnts = &dependency->mDependents;
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

// ===========================================================================
// @ 0x00691400  eastl::fixed_hash_set constructor
// ===========================================================================
void* FixedHashSet_Construct(void* self) {
    return self;
}

// ===========================================================================
// @ 0x00691500  cJobManager waiting-list fill
// ===========================================================================
void cJobManager::InsertWaitingThread(cJobThread* t, int priority) {
    (void)t; (void)priority;
}

// ===========================================================================
// @ 0x006915c0  cJobManager waiting-list drain
// ===========================================================================
void cJobManager::FlushWaitingLists() {
}

// ---- out-of-line virtual stubs ----
void cJobManager::slot0() {}
void cJobManager::slot1() {}
void cJobManager::slot2() {}
void cJobManager::slot3() {}
void cJobManager::slot4() {}
void cJobManager::RemoveThread(cJobThread*) {}
bool cJobManager::EndThread(cJobThread*, int, int) { return false; }
cJobManager* cJobManager_Construct(cJobManager* p) { return p; }
unsigned int GetMaxDependentPriority(cJobData* job) {
    unsigned int maxPri = (unsigned int)job->mPriority;
    IntrusiveList* pAnchor = &job->mDependents;
    for (IntrusiveList* it = pAnchor->mpNext; it != pAnchor; it = it->mpNext) {
        cJobLink* link = (cJobLink*)((char*)it - 8);
        int pri = link->mpDependent->mRealPriority;
        if ((int)maxPri < pri) maxPri = (unsigned int)pri;
    }
    return maxPri;
}
void cJobManager::ScheduleJob(cJobData*) {}
