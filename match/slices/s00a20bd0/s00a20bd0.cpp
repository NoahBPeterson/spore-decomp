// Forwarder (0x00a20bd0): pass the call on to the embedded member object at +0x214 (0xa0f960, tail call).
#include "game/types.h"

struct Member_a20bd0 {
    char mData[4];
    void* Call();   // 0x00a0f960
};
struct Owner_a20bd0 {
    char mPad[0x214];
    Member_a20bd0 mMember;                       // +0x214
    void* Call();
};

// @ 0x00a20bd0
void* Owner_a20bd0::Call()
{
    return mMember.Call();
}
