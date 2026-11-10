// Slice s0089b010: constructor of a large object with two sub-objects.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
//
// Complete (m0C/m10, both sub-constructors, the 0x370..0x37a block, the three head pointers).
// Remaining difference: retail zeroes the head pointers into a fresh register (`xor eax,eax` before
// m371/m374, then three `mov [esi+0/4/8],eax` after m374), i.e. they are not known to be zero yet at
// that point in the original source; ours reuses ebx (already 0) and schedules the stores earlier.
// Tried: explicit zero init at the top, inlined defaulted base/ctor, assigning from an inline helper,
// from a zero-valued global (adds a load) and via a shared local — all keep the ebx form.
#include "types.h"

extern float g_f_01485720;   // 0x01485720

struct SubA { char pad[0xe0]; void ctor(); };   // 0x0089a570, at +0x14
struct SubB { char pad[0x278]; void ctor(); };  // 0x008941d0, at +0xf8

struct S89B010 {
    void* p0;                       // +0x000
    void* p4;                       // +0x004
    void* p8;                       // +0x008
    int   m0C;                      // +0x00c
    int   m10;                      // +0x010
    SubA  a;                        // +0x014
    uint8_t mF4;                    // +0x0f4
    char  pad_f5[3];
    SubB  b;                        // +0x0f8
    uint8_t m370;                   // +0x370
    uint8_t m371;                   // +0x371
    char  pad_372[2];
    float m374;                     // +0x374
    uint8_t m378;                   // +0x378
    uint8_t m379;                   // +0x379
    uint8_t m37A;                   // +0x37a

    void ctor();
};


// @ 0x0089b010
void S89B010::ctor()
{
    m0C = 0x1e;
    m10 = 0;
    a.ctor();
    mF4 = 1;
    b.ctor();
    float f = g_f_01485720;
    m370 = 0;
    m378 = 0;
    m379 = 0;
    m37A = 0;
    m371 = 1;
    m374 = f;
    p0 = 0;
    p4 = 0;
    p8 = 0;
}
