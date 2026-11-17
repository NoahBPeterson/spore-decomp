// Forwarder (0x0112b4b0): pass the call on to the embedded member object at +0x24 (0x107de70, tail call).
#include "game/types.h"

struct Member_112b4b0 {
    char mData[4];
    void* Call();   // 0x0107de70
};
struct Owner_112b4b0 {
    char mPad[0x24];
    Member_112b4b0 mMember;                       // +0x24
    void* Call();
};

// @ 0x0112b4b0
void* Owner_112b4b0::Call()
{
    return mMember.Call();
}
