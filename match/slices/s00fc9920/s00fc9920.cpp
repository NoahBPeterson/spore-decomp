// Forwarder (0x00fc9920): pass the call on to the embedded member object at +0x14 (0xfc8380, tail call).
#include "game/types.h"

struct Member_fc9920 {
    char mData[4];
    void* Call();   // 0x00fc8380
};
struct Owner_fc9920 {
    char mPad[0x14];
    Member_fc9920 mMember;                       // +0x14
    void* Call();
};

// @ 0x00fc9920
void* Owner_fc9920::Call()
{
    return mMember.Call();
}
