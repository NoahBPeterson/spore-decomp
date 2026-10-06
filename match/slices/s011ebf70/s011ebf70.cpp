// Slice s011ebf70 -- RenderWare core threading (rw::core::thread::Mutex) and
// file-system iterator helpers.
//
// Small wrappers plus Mutex::{Init,Lock,Unlock,Destroy}; the remaining scheduler /
// filesystem stream bodies are recorded as partial (see partial.txt).
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
}

unsigned int GetThreadTime();      // 0x011ec7f0
void FUN_011ed3f0(void*);          // stream/list teardown
void FUN_011eba20(char* dst, const char* src, int n);   // rw::core::stdc::StringnCopy
void* FUN_011e6d20(unsigned int);  // rw::core::filesys::StreamImpl::operator new

#define FUNC(va) void f_##va() {}

// @ 0x011ec070
unsigned long long __stdcall f_011ec070(int, int, int, int, int, int) { return 0; }

// @ 0x011ec080
unsigned long long __stdcall f_011ec080(int) { return 0; }

// @ 0x011ec0b0
struct RwwString
{
    char m_flag;          // +0
    char m_buf[0x10];     // +1
    RwwString* set(char flag, const char* src);
};
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
struct Mutex
{
    void* mData0;             // +0
    char pad[0x20 - 4];
    int  mnLockCount;         // +0x20
    bool mbIntraProcess;      // +0x24

    __declspec(noinline) void Destroy();
    bool Init(const char* name);
    int  Lock(unsigned int* timeout);
    int  Unlock();
};

struct StreamList { void teardown(); };

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
    if (!name) return false;
    mnLockCount = 0;
    mbIntraProcess = *name != 0;
    if (*name)
    {
        InitializeCriticalSection(this);
        return true;
    }
    const char* p = name[1] ? name + 1 : 0;
    void* h = CreateMutexA(0, 0, p);
    mData0 = h;
    return h != 0;
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

// @ 0x011ec2d0
void __fastcall f_011ec2d0(char* self)
{
    ((Mutex*)(self + 0x2c))->Destroy();
    ((StreamList*)(self + 0x1c))->teardown();
    ((StreamList*)(self + 0xc))->teardown();
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

// ---- remaining scheduler / filesystem stream bodies: partial -------------
FUNC(011ebf70)
FUNC(011ec260)
FUNC(011ec2f0)
FUNC(011ec390)
FUNC(011ec410)
FUNC(011ec4e0)
FUNC(011ec5d0)
FUNC(011ec650)
FUNC(011ec750)
FUNC(011ec840)
FUNC(011ec8c0)
FUNC(011ec960)
FUNC(011eca30)
FUNC(011eca90)
FUNC(011ecb20)
FUNC(011ecba9)
FUNC(011ecc20)
FUNC(011ecdf0)
