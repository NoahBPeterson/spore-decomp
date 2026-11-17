// Forwarder (0x00c6ffa0): pass the call on to the embedded member object at +0x198 (0xbc3130, tail call).
#include "game/types.h"

struct Member_c6ffa0 {
    char mData[4];
    void* Call();   // 0x00bc3130
};
struct Owner_c6ffa0 {
    char mPad[0x198];
    Member_c6ffa0 mMember;                       // +0x198
    void* Call();
};

// @ 0x00c6ffa0
void* Owner_c6ffa0::Call()
{
    return mMember.Call();
}
