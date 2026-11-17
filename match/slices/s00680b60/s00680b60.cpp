// Forwarder (0x00680b60): pass the call on to the embedded member object at +0x4 (0x6809f0, tail call).
#include "game/types.h"

struct Member_680b60 {
    char mData[4];
    void* Call();   // 0x006809f0
};
struct Owner_680b60 {
    char mPad[0x4];
    Member_680b60 mMember;                       // +0x4
    void* Call();
};

// @ 0x00680b60
void* Owner_680b60::Call()
{
    return mMember.Call();
}
