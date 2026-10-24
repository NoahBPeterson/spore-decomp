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

// ---- items of slice s009215c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Thread {
unsigned GetThreadTime();
}
}
namespace EA {
namespace Thread {
void ThreadSleep(unsigned* pMilliseconds);
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
class Mutex_s0092_15c0 {
public:
    EAMutexData mMutexData;      // +0x00, size 0x30
    Mutex_s0092_15c0(int name, char intraProcess);
    ~Mutex_s0092_15c0();
    bool Init(char* pName);  // 0x00922150 (EA::Thread::Mutex::Init)
    int  Lock(unsigned* pTimeout);  // 0x009221b0 (EA::Thread::Mutex::Lock)
    int  Unlock();  // 0x00922270 (EA::Thread::Mutex::Unlock)
};
}
}
// ---- items of slice s009215c0 end

// @ 0x00922130
namespace EA { namespace Thread {
Mutex_s0092_15c0::~Mutex_s0092_15c0()
{
    if (mMutexData.mbIntraProcess) { DeleteCriticalSection((CRITICAL_SECTION*)this); return; }
    CloseHandle(*(HANDLE*)mMutexData.mData);
}
}}  // namespace EA::Thread

// @ 0x00922150
namespace EA { namespace Thread {
bool Mutex_s0092_15c0::Init(char* pName)
{
    if (pName) {
        mMutexData.mnLockCount = 0;
        unsigned char intra = (unsigned char)*pName;
        mMutexData.mbIntraProcess = intra;
        if (intra) { InitializeCriticalSection((CRITICAL_SECTION*)this); return true; }
        HANDLE h = CreateMutexA(0, 0, pName[1] ? (pName + 1) : 0);
        *(HANDLE*)mMutexData.mData = h;
        return h != 0;
    }
    return false;
}
}}  // namespace EA::Thread

// @ 0x009221b0
namespace EA { namespace Thread {
int Mutex_s0092_15c0::Lock(unsigned* pTimeout)
{
    if (!mMutexData.mbIntraProcess) {
        unsigned t = *pTimeout;
        if (t != 0xffffffffu && t != 0) {
            unsigned now = GetThreadTime();
            t = (now < t) ? (t - now) : 0;
        }
        DWORD r = WaitForSingleObject(*(HANDLE*)mMutexData.mData, t);
        if (r == 0x102) return -2;
        if (r != 0) return -1;
    } else if (*pTimeout == 0xffffffffu) {
        EnterCriticalSection((CRITICAL_SECTION*)this);
    } else if (!TryEnterCriticalSection((CRITICAL_SECTION*)this)) {
        for (;;) {
            unsigned now = GetThreadTime();
            if (*pTimeout <= now) return -2;
            unsigned one = 1;
            ThreadSleep(&one);
            if (TryEnterCriticalSection((CRITICAL_SECTION*)this)) break;
        }
    }
    return ++mMutexData.mnLockCount;
}
}}  // namespace EA::Thread

// @ 0x00922270
namespace EA { namespace Thread {
int Mutex_s0092_15c0::Unlock()
{
    int n = --mMutexData.mnLockCount;
    if (mMutexData.mbIntraProcess) { LeaveCriticalSection((CRITICAL_SECTION*)this); return n; }
    ReleaseMutex(*(HANDLE*)mMutexData.mData);
    return n;
}
}}  // namespace EA::Thread

// @ 0x009222a0
namespace EA { namespace Thread {
Mutex_s0092_15c0::Mutex_s0092_15c0(int name, char intraProcess)
{
    mMutexData.mnLockCount = 0;
    mMutexData.mThreadId = 0;
    mMutexData.mbIntraProcess = true;
    memset(mMutexData.mData, 0, sizeof(mMutexData.mData));
    if (name == 0 && intraProcess != 0) { char n[2]; n[0] = 1; n[1] = 0; Init(n); return; }
    Init((char*)name);
}
}}  // namespace EA::Thread

// @ 0x00922500
void FUN_00922500(void* self, void* a2, char a3)
{
    (void)self; (void)a2; (void)a3;
}
