#include "game/types.h"

struct Obj_0088b9a0 {
    uint8_t pad00[9];
    bool mFlag9; // +0x09
    bool mFlagA; // +0x0a

    // @ 0x0088b9a0
    void SetFlag(int which, int val);
};

// @ 0x0088b9a0
void Obj_0088b9a0::SetFlag(int which, int val)
{
    if (which == 1) {
        mFlag9 = (val != 0);
    } else if (which == 2) {
        mFlagA = (val != 0);
    }
}
