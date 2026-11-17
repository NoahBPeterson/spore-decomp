// Scalar deleting destructor (0x007ef710): run the destructor (0x7ef560), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7ef710(void* p);   // 0x00f47380

struct Object_7ef710 {
    ~Object_7ef710();        // 0x007ef560
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007ef710
void* Object_7ef710::DeletingDtor(unsigned int flags)
{
    this->~Object_7ef710();
    if (flags & 1)
        Free_7ef710(this);
    return this;
}
