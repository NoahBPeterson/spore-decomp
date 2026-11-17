// Forwarder (0x00d204b0): pass the call on to the embedded member object at +0x2bc (0x697a10, tail call).
#include "game/types.h"

struct Member_d204b0 {
    char mData[4];
    void* Call();   // 0x00697a10
};
struct Owner_d204b0 {
    char mPad[0x2bc];
    Member_d204b0 mMember;                       // +0x2bc
    void* Call();
};

// @ 0x00d204b0
void* Owner_d204b0::Call()
{
    return mMember.Call();
}
