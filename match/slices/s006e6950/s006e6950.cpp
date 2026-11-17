// Forwarder (0x006e6950): if the member object at +0x35c exists, pass the argument on to it (0xb8da30, tail call).
#include "game/types.h"

struct Child_6e6950 {
    void Call(uint32_t arg);   // 0x00b8da30
};
struct Owner_6e6950 {
    char mPad[0x35c];
    Child_6e6950* mpChild;                       // +0x35c
    void Call(uint32_t arg);
};

// @ 0x006e6950
void Owner_6e6950::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
