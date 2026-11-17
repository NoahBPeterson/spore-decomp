// Scalar deleting destructor (0x00c6fb60): run the destructor (0xc3f250), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c6fb60(void* p);   // 0x00f47380

struct Object_c6fb60 {
    ~Object_c6fb60();        // 0x00c3f250
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c6fb60
void* Object_c6fb60::DeletingDtor(unsigned int flags)
{
    this->~Object_c6fb60();
    if (flags & 1)
        Free_c6fb60(this);
    return this;
}
