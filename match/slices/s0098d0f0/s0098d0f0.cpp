// Scalar deleting destructor (0x0098d0f0): run the destructor (0x98cbb0), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_98d0f0(void* p);   // 0x00951330

struct Object_98d0f0 {
    ~Object_98d0f0();        // 0x0098cbb0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0098d0f0
void* Object_98d0f0::DeletingDtor(unsigned int flags)
{
    this->~Object_98d0f0();
    if (flags & 1)
        Free_98d0f0(this);
    return this;
}
