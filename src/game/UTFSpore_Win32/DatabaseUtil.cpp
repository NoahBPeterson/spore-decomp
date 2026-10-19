// src/game/UTFSpore_Win32/DatabaseUtil.cpp -- migrated from slice(s) s008dd0d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DatabaseUtil.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "eastl/allocator.h"
#include "EA/ResourceMan/Manager.h"
#include "EA/ResourceMan/Database.h"
#include "EA/SharedLibrary.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedIncrement)

// ---- items of slice s008dd0d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Str { void append(const wchar_t* s); };
// ---- items of slice s008dd0d0 end

// @ 0x008dd8f0
extern "C" int FUN_008dd8f0(int* self, void* out)
{
    (void)self; (void)out;
    return 0;
}

// @ 0x008ddb00
extern "C" unsigned FUN_008ddb00(void* self, int a2, int a3, int a4, int a5, int a6)
{
    void* io = 0;
    int r = ((char (__thiscall*)(void*, int, void**, int, int, int, int))
             (((void**)*(void**)self)[0x34 / 4]))(self, a2, &io, 1, 3, a5, a6);
    unsigned result = 0;
    if (r) {
        void* s = ((void* (__thiscall*)(void*))(((void**)*(void**)io)[0x18 / 4]))(io);
        if (s != 0) {
            unsigned avail = ((unsigned (__thiscall*)(void*))(((void**)*(void**)s)[0x1c / 4]))(s);
            if (a4 < (int)avail)
                avail = (unsigned)a4;
            result = ((unsigned (__thiscall*)(void*, int, unsigned))(((void**)*(void**)s)[0x30 / 4]))(s, a6, avail);
            ((void (__thiscall*)(void*))(((void**)*(void**)io)[0x24 / 4]))(io);
        }
    }
    if (io != 0)
        ((void (__thiscall*)(void*))(((void**)*(void**)io)[8 / 4]))(io);
    return result;
}

// @ 0x008ddb90
extern "C" char FUN_008ddb90(void* self, int a2, int a3, int a4, int a5)
{
    void* io = 0;
    char result = 0;
    int r = ((char (__thiscall*)(void*, int, void**, int, int, int, int))
             (((void**)*(void**)self)[0x34 / 4]))(self, a2, &io, 2, 2, a5, 0);
    if (r) {
        void* s = ((void* (__thiscall*)(void*))(((void**)*(void**)io)[0x18 / 4]))(io);
        if (s != 0)
            result = ((char (__thiscall*)(void*, int, int))(((void**)*(void**)s)[0x38 / 4]))(s, a3, a4);
        ((void (__thiscall*)(void*))(((void**)*(void**)io)[0x24 / 4]))(io);
    }
    if (io != 0)
        ((void (__thiscall*)(void*))(((void**)*(void**)io)[8 / 4]))(io);
    return result;
}

// @ 0x008ddc10
extern "C" char FUN_008ddc10(int a1, void* out, void* pKey)
{
    wchar_t buf[0x104];
    if (pKey == 0)
        return 0;
    if (((int (__thiscall*)(void*))(((void**)*(void**)pKey)[0x0c / 4]))(pKey) != 0x34728492)
        return 0;
    if (!((char (__thiscall*)(void*, int, void*))(((void**)*(void**)pKey)[0x64 / 4]))(pKey, a1, buf))
        return 0;
    ((Str*)out)->append(buf);
    return 1;
}

// @ 0x008ddc80
namespace EA {
namespace ResourceMan {
void DefaultCreateNameFromKey(Key const & key, eastl::basic_string<wchar_t, eastl::allocator> & out, Manager const * a3, Database const * a4, wchar_t const * a5)
{
    (void)key; (void)out; (void)a3; (void)a4; (void)a5;
}
}
}  // namespace EA::ResourceMan
