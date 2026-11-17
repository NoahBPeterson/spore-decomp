// Scalar deleting destructor (0x00755500): run the destructor (0x755470), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_755500(void* p);   // 0x00f47380

struct Object_755500 {
    ~Object_755500();        // 0x00755470
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00755500
void* Object_755500::DeletingDtor(unsigned int flags)
{
    this->~Object_755500();
    if (flags & 1)
        Free_755500(this);
    return this;
}
