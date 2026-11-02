// src/game/SPGonzago/_at_01390000.cpp -- migrated from slice(s) s01399700, s0138d560 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01390000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern "C" int atexit(void (__cdecl*)());
extern void FUN_013c9dd0(void);
extern void FUN_013c9e00(void);

// ---- items of slice s0138d560 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int atexit(void (__cdecl*)());
extern void FUN_013c9dd0(void);
extern void FUN_013c9e00(void);
// ---- items of slice s0138d560 end

// ---- items of slice s01399700 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
typedef unsigned int uint;
float cosf(float x);
float sinf(float x);
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
extern PropDesc g_props_e870[2];    // 0x15b6a80  (stride 0x3c)
void FUN_00692ca0();
void FUN_00693090();
void FUN_00572810();
void FUN_00572840();
void FUN_00694f00();
void FUN_00675ca0();
void FUN_00b1fbf0();
// ---- items of slice s01399700 end

// @ 0x01390c90
void init_16c9b8c()
{
    int c = 0x803000;
    *(int*)0x16c9b8c = c;
    *(int*)0x16c9b90 = 0;
}

// @ 0x01390cb0
void init_16c9b94()
{
    int c = 0xe0;
    *(int*)0x16c9b94 = c;
    *(int*)0x16c9b98 = 0;
}

// @ 0x01391740
void init_16ca3d4()
{
    *(int*)0x16ca3d4 = -1;
    *(int*)0x16ca3d8 = -1;
    *(int*)0x16ca3dc = -1;
    *(int*)0x16ca3e0 = -1;
    *(int*)0x16ca3e4 = -1;
    *(int*)0x16ca3e8 = -1;
    *(int*)0x16ca3ec = -1;
    *(int*)0x16ca3f0 = -1;
    *(int*)0x16ca3f4 = -1;
    *(int*)0x16ca3f8 = -1;
    *(int*)0x16ca3fc = -1;
    *(int*)0x16ca400 = -1;
}

// @ 0x01391bc0
void init_16d6d30()
{
    *(int*)0x16d6d30 = 0;
    *(int*)0x16d6d34 = 0;
    *(int*)0x16d6d38 = 0;
    *(int*)0x16d6d3c = 0;
    *(int*)0x16d6d40 = 0;
    *(int*)0x16d6d44 = 0;
    *(int*)0x16d6d48 = 0;
    *(int*)0x16d6d4c = 0;
    *(int*)0x16d6d50 = 0;
    *(int*)0x16d6d54 = 0;
    *(int*)0x16d6d58 = 0;
    *(int*)0x16d6d5c = 0;
    *(int*)0x16d6d60 = 0;
    *(int*)0x16d6d64 = 0;
    *(int*)0x16d6d68 = 0;
    *(int*)0x16d6d6c = 0;
    atexit(&FUN_013c9dd0);
}

// @ 0x01391c20
void init_16d6d70()
{
    *(int*)0x16d6d70 = 0;
    *(int*)0x16d6d74 = 0;
    *(int*)0x16d6d78 = 0;
    *(int*)0x16d6d7c = 0;
    *(int*)0x16d6d80 = 0;
    *(int*)0x16d6d84 = 0;
    *(int*)0x16d6d88 = 0;
    *(int*)0x16d6d8c = 0;
    *(int*)0x16d6d90 = 0;
    *(int*)0x16d6d94 = 0;
    *(int*)0x16d6d98 = 0;
    *(int*)0x16d6d9c = 0;
    *(int*)0x16d6da0 = 0;
    *(int*)0x16d6da4 = 0;
    *(int*)0x16d6da8 = 0;
    *(int*)0x16d6dac = 0;
    atexit(&FUN_013c9e00);
}

// @ 0x013921c0
void init_16d6fa8()
{
    *(float*)0x016d6fa8 = 0.0f;
    *(float*)0x016d6fac = -0.70710678f;
    *(float*)0x016d6fb0 = 0.70710678f;
    *(float*)0x016d6fb4 = 0.70710678f;
    *(float*)0x016d6fb8 = 0.0f;
    *(float*)0x016d6fbc = 0.70710678f;
    *(float*)0x016d6fc0 = 0.0f;
    *(float*)0x016d6fc4 = 0.70710678f;
    *(float*)0x016d6fc8 = 0.70710678f;
    *(float*)0x016d6fcc = -0.70710678f;
    *(float*)0x016d6fd0 = 0.0f;
    *(float*)0x016d6fd4 = 0.70710678f;
    *(float*)0x016d6fd8 = 0.0f;
    *(float*)0x016d6fdc = -0.70710678f;
    *(float*)0x016d6fe0 = -0.70710678f;
    *(float*)0x016d6fe4 = 0.70710678f;
    *(float*)0x016d6fe8 = 0.0f;
    *(float*)0x016d6fec = -0.70710678f;
    *(float*)0x016d6ff0 = 0.0f;
    *(float*)0x016d6ff4 = 0.70710678f;
    *(float*)0x016d6ff8 = -0.70710678f;
    *(float*)0x016d6ffc = -0.70710678f;
    *(float*)0x016d7000 = 0.0f;
    *(float*)0x016d7004 = -0.70710678f;
    *(float*)0x016d7008 = 0.70710678f;
    *(float*)0x016d700c = -0.70710678f;
    *(float*)0x016d7010 = 0.0f;
    *(float*)0x016d7014 = 0.70710678f;
    *(float*)0x016d7018 = 0.0f;
    *(float*)0x016d701c = 0.70710678f;
    *(float*)0x016d7020 = 0.70710678f;
    *(float*)0x016d7024 = 0.70710678f;
    *(float*)0x016d7028 = 0.0f;
    *(float*)0x016d702c = 0.70710678f;
    *(float*)0x016d7030 = 0.0f;
    *(float*)0x016d7034 = -0.70710678f;
    *(float*)0x016d7038 = -0.70710678f;
    *(float*)0x016d703c = -0.70710678f;
    *(float*)0x016d7040 = 0.0f;
    *(float*)0x016d7044 = -0.70710678f;
    *(float*)0x016d7048 = 0.0f;
    *(float*)0x016d704c = 0.70710678f;
    *(float*)0x016d7050 = -0.70710678f;
    *(float*)0x016d7054 = 0.70710678f;
    *(float*)0x016d7058 = 0.0f;
    *(float*)0x016d705c = -0.70710678f;
    *(float*)0x016d7060 = 0.0f;
    *(float*)0x016d7064 = -0.70710678f;
    *(float*)0x016d7068 = -0.70710678f;
    *(float*)0x016d706c = 0.70710678f;
    *(float*)0x016d7070 = 0.0f;
    *(float*)0x016d7074 = -0.0f;
    *(float*)0x016d7078 = 0.70710678f;
    *(float*)0x016d707c = 0.70710678f;
    *(float*)0x016d7080 = 0.70710678f;
    *(float*)0x016d7084 = 0.70710678f;
    *(float*)0x016d7088 = 0.0f;
    *(float*)0x016d708c = 0.0f;
    *(float*)0x016d7090 = 0.70710678f;
    *(float*)0x016d7094 = -0.70710678f;
    *(float*)0x016d7098 = -0.70710678f;
    *(float*)0x016d709c = -0.70710678f;
    *(float*)0x016d70a0 = 0.0f;
    *(float*)0x016d70a4 = 0.0f;
    *(float*)0x016d70a8 = -0.70710678f;
    *(float*)0x016d70ac = 0.70710678f;
    *(float*)0x016d70b0 = 0.70710678f;
    *(float*)0x016d70b4 = -0.70710678f;
    *(float*)0x016d70b8 = 0.0f;
    *(float*)0x016d70bc = 0.0f;
    *(float*)0x016d70c0 = -0.70710678f;
    *(float*)0x016d70c4 = -0.70710678f;
}

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
