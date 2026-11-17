// Scalar deleting destructor (0x007fda30): run the destructor (0x7faa70), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7fda30(void* p);   // 0x00951330

struct Object_7fda30 {
    ~Object_7fda30();        // 0x007faa70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007fda30
void* Object_7fda30::DeletingDtor(unsigned int flags)
{
    this->~Object_7fda30();
    if (flags & 1)
        Free_7fda30(this);
    return this;
}
