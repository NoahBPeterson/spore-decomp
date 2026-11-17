// Forwarder (0x00e31160): if the member object at +0xc exists, pass the argument on to it (0x810590, tail call).
#include "game/types.h"

struct Child_e31160 {
    void Call(uint32_t arg);   // 0x00810590
};
struct Owner_e31160 {
    char mPad[0xc];
    Child_e31160* mpChild;                       // +0xc
    void Call(uint32_t arg);
};

// @ 0x00e31160
void Owner_e31160::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
