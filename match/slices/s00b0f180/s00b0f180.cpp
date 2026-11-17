// Forwarder (0x00b0f180): pass the call on to the embedded member object at +0x31c (0x697a10, tail call).
#include "game/types.h"

struct Member_b0f180 {
    char mData[4];
    void* Call();   // 0x00697a10
};
struct Owner_b0f180 {
    char mPad[0x31c];
    Member_b0f180 mMember;                       // +0x31c
    void* Call();
};

// @ 0x00b0f180
void* Owner_b0f180::Call()
{
    return mMember.Call();
}
