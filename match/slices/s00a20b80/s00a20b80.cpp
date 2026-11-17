// Forwarder (0x00a20b80): pass the call on to the embedded member object at +0x214 (0xa10540, tail call).
#include "game/types.h"

struct Member_a20b80 {
    char mData[4];
    void* Call();   // 0x00a10540
};
struct Owner_a20b80 {
    char mPad[0x214];
    Member_a20b80 mMember;                       // +0x214
    void* Call();
};

// @ 0x00a20b80
void* Owner_a20b80::Call()
{
    return mMember.Call();
}
