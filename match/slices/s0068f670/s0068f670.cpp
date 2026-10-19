// Batch w1g5 slice s0068f670 — SP::cJobManager / SP::cJob subsystem.
// Region is /O2 (no frame pointer, register-allocated, EH with __ehhandler$).
#include "types.h"
#include <new>
#include <intrin.h>

// ---------------------------------------------------------------------------
// External helpers (addresses are masked relocations; bodies never inline).
// ---------------------------------------------------------------------------
__declspec(noinline) void* EAAllocate(size_t size, const char* name, int, int, int, int);  // 0x00f473a0
__declspec(noinline) void  EADeallocate(void* p);   // 0x00f47380
// EAAllocate / EADeallocate are external; bodies are not defined here.

// ---------------------------------------------------------------------------
// EASTL-style intrusive list (8-byte, self-referential anchor).
// ---------------------------------------------------------------------------
struct IntrusiveList {
    IntrusiveList* mpNext;   // +0
    IntrusiveList* mpPrev;   // +4
    IntrusiveList();
    ~IntrusiveList();        // out of line in the image (0x00620230)
};

IntrusiveList::IntrusiveList() {
    mpPrev = this;
    mpNext = this;
}

// Append a node at the tail of an intrusive list.
inline void AppendTail(IntrusiveList* pList, IntrusiveList* pNode) {
    pNode->mpPrev = pList->mpPrev;
    pNode->mpNext = pList;
    pList->mpPrev = pNode;
    pNode->mpPrev->mpNext = pNode;
}

// Detach and zero every node of a list, then zero the anchor itself.
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

// Reference-counted pointer that releases on scope exit (used for the extra
// object a finished job hands back).
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

// ---------------------------------------------------------------------------
// EA::Thread
// ---------------------------------------------------------------------------
namespace EA { namespace Thread {

class Mutex {
public:
    char mData[0x30];
    Mutex(const void* pParams, bool bInit); // 0x009222a0
    ~Mutex();                               // 0x00922130
    void Lock(unsigned int flags);          // 0x009221b0
    void Unlock();                          // 0x00922270
};

class Semaphore {
public:
    char mData[0x10];
    Semaphore(int initial); // 0x00922880
    ~Semaphore();           // 0x00922610
    void Post(int count = 1);                       // 0x00922740
};

}} // namespace EA::Thread

extern unsigned int g_MutexFlags;   // 0x01403750
extern char sz_13ec47c[];           // 0x013ec47c

// ---------------------------------------------------------------------------
// Reference-counted payload held by cJob::mpExtraObject.
// ---------------------------------------------------------------------------
struct IUnknown32 {
    virtual int AddRef();           // +0
    virtual int Release();          // +4
};

// EA vector: the allocation carries a leading refcount word in the image, so
// the destructor only frees the buffer when that word is zero.
template <class T>
struct EAVector {
    T* mpBegin;                     // +0
    T* mpEnd;                       // +4
    T* mpCap;                       // +8

    EAVector() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~EAVector() {
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            EADeallocate(mpBegin);
    }
};

// ---------------------------------------------------------------------------
// SP job classes (offsets from disassembly).
// ---------------------------------------------------------------------------
struct AutoRefCount {
    void* mpPtr;                    // +0
    AutoRefCount() : mpPtr(0) {}
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
struct cJobDataNode {
    void* mpNext; void* mpPrev;
    cJobDataNode() { mpPrev = 0; mpNext = 0; }
};

struct cJobData : cJobDataNode, cJob {
    cJobData();

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

// SP::cIJobManager — the interface base of cJobManager (vftable 0x01403758).
// Its virtual destructor is trivial and inlined, so a cJobManager destructor
// ends with nothing but the base vftable store.
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

// SP::cJobManager
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
    EA::Thread::Mutex mMutex;       // +0x08
    int mnLockCount;                // +0x38
    IntrusiveList mJobReadyCondition;       // +0x3c
    IntrusiveList mJobReadyOrSyncCondition; // +0x44
    IntrusiveList mJobs[9];         // +0x4c
    IntrusiveList mReadyList[32];   // +0x94
    unsigned int mValidAffinities;  // +0x194
    IntrusiveList mThreads;         // +0x198
    int mUnknown1a0;                // +0x1a0
    EAVector<void*> mWaitingThreads;    // +0x1a4
    char mPad1b0[8];                // +0x1b0
    EAVector<void*> mWaitingPriorities; // +0x1b8
    char mPad1c4[8];                // +0x1c4
    cJobThread* mpSyncThread;       // +0x1cc
    IntrusiveList mFreeLinks;       // +0x1d0
    IntrusiveList mFreeWaitNodes;   // +0x1d8
    void* mInitThreadFunc;          // +0x1e0

    cJobData* GetRunnableJob(cJobThread* pThread, int minPriority);
    JobWaitNode* GetFreeWaitNode();
    __declspec(noinline) void FreeJobUnderLock(EA::Thread::Mutex** ppMutex, cJobData* pJob);
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

// SP::ProfHashTable — open hash table of (key, next) nodes.
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
bool cJobManager::GetFreeJob(cJob** ppOut) {
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
            ((JobWaitNode*)pNode)->mSemaphore.~Semaphore();
            EADeallocate(pNode);
        }
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

// ===========================================================================
// Standalone constructors / destructors and the free function definitions.
// ===========================================================================

// @ 0x0068fbe0  SP::cJobData::cJobData
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

// @ 0x0068fad0  eastl::hashtable DoRehash
void ProfHashTable::DoRehash(unsigned int nNewBucketCount) {
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

// @ 0x00690210  SP::cJobManager::cJobManager
cJobManager::cJobManager()
    : mMutex(0, true), mnLockCount(0), mValidAffinities(0),
      mUnknown1a0(0), mpSyncThread(0), mInitThreadFunc(0)
{
}

// @ 0x0068fc60  SP::cJobManager::~cJobManager
cJobManager::~cJobManager() {
}

// ---- virtual stubs ----
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

