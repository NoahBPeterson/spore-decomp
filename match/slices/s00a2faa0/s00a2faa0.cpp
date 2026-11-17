// Forwarder (0x00a2faa0): pass the call on to the embedded member object at +0x10 (0xa33e90, tail call).
#include "game/types.h"

struct Member_a2faa0 {
    char mData[4];
    void* Call();   // 0x00a33e90
};
struct Owner_a2faa0 {
    char mPad[0x10];
    Member_a2faa0 mMember;                       // +0x10
    void* Call();
};

// @ 0x00a2faa0
void* Owner_a2faa0::Call()
{
    return mMember.Call();
}
