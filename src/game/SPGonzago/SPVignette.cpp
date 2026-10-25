// src/game/SPGonzago/SPVignette.cpp -- migrated from slice(s) s0042f160 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPVignette.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
#include <string.h>
#pragma intrinsic(_InterlockedIncrement)

// ---- items of slice s0042f160 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};
inline void AssignRef(IRefCounted*& dst, IRefCounted* p)
{
    if (p != dst) {
        IRefCounted* old = dst;
        if (p)
            p->AddRef();
        dst = p;
        if (old)
            old->Release();
    }
}
// ---- items of slice s0042f160 end

// @ 0x0042f530
IRefCounted** CopyPtrs(IRefCounted** first, IRefCounted** last, IRefCounted** result)
{
    for (; first != last; ++result, ++first)
        AssignRef(*result, *first);
    return result;
}
