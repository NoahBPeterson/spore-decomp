// Forwarder (0x00c71540): pass the call on to the member object at +0x13c (0xb8dac0, tail call).
#include "game/types.h"

struct Child_c71540 {
    void* Call();   // 0x00b8dac0
};
struct Owner_c71540 {
    char mPad[0x13c];
    Child_c71540* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c71540
void* Owner_c71540::Call()
{
    return mpChild->Call();
}
