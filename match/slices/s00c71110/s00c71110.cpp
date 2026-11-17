// Forwarder (0x00c71110): pass the call on to the member object at +0x13c (0xb8def0, tail call).
#include "game/types.h"

struct Child_c71110 {
    void* Call();   // 0x00b8def0
};
struct Owner_c71110 {
    char mPad[0x13c];
    Child_c71110* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c71110
void* Owner_c71110::Call()
{
    return mpChild->Call();
}
