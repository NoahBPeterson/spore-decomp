// Forwarder (0x00a20b90): pass the call on to the embedded member object at +0x214 (0xa10670, tail call).
#include "game/types.h"

struct Member_a20b90 {
    char mData[4];
    void* Call();   // 0x00a10670
};
struct Owner_a20b90 {
    char mPad[0x214];
    Member_a20b90 mMember;                       // +0x214
    void* Call();
};

// @ 0x00a20b90
void* Owner_a20b90::Call()
{
    return mMember.Call();
}
