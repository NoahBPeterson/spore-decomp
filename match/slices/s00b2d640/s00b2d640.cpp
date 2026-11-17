// Scalar deleting destructor (0x00b2d640): run the destructor (0xb2cc40), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b2d640(void* p);   // 0x00f47380

struct Object_b2d640 {
    ~Object_b2d640();        // 0x00b2cc40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b2d640
void* Object_b2d640::DeletingDtor(unsigned int flags)
{
    this->~Object_b2d640();
    if (flags & 1)
        Free_b2d640(this);
    return this;
}
