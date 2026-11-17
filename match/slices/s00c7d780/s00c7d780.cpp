// Scalar deleting destructor (0x00c7d780): run the destructor (0xc7d650), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c7d780(void* p);   // 0x00f47380

struct Object_c7d780 {
    ~Object_c7d780();        // 0x00c7d650
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c7d780
void* Object_c7d780::DeletingDtor(unsigned int flags)
{
    this->~Object_c7d780();
    if (flags & 1)
        Free_c7d780(this);
    return this;
}
