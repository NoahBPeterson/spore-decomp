// Scalar deleting destructor (0x00fd8170): run the destructor (0xfd7cd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fd8170(void* p);   // 0x00f47380

struct Object_fd8170 {
    ~Object_fd8170();        // 0x00fd7cd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fd8170
void* Object_fd8170::DeletingDtor(unsigned int flags)
{
    this->~Object_fd8170();
    if (flags & 1)
        Free_fd8170(this);
    return this;
}
