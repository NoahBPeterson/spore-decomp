// Scalar deleting destructor (0x00f39560): run the destructor (0xf39220), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f39560(void* p);   // 0x00f47380

struct Object_f39560 {
    ~Object_f39560();        // 0x00f39220
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f39560
void* Object_f39560::DeletingDtor(unsigned int flags)
{
    this->~Object_f39560();
    if (flags & 1)
        Free_f39560(this);
    return this;
}
