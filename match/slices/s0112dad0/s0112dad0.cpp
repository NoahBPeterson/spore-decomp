// Forwarder (0x0112dad0): pass the call on to the embedded member object at +0x60 (0x112d940, tail call).
#include "game/types.h"

struct Member_112dad0 {
    char mData[4];
    void* Call();   // 0x0112d940
};
struct Owner_112dad0 {
    char mPad[0x60];
    Member_112dad0 mMember;                       // +0x60
    void* Call();
};

// @ 0x0112dad0
void* Owner_112dad0::Call()
{
    return mMember.Call();
}
