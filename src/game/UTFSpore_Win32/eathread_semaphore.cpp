// src/game/UTFSpore_Win32/eathread_semaphore.cpp -- migrated from slice(s) s00922500 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/eathread_semaphore.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EASemaphoreData.h"
#include "EA/Thread/Semaphore.h"
#include "EAThreadDynamicData.h"
#include <intrin.h>
#include <windows.h>

// The original EA code calls the kernel32 entry points, not the compiler intrinsics.
#undef InterlockedCompareExchange
#undef InterlockedExchangeAdd
extern "C" __declspec(dllimport) LONG __stdcall InterlockedCompareExchange(volatile LONG*, LONG, LONG);
extern "C" __declspec(dllimport) LONG __stdcall InterlockedExchangeAdd(volatile LONG*, LONG);

// ---- items of slice s00922500 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
namespace EA {
namespace Thread {
struct EASemaphoreData {
    void*  mhSemaphore;     // +0x00
    int    mnCount;         // +0x04
    int    mnCancelCount;   // +0x08
    bool   mbIntraProcess;  // +0x0c

    void UpdateCancelCount(int n);   // @ 0x00922570
};
}
}
namespace EA {
namespace Thread {
struct SemaphoreData {
    int   mnCount;          // +0x00
    bool  mbIntraProcess;   // +0x04
    char  mName[0x10];      // +0x05

    SemaphoreData(int count, bool intra, const char* name); // @ 0x009225d0
};
}
}
namespace EA {
namespace Thread {
class Semaphore_s0092_2500 {
public:
    EASemaphoreData mSemaphoreData;   // +0x00

    bool Init(int* pData);      // @ 0x00922620
    uint32 Wait(uint32* pTimeout); // @ 0x00922690
    uint32 Post(int count);     // @ 0x00922740
    Semaphore_s0092_2500(int count, bool intra);            // @ 0x00922820
    Semaphore_s0092_2500(int count);                        // @ 0x00922880
    static Semaphore_s0092_2500* Create(Semaphore_s0092_2500* p);      // @ 0x009228c0
};
}
}
namespace EA {
namespace Thread {
uint32 GetThreadTime();                 // 0x0094d340
}
}
namespace EA {
namespace Thread {
void   UpdateCancelCount(EASemaphoreData* d, int n); // fwd
}
}
// ---- items of slice s00922500 end

// @ 0x00922570
void EASemaphoreData::UpdateCancelCount(int n)
{
    if (n > 0) {
        int cmp = mnCount;
        while (cmp < 0) {
            int ex = cmp + n;
            if (ex > 0)
                ex = 0;
            LONG old = InterlockedCompareExchange((volatile LONG*)&mnCount, ex, cmp);
            if (old == cmp) {
                n = n + (old - ex);
                break;
            }
            cmp = old;
            if (old >= 0)
                break;
        }
        if (n > 0)
            InterlockedExchangeAdd((volatile LONG*)&mnCancelCount, n);
    }
}

// @ 0x009225d0
EA::Thread::SemaphoreData::SemaphoreData(int count, bool intra, const char* name)
{
    mnCount = count;
    mbIntraProcess = intra;
    if (name != 0) {
        strncpy(mName, name, 0xf);
        mName[0xf] = 0;
    } else {
        mName[0] = 0;
    }
}

// @ 0x00922610
void __fastcall FUN_00922610(void** p)
{
    if ((HANDLE)*p != 0)
        CloseHandle((HANDLE)*p);
}

// @ 0x00922620
bool EA::Thread::Semaphore_s0092_2500::Init(int* pData)
{
    if (pData != 0 && mSemaphoreData.mhSemaphore == 0) {
        int count = *pData;
        mSemaphoreData.mnCount = count;
        if (count < 0)
            mSemaphoreData.mnCount = 0;
        mSemaphoreData.mbIntraProcess = *(char*)((char*)pData + 4) != 0;
        const char* name;
        int initCount;
        if (mSemaphoreData.mbIntraProcess) {
            name = 0;
            initCount = 0;
        } else {
            name = *(char*)((char*)pData + 5) ? (char*)pData + 5 : 0;
            initCount = mSemaphoreData.mnCount;
        }
        mSemaphoreData.mhSemaphore = CreateSemaphoreA(0, initCount, 0x3fffffff, name);
        return mSemaphoreData.mhSemaphore != 0;
    }
    return false;
}

// @ 0x00922690
int EA::Thread::Semaphore::Wait(unsigned int const & pTimeout)
{
    uint32 t = pTimeout;
    if (t != 0xffffffff && t != 0) {
        uint32 now = GetThreadTime();
        if (now < pTimeout)
            t = pTimeout - now;
        else
            t = 0;
    }
    if (!mSemaphoreData.mbIntraProcess) {
        DWORD r = WaitForSingleObject(mSemaphoreData.mhSemaphore, t);
        if (r != 0)
            return (r != 0x102) - 2;
        return InterlockedDecrement((LONG*)&mSemaphoreData.mnCount);
    }
    int* p = &mSemaphoreData.mnCount;
    LONG n = InterlockedDecrement((LONG*)p);
    if (n < 0) {
        DWORD r = WaitForSingleObject(mSemaphoreData.mhSemaphore, t);
        if (r != 0) {
            mSemaphoreData.UpdateCancelCount(1);
            return 0xfffffffe;
        }
    }
    uint32 v = (uint32)*p;
    return v & (((int)v < 1) - 1);
}

// @ 0x00922740
int EA::Thread::Semaphore::Post(int count)
{
    if (count > 0) {
        if (mSemaphoreData.mbIntraProcess) {
            if (mSemaphoreData.mnCancelCount > 0 && mSemaphoreData.mnCount < 0) {
                LONG old = InterlockedExchange((LONG*)&mSemaphoreData.mnCancelCount, 0);
                mSemaphoreData.UpdateCancelCount(old);
            }
            int* p = &mSemaphoreData.mnCount;
            LONG old = InterlockedExchangeAdd((LONG*)p, count);
            if (old < 0) {
                int release = -old;
                if (count < release)
                    release = count;
                ReleaseSemaphore(mSemaphoreData.mhSemaphore, release, 0);
            }
            uint32 v = (uint32)*p;
            return v & (((int)v < 1) - 1);
        }
        int* p = &mSemaphoreData.mnCount;
        InterlockedExchangeAdd((LONG*)p, count);
        BOOL ok = ReleaseSemaphore(mSemaphoreData.mhSemaphore, count, 0);
        if (ok == 0) {
            InterlockedExchangeAdd((LONG*)p, -count);
            return 0xffffffff;
        }
    }
    return (uint32)mSemaphoreData.mnCount;
}
