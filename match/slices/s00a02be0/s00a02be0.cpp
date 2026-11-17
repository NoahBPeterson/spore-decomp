// Forwarder (0x00a02be0): pass the call on to the member object at +0x184 (0xa02440, tail call).
#include "game/types.h"

struct Child_a02be0 {
    void* Call();   // 0x00a02440
};
struct Owner_a02be0 {
    char mPad[0x184];
    Child_a02be0* mpChild;                       // +0x184
    void* Call();
};

// @ 0x00a02be0
void* Owner_a02be0::Call()
{
    return mpChild->Call();
}
