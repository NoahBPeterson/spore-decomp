// Forwarder (0x00748c20): pass the call on to the embedded member object at +0x314 (0x7476c0, tail call).
#include "game/types.h"

struct Member_748c20 {
    char mData[4];
    void* Call();   // 0x007476c0
};
struct Owner_748c20 {
    char mPad[0x314];
    Member_748c20 mMember;                       // +0x314
    void* Call();
};

// @ 0x00748c20
void* Owner_748c20::Call()
{
    return mMember.Call();
}
