// Forwarder (0x00c8b370): pass the call on to the member object at +0x48 (0x989360, tail call).
#include "game/types.h"

struct Child_c8b370 {
    void* Call();   // 0x00989360
};
struct Owner_c8b370 {
    char mPad[0x48];
    Child_c8b370* mpChild;                       // +0x48
    void* Call();
};

// @ 0x00c8b370
void* Owner_c8b370::Call()
{
    return mpChild->Call();
}
