// Forwarder (0x00c71030): pass the call on to the member object at +0x13c (0xb8dec0, tail call).
#include "game/types.h"

struct Child_c71030 {
    void* Call();   // 0x00b8dec0
};
struct Owner_c71030 {
    char mPad[0x13c];
    Child_c71030* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c71030
void* Owner_c71030::Call()
{
    return mpChild->Call();
}
