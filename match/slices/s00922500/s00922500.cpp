// Slice s00922500 (bfs2 #22), 32-bit MSVC 2008.
// EA::Thread (Semaphore/Thread) + EA::Trace helpers. Real names/layouts from the 2008 dev PDB.
#include <intrin.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef unsigned int uint32;

// ---------------------------------------------------------------------------
// EA::Thread
// ---------------------------------------------------------------------------
namespace EA { namespace Thread {

struct EASemaphoreData {
    void*  mhSemaphore;     // +0x00
    int    mnCount;         // +0x04
    int    mnCancelCount;   // +0x08
    bool   mbIntraProcess;  // +0x0c

    void UpdateCancelCount(int n);   // @ 0x00922570
};

struct SemaphoreData {
    int   mnCount;          // +0x00
    bool  mbIntraProcess;   // +0x04
    char  mName[0x10];      // +0x05

    SemaphoreData(int count, bool intra, const char* name); // @ 0x009225d0
};

class Semaphore {
public:
    EASemaphoreData mSemaphoreData;   // +0x00

    bool Init(int* pData);      // @ 0x00922620
    uint32 Wait(uint32* pTimeout); // @ 0x00922690
    uint32 Post(int count);     // @ 0x00922740
    Semaphore(int count, bool intra);            // @ 0x00922820
    Semaphore(int count);                        // @ 0x00922880
    static Semaphore* Create(Semaphore* p);      // @ 0x009228c0
};

struct EAThreadDynamicData {
    void*    mhThread;      // +0x00
    uint32   mnThreadId;    // +0x04
    char     pad0[0x18];    // +0x08
    int      mnRefCount;    // +0x20
    char     mName[0x40];   // +0x24
};

class Thread {
public:
    EAThreadDynamicData* mpData;   // +0x00
    void SetName(const char* name);      // @ 0x00922b30
};

uint32 GetThreadTime();                 // 0x0094d340
void   ThreadSleep(uint32* ms);         // 0x00921df0
void   UpdateCancelCount(EASemaphoreData* d, int n); // fwd

void* operator_new_6abeb0(unsigned size); // 0x006abeb0
void  operator_delete_f47380(void* p);    // 0x00f47380
}}

namespace EA { namespace Trace {
void* GetTracer();               // 0x009250f0
void* GetTraceHelperTable();     // 0x009250e0
void* GetServer();
void  UpdateLogFilters();
}}

void* FUN_00922da0(void* p);     // @ 0x00922da0

// ---------------------------------------------------------------------------
// Semaphore helpers
// ---------------------------------------------------------------------------

// @ 0x00922570
void EA::Thread::EASemaphoreData::UpdateCancelCount(int n)
{
    if (n > 0) {
        int cmp = mnCount;
        while (cmp < 0) {
            int ex = cmp + n;
            if (ex > 0)
                ex = 0;
            LONG old = _InterlockedCompareExchange((volatile long*)&mnCount, ex, cmp);
            if (old == cmp) {
                n = n + (old - ex);
                break;
            }
            cmp = old;
            if (old >= 0)
                break;
        }
        if (n > 0)
            _InterlockedExchangeAdd((volatile long*)&mnCancelCount, n);
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

// @ 0x00922800
void FUN_00922800(void** p)
{
    if ((HANDLE)*p != 0)
        CloseHandle((HANDLE)*p);
}

// @ 0x00922620
bool EA::Thread::Semaphore::Init(int* pData)
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
uint32 EA::Thread::Semaphore::Wait(uint32* pTimeout)
{
    uint32 t = *pTimeout;
    if (t != 0xffffffff && t != 0) {
        uint32 now = GetThreadTime();
        if (now < *pTimeout)
            t = *pTimeout - now;
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
uint32 EA::Thread::Semaphore::Post(int count)
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

// @ 0x00922820
EA::Thread::Semaphore::Semaphore(int count, bool intra)
{
    mSemaphoreData.mhSemaphore = 0;
    mSemaphoreData.mnCount = 0;
    mSemaphoreData.mnCancelCount = 0;
    mSemaphoreData.mbIntraProcess = true;
    if (count == 0 && intra) {
        SemaphoreData local(0, true, 0);
        Init((int*)&local);
    } else {
        Init(&count);
    }
}

// @ 0x00922880
EA::Thread::Semaphore::Semaphore(int count)
{
    mSemaphoreData.mhSemaphore = 0;
    mSemaphoreData.mnCount = 0;
    mSemaphoreData.mnCancelCount = 0;
    mSemaphoreData.mbIntraProcess = true;
    SemaphoreData local(count, true, 0);
    Init((int*)&local);
}

// @ 0x009228c0
EA::Thread::Semaphore* EA::Thread::Semaphore::Create(Semaphore* p)
{
    if (p != 0) {
        p->mSemaphoreData.mhSemaphore = 0;
        p->mSemaphoreData.mnCount = 0;
        p->mSemaphoreData.mnCancelCount = 0;
        p->mSemaphoreData.mbIntraProcess = true;
        SemaphoreData local(0, true, 0);
        p->Init((int*)&local);
    }
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x00922900
void __fastcall FUN_00922900(int* p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = -1;
    *((char*)p + 0x10) = 0;
    p[5] = 0x013ec47c;
}

// ---------------------------------------------------------------------------
// @ 0x00922a80
void* __fastcall FUN_00922a80(void** p)
{
    if (*p != 0)
        return *(void**)*p;
    return 0;
}

// @ 0x00922a90
int __fastcall FUN_00922a90(void** p)
{
    if (*p != 0)
        return GetThreadPriority((HANDLE)*(void**)*p);
    return (int)0x80000000;
}

// @ 0x00922ab0
bool __fastcall FUN_00922ab0(void** p, int prio)
{
    if (*p == 0)
        return false;
    BOOL ok = SetThreadPriority((HANDLE)*(void**)*p, prio);
    bool r = ok != 0;
    if (!r) {
        while (prio < 0xf) {
            if (prio < -0xe) {
                BOOL ok2 = SetThreadPriority((HANDLE)*(void**)*p, -0xf);
                return ok2 != 0;
            }
            BOOL ok2 = SetThreadPriority((HANDLE)*(void**)*p, prio);
            prio++;
            if (ok2 != 0)
                return true;
        }
        BOOL ok3 = SetThreadPriority((HANDLE)*(void**)*p, 0xf);
        r = ok3 != 0;
    }
    return r;
}

// @ 0x00922b30
void EA::Thread::Thread::SetName(const char* name)
{
    if (mpData != 0 && name != 0) {
        strncpy(mpData->mName, name, 0x40);
        mpData->mName[0x3f] = 0;
        if (mpData->mhThread != 0) {
            struct { DWORD a; const char* b; uint32 c; DWORD d; } info;
            info.a = 0x1000;
            info.b = mpData->mName;
            info.c = mpData->mnThreadId;
            info.d = 0;
            RaiseException(0x406d1388, 0, 4, (ULONG_PTR*)&info);
        }
    }
}

// @ 0x00922bd0
void* FUN_00922bd0()
{
    void** p = (void**)EA::Thread::operator_new_6abeb0(4);
    if (p != 0) {
        *p = 0;
        return p;
    }
    return 0;
}

// @ 0x00922c00
void* FUN_00922c00(void** p)
{
    if (p != 0) {
        *p = 0;
        return p;
    }
    return 0;
}

// @ 0x00922c20
struct C22c20 { void* p; void Copy(void** src); };
void C22c20::Copy(void** src)
{
    void* q = *src;
    p = q;
    _InterlockedExchangeAdd((volatile long*)((char*)q + 0x20), 1);
}

// @ 0x00922c40
void FUN_00922c40(void** p, int proc)
{
    if (*p != 0) {
        if ((_InterlockedCompareExchange((volatile long*)0x0166892c, 1, 0)) != 0) { }
        if (_InterlockedExchangeAdd((volatile long*)0x01668928, 0) == 0) {
            SYSTEM_INFO si;
            GetSystemInfo(&si);
            _InterlockedExchange((volatile long*)0x01668928, si.dwNumberOfProcessors);
        }
        if (proc < 0) {
            SetThreadIdealProcessor((HANDLE)*p, 0x20);
            return;
        }
        int n = _InterlockedExchangeAdd((volatile long*)0x01668928, 0);
        if (n <= proc)
            proc = proc % n;
        SetThreadIdealProcessor((HANDLE)*p, proc);
    }
}

// @ 0x00922d10
void __fastcall FUN_00922d10(void*** p)
{
    void* d = *p;
    if (d != 0 && *(void**)d != 0)
        QueueUserAPC((PAPCFUNC)0x010829f0, (HANDLE)*(void**)d, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00922da0
void* FUN_00922da0(void* p)
{
    if ((unsigned)p >= 0x01667c18u && (unsigned)p < 0x01668898u) {
        unsigned idx = ((unsigned)p - 0x01667c18u) / 100u;
        ((long*)0x016688a8)[idx] = 0;
        if (*(HANDLE*)p != 0)
            CloseHandle(*(HANDLE*)p);
        return p;
    }
    if (p != 0) {
        if (*(HANDLE*)p != 0)
            CloseHandle(*(HANDLE*)p);
        EA::Thread::operator_delete_f47380(p);
    }
    return p;
}

// @ 0x00922e10
void __fastcall FUN_00922e10(void** p)
{
    void* d = *p;
    if (d != 0 && _InterlockedExchangeAdd((volatile long*)((char*)d + 0x20), -1) == 1)
        FUN_00922da0(d);
}

// @ 0x00923310
void FUN_00923310(void** p)
{
    if (*p != 0 && _InterlockedExchangeAdd((volatile long*)((char*)*p + 0x20), -1) == 1)
        FUN_00922da0(*p);
}

// @ 0x00923330
void FUN_00923330(void** p)
{
    if (p != 0) {
        void* d = *p;
        if (d != 0 && _InterlockedExchangeAdd((volatile long*)((char*)d + 0x20), -1) == 1)
            FUN_00922da0(d);
        EA::Thread::operator_delete_f47380(p);
    }
}

// @ 0x009233e0
struct C233e0 { char pad[0x21c]; unsigned short v; void Set(unsigned short); };
void C233e0::Set(unsigned short x)
{
    v = x;
}

// @ 0x009233f0
struct C233f0 { void** vtbl; void Call(void* arg); };
void C233f0::Call(void* arg)
{
    void* v = *(void**)((char*)arg + 0xc);
    (*(void(__thiscall**)(void*, void*))((char*)vtbl + 0x14))(this, v);
}

// @ 0x00923440
int __fastcall FUN_00923440(void* self)
{
    int n = *(int*)((char*)self + 4);
    if (n > 1) {
        *(int*)((char*)self + 4) = n - 1;
        return n - 1;
    }
    (*(void(__thiscall**)(void*, int))((char*)*(void**)self + 8))(self, 1);
    return 0;
}

// @ 0x009234a0
int __fastcall FUN_009234a0(void* self)
{
    int n = *(int*)((char*)self + 0x10);
    if (n > 1) {
        *(int*)((char*)self + 0x10) = n - 1;
        return n - 1;
    }
    (*(void(__thiscall**)(void*, int))((char*)*(void**)self + 8))(self, 1);
    return 0;
}

// @ 0x009234c0
void* EA::Trace::GetServer()
{
    void* p = EA::Trace::GetTracer();
    if (p != 0)
        return (*(void*(__thiscall**)(void*, int))((char*)*(void**)p + 0xc))(p, 0x23ab34a1);
    return 0;
}

// @ 0x009234e0
void EA::Trace::UpdateLogFilters()
{
    void* p = EA::Trace::GetTraceHelperTable();
    (*(void(__thiscall**)(void*))((char*)*(void**)p + 0x14))(p);
}

// ===========================================================================
// Large functions: behaviourally-shaped skeletons (marked partial).
// ===========================================================================

// @ 0x00922500
void FUN_00922500(void* self, void* a2, char a3)
{
    (void)self; (void)a2; (void)a3;
}

// @ 0x00922940
int FUN_00922940(void* self, void* a2, void* a3)
{
    (void)self; (void)a2; (void)a3;
    return 0;
}

// @ 0x00922a10
int FUN_00922a10(void* self, void* a2)
{
    (void)self; (void)a2;
    return 0;
}

// @ 0x00922d30
void* FUN_00922d30()
{
    return 0;
}

// @ 0x00922e30
void FUN_00922e30(void* self)
{
    (void)self;
}

// @ 0x00922f30
void FUN_00922f30(void* self)
{
    (void)self;
}

// @ 0x009230a0
void FUN_009230a0(void* self)
{
    (void)self;
}

// @ 0x009231a0
void FUN_009231a0(void* self)
{
    (void)self;
}
