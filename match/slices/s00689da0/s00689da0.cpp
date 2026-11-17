// Scalar deleting destructor (0x00689da0): run the destructor (0x689880), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_689da0(void* p);   // 0x00f47380

struct Object_689da0 {
    ~Object_689da0();        // 0x00689880
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00689da0
void* Object_689da0::DeletingDtor(unsigned int flags)
{
    this->~Object_689da0();
    if (flags & 1)
        Free_689da0(this);
    return this;
}
