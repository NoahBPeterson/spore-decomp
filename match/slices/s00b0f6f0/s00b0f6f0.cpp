// Forwarder (0x00b0f6f0): pass the call on to the embedded member object at +0x31c (0x697980, tail call).
#include "game/types.h"

struct Member_b0f6f0 {
    char mData[4];
    void* Call();   // 0x00697980
};
struct Owner_b0f6f0 {
    char mPad[0x31c];
    Member_b0f6f0 mMember;                       // +0x31c
    void* Call();
};

// @ 0x00b0f6f0
void* Owner_b0f6f0::Call()
{
    return mMember.Call();
}
