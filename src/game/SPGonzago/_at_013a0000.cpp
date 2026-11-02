// src/game/SPGonzago/_at_013a0000.cpp -- migrated from slice(s) s013a55c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_013a0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int atexit(void (__cdecl*)(void));              // 0x011e07ef CRT atexit
extern "C" void* memset(void*, int, unsigned int);         // CRT memset (inlined)

// ---- items of slice s013a55c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* FUN_00f473a0(unsigned int, const char*, int, int, const char*, int); // 0x00f473a0 operator_new
void  FUN_013ca8f0(void);                                  // 0x013ca8f0
void  FUN_013ca920(void);                                  // 0x013ca920
extern "C" int atexit(void (__cdecl*)(void));              // 0x011e07ef CRT atexit
extern "C" void* memset(void*, int, unsigned int);         // CRT memset (inlined)
char  g_vtbl_1499738;      // vtbl of Simulator::cSpaceGameBehaviorAbducted
char  g_vtbl_1499724;      // its second (IUnknown) vtbl
char  g_vtbl_1499810;      // vtbl of Simulator::cSpaceGameBehaviorSlowDeath
char  g_vtbl_1499800;
void* g_16df2f4;           // the singletons
void* g_16df328;
struct cGonzagoTimer {               // 0x20 bytes, overlaid list/timer block
    void*  mp00;                     // +0x00  (object +0x78)
    void*  mp04;                     // +0x04  (object +0x7c)
    char   _p08[0x04];               // +0x08
    void*  mp0c;                     // +0x0c  (object +0x84)  intrusive head
    void*  mp10;                     // +0x10  (object +0x88)
    void*  mp14;                     // +0x14  (object +0x8c)
    union {
        uint32_t m18dw;              // +0x18  (object +0x90)
        uint8_t  m18b;
    };
    void*  mp1c;                     // +0x1c  (object +0x94)
    void   ctor();                   // 0x00b63890
};
struct cSpaceGameBehavior {
    void*         mpVtbl;            // +0x00
    void*         mpVtbl2;           // +0x04
    char          _p008[0x74 - 0x08];
    union {
        uint32_t  m74dw;             // +0x74
        uint8_t   m74b;
    };
    cGonzagoTimer mTimer;            // +0x78
    void*         mp98;              // +0x98
    void*         mp9c;              // +0x9c
    void  ctor();                    // 0x00abf320
};
struct IntAlloc {                    // int-typed view of the timer's list head
    int32_t m00;                     // +0x00  (object +0x84)
    int32_t m04;                     // +0x04  (object +0x88)
    int32_t m08;                     // +0x08  (object +0x8c)
    int32_t m0c;                     // +0x0c  (object +0x90)
};
struct DtorPair {
    uint16_t mA;                     // +0x00
    uint16_t mB;                     // +0x02
    char     _p04[0x10];
};
DtorPair g_pairs_16df3e8[4];
struct cViewer {
    char      _p000[0x40];
    cViewer*  FUN_007c3f70();        // 0x007c3f70
};
extern cViewer g_15b7844;
extern cViewer g_15b79b8;
extern cViewer g_15b7b2c;
float g_f15b7744[21];            // source
float g_f16df428[21];            // destination
// ---- items of slice s013a55c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cViewer g_15b7844;
extern cViewer g_15b79b8;
extern cViewer g_15b7b2c;

// @ 0x013a55c0
void FUN_013a55c0(void)
{
    cSpaceGameBehavior* p = (cSpaceGameBehavior*)FUN_00f473a0(
        0xa0, "Simulator/cSpaceGameBehaviorAbducted", 0, 0, 0, 0);

    if (p != 0) {
        p->ctor();
        p->mTimer.mp00 = 0;
        p->mTimer.mp04 = 0;
        p->mpVtbl  = (void*)&g_vtbl_1499738;
        p->mpVtbl2 = (void*)&g_vtbl_1499724;
        p->m74b = 1;
        IntAlloc* a = (IntAlloc*)&p->mTimer.mp0c;
        memset(&a->m04, 0, 0xc);          // clears object +0x88/+0x8c/+0x90
        p->mTimer.mp14 = 0;
        p->mTimer.m18b = 0;
        p->mTimer.mp1c = 0;
        p->mTimer.mp10 = (void*)a;
        a->m00 = (int32_t)a;
        p->mp9c = 0;
        g_16df2f4 = (void*)p;
    } else {
        g_16df2f4 = 0;
    }
}

// @ 0x013a56b0
void FUN_013a56b0(void)
{
    cSpaceGameBehavior* p = (cSpaceGameBehavior*)FUN_00f473a0(
        0xa0, "Simulator", 0, 0, 0, 0);

    if (p != 0) {
        p->ctor();
        p->mpVtbl  = (void*)&g_vtbl_1499810;
        p->mpVtbl2 = (void*)&g_vtbl_1499800;
        p->m74dw = 0;
        p->mTimer.ctor();
        p->mp98 = 0;
        g_16df328 = (void*)p;
    } else {
        g_16df328 = 0;
    }
}

// @ 0x013a5880
void FUN_013a5880(void)
{
    g_pairs_16df3e8[0].mA = 0;
    g_pairs_16df3e8[0].mB = 0;
    g_pairs_16df3e8[1].mA = 0;
    g_pairs_16df3e8[1].mB = 0;
    g_pairs_16df3e8[2].mA = 0;
    g_pairs_16df3e8[2].mB = 0;
    g_pairs_16df3e8[3].mA = 0;
    g_pairs_16df3e8[3].mB = 0;
    atexit(FUN_013ca8f0);
}

// @ 0x013a58d0
void FUN_013a58d0(void)
{
    g_15b7844.FUN_007c3f70();
    g_15b79b8.FUN_007c3f70();
    g_15b7b2c.FUN_007c3f70();
    atexit(FUN_013ca920);
}

// @ 0x013a5900
void FUN_013a5900(void)
{
    g_f16df428[0]  = g_f15b7744[0];
    g_f16df428[1]  = g_f15b7744[1];
    g_f16df428[2]  = g_f15b7744[2];
    g_f16df428[3]  = g_f15b7744[3];
    g_f16df428[4]  = g_f15b7744[4];
    g_f16df428[5]  = g_f15b7744[5];
    g_f16df428[6]  = g_f15b7744[6];
    g_f16df428[7]  = g_f15b7744[7];
    g_f16df428[8]  = g_f15b7744[8];
    g_f16df428[9]  = g_f15b7744[9];
    g_f16df428[10] = g_f15b7744[10];
    g_f16df428[11] = g_f15b7744[11];
    g_f16df428[12] = g_f15b7744[12];
    g_f16df428[13] = g_f15b7744[13];
    g_f16df428[14] = g_f15b7744[14];
    g_f16df428[15] = g_f15b7744[18];
    g_f16df428[16] = g_f15b7744[19];
    g_f16df428[17] = g_f15b7744[20];
    g_f16df428[18] = g_f15b7744[15];
    g_f16df428[19] = g_f15b7744[16];
    g_f16df428[20] = g_f15b7744[17];
}
