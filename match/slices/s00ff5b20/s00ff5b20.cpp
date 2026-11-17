// Forwarder (0x00ff5b20): pass the call on to the embedded member object at +0x1e4 (0x7cfc60, tail call).
#include "game/types.h"

struct Member_ff5b20 {
    char mData[4];
    void* Call();   // 0x007cfc60
};
struct Owner_ff5b20 {
    char mPad[0x1e4];
    Member_ff5b20 mMember;                       // +0x1e4
    void* Call();
};

// @ 0x00ff5b20
void* Owner_ff5b20::Call()
{
    return mMember.Call();
}
