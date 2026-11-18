// @ 0x00cf98b0 SP::cCivModeStrategy::cCivModeStrategy
// Reconstructed from the retail constructor; layout follows the destructor at
// 0x00cf9a80 (same object: five vtable words, array members at 0x2c/0x40/0x54,
// EA::Stopwatch at 0xc8, cGonzagoTimer at 0x128, open flag at 0x148).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// Vtable images stored by the constructor (base class, then most-derived).
extern void* g_vtbl_01477530;   // 0x01477530
extern void* g_vtbl_014426a0;   // 0x014426a0
extern void* g_vtbl_013eb384;   // 0x013eb384
extern void* g_vtbl_01478a28;   // 0x01478a28
extern void* g_vtbl_014789d8;   // 0x014789d8
extern void* g_vtbl_014789d0;   // 0x014789d0
extern void* g_vtbl_014789b4;   // 0x014789b4
extern void* g_vtbl_014789a4;   // 0x014789a4

struct cCivModeStrategy;
extern cCivModeStrategy* gCivModeStrategy;   // 0x0169d2c8

// Subobject constructors, called through their item at the retail offset.
struct cGonzagoSubsystem {          // 0x00b5b960
    void Construct();
};
struct cLocalInputState {           // 0x00697960
    void Construct();
};
struct EAStopwatch {                // 0x0093a560
    void Construct(int units, bool useRdtsc);
};
struct cGonzagoTimer {              // 0x00b63890
    void Construct();
};

struct cCivModeStrategy {
    void* mpVtbl0;                  // +0x000
    void* mpVtbl4;                  // +0x004  cGonzagoSubsystem
    void* mpVtbl8;                  // +0x008
    u8    mPad00c[0x14];            // +0x00c .. +0x01f
    void* mpVtbl20;                 // +0x020
    void* mpVtbl24;                 // +0x024
    u8    mb28;                     // +0x028
    u8    mb29;                     // +0x029
    u8    mb2a;                     // +0x02a
    u8    mb2b;                     // +0x02b
    void* mpArray2c;                // +0x02c
    u32   m30;                      // +0x030
    u32   m34;                      // +0x034
    u32   m38;                      // +0x038
    u32   m3c;                      // +0x03c
    void* mpArray40;                // +0x040
    u32   m44;                      // +0x044
    u32   m48;                      // +0x048
    u32   m4c;                      // +0x04c
    u32   m50;                      // +0x050
    void* mpArray54;                // +0x054
    u32   m58;                      // +0x058
    u32   m5c;                      // +0x05c
    u32   m60;                      // +0x060
    u32   m64;                      // +0x064
    u8    mSub68[0x48];             // +0x068  cLocalInputState
    u8    mb0b0;                    // +0x0b0
    u8    mPad0b1[3];               // +0x0b1
    u32   m0b4;                     // +0x0b4
    u32   m0b8;                     // +0x0b8
    u32   m0bc;                     // +0x0bc
    u32   m0c0;                     // +0x0c0
    u8    mPad0c4[4];               // +0x0c4
    u8    mStopwatchC8[0x18];       // +0x0c8  EA::Stopwatch
    u8    mb0e0;                    // +0x0e0
    u8    mPad0e1[3];               // +0x0e1
    u32   m0e4;                     // +0x0e4
    u32   m0e8;                     // +0x0e8
    u32   m0ec;                     // +0x0ec
    u8    mb0f0;                    // +0x0f0
    u8    mb0f1;                    // +0x0f1
    u16   mPad0f2;                  // +0x0f2
    u32   m0f4;                     // +0x0f4
    u32   m0f8;                     // +0x0f8
    u8    mb0fc;                    // +0x0fc
    u8    mPad0fd[3];               // +0x0fd
    u32   m100;                     // +0x100
    u32   m104;                     // +0x104
    u32   m108;                     // +0x108
    u32   m10c;                     // +0x10c
    u32   m110;                     // +0x110
    u32   m114;                     // +0x114
    u32   m118;                     // +0x118
    u32   m11c;                     // +0x11c
    u8    m120;                     // +0x120
    u8    m121;                     // +0x121
    u8    mb122;                    // +0x122
    u8    mb123;                    // +0x123
    u8    mb124;                    // +0x124
    u8    mb125;                    // +0x125
    u16   mPad126;                  // +0x126
    u8    mTimer128[0x20];          // +0x128  SP::cGonzagoTimer
    u8    mb148;                    // +0x148

    cCivModeStrategy();
};

// @ 0x00cf98b0
cCivModeStrategy::cCivModeStrategy()
{
    mpVtbl0 = &g_vtbl_01477530;
    ((cGonzagoSubsystem*)&mpVtbl4)->Construct();
    mpVtbl20 = &g_vtbl_014426a0;
    mpVtbl24 = &g_vtbl_013eb384;
    // The base subobject vtable stores above are overwritten with this class's
    // vtables below; keep both writes (retail keeps them).
    _ReadWriteBarrier();

    mpVtbl0  = &g_vtbl_01478a28;
    mpVtbl4  = &g_vtbl_014789d8;
    mpVtbl8  = &g_vtbl_014789d0;
    mpVtbl20 = &g_vtbl_014789b4;
    mpVtbl24 = &g_vtbl_014789a4;

    mb28 = 0;
    mb29 = 0;
    mb2a = 0;
    mb2b = 0;
    mpArray2c = 0;
    m30 = 0;
    m34 = 0;
    mpArray40 = 0;
    m44 = 0;
    m48 = 0;
    _ReadWriteBarrier();
    mpArray54 = 0;
    m58 = 0;
    m5c = 0;

    ((cLocalInputState*)&mSub68)->Construct();

    mb0b0 = 0;
    _ReadWriteBarrier();
    m0b4 = 0;
    m0b8 = 0xffffffffu;
    m0bc = 0xffffffffu;
    m0c0 = 0;

    ((EAStopwatch*)&mStopwatchC8)->Construct(4, false);

    mb0e0 = 0;
    m0e4 = 0xffffffffu;
    m0e8 = 0;
    m0ec = 0;
    mb0f0 = 0;
    mb0f1 = 0;
    m0f4 = 0;
    m0f8 = 0xffffffffu;
    mb0fc = 0;

    m100 = 0;
    m104 = 0;
    m108 = 0;
    m10c = 0;
    _ReadWriteBarrier();
    m110 = 0;
    m114 = 0;
    m118 = 0;
    m11c = 0;

    mb122 = 0;
    mb123 = 0;
    mb124 = 0;
    mb125 = 0;

    ((cGonzagoTimer*)&mTimer128)->Construct();

    mb148 = 0;
    gCivModeStrategy = this;
}
