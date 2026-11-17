// Forwarder (0x00c71150): pass the call on to the member object at +0x13c (0xb8df80, tail call).
#include "game/types.h"

struct Child_c71150 {
    void* Call();   // 0x00b8df80
};
struct Owner_c71150 {
    char mPad[0x13c];
    Child_c71150* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c71150
void* Owner_c71150::Call()
{
    return mpChild->Call();
}
