// src/game/UTFSpore_Win32/EAOSGlobal.cpp -- migrated from slice(s) s009350f0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAOSGlobal.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void* __stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void* __stdcall HeapAlloc(void* hHeap, unsigned long dwFlags, unsigned long dwBytes);
extern "C" __declspec(dllimport) int   __stdcall HeapFree(void* hHeap, unsigned long dwFlags, void* lpMem);
extern "C" __declspec(dllimport) void  __stdcall InitializeCriticalSection(void* cs);
extern "C" __declspec(dllimport) void  __stdcall DeleteCriticalSection(void* cs);
extern "C" __declspec(dllimport) void  __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void  __stdcall LeaveCriticalSection(void* cs);
extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentProcessId(void);
extern "C" __declspec(dllimport) void* __stdcall CreateMutexA(void* sa, int initialOwner, const char* name);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void* h, unsigned long ms);
extern "C" __declspec(dllimport) unsigned long __stdcall GetEnvironmentVariableA(const char* name, char* buf, unsigned long n);
extern "C" __declspec(dllimport) int   __stdcall SetEnvironmentVariableA(const char* name, const char* value);
extern "C" __declspec(dllimport) int   __stdcall ReleaseMutex(void* h);
extern "C" __declspec(dllimport) int   __stdcall CloseHandle(void* h);
extern "C" __declspec(dllimport) int   __cdecl wsprintfA(char* dst, const char* fmt, ...);
extern "C" __declspec(dllimport) int   __cdecl sprintf(char* dst, const char* fmt, ...);
extern "C" __declspec(dllimport) unsigned __int64 __cdecl _strtoui64(const char* s, char** end, int base);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" unsigned __int64 __rdtsc(void);
extern "C" void* gpOSGlobalManager;
extern "C" long  gOSGlobalRefs;
#pragma intrinsic(_InterlockedExchange, _InterlockedDecrement, _InterlockedIncrement, _InterlockedExchangeAdd)
#pragma intrinsic(__rdtsc)

// ---- items of slice s009350f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void* __stdcall HeapAlloc(void* hHeap, unsigned long dwFlags, unsigned long dwBytes);
extern "C" __declspec(dllimport) int   __stdcall HeapFree(void* hHeap, unsigned long dwFlags, void* lpMem);
extern "C" __declspec(dllimport) void  __stdcall InitializeCriticalSection(void* cs);
extern "C" __declspec(dllimport) void  __stdcall DeleteCriticalSection(void* cs);
extern "C" __declspec(dllimport) void  __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void  __stdcall LeaveCriticalSection(void* cs);
extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentProcessId(void);
extern "C" __declspec(dllimport) void* __stdcall CreateMutexA(void* sa, int initialOwner, const char* name);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void* h, unsigned long ms);
extern "C" __declspec(dllimport) unsigned long __stdcall GetEnvironmentVariableA(const char* name, char* buf, unsigned long n);
extern "C" __declspec(dllimport) int   __stdcall SetEnvironmentVariableA(const char* name, const char* value);
extern "C" __declspec(dllimport) int   __stdcall ReleaseMutex(void* h);
extern "C" __declspec(dllimport) int   __stdcall CloseHandle(void* h);
extern "C" __declspec(dllimport) int   __cdecl wsprintfA(char* dst, const char* fmt, ...);
extern "C" __declspec(dllimport) int   __cdecl sprintf(char* dst, const char* fmt, ...);
extern "C" __declspec(dllimport) unsigned __int64 __cdecl _strtoui64(const char* s, char** end, int base);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" void* gpOSGlobalManager;
extern "C" long  gOSGlobalRefs;
struct OSGlobalNode {
    OSGlobalNode* mpNext;     // +0x00
    OSGlobalNode* mpPrev;     // +0x04
    int           mnId;       // +0x08
    volatile long mnRefCount; // +0x0c
};
struct OSGlobalManager {
    uint32_t mpNext;          // +0x00
    uint32_t mpPrev;          // +0x04
    volatile long mnRefCount; // +0x08
    char mCS[0x18];           // +0x0c
};
struct intrusive_list_base { ~intrusive_list_base(); };
// ---- items of slice s009350f0 end

// @ 0x00935a30
void* CreateOSGlobalManager()
{
    void* pv = HeapAlloc(GetProcessHeap(), 0, 0x37);
    uint32_t u = ((uint32_t)pv + 0x13) & 0xfffffff0;
    *(void**)(u - 4) = pv;
    *(uint32_t*)(u + 4) = u;
    *(uint32_t*)u = u;
    _InterlockedExchange((volatile long*)(u + 8), 0);
    InitializeCriticalSection((void*)(u + 0xc));
    return (void*)u;
}

// @ 0x00935a70
void ShutdownOSGlobalSystem()
{
    if (_InterlockedDecrement(&gOSGlobalRefs) == 0) {
        if (gpOSGlobalManager) {
            if (_InterlockedDecrement((long*)((char*)gpOSGlobalManager + 8)) == 0) {
                OSGlobalManager* p = (OSGlobalManager*)gpOSGlobalManager;
                DeleteCriticalSection(p->mCS);
                ((intrusive_list_base*)p)->~intrusive_list_base();
                HeapFree(GetProcessHeap(), 0, *(void**)((char*)gpOSGlobalManager - 4));
            }
            gpOSGlobalManager = 0;
        }
    }
}

// @ 0x00935ad0
bool EA_ReleaseOSGlobal(OSGlobalNode* p)
{
    EnterCriticalSection((char*)gpOSGlobalManager + 0xc);
    bool bLast = _InterlockedDecrement(&gOSGlobalRefs) == 0;
    long n = _InterlockedDecrement(&p->mnRefCount);
    n = _InterlockedExchangeAdd(&p->mnRefCount, 0);
    if (n == 0) {
        OSGlobalNode* anchor = (OSGlobalNode*)gpOSGlobalManager;
        OSGlobalNode* it = anchor->mpNext;
        while (it != anchor && it != p)
            it = it->mpNext;
        OSGlobalNode* prev = it->mpPrev;
        OSGlobalNode* next = it->mpNext;
        prev->mpNext = next;
        next->mpPrev = prev;
        it->mpNext = 0;
        it->mpPrev = 0;
    }
    LeaveCriticalSection((char*)gpOSGlobalManager + 0xc);
    if (bLast)
        ShutdownOSGlobalSystem();
    return n == 0;
}

// @ 0x00935b70
bool InitOSGlobalSystem()
{
    if (gpOSGlobalManager != 0) {
        _InterlockedIncrement(&gOSGlobalRefs);
        return true;
    }
    char mutexName[64];
    char value[32];
    wsprintfA(mutexName, "SingleMgrMutex%08x", GetCurrentProcessId());
    void* h = CreateMutexA(0, 0, mutexName);
    if (h != 0) {
        if (WaitForSingleObject(h, 0xffffffff) != 0xffffffff) {
            unsigned long n = GetEnvironmentVariableA(mutexName, value, 0x20);
            if (n == 0 || value[0] == 0) {
                gpOSGlobalManager = CreateOSGlobalManager();
                sprintf(value, "%I64x", (uint64_t)(uint32_t)gpOSGlobalManager);
                SetEnvironmentVariableA(mutexName, value);
            } else {
                gpOSGlobalManager = (void*)(uint32_t)_strtoui64(value, 0, 16);
            }
            _InterlockedIncrement((long*)((char*)gpOSGlobalManager + 8));
            ReleaseMutex(h);
            CloseHandle(h);
        }
        if (gpOSGlobalManager != 0) {
            _InterlockedIncrement(&gOSGlobalRefs);
            return true;
        }
        ShutdownOSGlobalSystem();
    }
    return false;
}

// @ 0x00935c80
OSGlobalNode* GetOSGlobal(int id, void* (*ctor)())
{
    if (!InitOSGlobalSystem())
        return 0;
    EnterCriticalSection((char*)gpOSGlobalManager + 0xc);
    OSGlobalNode* it;
    for (it = ((OSGlobalNode*)gpOSGlobalManager)->mpNext; it != (OSGlobalNode*)gpOSGlobalManager; it = it->mpNext) {
        if (it->mnId == id)
            goto found;
    }
    it = 0;
    if (ctor) {
        it = (OSGlobalNode*)ctor();
        it->mnId = id;
        _InterlockedExchange(&it->mnRefCount, 0);
        it->mpNext = 0;
        it->mpPrev = 0;
        OSGlobalNode* anchor = (OSGlobalNode*)gpOSGlobalManager;
        it->mpNext = anchor->mpNext;
        it->mpPrev = anchor;
        anchor->mpNext = it;
        it->mpNext->mpPrev = it;
    found:
        _InterlockedIncrement(&it->mnRefCount);
        _InterlockedIncrement(&gOSGlobalRefs);
    }
    LeaveCriticalSection((char*)gpOSGlobalManager + 0xc);
    return it;
}
