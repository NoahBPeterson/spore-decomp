// Forwarder (0x0112b4c0): pass the call on to the embedded member object at +0x24 (0x107e560, tail call).
#include "game/types.h"

struct Member_112b4c0 {
    char mData[4];
    void* Call();   // 0x0107e560
};
struct Owner_112b4c0 {
    char mPad[0x24];
    Member_112b4c0 mMember;                       // +0x24
    void* Call();
};

// @ 0x0112b4c0
void* Owner_112b4c0::Call()
{
    return mMember.Call();
}
