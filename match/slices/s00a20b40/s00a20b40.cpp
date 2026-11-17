// Forwarder (0x00a20b40): pass the call on to the embedded member object at +0x214 (0xa103b0, tail call).
#include "game/types.h"

struct Member_a20b40 {
    char mData[4];
    void* Call();   // 0x00a103b0
};
struct Owner_a20b40 {
    char mPad[0x214];
    Member_a20b40 mMember;                       // +0x214
    void* Call();
};

// @ 0x00a20b40
void* Owner_a20b40::Call()
{
    return mMember.Call();
}
