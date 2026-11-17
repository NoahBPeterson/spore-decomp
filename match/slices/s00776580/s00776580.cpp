// Forwarder (0x00776580): pass the call on to the embedded member object at +0x178 (0x537dc0, tail call).
#include "game/types.h"

struct Member_776580 {
    char mData[4];
    void* Call();   // 0x00537dc0
};
struct Owner_776580 {
    char mPad[0x178];
    Member_776580 mMember;                       // +0x178
    void* Call();
};

// @ 0x00776580
void* Owner_776580::Call()
{
    return mMember.Call();
}
