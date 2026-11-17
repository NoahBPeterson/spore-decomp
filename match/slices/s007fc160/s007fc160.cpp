// Forwarder (0x007fc160): pass the call on to the embedded member object at +0x8 (0x453540, tail call).
#include "game/types.h"

struct Member_7fc160 {
    char mData[4];
    void* Call();   // 0x00453540
};
struct Owner_7fc160 {
    char mPad[0x8];
    Member_7fc160 mMember;                       // +0x8
    void* Call();
};

// @ 0x007fc160
void* Owner_7fc160::Call()
{
    return mMember.Call();
}
