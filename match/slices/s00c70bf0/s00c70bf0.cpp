// Forwarder (0x00c70bf0): pass the call on to the member object at +0x13c (0xb8d920, tail call).
#include "game/types.h"

struct Child_c70bf0 {
    void* Call();   // 0x00b8d920
};
struct Owner_c70bf0 {
    char mPad[0x13c];
    Child_c70bf0* mpChild;                       // +0x13c
    void* Call();
};

// @ 0x00c70bf0
void* Owner_c70bf0::Call()
{
    return mpChild->Call();
}
