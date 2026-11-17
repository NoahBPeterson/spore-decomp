// Forwarder (0x008413f0): pass the call on to the embedded member object at +0x4c (0x83e4f0, tail call).
#include "game/types.h"

struct Member_8413f0 {
    char mData[4];
    void* Call();   // 0x0083e4f0
};
struct Owner_8413f0 {
    char mPad[0x4c];
    Member_8413f0 mMember;                       // +0x4c
    void* Call();
};

// @ 0x008413f0
void* Owner_8413f0::Call()
{
    return mMember.Call();
}
