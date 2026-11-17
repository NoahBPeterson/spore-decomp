// Forwarder (0x00d09690): if the member object at +0xb4 exists, pass the argument on to it (0x5cb240, tail call).
#include "game/types.h"

struct Child_d09690 {
    void Call(uint32_t arg);   // 0x005cb240
};
struct Owner_d09690 {
    char mPad[0xb4];
    Child_d09690* mpChild;                       // +0xb4
    void Call(uint32_t arg);
};

// @ 0x00d09690
void Owner_d09690::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
