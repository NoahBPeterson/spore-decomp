// Forwarder (0x00c710b0): pass the call on to the member object at +0x13c (0xb8eec0, tail call).
#include "game/types.h"

struct Child_c710b0 {
    void* Call();   // 0x00b8eec0
};
struct Owner_c710b0 {
    char mPad[0x13c];
    Child_c710b0* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c710b0
void* Owner_c710b0::Call()
{
    return mpChild->Call();
}
