// Scalar deleting destructor (0x00623c70): run the destructor (0x623280), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_623c70(void* p);   // 0x00951330

struct Object_623c70 {
    ~Object_623c70();        // 0x00623280
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00623c70
void* Object_623c70::DeletingDtor(unsigned int flags)
{
    this->~Object_623c70();
    if (flags & 1)
        Free_623c70(this);
    return this;
}
