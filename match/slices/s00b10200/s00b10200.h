// Slice s00b10200 (batch bfs1) — shared types.
// Module "Spore".  00b108b0 is named SP::cTerrainCameraController::ReloadZoomProgram
// in the PDB; the other methods operate on the same object (retail field offsets
// are read from the disassembly, since the retail layout differs from the 2008 PDB).

#pragma once
#include "types.h"

// ---------------------------------------------------------------------------
// SP::cTerrainCameraController (retail field offsets from the disassembly).
// ---------------------------------------------------------------------------
struct cTerrainCameraController
{
    char  pad_00[0x18];
    bool  m18;              // +0x18
    char  pad_19[0xb];
    float m24;              // +0x24
    float m28;              // +0x28
    char  pad_2c[4];
    float m30;              // +0x30
    char  pad_34[0x54 - 0x34];
    float m54, m58, m5c;    // +0x54..+0x5c
    char  pad_60[0x6c - 0x60];
    float m6c, m70, m74;    // +0x6c..+0x74
    char  pad_78[0xfc - 0x78];
    bool  mfc, mfd;         // +0xfc,+0xfd
    char  pad_fe[0x108 - 0xfe];
    float m108, m10c, m110, m114, m118, m11c;   // +0x108..+0x11c
    bool  m120, m121;
    char  pad_122[0x124 - 0x122];
    float m124, m128;                            // +0x124,+0x128
    float m12c, m130, m134, m138, m13c, m140;   // +0x12c..+0x140
    bool  m144, m145;
    char  pad_146[0x148 - 0x146];
    float m148, m14c;                            // +0x148,+0x14c
    float m150, m154, m158, m15c, m160, m164;   // +0x150..+0x164
    char  pad_168[0x290 - 0x168];
    float m290;                                  // +0x290
    float m294, m298, m29c, m2a0, m2a4;          // +0x294..+0x2a4
    char  pad_2a8[0x2ac - 0x2a8];
    float m2ac, m2b0, m2b4;                      // +0x2ac..+0x2b4
    char  pad_2b8[0x304 - 0x2b8];
    bool  m304;             // +0x304
    char  pad_305[0x35c - 0x305];

    float* FUN_00b10200();                               // @ 0x00b10200
    float* FUN_00b10260();                               // @ 0x00b10260
    void   FUN_00b102c0();                               // @ 0x00b102c0
    void   FUN_00b10340(float, float, float);            // @ 0x00b10340
    void   FUN_00b10470(float);                          // @ 0x00b10470
    void   FUN_00b104c0(float);                          // @ 0x00b104c0
    void   FUN_00b10540(float, float, float);            // @ 0x00b10540
    void   FUN_00b10760(float, float, float);            // @ 0x00b10760
    void   ReloadZoomProgram();                          // @ 0x00b108b0
    void   FUN_00b10a90(float);                          // @ 0x00b10a90
    void   FUN_00b10c40(bool);                           // @ 0x00b10c40
};

// Reset helper used at 0x00b10de0 (Hermite spline / interpolation scratch block).
struct HermiteFloatScratch
{
    char  pad_00[8];
    float m08;              // +0x08
    char  pad_0c[0x2c - 0x0c];
    float m2c, m30, m34, m38;   // +0x2c..+0x38
    float m3c, m40, m44, m48;   // +0x3c..+0x48
    char  pad_4c[0x5c - 0x4c];
    float m5c, m60, m64, m68;   // +0x5c..+0x68
    char  pad_6c[4];

    void FUN_00b10de0(float);                            // @ 0x00b10de0
};

// @ 0x00b10e50 (free __cdecl): one Hermite/Catmull-Rom spline segment.
void FUN_00b10e50(float* out, float* p2, float* p3, float* p4, float* p5, float t, float s);