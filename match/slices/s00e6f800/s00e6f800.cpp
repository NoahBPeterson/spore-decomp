// Slice s00e6f800 -- SP cell TU: route a cell toward a cell chosen by handle.
// Flags: /O2 /MD /Gy /TP.
#include "types.h"

struct cObjectPool {
    void* Get(int index);                     // 0x00b72210 (thiscall, ret 4)
};

struct cGameStub {
    char pad0[0x1c];
    cObjectPool mCells;                       // +0x1c
};
extern cGameStub* gspCellGame;                // 0x016b3c04

struct cEntity {
    char pad00[0x4c];
    float mX;                                 // +0x4c
    float mY;                                 // +0x50
    float mZ;                                 // +0x54
};

extern "C" void __cdecl FUN_00e6f660(cEntity* self, const float* pos, float dt, float f18,
                                     float f40, unsigned hash, int mode, unsigned char last);

// @ 0x00e6f800
void FUN_00e6f800(cEntity* cell, unsigned handle, float dt, float f18, float f40,
                  unsigned hash, int mode, unsigned char last)
{
    cObjectPool& cells = gspCellGame->mCells;
    cEntity* other = (cEntity*)cells.Get((int)handle);
    FUN_00e6f660(cell, &other->mX, dt, f18, f40, hash, mode, last);
}
