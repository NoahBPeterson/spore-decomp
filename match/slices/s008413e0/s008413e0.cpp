// Forwarder (0x008413e0): pass the call on to the embedded member object at +0x4c (0x83f510, tail call).
#include "game/types.h"

struct Member_8413e0 {
    char mData[4];
    void* Call();   // 0x0083f510
};
struct Owner_8413e0 {
    char mPad[0x4c];
    Member_8413e0 mMember;                       // +0x4c
    void* Call();
};

// @ 0x008413e0
void* Owner_8413e0::Call()
{
    return mMember.Call();
}
