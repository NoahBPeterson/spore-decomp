// Forwarder (0x00c30b20): pass the call on to the embedded member object at +0x128 (0xbc3130, tail call).
#include "game/types.h"

struct Member_c30b20 {
    char mData[4];
    void* Call();   // 0x00bc3130
};
struct Owner_c30b20 {
    char mPad[0x128];
    Member_c30b20 mMember;                       // +0x128
    void* Call();
};

// @ 0x00c30b20
void* Owner_c30b20::Call()
{
    return mMember.Call();
}
