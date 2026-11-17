// Forwarder (0x00641860): if the member object at +0x1c exists, pass the argument on to it (0x550cf0, tail call).
#include "game/types.h"

struct Child_641860 {
    void Call(uint32_t arg);   // 0x00550cf0
};
struct Owner_641860 {
    char mPad[0x1c];
    Child_641860* mpChild;                       // +0x1c
    void Call(uint32_t arg);
};

// @ 0x00641860
void Owner_641860::Call(uint32_t arg)
{
    if (mpChild)
        mpChild->Call(arg);
}
