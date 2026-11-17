// Scalar deleting destructor (0x0096e330): run the destructor (0x96e260), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_96e330(void* p);   // 0x00951330

struct Object_96e330 {
    ~Object_96e330();        // 0x0096e260
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0096e330
void* Object_96e330::DeletingDtor(unsigned int flags)
{
    this->~Object_96e330();
    if (flags & 1)
        Free_96e330(this);
    return this;
}
