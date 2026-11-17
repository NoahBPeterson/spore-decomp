// Forwarder (0x00ed4e80): pass the call on to the member object at +0x2c (0xedaca0, tail call).
#include "game/types.h"

struct Child_ed4e80 {
    void* Call();   // 0x00edaca0
};
struct Owner_ed4e80 {
    char mPad[0x2c];
    Child_ed4e80* mpChild;                       // +0x2c
    void* Call();
};

// @ 0x00ed4e80
void* Owner_ed4e80::Call()
{
    return mpChild->Call();
}
