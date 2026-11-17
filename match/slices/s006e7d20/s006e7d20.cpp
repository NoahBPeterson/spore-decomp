// Forwarder (0x006e7d20): if the member object at +0x360 exists, pass the argument on to it (0x7763e0, tail call).
#include "game/types.h"

struct Child_6e7d20 {
    void Call(uint32_t arg);   // 0x007763e0
};
struct Owner_6e7d20 {
    char mPad[0x360];
    Child_6e7d20* mpChild;                       // +0x360
    void Call(uint32_t arg);
};

// @ 0x006e7d20
void Owner_6e7d20::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
