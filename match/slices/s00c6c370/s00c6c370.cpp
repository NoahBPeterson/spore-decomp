// Scalar deleting destructor (0x00c6c370): run the destructor (0xc6bde0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c6c370(void* p);   // 0x00f47380

struct Object_c6c370 {
    ~Object_c6c370();        // 0x00c6bde0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c6c370
void* Object_c6c370::DeletingDtor(unsigned int flags)
{
    this->~Object_c6c370();
    if (flags & 1)
        Free_c6c370(this);
    return this;
}
