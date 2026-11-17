// Forwarder (0x00c713e0): pass the call on to the member object at +0x13c (0xb8d8e0, tail call).
#include "game/types.h"

struct Child_c713e0 {
    void* Call();   // 0x00b8d8e0
};
struct Owner_c713e0 {
    char mPad[0x13c];
    Child_c713e0* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c713e0
void* Owner_c713e0::Call()
{
    return mpChild->Call();
}
