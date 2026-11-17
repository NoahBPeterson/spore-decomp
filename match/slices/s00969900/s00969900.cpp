// Scalar deleting destructor (0x00969900): run the destructor (0x9695d0), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_969900(void* p);   // 0x00951330

struct Object_969900 {
    ~Object_969900();        // 0x009695d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00969900
void* Object_969900::DeletingDtor(unsigned int flags)
{
    this->~Object_969900();
    if (flags & 1)
        Free_969900(this);
    return this;
}
