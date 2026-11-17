// Scalar deleting destructor (0x00ef9ad0): run the destructor (0xef9180), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ef9ad0(void* p);   // 0x00f47380

struct Object_ef9ad0 {
    ~Object_ef9ad0();        // 0x00ef9180
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ef9ad0
void* Object_ef9ad0::DeletingDtor(unsigned int flags)
{
    this->~Object_ef9ad0();
    if (flags & 1)
        Free_ef9ad0(this);
    return this;
}
