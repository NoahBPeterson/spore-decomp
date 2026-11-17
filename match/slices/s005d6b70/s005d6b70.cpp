// Forwarder (0x005d6b70): pass the call on to the embedded member object at +0x8 (0x107ddd0, tail call).
#include "game/types.h"

struct Member_5d6b70 {
    char mData[4];
    void* Call();   // 0x0107ddd0
};
struct Owner_5d6b70 {
    char mPad[0x8];
    Member_5d6b70 mMember;                       // +0x8
    void* Call();
};

// @ 0x005d6b70
void* Owner_5d6b70::Call()
{
    return mMember.Call();
}
