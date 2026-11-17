// Forwarder (0x00c86f80): pass the call on to the embedded member object at +0x48 (0x6b55c0, tail call).
#include "game/types.h"

struct Member_c86f80 {
    char mData[4];
    void* Call();   // 0x006b55c0
};
struct Owner_c86f80 {
    char mPad[0x48];
    Member_c86f80 mMember;                       // +0x48
    void* Call();
};

// @ 0x00c86f80
void* Owner_c86f80::Call()
{
    return mMember.Call();
}
