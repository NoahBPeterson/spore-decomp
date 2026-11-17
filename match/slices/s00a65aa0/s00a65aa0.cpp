// Forwarder (0x00a65aa0): pass the call on to the embedded member object at +0x8 (0x620230, tail call).
#include "game/types.h"

struct Member_a65aa0 {
    char mData[4];
    void* Call();   // 0x00620230
};
struct Owner_a65aa0 {
    char mPad[0x8];
    Member_a65aa0 mMember;                       // +0x8
    void* Call();
};

// @ 0x00a65aa0
void* Owner_a65aa0::Call()
{
    return mMember.Call();
}
