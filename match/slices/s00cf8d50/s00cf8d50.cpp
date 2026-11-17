// Forwarder (0x00cf8d50): pass the call on to the member object at +0xec (0xce9380, tail call).
#include "game/types.h"

struct Child_cf8d50 {
    void* Call();   // 0x00ce9380
};
struct Owner_cf8d50 {
    char mPad[0xec];
    Child_cf8d50* mpChild;                       // +0xec
    void* Call();
};

// @ 0x00cf8d50
void* Owner_cf8d50::Call()
{
    return mpChild->Call();
}
