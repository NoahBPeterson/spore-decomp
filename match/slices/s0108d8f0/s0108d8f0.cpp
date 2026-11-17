// Forwarder (0x0108d8f0): pass the call on to the embedded member object at +0x1c (0x108d8a0, tail call).
#include "game/types.h"

struct Member_108d8f0 {
    char mData[4];
    void* Call();   // 0x0108d8a0
};
struct Owner_108d8f0 {
    char mPad[0x1c];
    Member_108d8f0 mMember;                       // +0x1c
    void* Call();
};

// @ 0x0108d8f0
void* Owner_108d8f0::Call()
{
    return mMember.Call();
}
