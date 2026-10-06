// Batch w1g5 slice s00691680 — SP::cJobManager run/cancel subsystem.
// Region is /O2 (no frame pointer, register-allocated, EH with __ehhandler$).
#include "types.h"
#include <new>
#include <intrin.h>

__declspec(noinline) void* EAAllocate(size_t size, const char* name, int, int, int, int);
__declspec(noinline) void  EADeallocate(void* p);

struct IntrusiveList {
    IntrusiveList* mpNext;
    IntrusiveList* mpPrev;
    IntrusiveList();
    bool empty() const { return mpPrev == this; }
    // unlink and clear (debug-style zeroing of the node)
    void remove() {
        IntrusiveList* p = mpPrev;
        IntrusiveList* n = mpNext;
        p->mpNext = n;
        n->mpPrev = p;
        mpPrev = 0;
        mpNext = 0;
    }
    // link this node before the anchor (push_back)
    void push_back_to(IntrusiveList* anchor) {
        mpPrev = anchor->mpPrev;
        mpNext = anchor;
        anchor->mpPrev = this;
        mpPrev->mpNext = this;
    }
    // link this node after the anchor (push_front)
    void push_front_to(IntrusiveList* anchor) {
        mpNext = anchor->mpNext;
        mpPrev = anchor;
        anchor->mpNext = this;
        mpNext->mpPrev = this;
    }
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
    int Wait(unsigned int timeout);
};
class Thread {
public:
    char mData[4];
    int GetStatus(void* pStatus);                    // 0x00922a10
    int WaitForEnd(unsigned int timeout, int* pRet); // 0x00922940
};
void* GetThreadId();                                 // 0x00921cc0
}} // namespace EA::Thread

extern unsigned int g_MutexFlags;   // 0x01403750
#define K_TIMEOUT ((unsigned int)&g_MutexFlags)

struct MutexScopedLock {
    EA::Thread::Mutex* mpMutex;
    MutexScopedLock(EA::Thread::Mutex* m) : mpMutex(m) { m->Lock(K_TIMEOUT); }
    ~MutexScopedLock() { mpMutex->Unlock(); }
};

struct AutoRefCount { void* mpPtr; };
struct cJobData;
class cJobManager;
struct cJobThread;
struct cJobLink;
struct JobDependencyNode : IntrusiveList {};
struct JobDependentNode : IntrusiveList {};

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
    bool Cancel(bool b);
};

struct cJobData : IntrusiveList, cJob {
    cJobManager* mpManager;         // +0x30
    bool mbSynchronousWait;         // +0x34
    char mPad35[3];
    IntrusiveList mDependencies;    // +0x38  (JobDependencyNode list)
    IntrusiveList mDependents;      // +0x40  (JobDependentNode list)
    int mRealPriority;              // +0x48
    int mRefCount;                  // +0x4c
    cJobManager* GetManager() { return mpManager; }
};

struct JobWaitNode : IntrusiveList {
    EA::Thread::Semaphore mSemaphore;   // +0x08
};

struct cJobThread : IntrusiveList, JobWaitNode {
    EA::Thread::Thread mThread;     // +0x20
    void* mThreadId;                // +0x24
    cJobManager* mpJobManager;      // +0x28
    unsigned int mAffinity;         // +0x2c
    int mCurrentPriority;           // +0x30
    cJobData* mCurrentJob;          // +0x34
    bool mbExit;                    // +0x38
    void Destruct();                // 0x0068f4e0
};

struct cJobLink : JobDependencyNode, JobDependentNode {
    cJobData* mpDependency;         // +0x10
    cJobData* mpDependent;          // +0x14
    bool isWeak;                    // +0x18
};

// Deadline used by RunUnderLock (QueryPerformanceCounter ticks at +0x18).
struct TimeBudget {
    char mPad[0x18];
    long long mDeadline;
};

struct JobCondition {
    IntrusiveList mWaitList;
    void NotifyAll();               // 0x0068f5d0
};

struct EAVector { void* mpBegin; void* mpEnd; void* mpCapacity; };

// ---- eastl::fixed_hash_set<cJobData*,32,33,true,...> (0x24c bytes) ----
struct Tag {};
struct HashNode { cJobData* mKey; HashNode* mpNext; };
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
    HashInsertResult insert(cJobData* const& key, Tag t);         // 0x006909e0
    void FreeBuckets(HashNode** p, unsigned int n);               // 0x0068fb70
    unsigned int count(cJobData* const& k) const {
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

// ---- eastl::fixed_vector<cJobData*,32,true> ----
struct JobStack {
    cJobData** mpBegin;
    cJobData** mpEnd;
    cJobData** mpCapacity;
    unsigned int mAlloc;
    cJobData** mpFixed;
    cJobData* mBuf[32];
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
    void DoInsertValueEnd(cJobData** pos, cJobData* const& v);    // 0x00690c90
    void push_back(cJobData* const& v) {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) cJobData*(v);
        else
            DoInsertValueEnd(mpEnd, v);
    }
    bool empty() const { return mpBegin == mpEnd; }
};

class cJobManager {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual cJobThread* CreateThread(unsigned int affinity, int a, int b);
    virtual void RemoveThread(cJobThread* pThread);
    virtual bool EndThread(cJobThread* pThread, int a, int b);

    unsigned int mPad04;
    EA::Thread::Mutex mMutex;       // +0x08
    int mLockCount;                 // +0x38 (recursive lock depth, saved across waits)
    JobCondition mJobReadyCondition;        // +0x3c
    JobCondition mJobReadyOrSyncCondition;  // +0x44
    IntrusiveList mJobs[9];         // +0x4c
    IntrusiveList mReadyList[32];   // +0x94
    unsigned int mValidAffinities;  // +0x194
    IntrusiveList mThreads;         // +0x198
    int mActiveJobCount;            // +0x1a0
    EAVector mWaitingThreads;       // +0x1a4
    char mPad1b0[8];
    EAVector mWaitingPriorities;    // +0x1b8
    char mPad1c4[8];
    cJobThread* mpSyncThread;       // +0x1cc
    IntrusiveList mFreeLinks;       // +0x1d0
    IntrusiveList mFreeWaitNodes;   // +0x1d8
    void* mInitThreadFunc;          // +0x1e0

    __declspec(noinline) void InsertWaitingThread(int priority);
    __declspec(noinline) void FlushWaitingLists();
    void AddWaitingJob(int priority);
    void FlushWaiting();
    bool CircularRef(cJob* a, cJob* b);                                   // 0x00691680
    void RunJob(MutexScopedLock* lock, cJobThread* thread, cJobData* job); // 0x00691d30
    bool RunUnderLock(MutexScopedLock* lock, cJobThread* thread, TimeBudget* budget, bool noWait); // 0x00691f60
    void WaitForJobUnderLock(MutexScopedLock* lock, cJobData* job);       // 0x00692150
    bool CancelJob(cJobData* job, bool wait);                             // 0x00692330
    void DestroyJobThread(cJobThread* thread);                            // 0x00692430
    cJobData* GetRunnableJob(cJobThread* pThread, int minPriority);       // 0x0068f670
    void ScheduleJob(cJobData* job);                                      // 0x00690540
    void FailJob(cJobData* job);                                          // 0x00690f60
    void FailJobDependents(cJobData* job, bool b);                        // 0x00690630
    void FailNonRunnableJobs();                                           // 0x006910a0
    void FreeJobUnderLock(MutexScopedLock* lock, cJobData* job);          // 0x0068f7c0
    void PromoteJobPriorityUnderLock(cJobData* job, int priority);        // 0x006908a0
    void LowerJobPriority(cJobData* job, int priority);                   // 0x00690930
    int ComputePriority(cJobData* job);                                   // 0x0068ffb0
    void SyncThreadTime(unsigned int t);                                  // 0x00691500
    JobWaitNode* AcquireWaitNode();                                       // 0x0068f700
    void WakeUp();                                                        // 0x006915c0
};
unsigned int GetCurrentThreadTime();                                      // 0x00921d70
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* p);

// ===========================================================================
// @ 0x00692080  cJobManager::AddWaitingJob
// ===========================================================================
void cJobManager::AddWaitingJob(int priority) {
    MutexScopedLock lock(&mMutex);
    InsertWaitingThread(priority);
}

// ===========================================================================
// @ 0x006920f0  cJobManager::FlushWaiting
// ===========================================================================
void cJobManager::FlushWaiting() {
    MutexScopedLock lock(&mMutex);
    FlushWaitingLists();
}

// ===========================================================================
// @ 0x00692400  cJob::Cancel
// ===========================================================================
bool cJob::Cancel(bool wait) {
    cJobData* self = static_cast<cJobData*>(this);
    return self->GetManager()->CancelJob(self, wait);
}

// ===========================================================================
// @ 0x00691680  SP::cJobManager::CircularRef
// Bidirectional search: grows A's dependents and B's dependencies; if the two
// frontiers meet, adding B -> A would close a cycle.
// ===========================================================================
bool cJobManager::CircularRef(cJob* a, cJob* b) {
    MutexScopedLock lock(&mMutex);
    cJobData* jobA = static_cast<cJobData*>(a);
    cJobData* jobB = static_cast<cJobData*>(b);
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
        cJobData* x = *--stackB.mpEnd;
        if (visitedA.count(x) != 0)
            return true;
        for (IntrusiveList* n = x->mDependencies.mpNext; n != &x->mDependencies; n = n->mpNext) {
            cJobLink* link = static_cast<cJobLink*>(static_cast<JobDependencyNode*>(n));
            if (visitedB.count(link->mpDependency) == 0) {
                stackB.push_back(link->mpDependency);
                visitedB.insert(link->mpDependency, tag);
            }
        }
        cJobData* y = *--stackA.mpEnd;
        if (visitedB.count(y) != 0)
            return true;
        for (IntrusiveList* n = y->mDependents.mpNext; n != &y->mDependents; n = n->mpNext) {
            cJobLink* link = static_cast<cJobLink*>(static_cast<JobDependentNode*>(n));
            if (visitedA.count(link->mpDependent) == 0) {
                stackA.push_back(link->mpDependent);
                visitedA.insert(link->mpDependent, tag);
            }
        }
    }
    return false;
}

// ===========================================================================
// @ 0x00691d30  SP::cJobManager::RunJob
// ===========================================================================
void cJobManager::RunJob(MutexScopedLock* lock, cJobThread* thread, cJobData* job) {
    job->remove();
    job->push_back_to(&mJobs[4]);
    cJob* j = job;
    if (j->mpCallback != 0) {
        job->mStatus = 4;
        cJobData* prev = thread->mCurrentJob;
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
        bool ok = ((bool (*)(cJob*, void*))j->mpCallback)(j, job->mpCallbackData);
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
        IntrusiveList* n = job->mDependents.mpPrev;
        cJobLink* link = static_cast<cJobLink*>(static_cast<JobDependentNode*>(n));
        cJobData* dep = link->mpDependent;
        static_cast<JobDependentNode*>(link)->remove();
        static_cast<JobDependencyNode*>(link)->remove();
        static_cast<JobDependencyNode*>(link)->push_back_to(&mFreeLinks);
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

// ===========================================================================
// @ 0x00691f60  SP::cJobManager::RunUnderLock
// Runs jobs on `thread` until it is told to exit (or the budget expires).
// ===========================================================================
bool cJobManager::RunUnderLock(MutexScopedLock* lock, cJobThread* thread, TimeBudget* budget, bool noWait) {
    bool ran = false;
    while (!thread->mbExit) {
        cJobData* run;
        IntrusiveList* ready = &mJobs[3];
        if (!ready->empty()) {
            run = static_cast<cJobData*>(ready->mpNext);
            cJobData* r = GetRunnableJob(thread, run->mRealPriority);
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
            JobWaitNode* node = thread;
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

// ===========================================================================
// @ 0x00692150  SP::cJobManager::WaitForJobUnderLock
// ===========================================================================
void cJobManager::WaitForJobUnderLock(MutexScopedLock* lock, cJobData* job) {
    int st = job->mStatus;
    if (st == 8 || st == 7 || st == 0 || st == 1)
        return;
    void* tid = EA::Thread::GetThreadId();
    cJobThread* thread = 0;
    SyncThreadTime(GetCurrentThreadTime());
    JobWaitNode* node;
    for (IntrusiveList* t = mThreads.mpNext; t != &mThreads; t = t->mpNext) {
        if (((cJobThread*)t)->mThreadId == tid) {
            thread = (cJobThread*)t;
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

// ===========================================================================
// @ 0x00692330  SP::cJobManager::CancelJob
// ===========================================================================
bool cJobManager::CancelJob(cJobData* job, bool wait) {
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

// ===========================================================================
// @ 0x00692430  SP::cJobManager::DestroyJobThread
// ===========================================================================
void cJobManager::DestroyJobThread(cJobThread* thread) {
    MutexScopedLock lock(&mMutex);
    if (thread->mThread.GetStatus(0) == 1) {
        for (;;) {
            if (thread->mCurrentJob) {
                WaitForJobUnderLock(&lock, thread->mCurrentJob);
                continue;
            }
            cJobData* j = GetRunnableJob(thread, 0x80000000);
            if (!j)
                break;
            WaitForJobUnderLock(&lock, j);
        }
        thread->mbExit = true;
        JobWaitNode* node = thread;
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
    static_cast<IntrusiveList*>(thread)->remove();
    unsigned int affinities = 0;
    for (IntrusiveList* t = mThreads.mpNext; t != &mThreads; t = t->mpNext) {
        cJobThread* ct = (cJobThread*)t;
        if (ct->mThreadId)
            affinities |= ct->mAffinity;
    }
    mValidAffinities = affinities;
    FailNonRunnableJobs();
    thread->Destruct();
    operator delete[](thread);
}

// ---- out-of-line stubs ----
void cJobManager::slot0() {}
void cJobManager::slot1() {}
void cJobManager::slot2() {}
void cJobManager::slot3() {}
void cJobManager::slot4() {}
cJobThread* cJobManager::CreateThread(unsigned int, int, int) { return 0; }
void cJobManager::RemoveThread(cJobThread*) {}
bool cJobManager::EndThread(cJobThread*, int, int) { return false; }
