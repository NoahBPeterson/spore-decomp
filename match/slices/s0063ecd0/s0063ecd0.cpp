// Forwarder (0x0063ecd0): pass the call on to the embedded member object at +0x50 (0x62fd60, tail call).
#include "game/types.h"

struct Member_63ecd0 {
    char mData[4];
    void* Call();   // 0x0062fd60
};
struct Owner_63ecd0 {
    char mPad[0x50];
    Member_63ecd0 mMember;                       // +0x50
    void* Call();
};

// @ 0x0063ecd0
void* Owner_63ecd0::Call()
{
    return mMember.Call();
}
