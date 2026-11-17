// Scalar deleting destructor (0x0096e060): run the destructor (0x96d640), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_96e060(void* p);   // 0x00951330

struct Object_96e060 {
    ~Object_96e060();        // 0x0096d640
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0096e060
void* Object_96e060::DeletingDtor(unsigned int flags)
{
    this->~Object_96e060();
    if (flags & 1)
        Free_96e060(this);
    return this;
}
