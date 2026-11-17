// Forwarder (0x00c8b360): pass the call on to the member object at +0x48 (0x5c65e0, tail call).
#include "game/types.h"

struct Child_c8b360 {
    void* Call();   // 0x005c65e0
};
struct Owner_c8b360 {
    char mPad[0x48];
    Child_c8b360* mpChild;                       // +0x48
    void* Call();
};

// @ 0x00c8b360
void* Owner_c8b360::Call()
{
    return mpChild->Call();
}
