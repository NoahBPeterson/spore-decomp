// Scalar deleting destructor (0x00c65e60): run the destructor (0xc653e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c65e60(void* p);   // 0x00f47380

struct Object_c65e60 {
    ~Object_c65e60();        // 0x00c653e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c65e60
void* Object_c65e60::DeletingDtor(unsigned int flags)
{
    this->~Object_c65e60();
    if (flags & 1)
        Free_c65e60(this);
    return this;
}
