// Forwarder (0x00a67bf0): pass the call on to the embedded member object at +0x1c (0xa63680, tail call).
#include "game/types.h"

struct Member_a67bf0 {
    char mData[4];
    void* Call();   // 0x00a63680
};
struct Owner_a67bf0 {
    char mPad[0x1c];
    Member_a67bf0 mMember;                       // +0x1c
    void* Call();
};

// @ 0x00a67bf0
void* Owner_a67bf0::Call()
{
    return mMember.Call();
}
