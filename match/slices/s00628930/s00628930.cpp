// Forwarder (0x00628930): pass the call on to the member object at +0xcc (0x63ecf0, tail call).
#include "game/types.h"

struct Child_628930 {
    void* Call();   // 0x0063ecf0
};
struct Owner_628930 {
    char mPad[0xcc];
    Child_628930* mpChild;                       // +0xcc
    void* Call();
};

// @ 0x00628930
void* Owner_628930::Call()
{
    return mpChild->Call();
}
