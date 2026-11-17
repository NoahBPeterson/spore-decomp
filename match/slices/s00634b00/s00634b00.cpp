// Forwarder (0x00634b00): pass the call on to the member object at +0x10 (0x6288c0, tail call).
#include "game/types.h"

struct Child_634b00 {
    void* Call();   // 0x006288c0
};
struct Owner_634b00 {
    char mPad[0x10];
    Child_634b00* mpChild;                       // +0x10
    void* Call();
};

// @ 0x00634b00
void* Owner_634b00::Call()
{
    return mpChild->Call();
}
