// Scalar deleting destructor (0x0068dcf0): run the destructor (0x68dc90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_68dcf0(void* p);   // 0x00f47380

struct Object_68dcf0 {
    ~Object_68dcf0();        // 0x0068dc90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0068dcf0
void* Object_68dcf0::DeletingDtor(unsigned int flags)
{
    this->~Object_68dcf0();
    if (flags & 1)
        Free_68dcf0(this);
    return this;
}
