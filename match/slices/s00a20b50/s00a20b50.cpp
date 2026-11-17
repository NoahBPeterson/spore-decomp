// Forwarder (0x00a20b50): pass the call on to the embedded member object at +0x214 (0xa103c0, tail call).
#include "game/types.h"

struct Member_a20b50 {
    char mData[4];
    void* Call();   // 0x00a103c0
};
struct Owner_a20b50 {
    char mPad[0x214];
    Member_a20b50 mMember;                       // +0x214
    void* Call();
};

// @ 0x00a20b50
void* Owner_a20b50::Call()
{
    return mMember.Call();
}
