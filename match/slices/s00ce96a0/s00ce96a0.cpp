// Forwarder (0x00ce96a0): pass the call on to the member object at +0x64 (0xe065c0, tail call).
#include "game/types.h"

struct Child_ce96a0 {
    void* Call();   // 0x00e065c0
};
struct Owner_ce96a0 {
    char mPad[0x64];
    Child_ce96a0* mpChild;                       // +0x64
    void* Call();
};

// @ 0x00ce96a0
void* Owner_ce96a0::Call()
{
    return mpChild->Call();
}
