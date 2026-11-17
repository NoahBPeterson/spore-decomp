// Forwarder (0x00fc9910): pass the call on to the embedded member object at +0x14 (0xfc8370, tail call).
#include "game/types.h"

struct Member_fc9910 {
    char mData[4];
    void* Call();   // 0x00fc8370
};
struct Owner_fc9910 {
    char mPad[0x14];
    Member_fc9910 mMember;                       // +0x14
    void* Call();
};

// @ 0x00fc9910
void* Owner_fc9910::Call()
{
    return mMember.Call();
}
