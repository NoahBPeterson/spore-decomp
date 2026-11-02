// src/game/UTFSpore_Win32/eathread_mutex.cpp -- migrated from slice(s) s00922500, s009215c0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/eathread_mutex.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Thread/Condition.h"
#include "EAConditionData.h"
#include "EAMutexData.h"
#include "EASemaphoreData.h"
#include "EA/Thread/Mutex.h"
#include "EA/Thread/Semaphore.h"
#include <windows.h>
#include <stddef.h>
#include <string.h>
#include "EAThreadDynamicData.h"
#include "EA/Thread/Thread.h"
#include <intrin.h>
#include <new>

// ---- items of slice s009215c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Thread {
unsigned GetThreadTime();              // 0x0094d340 (jmp GetTickCount)
}
}
namespace EA {
namespace Thread {
void ThreadSleep(unsigned* pMilliseconds);
}
}
namespace EA {
namespace Thread {
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
}
}
namespace EA {
namespace Thread {
extern "C" long _InterlockedExchange(volatile long*, long);
}
}
namespace EA {
namespace Thread {
template <typename T>
class AtomicInt_s0092_15c0 {
public:
    volatile T mValue;                                  // +0x00
    AtomicInt_s0092_15c0(T n = 0) { SetValue(n); }
    void SetValue(T n) { _InterlockedExchange((long*)&mValue, n); }
};
}
}
namespace EA {
namespace Thread {
struct MutexParameters {
    unsigned char mbIntraProcess;  // +0x00
    char          mName[0x10];     // +0x01
    MutexParameters() {}
    MutexParameters(int count, bool intra, const char* name);  // 0x009225d0-style, unused
};
}
}
namespace EA {
namespace Thread {
struct ConditionParameters {
    unsigned char mbIntraProcess;  // +0x00
    char          mName[0x10];     // +0x01
};
}
}
namespace EA {
namespace Thread {
struct RWMutexParameters {
    unsigned char mbIntraProcess;  // +0x00
    char          mName[0x10];     // +0x01
};
}
}
namespace EA {
namespace Thread {
struct SemaphoreParameters {
    int           mnCount;         // +0x00
    bool          mbIntraProcess;  // +0x04
    char          mName[0x10];     // +0x05
    SemaphoreParameters() {}
    SemaphoreParameters(int count, bool intra, const char* name);  // 0x009225d0
};
}
}
namespace EA {
namespace Thread {
struct EAMutexData {
    unsigned __int64 mData[4];        // +0x00
    int              mnLockCount;     // +0x20
    unsigned char    mbIntraProcess;  // +0x24
    void*            mThreadId;       // +0x28
};
}
}
namespace EA {
namespace Thread {
struct EASemaphoreData {
    void* mhSemaphore;       // +0x00
    int   mnCount;           // +0x04
    int   mnCancelCount;     // +0x08
    bool  mbIntraProcess;    // +0x0c
    __declspec(noinline) ~EASemaphoreData();   // 0x00922610
};
}
}
namespace EA {
namespace Thread {
class Semaphore_s0092_15c0 {
public:
    EASemaphoreData mSemaphoreData;                     // +0x00, size 0x10
    Semaphore_s0092_15c0(const SemaphoreParameters* p, bool bDefault);  // 0x00922820
    bool Init(const SemaphoreParameters* p);            // 0x00922620
    int  Wait(unsigned const& timeout);                 // 0x00922690
    int  Post(int n);                                   // 0x00922740
};
}
}
namespace EA {
namespace Thread {
class Mutex_s0092_15c0 {
public:
    EAMutexData mMutexData;      // +0x00, size 0x30
    Mutex_s0092_15c0(const MutexParameters* p = 0, bool bDefault = true);   // 0x009222a0
    __declspec(noinline) ~Mutex_s0092_15c0();                              // 0x00922130
    bool Init(const MutexParameters* p);                        // 0x00922150
    int  Lock(unsigned const& timeout);                         // 0x009221b0
    int  Unlock();                                              // 0x00922270
};
}
}
namespace EA {
namespace Thread {
struct EAConditionData {
    AtomicInt_s0092_15c0<int> mnWaitersBlocked;    // +0x00
    int            mnWaitersToUnblock;  // +0x04
    int            mnWaitersDone;       // +0x08
    Semaphore_s0092_15c0      mSemaphoreBlockQueue;// +0x0c
    Semaphore_s0092_15c0      mSemaphoreBlockLock; // +0x1c
    Mutex_s0092_15c0          mUnblockLock;        // +0x30
    __forceinline EAConditionData()
        : mnWaitersBlocked(0), mnWaitersToUnblock(0), mnWaitersDone(0),
          mSemaphoreBlockQueue((const SemaphoreParameters*)0, false),
          mSemaphoreBlockLock((const SemaphoreParameters*)0, false),
          mUnblockLock((const MutexParameters*)0, false) {}
};
}
}
namespace EA {
namespace Thread {
class Condition_s0092_15c0 {
public:
    EAConditionData mConditionData;                      // +0x00, size 0x60
    Condition_s0092_15c0(const ConditionParameters* p = 0, bool bInit = true);  // 0x00921f00
    __declspec(noinline) ~Condition_s0092_15c0();                    // 0x00921e40
    bool Init(const ConditionParameters* pParameters);   // 0x00921e60
    int  Wait(Mutex_s0092_15c0* pMutex, unsigned const& timeout);   // 0x00921f80
    bool Signal(bool bAll);                              // 0x00922050
};
}
}
namespace EA {
namespace Thread {
extern unsigned g_mutexTimeout;   // 0x0143dc58
}
}
namespace EA {
namespace Thread {
extern unsigned g_rwTimeout;      // 0x0143dc64
}
}
namespace EA {
namespace Thread {
struct EARWMutexData {
    int       mnReadWaiters;    // +0x00
    int       mnWriteWaiters;   // +0x04
    int       mnReaders;        // +0x08
    void*     mThreadIdWriter;  // +0x0c
    Mutex_s0092_15c0     mMutex;           // +0x10
    Condition_s0092_15c0 mReadCondition;   // +0x40
    Condition_s0092_15c0 mWriteCondition;  // +0xa0
};
}
}
namespace EA {
namespace Thread {
class RWMutex {
public:
    enum LockType { kLockTypeNone = 0, kLockTypeRead = 1, kLockTypeWrite = 2 };
    EARWMutexData mRWMutexData;         // +0x00, size 0x100
    ~RWMutex();                         // 0x00922310
    bool Init(const RWMutexParameters* pParameters);  // 0x00922330
    int  Lock(LockType lockType, unsigned const& timeout);   // 0x009223a0
    int  Unlock();                      // 0x00922480
};
}
}
namespace EA {
namespace Thread {
__declspec(noinline) EASemaphoreData::~EASemaphoreData() { if (mhSemaphore) CloseHandle(mhSemaphore); }  // namespace EA::Thread
}
}
// ---- items of slice s009215c0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
namespace EA { namespace Thread { HANDLE GetThreadId(); }}  // 0x00921cc0 (stays in the slice: not this object's)

// @ 0x00922050
namespace EA { namespace Thread {
bool Condition_s0092_15c0::Signal(bool bBroadcast)
{
    if (mConditionData.mUnblockLock.Lock(g_mutexTimeout) < 0) return false;
    int n;
    if (mConditionData.mnWaitersToUnblock != 0) {
        if (_InterlockedExchangeAdd((volatile long*)&mConditionData.mnWaitersBlocked, 0) == 0) {
            mConditionData.mUnblockLock.Unlock();
            return true;
        }
        if (bBroadcast) {
            n = _InterlockedExchange((volatile long*)&mConditionData.mnWaitersBlocked, 0);
            mConditionData.mnWaitersToUnblock += n;
            mConditionData.mUnblockLock.Unlock();
            mConditionData.mSemaphoreBlockQueue.Post(n);
            return true;
        }
        ++mConditionData.mnWaitersToUnblock;
        n = 1;
    } else {
        if (_InterlockedExchangeAdd((volatile long*)&mConditionData.mnWaitersBlocked, 0)
                <= mConditionData.mnWaitersDone) {
            mConditionData.mUnblockLock.Unlock();
            return true;
        }
        if (mConditionData.mSemaphoreBlockLock.Wait(g_mutexTimeout) == -1) {
            mConditionData.mUnblockLock.Unlock();
            return false;
        }
        if (mConditionData.mnWaitersDone != 0) {
            _InterlockedExchangeAdd((volatile long*)&mConditionData.mnWaitersBlocked,
                                    -mConditionData.mnWaitersDone);
            mConditionData.mnWaitersDone = 0;
        }
        if (bBroadcast) {
            n = _InterlockedExchange((volatile long*)&mConditionData.mnWaitersBlocked, 0);
            mConditionData.mnWaitersToUnblock = n;
            mConditionData.mUnblockLock.Unlock();
            mConditionData.mSemaphoreBlockQueue.Post(n);
            return true;
        }
        mConditionData.mnWaitersToUnblock = 1;
        n = 1;
    }
    _InterlockedExchangeAdd((volatile long*)&mConditionData.mnWaitersBlocked, -1);
    mConditionData.mUnblockLock.Unlock();
    mConditionData.mSemaphoreBlockQueue.Post(n);
    return true;
}
}}  // namespace EA::Thread

// @ 0x00922130
EA::Thread::Mutex::~Mutex()
{
    if (mMutexData.mbIntraProcess) { DeleteCriticalSection((CRITICAL_SECTION*)this); return; }
    CloseHandle(*(HANDLE*)mMutexData.mData);
}

// @ 0x00922150
namespace EA { namespace Thread {
bool Mutex_s0092_15c0::Init(const MutexParameters* p)
{
    if (p) {
        mMutexData.mnLockCount = 0;
        unsigned char intra = p->mbIntraProcess;
        mMutexData.mbIntraProcess = intra;
        if (intra) { InitializeCriticalSection((CRITICAL_SECTION*)this); return true; }
        HANDLE h = CreateMutexA(0, 0, p->mName[0] ? p->mName : 0);
        *(HANDLE*)mMutexData.mData = h;
        return h != 0;
    }
    return false;
}
}}  // namespace EA::Thread

// @ 0x009221b0
int EA::Thread::Mutex::Lock(unsigned int const & timeout)
{
    if (!mMutexData.mbIntraProcess) {
        unsigned t = timeout;
        if (t != 0xffffffffu && t != 0) {
            unsigned now = GetThreadTime();
            t = (now < t) ? (t - now) : 0;
        }
        DWORD r = WaitForSingleObject(*(HANDLE*)mMutexData.mData, t);
        if (r == 0x102) return -2;
        if (r != 0) return -1;
    } else if (timeout == 0xffffffffu) {
        EnterCriticalSection((CRITICAL_SECTION*)this);
    } else if (!TryEnterCriticalSection((CRITICAL_SECTION*)this)) {
        for (;;) {
            unsigned now = GetThreadTime();
            if (timeout <= now) return -2;
            unsigned one = 1;
            ThreadSleep(&one);
            if (TryEnterCriticalSection((CRITICAL_SECTION*)this)) break;
        }
    }
    return ++mMutexData.mnLockCount;
}

// @ 0x00922270
int EA::Thread::Mutex::Unlock()
{
    int n = --mMutexData.mnLockCount;
    if (mMutexData.mbIntraProcess) { LeaveCriticalSection((CRITICAL_SECTION*)this); return n; }
    ReleaseMutex(*(HANDLE*)mMutexData.mData);
    return n;
}

// @ 0x009222a0
namespace EA { namespace Thread {
Mutex_s0092_15c0::Mutex_s0092_15c0(const MutexParameters* p, bool bDefault)
{
    mMutexData.mnLockCount = 0;
    mMutexData.mThreadId = 0;
    mMutexData.mbIntraProcess = true;
    memset(mMutexData.mData, 0, sizeof(mMutexData.mData));
    if (p == 0 && bDefault) {
        MutexParameters d;
        d.mbIntraProcess = 1;
        d.mName[0] = 0;
        Init(&d);
        return;
    }
    Init(p);
}
}}  // namespace EA::Thread

// @ 0x009223a0
namespace EA { namespace Thread {
int RWMutex::Lock(LockType lockType, unsigned const& timeout)
{
    Mutex_s0092_15c0* m = &mRWMutexData.mMutex;
    int r = 0;
    m->Lock(g_rwTimeout);
    if (lockType == kLockTypeRead) {
        while (mRWMutexData.mThreadIdWriter != 0) {
            ++mRWMutexData.mnReadWaiters;
            r = mRWMutexData.mReadCondition.Wait(m, timeout);
            --mRWMutexData.mnReadWaiters;
            if (r == -2) { m->Unlock(); return -2; }
        }
        r = ++mRWMutexData.mnReaders;
        m->Unlock();
        return r;
    }
    if (lockType == kLockTypeWrite) {
        while (mRWMutexData.mnReaders > 0 || mRWMutexData.mThreadIdWriter != 0) {
            ++mRWMutexData.mnWriteWaiters;
            r = mRWMutexData.mWriteCondition.Wait(m, timeout);
            --mRWMutexData.mnWriteWaiters;
            if (r == -2) { m->Unlock(); return -2; }
        }
        r = 1;
        mRWMutexData.mThreadIdWriter = GetThreadId();
    }
    m->Unlock();
    return r;
}
}}  // namespace EA::Thread

// @ 0x00922500
void FUN_00922500(void* self, void* a2, char a3)
{
    (void)self; (void)a2; (void)a3;
}
