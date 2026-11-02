// src/game/UTFSpore_Win32/eathread_condition.cpp -- migrated from slice(s) s009215c0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/eathread_condition.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Thread/Condition.h"
#include "EAConditionData.h"
#include "EAMutexData.h"
#include "EASemaphoreData.h"
#include "EA/Thread/Mutex.h"
#include "EA/Thread/Semaphore.h"

// ---- items of slice s009215c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Thread {
extern "C" long _InterlockedIncrement(volatile long*);
}
}
namespace EA {
namespace Thread {
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
}
}
namespace EA {
namespace Thread {
extern unsigned g_mutexTimeout;   // 0x0143dc58
}
}
// ---- items of slice s009215c0 end

// @ 0x00921f80
EA::Thread::Condition::Result EA::Thread::Condition::Wait(EA::Thread::Mutex * pMutex, unsigned int const & timeout)
{
    _InterlockedIncrement((volatile long*)&mConditionData.mnWaitersBlocked.mValue);
    int r = pMutex->Unlock();
    if (r < 0) return (EA::Thread::Condition::Result)(r);
    r = mConditionData.mSemaphoreBlockQueue.Wait(timeout);
    mConditionData.mUnblockLock.Lock(g_mutexTimeout);
    int n = mConditionData.mnWaitersToUnblock;
    if (n != 0) {
        mConditionData.mnWaitersToUnblock = n - 1;
    } else {
        ++mConditionData.mnWaitersDone;
        if (mConditionData.mnWaitersDone == 0x3fffffff) {
            mConditionData.mSemaphoreBlockLock.Wait(g_mutexTimeout);
            _InterlockedExchangeAdd((volatile long*)&mConditionData.mnWaitersBlocked.mValue,
                                    -mConditionData.mnWaitersDone);
            mConditionData.mSemaphoreBlockLock.Post(1);
            mConditionData.mnWaitersDone = 0;
        }
    }
    mConditionData.mUnblockLock.Unlock();
    if (n == 1) mConditionData.mSemaphoreBlockLock.Post(1);
    if (pMutex->Lock(g_mutexTimeout) == -1) return (EA::Thread::Condition::Result)(-1);
    return (EA::Thread::Condition::Result)(r);
}
