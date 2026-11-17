// Scalar deleting destructor (0x0065bd60): run the destructor (0x65ba20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_65bd60(void* p);   // 0x00f47380

struct Object_65bd60 {
    ~Object_65bd60();        // 0x0065ba20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0065bd60
void* Object_65bd60::DeletingDtor(unsigned int flags)
{
    this->~Object_65bd60();
    if (flags & 1)
        Free_65bd60(this);
    return this;
}
