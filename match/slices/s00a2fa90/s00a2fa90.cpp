// Forwarder (0x00a2fa90): pass the call on to the embedded member object at +0x10 (0xa33fd0, tail call).
#include "game/types.h"

struct Member_a2fa90 {
    char mData[4];
    void* Call();   // 0x00a33fd0
};
struct Owner_a2fa90 {
    char mPad[0x10];
    Member_a2fa90 mMember;                       // +0x10
    void* Call();
};

// @ 0x00a2fa90
void* Owner_a2fa90::Call()
{
    return mMember.Call();
}
