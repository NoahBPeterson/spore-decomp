// Forwarder (0x007c3c10): pass the call on to the member object at +0x170 (0x11f38e0, tail call).
#include "game/types.h"

struct Child_7c3c10 {
    void* Call();   // 0x011f38e0
};
struct Owner_7c3c10 {
    char mPad[0x170];
    Child_7c3c10* mpChild;                       // +0x170
    void* Call();
};

// @ 0x007c3c10
void* Owner_7c3c10::Call()
{
    return mpChild->Call();
}
