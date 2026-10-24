// Slice s013a55c0 -- static initialisers: Simulator behaviour singletons, viewer
// globals, float-vector copies and editor attribute-table registration.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// callees (call targets are relocation-masked by the checker)
// ---------------------------------------------------------------------------
void* FUN_00f473a0(unsigned int, const char*, int, int, const char*, int); // 0x00f473a0 operator_new
void  FUN_013ca8f0(void);                                  // 0x013ca8f0
void  FUN_013ca920(void);                                  // 0x013ca920
extern "C" int atexit(void (__cdecl*)(void));              // 0x011e07ef CRT atexit
extern "C" void* memset(void*, int, unsigned int);         // CRT memset (inlined)

// ---------------------------------------------------------------------------
// placeholder globals: their addresses become relocations, which the checker
// masks, exactly like the absolute addresses the original encodes.
// ---------------------------------------------------------------------------
char  g_vtbl_1499738;      // vtbl of Simulator::cSpaceGameBehaviorAbducted
char  g_vtbl_1499724;      // its second (IUnknown) vtbl
char  g_vtbl_1499810;      // vtbl of Simulator::cSpaceGameBehaviorSlowDeath
char  g_vtbl_1499800;
void* g_16df2f4;           // the singletons
void* g_16df328;

// ---------------------------------------------------------------------------
// behaviour layout (only the offsets this slice touches)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x013a55c0 -- singleton of cSpaceGameBehaviorAbducted
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x013a56b0 -- singleton of cSpaceGameBehaviorSlowDeath
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x013a5880 -- zero four 0x14-byte records at 0x016df3e8, register the dtor
// ---------------------------------------------------------------------------
struct DtorPair {
    uint16_t mA;                     // +0x00
    uint16_t mB;                     // +0x02
    char     _p04[0x10];
};
DtorPair g_pairs_16df3e8[4];

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

// ---------------------------------------------------------------------------
// 0x013a58d0 -- three cViewer globals then the dtor
// ---------------------------------------------------------------------------
struct cViewer {
    char      _p000[0x40];
    cViewer*  FUN_007c3f70();        // 0x007c3f70
};
extern cViewer g_15b7844;
extern cViewer g_15b79b8;
extern cViewer g_15b7b2c;

// @ 0x013a58d0
void FUN_013a58d0(void)
{
    g_15b7844.FUN_007c3f70();
    g_15b79b8.FUN_007c3f70();
    g_15b7b2c.FUN_007c3f70();
    atexit(FUN_013ca920);
}

// ---------------------------------------------------------------------------
// 0x013a5900 -- copy 21 floats from 0x015b7744 into 0x016df428
// ---------------------------------------------------------------------------
float g_f15b7744[21];            // source
float g_f16df428[21];            // destination

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

// ---------------------------------------------------------------------------
// editor attribute-table record (0x3c bytes) and the placeholder addresses it
// is built from
// ---------------------------------------------------------------------------
struct AttrRec {
    const char* mpName;              // +0x00
    void*       mpField;             // +0x04
    int32_t     mFieldOfs;           // +0x08
    int32_t     mUnk0c;              // +0x0c  (left indeterminate, as in the original)
    int32_t     mUnk10;              // +0x10
    int32_t     mUnk14;              // +0x14
    int32_t     mZero18;             // +0x18
    int32_t     mZero1c;             // +0x1c
    void*       mpFn20;              // +0x20
    void*       mpFn24;              // +0x24
    void*       mpFn28;              // +0x28
    void*       mpFn2c;              // +0x2c
    void*       mpFn30;              // +0x30
    void*       mpFn34;              // +0x34
    void*       mpFn38;              // +0x38
};

// field addresses (data) and callbacks (code) referenced by the records
char g_55271b4;  char g_55271ba;  char g_55271c0;  char g_55271c4;
char g_5540e28;  char g_5540e44;  char g_55271c7;  char g_55555c7;
char g_5b83971;  char g_5b83972;  char g_5b83973;  char g_5b83974;
char g_5b83975;  char g_5b83976;  char g_5b83977;  char g_60b5062;
char g_3d840ef;  char g_5b82ced;  char g_5f76c77;
char g_692ca0;   char g_572810;   char g_572840;   char g_693090;
char g_694f00;   char g_b1fbf0;   char g_675ca0;   char g_ac88f0;
char g_6930b0;   char g_694fc0;   char g_acbb80;   char g_ae3470;
char g_ae3490;   char g_c2e4e0;   char g_692fb0;   char g_ae3310;
char g_ac8050;   char g_692ff0;   char g_694ee0;   char g_57cde0;
char g_ac8750;   char g_ac8780;   char g_694fa0;   char g_57ce00;
char g_103c1f0;  char g_c6adc0;   char g_c6c4e0;   char g_103c2c0;
char g_f26ca0;   char g_103c3a0;  char g_c87f80;   char g_c87c00;
char g_c875f0;   char g_c6c390;   char g_bf77d0;   char g_bf1cf0;
char g_bf1d50;   char g_f29650;   char g_103d380;  char g_103b100;
char g_d011e0;   char g_fe4aa0;   char g_103d4a0;  char g_103b460;
char g_103a0a0;  char g_b04e00;   char g_c761c0;   char g_eafe40;

AttrRec g_t15b7dc0[8];
AttrRec g_t15b8140[8];
AttrRec g_t15b8360[3];

// ---------------------------------------------------------------------------
// 0x013a5c20 -- eight records for Simulator::cSpaceGameBehaviorAbducted
// ---------------------------------------------------------------------------
// @ 0x013a5c20
void FUN_013a5c20(void)
{
    AttrRec rec;

    rec.mpName     = "mPoliticalID1";
    rec.mpField    = (void*)&g_55271b4;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 4;
    g_t15b7dc0[0] = rec;

    rec.mpName     = "mPoliticalID2";
    rec.mpField    = (void*)&g_55271ba;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 8;
    g_t15b7dc0[1] = rec;

    rec.mpName     = "mStarID1";
    rec.mpField    = (void*)&g_55271c0;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 0xc;
    g_t15b7dc0[2] = rec;

    rec.mpName     = "mStarID2";
    rec.mpField    = (void*)&g_55271c4;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 0x10;
    g_t15b7dc0[3] = rec;

    rec.mpName     = "mTimeSinceLastUFOMS";
    rec.mpField    = (void*)&g_5540e28;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 0x1c;
    g_t15b7dc0[4] = rec;

    rec.mpName     = "mTimeSinceLastSimMS";
    rec.mpField    = (void*)&g_5540e44;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 0x20;
    g_t15b7dc0[5] = rec;

    rec.mpName     = "mTradeRouteProgress";
    rec.mpField    = (void*)&g_55271c7;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_ac88f0;
    rec.mpFn2c     = (void*)&g_6930b0;
    rec.mpFn30     = (void*)&g_694fc0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_acbb80;
    rec.mFieldOfs  = 0x14;
    g_t15b7dc0[6] = rec;

    rec.mpName     = "mRouteLength";
    rec.mpField    = (void*)&g_55555c7;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_ac88f0;
    rec.mpFn2c     = (void*)&g_6930b0;
    rec.mpFn30     = (void*)&g_694fc0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_acbb80;
    rec.mFieldOfs  = 0x24;
    g_t15b7dc0[7] = rec;
}

// ---------------------------------------------------------------------------
// 0x013a6f80 -- eight records for Simulator::cSpaceGameBehaviorSlowDeath
// ---------------------------------------------------------------------------
// @ 0x013a6f80
void FUN_013a6f80(void)
{
    AttrRec rec;

    rec.mpName     = "planetKey";
    rec.mpField    = (void*)&g_5b83971;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 0xc;
    g_t15b8140[0] = rec;

    rec.mpName     = "lifetime";
    rec.mpField    = (void*)&g_5b83972;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_ae3470;
    rec.mpFn28     = (void*)&g_ae3490;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_ae3310;
    rec.mpFn38     = (void*)&g_ac8050;
    rec.mFieldOfs  = 0x10;
    g_t15b8140[1] = rec;

    rec.mpName     = "spiceBought";
    rec.mpField    = (void*)&g_5b83973;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_692ff0;
    rec.mpFn30     = (void*)&g_694ee0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_57cde0;
    rec.mFieldOfs  = 0x30;
    g_t15b8140[2] = rec;

    rec.mpName     = "mbDirty";
    rec.mpField    = (void*)&g_60b5062;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_ac8750;
    rec.mpFn28     = (void*)&g_ac8780;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694fa0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_57ce00;
    rec.mFieldOfs  = 0x5c;
    g_t15b8140[3] = rec;

    rec.mpName     = "mSpiceID";
    rec.mpField    = (void*)&g_5b83974;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_103c1f0;
    rec.mpFn28     = (void*)&g_c6adc0;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_c6c4e0;
    rec.mFieldOfs  = 0x60;
    g_t15b8140[4] = rec;

    rec.mpName     = "mSpiceCost";
    rec.mpField    = (void*)&g_5b83975;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_103c2c0;
    rec.mpFn28     = (void*)&g_f26ca0;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_103c3a0;
    rec.mFieldOfs  = 0x9c;
    g_t15b8140[5] = rec;

    rec.mpName     = "mNPCInventory";
    rec.mpField    = (void*)&g_5b83976;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_c87f80;
    rec.mpFn28     = (void*)&g_c87c00;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_c875f0;
    rec.mpFn38     = (void*)&g_c6c390;
    rec.mFieldOfs  = 0x34;
    g_t15b8140[6] = rec;

    rec.mpName     = "mNPCInventoryAges";
    rec.mpField    = (void*)&g_5b83977;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_bf77d0;
    rec.mpFn28     = (void*)&g_bf1cf0;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_bf1d50;
    rec.mpFn38     = (void*)&g_f29650;
    rec.mFieldOfs  = 0x48;
    g_t15b8140[7] = rec;
}

// ---------------------------------------------------------------------------
// 0x013a72b0 -- three records for Simulator::cSpaceGameBehaviorTrade
// ---------------------------------------------------------------------------
// @ 0x013a72b0
void FUN_013a72b0(void)
{
    AttrRec rec;

    rec.mpName     = "mRareMap";
    rec.mpField    = (void*)&g_3d840ef;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_103d380;
    rec.mpFn28     = (void*)&g_103b100;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_d011e0;
    rec.mpFn38     = (void*)&g_fe4aa0;
    rec.mFieldOfs  = 0xa0;
    g_t15b8360[0] = rec;

    rec.mpName     = "mNPCStore";
    rec.mpField    = (void*)&g_5b82ced;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_103d4a0;
    rec.mpFn28     = (void*)&g_103b460;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_103a0a0;
    rec.mpFn38     = (void*)&g_c6c390;
    rec.mFieldOfs  = 0x48;
    g_t15b8360[1] = rec;

    rec.mpName     = "mNewlyAvailableCommodities";
    rec.mpField    = (void*)&g_5f76c77;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_b04e00;
    rec.mpFn28     = (void*)&g_c761c0;
    rec.mpFn2c     = (void*)&g_c2e4e0;
    rec.mpFn30     = (void*)&g_692fb0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_eafe40;
    rec.mFieldOfs  = 0xe4;
    g_t15b8360[2] = rec;
}