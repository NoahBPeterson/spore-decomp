// Forwarder (0x005a2310): pass the call on to the embedded member object at +0xa0 (0x697980, tail call).
#include "game/types.h"

struct Member_5a2310 {
    char mData[4];
    void* Call();   // 0x00697980
};
struct Owner_5a2310 {
    char mPad[0xa0];
    Member_5a2310 mMember;                       // +0xa0
    void* Call();
};

// @ 0x005a2310
void* Owner_5a2310::Call()
{
    return mMember.Call();
}
