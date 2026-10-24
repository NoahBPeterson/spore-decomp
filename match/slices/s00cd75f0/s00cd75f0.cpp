// Slice s00cd75f0 -- Simulator/tGameDataVectorT factory (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace Simulator {

struct tGameDataVectorT {
    void*    mpVtable;                                       // +0x00
    uint32_t mValue04;                                       // +0x04
    uint32_t mValue08;                                       // +0x08
    uint32_t mValue0c;                                       // +0x0c
};

} // namespace Simulator

extern "C" void* __cdecl operator_new(uint32_t size, const char* name, int a, int b, int c, int d); // 0x00f473a0
extern "C" void GameDataVectorBaseCtor();                    // 0x00b1e540

// @ 0x00cd7d10
Simulator::tGameDataVectorT* __cdecl CreateGameDataVector()
{
    Simulator::tGameDataVectorT* p = (Simulator::tGameDataVectorT*)operator_new(
        0x18, "Simulator/tGameDataVectorT", 0, 0, 0, 0);
    if (p) {
        ((void (__thiscall*)(void*))GameDataVectorBaseCtor)(p);
        p->mValue04 = 0;
        p->mValue08 = 0;
        p->mValue0c = 0;
        return p;
    }
    return 0;
}
