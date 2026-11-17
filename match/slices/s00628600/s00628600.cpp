// Forwarder (0x00628600): pass the call on to the embedded member object at +0x11b0 (0x63b570, tail call).
#include "game/types.h"

struct Member_628600 {
    char mData[4];
    void* Call();   // 0x0063b570
};
struct Owner_628600 {
    char mPad[0x11b0];
    Member_628600 mMember;                       // +0x11b0
    void* Call();
};

// @ 0x00628600
void* Owner_628600::Call()
{
    return mMember.Call();
}
