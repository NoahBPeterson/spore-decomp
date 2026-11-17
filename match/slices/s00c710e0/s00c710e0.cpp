// Forwarder (0x00c710e0): pass the call on to the member object at +0x13c (0xb8de60, tail call).
#include "game/types.h"

struct Child_c710e0 {
    void* Call();   // 0x00b8de60
};
struct Owner_c710e0 {
    char mPad[0x13c];
    Child_c710e0* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c710e0
void* Owner_c710e0::Call()
{
    return mpChild->Call();
}
