// Slice s00922500 (bfs2 #22), 32-bit MSVC 2008.
// EA::Thread (Semaphore/Thread) + EA::Trace helpers. Real names/layouts from the 2008 dev PDB.
#include <intrin.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// The original EA code calls the kernel32 entry points, not the compiler intrinsics.
#undef InterlockedCompareExchange
#undef InterlockedExchangeAdd
extern "C" __declspec(dllimport) LONG __stdcall InterlockedCompareExchange(volatile LONG*, LONG, LONG);
extern "C" __declspec(dllimport) LONG __stdcall InterlockedExchangeAdd(volatile LONG*, LONG);

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

    void UpdateCancelCount(int n);   // 0x00922570
};

struct SemaphoreData {
    int   mnCount;          // +0x00
    bool  mbIntraProcess;   // +0x04
    char  mName[0x10];      // +0x05

    SemaphoreData(int count, bool intra, const char* name); // 0x009225d0
};

class Semaphore {
public:
    EASemaphoreData mSemaphoreData;   // +0x00

    bool Init(int* pData);      // 0x00922620
    uint32 Wait(const uint32& timeout); // 0x00922690
    uint32 Post(int count);     // 0x00922740
    Semaphore(int count, bool intra);            // 0x00922820
    Semaphore(int count);                        // 0x00922880
    static Semaphore* Create(Semaphore* p);      // 0x009228c0
};

struct EAThreadDynamicData {
    void*    mhThread;             // +0x00
    uint32   mnThreadId;           // +0x04
    int      mnStatus;             // +0x08  (0=idle, 1=running, 2=ended)
    int      mnReturnValue;        // +0x0c
    void*    mpStartContext0;      // +0x10  thread function pointer
    void*    mpStartContext1;      // +0x14  thread function argument
    void*    mpStartContext2;      // +0x18  thread handle (SetCurrentThreadHandle arg)
    void*    mpBeginThreadUserWrapper; // +0x1c  optional user wrapper callback
    volatile long mnRefCount;      // +0x20
    char     mName[0x40];          // +0x24

    void Release();                                       // 0x00922e10 (conditional)
    static EAThreadDynamicData* Alloc();                  // 0x00922d30
};

struct ThreadParameters {                                 // passed by pointer to Start
    int   mnStackSize;      // +0x00
    uint32 mnStackSize2;    // +0x04  (stack size passed to _beginthreadex)
    int   mnPriority;       // +0x08
    int   mnProcessor;      // +0x0c
    void* mpFunction;       // +0x10
    const char* mpName;     // +0x14
};

class Mutex {                                   // size 0x30
public:
    Mutex(const void* params, bool b);          // 0x009222a0
    unsigned int mData[0x0c];
};

class Event {                                   // size 0x60
public:
    Event(const void* params, bool b);          // 0x00921f00
    unsigned int mData[0x18];
};

struct SuspendedParams {                        // 2-byte default parameter block
    bool mbStartSuspended;                      // +0x00
    bool mbPad;                                 // +0x01
};

class Thread {
public:
    enum Status { kStatusNone = 0, kStatusRunning = 1, kStatusComplete = 2 };

    EAThreadDynamicData* mpData;   // +0x00
    void*    mpContext[3];         // +0x04
    Mutex    mRunMutex;            // +0x10
    Event    mRunEvent;            // +0x40
    Event    mExitEvent;           // +0xa0

    Thread(const void* params, bool bStartSuspended);   // 0x00922500
    void SetParameters(const void* params);            // 0x00922330
    void SetName(const char* name);      // 0x00922b30
    bool SetPriority(int prio);          // 0x00922ab0
    void SetIdealProcessor(int proc);    // 0x00922c40
    Status WaitForEnd(const uint32& timeout, int* pValue);        // 0x00922940
    Status GetStatus(int* pValue) const;                          // 0x00922a10
    void* Start(void* fn, void* arg, const ThreadParameters* params, void* wrapper);      // 0x00922f30
    void* Start2(void* fn, void* arg, const ThreadParameters* params, void* wrapper);     // 0x009231a0
};

void SetCurrentThreadHandle(void* h, bool b);             // 0x00921c50
unsigned __stdcall EAThreadEntryPlain(void* p);           // 0x00922e30
unsigned __stdcall EAThreadEntryWrapped(void* p);         // 0x009230a0

extern long g_ThreadDataLocks[32];                        // 0x016688a8
extern char g_ThreadDataPool[];                           // 0x01667c18
extern long g_ThreadCount;                                // 0x016688a0
extern long g_DefaultProcessor;                           // 0x0154df60
extern long g_ProcessorCount;                             // 0x01668928
extern long g_ProcessorCountInit;                         // 0x0166892c

uint32 GetThreadTime();                 // 0x0094d340
void   ThreadSleep(uint32* ms);         // 0x00921df0
void   UpdateCancelCount(EASemaphoreData* d, int n); // fwd

void* operator_new_6abeb0(unsigned size); // 0x006abeb0
void  operator_delete_f47380(void* p);    // 0x00f47380
}}

extern "C" unsigned long __cdecl _beginthreadex(void* lpSecurity, unsigned cbStack,
        unsigned (__stdcall* pfnStart)(void*), void* pArg, unsigned nFlags, unsigned* pThreadId);

namespace EA { namespace Trace {
void* GetTracer();               // 0x009250f0
void* GetTraceHelperTable();     // 0x009250e0
void* GetServer();
void  UpdateLogFilters();
}}

void FUN_00922da0(void* p);      // 0x00922da0

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
uint32 EA::Thread::Semaphore::Wait(const uint32& timeout)
{
    uint32 t = timeout;
    if (t != 0xffffffff && t != 0) {
        uint32 now = GetThreadTime();
        if (now < timeout)
            t = timeout - now;
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
        struct LocalData {
            int  mnCount;
            bool mbIntraProcess;
            char mName[0x10];
        } local;
        local.mnCount = 0;
        local.mbIntraProcess = true;
        local.mName[0] = 0;
        Init((int*)&local);
    } else {
        Init((int*)count);
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
    __asm { mov eax, p }
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
bool EA::Thread::Thread::SetPriority(int prio)
{
    if (mpData == 0)
        return false;
    HANDLE h = (HANDLE)mpData->mhThread;
    if (!SetThreadPriority(h, prio)) {
        while (prio < 0xf) {
            if (prio <= -0xf)
                return SetThreadPriority(h, -0xf) != 0;
            if (SetThreadPriority(h, prio))
                return true;
            ++prio;
        }
        return SetThreadPriority(h, 0xf) != 0;
    }
    return true;
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
    C22c20* self = this;
    __asm { mov eax, self }
}

// @ 0x00922c40
void EA::Thread::Thread::SetIdealProcessor(int proc)
{
    if (mpData == 0)
        return;
    if ((g_ProcessorCountInit & 1) == 0) {
        g_ProcessorCountInit |= 1;
        _InterlockedExchange((volatile long*)&g_ProcessorCount, 0);
    }
    if (_InterlockedExchangeAdd((volatile long*)&g_ProcessorCount, 0) == 0) {
        SYSTEM_INFO si;
        si.dwOemId = 0;
        si.dwPageSize = 0;
        si.lpMinimumApplicationAddress = 0;
        si.lpMaximumApplicationAddress = 0;
        si.dwActiveProcessorMask = 0;
        si.dwNumberOfProcessors = 0;
        si.dwProcessorType = 0;
        si.dwAllocationGranularity = 0;
        si.wProcessorLevel = 0;
        si.wProcessorRevision = 0;
        GetSystemInfo(&si);
        _InterlockedExchange((volatile long*)&g_ProcessorCount, si.dwNumberOfProcessors);
    }
    if (proc < 0) {
        SetThreadIdealProcessor((HANDLE)mpData->mhThread, 0x20);
        return;
    }
    if (proc >= _InterlockedExchangeAdd((volatile long*)&g_ProcessorCount, 0))
        proc = proc % _InterlockedExchangeAdd((volatile long*)&g_ProcessorCount, 0);
    SetThreadIdealProcessor((HANDLE)mpData->mhThread, proc);
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
void FUN_00922da0(void* p)
{
    if ((unsigned)p >= 0x01667c18u && (unsigned)p < 0x01668898u) {
        unsigned idx = ((unsigned)p - 0x01667c18u) / 100u;
        ((long*)0x016688a8)[idx] = 0;
        if (*(HANDLE*)p != 0)
            CloseHandle(*(HANDLE*)p);
        return;
    }
    if (p != 0) {
        if (*(HANDLE*)p != 0)
            CloseHandle(*(HANDLE*)p);
        EA::Thread::operator_delete_f47380(p);
    }
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
    void* d = *p;
    if (d != 0) {
        if (_InterlockedExchangeAdd((volatile long*)((char*)d + 0x20), -1) == 1) {
            FUN_00922da0(d);
            return;
        }
    }
    __asm { mov eax, d }
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
// Thread lifetime: ctor, wait/status, dynamic-data allocator, start.
// ===========================================================================

// @ 0x00922500
EA::Thread::Thread::Thread(const void* params, bool bStartSuspended)
    : mRunMutex(0, true), mRunEvent(0, true), mExitEvent(0, true)
{
    mpData = 0;
    mpContext[0] = 0;
    mpContext[1] = 0;
    mpContext[2] = 0;
    SuspendedParams sp;
    if (params == 0 && bStartSuspended) {
        sp.mbStartSuspended = true;
        sp.mbPad = false;
        params = &sp;
    }
    SetParameters(params);
}

// @ 0x00922940
EA::Thread::Thread::Status EA::Thread::Thread::WaitForEnd(const uint32& timeout, int* pValue)
{
    int* pOut = pValue;
    while (mpData == 0) {
        while ((mpData == 0 || mpData->mhThread == 0) && GetThreadTime() < timeout) {
            uint32 ms = 1;
            ThreadSleep(&ms);
        }
        if (mpData == 0)
            return kStatusNone;
        pOut = 0;
        if (mpData == 0)
            continue;
    }
    if (mpData->mhThread != 0) {
        uint32 t = timeout;
        if (t != 0xffffffff && t != 0) {
            uint32 now = GetThreadTime();
            t = (now < timeout) ? timeout - now : 0;
        }
        DWORD r = WaitForSingleObject((HANDLE)mpData->mhThread, t);
        if (r == 0x102)
            return kStatusRunning;
        CloseHandle((HANDLE)mpData->mhThread);
        mpData->mhThread = 0;
        mpData->mnStatus = kStatusComplete;
    }
    if (pOut != 0)
        *pOut = mpData->mnReturnValue;
    return kStatusComplete;
}

// @ 0x00922a10
EA::Thread::Thread::Status EA::Thread::Thread::GetStatus(int* pValue) const
{
    if (mpData == 0)
        return kStatusNone;
    if (mpData->mhThread != 0) {
        DWORD code;
        if (GetExitCodeThread((HANDLE)mpData->mhThread, &code) != 0) {
            if (code == 0x103)
                return kStatusRunning;
            CloseHandle((HANDLE)mpData->mhThread);
            mpData->mhThread = 0;
        }
    }
    if (pValue != 0)
        *pValue = mpData->mnReturnValue;
    mpData->mnStatus = kStatusComplete;
    return kStatusComplete;
}

// @ 0x00922d30
EA::Thread::EAThreadDynamicData* EA::Thread::EAThreadDynamicData::Alloc()
{
    unsigned i = 0;
    for (; i < 0x20; i++) {
        if (_InterlockedCompareExchange(&g_ThreadDataLocks[i], 1, 0) == 0)
            break;
    }
    if (i < 0x20) {
        EAThreadDynamicData* p = (EAThreadDynamicData*)(g_ThreadDataPool + i * 100);
        p->mhThread = 0;
        p->mnThreadId = 0;
        p->mnStatus = 0;
        p->mnReturnValue = 0;
        p->mpBeginThreadUserWrapper = 0;
        _InterlockedExchange(&p->mnRefCount, 0);
        return p;
    }
    EAThreadDynamicData* p = (EAThreadDynamicData*)operator_new_6abeb0(0x64);
    if (p == 0)
        return 0;
    p->mhThread = 0;
    p->mnThreadId = 0;
    p->mnStatus = 0;
    p->mnReturnValue = 0;
    p->mpBeginThreadUserWrapper = 0;
    _InterlockedExchange(&p->mnRefCount, 0);
    return p;
}

// @ 0x00922e30
unsigned __stdcall EA::Thread::EAThreadEntryPlain(void* arg)
{
    EAThreadDynamicData* p = (EAThreadDynamicData*)arg;
    void* pfn = p->mpStartContext0;
    void* pctx = p->mpStartContext1;
    SetCurrentThreadHandle(p->mpStartContext2, false);
    p->mnStatus = 1;
    if (p->mName[0] != 0) {
        struct { DWORD a; const char* b; uint32 c; DWORD d; } info;
        info.a = 0x1000;
        info.b = p->mName;
        info.c = p->mnThreadId;
        info.d = 0;
        __try {
            RaiseException(0x406d1388, 0, 4, (ULONG_PTR*)&info);
        } __except (1) {
        }
    }
    unsigned r;
    if (p->mpBeginThreadUserWrapper != 0)
        r = ((unsigned (__cdecl*)(void*, void*))p->mpBeginThreadUserWrapper)(pfn, pctx);
    else
        r = ((unsigned (__stdcall*)(void*))pfn)(pctx);
    p->mnReturnValue = r;
    SetCurrentThreadHandle(0, false);
    p->mnStatus = 2;
    if (_InterlockedExchangeAdd(&p->mnRefCount, -1) == 1)
        FUN_00922da0(p);
    return r;
}

// @ 0x00922f30
void* EA::Thread::Thread::Start(void* fn, void* arg, const ThreadParameters* params, void* wrapper)
{
    if (mpData != 0 && _InterlockedExchangeAdd(&mpData->mnRefCount, -1) == 1)
        FUN_00922da0(mpData);
    EAThreadDynamicData* p = EAThreadDynamicData::Alloc();
    mpData = p;
    _InterlockedExchangeAdd(&p->mnRefCount, 1);
    _InterlockedExchangeAdd(&mpData->mnRefCount, 1);
    p->mhThread = 0;
    p->mpStartContext0 = fn;
    p->mpStartContext1 = arg;
    p->mpBeginThreadUserWrapper = wrapper;
    unsigned stackSize = (params != 0) ? params->mnStackSize2 : 0;
    mpData->mhThread = (void*)_beginthreadex(0, stackSize, EAThreadEntryPlain, mpData, 4,
                                            (unsigned*)&mpData->mnThreadId);
    if (mpData->mhThread == 0) {
        if (_InterlockedExchangeAdd(&mpData->mnRefCount, -1) == 1)
            FUN_00922da0(mpData);
        if (_InterlockedExchangeAdd(&mpData->mnRefCount, -1) == 1)
            FUN_00922da0(mpData);
        mpData = 0;
        return 0;
    }
    if (params != 0)
        SetName(params->mpName);
    mpData->mpStartContext2 = mpData->mhThread;
    if (params != 0) {
        if (params->mnPriority != 0)
            SetPriority(params->mnPriority);
        int proc = params->mnProcessor;
        if (proc >= 0) {
            if (proc == _InterlockedExchangeAdd(&g_ThreadCount, 0))
                _InterlockedExchangeAdd(&g_ThreadCount, 1);
            SetIdealProcessor(proc);
            ResumeThread((HANDLE)mpData->mhThread);
            return mpData->mhThread;
        }
    }
    int proc2 = g_DefaultProcessor;
    if (g_DefaultProcessor < 0)
        proc2 = _InterlockedExchangeAdd(&g_ThreadCount, 1) + 1;
    SetIdealProcessor(proc2);
    ResumeThread((HANDLE)mpData->mhThread);
    return mpData->mhThread;
}

// @ 0x009230a0
unsigned __stdcall EA::Thread::EAThreadEntryWrapped(void* arg)
{
    EAThreadDynamicData* p = (EAThreadDynamicData*)arg;
    void* pfn = p->mpStartContext0;
    void* pctx = p->mpStartContext1;
    SetCurrentThreadHandle(p->mpStartContext2, false);
    p->mnStatus = 1;
    if (p->mName[0] != 0 && p->mhThread != 0) {
        struct { DWORD a; const char* b; uint32 c; DWORD d; } info;
        info.a = 0x1000;
        info.b = p->mName;
        info.c = p->mnThreadId;
        info.d = 0;
        __try {
            RaiseException(0x406d1388, 0, 4, (ULONG_PTR*)&info);
        } __except (1) {
        }
    }
    unsigned r;
    if (p->mpBeginThreadUserWrapper != 0)
        r = ((unsigned (__cdecl*)(void*, void*))p->mpBeginThreadUserWrapper)(pfn, pctx);
    else
        r = (*(unsigned (__thiscall**)(void*, void*))((char*)*(void**)pfn + 4))(pfn, pctx);
    p->mnReturnValue = r;
    SetCurrentThreadHandle(0, false);
    p->mnStatus = 2;
    if (_InterlockedExchangeAdd(&p->mnRefCount, -1) == 1)
        FUN_00922da0(p);
    return r;
}

// @ 0x009231a0
void* EA::Thread::Thread::Start2(void* fn, void* arg, const ThreadParameters* params, void* wrapper)
{
    if (mpData != 0 && _InterlockedExchangeAdd(&mpData->mnRefCount, -1) == 1)
        FUN_00922da0(mpData);
    EAThreadDynamicData* p = EAThreadDynamicData::Alloc();
    mpData = p;
    _InterlockedExchangeAdd(&p->mnRefCount, 1);
    _InterlockedExchangeAdd(&mpData->mnRefCount, 1);
    p->mhThread = 0;
    p->mpStartContext0 = fn;
    p->mpStartContext1 = arg;
    p->mpBeginThreadUserWrapper = wrapper;
    unsigned stackSize = (params != 0) ? params->mnStackSize2 : 0;
    mpData->mhThread = (void*)_beginthreadex(0, stackSize, EAThreadEntryWrapped, mpData, 4,
                                            (unsigned*)&mpData->mnThreadId);
    if (mpData->mhThread == 0) {
        if (_InterlockedExchangeAdd(&mpData->mnRefCount, -1) == 1)
            FUN_00922da0(mpData);
        if (_InterlockedExchangeAdd(&mpData->mnRefCount, -1) == 1)
            FUN_00922da0(mpData);
        mpData = 0;
        return 0;
    }
    if (params != 0)
        SetName(params->mpName);
    mpData->mpStartContext2 = mpData->mhThread;
    if (params != 0) {
        if (params->mnPriority != 0)
            SetPriority(params->mnPriority);
        int proc = params->mnProcessor;
        if (proc >= 0) {
            if (proc == _InterlockedExchangeAdd(&g_ThreadCount, 0))
                _InterlockedExchangeAdd(&g_ThreadCount, 1);
            SetIdealProcessor(proc);
            ResumeThread((HANDLE)mpData->mhThread);
            return mpData->mhThread;
        }
    }
    int proc2 = g_DefaultProcessor;
    if (g_DefaultProcessor < 0)
        proc2 = _InterlockedExchangeAdd(&g_ThreadCount, 1) + 1;
    SetIdealProcessor(proc2);
    ResumeThread((HANDLE)mpData->mhThread);
    return mpData->mhThread;
}
