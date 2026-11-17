// Scalar deleting destructor (0x00620720): run the destructor (0x8e4ba0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_620720(void* p);   // 0x00f47380

struct Object_620720 {
    ~Object_620720();        // 0x008e4ba0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00620720
void* Object_620720::DeletingDtor(unsigned int flags)
{
    this->~Object_620720();
    if (flags & 1)
        Free_620720(this);
    return this;
}
