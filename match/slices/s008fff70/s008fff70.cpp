// Forwarder (0x008fff70): pass the call on to the embedded member object at +0x13c (0x8feae0, tail call).
#include "game/types.h"

struct Member_8fff70 {
    char mData[4];
    void* Call();   // 0x008feae0
};
struct Owner_8fff70 {
    char mPad[0x13c];
    Member_8fff70 mMember;                       // +0x13c
    void* Call();
};

// @ 0x008fff70
void* Owner_8fff70::Call()
{
    return mMember.Call();
}
