// Scalar deleting destructor (0x008d3430): run the destructor (0x8d3130), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8d3430(void* p);   // 0x00f47380

struct Object_8d3430 {
    ~Object_8d3430();        // 0x008d3130
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008d3430
void* Object_8d3430::DeletingDtor(unsigned int flags)
{
    this->~Object_8d3430();
    if (flags & 1)
        Free_8d3430(this);
    return this;
}
