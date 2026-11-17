// Forwarder (0x00ac8530): if the member object at +0xa4 exists, pass the argument on to it (0xd59520, tail call).
#include "game/types.h"

struct Child_ac8530 {
    void Call(uint32_t arg);   // 0x00d59520
};
struct Owner_ac8530 {
    char mPad[0xa4];
    Child_ac8530* mpChild;                       // +0xa4
    void Call(uint32_t arg);
};

// @ 0x00ac8530
void Owner_ac8530::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
