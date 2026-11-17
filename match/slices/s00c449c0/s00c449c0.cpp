// Forwarder (0x00c449c0): pass the call on to the embedded member object at +0x38 (0xbc3130, tail call).
#include "game/types.h"

struct Member_c449c0 {
    char mData[4];
    void* Call();   // 0x00bc3130
};
struct Owner_c449c0 {
    char mPad[0x38];
    Member_c449c0 mMember;                       // +0x38
    void* Call();
};

// @ 0x00c449c0
void* Owner_c449c0::Call()
{
    return mMember.Call();
}
