// Scalar deleting destructor (0x00a66950): run the destructor (0xa66830), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a66950(void* p);   // 0x00f47380

struct Object_a66950 {
    ~Object_a66950();        // 0x00a66830
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a66950
void* Object_a66950::DeletingDtor(unsigned int flags)
{
    this->~Object_a66950();
    if (flags & 1)
        Free_a66950(this);
    return this;
}
