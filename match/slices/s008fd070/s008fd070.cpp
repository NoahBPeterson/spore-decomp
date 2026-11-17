// Forwarder (0x008fd070): pass the call on to the embedded member object at +0x10 (0x943d70, tail call).
#include "game/types.h"

struct Member_8fd070 {
    char mData[4];
    void* Call();   // 0x00943d70
};
struct Owner_8fd070 {
    char mPad[0x10];
    Member_8fd070 mMember;                       // +0x10
    void* Call();
};

// @ 0x008fd070
void* Owner_8fd070::Call()
{
    return mMember.Call();
}
