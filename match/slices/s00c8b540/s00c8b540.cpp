// Forwarder (0x00c8b540): pass the call on to the member object at +0x48 (0xbb9de0, tail call).
#include "game/types.h"

struct Child_c8b540 {
    void* Call();   // 0x00bb9de0
};
struct Owner_c8b540 {
    char mPad[0x48];
    Child_c8b540* mpChild;                       // +0x48
    void* Call();
};

// @ 0x00c8b540
void* Owner_c8b540::Call()
{
    return mpChild->Call();
}
