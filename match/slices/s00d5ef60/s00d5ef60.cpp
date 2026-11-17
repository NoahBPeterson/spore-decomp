// Scalar deleting destructor (0x00d5ef60): run the destructor (0xd5ea70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d5ef60(void* p);   // 0x00f47380

struct Object_d5ef60 {
    ~Object_d5ef60();        // 0x00d5ea70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d5ef60
void* Object_d5ef60::DeletingDtor(unsigned int flags)
{
    this->~Object_d5ef60();
    if (flags & 1)
        Free_d5ef60(this);
    return this;
}
