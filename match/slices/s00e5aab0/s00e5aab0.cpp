// @ 0x00e5aab0
// cApp (SharedApp) helper: fetch the object held for a handle and copy the
// position vector at its +0x4c into `out` (returns `out`).
#include "game/types.h"

// Element returned by the resource map; the game's record has its position at
// +0x4c (the map call is 0x00b72210, thiscall, ret 4).
struct cElem {
    char pad0[0x4c];
    float pos[3];                          // +0x4c
};

struct ResMap {
    cElem* Get(unsigned int id);
};

struct cApp {
    char pad0[0x1c];
    ResMap* mMap;                          // +0x1c: map subobject, reached via the global
};

extern cApp* gApp;                         // 0x016b3c04

// @ 0x00e5aab0
float* FUN_00e5aab0(float* out, unsigned int handle)
{
    ResMap* map = (ResMap*)((char*)gApp + 0x1c);
    const float* p = map->Get(handle)->pos;
    out[0] = p[0];
    out[1] = p[1];
    out[2] = p[2];
    return out;
}
