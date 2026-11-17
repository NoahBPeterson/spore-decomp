// Scalar deleting destructor (0x006a1d60): run the destructor (0x6a1bd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6a1d60(void* p);   // 0x00f47380

struct Object_6a1d60 {
    ~Object_6a1d60();        // 0x006a1bd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006a1d60
void* Object_6a1d60::DeletingDtor(unsigned int flags)
{
    this->~Object_6a1d60();
    if (flags & 1)
        Free_6a1d60(this);
    return this;
}
