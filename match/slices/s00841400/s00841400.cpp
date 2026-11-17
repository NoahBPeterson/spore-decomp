// Forwarder (0x00841400): pass the call on to the embedded member object at +0x4c (0x83edc0, tail call).
#include "game/types.h"

struct Member_841400 {
    char mData[4];
    void* Call();   // 0x0083edc0
};
struct Owner_841400 {
    char mPad[0x4c];
    Member_841400 mMember;                       // +0x4c
    void* Call();
};

// @ 0x00841400
void* Owner_841400::Call()
{
    return mMember.Call();
}
