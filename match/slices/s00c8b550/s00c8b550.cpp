// Forwarder (0x00c8b550): pass the call on to the member object at +0x48 (0x801920, tail call).
#include "game/types.h"

struct Child_c8b550 {
    void* Call();   // 0x00801920
};
struct Owner_c8b550 {
    char mPad[0x48];
    Child_c8b550* mpChild;                       // +0x48
    void* Call();
};

// @ 0x00c8b550
void* Owner_c8b550::Call()
{
    return mpChild->Call();
}
