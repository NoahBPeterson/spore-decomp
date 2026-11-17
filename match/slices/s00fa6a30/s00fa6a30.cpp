// Forwarder (0x00fa6a30): if the member object at +0x8 exists, pass the argument on to it (0xfa4e90, tail call).
#include "game/types.h"

struct Child_fa6a30 {
    void Call(uint32_t arg);   // 0x00fa4e90
};
struct Owner_fa6a30 {
    char mPad[0x8];
    Child_fa6a30* mpChild;                       // +0x8
    void Call(uint32_t arg);
};

// @ 0x00fa6a30
void Owner_fa6a30::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
