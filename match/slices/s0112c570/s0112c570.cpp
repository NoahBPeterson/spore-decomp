// Forwarder (0x0112c570): pass the call on to the member object at +0x48 (0x922270, tail call).
#include "game/types.h"

struct Child_112c570 {
    void* Call();   // 0x00922270
};
struct Owner_112c570 {
    char mPad[0x48];
    Child_112c570* mpChild;                       // +0x48
    void* Call();
};

// @ 0x0112c570
void* Owner_112c570::Call()
{
    return mpChild->Call();
}
