// Forwarder (0x00c71140): pass the call on to the member object at +0x13c (0xb8dfe0, tail call).
#include "game/types.h"

struct Child_c71140 {
    void* Call();   // 0x00b8dfe0
};
struct Owner_c71140 {
    char mPad[0x13c];
    Child_c71140* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c71140
void* Owner_c71140::Call()
{
    return mpChild->Call();
}
