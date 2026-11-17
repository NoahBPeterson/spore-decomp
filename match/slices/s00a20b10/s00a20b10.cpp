// Forwarder (0x00a20b10): pass the call on to the embedded member object at +0x214 (0xa102e0, tail call).
#include "game/types.h"

struct Member_a20b10 {
    char mData[4];
    void* Call();   // 0x00a102e0
};
struct Owner_a20b10 {
    char mPad[0x214];
    Member_a20b10 mMember;                       // +0x214
    void* Call();
};

// @ 0x00a20b10
void* Owner_a20b10::Call()
{
    return mMember.Call();
}
