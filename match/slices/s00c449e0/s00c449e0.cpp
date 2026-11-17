// Forwarder (0x00c449e0): pass the call on to the embedded member object at +0x58 (0xfeba90, tail call).
#include "game/types.h"

struct Member_c449e0 {
    char mData[4];
    void* Call();   // 0x00feba90
};
struct Owner_c449e0 {
    char mPad[0x58];
    Member_c449e0 mMember;                       // +0x58
    void* Call();
};

// @ 0x00c449e0
void* Owner_c449e0::Call()
{
    return mMember.Call();
}
