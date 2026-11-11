// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// cSolarSystem accessor. Passes the star's type and the caller's index to the helper at 0x00c84c60.
#include "types.h"

struct cStar {
    int GetType(); // 0x00c8b550
};

struct cSolarSystem {
    char mPad00[0x0c];
    cStar* mpStar; // +0x0c

    float FUN_00c84d40(int index);
};

float FUN_00c84c60(int starType, int index); // 0x00c84c60

// @ 0x00c84d40
float cSolarSystem::FUN_00c84d40(int index)
{
    return FUN_00c84c60(mpStar->GetType(), index);
}
