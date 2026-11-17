// Forwarder (0x0064f2f0): if the member object at +0xe0 exists, pass the argument on to it (0x65fa80, tail call).
#include "game/types.h"

struct Child_64f2f0 {
    void Call(uint32_t arg);   // 0x0065fa80
};
struct Owner_64f2f0 {
    char mPad[0xe0];
    Child_64f2f0* mpChild;                       // +0xe0
    void Call(uint32_t arg);
};

// @ 0x0064f2f0
void Owner_64f2f0::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
