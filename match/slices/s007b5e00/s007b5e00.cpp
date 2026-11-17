// Scalar deleting destructor (0x007b5e00): run the destructor (0x7b2a40), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b5e00(void* p);   // 0x00f47380

struct Object_7b5e00 {
    ~Object_7b5e00();        // 0x007b2a40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b5e00
void* Object_7b5e00::DeletingDtor(unsigned int flags)
{
    this->~Object_7b5e00();
    if (flags & 1)
        Free_7b5e00(this);
    return this;
}
