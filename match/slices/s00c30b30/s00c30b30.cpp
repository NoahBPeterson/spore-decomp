// Forwarder (0x00c30b30): pass the call on to the embedded member object at +0x128 (0xfeba90, tail call).
#include "game/types.h"

struct Member_c30b30 {
    char mData[4];
    void* Call();   // 0x00feba90
};
struct Owner_c30b30 {
    char mPad[0x128];
    Member_c30b30 mMember;                       // +0x128
    void* Call();
};

// @ 0x00c30b30
void* Owner_c30b30::Call()
{
    return mMember.Call();
}
