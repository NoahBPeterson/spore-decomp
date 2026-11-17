// Forwarder (0x00fa6a40): if the member object at +0x8 exists, pass the argument on to it (0xfa4fc0, tail call).
#include "game/types.h"

struct Child_fa6a40 {
    void Call(uint32_t arg);   // 0x00fa4fc0
};
struct Owner_fa6a40 {
    char mPad[0x8];
    Child_fa6a40* mpChild;                       // +0x8
    void Call(uint32_t arg);
};

// @ 0x00fa6a40
void Owner_fa6a40::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
