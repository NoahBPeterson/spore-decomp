// Forwarder (0x00c8e6c0): pass the call on to the embedded member object at +0x510 (0xbc30f0, tail call).
#include "game/types.h"

struct Member_c8e6c0 {
    char mData[4];
    void* Call();   // 0x00bc30f0
};
struct Owner_c8e6c0 {
    char mPad[0x510];
    Member_c8e6c0 mMember;                       // +0x510
    void* Call();
};

// @ 0x00c8e6c0
void* Owner_c8e6c0::Call()
{
    return mMember.Call();
}
