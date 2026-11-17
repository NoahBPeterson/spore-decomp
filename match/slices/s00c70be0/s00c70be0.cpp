// Forwarder (0x00c70be0): pass the call on to the member object at +0x13c (0xb8d940, tail call).
#include "game/types.h"

struct Child_c70be0 {
    void* Call();   // 0x00b8d940
};
struct Owner_c70be0 {
    char mPad[0x13c];
    Child_c70be0* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c70be0
void* Owner_c70be0::Call()
{
    return mpChild->Call();
}
