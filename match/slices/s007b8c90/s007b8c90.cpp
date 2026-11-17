// Scalar deleting destructor (0x007b8c90): run the destructor (0x7b8780), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b8c90(void* p);   // 0x00f47380

struct Object_7b8c90 {
    ~Object_7b8c90();        // 0x007b8780
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b8c90
void* Object_7b8c90::DeletingDtor(unsigned int flags)
{
    this->~Object_7b8c90();
    if (flags & 1)
        Free_7b8c90(this);
    return this;
}
