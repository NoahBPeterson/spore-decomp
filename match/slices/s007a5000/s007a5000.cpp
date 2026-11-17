// Forwarder (0x007a5000): pass the call on to the member object at +0x38 (0x6e6c60, tail call).
#include "game/types.h"

struct Child_7a5000 {
    void* Call();   // 0x006e6c60
};
struct Owner_7a5000 {
    char mPad[0x38];
    Child_7a5000* mpChild;                       // +0x38
    void* Call();
};

// @ 0x007a5000
void* Owner_7a5000::Call()
{
    return mpChild->Call();
}
