// Forwarder (0x007d1000): pass the call on to the embedded member object at +0x4 (0x7d0f60, tail call).
#include "game/types.h"

struct Member_7d1000 {
    char mData[4];
    void* Call();   // 0x007d0f60
};
struct Owner_7d1000 {
    char mPad[0x4];
    Member_7d1000 mMember;                       // +0x4
    void* Call();
};

// @ 0x007d1000
void* Owner_7d1000::Call()
{
    return mMember.Call();
}
