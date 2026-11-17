// Forwarder (0x00bd9e40): pass the call on to the member object at +0x590 (0xbef950, tail call).
#include "game/types.h"

struct Child_bd9e40 {
    void* Call();   // 0x00bef950
};
struct Owner_bd9e40 {
    char mPad[0x590];
    Child_bd9e40* mpChild;                       // +0x590
    void* Call();
};

// @ 0x00bd9e40
void* Owner_bd9e40::Call()
{
    return mpChild->Call();
}
