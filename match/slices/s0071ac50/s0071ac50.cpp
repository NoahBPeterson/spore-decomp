// Slice s0071ac50: a single very large (>7 KB) SP::Simulator registration/loader
// routine.  It allocates a SP::Simulator::cCreatureAbility (size 0x58, vtable
// 0x13eb8d0) and walks huge tables.  Optimized module: /O2 /MD /Gy /EHsc /TP.
//
// Partial: only a compiling skeleton is provided; the table walk and allocation
// sequence are not reproduced.
#include "types.h"

void* SpAlloc(unsigned size, const char* area, int a, int b, const char* file, int line); // 0x00f473a0

struct SimAbility {
    void** mpVtbl;      // +0x0
    long   mnRefCount;  // +0x4
    uint32_t mData[0x50];
};

// @ 0x0071ac50
void Sim_RegisterCreatureAbilities_AC50()
{
    SimAbility* p = (SimAbility*)SpAlloc(0x58, "Graphics", 0, 0, 0, 0);
    if (p != 0) {
        p->mpVtbl = 0;
        p->mnRefCount = 0;
        for (int i = 0; i < 0x14; ++i)
            p->mData[i] = 0;
    }
}
