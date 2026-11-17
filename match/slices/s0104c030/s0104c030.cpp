// Forwarder (0x0104c030): pass the call on to the embedded member object at +0x258 (0x6b55c0, tail call).
#include "game/types.h"

struct Member_104c030 {
    char mData[4];
    void* Call();   // 0x006b55c0
};
struct Owner_104c030 {
    char mPad[0x258];
    Member_104c030 mMember;                       // +0x258
    void* Call();
};

// @ 0x0104c030
void* Owner_104c030::Call()
{
    return mMember.Call();
}
