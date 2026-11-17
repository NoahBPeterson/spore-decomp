// Forwarder (0x006b1e80): pass the call on to the embedded member object at +0x4 (0x6b1e20, tail call).
#include "game/types.h"

struct Member_6b1e80 {
    char mData[4];
    void* Call();   // 0x006b1e20
};
struct Owner_6b1e80 {
    char mPad[0x4];
    Member_6b1e80 mMember;                       // +0x4
    void* Call();
};

// @ 0x006b1e80
void* Owner_6b1e80::Call()
{
    return mMember.Call();
}
