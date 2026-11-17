// Forwarder (0x00c449f0): pass the call on to the embedded member object at +0x58 (0xbc3130, tail call).
#include "game/types.h"

struct Member_c449f0 {
    char mData[4];
    void* Call();   // 0x00bc3130
};
struct Owner_c449f0 {
    char mPad[0x58];
    Member_c449f0 mMember;                       // +0x58
    void* Call();
};

// @ 0x00c449f0
void* Owner_c449f0::Call()
{
    return mMember.Call();
}
