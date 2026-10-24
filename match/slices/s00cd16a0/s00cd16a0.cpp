// Slice s00cd16a0 -- cScenarioEditModeInputStrategy destructor (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace Simulator {

struct cNested1c {
    uint32_t mPad00[3];                                      // +0x00 .. +0x0b
    void*    mpValue0c;                                      // +0x0c

    void Release(void* value);                               // 0x00e4b990
};

struct cSub04 {
    uint32_t  mPad00[3];                                     // +0x00 .. +0x0b
    void*     mpValue0c;                                     // +0x0c
    uint32_t  mPad10[3];                                     // +0x10 .. +0x1b
    cNested1c mNested1c;                                     // +0x1c

    void Release(void* value);                               // 0x00b1b830
};

struct cScenarioEditModeInputStrategy {
    void*    mpVtable;                                       // +0x00
    cSub04   mSub;                                           // +0x04

    void* Destroy(uint8_t flags);
};

} // namespace Simulator

extern "C" void operator_delete(void* p);                    // 0x00f47380

// @ 0x00cd1750
void* Simulator::cScenarioEditModeInputStrategy::Destroy(uint8_t flags)
{
    cSub04& sub = mSub;
    cNested1c& nested = sub.mNested1c;
    mpVtable = (void*)0x014771e0;
    nested.Release(nested.mpValue0c);
    sub.Release(sub.mpValue0c);
    if (flags & 1)
        operator_delete(this);
    return this;
}
