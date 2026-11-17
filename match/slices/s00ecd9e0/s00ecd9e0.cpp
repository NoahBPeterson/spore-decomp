// Forwarder (0x00ecd9e0): pass the call on to the embedded member object at +0x6c (0x83f5d0, tail call).
#include "game/types.h"

struct Member_ecd9e0 {
    char mData[4];
    void* Call();   // 0x0083f5d0
};
struct Owner_ecd9e0 {
    char mPad[0x6c];
    Member_ecd9e0 mMember;                       // +0x6c
    void* Call();
};

// @ 0x00ecd9e0
void* Owner_ecd9e0::Call()
{
    return mMember.Call();
}
