// Scalar deleting destructor (0x00c1fe60): run the destructor (0xc1bbd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c1fe60(void* p);   // 0x00f47380

struct Object_c1fe60 {
    ~Object_c1fe60();        // 0x00c1bbd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c1fe60
void* Object_c1fe60::DeletingDtor(unsigned int flags)
{
    this->~Object_c1fe60();
    if (flags & 1)
        Free_c1fe60(this);
    return this;
}
