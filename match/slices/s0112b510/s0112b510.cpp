// Forwarder (0x0112b510): pass the call on to the member object at +0x8 (0x112b520, tail call).
#include "game/types.h"

struct Child_112b510 {
    void* Call();   // 0x0112b520
};
struct Owner_112b510 {
    char mPad[0x8];
    Child_112b510* mpChild;                       // +0x8
    void* Call();
};

// @ 0x0112b510
void* Owner_112b510::Call()
{
    return mpChild->Call();
}
