// Forwarder (0x00c86f70): pass the call on to the embedded member object at +0x34 (0x6b55c0, tail call).
#include "game/types.h"

struct Member_c86f70 {
    char mData[4];
    void* Call();   // 0x006b55c0
};
struct Owner_c86f70 {
    char mPad[0x34];
    Member_c86f70 mMember;                       // +0x34
    void* Call();
};

// @ 0x00c86f70
void* Owner_c86f70::Call()
{
    return mMember.Call();
}
