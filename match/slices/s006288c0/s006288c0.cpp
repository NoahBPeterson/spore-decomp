// Forwarder (0x006288c0): pass the call on to the embedded member object at +0x1e8 (0x63ecd0, tail call).
#include "game/types.h"

struct Member_6288c0 {
    char mData[4];
    void* Call();   // 0x0063ecd0
};
struct Owner_6288c0 {
    char mPad[0x1e8];
    Member_6288c0 mMember;                       // +0x1e8
    void* Call();
};

// @ 0x006288c0
void* Owner_6288c0::Call()
{
    return mMember.Call();
}
