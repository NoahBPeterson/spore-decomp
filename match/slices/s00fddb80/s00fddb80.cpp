// Scalar deleting destructor (0x00fddb80): run the destructor (0xfdcba0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fddb80(void* p);   // 0x00f47380

struct Object_fddb80 {
    ~Object_fddb80();        // 0x00fdcba0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fddb80
void* Object_fddb80::DeletingDtor(unsigned int flags)
{
    this->~Object_fddb80();
    if (flags & 1)
        Free_fddb80(this);
    return this;
}
