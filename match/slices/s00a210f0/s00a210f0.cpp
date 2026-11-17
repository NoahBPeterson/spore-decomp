// Forwarder (0x00a210f0): pass the call on to the embedded member object at +0xb8 (0x922270, tail call).
#include "game/types.h"

struct Member_a210f0 {
    char mData[4];
    void* Call();   // 0x00922270
};
struct Owner_a210f0 {
    char mPad[0xb8];
    Member_a210f0 mMember;                       // +0xb8
    void* Call();
};

// @ 0x00a210f0
void* Owner_a210f0::Call()
{
    return mMember.Call();
}
