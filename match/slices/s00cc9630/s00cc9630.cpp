// Forwarder (0x00cc9630): pass the call on to the member object at +0x78 (0xcc9270, tail call).
#include "game/types.h"

struct Child_cc9630 {
    void* Call();   // 0x00cc9270
};
struct Owner_cc9630 {
    char mPad[0x78];
    Child_cc9630* mpChild;                       // +0x78
    void* Call();
};

// @ 0x00cc9630
void* Owner_cc9630::Call()
{
    return mpChild->Call();
}
