// Forwarder (0x00ce9550): pass the call on to the member object at +0x64 (0xe05930, tail call).
#include "game/types.h"

struct Child_ce9550 {
    void* Call();   // 0x00e05930
};
struct Owner_ce9550 {
    char mPad[0x64];
    Child_ce9550* mpChild;                       // +0x64
    void* Call();
};

// @ 0x00ce9550
void* Owner_ce9550::Call()
{
    return mpChild->Call();
}
