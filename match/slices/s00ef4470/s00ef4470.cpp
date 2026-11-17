// Forwarder (0x00ef4470): pass the call on to the embedded member object at +0x1c (0x6b55c0, tail call).
#include "game/types.h"

struct Member_ef4470 {
    char mData[4];
    void* Call();   // 0x006b55c0
};
struct Owner_ef4470 {
    char mPad[0x1c];
    Member_ef4470 mMember;                       // +0x1c
    void* Call();
};

// @ 0x00ef4470
void* Owner_ef4470::Call()
{
    return mMember.Call();
}
