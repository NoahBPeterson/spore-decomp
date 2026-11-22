#include <windows.h>
#include "game/types.h"
#include "EA/Thread/Condition.h"
#include "EAConditionData.h"
#include "EAMutexData.h"
#include "EASemaphoreData.h"
#include "EA/Thread/Mutex.h"
#include "EA/Thread/Semaphore.h"
#include <stddef.h>
#include <string.h>
#include <new>

namespace EA {
namespace Thread {

extern "C" __declspec(dllimport) HANDLE __stdcall GetCurrentThread();
extern "C" __declspec(dllimport) BOOL __stdcall GetThreadPriority(HANDLE);
extern "C" __declspec(dllimport) BOOL __stdcall SetThreadPriority(HANDLE, int);
extern "C" __declspec(dllimport) DWORD __stdcall SleepEx(DWORD, BOOL);
extern "C" __declspec(dllimport) HANDLE __stdcall GetCurrentProcess();

struct ThreadGroup {
    HANDLE           mThreads[16];   // +0x00
    CRITICAL_SECTION mCS;            // +0x40
    void ClearThreads(bool bWait);              // 0x00921B40
    void AddRemoveThread(HANDLE h, char bAdd);  // 0x00921BC0
};

extern ThreadGroup g_ThreadGroup;
extern unsigned long g_ThreadTlsIndex;   // 0x0154DF38

}  // namespace Thread
}  // namespace EA

// @ 0x00921b40
namespace EA { namespace Thread {
void ThreadGroup::ClearThreads(bool bWait)
{
    EnterCriticalSection(&mCS);
    for (unsigned i = 0; i < 16; ++i) {
        HANDLE h = mThreads[i];
        if (h) {
            DWORD code = 0;
            if (!bWait) {
                if (GetExitCodeThread(h, &code) && code == 0x103) continue;
            }
            CloseHandle(mThreads[i]);
            mThreads[i] = 0;
        }
    }
    LeaveCriticalSection(&mCS);
}
}}  // namespace EA::Thread

// @ 0x00921bc0
namespace EA { namespace Thread {
void ThreadGroup::AddRemoveThread(HANDLE h, char bAdd)
{
    if (!h) return;
    EnterCriticalSection(&mCS);
    if (bAdd) {
        for (unsigned i = 0; i < 16; ++i) {
            if (mThreads[i] == 0) { mThreads[i] = h; LeaveCriticalSection(&mCS); return; }
        }
        CloseHandle(h);
        LeaveCriticalSection(&mCS);
        return;
    }
    for (unsigned i = 0; i < 16; ++i) {
        if (mThreads[i] == h) {
            CloseHandle(h);
            mThreads[i] = 0;
            break;
        }
    }
    LeaveCriticalSection(&mCS);
}
}}  // namespace EA::Thread

// @ 0x00921c50
namespace EA {
namespace Thread {
void SetCurrentThreadHandle(void * h, bool bAdd)
{
    if (g_ThreadTlsIndex == 0xfffffffful) {
        g_ThreadTlsIndex = TlsAlloc();
        if (g_ThreadTlsIndex == 0xfffffffful) return;
    }
    g_ThreadGroup.ClearThreads(false);
    if (bAdd) {
        if (h) g_ThreadGroup.AddRemoveThread(h, 1);
        else {
            HANDLE t = TlsGetValue(g_ThreadTlsIndex);
            if (t) g_ThreadGroup.AddRemoveThread(t, 0);
        }
    }
    TlsSetValue(g_ThreadTlsIndex, h);
}
}
}  // namespace EA::Thread

// @ 0x00921cc0
namespace EA {
namespace Thread {
void * GetThreadId()
{
    if (g_ThreadTlsIndex != 0xfffffffful) {
        HANDLE t = TlsGetValue(g_ThreadTlsIndex);
        if (t) return t;
    }
    HANDLE src = GetCurrentThread();
    HANDLE proc = GetCurrentProcess();
    HANDLE dup = 0;
    if (!DuplicateHandle(proc, src, proc, &dup, 0, TRUE, 2)) return dup;
    if (g_ThreadTlsIndex == 0xfffffffful) {
        g_ThreadTlsIndex = TlsAlloc();
        if (g_ThreadTlsIndex == 0xfffffffful) return dup;
    }
    g_ThreadGroup.ClearThreads(false);
    if (dup) g_ThreadGroup.AddRemoveThread(dup, 1);
    else {
        HANDLE t = TlsGetValue(g_ThreadTlsIndex);
        if (t) g_ThreadGroup.AddRemoveThread(t, 0);
    }
    TlsSetValue(g_ThreadTlsIndex, dup);
    return dup;
}
}
}  // namespace EA::Thread

// @ 0x00921d70
namespace EA { namespace Thread {
void GetCurrentThreadPriority()
{ GetThreadPriority(GetCurrentThread()); }
}}  // namespace EA::Thread

// @ 0x00921d80
namespace EA { namespace Thread {
bool SetCurrentThreadPriority(int nPriority)
{
    bool b = SetThreadPriority(GetCurrentThread(), nPriority) != 0;
    HANDLE h = GetCurrentThread();
    while (!b) {
        if (nPriority >= 0xf)  return SetThreadPriority(h, 0xf) != 0;
        if (nPriority <= -0xf) return SetThreadPriority(h, -0xf) != 0;
        b = SetThreadPriority(h, nPriority) != 0;
        ++nPriority;
    }
    return b;
}
}}  // namespace EA::Thread

// @ 0x00921df0
namespace EA {
namespace Thread {
void ThreadSleep(unsigned int const & pMilliseconds)
{ SleepEx(pMilliseconds, TRUE); }
}
}  // namespace EA::Thread
