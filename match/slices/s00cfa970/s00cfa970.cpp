// Scalar deleting destructor (0x00cfa970): run the destructor (0xcf9a80), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cfa970(void* p);   // 0x00f47380

struct Object_cfa970 {
    ~Object_cfa970();        // 0x00cf9a80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cfa970
void* Object_cfa970::DeletingDtor(unsigned int flags)
{
    this->~Object_cfa970();
    if (flags & 1)
        Free_cfa970(this);
    return this;
}
