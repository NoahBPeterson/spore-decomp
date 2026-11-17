// Scalar deleting destructor (0x007abc70): run the destructor (0x7ab2f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7abc70(void* p);   // 0x00f47380

struct Object_7abc70 {
    ~Object_7abc70();        // 0x007ab2f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007abc70
void* Object_7abc70::DeletingDtor(unsigned int flags)
{
    this->~Object_7abc70();
    if (flags & 1)
        Free_7abc70(this);
    return this;
}
