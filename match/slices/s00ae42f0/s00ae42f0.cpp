// Forwarder (0x00ae42f0): pass the call on to the embedded member object at +0x60 (0x576650, tail call).
#include "game/types.h"

struct Member_ae42f0 {
    char mData[4];
    void* Call();   // 0x00576650
};
struct Owner_ae42f0 {
    char mPad[0x60];
    Member_ae42f0 mMember;                       // +0x60
    void* Call();
};

// @ 0x00ae42f0
void* Owner_ae42f0::Call()
{
    return mMember.Call();
}
