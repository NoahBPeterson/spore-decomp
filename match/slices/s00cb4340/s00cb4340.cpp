// Forwarder (0x00cb4340): pass the call on to the embedded member object at +0x530 (0xbc3190, tail call).
#include "game/types.h"

struct Member_cb4340 {
    char mData[4];
    void* Call();   // 0x00bc3190
};
struct Owner_cb4340 {
    char mPad[0x530];
    Member_cb4340 mMember;                       // +0x530
    void* Call();
};

// @ 0x00cb4340
void* Owner_cb4340::Call()
{
    return mMember.Call();
}
