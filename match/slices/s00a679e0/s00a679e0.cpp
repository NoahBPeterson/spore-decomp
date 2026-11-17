// Forwarder (0x00a679e0): pass the call on to the embedded member object at +0x154 (0xa65cd0, tail call).
#include "game/types.h"

struct Member_a679e0 {
    char mData[4];
    void* Call();   // 0x00a65cd0
};
struct Owner_a679e0 {
    char mPad[0x154];
    Member_a679e0 mMember;                       // +0x154
    void* Call();
};

// @ 0x00a679e0
void* Owner_a679e0::Call()
{
    return mMember.Call();
}
