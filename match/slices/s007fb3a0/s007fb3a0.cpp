// Forwarder (0x007fb3a0): pass the call on to the embedded member object at +0x4 (0x453540, tail call).
#include "game/types.h"

struct Member_7fb3a0 {
    char mData[4];
    void* Call();   // 0x00453540
};
struct Owner_7fb3a0 {
    char mPad[0x4];
    Member_7fb3a0 mMember;                       // +0x4
    void* Call();
};

// @ 0x007fb3a0
void* Owner_7fb3a0::Call()
{
    return mMember.Call();
}
