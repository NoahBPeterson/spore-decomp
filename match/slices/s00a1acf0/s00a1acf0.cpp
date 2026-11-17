// Forwarder (0x00a1acf0): pass the call on to the embedded member object at +0xe4 (0xa108e0, tail call).
#include "game/types.h"

struct Member_a1acf0 {
    char mData[4];
    void* Call();   // 0x00a108e0
};
struct Owner_a1acf0 {
    char mPad[0xe4];
    Member_a1acf0 mMember;                       // +0xe4
    void* Call();
};

// @ 0x00a1acf0
void* Owner_a1acf0::Call()
{
    return mMember.Call();
}
