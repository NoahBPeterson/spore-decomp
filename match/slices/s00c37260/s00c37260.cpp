// Forwarder (0x00c37260): pass the call on to the embedded member object at +0x7b8 (0xbc3190, tail call).
#include "game/types.h"

struct Member_c37260 {
    char mData[4];
    void* Call();   // 0x00bc3190
};
struct Owner_c37260 {
    char mPad[0x7b8];
    Member_c37260 mMember;                       // +0x7b8
    void* Call();
};

// @ 0x00c37260
void* Owner_c37260::Call()
{
    return mMember.Call();
}
