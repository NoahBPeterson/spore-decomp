// Forwarder (0x00a42c90): if the member object at +0xcc exists, pass the argument on to it (0xa3c800, tail call).
#include "game/types.h"

struct Child_a42c90 {
    void Call(uint32_t arg);   // 0x00a3c800
};
struct Owner_a42c90 {
    char mPad[0xcc];
    Child_a42c90* mpChild;                       // +0xcc
    void Call(uint32_t arg);
};

// @ 0x00a42c90
void Owner_a42c90::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
