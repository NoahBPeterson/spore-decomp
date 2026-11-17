// Forwarder (0x005a2070): pass the call on to the embedded member object at +0xa0 (0x697a10, tail call).
#include "game/types.h"

struct Member_5a2070 {
    char mData[4];
    void* Call();   // 0x00697a10
};
struct Owner_5a2070 {
    char mPad[0xa0];
    Member_5a2070 mMember;                       // +0xa0
    void* Call();
};

// @ 0x005a2070
void* Owner_5a2070::Call()
{
    return mMember.Call();
}
