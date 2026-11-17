// Forwarder (0x006e6c40): if the member object at +0x35c exists, pass the argument on to it (0x6f4190, tail call).
#include "game/types.h"

struct Child_6e6c40 {
    void Call(uint32_t arg);   // 0x006f4190
};
struct Owner_6e6c40 {
    char mPad[0x35c];
    Child_6e6c40* mpChild;                       // +0x35c
    void Call(uint32_t arg);
};

// @ 0x006e6c40
void Owner_6e6c40::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
