// Scalar deleting destructor (0x007e5410): run the destructor (0x7e4bc0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7e5410(void* p);   // 0x00f47380

struct Object_7e5410 {
    ~Object_7e5410();        // 0x007e4bc0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007e5410
void* Object_7e5410::DeletingDtor(unsigned int flags)
{
    this->~Object_7e5410();
    if (flags & 1)
        Free_7e5410(this);
    return this;
}
