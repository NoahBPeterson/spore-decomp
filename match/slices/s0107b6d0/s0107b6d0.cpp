// Scalar deleting destructor (0x0107b6d0): run the destructor (0x107af00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_107b6d0(void* p);   // 0x00f47380

struct Object_107b6d0 {
    ~Object_107b6d0();        // 0x0107af00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0107b6d0
void* Object_107b6d0::DeletingDtor(unsigned int flags)
{
    this->~Object_107b6d0();
    if (flags & 1)
        Free_107b6d0(this);
    return this;
}
