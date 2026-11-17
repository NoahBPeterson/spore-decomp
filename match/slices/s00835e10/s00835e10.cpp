// Scalar deleting destructor (0x00835e10): run the destructor (0x835d90), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_835e10(void* p);   // 0x00951330

struct Object_835e10 {
    ~Object_835e10();        // 0x00835d90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00835e10
void* Object_835e10::DeletingDtor(unsigned int flags)
{
    this->~Object_835e10();
    if (flags & 1)
        Free_835e10(this);
    return this;
}
