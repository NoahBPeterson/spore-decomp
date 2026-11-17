// Forwarder (0x00a64a40): pass the call on to the embedded member object at +0x4 (0xa64710, tail call).
#include "game/types.h"

struct Member_a64a40 {
    char mData[4];
    void* Call();   // 0x00a64710
};
struct Owner_a64a40 {
    char mPad[0x4];
    Member_a64a40 mMember;                       // +0x4
    void* Call();
};

// @ 0x00a64a40
void* Owner_a64a40::Call()
{
    return mMember.Call();
}
