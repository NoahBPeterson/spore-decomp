// Scalar deleting destructor (0x00ef3e20): run the destructor (0xef3bf0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ef3e20(void* p);   // 0x00f47380

struct Object_ef3e20 {
    ~Object_ef3e20();        // 0x00ef3bf0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ef3e20
void* Object_ef3e20::DeletingDtor(unsigned int flags)
{
    this->~Object_ef3e20();
    if (flags & 1)
        Free_ef3e20(this);
    return this;
}
