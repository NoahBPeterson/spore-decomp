// Forwarder (0x00ad7eb0): pass the call on to the member object at +0x140 (0x7e1760, tail call).
#include "game/types.h"

struct Child_ad7eb0 {
    void* Call();   // 0x007e1760
};
struct Owner_ad7eb0 {
    char mPad[0x140];
    Child_ad7eb0* mpChild;                       // +0x140
    void* Call();
};

// @ 0x00ad7eb0
void* Owner_ad7eb0::Call()
{
    return mpChild->Call();
}
