// Forwarder (0x00c9d140): pass the call on to the embedded member object at +0x200 (0xbc3130, tail call).
#include "game/types.h"

struct Member_c9d140 {
    char mData[4];
    void* Call();   // 0x00bc3130
};
struct Owner_c9d140 {
    char mPad[0x200];
    Member_c9d140 mMember;                       // +0x200
    void* Call();
};

// @ 0x00c9d140
void* Owner_c9d140::Call()
{
    return mMember.Call();
}
