// Slice s007ada40 — DXT block mapping, endpoint refinement and small surface
// descriptor helpers (0x7ada40..0x7ae9f0).
// Optimized region: /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// @ 0x007ae920
// Initialise a scanline descriptor from a starting point and two extents.
class Span {
public:
    void Init(int x, int y, int dx, int dy, int extra);
    int mX;         // +0x00
    int mY;         // +0x04
    int mXEnd;      // +0x08
    int mYEnd;      // +0x0c
    int mExtra;     // +0x10
    int mM1;        // +0x14
    int mM2;        // +0x18
    uint8_t mFlag;  // +0x1c
};

void Span::Init(int x, int y, int dx, int dy, int extra)
{
    int* p = (int*)this;
    p[0] = x;
    p[2] = x + dx;
    p[1] = y;
    p[3] = y + dy;
    p[4] = extra;
    p[5] = -1;
    p[6] = -1;
    ((uint8_t*)this)[0x1c] = 0;
}

// ---------------------------------------------------------------------------
// @ 0x007ae960
class InnerData {
public:
    char    mPad00[0x1c];
    uint8_t mFlag;      // +0x1c
};
class FlagHolder {
public:
    uint8_t IsSet();
    InnerData* mpData;  // +0x00
};

uint8_t FlagHolder::IsSet()
{
    return mpData->mFlag;
}

// ---------------------------------------------------------------------------
// @ 0x007ae9f0
class DxtBase1 { public: virtual void v1(); };
class DxtBase2 { public: virtual void v2(); };
class DxtRefCount {
public:
    long mCount;
    DxtRefCount() { _InterlockedExchange((volatile long*)&mCount, 0); }
};
class DxtSurface : public DxtBase1, public DxtBase2, public DxtRefCount {
public:
    int mC;    // +0x0c
    int m10;   // +0x10
    int m14;   // +0x14
    int m18;   // +0x18
    int m1c;   // +0x1c
    int m20;   // +0x20
    int m24;   // +0x24
    DxtSurface();
};

DxtSurface::DxtSurface() : mC(0), m10(0), m24(0)
{
}

// @ 0x007ae980
extern "C" void FUN_007ae980(void)
{
    // PARTIAL: DXT surface dtor (two refcounted member releases) skeleton.
}

// ---------------------------------------------------------------------------
// @ 0x007ada40
extern "C" void mapblock(void)
{
    // PARTIAL: map a 4x4 source block to a DXT block skeleton.
}

// @ 0x007adcf0
extern "C" void FUN_007adcf0(void)
{
    // PARTIAL: MMX nearest-endpoint block mapper skeleton.
}

// @ 0x007ade70
extern "C" void rtrymapblock(void)
{
    // PARTIAL: recursive block mapper skeleton.
}

// @ 0x007ae0b0
extern "C" void rbtrymapblock(void)
{
    // PARTIAL: recursive block mapper (bounded) skeleton.
}

// @ 0x007ae2a0
extern "C" void RefineMinMaxColors(void)
{
    // PARTIAL: endpoint refinement skeleton.
}

// @ 0x007ae5b0
extern "C" void FUN_007ae5b0(void)
{
    // PARTIAL: interleave two rows into a 8-byte DXT3 alpha block.
}

// @ 0x007ae660
extern "C" void InterpolatedAlphaBlock(void)
{
    // PARTIAL: build an interpolated DXT5 alpha block skeleton.
}

// @ 0x007ae840
extern "C" void FUN_007ae840(void)
{
    // PARTIAL: MMX min/max reduction of a 4x4 block skeleton.
}
