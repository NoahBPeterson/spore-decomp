// Forwarder (0x00ce8dd0): pass the call on to the member object at +0xf0 (0xe0e1a0, tail call).
#include "game/types.h"

struct Child_ce8dd0 {
    void* Call();   // 0x00e0e1a0
};
struct Owner_ce8dd0 {
    char mPad[0xf0];
    Child_ce8dd0* mpChild;                       // +0xf0
    void* Call();
};

// @ 0x00ce8dd0
void* Owner_ce8dd0::Call()
{
    return mpChild->Call();
}
