// Forwarder (0x00c75630): pass the call on to the embedded member object at +0x1258 (0xbc3130, tail call).
#include "game/types.h"

struct Member_c75630 {
    char mData[4];
    void* Call();   // 0x00bc3130
};
struct Owner_c75630 {
    char mPad[0x1258];
    Member_c75630 mMember;                       // +0x1258
    void* Call();
};

// @ 0x00c75630
void* Owner_c75630::Call()
{
    return mMember.Call();
}
