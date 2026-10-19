// src/game/UTFSpore_Win32/Socket_imp.cpp -- migrated from slice(s) s0094ea80 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Socket_imp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/SSL/FileSystemDefault.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/SSL/SSLManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int   __cdecl strcmp(const char*, const char*);
#include <intrin.h>
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchangeAdd, _InterlockedExchange)
#pragma intrinsic(strcmp)

// ---- items of slice s0094ea80 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RefObj94 { virtual void Destroy(int); int mnRefCount; };
// ---- items of slice s0094ea80 end

// @ 0x0094ea80
int __fastcall RefCount_AddRef_M4(int* p)
{
    return _InterlockedIncrement((volatile long*)(p - 1));
}

// @ 0x0094ea90
int __fastcall RefCount_Release_M8(int* self)
{
    RefObj94* p = (RefObj94*)(self - 2);
    int n = _InterlockedExchangeAdd((volatile long*)&p->mnRefCount, -1);
    n--;
    if (n == 0) {
        _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
        if (p)
            p->Destroy(1);
    }
    return n;
}
