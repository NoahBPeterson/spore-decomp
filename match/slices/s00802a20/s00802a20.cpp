// Forwarder (0x00802a20): if the member object at +0x28 exists, pass the argument on to it (0x96acd0, tail call).
#include "game/types.h"

struct Child_802a20 {
    void Call(uint32_t arg);   // 0x0096acd0
};
struct Owner_802a20 {
    char mPad[0x28];
    Child_802a20* mpChild;                       // +0x28
    void Call(uint32_t arg);
};

// @ 0x00802a20
void Owner_802a20::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
