// Forwarder (0x00e352b0): pass the call on to the member object at +0x18 (0xe2a6c0, tail call).
#include "game/types.h"

struct Child_e352b0 {
    void* Call();   // 0x00e2a6c0
};
struct Owner_e352b0 {
    char mPad[0x18];
    Child_e352b0* mpChild;                       // +0x18
    void* Call();
};

// @ 0x00e352b0
void* Owner_e352b0::Call()
{
    return mpChild->Call();
}
