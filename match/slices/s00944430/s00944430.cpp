// Scalar deleting destructor (0x00944430): run the destructor (0x944380), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_944430(void* p);   // 0x00f47380

struct Object_944430 {
    ~Object_944430();        // 0x00944380
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00944430
void* Object_944430::DeletingDtor(unsigned int flags)
{
    this->~Object_944430();
    if (flags & 1)
        Free_944430(this);
    return this;
}
