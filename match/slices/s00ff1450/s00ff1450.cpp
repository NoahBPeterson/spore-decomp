// Slice s00ff1450: a 4-byte-element vector growth (reserve) — capacity check,
// allocator call through EA's 6-argument operator new, element-by-element copy
// into the new block, and the free of the old block behind its allocation header.
//
// Layouts are retail offsets read off the disassembly; field names are Claude-coined.
// Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;

// =========================================================================== free callees
void* __cdecl EAAllocate(uint size, const char* name, int, int, const char* file, int line); // 0x00f473a0
void  __cdecl operator_delete__(void* p);                            // 0x00f47380

// =========================================================================== little classes
struct HandleVec {                                                   // 3 pointers, 4-byte elements
    int* mpBegin_00;                                                 // +0x00
    int* mpEnd_04;                                                   // +0x04
    int* mpCap_08;                                                   // +0x08
    void reserve(unsigned newCap);
};

// @ 0x00ff1450
void HandleVec::reserve(unsigned newCap)
{
    if (newCap <= (unsigned)(mpCap_08 - mpBegin_00)) return;
    int* p = newCap ? (int*)EAAllocate(newCap * 4, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                     : 0;
    int* d = p;
    int* end = mpEnd_04;
    for (int* q = mpBegin_00; q != end; ++q, ++d)
        if (d) *d = *q;
    if (mpBegin_00 && mpBegin_00[-1] != 0)
        operator_delete__(mpBegin_00);
    int n = mpEnd_04 - mpBegin_00;
    mpBegin_00 = p;
    mpEnd_04 = p + n;
    mpCap_08 = p + newCap;
}
