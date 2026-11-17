// Forwarder (0x00bef8c0): pass the call on to the embedded member object at +0x108 (0xbc3130, tail call).
#include "game/types.h"

struct Member_bef8c0 {
    char mData[4];
    void* Call();   // 0x00bc3130
};
struct Owner_bef8c0 {
    char mPad[0x108];
    Member_bef8c0 mMember;                       // +0x108
    void* Call();
};

// @ 0x00bef8c0
void* Owner_bef8c0::Call()
{
    return mMember.Call();
}
