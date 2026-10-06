// Slice s00b159e0 (batch bfs1) — shared types.
// Module "Spore"; SP::cTerrainCameraController mouse/scroll handlers (retail field
// offsets taken from the disassembly; cLocalInputState sits at +0x31c in retail).

#pragma once
#include "types.h"

struct cLocalInputState
{
    void Reset();
    bool OnKeyDown(int, int);
    bool OnMouseDown(int, float, float, int);
    bool OnMouseUp(int, float, float, int);
    bool OnMouseWheel(int delta, float x, float y, int flag);
};

struct cTerrainCameraController
{
    char  pad_00[0x13];
    bool  m13;              // +0x13
    char  pad_14[0x114 - 0x14];
    float m114;             // +0x114
    char  pad_118[0x294 - 0x118];
    float m294;             // +0x294
    char  pad_298[0x2a0 - 0x298];
    float m2a0;             // +0x2a0
    char  pad_2a4[0x31c - 0x2a4];
    cLocalInputState mInput;   // +0x31c

    void FUN_00b148c0(float, float, float, float);   // out-of-slice helper
    void FUN_00b159e0(int);                          // @ 0x00b159e0
    void FUN_00b15a20(unsigned);                     // @ 0x00b15a20
    bool FUN_00b15a80(int, float, float, int);       // @ 0x00b15a80
    void FUN_00b15b00();                             // @ 0x00b15b00
    void FUN_00b16270();                             // @ 0x00b16270
};

// Free helpers in this slice.
void FUN_00b16450(float* v, int* list);              // @ 0x00b16450
void FUN_00b16490(float* v, float add);              // @ 0x00b16490
bool FUN_00b16520(int* world, float* a, float* b, bool flag, float* out);  // @ 0x00b16520