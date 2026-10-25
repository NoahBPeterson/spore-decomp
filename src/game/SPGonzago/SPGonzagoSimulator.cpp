// src/game/SPGonzago/SPGonzagoSimulator.cpp -- migrated from slice(s) s008337d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGonzagoSimulator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGonzagoSimulator.h"

// ---- items of slice s008337d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void** VT(void* o) { return *(void***)o; }
// ---- items of slice s008337d0 end

// @ 0x00834200
int SP::cGonzagoSimulator::Release()
{
    int n = *(volatile int*)&mRefCount;
    n += -1;
    *(volatile int*)&mRefCount = n;
    if (n == 0) {
        *(volatile int*)&mRefCount = 1;
        ((void (__thiscall*)(void*, int))VT(this)[0 / 4])(this, 1);
        n = 0;
    }
    return n;
}
