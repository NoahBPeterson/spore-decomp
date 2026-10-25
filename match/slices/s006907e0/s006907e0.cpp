// Batch w1g5 slice s006907e0 — SP::cJobManager scheduling/dependency subsystem.
// Region is /O2 (no frame pointer, register-allocated, EH with __ehhandler$).
#include "types.h"
#include <new>
#include <string.h>
#include <intrin.h>

__declspec(noinline) void* EAAllocate(size_t size, const char* name, int, int, int, int);
__declspec(noinline) void  EADeallocate(void* p);                                          // 0x00f47380

void* operator new(size_t, const char* name, int, unsigned, const char* file, int line);   // 0x00f473a0
#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

struct IntrusiveList {
    IntrusiveList* mpNext;   // +0
    IntrusiveList* mpPrev;   // +4
    IntrusiveList();
    ~IntrusiveList();
    bool empty() const { return mpPrev == this; }
    void remove()
    {
        IntrusiveList* p = mpPrev;
        IntrusiveList* n = mpNext;
        p->mpNext = n;
        n->mpPrev = p;
        mpNext = 0;
        mpPrev = 0;
    }
    void push_back_to(IntrusiveList* anchor)
    {
        mpNext = anchor;
        mpPrev = anchor->mpPrev;
        anchor->mpPrev = this;
        mpPrev->mpNext = this;
    }
};
IntrusiveList::IntrusiveList() { mpPrev = this; mpNext = this; }
// Debug-list teardown: detach and zero every node (the nodes themselves are owned elsewhere).
IntrusiveList::~IntrusiveList()
{
    IntrusiveList* p = mpNext;
    if (p != this) {
        for (;;) {
            IntrusiveList* pNext = p->mpNext;
            p->mpPrev = 0;
            p->mpNext = 0;
            p = pNext;
            if (pNext == this)
                break;
        }
    }
}

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
struct ThreadParameters;
class Thread {
public:
    char mData[4];
    int GetPriority() const;                                          // 0x00922a90
    bool SetPriority(int priority);                                   // 0x00922ab0
    void SetName(const char* name);                                   // 0x00922b30
    void* GetId() const;                                              // 0x00922a80
    void* Start(void* fn, void* arg, const ThreadParameters* params, void* wrapper);   // 0x00922f30
};
void* GetThreadId();                                                  // 0x00921cc0
int ThreadStartWrapper();                                             // 0x00922920
}} // namespace EA::Thread

extern unsigned int g_MutexFlags;   // 0x01403750

// ---------------------------------------------------------------------------
// eastl::basic_string<char> (only the pieces this slice uses)
// ---------------------------------------------------------------------------
extern char gEmptyString16[16];     // 0x01667bac
struct EStr {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    EStr()
    {
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCapacity = gEmptyString16 + 1;
    }
    ~EStr()
    {
        if ((int)(mpCapacity - mpBegin) > 1 && mpBegin != 0)
            EADeallocate(mpBegin);
    }
    EStr* sprintf(const char* fmt, ...);              // 0x00472fe0
    EStr* append_sprintf(const char* fmt, ...);       // 0x005f9450
};

// ---------------------------------------------------------------------------
// eastl::prime_rehash_policy / fixed_pool_base (shared EASTL subset)
// ---------------------------------------------------------------------------
struct fixed_pool_base {
    void* mpHead;          // +0x00
    void* mpNext;          // +0x04
    void* mpPoolBegin;     // +0x08
    void* mpCapacity;      // +0x0c
    uint32_t mnNodeSize;   // +0x10
    void* mpBucketBuffer;  // +0x14
    void init(void* pMemory, size_t memorySize, size_t nodeSize, size_t alignment, size_t alignmentOffset);   // 0x00921260
};
uint32_t GetPrevBucketCountOnly(uint32_t nBucketCount);   // 0x00921340

struct prime_rehash_policy {
    float mfMaxLoadFactor;    // +0x00
    float mfGrowthFactor;     // +0x04
    uint32_t mnNextResize;    // +0x08
    struct RehashResult {
        bool first;
        uint32_t second;
        RehashResult() {}
        RehashResult(const RehashResult& x) { first = x.first; second = x.second; }
    };
    RehashResult GetRehashRequired(uint32_t nBucketCount, uint32_t nElementCount, uint32_t nElementAdd);  // 0x00921440
    uint32_t GetBucketCount(uint32_t nElementCount) const;    // 0x009213c0
};

struct ProfHashNode {
    const void* mKey;        // +0x00
    ProfHashNode* mpNext;    // +0x04
};

struct ProfInsertResult {
    void* mpNode;      // +0x00
    void** mpBucket;   // +0x04
    bool mbInserted;   // +0x08
};

// The profiling hash table: buckets at +0x04, policy at +0x10, node allocator at +0x1c,
// and (for the fixed node-count instantiation) an embedded bucket buffer and node pool.
struct ProfHashTable {
    uint32_t mHashCodeBase;            // +0x00
    ProfHashNode** mpBuckets;          // +0x04
    uint32_t mnBucketCount;            // +0x08
    uint32_t mnElementCount;           // +0x0c
    prime_rehash_policy mRehashPolicy; // +0x10
    fixed_pool_base mAllocator;        // +0x1c
    void* mBucketBuffer[34];           // +0x34  (33 buckets + sentinel)
    char mNodePool[0x100];             // +0xbc  (32 nodes of 8 bytes)

    ProfHashTable(uint32_t hashFunction, uint32_t predicate);                // 0x00691400
    void BaseConstruct(uint32_t nBucketCount, uint32_t hash, const uint32_t& h2,
                       const uint32_t& h3, uint32_t eq, const uint32_t& ex,
                       const fixed_pool_base& a);                            // 0x00690160
    void DoRehash(uint32_t nBucketCount);                                    // 0x0068fad0
    ProfInsertResult DoInsertValue(const void* const& key, bool bUnused);    // 0x006909e0
};

// ---------------------------------------------------------------------------
// SPVector<T> (SP's vector: three pointers + an 8-byte allocator)
// ---------------------------------------------------------------------------
template <typename T>
struct SPVector {
    T* mpBegin;                 // +0x00
    T* mpEnd;                   // +0x04
    T* mpCapacity;              // +0x08
    char mAllocator[8];         // +0x0c

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (uint32_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValueI(mpEnd, value);
    }
    void DoInsertValueI(T* position, const T& value);   // 0x004558a0
};

// eastl::vector<cJobThread*, fixed_vector_allocator<4,N,4,0,true> > (waiting list 1):
// same growth policy as WaitingList2, but the release path checks the debug allocation header.
struct WaitingList1 {
    EA::Thread::Thread** mpBegin;      // +0x00
    EA::Thread::Thread** mpEnd;        // +0x04
    EA::Thread::Thread** mpCapacity;   // +0x08
    char mAllocator[8];                // +0x0c

    typedef EA::Thread::Thread* T;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (uint32_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(T const& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(T* position, T const& value);   // 0x00690b80
};

struct AutoRefCount { void* mpPtr; };
struct cJobData;
class cJobManager;
struct cJobThread;
struct cJobLink;
struct JobDependencyNode { JobDependencyNode* mpNext; JobDependencyNode* mpPrev; };

namespace SP {
struct JobCondition {
    IntrusiveList mWaitList;   // +0x00
    void Signal();             // 0x0068f5d0
};
} // namespace SP

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
    EA::Thread::Thread mThread;     // +0x20
    void* mThreadId;                // +0x24
    cJobManager* mpJobManager;      // +0x28
    unsigned int mAffinity;         // +0x2c
    int mCurrentPriority;           // +0x30
    cJobData* mCurrentJob;          // +0x34
    bool mbExit;                    // +0x38
    cJobThread* Ctor();             // 0x0068f600
};

struct cJobLink : JobDependencyNode {
    JobDependencyNode mDependentLink;  // +0x8
    cJobData* mpDependency;         // +0x10
    cJobData* mpDependent;          // +0x14
    bool isWeak;                    // +0x18
};

unsigned __stdcall JobThreadProc(void* p);
class cJobManager {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual cJobThread* CreateJobThread(unsigned int affinity, bool createThread, int priority); // +0x14
    virtual void RemoveThread(cJobThread* pThread);                        // +0x18
    virtual bool EndThread(cJobThread* pThread, int a, int b);             // +0x1c

    unsigned int mPad04;            // +0x04
    EA::Thread::Mutex mMutex;       // +0x08
    int mUnknown38;                 // +0x38
    SP::JobCondition mJobReadyCondition;       // +0x3c
    SP::JobCondition mJobReadyOrSyncCondition; // +0x44
    IntrusiveList mJobs[9];         // +0x4c
    IntrusiveList mReadyList[32];   // +0x94
    unsigned int mValidAffinities;  // +0x194
    IntrusiveList mThreads;         // +0x198
    int mActiveJobCount;            // +0x1a0
    SPVector<unsigned int> mWaitingPriorities;   // +0x1a4
    WaitingList1 mWaitingThreads;                // +0x1b8
    cJobThread* mpSyncThread;       // +0x1cc
    IntrusiveList mFreeLinks;       // +0x1d0
    IntrusiveList mFreeWaitNodes;   // +0x1d8
    void* mInitThreadFunc;          // +0x1e0

    void QueueJobUnderLock(cJobData* job);
    void PromoteJobPriorityUnderLock(cJobData* job, int priority);
    void SetJobPriorityUnderLock(cJobData* job, int priority);
    void CheckDependentPriority(cJobData* job, int priority);
    void InsertWaitingThread(int priority);                              // 0x00691500
    void ScheduleJob(cJobData* job);
    void FailJob(cJobData& job);                                         // 0x00690f60
    void FailNonRunnableJobs();                                          // 0x006910a0
    void FailJobDependents(cJobData* job, bool weakOnly);                // 0x00690630
    __declspec(noinline) void AddJobDependency(cJobData* dependent, cJobData* dependency, bool weak);
    cJobLink* GetFreeLink();
    void FlushWaitingLists();                                            // 0x006915c0
    void RebuildWaitingLists();
    void FreeJobUnderLock(EA::Thread::Mutex** ppMutex, cJobData* job);   // 0x0068f7c0
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
// @ 0x006909e0  ProfHashTable::DoInsertValue
// Hashes the key, walks the bucket chain, and on a miss takes a node either from
// the allocator's free list or from the allocator, rehashes if the policy asks,
// then links the node at the head of its bucket.
// ===========================================================================
ProfInsertResult ProfHashTable::DoInsertValue(const void* const& key, bool) {
    ProfInsertResult result;
    const uint32_t hash = (uint32_t)key;
    uint32_t bucket = hash % mnBucketCount;
    ProfHashNode** pBucket = &mpBuckets[bucket];
    ProfHashNode* node = *pBucket;
    while (node != 0) {
        if (node->mKey == key) {
            result.mpNode = node;
            result.mpBucket = (void**)pBucket;
            result.mbInserted = false;
            return result;
        }
        node = node->mpNext;
    }
    prime_rehash_policy::RehashResult rehash =
        mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
    node = (ProfHashNode*)mAllocator.mpHead;
    if (node != 0) {
        mAllocator.mpHead = *(void**)node;
    } else {
        node = (ProfHashNode*)::operator new(mAllocator.mnNodeSize, "App", 0, 0,
                                             EASTL_ALLOC_FILE, 0xd1);
    }
    if (node != 0)
        node->mKey = key;
    node->mpNext = 0;
    if (rehash.first) {
        bucket = hash % rehash.second;
        DoRehash(rehash.second);
    }
    node->mpNext = mpBuckets[bucket];
    mpBuckets[bucket] = node;
    ++mnElementCount;
    result.mpNode = node;
    result.mpBucket = (void**)&mpBuckets[bucket];
    result.mbInserted = true;
    return result;
}

// ===========================================================================
// @ 0x00690b80  WaitingList1::DoInsertValue
// ===========================================================================
void WaitingList1::DoInsertValue(EA::Thread::Thread** position, EA::Thread::Thread* const& value) {
    if (mpEnd != mpCapacity) {
        EA::Thread::Thread* const* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        if (mpEnd != 0)
            *mpEnd = *(mpEnd - 1);
        memmove(mpEnd - ((mpEnd - 1) - position), position,
                (size_t)((char*)(mpEnd - 1) - (char*)position));
        *position = *pValue;
        ++mpEnd;
    } else {
        const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
        const size_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        EA::Thread::Thread** const pNewData =
            (nNewSize != 0) ? (EA::Thread::Thread**)::operator new(nNewSize * sizeof(EA::Thread::Thread*),
                                                                  "App", 0, 0, EASTL_ALLOC_FILE, 0xd1)
                            : 0;
        EA::Thread::Thread** pNewEnd = (EA::Thread::Thread**)memcpy(
            pNewData, mpBegin, (size_t)((char*)position - (char*)mpBegin)) + (position - mpBegin);
        if (pNewEnd != 0)
            *pNewEnd = value;
        ++pNewEnd;
        pNewEnd = (EA::Thread::Thread**)memcpy(pNewEnd, position,
                                              (size_t)((char*)mpEnd - (char*)position)) + (mpEnd - position);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            EADeallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// eastl::vector<cJob*, fixed_vector_allocator<4,N,4,0,true> >::DoInsertValue (waiting list 2).
struct WaitingList2 {
    cJob** mpBegin;          // +0
    cJob** mpEnd;            // +4
    cJob** mpCapacity;       // +8
    int mOverflowAllocator;  // +0xc
    void* mpPoolBegin;       // +0x10
    cJob** DoAllocate(const size_t& n) {
        if (n)
            return (cJob**)::operator new(n * sizeof(cJob*), "App", 0, 0, EASTL_ALLOC_FILE, 0xd1);
        return 0;
    }
    void DoFree(cJob** p) {
        if (p && p != mpPoolBegin)
            EADeallocate(p);
    }
    void DoInsertValue(cJob** position, cJob* const& value);
};
// @ 0x00690c90
void WaitingList2::DoInsertValue(cJob** position, cJob* const& value) {
    if (mpEnd != mpCapacity) {
        cJob* const* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) cJob*(*(mpEnd - 1));
        memmove(mpEnd - ((mpEnd - 1) - position), position, (size_t)((char*)(mpEnd - 1) - (char*)position));
        *position = *pValue;
        ++mpEnd;
    } else {
        const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
        const size_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        cJob** const pNewData = DoAllocate(nNewSize);
        cJob** pNewEnd = (cJob**)memcpy(pNewData, mpBegin, (size_t)((char*)position - (char*)mpBegin)) + (position - mpBegin);
        ::new (pNewEnd) cJob*(value);
        ++pNewEnd;
        pNewEnd = (cJob**)memcpy(pNewEnd, position, (size_t)((char*)mpEnd - (char*)position)) + (mpEnd - position);
        DoFree(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ===========================================================================
// @ 0x00690da0  SP::cJobManager::CreateJobThread
// ===========================================================================
cJobThread* cJobManager::CreateJobThread(unsigned int affinity, bool createThread, int priority) {
    cJobThread* pThread = (cJobThread*)::operator new(0x3c, "App/cJobManager/cJobThread", 0, 0, 0, 0);
    if (pThread != 0)
        pThread = pThread->Ctor();
    if (pThread == 0)
        return 0;
    pThread->mpJobManager = this;
    pThread->mAffinity = affinity;
    pThread->mCurrentPriority = (int)0x80000000;
    pThread->mCurrentJob = 0;
    pThread->mbExit = false;
    mMutex.Lock((unsigned int)&g_MutexFlags);
    ((IntrusiveList*)pThread)->push_back_to(&mThreads);
    if (createThread) {
        pThread->mThread.Start((void*)&JobThreadProc, pThread, 0,
                               (void*)EA::Thread::ThreadStartWrapper());
        EStr name;
        int index = -1;
        IntrusiveList* p = (IntrusiveList*)&mThreads;
        do {
            p = p->mpNext;
            ++index;
        } while (p != (IntrusiveList*)&mThreads);
        --index;
        name.sprintf("Job Thread %d", index);
        if (affinity != 0x80000000)
            name.append_sprintf(", p=%d", priority);
        pThread->mThread.SetName(name.mpBegin);
        pThread->mThreadId = pThread->mThread.GetId();
    } else {
        pThread->mThreadId = EA::Thread::GetThreadId();
    }
    unsigned int validAffinities = 0;
    for (IntrusiveList* it = mThreads.mpNext; it != &mThreads; it = it->mpNext) {
        cJobThread* t = (cJobThread*)it;
        if (t->mThreadId != 0)
            validAffinities |= t->mAffinity;
    }
    mValidAffinities = validAffinities;
    mMutex.Unlock();
    return pThread;
}

// ===========================================================================
// @ 0x00690f60  SP::cJobManager::FailJob
// ===========================================================================
void cJobManager::FailJob(cJobData& job) {
    while (!job.mDependencies.empty()) {
        cJobLink* link = (cJobLink*)job.mDependencies.mpPrev;
        cJobData* dependency = link->mpDependency;
        ((IntrusiveList*)((char*)link + 8))->remove();
        ((IntrusiveList*)link)->remove();
        if (dependency->mRealPriority == job.mRealPriority) {
            int maxPriority = dependency->mPriority;
            IntrusiveList* pDepAnchor = &dependency->mDependents;
            for (IntrusiveList* it = pDepAnchor->mpNext; it != pDepAnchor; it = it->mpNext) {
                cJobLink* pDependentLink = (cJobLink*)((char*)it - 8);
                int pri = pDependentLink->mpDependent->mRealPriority;
                if (pri > maxPriority)
                    maxPriority = pri;
            }
            if (maxPriority < dependency->mRealPriority)
                SetJobPriorityUnderLock(dependency, maxPriority);
        }
        ((IntrusiveList*)link)->push_back_to(&mFreeLinks);
    }
    FailJobDependents(&job, false);
    ((IntrusiveList*)&job)->remove();
    ((IntrusiveList*)&job)->push_back_to(&mJobs[8]);
    const int oldStatus = job.mStatus;
    job.mStatus = 8;
    if (job.mbSynchronousWait) {
        job.mbSynchronousWait = false;
        mJobReadyOrSyncCondition.Signal();
    }
    if (((1 << (oldStatus & 0x1f)) & 0x7c) != 0) {
        if (_InterlockedExchangeAdd((volatile long*)&job.mRefCount, -1) == 1)
            job.mpManager->FreeJobUnderLock(0, &job);
    }
}

// ===========================================================================
// @ 0x006910a0  SP::cJobManager::FailNonRunnableJobs
// Moves every job that can no longer run (affinity no longer valid, or waiting in a
// ready list whose affinity is gone) to a local list and fails them.
// ===========================================================================
void cJobManager::FailNonRunnableJobs() {
    IntrusiveList failed;
    for (IntrusiveList* it = mJobs[2].mpNext; it != &mJobs[2]; ) {
        IntrusiveList* pNext = it->mpNext;
        cJobData* job = (cJobData*)it;
        if ((mValidAffinities & job->mThreadAffinity) == 0)
            it->push_back_to(&failed);
        it = pNext;
    }
    if (mValidAffinities == 0) {
        for (IntrusiveList* it = mJobs[3].mpNext; it != &mJobs[3]; ) {
            IntrusiveList* pNext = it->mpNext;
            it->push_back_to(&failed);
            it = pNext;
        }
    }
    unsigned int bits = ~mValidAffinities;
    while (bits != 0) {
        unsigned int bit = 0;
        unsigned int value = bits;
        if ((value & 0xffff0000) != 0) {
            bit = 0x10;
            value >>= 0x10;
        }
        if ((value & 0xff00) != 0) {
            bit += 8;
            value >>= 8;
        }
        if ((value & 0xf0) != 0) {
            bit += 4;
            value >>= 4;
        }
        if ((value & 0xc) != 0) {
            bit += 2;
            value >>= 2;
        }
        if ((value & 0x2) != 0)
            bit += 1;
        bits &= ~(1u << bit);
        IntrusiveList* pReady = &mReadyList[bit];
        for (IntrusiveList* it = pReady->mpNext; it != pReady; ) {
            IntrusiveList* pNext = it->mpNext;
            it->push_back_to(&failed);
            it = pNext;
        }
    }
    while (!failed.empty())
        FailJob(*(cJobData*)failed.mpNext);
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
                FailJob(*dependent);
        } else if (dependency->mStatus != 7) {
            cJobLink* link = GetFreeLink();
            if (link == 0) {
                FailJob(*dependent);
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
// @ 0x00691400  ProfHashTable::ProfHashTable (fixed hash set instantiation)
// Embeds the node pool at +0xbc and the bucket buffer at +0x34, then applies
// the rehash policy.
// ===========================================================================
ProfHashTable::ProfHashTable(uint32_t hashFunction, uint32_t predicate) {
    union PoolOrPolicy {
        fixed_pool_base pool;
        prime_rehash_policy policy;
    } temp;
    char* const poolBegin = (char*)this + 0xbc;
    const size_t alignment = 4;
    temp.pool.mpHead = 0;
    temp.pool.init(poolBegin, (size_t)(8 * 32), 8, alignment, 0);
    temp.pool.mpPoolBegin = poolBegin;
    temp.pool.mpCapacity = poolBegin + 8 * 32;
    temp.pool.mnNodeSize = 8;
    temp.pool.mpBucketBuffer = mBucketBuffer;
    const uint32_t nPrevBuckets = GetPrevBucketCountOnly(0x21);
    BaseConstruct(nPrevBuckets, hashFunction, predicate, predicate, predicate, predicate, temp.pool);

    temp.policy.mfMaxLoadFactor = 10000.0f;
    temp.policy.mfGrowthFactor = 2.0f;
    temp.policy.mnNextResize = 0;
    mRehashPolicy = temp.policy;
    const uint32_t nBuckets = temp.policy.GetBucketCount(mnElementCount);
    if (nBuckets > mnBucketCount)
        DoRehash(nBuckets);
}

// ===========================================================================
// @ 0x00691500  cJobManager::InsertWaitingThread
// Raises every worker thread to at least `priority`, remembering the old values.
// ===========================================================================
void cJobManager::InsertWaitingThread(int priority) {
    ++mActiveJobCount;
    for (IntrusiveList* it = mThreads.mpNext; it != &mThreads; it = it->mpNext) {
        cJobThread* pThread = (cJobThread*)it;
        EA::Thread::Thread* pEAThread = &pThread->mThread;
        int oldPriority = pEAThread->GetPriority();
        if (oldPriority != (int)0x80000000 && oldPriority < priority) {
            pEAThread->SetPriority(priority);
            mWaitingPriorities.push_back((unsigned int)oldPriority);
            mWaitingThreads.push_back(pEAThread);
        }
    }
}

// ===========================================================================
// @ 0x006915c0  cJobManager::FlushWaitingLists
// Restores the thread priorities recorded by InsertWaitingThread once the last
// waiting job has been let through.
// ===========================================================================
void cJobManager::FlushWaitingLists() {
    if (mActiveJobCount > 0) {
        if (--mActiveJobCount == 0) {
            for (int i = (int)mWaitingPriorities.size() - 1; i >= 0; --i)
                mWaitingThreads[i]->SetPriority((int)mWaitingPriorities[i]);
            mWaitingPriorities.clear();
            mWaitingThreads.clear();
        }
    }
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

// ===========================================================================
// @ 0x0068f570  job thread entry point
// ===========================================================================
unsigned __stdcall JobThreadProc(void* p) {
    (void)p;
    return 0;
}
