// Slice s011ebf70 -- RenderWare core threading (rw::core::thread) scheduler and
// file-system helpers, plus the neighbouring Mutex / RwwString helpers.
//
// The 10 targets of this slice are the scheduler / filesystem entry points; the
// Mutex::{Destroy,Init,Lock,Unlock}, RwwString::set and the small trivial
// wrappers are the neighbouring functions recorded alongside them.
#include "types.h"
#include <intrin.h>

#define EXCEPTION_EXECUTE_HANDLER 1

void FUN_011eca90(int*);

extern "C" {
__declspec(dllimport) void* __stdcall FindFirstFileA(const char*, void*);
__declspec(dllimport) void  __stdcall DeleteCriticalSection(void*);
__declspec(dllimport) int   __stdcall CloseHandle(void*);
__declspec(dllimport) void  __stdcall InitializeCriticalSection(void*);
__declspec(dllimport) void* __stdcall CreateMutexA(void*, int, const char*);
__declspec(dllimport) void  __stdcall EnterCriticalSection(void*);
__declspec(dllimport) int   __stdcall TryEnterCriticalSection(void*);
__declspec(dllimport) void  __stdcall LeaveCriticalSection(void*);
__declspec(dllimport) int   __stdcall ReleaseMutex(void*);
__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void*, unsigned long);
__declspec(dllimport) unsigned long __stdcall SleepEx(unsigned long, int);
__declspec(dllimport) void  __stdcall Sleep(unsigned long);
__declspec(dllimport) char* __cdecl strncpy(char*, const char*, unsigned int);
__declspec(dllimport) int   __stdcall GetExitCodeThread(void*, unsigned long*);
__declspec(dllimport) unsigned long __stdcall TlsAlloc(void);
__declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
__declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
__declspec(dllimport) int   __stdcall SetThreadPriority(void*, int);
__declspec(dllimport) unsigned int __stdcall SetThreadIdealProcessor(void*, unsigned int);
__declspec(dllimport) void  __stdcall GetSystemInfo(void*);
__declspec(dllimport) void  __stdcall RaiseException(unsigned long, unsigned long, unsigned long, const unsigned long*);
__declspec(dllimport) unsigned long __stdcall ResumeThread(void*);

// SYSTEM_INFO: only the processor count (the low word) is read here.
struct SYSTEM_INFO
{
    unsigned int  dwOemId;            // +0x00 (union with dwProcessorArchitecture)
    unsigned int  dwPageSize;         // +0x04
    void*         lpMinimumApplicationAddress;  // +0x08
    void*         lpMaximumApplicationAddress;  // +0x0c
    unsigned int  dwActiveProcessorMask;        // +0x10
    unsigned int  dwNumberOfProcessors;         // +0x14
    unsigned int  dwProcessorType;              // +0x18
    unsigned int  dwAllocationGranularity;      // +0x1c
    unsigned short wProcessorLevel;             // +0x20
    unsigned short wProcessorRevision;          // +0x22
};
}

// out-of-slice helpers.
void* FUN_011e6d20(unsigned int);                    // 0x011e6d20  operator new
void  FUN_011eba20(char* dst, const char* src, int n);   // 0x011eba20  stdc::StringnCopy
unsigned int GetThreadTime();                        // 0x011ec7f0
void FUN_011ed3f0(void*);                            // stream/list teardown
void* f_011eca10(unsigned int);                      // 0x011eca10  rw::core::thread local allocator
void  f_011ec820();                                  // 0x011ec820  thread-name slot accessor
void  f_011ec750(void* handle, char add);            // 0x011ec750  TLS thread hook
void  operator_del(void*);                           // 0x00f47380
int   sprintf(char* dst, const char* fmt, ...);      // 0x011ea770  stream-path formatter
void* __stdcall _beginthreadex(void*, unsigned int, unsigned int (__stdcall*)(void*),
                               void*, unsigned int, unsigned int*);   // 0x013cc3d4

// The package state singleton and the per-slot stream records.
struct ThreadObj;
struct StreamFile;
struct StreamHandle;
struct PackageStreamEntry
{
    void*        mName;   // +0x00
    StreamFile*  mFile;   // +0x04
};
struct PackageState
{
    int                  mField00;   // +0x00
    int                  mField04;   // +0x04
    int                  mField08;   // +0x08
    int                  mField0C;   // +0x0c
    StreamFile*          mFile;      // +0x10
    int                  mField14;   // +0x14
    int                  mField18;   // +0x18
    unsigned int         mCount;     // +0x1c
    PackageStreamEntry*  mEntries;   // +0x20
};
PackageState* GetPackageState();                     // 0x011e58f0
extern ThreadObj g_016f4e18;                         // 0x016f4e18
extern unsigned long g_015d0690;                     // 0x015d0690
extern unsigned int g_014f70f8;                      // 0x014f70f8
extern long g_016f5bc0;                              // 0x016f5bc0  processor count / affinity mask
extern int  g_016f5bc4;                              // 0x016f5bc4  mask initialised flag
extern int  g_016f5b38;                              // 0x016f5b38  processor round-robin counter
extern int  g_015d0694;                              // 0x015d0694  requested processor

// The descriptor of the thread being started (system THREADNAME_INFO layout).
struct THREADNAME_INFO
{
    unsigned long dwType;      // +0x00
    const char*   szName;      // +0x04
    unsigned long dwThreadID;  // +0x08
    unsigned long dwFlags;     // +0x0c
};

// ----- object layouts -------------------------------------------------------

// A fixed-capacity name: an int tag, a char flag and 0xf characters + terminator.
struct StreamName
{
    int  mIndex;          // +0
    char mFlag;           // +4
    char mBuf[0x10];      // +5  (strncpy 0xf, terminator at +0x14)

    __declspec(noinline) StreamName* set(int index, char flag, const char* src);   // 0x011ed3b0
};

// A fixed-capacity name owned by a Mutex / RwwString.
struct RwwString
{
    char m_flag;          // +0
    char m_buf[0x10];     // +1

    __declspec(noinline) RwwString* set(char flag, const char* src);   // 0x011ec0b0
};

struct Mutex
{
    void* mData0;             // +0
    int   mField04;           // +4
    int   mField08;           // +8
    int   mField0C;           // +0xc
    int   mField10;           // +0x10
    int   mField14;           // +0x14
    int   mField18;           // +0x18
    int   mField1C;           // +0x1c
    int   mnLockCount;        // +0x20
    char  mbIntraProcess;     // +0x24
    char  pad25[3];
    int   mField28;           // +0x28

    __declspec(noinline) void Destroy();            // 0x011ec0f0
    __declspec(noinline) bool Init(const char* name);   // 0x011ec110
    __declspec(noinline) int  Lock(unsigned int* timeout);   // 0x011ec170
    __declspec(noinline) int  Unlock();             // 0x011ec230
    __declspec(noinline) Mutex* ctor0(int a, char b);   // 0x011ec260
};

// A counting semaphore.  Init/Wait/Post/ctor0 live out of slice.
struct Semaphore
{
    int  mHandle;         // +0
    int  mCount;          // +4
    int  mWaiters;        // +8
    char mIntra;          // +0xc

    __declspec(noinline) char Init(const void* name);   // 0x011ed400
    __declspec(noinline) int  Wait(unsigned int* timeout);   // 0x011ed470
    __declspec(noinline) int  Post(int count);      // 0x011ed520
    __declspec(noinline) Semaphore* ctor0(int a, char b);   // 0x011ed5d0
};

struct StreamList { void teardown(); };

// A spawned thread's control block (returned by the allocator, owned by ThreadObj::mRecord).
struct ThreadRecord
{
    void*        mHandle;       // +0x00  OS thread handle
    unsigned int mThreadId;     // +0x04
    int          mState;        // +0x08  0 = new, 1 = starting, 2 = start routine done
    int          mResult;       // +0x0c
    int          mContext;      // +0x10
    int          mArg;          // +0x14
    void*        mOwnerHandle;  // +0x18  handle given to the thread-local hook
    int          mStart;        // +0x1c  start routine (0 = call the context directly)
    long         mRefCount;     // +0x20
    char         mName[0x40];   // +0x24  name buffer (terminator at +0x63)
};

// The descriptor a caller passes to ThreadObj::createThread.
struct ThreadDesc
{
    int         mField00;     // +0x00
    int         mStackSize;   // +0x04
    int         mPriority;    // +0x08
    int         mProcessor;   // +0x0c
    int         mField10;     // +0x10
    const char* mName;        // +0x14
};

// A streamed package file record: the owner object (with its vtable) lives at +0x120.
struct StreamFile
{
    int   mField00;              // +0x00
    char  mOpened;               // +0x04
    char  pad05[0x120 - 0x05];   // +0x05 .. +0x11f
    void* mOwner;                // +0x120

    __declspec(noinline) void openRecord();           // 0x011e62b0
};

// A file-system stream handle bound to a package slot or opened by path.
struct StreamHandle
{
    void*       mHandle;    // +0x00
    void*       mBase;      // +0x04  owning object (or the returned slot)
    int         mStatus;    // +0x08
    StreamFile* mRecord;    // +0x0c
    void*       mOwner;     // +0x10
    int         mField14;   // +0x14
    int         mField18;   // +0x18
    int         mField1C;   // +0x1c
    int         mField20;   // +0x20
    int         mField24;   // +0x24

    __declspec(noinline) StreamHandle* open(const char* path, int flags, StreamFile* record);  // 0x011ecdf0
};

// The scheduler condition object: a count @+0, waiter count @+4, spin count @+8,
// two semaphores @+0xc/@+0x1c, an embedded Mutex @+0x2c, and a thread table
// (32 handles @+0x0, its critical section @+0x80).
struct ThreadObj
{
    ThreadRecord* mField0;    // +0x00  the thread record this object owns
    int   mField4;            // +0x04
    int   mField8;            // +0x08
    char  pad0C[0x80 - 0x0c]; // +0x0c .. +0x7f
    char  mCrit[0x18];        // +0x80

    __declspec(noinline) ThreadObj* ctor(int a, char b);          // 0x011ec390
    __declspec(noinline) char ctorStream(const char* name);       // 0x011ec2f0
    __declspec(noinline) int  condWait(Mutex* m, unsigned int* timeout);  // 0x011ec410
    __declspec(noinline) char condSignal(char all);               // 0x011ec4e0
    __declspec(noinline) void threadCleanup(char force);          // 0x011ec5d0
    __declspec(noinline) void threadAdd(void* handle, char add);  // 0x011ec650
    __declspec(noinline) char setPriority(int prio);              // 0x011ec840
    __declspec(noinline) int  setName(const char* name);          // 0x011ec8c0
    __declspec(noinline) void setIdealProcessor(int value);       // 0x011ec960
    __declspec(noinline) void* createThread(int ctx, int arg, ThreadDesc* desc, int start);  // 0x011ecc20
};

#define FUNC(va) void f_##va() {}

// WIN32_FIND_DATAA has an 0x140-byte layout; only the fields touched here matter.
struct FindData
{
    unsigned int dwFileAttributes;   // +0x00
    unsigned int ftCreationTimeLo;   // +0x04
    unsigned int ftCreationTimeHi;   // +0x08
    unsigned int ftLastAccessLo;     // +0x0c
    unsigned int ftLastAccessHi;     // +0x10
    unsigned int ftLastWriteLo;      // +0x14
    unsigned int ftLastWriteHi;      // +0x18
    unsigned int nFileSizeHigh;      // +0x1c
    unsigned int nFileSizeLow;       // +0x20
    unsigned int dwReserved0;        // +0x24
    unsigned int dwReserved1;        // +0x28
    char cFileName[0x104];           // +0x2c
    char cAlternateFileName[0x0e];   // +0x130
};

// A find-handle: {HANDLE, ?, ?, ?} allocated 0x10 bytes.
struct FindHandle { void* mHandle; void* f4; void* f8; void* fc; };

// @ 0x011ebf70
FindHandle* __stdcall f_011ebf70(const char* path, unsigned int* out)
{
    FindData fd;
    FindHandle* h = (FindHandle*)0;
    void* find = FindFirstFileA(path, &fd);
    if (find != (void*)-1)
    {
        FindHandle* p = (FindHandle*)FUN_011e6d20(0x10);
        if (!p)
        {
            h = 0;
        }
        else
        {
            p->f8 = 0;
            p->fc = 0;
            p->mHandle = find;
            h = p;
        }
        if (out)
        {
            out[2] = fd.ftCreationTimeLo;
            out[3] = fd.ftCreationTimeHi;
            out[4] = fd.ftLastAccessLo;
            out[5] = fd.ftLastAccessHi;
            out[6] = fd.ftLastWriteLo;
            out[7] = fd.ftLastWriteHi;
            out[8] = fd.nFileSizeHigh | 0;
            out[9] = fd.nFileSizeLow;
            FUN_011eba20((char*)(out + 10), fd.cFileName, 0x100);
            out[0] = 0;
            if ((fd.dwFileAttributes & 1) != 0) out[0] = 1;
            if ((fd.dwFileAttributes & 0x10) != 0) out[0] |= 2;
        }
    }
    return h;
}

// @ 0x011ec070
unsigned long long __stdcall f_011ec070(int, int, int, int, int, int) { return 0; }

// @ 0x011ec080
unsigned long long __stdcall f_011ec080(int) { return 0; }

// @ 0x011ec0b0
RwwString* RwwString::set(char flag, const char* src)
{
    m_flag = flag;
    if (src)
    {
        strncpy(m_buf, src, 0xf);
        m_buf[0xf] = 0;
    }
    else
    {
        m_buf[0] = 0;
    }
    return this;
}

// @ 0x011ec0f0
void Mutex::Destroy()
{
    if (mbIntraProcess)
        DeleteCriticalSection(this);
    else
        CloseHandle(mData0);
}

// @ 0x011ec110
bool Mutex::Init(const char* name)
{
    if (name)
    {
        mnLockCount = 0;
        mbIntraProcess = *name;
        if (mbIntraProcess)
        {
            InitializeCriticalSection(this);
            return true;
        }
        char tail = name[1];
        const char* p = tail ? name + 1 : 0;
        void* h = CreateMutexA(0, 0, p);
        mData0 = h;
        return h != 0;
    }
    return false;
}

// @ 0x011ec170
int Mutex::Lock(unsigned int* timeout)
{
    if (!mbIntraProcess)
    {
        unsigned int ms = *timeout;
        if (ms != 0xffffffffu && ms != 0)
        {
            unsigned int t = GetThreadTime();
            ms = (t < *timeout) ? (*timeout - t) : 0;
        }
        unsigned long r = WaitForSingleObject(mData0, ms);
        if (r == 0x102) return -2;
        if (r != 0) return -1;
    }
    else
    {
        if (*timeout == 0xffffffffu)
        {
            EnterCriticalSection(this);
        }
        else if (!TryEnterCriticalSection(this))
        {
            do
            {
                if (GetThreadTime() >= *timeout) return -2;
                Sleep(1);
            } while (!TryEnterCriticalSection(this));
        }
    }
    int n = mnLockCount + 1;
    mnLockCount = n;
    return n;
}

// @ 0x011ec230
int Mutex::Unlock()
{
    int n = mnLockCount - 1;
    mnLockCount = n;
    if (mbIntraProcess)
        LeaveCriticalSection(this);
    else
        ReleaseMutex(mData0);
    return n;
}

// @ 0x011ec260
Mutex* Mutex::ctor0(int a, char b)
{
    this->mnLockCount = 0;
    this->mField28 = 0;
    this->mbIntraProcess = 1;
    this->mData0 = 0;
    this->mField04 = 0;
    this->mField08 = 0;
    this->mField0C = 0;
    this->mField10 = 0;
    this->mField14 = 0;
    this->mField18 = 0;
    this->mField1C = 0;
    if (a == 0 && b != 0)
    {
        RwwString nm;
        nm.m_flag = 1;
        nm.m_buf[0] = 0;
        this->Init((const char*)&nm);
    }
    else
    {
        this->Init((const char*)a);
    }
    return this;
}

// @ 0x011ec2d0
void __fastcall f_011ec2d0(char* self)
{
    ((Mutex*)(self + 0x2c))->Destroy();
    ((StreamList*)(self + 0x1c))->teardown();
    ((StreamList*)(self + 0xc))->teardown();
}

// @ 0x011ec2f0
char ThreadObj::ctorStream(const char* name)
{
    if (!name) return 0;
    const char* nm = name[1] ? name + 1 : 0;
    char flag = name[0];
    RwwString s;
    StreamName n1;
    StreamName n2;
    n1.set(0, flag, nm);
    n2.set(1, flag, nm);
    s.set(flag, nm);
    if (!((Semaphore*)((char*)this + 0x0c))->Init(&n1)) return 0;
    if (!((Semaphore*)((char*)this + 0x1c))->Init(&n2)) return 0;
    if (!((Mutex*)((char*)this + 0x2c))->Init((const char*)&s)) return 0;
    return 1;
}

// @ 0x011ec390
ThreadObj* ThreadObj::ctor(int a, char b)
{
    _InterlockedExchange((volatile long*)this, 0);
    this->mField4 = 0;
    this->mField8 = 0;
    ((Semaphore*)((char*)this + 0x0c))->ctor0(0, 0);
    ((Semaphore*)((char*)this + 0x1c))->ctor0(0, 0);
    ((Mutex*)((char*)this + 0x2c))->ctor0(0, 0);
    if (a == 0 && b)
    {
        RwwString nm;
        nm.m_flag = 1;
        nm.m_buf[0] = 0;
        this->ctorStream((const char*)&nm);
    }
    else
    {
        this->ctorStream((const char*)a);
    }
    return this;
}

// @ 0x011ec410
int ThreadObj::condWait(Mutex* m, unsigned int* timeout)
{
    _InterlockedExchangeAdd((volatile long*)this, 1);
    int r = m->Unlock();
    if (r < 0) return r;
    r = ((Semaphore*)((char*)this + 0x0c))->Wait(timeout);
    ((Mutex*)((char*)this + 0x2c))->Lock(&g_014f70f8);
    int n = this->mField4;
    if (n != 0)
    {
        this->mField4 = n - 1;
    }
    else
    {
        int c = this->mField8 + 1;
        this->mField8 = c;
        if (c == 0x3fffffff)
        {
            ((Semaphore*)((char*)this + 0x1c))->Wait(&g_014f70f8);
            _InterlockedExchangeAdd((volatile long*)this, -this->mField8);
            ((Semaphore*)((char*)this + 0x1c))->Post(1);
            this->mField8 = 0;
        }
    }
    ((Mutex*)((char*)this + 0x2c))->Unlock();
    if (n == 1) ((Semaphore*)((char*)this + 0x1c))->Post(1);
    if (m->Lock(&g_014f70f8) == -1) return -1;
    return r;
}

// @ 0x011ec4e0
char ThreadObj::condSignal(char all)
{
    Mutex* mu = (Mutex*)((char*)this + 0x2c);
    if (mu->Lock(&g_014f70f8) < 0) return 0;
    int c = 1;
    if (this->mField4 != 0)
    {
        int t = _InterlockedExchangeAdd((volatile long*)this, 0);
        if (t == 0)
        {
            mu->Unlock();
            return 1;
        }
        if (all)
        {
            c = t;
            this->mField4 = this->mField4 + t;
            _InterlockedExchange((volatile long*)this, 0);
        }
        else
        {
            this->mField4 = this->mField4 + 1;
            _InterlockedExchangeAdd((volatile long*)this, -1);
        }
    }
    else
    {
        int t = _InterlockedExchangeAdd((volatile long*)this, 0);
        if (t <= this->mField8)
        {
            mu->Unlock();
            return 1;
        }
        if (((Semaphore*)((char*)this + 0x1c))->Wait(&g_014f70f8) == -1)
        {
            mu->Unlock();
            return 0;
        }
        if (this->mField8 != 0)
        {
            _InterlockedExchangeAdd((volatile long*)this, -this->mField8);
            this->mField8 = 0;
        }
        if (all)
        {
            c = _InterlockedExchangeAdd((volatile long*)this, 0);
            this->mField4 = c;
            _InterlockedExchange((volatile long*)this, 0);
        }
        else
        {
            this->mField4 = 1;
            _InterlockedExchangeAdd((volatile long*)this, -1);
        }
    }
    mu->Unlock();
    ((Semaphore*)((char*)this + 0x0c))->Post(c);
    return 1;
}

// @ 0x011ec5d0
void ThreadObj::threadCleanup(char force)
{
    void* cs = (char*)this + 0x80;
    EnterCriticalSection(cs);
    for (unsigned int i = 0; i < 0x20; i++)
    {
        void* h = ((void**)this)[i];
        if (!h) continue;
        if (force == 0)
        {
            unsigned long code = 0;
            if (GetExitCodeThread(h, &code) && code == 0x103) continue;
        }
        CloseHandle(((void**)this)[i]);
        ((void**)this)[i] = 0;
    }
    LeaveCriticalSection(cs);
}

// @ 0x011ec650
void ThreadObj::threadAdd(void* handle, char add)
{
    if (!handle) return;
    EnterCriticalSection((void*)((char*)this + 0x80));
    if (add)
    {
        unsigned int i;
        for (i = 0; i < 0x20; i++)
        {
            if (((void**)this)[i] == 0)
            {
                ((void**)this)[i] = handle;
                LeaveCriticalSection((void*)((char*)this + 0x80));
                return;
            }
        }
        for (i = 0; ; )
        {
            unsigned long code = 0;
            if (!GetExitCodeThread(((void**)this)[i], &code)) goto useSlot;
            if (code != 0x103) goto useSlot;
            if (++i >= 0x20) break;
        }
        CloseHandle(handle);
        LeaveCriticalSection((void*)((char*)this + 0x80));
        return;
useSlot:
        CloseHandle(((void**)this)[i]);
        ((void**)this)[i] = handle;
        LeaveCriticalSection((void*)((char*)this + 0x80));
        return;
    }
    unsigned int i = 0;
    for (;;)
    {
        if (((void**)this)[i] == handle) break;
        if (++i >= 0x20)
        {
            LeaveCriticalSection((void*)((char*)this + 0x80));
            return;
        }
    }
    CloseHandle(handle);
    ((void**)this)[i] = 0;
    LeaveCriticalSection((void*)((char*)this + 0x80));
}

// @ 0x011ec750
void f_011ec750(void* p, char c)
{
    if (g_015d0690 == 0xffffffff)
    {
        g_015d0690 = TlsAlloc();
        if (g_015d0690 == 0xffffffff) return;
    }
    if (c == 0)
    {
        g_016f4e18.threadCleanup(0);
    }
    else if (p != 0)
    {
        g_016f4e18.threadAdd(p, 1);
        TlsSetValue(g_015d0690, p);
        return;
    }
    else
    {
        void* v = TlsGetValue(g_015d0690);
        if (v != 0)
        {
            g_016f4e18.threadAdd(v, 0);
            TlsSetValue(g_015d0690, 0);
            return;
        }
    }
    TlsSetValue(g_015d0690, p);
}

// @ 0x011ec7e0
void f_011ec7e0(unsigned long* p)
{
    SleepEx(*p, 1);
}

// @ 0x011ec800
int* __fastcall f_011ec800(int* p)
{
    p[0] = 0; p[1] = 0; p[2] = 0; p[3] = -1;
    ((char*)p)[0x10] = 0;
    p[5] = (int)0x13ec47c;
    return p;
}

// @ 0x011ec830
int* __fastcall f_011ec830(int* p) { *p = 0; return p; }

// @ 0x011ec840
char ThreadObj::setPriority(int prio)
{
    if (this->mField0 != 0)
    {
        if (SetThreadPriority(*(void**)this->mField0, prio) != 0) return 1;
        if (prio < 0xf)
        {
            do
            {
                if (prio <= -0xf) return SetThreadPriority(*(void**)this->mField0, -0xf) != 0;
                char r = SetThreadPriority(*(void**)this->mField0, prio) != 0;
                if (r) return 1;
                prio++;
            } while (prio < 0xf);
        }
        return SetThreadPriority(*(void**)this->mField0, 0xf) != 0;
    }
    return 0;
}

// @ 0x011ecb00
void __fastcall f_011ecb00(int** self)
{
    int* q = *self;
    if (q)
    {
        if (_InterlockedDecrement((volatile long*)((char*)q + 0x20)) == 0)
            FUN_011eca90(q);
    }
}

// @ 0x011ecba5
int f_011ecba5() { return -1; }

// @ 0x011ecd90
void __fastcall f_011ecd90(int* p)
{
    InitializeCriticalSection((void*)(p + 1));
    *p = 1;
}

// @ 0x011ecdb0
void __fastcall f_011ecdb0(int* p)
{
    if (*p)
    {
        DeleteCriticalSection((void*)(p + 1));
        *p = 0;
    }
}

// @ 0x011ecdd0
void __fastcall f_011ecdd0(int* p)
{
    if (*p) EnterCriticalSection((void*)(p + 1));
}

// @ 0x011ecde0
void __fastcall f_011ecde0(int* p)
{
    if (*p) LeaveCriticalSection((void*)(p + 1));
}

// @ 0x011ecf40
void __fastcall f_011ecf40(int* p)
{
    if (p[2])
        (*(void (__thiscall**)(void*, int))((*(char**)p[4]) + 0x10))((void*)p[4], p[2]);
    p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[0] = 0;
}

// @ 0x011ec8c0
// Set the thread name (SEH-guarded): copy the requested name into the thread record and
// hand it to the debugger through RaiseException.
int __thiscall ThreadObj::setName(const char* name)
{
    int result = 0;
    __try
    {
        if (mField0 != 0 && name != 0)
        {
            strncpy(mField0->mName, name, 0x40);
            mField0->mName[0x3f] = 0;
            if (mField0->mHandle != 0)
            {
                THREADNAME_INFO info;
                info.dwType = 0x1000;
                info.szName = mField0->mName;
                info.dwThreadID = mField0->mThreadId;
                info.dwFlags = 0;
                RaiseException(0x406d1388, 0, 4, (unsigned long*)&info);
            }
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return -1;
    }
    return result;
}

// @ 0x011ec960
// Pick the processor for this thread: initialise the processor-count word from
// GetSystemInfo on first use, map the requested index (negative wraps to 0x20) into it,
// and hand it to SetThreadIdealProcessor.
void __thiscall ThreadObj::setIdealProcessor(int value)
{
    if (mField0 == 0) return;
    if (g_016f5bc4 & 1)
    {
    }
    else
    {
        g_016f5bc4 |= 1;
        _InterlockedExchange((volatile long*)&g_016f5bc0, 0);
    }
    if (_InterlockedExchangeAdd((volatile long*)&g_016f5bc0, 0) == 0)
    {
        SYSTEM_INFO si = {0};
        GetSystemInfo(&si);
        _InterlockedExchange((volatile long*)&g_016f5bc0, si.dwNumberOfProcessors);
    }
    int n = value;
    if (value >= _InterlockedExchangeAdd((volatile long*)&g_016f5bc0, 0))
        n = value % _InterlockedExchangeAdd((volatile long*)&g_016f5bc0, 0);
    if (value < 0)
        n = 0x20;
    SetThreadIdealProcessor(mField0->mHandle, n);
}

// @ 0x011eca30
// Allocate a refcounted object: claim one of the 0x20 lock words at 0x16f5b40 with a
// cmpxchg and return the matching entry of the 0x16f4eb0 table (stride 0x64), or a
// freshly zeroed block when every lock word is taken.
int* AllocThreadRecord()
{
    int i = 0;
    int* lock = (int*)0x016f5b40;
    do
    {
        if (_InterlockedCompareExchange((volatile long*)lock, 1, 0) == 0)
            return (int*)(0x016f4eb0 + i * 0x64);
        i++;
        lock++;
    } while ((unsigned int)i < 0x20);
    ThreadRecord* block = (ThreadRecord*)f_011eca10(0x64);
    if (block != 0)
    {
        block->mHandle = 0;
        block->mThreadId = 0;
        block->mState = 0;
        block->mResult = 0;
        block->mStart = 0;
        _InterlockedExchange(&block->mRefCount, 0);
        return (int*)block;
    }
    return 0;
}

// @ 0x011eca90
// Release a refcounted object: inside the 0x16f4eb0 table clear its lock word and close
// the handle it holds, outside it close the handle and free the block.
void f_011eca90(int* p)
{
    if (p >= (int*)0x016f4eb0 && p < (int*)0x016f5b30)
    {
        int i = (int)((unsigned int)p - 0x016f4eb0) / 0x64;
        _InterlockedExchange((volatile long*)(0x016f5b40 + i * 4), 0);
        p = (int*)*p;
        if (p == 0) return;
        CloseHandle(p);
        return;
    }
    if (p != 0)
    {
        if (*p != 0) CloseHandle((void*)*p);
        operator_del(p);
    }
}

// @ 0x011ecb20
// Render-thread entry point (SEH-guarded setup): install the thread-local hook, publish
// the running state and optional thread name, then run the record's start routine,
// publish its result and release the record.
unsigned int __stdcall f_011ecb20(void* arg)
{
    ThreadRecord* self = (ThreadRecord*)arg;
    int ctx = self->mContext;
    int startArg = self->mArg;
    __try
    {
        f_011ec750(self->mOwnerHandle, 0);
        self->mState = 1;
        if (self->mName[0] != 0)
        {
            THREADNAME_INFO info;
            info.dwType = 0x1000;
            info.szName = self->mName;
            info.dwThreadID = self->mThreadId;
            info.dwFlags = 0;
            RaiseException(0x406d1388, 0, 4, (unsigned long*)&info);
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (unsigned int)-1;
    }
    int r;
    if (self->mStart != 0)
        r = ((int (*)(int, int))self->mStart)(startArg, ctx);
    else
        r = ((int (*)(int))ctx)(startArg);
    self->mResult = r;
    f_011ec750(0, 0);
    self->mState = 2;
    if (_InterlockedExchangeAdd(&self->mRefCount, -1) == 0)
        f_011eca90((int*)self);
    return r;
}

// @ 0x011ecba9
// SEH continuation of 0x011ecb20: run the record's start routine, publish its result and
// release the record.
int f_011ecba9(ThreadRecord* self)
{
    int ctx = self->mContext;
    int startArg = self->mArg;
    int r;
    if (self->mStart != 0)
        r = ((int (*)(int, int))self->mStart)(startArg, ctx);
    else
        r = ((int (*)(int))ctx)(startArg);
    self->mResult = r;
    f_011ec750(0, 0);
    self->mState = 2;
    if (_InterlockedExchangeAdd(&self->mRefCount, -1) == 0)
        f_011eca90((int*)self);
    return r;
}

// @ 0x011ecc20
// Create the render thread: release the previous record, take a refcounted record, fill
// in its start routine/arguments, spawn it with _beginthreadex, then set the thread
// name, priority and processor from the descriptor before resuming it.
void* __thiscall ThreadObj::createThread(int ctx, int arg, ThreadDesc* desc, int start)
{
    ThreadRecord* old = mField0;
    if (old != 0 && _InterlockedExchangeAdd(&old->mRefCount, -1) == 0)
        f_011eca90((int*)old);
    ThreadRecord* obj = (ThreadRecord*)AllocThreadRecord();
    if (obj != 0)
    {
        obj->mHandle = 0;
        obj->mThreadId = 0;
        obj->mState = 0;
        obj->mResult = 0;
        obj->mStart = 0;
        _InterlockedExchange(&obj->mRefCount, 0);
    }
    else
    {
        obj = 0;
    }
    mField0 = obj;
    _InterlockedExchangeAdd(&obj->mRefCount, 1);
    _InterlockedExchangeAdd(&mField0->mRefCount, 1);
    ThreadRecord* o = mField0;
    o->mHandle = 0;
    o->mContext = ctx;
    o->mArg = arg;
    o->mStart = start;
    void* handle = _beginthreadex(0, desc != 0 ? desc->mStackSize : 0, f_011ecb20, o, 4,
                                  &o->mThreadId);
    *mField0 = o[1];
    o->mHandle = handle;
    if (handle == 0)
    {
        if (_InterlockedExchangeAdd(&o->mRefCount, -1) == 0)
            f_011eca90((int*)o);
        if (_InterlockedExchangeAdd(&mField0->mRefCount, -1) == 0)
            f_011eca90((int*)mField0);
        mField0 = 0;
        return 0;
    }
    if (desc != 0) setName(desc->mName);
    o->mOwnerHandle = handle;
    if (desc != 0)
    {
        if (desc->mPriority != 0)
            setPriority(desc->mPriority);
        if (desc->mProcessor >= 0)
        {
            int proc = desc->mProcessor;
            if (proc == _InterlockedExchangeAdd((volatile long*)&g_016f5b38, 0))
                _InterlockedExchangeAdd((volatile long*)&g_016f5b38, 1);
            setIdealProcessor(proc);
        }
        else if (g_015d0694 < 0)
        {
            int proc = (int)_InterlockedExchangeAdd((volatile long*)&g_016f5b38, 1) + 1;
            setIdealProcessor(proc);
        }
    }
    ResumeThread(handle);
    return handle;
}

// @ 0x011ecdf0
// File-system stream handle: bind to a streamed-file slot of the package (opening the
// slot record and formatting its "%s/%s" path), or open a standalone record by path.
StreamHandle* __thiscall StreamHandle::open(const char* path, int flags, StreamFile* record)
{
    void* unused = 0;
    mHandle = 0;
    mBase = 0;
    mStatus = 0;
    mRecord = record;
    mOwner = record->mOwner;
    mField18 = 0;
    mField1C = 0;
    mField20 = 0;
    mField24 = 0;

    StreamFile* file = record;
    if (record == GetPackageState()->mFile)
    {
        if (GetPackageState()->mCount != 0)
        {
            unsigned int i = 0;
            do
            {
                void* name = GetPackageState()->mEntries[i].mName;
                if (name == 0) break;
                file = GetPackageState()->mEntries[i].mFile;
                if (file->mOpened == 0) file->openRecord();
                char buf[0x100];
                sprintf(buf, "%s/%s", (const char*)name, path);
                void* owner = file->mOwner;
                void** vtbl = *(void***)owner;
                int (__thiscall* openFn)(void*, const char*, int, void*) =
                    (int (__thiscall*)(void*, const char*, int, void*))vtbl[3];
                mStatus = openFn(owner, buf, flags, &unused);
                if (mStatus != 0) break;
                i++;
            } while (i < GetPackageState()->mCount);
        }
    }
    else
    {
        void* owner = record->mOwner;
        void** vtbl = *(void***)owner;
        int (__thiscall* openFn)(void*, int, StreamFile*, void*) =
            (int (__thiscall*)(void*, int, StreamFile*, void*))vtbl[3];
        mStatus = openFn(owner, flags, record, &unused);
    }

    if (mStatus == 0) return this;
    mRecord = file;
    mOwner = file->mOwner;
    {
        void* owner = mOwner;
        void** vtbl = *(void***)owner;
        long long (__thiscall* seekFn)(void*, int) =
            (long long (__thiscall*)(void*, int))vtbl[8];
        long long pos = seekFn(owner, mStatus);
        mField18 = (int)pos;
        mField1C = (int)(pos >> 32);
    }
    mBase = this;
    if (unused != 0)
    {
        mBase = unused;
        mRecord = *(StreamFile**)((char*)unused + 0xc);
    }
    return this;
}
