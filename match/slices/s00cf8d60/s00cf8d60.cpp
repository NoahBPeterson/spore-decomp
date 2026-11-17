// Forwarder (0x00cf8d60): pass the call on to the member object at +0xec (0xce9b70, tail call).
#include "game/types.h"

struct Child_cf8d60 {
    void* Call();   // 0x00ce9b70
};
struct Owner_cf8d60 {
    char mPad[0xec];
    Child_cf8d60* mpChild;                       // +0xec
    void* Call();
};

// @ 0x00cf8d60
void* Owner_cf8d60::Call()
{
    return mpChild->Call();
}
