// src/game/UTFSpore_Win32/EAProcess.cpp -- migrated from slice(s) s009350f0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAProcess.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void  __cdecl _wsearchenv(const wchar_t* file, const wchar_t* var, wchar_t* buf);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(_InterlockedExchange, _InterlockedDecrement, _InterlockedIncrement, _InterlockedExchangeAdd)
#pragma intrinsic(__rdtsc)

// ---- items of slice s009350f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void  __cdecl _wsearchenv(const wchar_t* file, const wchar_t* var, wchar_t* buf);
// ---- items of slice s009350f0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) int   __cdecl _spawnv(int mode, const char* path, const char* const* argv);
extern "C" __declspec(dllimport) void  __cdecl _searchenv(const char* file, const char* var, char* buf);

// @ 0x00935db0
namespace EA {
namespace Process {
int Spawn(char const * path, char const *const * argv, bool wait)
{
    if (wait)
        return _spawnv(0, path, argv);
    return _spawnv(4, path, argv);
}
}
}  // namespace EA::Process

// @ 0x00935e00
bool WideSearchEnvironmentPath(const wchar_t* file, wchar_t* buf, const wchar_t* env)
{
    if (env == 0)
        env = L"PATH";
    _wsearchenv(file, env, buf);
    return buf[0] != 0;
}

// @ 0x00935e30
namespace EA {
namespace Process {
bool SearchEnvironmentPath(char const * file, char * buf, char const * env)
{
    if (env == 0)
        env = "PATH";
    _searchenv(file, env, buf);
    return buf[0] != 0;
}
}
}  // namespace EA::Process

// @ 0x00935e60
namespace EA {
namespace Process {
bool OpenFile(wchar_t const * url)
{
    (void)url;
    return false;
}
}
}  // namespace EA::Process

// @ 0x00935f80
void Process_OpenFileA(const char* path)
{
    (void)path;
}

// @ 0x00935fb0
namespace EA {
namespace Process {
bool OpenBrowser(wchar_t const * url, bool a2)
{
    (void)url;
    return false;
}
}
}  // namespace EA::Process
