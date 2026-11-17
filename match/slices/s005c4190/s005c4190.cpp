// Scalar deleting destructor (0x005c4190): run the destructor (0x5c3f60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5c4190(void* p);   // 0x00f47380

struct Object_5c4190 {
    ~Object_5c4190();        // 0x005c3f60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005c4190
void* Object_5c4190::DeletingDtor(unsigned int flags)
{
    this->~Object_5c4190();
    if (flags & 1)
        Free_5c4190(this);
    return this;
}
