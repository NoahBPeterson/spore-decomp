// Forwarder (0x00a04a90): if the member object at +0x17c exists, pass the argument on to it (0x9b3aa0, tail call).
#include "game/types.h"

struct Child_a04a90 {
    void Call(uint32_t arg);   // 0x009b3aa0
};
struct Owner_a04a90 {
    char mPad[0x17c];
    Child_a04a90* mpChild;                       // +0x17c
    void Call(uint32_t arg);
};

// @ 0x00a04a90
void Owner_a04a90::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
