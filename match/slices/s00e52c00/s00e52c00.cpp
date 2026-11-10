// Slice s00e52c00 -- SP cell-game helper: reset the cell game, then build a 3-vector UI log
// entry (id 0x3e2a3040) from three zero-initialised Vec3s and post a second event (0xd082675a).
// Flags: /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"

extern char* gCellGame_16b3c04;             // 0x016b3c04 SP::cCellGame*
extern "C" void __cdecl FUN_00e3c760();     // 0x00e3c760 reset
extern "C" void __cdecl FUN_00e394f0(unsigned id, void* p2, void* p3, void* p4, void* p5); // 0x00e394f0
extern "C" void __cdecl FUN_00e82cf0(int a, int b, int c); // 0x00e82cf0

struct Vec3 { float x, y, z; };

// @ 0x00e52c00
void FUN_00e52c00()
{
    FUN_00e3c760();
    int local[9] = {0};
    char* level = (char*)*(int*)(gCellGame_16b3c04 + 0x5190);
    FUN_00e394f0(0x3e2a3040, level + 0x10, &local[6], &local[3], &local[0]);
    FUN_00e82cf0(0xd082675a, 1, 1);
}
