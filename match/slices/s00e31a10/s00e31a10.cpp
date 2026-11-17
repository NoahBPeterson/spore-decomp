// Forwarder (0x00e31a10): pass the call on to the embedded member object at +0xc (0x810590, tail call).
#include "game/types.h"

struct Member_e31a10 {
    char mData[4];
    void* Call();   // 0x00810590
};
struct Owner_e31a10 {
    char mPad[0xc];
    Member_e31a10 mMember;                       // +0xc
    void* Call();
};

// @ 0x00e31a10
void* Owner_e31a10::Call()
{
    return mMember.Call();
}
