// Forwarder (0x0109c720): pass the call on to the embedded member object at +0x1c0 (0x107f820, tail call).
#include "game/types.h"

struct Member_109c720 {
    char mData[4];
    void* Call();   // 0x0107f820
};
struct Owner_109c720 {
    char mPad[0x1c0];
    Member_109c720 mMember;                       // +0x1c0
    void* Call();
};

// @ 0x0109c720
void* Owner_109c720::Call()
{
    return mMember.Call();
}
