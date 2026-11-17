// Forwarder (0x00781ca0): pass the call on to the embedded member object at +0x4 (0x781b10, tail call).
#include "game/types.h"

struct Member_781ca0 {
    char mData[4];
    void* Call();   // 0x00781b10
};
struct Owner_781ca0 {
    char mPad[0x4];
    Member_781ca0 mMember;                       // +0x4
    void* Call();
};

// @ 0x00781ca0
void* Owner_781ca0::Call()
{
    return mMember.Call();
}
