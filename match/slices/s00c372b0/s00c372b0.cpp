// Forwarder (0x00c372b0): pass the call on to the embedded member object at +0x7b8 (0xfeba90, tail call).
#include "game/types.h"

struct Member_c372b0 {
    char mData[4];
    void* Call();   // 0x00feba90
};
struct Owner_c372b0 {
    char mPad[0x7b8];
    Member_c372b0 mMember;                       // +0x7b8
    void* Call();
};

// @ 0x00c372b0
void* Owner_c372b0::Call()
{
    return mMember.Call();
}
