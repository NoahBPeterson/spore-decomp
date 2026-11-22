// src/game/SPGonzago/SPGonzagoSimulator.cpp -- migrated from slice(s) s00b5b540, s008337d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGonzagoSimulator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGonzagoSimulator.h"

// ---- items of slice s008337d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void** VT(void* o) { return *(void***)o; }
// ---- items of slice s008337d0 end

// ---- items of slice s00b5b540 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00b5b690(int);
extern int* g_1686a18;   // vector begin
extern int* g_1686a1c;   // vector end
namespace SP {
struct RefCountVBase
{
    virtual void OnTick();
    RefCountVBase() : mRefCount(0) {}
    int mRefCount;              // +0x04
};
}
namespace SP {
struct ISerializableObject
{
    virtual void AsInterface();
};
}
namespace SP {
class cGonzagoSimulator_s00b5_b540 : public RefCountVBase, public ISerializableObject
{
public:
    bool mbPaused;              // +0x0c
    bool mbTickPaused;          // +0x0d
    bool mbUnregisterPending;   // +0x0e

    cGonzagoSimulator_s00b5_b540();        // 0x00b5b6c0
};
}
// ---- items of slice s00b5b540 end

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

// @ 0x00b5b690
void FUN_00b5b690(int v)
{
    int* p = g_1686a18;
    for (; p != g_1686a1c && *p != v; ++p) {}
    if (p != g_1686a1c) {
        *p = g_1686a1c[-1];
        --g_1686a1c;
    }
}

// @ 0x00b5b6c0
namespace SP {
cGonzagoSimulator_s00b5_b540::cGonzagoSimulator_s00b5_b540()
{
    mbPaused = false;
    mbTickPaused = false;
    mbUnregisterPending = false;
}
}  // namespace SP
