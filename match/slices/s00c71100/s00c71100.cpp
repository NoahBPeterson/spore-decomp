// Forwarder (0x00c71100): pass the call on to the member object at +0x13c (0xb8df20, tail call).
#include "game/types.h"

struct Child_c71100 {
    void* Call();   // 0x00b8df20
};
struct Owner_c71100 {
    char mPad[0x13c];
    Child_c71100* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c71100
void* Owner_c71100::Call()
{
    return mpChild->Call();
}
