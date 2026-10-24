// Slice s011ebf70 -- RenderWare core threading (rw::core::thread) scheduler and
// file-system helpers, plus the neighbouring Mutex / RwwString helpers.
//
// The 10 targets of this slice are the scheduler / filesystem entry points; the
// Mutex::{Destroy,Init,Lock,Unlock}, RwwString::set and the small trivial
// wrappers are the neighbouring functions recorded alongside them.
#include "types.h"
#include <intrin.h>

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
}

// out-of-slice helpers.
void* FUN_011e6d20(unsigned int);                    // 0x011e6d20  operator new
void  FUN_011eba20(char* dst, const char* src, int n);   // 0x011eba20  stdc::StringnCopy
unsigned int GetThreadTime();                        // 0x011ec7f0
void FUN_011ed3f0(void*);                            // stream/list teardown

// The process-wide thread scheduler object and its TLS index.
struct ThreadObj;
extern ThreadObj g_016f4e18;                         // 0x016f4e18
extern unsigned long g_015d0690;                     // 0x015d0690
extern unsigned int g_014f70f8;                      // 0x014f70f8

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

// The scheduler condition object: a count @+0, waiter count @+4, spin count @+8,
// two semaphores @+0xc/@+0x1c, an embedded Mutex @+0x2c, and a thread table
// (32 handles @+0x0, its critical section @+0x80).
struct ThreadObj
{
    void* mField0;            // +0x00
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

FUNC(011ec8c0)
FUNC(011ec960)
FUNC(011eca30)
FUNC(011eca90)
FUNC(011ecb20)
FUNC(011ecba9)
FUNC(011ecc20)
FUNC(011ecdf0)
