// Forwarder (0x00628920): pass the call on to the member object at +0xcc (0x63ec10, tail call).
#include "game/types.h"

struct Child_628920 {
    void* Call();   // 0x0063ec10
};
struct Owner_628920 {
    char mPad[0xcc];
    Child_628920* mpChild;                       // +0xcc
    void* Call();
};

// @ 0x00628920
void* Owner_628920::Call()
{
    return mpChild->Call();
}
