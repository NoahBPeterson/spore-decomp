// Forwarder (0x00a20b60): pass the call on to the embedded member object at +0x214 (0xa10480, tail call).
#include "game/types.h"

struct Member_a20b60 {
    char mData[4];
    void* Call();   // 0x00a10480
};
struct Owner_a20b60 {
    char mPad[0x214];
    Member_a20b60 mMember;                       // +0x214
    void* Call();
};

// @ 0x00a20b60
void* Owner_a20b60::Call()
{
    return mMember.Call();
}
