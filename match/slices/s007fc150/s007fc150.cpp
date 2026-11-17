// Forwarder (0x007fc150): pass the call on to the embedded member object at +0x8 (0x5454f0, tail call).
#include "game/types.h"

struct Member_7fc150 {
    char mData[4];
    void* Call();   // 0x005454f0
};
struct Owner_7fc150 {
    char mPad[0x8];
    Member_7fc150 mMember;                       // +0x8
    void* Call();
};

// @ 0x007fc150
void* Owner_7fc150::Call()
{
    return mMember.Call();
}
