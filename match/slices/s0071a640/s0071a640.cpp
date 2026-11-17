// Forwarder (0x0071a640): pass the call on to the embedded member object at +0x134 (0x719d30, tail call).
#include "game/types.h"

struct Member_71a640 {
    char mData[4];
    void* Call();   // 0x00719d30
};
struct Owner_71a640 {
    char mPad[0x134];
    Member_71a640 mMember;                       // +0x134
    void* Call();
};

// @ 0x0071a640
void* Owner_71a640::Call()
{
    return mMember.Call();
}
