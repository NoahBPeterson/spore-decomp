// Forwarder (0x007faac0): pass the call on to the embedded member object at +0x4 (0x5454f0, tail call).
#include "game/types.h"

struct Member_7faac0 {
    char mData[4];
    void* Call();   // 0x005454f0
};
struct Owner_7faac0 {
    char mPad[0x4];
    Member_7faac0 mMember;                       // +0x4
    void* Call();
};

// @ 0x007faac0
void* Owner_7faac0::Call()
{
    return mMember.Call();
}
