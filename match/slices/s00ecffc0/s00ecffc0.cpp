// Forwarder (0x00ecffc0): pass the call on to the member object at +0x8 (0xf326d0, tail call).
#include "game/types.h"

struct Child_ecffc0 {
    void* Call();   // 0x00f326d0
};
struct Owner_ecffc0 {
    char mPad[0x8];
    Child_ecffc0* mpChild;                       // +0x8
    void* Call();
};

// @ 0x00ecffc0
void* Owner_ecffc0::Call()
{
    return mpChild->Call();
}
