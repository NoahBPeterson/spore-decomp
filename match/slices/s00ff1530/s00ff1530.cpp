// Slice s00ff1530 - SporeApp 0x00ff1530
// Grow a vector of 0x38-byte ornament records (same record as cOrnamentDataA in
// the s00ff11c0 / s00ff1290 slices) so that it can hold n elements: allocate the
// new block, range-copy the live elements into it, free the old block, then fix
// up begin/end/capacity.  Nothing is constructed past the old end (a reserve).
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <stddef.h>
#include <new>

typedef unsigned int uint32;

struct cOrnamentTail {
    float mF0c;                    // 0x0c
    float mF10;                    // 0x10
    float mF14;                    // 0x14
    float mF18;                    // 0x18
    float mF1c;                    // 0x1c
    int   mField20;                // 0x20
    bool  mFlag24;                 // 0x24
    bool  mFlag25;                 // 0x25
    int   mField28;                // 0x28
    int   mField2c;                // 0x2c
    int   mField30;                // 0x30
    int   mField34;                // 0x34
};

// 0x38-byte ornament record (see cOrnamentDataA::operator= at 0x00ff11c0).
struct cOrnamentDataA {
    float mF00;                    // 0x00
    float mF04;                    // 0x04
    float mF08;                    // 0x08
    cOrnamentTail mTail;           // 0x0c
};

// eastl allocator helpers used by the retail vector template.
void* AllocateBlocks(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void FreeArray(void* p);                                                                          // 0x00f47380
cOrnamentDataA* CopyOrnamentRange(cOrnamentDataA* first, cOrnamentDataA* last, cOrnamentDataA* dest); // 0x00ff1290

static const char* const kAllocName = "cOrnamentDataA";
static const char* const kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

struct OrnamentVector {
    cOrnamentDataA* mpBegin;       // +0x00
    cOrnamentDataA* mpEnd;         // +0x04
    cOrnamentDataA* mpCapacity;    // +0x08

    void reserve(uint32_t n);
};

// @ 0x00ff1530
void OrnamentVector::reserve(uint32_t n)
{
    if (n <= (uint32_t)(mpCapacity - mpBegin))
        return;

    cOrnamentDataA* p = n ? (cOrnamentDataA*)AllocateBlocks(n * sizeof(cOrnamentDataA),
                                                            kAllocName,
                                                            0, 0,
                                                            kAllocFile,
                                                            209)
                          : 0;

    CopyOrnamentRange(mpBegin, mpEnd, p);

    if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
        FreeArray(mpBegin);

    uint32 oldSize = (uint32)(mpEnd - mpBegin);
    mpBegin = p;
    mpEnd = p + oldSize;
    mpCapacity = p + n;
}
