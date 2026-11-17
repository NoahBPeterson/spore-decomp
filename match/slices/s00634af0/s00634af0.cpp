// Forwarder (0x00634af0): pass the call on to the member object at +0x10 (0x628920, tail call).
#include "game/types.h"

struct Child_634af0 {
    void* Call();   // 0x00628920
};
struct Owner_634af0 {
    char mPad[0x10];
    Child_634af0* mpChild;                       // +0x10
    void* Call();
};

// @ 0x00634af0
void* Owner_634af0::Call()
{
    return mpChild->Call();
}
