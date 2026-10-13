// src/game/UTFSpore_Win32/EASharedLibrary.cpp -- migrated from slice(s) s00936090, s008dd0d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EASharedLibrary.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/SharedLibrary.h"
#include "EA/SharedLibraryRegistry.h"
#include "EA/Thread/Mutex.h"

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);

// ---- items of slice s00936090 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __int64 __rdtsc(void);
extern "C" const char kDefaultSharedLibraryVersionInfo[];   // 0x0143e990
#pragma intrinsic(__rdtsc)
namespace EA {
extern void* gpRegistryMutexName;   // 0x0143e98c
}
extern "C" void* gpSharedLibraryRegistry;   // 0x01669948
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryW(const wchar_t*);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void*, const char*);
extern "C" __declspec(dllimport) int   __stdcall FreeLibrary(void*);
// ---- items of slice s00936090 end

// @ 0x008dd1c0
int EA::SharedLibrary::Release()
{
    int n = _InterlockedExchangeAdd((volatile long*)((char*)this + 4), -1);
    --n;
    if (n == 0) {
        _InterlockedExchange((volatile long*)((char*)this + 4), 1);
        if (this != 0)
            ((void (__thiscall*)(void*, int))(*(void***)this)[0])(this, 1);
        n = 0;
    }
    return n;
}

// @ 0x00936330
bool EA::SharedLibrary::CanUnload() const
{
    void* p = 0;
    if (IsLoaded()) {
        if (!ExecuteCommand("CanSharedLibraryUnload", &p, 0, 0, 0) || p == 0)
            return false;
    }
    return true;
}

// @ 0x00936380
bool EA::SharedLibrary::Reload(bool flag)
{
    if (!Unload(flag))
        return false;
    return Load();
}

// @ 0x009363b0
EA::SharedLibrary::VersionInfo const * EA::SharedLibrary::GetVersionInfo() const
{
    void** p = 0;
    if (IsLoaded() && ExecuteCommand("GetSharedLibraryVersion", &p, 0, 0, 0) && p != 0)
        return (EA::SharedLibrary::VersionInfo const *)p;
    return (EA::SharedLibrary::VersionInfo const *)kDefaultSharedLibraryVersionInfo;
}

// @ 0x00936440
bool __cdecl EA_generic_command_function(const char* name, void* self, void** out, int a, int b, int c)
{
    if (self != 0) {
        struct Entry { void* fn; void* user; };
        Entry* it = *(Entry**)((char*)self + 0x1c);
        Entry* end = *(Entry**)((char*)self + 0x20);
        for (; it < end; it++) {
            typedef bool (__cdecl *Fn)(const char*, void*, void**, int, int, int);
            if (((Fn)it->fn)(name, it->user, out, a, b, c))
                return true;
        }
    }
    const char* s1 = name;
    const char* s2 = "GetSharedLibraryVersion";
    while (*s1 == *s2) {
        if (*s1 == 0)
            break;
        s1++;
        s2++;
    }
    bool equal = (*s1 == *s2);
    if (equal) {
        *out = (void*)kDefaultSharedLibraryVersionInfo;
        return true;
    }
    return false;
}

// @ 0x009364f0
bool EA::SharedLibraryRegistry::RemoveAllLibraries(bool flag)
{
    mMutex.Lock(*(unsigned int const *)&gpRegistryMutexName);
    void** begin = (void**)mSharedLibraries.mpBegin;
    void** end = (void**)mSharedLibraries.mpEnd;
    if (begin != end) {
        while (((char*)end - (char*)begin) >> 2 > 1) {
            void* lib = begin[1];
            RemoveLibrary((EA::SharedLibrary *)lib, flag);
            begin = (void**)mSharedLibraries.mpBegin;
            end = (void**)mSharedLibraries.mpEnd;
        }
    }
    mMutex.Unlock();
    return true;
}

// @ 0x00936550
unsigned int EA::SharedLibraryRegistry::ExecuteCommandAll(char const * a, void * b, void * c, void * d, void * e)
{
    mMutex.Lock(*(unsigned int const *)&gpRegistryMutexName);
    int count = 0;
    unsigned int n = (unsigned int)(((char*)mSharedLibraries.mpEnd - (char*)mSharedLibraries.mpBegin) >> 2);
    for (unsigned int i = 0; i < n; i++) {
        EA::SharedLibrary* lib = ((EA::SharedLibrary**)mSharedLibraries.mpBegin)[i];
        if (lib->ExecuteCommand((const char*)a, b, c, d, e))
            count++;
    }
    mMutex.Unlock();
    return count;
}

// @ 0x009365d0
EA::SharedLibrary * EA::SharedLibraryRegistry::GetMainLibrary()
{
    return *(EA::SharedLibrary**)mSharedLibraries.mpBegin;
}

// @ 0x009365e0
bool EA::SharedLibrary::Load()
{
    if (IsLoaded())
        return true;
    if (mPath.mpBegin == mPath.mpEnd)
        return false;
    void* h = LoadLibraryW(mPath.mpBegin);
    if (h == 0)
        return false;
    typedef bool (__cdecl *StartupFn)(void*, void*, void**, void**);
    StartupFn fn = (StartupFn)GetProcAddress(h, "EASharedLibraryStartupFunction");
    if (fn == 0) {
        FreeLibrary(h);
        return false;
    }
    void* registry = 0;
    if (gpSharedLibraryRegistry != 0)
        registry = (void*)(*(void*(__thiscall**)(void*))((char*)*(void**)gpSharedLibraryRegistry + 0x24))(gpSharedLibraryRegistry);
    void* ctx = 0;
    void* result = 0;
    if (fn(EA_generic_command_function, registry, &ctx, &result) && ctx != 0) {
        void* out = 0;
        if (!(*(bool(__cdecl**)(const char*, void*, void**, int, int, int))ctx)
                ("OnSharedLibraryLoad", result, (void**)&out, 0, 0, 0) || out != 0) {
            mHandle = h;
            (*(void(__thiscall**)(void*, void*, void*))((char*)*(void**)this + 0x24))(this, ctx, result);
            return true;
        }
    }
    FreeLibrary(h);
    return false;
}

// @ 0x00936710
bool EA::SharedLibrary::ExecuteCommand(char const * name, void * a, void * b, void * c, void * d) const
{
    int d_v = (int)d;
    int c_v = (int)c;
    int b_v = (int)b;
    return EA_generic_command_function(name, (void*)this, (void**)a, b_v, c_v, d_v);
}
