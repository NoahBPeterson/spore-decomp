// @ 0x00766250  ResE destructor: release the raster at +0x18 back to the pool
#include "types.h"

// ---------------------------------------------------------------------------
// out-of-slice callees (relocation targets); both take `this` in ecx
// ---------------------------------------------------------------------------
struct RasterX { void Destroy(); };                 // 0x011eff60
struct RObjPool { void Free(void* p); };            // 0x09276c0
extern RObjPool* g_pool_16c8b44;                    // 0x016c8b44

// The base's destructor is virtual: that is what gives the derived destructor
// its EH frame (the frame's state is set before the release and the vptr is
// reset on unwind), and the derived destructor is virtual in turn.
struct BaseE {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9(); virtual void eA(); virtual void eB();
    virtual ~BaseE() {}
    int mRef;                 // +0x4
    int k8, kc, k10, k14;     // +0x8..+0x14
};
struct ResE : BaseE {
    RasterX* a18;             // +0x18, the raster
    ~ResE();
};
ResE::~ResE() {
    if (a18) {
        a18->Destroy();
        g_pool_16c8b44->Free(a18);
    }
}
