// ===========================================================================
// Slice s01399700  (gold6 worker 42)
//
// Functions:
//  0x01399700  $E409  static-init: mUnlockableTools/... property table   (703 B)
//  0x0139bde0  kPosseFlockOffsets init                                    (502 B)
//  0x0139bfe0  posse ring unit-circle table init                          (135 B)
//  0x0139c070  posse ring angle table init                                (101 B)
//  0x0139d420  $E487  static-init: mPlayerInventory/... property table     (584 B)
//  0x0139e870  static-init: mKillerPoliticalID/mRemainingTime table        (214 B)
//  0x013a0c40  $E248  static-init: mScaleFactor/mLookAt* property table    (878 B)
//  0x013a1150  $E225  static-init: mMillisecondsSinceLastUpdate/... table
//
// Module flags: /O2 /MD /Gy /TP.  Float-only functions need /fp:fast; the
// ring table needs /arch:IA32 (x87 fmul + fcos/fsin), the angle table
// /arch:SSE (mulss).  Recorded per row in manifest/nonmatching.
//
// Result: 5 byte-exact (bfe0, c070, d420, e870, 1150); 3 not byte-exact but
// equiv PASS at 100% coverage (99700, bde0, 0c40).
// ===========================================================================
#include "types.h"
#include <math.h>
#include <string.h>

typedef unsigned int uint;

// ---- math intrinsics (x87 fcos/fsin in the original) -----------------------
float cosf(float x);
float sinf(float x);

// ===========================================================================
// Property-table descriptor emitted by the static initialisers.  60 bytes.
// ===========================================================================
struct PropDesc {
    const char* name;    // +0x00
    uint        hash;    // +0x04
    uint        offset;  // +0x08
    uint        f0c;     // +0x0c  (uninitialised in the original)
    uint        f10;     // +0x10  (uninitialised in the original)
    uint        f14;     // +0x14  (uninitialised in the original)
    void*       f18;     // +0x18
    void*       f1c;     // +0x1c
    void*       f20;     // +0x20
    void*       f24;     // +0x24
    void*       f28;     // +0x28
    void*       f2c;     // +0x2c
    void*       f30;     // +0x30
    void*       f34;     // +0x34
    void*       f38;     // +0x38
};

// property-table backing stores (raw addresses used verbatim by the original)
extern PropDesc g_props_99700[7];   // 0x15b5ed8  (stride 0x3c)
extern PropDesc g_props_d420[6];    // 0x15b6618  (stride 0x3c)
extern PropDesc g_props_e870[2];    // 0x15b6a80  (stride 0x3c)
extern PropDesc g_props_0c40[11];   // 0x15b6e28  (stride 0x3c)
extern PropDesc g_props_1150[8];    // 0x15b70d0  (stride 0x3c)

// shared helper function pointers referenced by the descriptors
void FUN_00692ca0();
void FUN_00692fb0();
void FUN_00692ff0();
void FUN_00693090();
void FUN_006930b0();
void FUN_006930f0();
void FUN_00572810();
void FUN_00572840();
void FUN_0057cde0();
void FUN_0057ce00();
void FUN_00694ee0();
void FUN_00694f00();
void FUN_00694fa0();
void FUN_00694fc0();
void FUN_00695010();
void FUN_00675ca0();
void FUN_00ac8050();
void FUN_00aca730();
void FUN_00ac8750();
void FUN_00ac8780();
void FUN_00ac88c0();
void FUN_00ac88f0();
void FUN_00acbb80();
void FUN_00acbba0();
void FUN_00ae3310();
void FUN_00ae3470();
void FUN_00ae3490();
void FUN_00b1fbf0();
void FUN_00b6e3a0();
void FUN_00b6f550();
void FUN_00b6f860();
void FUN_00bca960();
void FUN_00bceb00();
void FUN_00bd1780();
void FUN_00bdd350();
void FUN_00c2e4e0();
void FUN_00c43790();
void FUN_00c51440();
void FUN_00c6adc0();
void FUN_00c6c390();
void FUN_00c6c4e0();
void FUN_00c86560();
void FUN_00c87090();
void FUN_00c875f0();
void FUN_00c87630();
void FUN_00c87c00();
void FUN_00c87f80();
void FUN_00c95780();
void FUN_00fd9e80();
void FUN_00ff3cf0();
void FUN_01002e30();
void FUN_01005360();
void FUN_010061f0();
void FUN_01006220();
void FUN_01006250();
void FUN_01006600();
void FUN_01008680();
void FUN_0100a640();
void FUN_010213f0();
void FUN_01021b70();

// ---- 0139bde0 globals ------------------------------------------------------
extern float g_posseBase;         // 0x15b625c
extern float g_pfo_048;           // 0x16dc048
extern float g_pfo_04c;           // 0x16dc04c
extern float g_pfo_050;           // 0x16dc050
extern float g_pfo_054;           // 0x16dc054
extern float g_pfo_058;           // 0x16dc058
extern float g_pfo_05c;           // 0x16dc05c
extern float g_pfo_out[15];       // 0x16dc060

extern float g_ring_0;            // 0x16dba24
extern float g_ring_1;            // 0x16dba28
extern float g_ring_2;            // 0x16dba30
extern float g_ring_3;            // 0x16dba34
extern float g_ring_4;            // 0x16dba3c
extern float g_ring_5;            // 0x16dba40
extern float g_ring_6;            // 0x16dba48
extern float g_ring_7;            // 0x16dba4c
extern float g_ring_8;            // 0x16dba54
extern float g_ring_9;            // 0x16dba58

extern float g_ang_0;             // 0x16dc0d4
extern float g_ang_1;             // 0x16dc0d8
extern float g_ang_2;             // 0x16dc0dc
extern float g_ang_3;             // 0x16dc0e0
extern float g_ang_4;             // 0x16dc0e4

extern unsigned char g_didInit;   // 0x16daddc (01399700 sets it to 1)

// ===========================================================================
// 0x01399700  $E409  static-init property table
// ===========================================================================
// @ 0x01399700
void PropTableInit_99700()
{
    PropDesc d;
    d.name = "mUnlockableTools"; d.hash = 0x3851188u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00c87f80;
    d.f28 = (void*)&FUN_00c87c00; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00c875f0;
    d.f38 = (void*)&FUN_00c6c390;
    d.offset = 0x4cu;
    g_props_99700[0] = d;

    d.name = "mUpgradedToolIds"; d.hash = 0x6786ec4u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00c95780;
    d.f28 = (void*)&FUN_00c6adc0; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00c6c4e0;
    d.offset = 0x74u;
    g_props_99700[1] = d;

    d.name = "mpDropCargoTool"; d.hash = 0x61c7e21u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00bceb00;
    d.f28 = (void*)&FUN_00bd1780; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00c87090;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x88u;
    g_props_99700[2] = d;

    d.name = "mpActiveTool"; d.hash = 0x61c7e4au;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00bceb00;
    d.f28 = (void*)&FUN_00bd1780; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00c87090;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x8cu;
    g_props_99700[3] = d;

    d.name = "mpActiveCargoItem"; d.hash = 0x61c7e5du;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00c87630;
    d.f28 = (void*)&FUN_00bd1780; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00c87090;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x90u;
    g_props_99700[4] = d;

    d.name = "mMaxItemCountPerItem"; d.hash = 0x649014bu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00572840; d.f2c = (void*)&FUN_00692ff0;
    d.f30 = (void*)&FUN_00694ee0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_0057cde0;
    d.offset = 0x48u;
    g_props_99700[5] = d;

    d.name = "mbHasAddedItem"; d.hash = 0x68398c2u;
    d.f18 = 0; d.f1c = (void*)&FUN_00ff3cf0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00ac8750;
    d.f28 = (void*)&FUN_00ac8780; d.f2c = (void*)&FUN_00693090;
    d.f30 = (void*)&FUN_00694fa0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_0057ce00;
    d.offset = 0x94u;
    g_props_99700[6] = d;

    g_didInit = 1;
}

// ===========================================================================
// 0x0139bde0  kPosseFlockOffsets init
// ===========================================================================
// @ 0x0139bde0
void PosseFlockOffsetsInit()
{
    float ix = g_pfo_048, iy = g_pfo_04c, iz = g_pfo_050;
    float vx = g_pfo_054, vy = g_pfo_058, vz = g_pfo_05c;

    float ax = ix * 0.5f;
    float ay = iy * 0.5f;
    float az = iz * 0.5f;

    g_pfo_out[0] = vx * 0.4f - ax;
    g_pfo_out[1] = vy * 0.4f - ay;
    g_pfo_out[2] = vz * 0.4f - az;
    g_pfo_out[3] = vx * -0.4f - ax;
    g_pfo_out[4] = vy * -0.4f - ay;
    g_pfo_out[5] = vz * -0.4f - az;
    g_pfo_out[6] = vx * 0.8f - ix;
    g_pfo_out[7] = vy * 0.8f - iy;
    g_pfo_out[8] = vz * 0.8f - iz;
    g_pfo_out[9] = vx * 0.0f - ix;
    g_pfo_out[10] = vy * 0.0f - iy;
    g_pfo_out[11] = vz * 0.0f - iz;
    g_pfo_out[12] = vx * -0.8f - ix;
    g_pfo_out[13] = vy * -0.8f - iy;
    g_pfo_out[14] = vz * -0.8f - iz;
}

// ===========================================================================
// 0x0139bfe0  posse ring unit-circle table
// ===========================================================================
// @ 0x0139bfe0
void PosseRingTableInit()
{
    float b = g_posseBase;
    g_ring_0 = cosf(0.48f * b);
    g_ring_1 = sinf(0.48f * b);
    g_ring_2 = cosf(1.29f * b);
    g_ring_3 = sinf(1.29f * b);
    g_ring_4 = cosf(2.12f * b);
    g_ring_5 = sinf(2.12f * b);
    g_ring_6 = cosf(0.95f * b);
    g_ring_7 = sinf(0.95f * b);
    g_ring_8 = cosf(b * 1.73f);
    g_ring_9 = sinf(b * 1.73f);
}

// ===========================================================================
// 0x0139c070  posse ring angle table
// ===========================================================================
// @ 0x0139c070
void PosseRingAngleInit()
{
    float b = g_posseBase;
    g_ang_0 = b * 2.12f;
    g_ang_1 = b * 1.29f;
    g_ang_2 = b * 0.28f;
    g_ang_3 = b * 1.73f;
    g_ang_4 = b * 0.95f;
}

// ===========================================================================
// 0x0139d420  $E487  static-init property table
// ===========================================================================
// @ 0x0139d420
void PropTableInit_d420()
{
    PropDesc d;
    d.name = "mPlayerInventory"; d.hash = 0x22556eau;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_010061f0;
    d.f28 = (void*)&FUN_00bca960; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b6f550;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x40u;
    g_props_d420[0] = d;

    d.name = "mHighLODPlanetSim"; d.hash = 0x22556f0u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_01006220;
    d.f28 = (void*)&FUN_01006600; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00fd9e80;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x54u;
    g_props_d420[1] = d;

    d.name = "mBadgeManager"; d.hash = 0x22556f1u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_01006250;
    d.f28 = (void*)&FUN_01006600; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00fd9e80;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x70u;
    g_props_d420[2] = d;

    d.name = "mTimeSinceStartedSpaceGame"; d.hash = 0x57a55b9u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00ae3470;
    d.f28 = (void*)&FUN_00ae3490; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00ae3310;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0x90u;
    g_props_d420[3] = d;

    d.name = "mNPC_UFOs"; d.hash = 0x53eb2edu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_01008680;
    d.f28 = (void*)&FUN_00aca730; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b6f860;
    d.f38 = (void*)&FUN_00c6c390;
    d.offset = 0x78u;
    g_props_d420[4] = d;

    d.name = "mPlanetsToUplift"; d.hash = 0x670c962u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_0100a640;
    d.f28 = (void*)&FUN_01002e30; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_01005360;
    d.f38 = (void*)&FUN_00c51440;
    d.offset = 0xdcu;
    g_props_d420[5] = d;
}

// ===========================================================================
// 0x0139e870  static-init property table
// ===========================================================================
// @ 0x0139e870
void PropTableInit_e870()
{
    PropDesc d;
    d.name = "mKillerPoliticalID"; d.hash = 0xb3f2c2a7u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00572840; d.f2c = (void*)&FUN_00693090;
    d.f30 = (void*)&FUN_00694f00; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00675ca0;
    d.offset = 0u;
    g_props_e870[0] = d;

    d.name = "mRemainingTime"; d.hash = 0xa3f2c2a8u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00572840; d.f2c = (void*)&FUN_00693090;
    d.f30 = (void*)&FUN_00694f00; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00675ca0;
    d.offset = 4u;
    g_props_e870[1] = d;
}

// ===========================================================================
// 0x013a0c40  $E248  static-init property table
// ===========================================================================
// @ 0x013a0c40
void PropTableInit_0c40()
{
    PropDesc d;
    d.name = "mScaleFactor"; d.hash = 0x3a212e6u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00ac88f0; d.f2c = (void*)&FUN_006930b0;
    d.f30 = (void*)&FUN_00694fc0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbb80;
    d.offset = 0xbcu;
    g_props_0c40[0] = d;

    d.name = "mLookAtCenter"; d.hash = 0x3a212f4u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00b6e3a0;
    d.f28 = (void*)&FUN_00ac88c0; d.f2c = (void*)&FUN_006930f0;
    d.f30 = (void*)&FUN_00695010; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbba0;
    d.offset = 0x8cu;
    g_props_0c40[1] = d;

    d.name = "mLookAtCurrent"; d.hash = 0x3a21303u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00b6e3a0;
    d.f28 = (void*)&FUN_00ac88c0; d.f2c = (void*)&FUN_006930f0;
    d.f30 = (void*)&FUN_00695010; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbba0;
    d.offset = 0x98u;
    g_props_0c40[2] = d;

    d.name = "mLookAtVelocity"; d.hash = 0x3a21318u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00b6e3a0;
    d.f28 = (void*)&FUN_00ac88c0; d.f2c = (void*)&FUN_006930f0;
    d.f30 = (void*)&FUN_00695010; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbba0;
    d.offset = 0xa4u;
    g_props_0c40[3] = d;

    d.name = "mOffsetCurrent"; d.hash = 0x3a21342u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00b6e3a0;
    d.f28 = (void*)&FUN_00ac88c0; d.f2c = (void*)&FUN_006930f0;
    d.f30 = (void*)&FUN_00695010; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbba0;
    d.offset = 0x68u;
    g_props_0c40[4] = d;

    d.name = "mLastGalacticOffset"; d.hash = 0x684df08u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00b6e3a0;
    d.f28 = (void*)&FUN_00ac88c0; d.f2c = (void*)&FUN_006930f0;
    d.f30 = (void*)&FUN_00695010; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbba0;
    d.offset = 0x74u;
    g_props_0c40[5] = d;

    d.name = "mZoomTarget"; d.hash = 0x3a21345u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00ac88f0; d.f2c = (void*)&FUN_006930b0;
    d.f30 = (void*)&FUN_00694fc0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbb80;
    d.offset = 0xb4u;
    g_props_0c40[6] = d;

    d.name = "mZoomVelocity"; d.hash = 0x3a2135bu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00ac88f0; d.f2c = (void*)&FUN_006930b0;
    d.f30 = (void*)&FUN_00694fc0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbb80;
    d.offset = 0xb8u;
    g_props_0c40[7] = d;

    d.name = "mLastDeltaPhi"; d.hash = 0x22556efu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00ac88f0; d.f2c = (void*)&FUN_006930b0;
    d.f30 = (void*)&FUN_00694fc0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbb80;
    d.offset = 0x80u;
    g_props_0c40[8] = d;
}

// ===========================================================================
// 0x013a1150  $E225  static-init property table
// ===========================================================================
// @ 0x013a1150
void PropTableInit_1150()
{
    PropDesc d;
    d.name = "mMillisecondsSinceLastUpdate"; d.hash = 0x366df4cu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00572840; d.f2c = (void*)&FUN_00692ff0;
    d.f30 = (void*)&FUN_00693090; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_0057cde0;
    d.offset = 0u;
    g_props_1150[0] = d;

    d.name = "mActivePlanet"; d.hash = 0x338a74au;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_010213f0;
    d.f28 = (void*)&FUN_00bdd350; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b6f550;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 4u;
    g_props_1150[1] = d;

    d.name = "mpActiveStar"; d.hash = 0x3598939u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_010213f0;
    d.f28 = (void*)&FUN_00bca960; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b6f550;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 8u;
    g_props_1150[2] = d;

    d.name = "mCurrentContext"; d.hash = 0x366e013u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00572840; d.f2c = (void*)&FUN_00692ff0;
    d.f30 = (void*)&FUN_00693090; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_0057cde0;
    d.offset = 0x10u;
    g_props_1150[3] = d;

    d.name = "mRotationRateFactor"; d.hash = 0x366e045u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00ac88f0; d.f2c = (void*)&FUN_006930b0;
    d.f30 = (void*)&FUN_00694fc0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbb80;
    d.offset = 0x14u;
    g_props_1150[4] = d;

    d.name = "mPlayerEmpire"; d.hash = 0x366e0c2u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00572840; d.f2c = (void*)&FUN_00693090;
    d.f30 = (void*)&FUN_00694f00; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00675ca0;
    d.offset = 0x18u;
    g_props_1150[5] = d;

    d.name = "mTribeCivRelationships"; d.hash = 0x6494431u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_01021b70;
    d.f28 = (void*)&FUN_00bd1780; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00c87090;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0xcu;
    g_props_1150[6] = d;

    d.name = "mPlayerColonies"; d.hash = 0x4f3cd9bu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00c86560;
    d.f28 = (void*)&FUN_00c43790; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b6f860;
    d.f38 = (void*)&FUN_00c6c390;
    d.offset = 0x20u;
    g_props_1150[7] = d;
}
