// Forwarder (0x00628960): pass the call on to the embedded member object at +0xd8 (0x6388e0, tail call).
#include "game/types.h"

struct Member_628960 {
    char mData[4];
    void* Call();   // 0x006388e0
};
struct Owner_628960 {
    char mPad[0xd8];
    Member_628960 mMember;                       // +0xd8
    void* Call();
};

// @ 0x00628960
void* Owner_628960::Call()
{
    return mMember.Call();
}
