// Forwarder (0x0112bbc0): pass the call on to the embedded member object at +0x8 (0x107de70, tail call).
#include "game/types.h"

struct Member_112bbc0 {
    char mData[4];
    void* Call();   // 0x0107de70
};
struct Owner_112bbc0 {
    char mPad[0x8];
    Member_112bbc0 mMember;                       // +0x8
    void* Call();
};

// @ 0x0112bbc0
void* Owner_112bbc0::Call()
{
    return mMember.Call();
}
