// Forwarder (0x00c35310): pass the call on to the embedded member object at +0x108 (0xbf3460, tail call).
#include "game/types.h"

struct Member_c35310 {
    char mData[4];
    void* Call();   // 0x00bf3460
};
struct Owner_c35310 {
    char mPad[0x108];
    Member_c35310 mMember;                       // +0x108
    void* Call();
};

// @ 0x00c35310
void* Owner_c35310::Call()
{
    return mMember.Call();
}
