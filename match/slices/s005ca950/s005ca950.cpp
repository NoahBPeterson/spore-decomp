// Forwarder (0x005ca950): if the member object at +0x64 exists, pass the argument on to it (0x5c34e0, tail call).
#include "game/types.h"

struct Child_5ca950 {
    void Call(uint32_t arg);   // 0x005c34e0
};
struct Owner_5ca950 {
    char mPad[0x64];
    Child_5ca950* mpChild;                       // +0x64
    void Call(uint32_t arg);
};

// @ 0x005ca950
void Owner_5ca950::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
