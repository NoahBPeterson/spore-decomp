// Forwarder (0x007eb7c0): pass the call on to the embedded member object at +0x4 (0x7eb3f0, tail call).
#include "game/types.h"

struct Member_7eb7c0 {
    char mData[4];
    void* Call();   // 0x007eb3f0
};
struct Owner_7eb7c0 {
    char mPad[0x4];
    Member_7eb7c0 mMember;                       // +0x4
    void* Call();
};

// @ 0x007eb7c0
void* Owner_7eb7c0::Call()
{
    return mMember.Call();
}
