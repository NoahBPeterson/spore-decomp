// Scalar deleting destructor (0x00999440): run the destructor (0x999110), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_999440(void* p);   // 0x00f47380

struct Object_999440 {
    ~Object_999440();        // 0x00999110
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00999440
void* Object_999440::DeletingDtor(unsigned int flags)
{
    this->~Object_999440();
    if (flags & 1)
        Free_999440(this);
    return this;
}
