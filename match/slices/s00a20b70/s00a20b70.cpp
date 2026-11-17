// Forwarder (0x00a20b70): pass the call on to the embedded member object at +0x214 (0xa10490, tail call).
#include "game/types.h"

struct Member_a20b70 {
    char mData[4];
    void* Call();   // 0x00a10490
};
struct Owner_a20b70 {
    char mPad[0x214];
    Member_a20b70 mMember;                       // +0x214
    void* Call();
};

// @ 0x00a20b70
void* Owner_a20b70::Call()
{
    return mMember.Call();
}
