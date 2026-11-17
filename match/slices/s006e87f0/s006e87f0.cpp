// Forwarder (0x006e87f0): if the member object at +0x360 exists, pass the argument on to it (0x776580, tail call).
#include "game/types.h"

struct Child_6e87f0 {
    void Call(uint32_t arg);   // 0x00776580
};
struct Owner_6e87f0 {
    char mPad[0x360];
    Child_6e87f0* mpChild;                       // +0x360
    void Call(uint32_t arg);
};

// @ 0x006e87f0
void Owner_6e87f0::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
