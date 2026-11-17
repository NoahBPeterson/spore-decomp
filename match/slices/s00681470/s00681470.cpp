// Forwarder (0x00681470): pass the call on to the embedded member object at +0x4 (0x681400, tail call).
#include "game/types.h"

struct Member_681470 {
    char mData[4];
    void* Call();   // 0x00681400
};
struct Owner_681470 {
    char mPad[0x4];
    Member_681470 mMember;                       // +0x4
    void* Call();
};

// @ 0x00681470
void* Owner_681470::Call()
{
    return mMember.Call();
}
