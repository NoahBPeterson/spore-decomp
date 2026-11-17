// Forwarder (0x00661380): pass the call on to the embedded member object at +0xf4 (0x54afe0, tail call).
#include "game/types.h"

struct Member_661380 {
    char mData[4];
    void* Call();   // 0x0054afe0
};
struct Owner_661380 {
    char mPad[0xf4];
    Member_661380 mMember;                       // +0xf4
    void* Call();
};

// @ 0x00661380
void* Owner_661380::Call()
{
    return mMember.Call();
}
