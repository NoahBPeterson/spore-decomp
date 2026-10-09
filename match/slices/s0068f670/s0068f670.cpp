// Batch w1g5 slice s0068f670 — SP::cJobManager / SP::cJob subsystem.
// Region is /O2 (no frame pointer, register-allocated, EH with __ehhandler$).
#include "types.h"
#include <new>
#include <intrin.h>

// ---------------------------------------------------------------------------
// External helpers (addresses are masked relocations; bodies never inline).
// ---------------------------------------------------------------------------
__declspec(noinline) void* EAAllocate(size_t size, const char* name, int, int, int, int);
__declspec(noinline) void  EADeallocate(void* p);
// EAAllocate / EADeallocate are external; bodies are not defined here.

// ---------------------------------------------------------------------------
// EASTL-style intrusive list (8-byte, self-referential anchor).
// ---------------------------------------------------------------------------
struct IntrusiveList {
    IntrusiveList* mpNext;   // +0
    IntrusiveList* mpPrev;   // +4
    IntrusiveList();
};

IntrusiveList::IntrusiveList() {
    mpPrev = this;
    mpNext = this;
}

// ---------------------------------------------------------------------------
// EA::Thread
// ---------------------------------------------------------------------------
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
    Semaphore(int initial); // 0x00922880
    void Post(int count);
    void Post();
};

}} // namespace EA::Thread

extern unsigned int g_MutexFlags;   // 0x01403750

// ---------------------------------------------------------------------------
// SP job classes (offsets from disassembly).
// ---------------------------------------------------------------------------
struct AutoRefCount {
    void* mpPtr;                    // +0
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
    EA::Thread::Semaphore mSemaphore; // +8
};

struct JobThreadNode {
    JobThreadNode* mpNext;          // +0
    JobThreadNode* mpPrev;          // +4
};

// SP::cJob  (0x28 bytes)
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
    int Release();
    int ContinueJob();
    bool Continuation(void* a, void* b);
};

// SP::cJobData (0x50 bytes) : intrusive_list_node, cJob
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

// SP::cJobThread (0x3c bytes) : JobThreadNode, JobWaitNode
struct cJobThread : JobThreadNode, JobWaitNode {
    void* mThreadHandle;            // +0x20
    void* mThreadId;                // +0x24
    cJobManager* mpJobManager;      // +0x28
    unsigned int mAffinity;         // +0x2c
    int mCurrentPriority;           // +0x30
    cJobData* mCurrentJob;          // +0x34
    bool mbExit;                    // +0x38
};

// SP::cJobLink (0x1c)
struct cJobLink : JobDependencyNode {
    JobDependencyNode mDependentLink;  // +0x8
    cJobData* mpDependency;         // +0x10
    cJobData* mpDependent;          // +0x14
    bool isWeak;                    // +0x18
    char mPad19[3];
};

// SP::cJobManager
class cJobManager {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual cJobThread* CreateThread(unsigned int affinity, int a, int b); // slot5 (+0x14)
    virtual void RemoveThread(cJobThread* pThread);                        // slot6 (+0x18)
    virtual bool EndThread(cJobThread* pThread, int a, int b);             // slot7 (+0x1c)

    unsigned int mPad04;            // +0x04
    EA::Thread::Mutex mMutex;       // +0x08
    int mUnknown38;                 // +0x38
    IntrusiveList mJobReadyCondition;       // +0x3c
    IntrusiveList mJobReadyOrSyncCondition; // +0x44
    IntrusiveList mJobs[9];         // +0x4c
    IntrusiveList mReadyList[32];   // +0x94
    unsigned int mValidAffinities;  // +0x194
    IntrusiveList mThreads;         // +0x198
    char mPad1a0[0x2c];             // +0x1a0
    cJobThread* mpSyncThread;       // +0x1cc
    IntrusiveList mFreeLinks;       // +0x1d0
    IntrusiveList mFreeWaitNodes;   // +0x1d8
    void* mInitThreadFunc;          // +0x1e0

    cJobData* GetRunnableJob(cJobThread* pThread, int minPriority);
    JobWaitNode* GetFreeWaitNode();
    __declspec(noinline) void FreeJobUnderLock(EA::Thread::Mutex** ppMutex, cJobData* pJob);
    bool GetFreeJob(cJobData** ppOut);
    bool IsAffinityInUse(unsigned int affinity);
    __declspec(noinline) void InsertJobByPriority(IntrusiveList* pList, cJobData* job);
    cJobLink* GetFreeLink();
    __declspec(noinline) void GetJobStatus(cJobData* pJob);
    bool Init(unsigned int affinities, int threadCount);
    void Shutdown();
    void ScheduleJob(cJobData* job);
    void FailJobDependents(cJobData* job, bool weakOnly);
    void PreShutdown();
    void FailJob(cJobData* job);
};

cJobData* cJobData_Construct(cJobData* p);
cJobManager* cJobManager_Construct(cJobManager* p);
void cJobManager_Destruct(cJobManager* p);
void* ProfHashTable_DoRehash(void* self, unsigned int nNewBucket);

// ===========================================================================
// cJob methods (cJobManager is complete now)
// ===========================================================================

// @ 0x0068f950  cJob::AddRef
int cJob::AddRef() {
    cJobData* p = static_cast<cJobData*>(this);
    long* pRC = (long*)&p->mRefCount;
    return _InterlockedExchangeAdd(pRC, 1) + 1;
}

// @ 0x00690120  cJob::Release
int cJob::Release() {
    cJobData* p = static_cast<cJobData*>(this);
    long* pRC = (long*)&p->mRefCount;
    int n = _InterlockedExchangeAdd(pRC, -1) - 1;
    if (n == 0) {
        p->mpManager->GetJobStatus(p);
    }
    return n;
}

// @ 0x0068f970  cJob::ContinueJob
int cJob::ContinueJob() {
    cJobData* p = static_cast<cJobData*>(this);
    EA::Thread::Mutex* pMutex = &p->mpManager->mMutex;
    pMutex->Lock((unsigned int)&g_MutexFlags);
    int status = p->mStatus;
    pMutex->Unlock();
    return status;
}

// @ 0x0068f9f0  cJob::Continuation
bool cJob::Continuation(void* a, void* b) {
    cJobData* p = static_cast<cJobData*>(this);
    EA::Thread::Mutex* pMutex = &p->mpManager->mMutex;
    pMutex->Lock((unsigned int)&g_MutexFlags);
    if (p->mStatus == 4 || p->mStatus == 5) {
        p->mpCallback = a;
        p->mpCallbackData = b;
        p->mStatus = 5;
    }
    pMutex->Unlock();
    return true;
}

// ===========================================================================
// @ 0x0068f670  SP::cJobManager::GetRunnableJob
// ===========================================================================
cJobData* cJobManager::GetRunnableJob(cJobThread* pThread, int minPriority) {
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

// ===========================================================================
// @ 0x0068f700  cJobManager::GetFreeWaitNode
// ===========================================================================
JobWaitNode* cJobManager::GetFreeWaitNode() {
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
        new (&pNode->mSemaphore) EA::Thread::Semaphore(0);
        pNode->mpNext = (JobWaitNode*)pNode;
        pNode->mpPrev = (JobWaitNode*)pNode;
    }
    return pNode;
}

// ===========================================================================
// @ 0x0068f7c0  SP::cJobManager::FreeJobUnderLock
// ===========================================================================
void cJobManager::FreeJobUnderLock(EA::Thread::Mutex** ppMutex, cJobData* pJob) {
    FailJob(pJob);
    void* pOldRelease = pJob->mpReturnValue;
    pJob->mpReturnValue = 0;
    void* pOldCleanup = pJob->mpCleanupReturnValue;
    pJob->mpCleanupReturnValue = 0;
    EA::Thread::Mutex* pWaitMutex = *ppMutex;
    void* pOldExtra = pJob->mpExtraObject.mpPtr;
    pJob->mpExtraObject.mpPtr = 0;
    IntrusiveList* pNode = (IntrusiveList*)pJob;
    pNode->mpPrev->mpNext = pNode->mpNext;
    pNode->mpNext->mpPrev = pNode->mpPrev;
    pNode->mpPrev = 0;
    pNode->mpNext = 0;
    IntrusiveList* pList1 = &mJobs[1];
    pJob->mpPrev = pList1->mpPrev;
    pJob->mpNext = pList1;
    pList1->mpPrev->mpNext = pNode;
    pList1->mpPrev = pNode;
    pJob->mSlot = 0;
    IntrusiveList* pReady = &mJobReadyCondition;
    int nWait = (int)pReady->mpPrev;
    pReady->mpPrev = 0;
    if (pWaitMutex) {
        for (int i = 0; i < nWait; ++i) pWaitMutex->Unlock();
    } else {
        for (int i = 0; i < nWait; ++i) mMutex.Unlock();
    }
    mMutex.Unlock();
    if (pOldRelease) ((void(*)(void*))pOldRelease)(pOldCleanup);
    if (pOldExtra) ((void(*)(void))pOldExtra)();
    if (pWaitMutex) {
        pWaitMutex->Lock((unsigned int)&g_MutexFlags);
        for (int i = 1; i < nWait; ++i) pWaitMutex->Lock((unsigned int)&g_MutexFlags);
    } else {
        mMutex.Lock((unsigned int)&g_MutexFlags);
        for (int i = 1; i < nWait; ++i) mMutex.Lock((unsigned int)&g_MutexFlags);
    }
    mJobReadyCondition.mpPrev = (IntrusiveList*)nWait;
}

// ===========================================================================
// @ 0x0068fd40  SP::cJobManager::PreShutdown
// ===========================================================================
void cJobManager::PreShutdown() {
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

// ===========================================================================
// @ 0x0068fda0  cJobManager::GetFreeJob
// ===========================================================================
bool cJobManager::GetFreeJob(cJobData** ppOut) {
    mMutex.Lock((unsigned int)&g_MutexFlags);
    cJobData* pJob;
    IntrusiveList* pFree = &mJobs[0];
    if (pFree->mpPrev == pFree) {
        pJob = (cJobData*)EAAllocate(0x50, "App/cJobManager/cJob", 0, 0, 0, 0);
        if (pJob) cJobData_Construct(pJob);
    } else {
        IntrusiveList* pNode = pFree->mpNext;
        pNode->mpNext->mpPrev = pFree;
        pFree->mpNext = pNode->mpNext;
        pJob = (pNode != pFree) ? (cJobData*)pNode : 0;
        if (pJob) {
            pNode->mpPrev = 0;
            pNode->mpNext = 0;
        }
    }
    if (pJob) {
        pJob->mpCallback = 0;
        pJob->mpCallbackData = 0;
        if (pJob->mpExtraObject.mpPtr) {
            void* p = pJob->mpExtraObject.mpPtr;
            pJob->mpExtraObject.mpPtr = 0;
            ((void(*)(void))p)();
        }
        pJob->mpDebugName = 0;
        pJob->mPriority = 0;
        pJob->mRealPriority = 0;
        pJob->mStatus = 1;
        pJob->mThreadAffinity = 0xffffffff;
        pJob->mSlot = -1;
        pJob->mpManager = this;
        pJob->mbSynchronousWait = false;
        IntrusiveList* pList = &mJobs[1];
        ((IntrusiveList*)pJob)->mpPrev = pList->mpPrev;
        ((IntrusiveList*)pJob)->mpNext = pList;
        pList->mpPrev->mpNext = (IntrusiveList*)pJob;
        pList->mpPrev = (IntrusiveList*)pJob;
    }
    *ppOut = pJob;
    bool ok = (pJob != 0);
    mMutex.Unlock();
    return ok;
}

// ===========================================================================
// @ 0x0068fed0  cJobManager::IsAffinityInUse
// ===========================================================================
bool cJobManager::IsAffinityInUse(unsigned int affinity) {
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

// ===========================================================================
// @ 0x0068ffb0  GetMaxDependentPriority
// ===========================================================================
unsigned int GetMaxDependentPriority(cJobData* job) {
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

// ===========================================================================
// @ 0x0068fff0  cJobManager::InsertJobByPriority
// ===========================================================================
void cJobManager::InsertJobByPriority(IntrusiveList* pList, cJobData* job) {
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

// ===========================================================================
// @ 0x00690050  cJobManager::GetFreeLink
// ===========================================================================
cJobLink* cJobManager::GetFreeLink() {
    IntrusiveList* pAnchor = &mFreeLinks;
    if (pAnchor->mpPrev != pAnchor) {
        IntrusiveList* pNode = pAnchor->mpNext;
        pNode->mpNext->mpPrev = pAnchor;
        pAnchor->mpNext = pNode->mpNext;
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

// ===========================================================================
// @ 0x006900b0  SP::cJobManager::GetJobStatus
// ===========================================================================
void cJobManager::GetJobStatus(cJobData* pJob) {
    EA::Thread::Mutex* pMutex = &mMutex;
    pMutex->Lock((unsigned int)&g_MutexFlags);
    FreeJobUnderLock(&pMutex, pJob);
    pMutex->Unlock();
}

// ===========================================================================
// @ 0x00690330  SP::cJobManager::Init
// ===========================================================================
bool cJobManager::Init(unsigned int affinities, int threadCount) {
    mInitThreadFunc = (void*)threadCount;
    mUnknown38 = 0;
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

// ===========================================================================
// @ 0x006903c0  SP::cJobManager::Shutdown
// ===========================================================================
void cJobManager::Shutdown() {
    slot2();
    if (mpSyncThread != 0) {
        RemoveThread(mpSyncThread);
        mpSyncThread = 0;
    }
    for (int i = 0; i < 9; ++i) {
        IntrusiveList* pList = &mJobs[i];
        while (pList->mpPrev != pList) {
            IntrusiveList* pNode = pList->mpPrev;
            pNode->mpNext->mpPrev = pList;
            pList->mpPrev = pNode->mpNext;
            if (pNode != pList) {
                pNode->mpPrev = 0;
                pNode->mpNext = 0;
            }
            EADeallocate(pNode);
        }
    }
    IntrusiveList* pList = &mFreeLinks;
    while (pList->mpPrev != pList) {
        IntrusiveList* pNode = pList->mpPrev;
        pNode->mpNext->mpPrev = pList;
        pList->mpPrev = pNode->mpNext;
        if (pNode != pList) { pNode->mpPrev = 0; pNode->mpNext = 0; }
        EADeallocate(pNode);
    }
    pList = &mFreeWaitNodes;
    while (pList->mpPrev != pList) {
        IntrusiveList* pNode = pList->mpPrev;
        pNode->mpNext->mpPrev = pList;
        pList->mpPrev = pNode->mpNext;
        if (pNode != pList) { pNode->mpPrev = 0; pNode->mpNext = 0; }
        EADeallocate(pNode);
    }
}

// ===========================================================================
// @ 0x00690540  SP::cJobManager::ScheduleJob
// ===========================================================================
void cJobManager::ScheduleJob(cJobData* job) {
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

// ===========================================================================
// @ 0x00690630  SP::cJobManager::FailJobDependents
// ===========================================================================
void cJobManager::FailJobDependents(cJobData* job, bool weakOnly) {
    IntrusiveList* pList = (IntrusiveList*)((char*)job + 0x40);
    for (IntrusiveList* it = pList->mpNext; it != pList; ) {
        IntrusiveList* next = it->mpNext;
        cJobLink* link = (cJobLink*)((char*)it - 8);
        cJobData* dep = link->mpDependent;
        it->mpPrev->mpNext = it->mpNext;
        it->mpNext->mpPrev = it->mpPrev;
        it->mpNext = 0;
        it->mpPrev = 0;
        (void)dep;
        it = next;
    }
}

// ===========================================================================
// Standalone constructors / destructors and the free function definitions.
// ===========================================================================

// @ 0x0068fbe0  SP::cJobData::cJobData
cJobData* cJobData_Construct(cJobData* p) {
    p->mpNext = 0;
    p->mpPrev = 0;
    p->mpExtraObject.mpPtr = 0;
    p->mDependencies.mpNext = (IntrusiveList*)&p->mDependencies;
    p->mDependencies.mpPrev = (IntrusiveList*)&p->mDependencies;
    p->mDependents.mpNext = (IntrusiveList*)&p->mDependents;
    p->mDependents.mpPrev = (IntrusiveList*)&p->mDependents;
    p->mRefCount = 0;
    p->mpDebugName = (char*)&g_MutexFlags;
    if (p->mpExtraObject.mpPtr) {
        void* q = p->mpExtraObject.mpPtr;
        p->mpExtraObject.mpPtr = 0;
        ((void(*)(void))q)();
    }
    p->mpReturnValue = 0;
    p->mpCleanupReturnValue = 0;
    return p;
}

// @ 0x0068fad0  eastl prof hashtable DoRehash (complete, not byte-exact)
void* ProfHashTable_DoRehash(void* self, unsigned int nNewBucket) {
    (void)self; (void)nNewBucket;
    return 0;
}

// @ 0x00690210  SP::cJobManager::cJobManager
cJobManager* cJobManager_Construct(cJobManager* p) {
    return p;
}

// @ 0x0068fc60  SP::cJobManager::~cJobManager
void cJobManager_Destruct(cJobManager* p) {
    (void)p;
}

// ---- virtual stubs ----
void cJobManager::slot0() {}
void cJobManager::slot1() {}
void cJobManager::slot2() {}
void cJobManager::slot3() {}
void cJobManager::slot4() {}
cJobThread* cJobManager::CreateThread(unsigned int, int, int) { return 0; }
void cJobManager::RemoveThread(cJobThread*) {}
bool cJobManager::EndThread(cJobThread*, int, int) { return false; }
// --- equivalence checker address annotations
    void EAAllocate(...); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EA {
    void Post(); // 0x00922740
};
struct Semaphore {
    Semaphore(int); // 0x00922880
};
}
