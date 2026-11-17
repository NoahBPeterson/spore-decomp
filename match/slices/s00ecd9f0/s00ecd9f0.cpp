// Forwarder (0x00ecd9f0): pass the call on to the embedded member object at +0x6c (0x97da40, tail call).
#include "game/types.h"

struct Member_ecd9f0 {
    char mData[4];
    void* Call();   // 0x0097da40
};
struct Owner_ecd9f0 {
    char mPad[0x6c];
    Member_ecd9f0 mMember;                       // +0x6c
    void* Call();
};

// @ 0x00ecd9f0
void* Owner_ecd9f0::Call()
{
    return mMember.Call();
}
