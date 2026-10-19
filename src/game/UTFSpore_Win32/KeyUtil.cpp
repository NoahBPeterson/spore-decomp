// src/game/UTFSpore_Win32/KeyUtil.cpp -- migrated from slice(s) s008de020 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/KeyUtil.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "EA/ResourceMan/Manager.h"
#include "EA/Thread/Mutex.h"

// ---- items of slice s008de020 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
typedef unsigned long long uint64;
// ---- items of slice s008de020 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int); // 0x13cc4a8 IAT
extern "C" uint64 __cdecl StrtoU6416(const wchar_t*, wchar_t**, int);                            // 0x0092d710

// @ 0x008de0c0
namespace EA {
namespace ResourceMan {
bool ReadKey(wchar_t const * pString, Key & pKey)
{
    wchar_t* pEnd;
    pKey.mType = (uint32)wcstoul(pString, &pEnd, 16);
    if (*pEnd != L':') return false;
    pKey.mGroup = (uint32)wcstoul(pEnd + 1, &pEnd, 16);
    if (*pEnd != L':') return false;
    uint64 v = StrtoU6416(pEnd + 1, &pEnd, 16);
    wchar_t* pStart = pEnd;
    uint32 lo = (uint32)v;
    uint32 hi = (uint32)(v >> 32);
    if (*pEnd == 0) { pKey.mInstance = lo; return true; }
    if (*pEnd == L'\'' && hi == 0) {
        lo = (uint32)wcstoul(pEnd + 1, &pEnd, 16);
        if ((((int)pEnd - (int)pStart) & 0xfffffffe) != 0x12) return false;
    }
    if (*pEnd == 0 || *pEnd == L' ') { pKey.mInstance = lo; return true; }
    return false;
}
}
}  // namespace EA::ResourceMan
