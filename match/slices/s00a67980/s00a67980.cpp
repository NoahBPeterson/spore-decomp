// Forwarder (0x00a67980): pass the call on to the embedded member object at +0x7c (0xa669b0, tail call).
#include "game/types.h"

struct Member_a67980 {
    char mData[4];
    void* Call();   // 0x00a669b0
};
struct Owner_a67980 {
    char mPad[0x7c];
    Member_a67980 mMember;                       // +0x7c
    void* Call();
};

// @ 0x00a67980
void* Owner_a67980::Call()
{
    return mMember.Call();
}
