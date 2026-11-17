// Forwarder (0x00c8b5a0): pass the call on to the member object at +0x48 (0xbb9ae0, tail call).
#include "game/types.h"

struct Child_c8b5a0 {
    void* Call();   // 0x00bb9ae0
};
struct Owner_c8b5a0 {
    char mPad[0x48];
    Child_c8b5a0* mpChild;                       // +0x48
    void* Call();
};

// @ 0x00c8b5a0
void* Owner_c8b5a0::Call()
{
    return mpChild->Call();
}
