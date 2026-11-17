// Forwarder (0x00de2a40): pass the call on to the embedded member object at +0x40 (0xde29f0, tail call).
#include "game/types.h"

struct Member_de2a40 {
    char mData[4];
    void* Call();   // 0x00de29f0
};
struct Owner_de2a40 {
    char mPad[0x40];
    Member_de2a40 mMember;                       // +0x40
    void* Call();
};

// @ 0x00de2a40
void* Owner_de2a40::Call()
{
    return mMember.Call();
}
