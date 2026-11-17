// Forwarder (0x00c449b0): pass the call on to the embedded member object at +0x38 (0xfeba90, tail call).
#include "game/types.h"

struct Member_c449b0 {
    char mData[4];
    void* Call();   // 0x00feba90
};
struct Owner_c449b0 {
    char mPad[0x38];
    Member_c449b0 mMember;                       // +0x38
    void* Call();
};

// @ 0x00c449b0
void* Owner_c449b0::Call()
{
    return mMember.Call();
}
