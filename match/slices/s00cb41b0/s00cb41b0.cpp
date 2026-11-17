// Forwarder (0x00cb41b0): pass the call on to the embedded member object at +0x540 (0xbc3190, tail call).
#include "game/types.h"

struct Member_cb41b0 {
    char mData[4];
    void* Call();   // 0x00bc3190
};
struct Owner_cb41b0 {
    char mPad[0x540];
    Member_cb41b0 mMember;                       // +0x540
    void* Call();
};

// @ 0x00cb41b0
void* Owner_cb41b0::Call()
{
    return mMember.Call();
}
