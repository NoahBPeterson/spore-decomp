// Forwarder (0x00a171c0): pass the call on to the embedded member object at +0xc (0xa1a590, tail call).
#include "game/types.h"

struct Member_a171c0 {
    char mData[4];
    void* Call();   // 0x00a1a590
};
struct Owner_a171c0 {
    char mPad[0xc];
    Member_a171c0 mMember;                       // +0xc
    void* Call();
};

// @ 0x00a171c0
void* Owner_a171c0::Call()
{
    return mMember.Call();
}
