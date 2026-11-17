// Scalar deleting destructor (0x0059a390): run the destructor (0x59a320), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_59a390(void* p);   // 0x00f47380

struct Object_59a390 {
    ~Object_59a390();        // 0x0059a320
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0059a390
void* Object_59a390::DeletingDtor(unsigned int flags)
{
    this->~Object_59a390();
    if (flags & 1)
        Free_59a390(this);
    return this;
}
