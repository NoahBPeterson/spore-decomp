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

extern unsigned int g_MutexFlags;

struct MutexScopedLock {
    EA::Thread::Mutex* mpMutex;
    MutexScopedLock(EA::Thread::Mutex* m) : mpMutex(m) { m->Lock((unsigned int)&g_MutexFlags); }
    ~MutexScopedLock() { mpMutex->Unlock(); }
};

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
    void Cancel(void* p);
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
    char mPad08[0x18];              // +0x08
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
    virtual cJobThread* CreateThread(unsigned int affinity, int a, int b);
    virtual void RemoveThread(cJobThread* pThread);
    virtual bool EndThread(cJobThread* pThread, int a, int b);

    unsigned int mPad04;
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
    void RunJobBody(cJobThread* t, cJobData** ppJob);
    void CancelJob(cJobData* job, void* p);
    cJobData* GetRunnableJob(cJobThread* pThread, int minPriority);
    void ScheduleJob(cJobData* job);
    void FailJob(cJobData* job);
    void HandleJobResult(cJobData* job);
};

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
void cJob::Cancel(void* p) {
    cJobData* self = static_cast<cJobData*>(this);
    self->mpManager->CancelJob(self, p);
}

// ===========================================================================
// @ 0x00691680  cJobManager worker loop (1706 bytes)
// ===========================================================================
void cJobManager::RunJobBody(cJobThread* t, cJobData** ppJob) {
    // TODO: full worker loop; left as a skeleton.
    (void)t; (void)ppJob;
}

// ===========================================================================
// @ 0x00691d30  SP::cJobManager::RunJob
// ===========================================================================
void JobManager_RunJob(cJobManager* mgr, cJobData* job) {
    // TODO: run the job callback and inspect the result; skeleton.
    (void)mgr; (void)job;
}

// ===========================================================================
// @ 0x00691f60  cJobManager helper (273 bytes)
// ===========================================================================
void JobManagerHelper00691f60() {
    // TODO: skeleton.
}

// ===========================================================================
// @ 0x00692150  cJobManager helper (466 bytes)
// ===========================================================================
void JobManagerHelper00692150() {
    // TODO: skeleton.
}

// ===========================================================================
// @ 0x00692330  SP::cJobManager::CancelJob
// ===========================================================================
void cJobManager::CancelJob(cJobData* job, void* p) {
    // TODO: skeleton.
    (void)job; (void)p;
}

// ===========================================================================
// @ 0x00692430  cJobManager helper (385 bytes)
// ===========================================================================
void JobManagerHelper00692430() {
    // TODO: skeleton.
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
void cJobManager::ScheduleJob(cJobData*) {}
void cJobManager::FailJob(cJobData*) {}
