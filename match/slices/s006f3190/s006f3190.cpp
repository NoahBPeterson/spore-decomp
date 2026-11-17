// Scalar deleting destructor (0x006f3190): run the destructor (0x6f3030), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6f3190(void* p);   // 0x00f47380

struct Object_6f3190 {
    ~Object_6f3190();        // 0x006f3030
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006f3190
void* Object_6f3190::DeletingDtor(unsigned int flags)
{
    this->~Object_6f3190();
    if (flags & 1)
        Free_6f3190(this);
    return this;
}
