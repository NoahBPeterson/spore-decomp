// Forwarder (0x007df700): pass the call on to the embedded member object at +0x14c (0x50d4e0, tail call).
#include "game/types.h"

struct Member_7df700 {
    char mData[4];
    void* Call();   // 0x0050d4e0
};
struct Owner_7df700 {
    char mPad[0x14c];
    Member_7df700 mMember;                       // +0x14c
    void* Call();
};

// @ 0x007df700
void* Owner_7df700::Call()
{
    return mMember.Call();
}
