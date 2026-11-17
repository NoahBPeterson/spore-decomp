// Forwarder (0x00c8b5b0): pass the call on to the member object at +0x48 (0xb1fdb0, tail call).
#include "game/types.h"

struct Child_c8b5b0 {
    void* Call();   // 0x00b1fdb0
};
struct Owner_c8b5b0 {
    char mPad[0x48];
    Child_c8b5b0* mpChild;                       // +0x48
    void* Call();
};

// @ 0x00c8b5b0
void* Owner_c8b5b0::Call()
{
    return mpChild->Call();
}
