// Forwarder (0x00b18d80): pass the call on to the embedded member object at +0x90 (0x8d49b0, tail call).
#include "game/types.h"

struct Member_b18d80 {
    char mData[4];
    void* Call();   // 0x008d49b0
};
struct Owner_b18d80 {
    char mPad[0x90];
    Member_b18d80 mMember;                       // +0x90
    void* Call();
};

// @ 0x00b18d80
void* Owner_b18d80::Call()
{
    return mMember.Call();
}
