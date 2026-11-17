// Forwarder (0x00bf9770): pass the call on to the embedded member object at +0x6c (0xbf9700, tail call).
#include "game/types.h"

struct Member_bf9770 {
    char mData[4];
    void* Call();   // 0x00bf9700
};
struct Owner_bf9770 {
    char mPad[0x6c];
    Member_bf9770 mMember;                       // +0x6c
    void* Call();
};

// @ 0x00bf9770
void* Owner_bf9770::Call()
{
    return mMember.Call();
}
