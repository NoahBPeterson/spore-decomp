// Forwarder (0x00c75640): pass the call on to the embedded member object at +0x1258 (0xbc3110, tail call).
#include "game/types.h"

struct Member_c75640 {
    char mData[4];
    void* Call();   // 0x00bc3110
};
struct Owner_c75640 {
    char mPad[0x1258];
    Member_c75640 mMember;                       // +0x1258
    void* Call();
};

// @ 0x00c75640
void* Owner_c75640::Call()
{
    return mMember.Call();
}
