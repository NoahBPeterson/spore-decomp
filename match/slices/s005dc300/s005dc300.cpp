// Forwarder (0x005dc300): pass the call on to the embedded member object at +0x14 (0x810070, tail call).
#include "game/types.h"

struct Member_5dc300 {
    char mData[4];
    void* Call();   // 0x00810070
};
struct Owner_5dc300 {
    char mPad[0x14];
    Member_5dc300 mMember;                       // +0x14
    void* Call();
};

// @ 0x005dc300
void* Owner_5dc300::Call()
{
    return mMember.Call();
}
