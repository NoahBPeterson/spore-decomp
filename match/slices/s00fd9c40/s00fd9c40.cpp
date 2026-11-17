// Scalar deleting destructor (0x00fd9c40): run the destructor (0xfd96d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fd9c40(void* p);   // 0x00f47380

struct Object_fd9c40 {
    ~Object_fd9c40();        // 0x00fd96d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fd9c40
void* Object_fd9c40::DeletingDtor(unsigned int flags)
{
    this->~Object_fd9c40();
    if (flags & 1)
        Free_fd9c40(this);
    return this;
}
