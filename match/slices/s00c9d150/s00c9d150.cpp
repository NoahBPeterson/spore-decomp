// Forwarder (0x00c9d150): pass the call on to the embedded member object at +0x200 (0xbc3110, tail call).
#include "game/types.h"

struct Member_c9d150 {
    char mData[4];
    void* Call();   // 0x00bc3110
};
struct Owner_c9d150 {
    char mPad[0x200];
    Member_c9d150 mMember;                       // +0x200
    void* Call();
};

// @ 0x00c9d150
void* Owner_c9d150::Call()
{
    return mMember.Call();
}
