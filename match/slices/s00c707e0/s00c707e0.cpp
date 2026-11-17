// Forwarder (0x00c707e0): pass the call on to the member object at +0x13c (0xecdba0, tail call).
#include "game/types.h"

struct Child_c707e0 {
    void* Call();   // 0x00ecdba0
};
struct Owner_c707e0 {
    char mPad[0x13c];
    Child_c707e0* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c707e0
void* Owner_c707e0::Call()
{
    return mpChild->Call();
}
