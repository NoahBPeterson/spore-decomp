// Forwarder (0x00c8b590): pass the call on to the member object at +0x48 (0xbb9ad0, tail call).
#include "game/types.h"

struct Child_c8b590 {
    void* Call();   // 0x00bb9ad0
};
struct Owner_c8b590 {
    char mPad[0x48];
    Child_c8b590* mpChild;                       // +0x48
    void* Call();
};

// @ 0x00c8b590
void* Owner_c8b590::Call()
{
    return mpChild->Call();
}
