// Scalar deleting destructor (0x00bd1a90): run the destructor (0xbd0dd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bd1a90(void* p);   // 0x00f47380

struct Object_bd1a90 {
    ~Object_bd1a90();        // 0x00bd0dd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bd1a90
void* Object_bd1a90::DeletingDtor(unsigned int flags)
{
    this->~Object_bd1a90();
    if (flags & 1)
        Free_bd1a90(this);
    return this;
}
