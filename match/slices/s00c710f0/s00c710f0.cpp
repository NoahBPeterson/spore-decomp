// Forwarder (0x00c710f0): pass the call on to the member object at +0x13c (0xb8ef00, tail call).
#include "game/types.h"

struct Child_c710f0 {
    void* Call();   // 0x00b8ef00
};
struct Owner_c710f0 {
    char mPad[0x13c];
    Child_c710f0* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c710f0
void* Owner_c710f0::Call()
{
    return mpChild->Call();
}
