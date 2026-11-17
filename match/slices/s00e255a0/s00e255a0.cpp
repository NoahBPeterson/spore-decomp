// Scalar deleting destructor (0x00e255a0): run the destructor (0xe24630), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e255a0(void* p);   // 0x00951330

struct Object_e255a0 {
    ~Object_e255a0();        // 0x00e24630
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e255a0
void* Object_e255a0::DeletingDtor(unsigned int flags)
{
    this->~Object_e255a0();
    if (flags & 1)
        Free_e255a0(this);
    return this;
}
