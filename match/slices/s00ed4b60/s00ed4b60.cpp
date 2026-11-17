// Forwarder (0x00ed4b60): pass the call on to the member object at +0x44 (0xe02e80, tail call).
#include "game/types.h"

struct Child_ed4b60 {
    void* Call();   // 0x00e02e80
};
struct Owner_ed4b60 {
    char mPad[0x44];
    Child_ed4b60* mpChild;                       // +0x44
    void* Call();
};

// @ 0x00ed4b60
void* Owner_ed4b60::Call()
{
    return mpChild->Call();
}
