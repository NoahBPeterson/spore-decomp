// Forwarder (0x00705f30): pass the call on to the embedded member object at +0x64 (0x537dc0, tail call).
#include "game/types.h"

struct Member_705f30 {
    char mData[4];
    void* Call();   // 0x00537dc0
};
struct Owner_705f30 {
    char mPad[0x64];
    Member_705f30 mMember;                       // +0x64
    void* Call();
};

// @ 0x00705f30
void* Owner_705f30::Call()
{
    return mMember.Call();
}
