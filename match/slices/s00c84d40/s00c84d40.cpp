// Slice s00c84d40: SP::cSolarSystem orbit-radius accessor.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// The +0x0c member forwards (through its +0x48 object) to the actual
// solar-system accessor at 0x00801920.
// 0x00801920: reads [this+0x48] (tail-called by 0x00c8b550).
int __cdecl GetIndex(void* pThis, int index);   // 0x00801920

class cPlanetHandle_00c84d40 {
public:
    void* mp48;                       // +0x48
    // 0x00c8b550: reads [this+0x48] and tail-calls 0x00801920, `ret 4`.
    int GetIndex(int index);
};
int cPlanetHandle_00c84d40::GetIndex(int index) {
    return ::GetIndex(this, index);
}

class cSolarSystem {
public:
    char  mPad00[0x0c];               // +0x00
    cPlanetHandle_00c84d40* mp0c;     // +0x0c
    float GetStarRadius(int index);   // 0x00c84d40
};

// cached per-index radius (0x00c84c60, 213 bytes)
float FUN_00c84c60(int index);        // 0x00c84c60

// @ 0x00c84d40
float cSolarSystem::GetStarRadius(int index) {
    return FUN_00c84c60(mp0c->GetIndex(index));
}
