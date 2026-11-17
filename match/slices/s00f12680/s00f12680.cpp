// Forwarder (0x00f12680): if the member object at +0x18 exists, pass the argument on to it (0x5c28b0, tail call).
#include "game/types.h"

struct Child_f12680 {
    void Call(uint32_t arg);   // 0x005c28b0
};
struct Owner_f12680 {
    char mPad[0x18];
    Child_f12680* mpChild;                       // +0x18
    void Call(uint32_t arg);
};

// @ 0x00f12680
void Owner_f12680::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
