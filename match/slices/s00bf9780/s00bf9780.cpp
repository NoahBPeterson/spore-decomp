// Forwarder (0x00bf9780): pass the call on to the embedded member object at +0x6c (0xbf9300, tail call).
#include "game/types.h"

struct Member_bf9780 {
    char mData[4];
    void* Call();   // 0x00bf9300
};
struct Owner_bf9780 {
    char mPad[0x6c];
    Member_bf9780 mMember;                       // +0x6c
    void* Call();
};

// @ 0x00bf9780
void* Owner_bf9780::Call()
{
    return mMember.Call();
}
