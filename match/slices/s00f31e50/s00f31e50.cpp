// Forwarder (0x00f31e50): pass the call on to the member object at +0x194 (0xfb7b80, tail call).
#include "game/types.h"

struct Child_f31e50 {
    void* Call();   // 0x00fb7b80
};
struct Owner_f31e50 {
    char mPad[0x194];
    Child_f31e50* mpChild;                       // +0x194
    void* Call();
};

// @ 0x00f31e50
void* Owner_f31e50::Call()
{
    return mpChild->Call();
}
