// Forwarder (0x00ddab00): pass the call on to the embedded member object at +0x38 (0x537dc0, tail call).
#include "game/types.h"

struct Member_ddab00 {
    char mData[4];
    void* Call();   // 0x00537dc0
};
struct Owner_ddab00 {
    char mPad[0x38];
    Member_ddab00 mMember;                       // +0x38
    void* Call();
};

// @ 0x00ddab00
void* Owner_ddab00::Call()
{
    return mMember.Call();
}
