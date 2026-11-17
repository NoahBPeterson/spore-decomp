// Forwarder (0x00cf7510): pass the call on to the member object at +0xe8 (0xcf0eb0, tail call).
#include "game/types.h"

struct Child_cf7510 {
    void* Call();   // 0x00cf0eb0
};
struct Owner_cf7510 {
    char mPad[0xe8];
    Child_cf7510* mpChild;                       // +0xe8
    void* Call();
};

// @ 0x00cf7510
void* Owner_cf7510::Call()
{
    return mpChild->Call();
}
