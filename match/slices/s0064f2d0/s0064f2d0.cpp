// Forwarder (0x0064f2d0): if the member object at +0xe0 exists, pass the argument on to it (0x660360, tail call).
#include "game/types.h"

struct Child_64f2d0 {
    void Call(uint32_t arg);   // 0x00660360
};
struct Owner_64f2d0 {
    char mPad[0xe0];
    Child_64f2d0* mpChild;                       // +0xe0
    void Call(uint32_t arg);
};

// @ 0x0064f2d0
void Owner_64f2d0::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
