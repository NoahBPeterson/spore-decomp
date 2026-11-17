// Forwarder (0x00bfeaf0): pass the call on to the embedded member object at +0x1dc (0x478db0, tail call).
#include "game/types.h"

struct Member_bfeaf0 {
    char mData[4];
    void* Call();   // 0x00478db0
};
struct Owner_bfeaf0 {
    char mPad[0x1dc];
    Member_bfeaf0 mMember;                       // +0x1dc
    void* Call();
};

// @ 0x00bfeaf0
void* Owner_bfeaf0::Call()
{
    return mMember.Call();
}
